## 1关于本文档的开源协议说明
**您可以自由地：**

**分享** 

- 在任何媒介以任何形式复制、发行本文档

**演绎** 

- 修改、转换或以本文档为基础进行创作。只要你遵守许可协议条款，许可人就无法收回你的这些权利。

**惟须遵守下列条件：**

**署名** 

- 您必须提供适当的证书，提供一个链接到许可证，并指示是否作出更改。您可以以任何合理的方式这样做，但不是以任何方式表明，许可方赞同您或您的使用。

**非商业性使用** 

- 您不得将本作品用于商业目的。

**相同方式共享** 

- 如果您的修改、转换，或以本文档为基础进行创作，仅得依本素材的
授权条款来散布您的贡献作品。

**没有附加限制** 

- 您不能增设法律条款或科技措施，来限制别人依授权条款本已许可的作为。

**声明：**

-  当您使用本素材中属于公众领域的元素，或当法律有例外或限制条款允许您的使用，
则您不需要遵守本授权条款。
未提供保证。本授权条款未必能完全提供您预期用途所需要的所有许可。例如：形象
权、隐私权、著作人格权等其他权利，可能限制您如何使用本素材。

**注意**

- 为了方便用户理解，这是协议的概述. 可以访问网址 https://creativecommons.org/licenses/by-sa/3.0/legalcode 了解完整协议内容.

## 2前言
### 目的

本文档介如何移植Huawei LiteOS到第三方开发板，并成功运行基础示例。

### 读者对象

本文档主要适用于使用Huawei LiteOS Kernel进行开发的开发者。

本文档主要适用于以下对象：

- 物联网端软件开发工程师

- 物联网架构设计师

### 符号约定
在本文中可能出现下列标志，它们所代表的含义如下。


![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/danger.png)     用于警示紧急的危险情形，若不避免，将会导致人员死亡或严重的人身伤害

![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/warning.png)     用于警示潜在的危险情形，若不避免，可能会导致人员死亡或严重的人身伤害

![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/careful.png)     用于警示潜在的危险情形，若不避免，可能会导致中度或轻微的人身伤害

![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/notice.png)      用于传递设备或环境安全警示信息，若不避免，可能会导致设备损坏、数据丢失、设备性能降低或其它不可预知的结果“注意”不涉及人身伤害

| 说明	|		“说明”不是安全警示信息，不涉及人身、设备及环境伤害信息	|

### 修订记录
修改记录累积了每次文档更新的说明。最新版本的文档包含以前所有文档版本的更新内容。

日期 | 修订版本 | 描述
---|--- |---
2017年06月21日 | 1.0 | 完成初稿




## 3概述
目前在github上已开源的Huawei LiteOS_Kernel源码已适配好STM32F412、STM32F429、STM32L476、GD32F450、GD32F190等芯片的keil示例工程，但是还没有NRF52832芯片的keil示例工程，这里就此芯片做LiteOS移植说明。
## 4环境准备
- 基于Huawei LiteOS Kernel开发前，我们首先需要准备好单板运行的环境，包括软件环 境和硬件环境。

硬件环境：


所需硬件 | 描述
---|--- 
开发板 | 基于Cortex-M4内核芯片开发板NRF52DK
PC机 | 用于编译、加载并调试镜像
电源 | 开发板供电
- 软件环境：

软件 | 描述  
---|---
Window 7  操作系统 | 安装Keil和相关调试驱动的操作系统
Keil(5.18以上版本) | 用于编译、链接、调试程序代码 uVision V5.18a
Link驱动 | 开发板与pc连接的驱动程序，用户加载及调试程序代码
开发板对应的pack | NordicSemiconductor.nRF_DeviceFamilyPack.8.12.0.pack
SDK 、nRFgo studio、板子原理图、spec | sdk包含一些外设驱动demo、nRFgo studio 可以烧写代码驱动，本工程下载的SDK 是nRF5_SDK_13.0.0_04a0bfd，硬件文件是nRF52 Development Kit - Hardware files 1_1_1，DataSheet是nRF52832_PS_v1.3.pdf


