# STC32G_Power_USB
这是基于STC32G12K128的一个功率计

============================================================================================

B站的视频连接【大专学生自己原创的功率计】 https://www.bilibili.com/video/BV1SY411Y74s/?share_source=copy_web&vd_source=99166498f906882ac8b22f356d05b148

============================================================================================
--------------------------------------------------------------------------------------------

V1.0.2版本夔牛USB功率计：
  1.支持PD3.0，QC2.0诱骗
  2.支持电流电压功率显示
  3.支持电压电流曲线显示（能显示方波、谐波（未测试）等）
  4.支持电压差显示
  5.支持1ms过流、过温保护
  6.USBA口支持QC2.0,QC3.0协议检测
  7.支持WH，AH功耗积累
  8.支持最大最小电压电流功率显示
  9.支持温度湿度显示
  
--------------------------------------------------------------------------------------------
********************************************************************************************

注意：
  0.最重要的是本产品支持最大电压21V,电流5A
  0.最重要的是本产品支持最大电压21V,电流5A
  0.最重要的是本产品支持最大电压21V,电流5A
  1.要想使用USBA口的快充充手机那就不能焊CH340N的USB_TTL的串口芯片（因为他会将D+,D-拉高导致不能通过D+，D-识别快充协议）
  2.使用电压电流曲线显示（大于0.5A的电流）时请选择50ms时间采样，小于0.5A电流用20ms采样最好
  3.type-c口由于被CH224K芯片控制了c口引脚所以不能充手机检测快充协议（支持诱骗）
  4.注意别接航模的锂电池（因为该电池的放电倍率高，上电瞬间电流高可能会烧坏NMOS管）
  5.type-c口不支持过温，过载保护。
  
********************************************************************************************

缺点：
硬件：
  1.由于使用的是ldo稳压芯片导致大功率时有点发热但是正常使用没问题的
  2.usb母座使用的是3块钱20个的劣质母座导致有时接触不良（加上USBA的公座和母座都没有使用能耐受大电流的USBA，所以发热有点严重，正常使用没问题的）
软件：无BUG

============================================================================================

*文件修改历史
*<时间>    | <版本>  | <作者>  | <功能>  
*2023.3.3 | V1.0.3   | 小夏    | 更新硬件

============================================================================================

--------------------------------------------------------------------------------------------

V1.0.3版本夔牛USB功率计：
  1.更换USB-A口为支撑5A大电流（解决大电流时USBA口发热严重问题）
  2.c口支撑过流，过温保护
  3.更换ldo为dc-dc芯片jw5017S(解决大电压时ldo发热严重的问题)
  4.过流过温按键取消(软件)
  5.解决usb-A接触不良问题。
  
-------------------------------------------------------------------------------------------- 
********************************************************************************************

缺点：
  1.由于使用的DC-DC芯片最低输入电压为4.5V，这导致华为/VOOC快充协议会将电压降到3.7V，这导致USB电流计一直重启。不能稳定充电，但是其他快充没有问题的
  
  
********************************************************************************************
