现在开始基于ATSAM4S-XPRO移植LiteOS。

PS：以下内容属个人见解，不足之处欢迎批评指正！

1.首先我们从下面的框图中大概了解一下LiteOS Kernel

![](meta/basicframe.png)

该图已经很好地描述了LiteOS Kernel的特性，我仅从移植角度再次分块。

- 系统时钟：系统内核时钟一般由Systick提供，是系统时间核心，所以移植时必定涉及SysTick_Config配置；
- 硬件中断：MCU除了内核中断外还有外设中断，中断响应涉及到中断向量表等相关概念，LiteOS可以接管这些中断，因此会涉及到中断向量表是否重载；
- 内存管理：MCU内存由LiteOS接管，因此我们需要知道该MCU的RAM大小等详细内容，重载中断向量表时以便配置分散加载文件；
- 任务调度：任务调度的核心的汇编实现，与MCU内核相关（M3/M4/M4F）；

更详细的内容请直接访问：[https://github.com/LITEOS/LiteOS_Kernel](https://github.com/LITEOS/LiteOS_Kernel)

2.明确任务目标

--参赛者需要适配Key、Led、Uart等基本驱动代码到移植的工程

从移植流程来说，笔者不是拿到开发板就直接开始移植工作，而是先搭建开发环境，基于裸机完成Key、Led、Uart等驱动的编写和调试，所以我真正开始移植的时候这些模块相关操作代码已经完成，通过这个过程不仅可以加深对MCU的认识，也使以后移植过程事半功倍成为可能。嘿嘿。

3.开始移植

首先在github上[https://github.com/LITEOS/LiteOS_Kernel](https://github.com/LITEOS/LiteOS_Kernel)获取LiteOS最新的代码和文档获取源码

![](meta/git_down.png)

解压后大致看一下目录结构

![](meta/catal.png)

我们需要做的就是：

- project目录下新建工程文件夹存放工程文件
- platform目录下新建工程文件夹存放驱动文件

不多说，建工程一系列操作走一波...

然后就成下面这样了：

![](meta/catal-proj.png)

下面就一些问题说明：

- 因为LiteOS已经包含系统启动最小实现los_startup_keil.s，所以不需要pack的Device了，只保留CMSIS，然后user下的system_SAM4S.c是从pack的目录下面拷贝出来的，存放在platform下对应我开发板文件夹ATSAM4S-XPRO-KEIL了，之所添加这个文件是因为我想使用SystemInit这个函数配置系统时钟，而不是用MCU默认的时钟，如果使用默认时钟不要这个文件也是可以的。
- SAM4SD32C是Cortex-M4内核，然而我却使用的cpu/m3/los_dispatch_keil.s是因为这颗U不带FPU，而最新LiteOS内核代码结构调整，m4对应los_dispatch_keil.s使用了几个浮点汇编指令，所以编译不过，只能使用m3的，进一步说，不带浮点的话m3和m4基本是一样的，这一点也和华为LiteOS的工程师沟通过，为了不改动原有LiteOS代码，所以综合评估后使用m3的，在此申明！

关于是否能够使用浮点功能，在Keil中看有没有这个选项：

![](meta/fpu-keil.png)

所以这里也提一个小建议吧，建议按m3/m4/m4f分类，才疏学浅，不知道这个问题是不是很小白，见谅...

4.细节说明

- 关于C99、Use MicroLIB就不说了，分散加载文件需要根据实际RAM大小配置LiteOS_Migration_Guide_Keil.md文档已经有相关叙述，而且目前已经有一部分移植成功的工程可以参考，不重载中断向量表的话是不用配置的。

- 就bsp驱动来说，可以先拷贝别的工程到自己的平台文件夹，然后只是改写核心实现，函数形式尽量保持不变，以los_bsp_key.c为例：

<pre>
#ifdef ATSAM4S_XPRO
#include "sam4s.h"
#endif

void LOS_EvbKeyInit(void) 
{
#ifdef ATSAM4S_XPRO	
  PMC->PMC_WPMR = 0x504D4300;             /* Disable write protect            */

  PMC->PMC_PCER0 = (1UL << ID_PIOA);      /* enable clock for push button     */

  PIOA->PIO_PUER =
  PIOA->PIO_IDR  =
  PIOA->PIO_ODR  =
  PIOA->PIO_PER  = (PIO_PA2);             /* Setup PA2 for user button SW0    */

  PMC->PMC_WPMR = 0x504D4301;             /* Enable write protect             */
#endif
	return;
}
</pre>

los_bsp_adapter.c中也有类似于：

<pre>
#ifdef ATSAM4S_XPRO
		SysTick_Config(g_ucycle_per_tick);
#else
</pre>

- 通过宏定义开关选择配置，我用到的宏定义有：ATSAM4S_XPRO,__SAM4SD32C__，ATSAM4S_XPRO的用途如上，__SAM4SD32C__是sam4s.h需要以包含真正的头文件sam4sd32c.h

- 修改时钟相关配置，在main函数中调用SystemInit后本平台将系统时钟配置到96MHz，相应的：

1.在los_config.h中大致57行位置修改#define OS_SYS_CLOCK 96000000

2.在los_bsp_adapter.c中大致36行位置修改const unsigned int sys_clk_freq = 96000000

##总结
总的来说要改动的地方不多，只涉及到main.c/bsp系列.c/los_config.h，好像就是这样，那看看效果啊：

![](meta/result.png)

![](meta/result-real.png)