说明

Keil工具需要开发者自行购买，Link在keil5.18安装以后就有，开发需要对应芯片的pack文件，可以到NRODIC官网搜索也可以到keil官网下载，NRODIC官网http://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832
## 5获取Huawei LiteOS 源码
首先下载Huawei LiteOS开发包，步骤如下：

 - 仓库地址：https://github.com/LITEOS/LiteOS_Kernel.git 
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/5-1.png) 
 
  - 点击”clone or download”按钮,下载源代码
  
  - 目录结构如下： 
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/5-2.png) 
 
- 关于代码树中各个目录存放的源代码的相关内容简介如下：







| 一级目录 | 二级目录                | 说明                                                                                                                                                                     |
|----------|-------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| doc      |                         | 此目录存放的是LiteOS的使用文档和API说明文档                                                                                                                              |
| example  | api                     | 此目录存放的是内核功能测试用的相关用例的代码                                                                                                                             |
|          | include                 | aip功能头文件存放目录                                                                                                                                                    |
| kernel   | base                    | 此目录存放的是与平台无关的内核代码，包含核心提供给外部调用的接口的头文件以及内核中进程调度、进程通信、内存管理等等功能的核心代码。用户一般不需要修改此目录下的相关内容。 |
|          | cmsis                   | LiteOS提供的cmsis接口                                                                                                                                                    |
|          | config                  | 此目录下是内核资源配置相关的代码，在头文件中配置了LiteOS所提供的各种资源所占用的内存池的总大小以及各种资源的数量，例如task的最大个数、信号量的最大个数等等               |
|          | cpu                     | 此目录以及以下目录存放的是与体系架构紧密相关的适配LiteOS的代码。比如目前我们适配了arm/cortex-m4及arm/cortex-m3系列对应的初始化内容。                                     |
|          | include                 | 内核的相关头文件存放目录                                                                                                                                                 |
|          | link                    | 与IDE相关的编译链接相关宏定义                                                                                                                                            |
| platform | GD32F190R-EVAL          | GD190开发板systick以及led、uart、key驱动bsp适配代码                                                                                                                      |
|          | GD32F450i-EVAL          | GD450开发板systick以及led、uart、key驱动bsp适配代码                                                                                                                      |
|          | STM32F412ZG-NUCLEO      | STM32F412开发板systick以及led、uart、key驱动bsp适配代码                                                                                                                  |
|          | STM32F429I_DISCO        | STM32F429开发板systick以及led、uart、key驱动bsp适配代码                                                                                                                  |
|          | STM32L476RG_NUCLEO      | STM32L476开发板systick以及led、uart、key驱动bsp适配代码                                                                                                                  |
|          | LPC824_LITE             | LPC824Lite开发板systick及驱动相关代码                                                                                                                                    |
|          | LPC54110_BOARD          | LPC54110开发板systick及驱动相关代码                                                                                                                                      |
|          | MM32F103_MINI           | MM32F103开发板systick及驱动相关代码                                                                                                                                      |
|          | STM32F746ZG_NUCLEO      | STM32F746ZG开发板systick以及led、uart、key驱动bsp适配代码                                                                                                                |
|          | LOS_EXPAND_XXX          | 用于新扩展的开发板systick以及led、uart、key驱动bsp适配代码                                                                                                               |
| projects | STM32F412ZG-NUCLEO-KEIL | stm32f412开发板的keil工程目录                                                                                                                                            |
|          | STM32F429I_DISCO_IAR    | stm32f429开发板的iar工程目录                                                                                                                                             |
|          | STM32F429I_DISCO_KEIL   | stm32f429开发板的keil工程目录                                                                                                                                            |
|          | STM32L476R-NUCLEO-KEIL  | stm32l476开发板的keil工程目录                                                                                                                                            |
|          | GD32F190R-EVAL-KEIL     | gd32f190开发板的keil工程目录                                                                                                                                             |
|          | GD32F450i-EVAL-KEIL     | gd32f450开发板的keil工程目录                                                                                                                                             |
|          | LPC824_LITE_KEIL        | lpc824Lite开发板的keil工程目录                                                                                                                                           |
|          | LPC54110_BOARD_KEIL     | lpc54110开发板的keil工程目录                                                                                                                                             |
|          | MM32F103_MINI_KEIL      | MindMotion MM32 MiniBoard开发板的keil工程目录                                                                                                                            |
|          | STM32F746ZG-NUCLEO-KEIL | NUCLEO-F746ZG 开发板的keil工程目录                                                                                                                                       |
| user     |                         | 此目录存放用户测试代码，LiteOS的初始化和使用示例在main.c文件中                                                                                                           |

获取Huawei LiteOS源代码之后，我们就可以开始创建自己的project开发工程了，详细内容请参考后续各章节。


## 6创建Huawei LiteOS 工程
###  6.1 创建工程
获取到LiteOS内核代码后，在platform下创建NRF52-DK目录,并拷贝platform\LOS_EXPAND_XXX目录下的所有文件到新创建的MRF52-DK目录下。如果您本地有开发板相关的驱动代码，可以先将您本地的驱动代码库拷贝到platform\NRF52-DK\Library目录下，以便添加到工程中。
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-1-1.png) 
 
在安装好Keil等开发工具后，我们使用Keil集成开发环境创建Huawei LiteOS工程，步骤如下：
  ● 打开Keil uVision5， 然后点击project->New uVision Project...创建一个新的工程
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-1-2.png) 
 
  ● 新建保存在project目录下名字NRF52-DK_KEIL，作为本工程目录,添加工程名文件名，比如HuaweiLiteOS
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-1-3.png) 
 
  ● 保存后会立即弹出芯片型号选择的窗口，根据实际的开发板的芯片进行选择，比如使用的是NRF52832芯片。 
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-1-4.png) 
 
  ● 然后选择要包含的开发基础库，比如CMSIS、DEVICE两个选项可以选择平台提供的支持包和启动汇编文件，目前LiteOS有提供的启动文件是配合中断动态注册功能使用的，本工程移植没有用到动态中注册功能。而且使用LiteOS启动文件，没有打开相应动态中断注册功能的宏开关，可以正常使用。如果不使用LiteOS的启动文件和不需要使用动态中断注册功能，可以勾选startup，也可以在工程建好后手动添加启动文件，我在此处保持默认，直接选择"OK"跳过。
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-1-5.png) 
 
至此，我们的工程已经创建完成，如下图所示：
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-1-6.png) 
 
完成上面的芯片和支持包选择之后，可以将内核源代码添加到工程中。
### 6.2 添加kernel代码到工程
 - 创建LiteOS的相关目录层级
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-2-1.png) 
 
创建完成目录树之后我们添加源代码到目录树中，最终添加完成的内容如下：
 - 将kernel/base目录下的所有C文件添加到工程中的kernel下
 - 将kernel/cmsis目录下的所有C文件添加到工程中的cmsis下。
  - 将platform\LOS_EXPAND_XXX目录下的所有C文件添加到工程中的platform/expand_nrf52-dk下
 -  根据芯片内核型号，将kernel\cpu\arm\cortex-m4（或者cortex-m3）目录下的所有C文件以及汇编代码添加到工程中的cpu/m4（cpu/m3）下
 -  将kernel\config目录下的所有C文件添加到工程中的config下
 -  将user目录下的所有C文件添加到工程中的user下
 - 如果需要使用中断动态注册功能或者本地没有可用的启动文件，可以将platform\LOS_EXPAND_XXX目录下的los_startup_keil.s汇编文件添加到工程中的startup目录下，或者添加芯片官方提供的启动文件，比如您使用的是nrf52832芯片，可添加arm_startup_nrf52.s文件，这里注意，nrfdic还有个文件配合启动文件使用，这个文件是system_nrf52.c，如果不添加会报错。
 - 将\platform\NRF52-DK\Library目录下的驱动文件添加到工程的library目录下，同时把自己需要的驱动C文件添加进来，本工程添加了UART驱动。
 - 添加example/api目录下的所有C文件到工程的example目录
完成代码添加后的工程目录如下图
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-2-2.png) 
 

添加的UART文件
### 6.3 配置工程属性
  ● 配置target，如果需要调试log输出（printf）到IDE，可以选择Use MicroLib。
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-3-1.png) 
 
  ● 编译C/C++设置中勾选C99选项
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-3-2.png) 
 
  ● 配置头文件搜索路径,可参考图片中所示内容
  
....\kernel\base\include; 

....\kernel\include;

....\kernel\config;

....\kernel\cmsis;

....\kernel\link\keil;

....\kernel\cpu\arm\cortex-m4;

....\example\include;

....\platform\NRF52-DK;

....\platform\NRF52-DK\Library;

....\platform\NRF52-DK\Library\hal;

....\platform\NRF52-DK\Library\include;

 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-3-3.png) 
 

  - 配置debug使用的驱动，比如您使用的是nrf52832芯片，则使用选择J-LINK/J-TRACE Cortex，注意如果烧写出现“NO Cortex-M Device found in JTAG chain“
 - 注意打开"Options for Target 'LiteOS" 选项卡”Debug“，并点击旁边的”Setting“  然后选择SW。注意看下面图示。
 
配置窗口：
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-3-4.png) 
 


出现的烧写错误提示窗口：
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-3-5.png) 
 


配置SW图示：
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-3-6.png) 
 

  - 如果需要使用printf输出调试log，可以使用软件仿真的方式。打开 Debug (printf) Viewer窗口即可查看log。因为LiteOS有对log重定向，注意打开以下宏定义：    LOS_KERNEL_TEST_KEIL_SWSIMU才可以定向到 Debug (printf) Viewer窗口。
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/6-3-7.png) 
 
## 7适配驱动代码

 - 内核代码中提供了bsp适配的框架代码，存放在文件夹platform\NRF52-DK下。
     
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-1.png) 
      

  - 前面已经完成了驱动适配代码及驱动代码的添加，这里只有串口驱动文件nrf52_uart.c,gpio操作函数在nrf_gpio.h中，路径\platform\NRF52-DK\Library\hal。
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-2.png) 
 
  - 根据本地Library代码提供的接口函数，来实现LiteOS中相关的bsp接口函数
（1）修改los_bsp_adapter.c文件，配置系统时钟及SysTick，适配sysTick_Handler函数，本工程保持默认值即可；
（2）实现los_bsp_led.c、los_bsp_key.c、los_bsp_uart.c等文件中提供的空函数，相应gpio脚对应板子的外设可在开发板背面看到。也可以在官网下载原理图查看。los_bsp_led.c、los_bsp_key.c需要添加头文件nrf_gpio.h，才可以用bsp库函数对gpio操作。los_bsp_uart.c需要添加nrf52_uart.h头文件。
  - 实现key功能，预留初始化函数里设置开发板button1 对应的gpio 13 为输入，获取key状态的函数里添加button1 对应gpio 读函数。这里需注意一点，gpio需配置下拉，不然有时候按键释放LED灯还会亮。具体如下图：
    
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-3.png) 
  
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-4.png) 
 


  - 实现led功能，预留初始化函数配置开发板led1对应的gpio 17为输出，获取led 亮灭的函数里使用gpio操作函数置1或置0。具体如下图：
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-5.png) 
  
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-6.png) 
 
         


  - 实现UART功能，预留初始化函数调用平台UART 初始化接口对UART进行初始化，这里默认按开发板背面标示的gpio pin脚定义RTS 为5，  CTS为7，  TX为 6，  RX 8  FLOWCONTROL 为false，不使用流控，默认波特率115200，8位，无奇偶校验位，一停止位。在预留的UART 写byte函数里添加具体的UART写函数。然后在printf 重定向的fputc函数里的添加UART打印函数，这样才能把log打印到串口。最后打印的log 会布满屏幕，无法左对齐，所有需要对fputc函数做些调整。具体如下图：
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-7.png) 
  
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-8.png) 
  
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/7-1-9.png) 
 




## 8如何验证移植后的工程
如果您需要验证移植后的LiteOS内核功能，可以参考本章内容。
### 8.1 API测试代码使用
 - 目前LiteOS提供了单独测试每个功能的api代码，可在main()函数中调用los_demo_entry.c文件中的LOS_Demo_Entry()函数，并放开相应的宏定义。
  - 如果需要一次测试内核所有的功能，则可调用los_inspect_entry.c文件中的LOS_Inspect_Entry()函数。
 - LiteOS最小需要占用8K的RAM,使用Inspect巡检功能需要再增加1k RAM，nrf52832 芯片的RAM 64K足够inspect巡检功能。
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/8-1-1.png) 
 
示例代码如下：
extern void LOS_Demo_Entry(void)；
int main(void)
{
    UINT32 uwRet;
    /*
		add you hardware init code here
		for example flash, i2c , system clock ....
    */
	//HAL_init();....
	
	/*Init LiteOS kernel */
    uwRet = LOS_KernelInit();
    if (uwRet != LOS_OK) {
        return LOS_NOK;
    }
	/* Enable LiteOS system tick interrupt */
    LOS_EnableTick();
	
    /* 
        Notice: add your code here
        here you can create task for your function 
        do some hw init that need after systemtick init
    */
    LOS_EvbSetup(); 

    LOS_Demo_Entry();	
    
    //LOS_Inspect_Entry();
    
	//LOS_BoadExampleEntry();	
		
    /* Kernel start to run */
    LOS_Start();
    for (;;);
    /* Replace the dots (...) with your own code.  */
}

如何选择测试的功能：
  - 在example\include\los_demo_entry.h 打开要测试的功能的宏开关LOS_KERNEL_TEST_xxx，比如测试task调度打开 LOS_KERNEL_TEST_TASK 即可（//#define LOS_KERNEL_TEST_TASK 修改为 #define LOS_KERNEL_TEST_TASK）
  - 中断测试无法在软件仿真的情况下测试, 如需进行中断功能测试，请自行添加中断初始化相关内容到Example_Exti0_Init函数。
在keil中使用printf打印的方法
  - 将printf重定向到uart输出，需要uart驱动支持，如果没有适配串口驱动代码，则不建议使用该方法。
  - 使用软件仿真的方式在keil IDE的debug printf view中查看，将los_demo_debug.h中的LOS_KERNEL_DEBUG_OUT及LOS_KERNEL_TEST_KEIL_SWSIMU宏定义打开（如果是在IAR工程中则不需要打开LOS_KERNEL_TEST_KEIL_SWSIMU）。
### 8.2 编译调试
  - 打开工程后，菜单栏Project→Clean Targets、Build target、Rebuild All target files，可编译文件。点击Rebuild All target file，编译全部文件
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/8-2-1.png) 
 
  - 调试运行代码，查看测试结果输出：
(1)如果调用LOS_Demo_Entry()函数进行测试，可根据《HuaweiLiteOSKernelDevGuide》文档中列出每项API功能测试结果来进行对比判断。
(2)如果调用LOS_Inspect_Entry()函数进行功能巡检，gInspectErrCnt值为0则代表移植成功。按压nrf52832开发板的button1 同时led1 会亮，长按长亮，抬起就灭。按下瞬间会打印Inspect Key success 提示。
 
![](https://github.com/wucool/LiteOSPorting/raw/master/pictures/8-2-2.png) 
 

## 9如何使用LiteOS 开发
LiteOS中提供的功能包括如下内容： 任务创建与删除、任务同步（信号量、互斥锁）、动态中断注册机制 等等内容，更详细的内容可以参考“HuaweiLiteOSKernelDevGuide”中描述的相关内容。下面章节将对任务和中断进行说明。
### 9.1 创建任务
  - 用户使用LOS_TaskCreate(...)等接口来进行任务的创建。具体可以参考example/api/los_api_task.c中的使用方法来创建管理任务。
### 9.2 中断处理
Huawei LiteOS 的中断使用
在驱动开发的过程中我们通常会使用到中断，Huawei LiteOS有一套自己的中断的逻辑，在使用每个中断前需要为其注册相关的中断处理程序。
  - OS启动后，RAM起始地址是0x20000000到0x20000400，用来存放中断向量表，系统启动的汇编代码中只将reset功能写入到了对应的区域，系统使用一个全局的m_pstHwiForm[ ]来管理中断。m3以及m4核的前16个异常处理程序都是直接写入m_pstHwiForm[]这个数组的。
  - 开发者需要使用某些中断(m3以及m4中非前16个异常)时，可以通过LOS_HwiCreate (…)接口来注册自己的中断处理函数。如果驱动卸载还可以通过LOS_HwiDelete(….)来删除已注册的中断处理函数。系统还提供了LOS_IntLock()关中断及LOS_IntRestore()恢复到中断前状态等接口。详细的使用方法可以参考LiteOS中已经使用的地方。
  - LiteOS中断机制会额外地使用2K的RAM，跟大部分开发板bsp代码包中的机制不一样。如果没有动态修改中断处理函数的需要，用户可以选择不使用该中断机制，简单的方法是在los_bsp_adapter.c中将g_use_ram_vect变量设置为0，并且在配置工程时不配置分散加载文件。这样就可以使用demo板bsp包中提供的中断方式。
  - 如果使用LiteOS的中断机制，那么在启动LiteOS之前，请先将所有用到的中断都用LOS_HwiCreate()完成注册，否则在完成中断注册前就初始化了相关的硬件以及中断会直接进入osHwiDefaultHandler()导致程序无法正常运行。
  - los_bsp_adapter.c中LosAdapIntInit() LosAdapIrpEnable() LosAdapIrqDisable（）等接口都可以调用BSP包中的接口实现。
关于中断向量位置选择
  - 在los_bsp_adapter.c中，g_use_ram_vect变量控制了LiteOS中是否使用vector向量表（中断向量表）重定向功能。如果g_use_ram_vect设置为 1 ，则需要在配置分散加载文件，如果配置为0，则不配置分散加载文件（即在上面的配置步骤中可以不进行分散加载文件配置），系统启动后默认中断向量表在Rom的0x00000000地址。
### 9.3 系统tick中断配置修改
 - los_bsp_adapter.c中修改后的osTickStart()函数，比如在该函数中直接调用BSP包中的接口配置system tick，本工程保持默认即可。
  - 根据实际配置的system clock 修改sys_clk_freq的值，工程中给出的值都是默认时钟频率，默认时钟是16M HZ。nrf52832 芯片支持64M HZ，所以本工程更改为64M HZ。
### 9.4 LiteOS资源配置
  - 对于嵌入式系统来说，内存都是比较宝贵的资源，因此一般的程序都会严格管理内存使用，LiteOS也一样。在LiteOS中系统资源使用g_ucMemStart[OS_SYS_MEM_SIZE]作为内存池，来管理任务、信号量等等资源的创建，总共是32K。而留给用户创建的task的的个数则是LOSCFG_BASE_CORE_TSK_LIMIT（15）.
  - LiteOS中的内存使用都是在los_config.h中进行配置的，需要使用多大的内存，可以根据实际的task个数、信号量、互斥锁、timer、消息队列、链表等内容的个数来决定的（根据各自的结构体大小以及个数计算），总的内存池的大小是OS_SYS_MEM_SIZE来定义的。
  - LiteOS的中断机制，目前使用了2K的内存。
### 9.5 移植LiteOS 内存问题，nrf52832 RAM 64K ，参照los_config.h文件中的注释，在工程中可不定义内存相关的宏。
  /* default LiteOS ram size level 
  
  	RAM_SIZE_LEVEL_0 means kernel ram < 8k  , 
	
  	RAM_SIZE_LEVEL_1 means kernel ram < 16k,
	
  	RAM_SIZE_LEVEL_2 means means kernel ram>=32k 
  */

