本文整合了sobereva在其个人博客http://sobereva.com/ 中的五篇文章文章，形成了一个计算电子结构动画的完整工作流程。

## 一. [计算IRC](http://sobereva.com/400)

> 软件：
>
> - GaussView
>
> - Gaussian 09W

### 1. 得到过渡态结构

画出近似过渡态结构 TS.gif

做过渡态优化 TS.out

```
%chk=C:\Users\hhhff\Desktop\computational chemistry\5\air\singletts.chk
%mem=1GB
%nprocshared=4
#p b3lyp/6-31g* opt=(ts,calcfc,noeigen) iop(1/8=6) scfcon=7

Title Card Required

-1 1
 C                 -0.68216900    0.00004400    0.00000000
 H                 -0.85672100    0.53158300    0.92179200
 H                 -0.85672100    0.53265500   -0.92117200
 H                 -0.85661800   -1.06401400   -0.00061800
 H                 -2.61100000   -0.00027000   -0.00000200
 F                  1.03045200   -0.00002400    0.00000000
[空行]
[空行]
```



### 2.  计算出IRC文件

打开 TS.out ，保存为输入文件 IRC.gjf。将IRC.gif关键词修改为

```
%chk=C:\Users\hhhff\Desktop\computational chemistry\5\air\singletts.chk
%mem=1GB
%nprocshared=4
# B3LYP/6-31G* IRC=(calcall,stepsize=5,maxpoints=65) nosymm

Title Card Required

-1 1
 C                  0.68216900   -0.00004400    0.00000000
 H                  0.85672100   -0.52965200    0.92290300
 H                  0.85672100   -0.53458200   -0.92005500
 H                  0.85661800    1.06401000   -0.00284500
 H                  2.61100000    0.00027000   -0.00000200
 F                 -1.03045200    0.00002400    0.00000000
[空行]
[空行]
```

> 其中stepsize=5代表步长为5
> maxpoints=50代表左右各取50个点
> nosymm代表固定座标（可能不需要）



## 二. [产生IRC各点波函数](http://sobereva.com/199)

> 软件：
>
> - Gaussian 09W
>
> - IRCsplit（脚本）(http://sobereva.com/soft/IRCsplit_1.0.3.rar)

### 1.创建单点文件模板

创建一个与计算出的IRC任务对应的普通单点文件 IRC_SP.gif

```
# rhf/3-21g nosymm

IRC test:   SIH2+H2 OPTM. AT 3-21G LEVEL (STEP=0.1,POINT NUMBER 1-30)

-1 1
 C                  0.68216900   -0.00004400    0.00000000
 H                  0.85672100   -0.52965200    0.92290300
 H                  0.85672100   -0.53458200   -0.92005500
 H                  0.85661800    1.06401000   -0.00284500
 H                  2.61100000    0.00027000   -0.00000200
 F                 -1.03045200    0.00002400    0.00000000
[空行]
[空行]
```

> IRC_SP.gif中带上nosymm关键词之后， 新生成的Gaussian输入文件也就都带着nosymm关键词了。
>
> 如果没有nosymm关键词，Gaussian做单点计算时由于会自动调整分子朝向到标准朝向，会导致某些点产生的.chk/.wfn文件中体系的平面和其它点不对应，随后做等值面变化动画的时候体系就会中途发生奇怪的翻转。
>
> 如果不打算做等值面变化的动画的话则无需nosymm，写了它之后做单点时由于不启用对称性，计算还会多耗时很多。



### 2.  生成每个点波函数文件

启动IRCsplit，然后依次输入
`C:\Users\hhhff\Desktop\computational chemistry\final\IRC.out`
`C:\Users\hhhff\Desktop\computational chemistry\final\IRC_SP.gjf`
`3`//输入1，则生成的Gaussian输入文件只能用来产生.wfn，输入2则只能产生.chk，这里输入3可以让.wfn和.chk都产生
`C:\Users\f\Desktop\computational chemistry\final\SP`//定义输出的.wfn和.chk文件的路径和名称
`20，65`//IRC向前提取20个点，向后提取65个点，加上TS结构，总共将提取86个结构。

命令行中信息如下：

```
 Input the path of output file of Gaussian IRC task, e.g. C:\miku.out
C:\Users\hhhff\Desktop\computational chemistry\final\IRC.out

 Input the path of Gaussian input file of standard single point task
 e.g. C:\Love_live\niconiconi.gjf
C:\Users\hhhff\Desktop\computational chemistry\final\IRC_SP.gjf

1: Generate .wfn   2: Generate .chk   3: Generate both .wfn and .chk
3

 Input the path of the files to be generated
 If you input e.g. C:\sob, then after you run all generated Gaussian input files,C:\sob0001.wfn, C:\sob0002.wfn... and C:\sob0001.chk, C:\sob0002.chk... will be yielded
C:\Users\hhhff\Desktop\computational chemistry\final\SP

 The total number of forward and reverse points:    20    65

 Extract how many forward and reverse points, respectively? e.g. 10,15
20,65

```



### 3. 批量编辑

把 IRCsplit\script 目录下的runall.bat拷到那个目录下，然后双击之，就会调用g09来执行此目录下所有.gjf文件。然后在就生成了C:\final\SP0001.wfn、C:\final\SP0002.wfn...以及C:\final\SP0001.chk、C:\final\SP0002.chk...

把script目录下的chk2fch.bat也拷到这个目录下并双击运行。然后就会生成C:\final\SP0001.fch、C:\final\SP0002.fch...





## 三. [LOL等值面动画](http://sobereva.com/86)

> 软件：
>
> - Multiwfn(http://sobereva.com/multiwfn/)

### 1.  创建文本文件batchcolor.txt

波函数文件（.wfn），放在Multiwfn目录中新建文件夹 Multiwfn\WFN 下。
将Multiwfn的Settings.ini里的isilent参数设为0。
在Multiwfn目录下编写一个文本文件batchcolor.txt，内容是（//后是注释）：

```
4  //绘制平面图
10 //LOL函数
1  //填色图
200,200  //两方向格点数
3  //YZ平面。波函数文件中分子轴顺着Z
0  //X=0
4  //显示原子标签
3  //用蓝色字体
0  //保存图像到当前目录
[空行]
[空行]
```



### 2. 创建文本文件batchrun.bat

编辑一个文本文件也放在Multiwfn目录下，叫batchrun.bat

```
for /f %%i in ('dir WFN\*.wfn /b') do Multiwfn WFN\%%i < batchcolor.txt
```

> 这是一个DOS的批处理脚本。其中dir WFN\*.wfn /b代表输出WFN目录下所有.wfn文件名。这个脚本会使每个.wfn文件都被Multiwfn安静地执行一遍，相当于依次执行
> Multiwfn WFN\SP0000.wfn < batchcolor.txt
> Multiwfn WFN\SP0001.wfn < batchcolor.txt
> ...
> Multiwfn H2tri\SP0010.wfn < batchcolor.txt
> 由于将isilent设为了1，图像不会自动弹出，而且每一步要输入的命令都通过batchcolor.txt重定向进了Multiwfn，所以每一步Multiwfn都会无声无息地执行，用户不需要干预。执行batchrun.bat后，由于体系小，几秒钟后当前目录下就出现了DISLIN.PNG, DISLIN_1.PNG, DISLIN_2.PNG...DISLI_10.PNG，依次对应核间距从近到远。



### 3. 生成逐帧图像

运行 batchrun.bat ，Multiwfn目录下就会生成每个wfn文件对应的 .png文件



### 4. 合成动画





## 四. [键级曲线](http://sobereva.com/200)

> 软件：
>
> - Multiwfn
> - LInux（系统） / Python
> - Excel / Origin

### 1. 生成键级文件

Multiwfn默认只输出>0.05的Mayer键级，所以需要修改settings.ini文件，将bndordthres参数改为0.0，之后所有键级就都会输出了。Multiwfn中计算Mayer键级的过程是输入9然后输入1，为了批量计算，我们写个文本文件（假设叫batch.txt）放在Multiwfn所在目录下，文件内容只有两行，即为

```
9
1
```

然后写个文本文件（假设叫batchrun.bat，即批处理文件）放在Multiwfn目录下，内容为

```
for /f %%i in ('dir c:\IRC\*.fch /b') do Multiwfn c:\IRC\%%i < batch.txt > c:\IRC\%%~ni.txt
```

双击batchrun.bat图标，Multiwfn就会依次使用那些.fch文件计算Mayer键级，输出信息依次产生在c:\IRC目录下的IRC0001.txt、IRC0002.txt...IRC0060.txt里面。



### 2. 提取键级信息

将这些输出文件拷贝到Linux系统某文件夹下，并在这个文件夹下运行

```
grep "1(C )  5(H )" * > out.txt
```

> 这个命令的作用是提取C1与H5之间的键级信息。可根据需要修改其中的参数。
>
> 然后将生成的out.txt复制到excel中，提取出最后一列。



### 3. 提取反应坐标

将之前IRC任务的输出文件IRC.gif用编辑器开打，在文件末尾找到

```
  Summary of reaction path following
 --------------------------------------------------------------------------
                        Energy    RxCoord
   1                   -0.07157  -5.16295
   2                   -0.07149  -5.08354
   3                   -0.07140  -5.00411
   4                   -0.07128  -4.92467
```

> 其中Energy就是相对于过渡态能量的每个点的能量，单位为a.u.。Rx Coord是反应坐标。用Excel把Rx Coord那一列的数据也提取出来。



### 4. 绘制键级-反应坐标图像

在origin里绘制曲线图，X轴就是Rx Coord值，Y轴就是键级数据，就得到了下图





## 五.  [ELF、RDG等值面动画](http://sobereva.com/200)

> 软件：
>
> - Multiwfn
> - VMD 1.9

### 1. 生成每个点对应的ELF的cube文件

在Multiwfn目录下编写一个文本文件batch.txt，内容是（//后是注释）：

```
5
9
2
2
```

在Multiwfn目录下编写一个文本文件batchrun.bat，内容是（//后是注释）：

```
for /f %%i in ('dir c:\IRC\*.fch /b') do (
Multiwfn c:\IRC\%%i < batch.txt
rename ELF.cub %%~ni.cub
)
```

双击运行 batchrun.bat，将会在当前目录下产生IRC0001.cub、IRC0002.cub...IRC0060.cub



### 2. 产生等值面图像

刚得到的cube文件都移动到VMD所在目录下面。
在VMD目录下写个文本文件isoall.tcl，内容如下

```
color Display Background white
set isoval 0.8
axes location Off
for {set i 1} {$i<=2} {incr i} {
set name SP[format %04d $i]
puts "Processing $name.cub..."
mol default style CPK
mol new $name.cub

scale to 0.3
rotate x by 20
rotate y by -30
rotate z by -20
translate by 0.000000 0.20000 0.000000

mol modstyle 0 top CPK 0.500000 0.300000 12.000000 10.000000
mol addrep top
mol modstyle 1 top Isosurface $isoval 0 0 0 1 1
mol modcolor 1 top ColorID 3
render snapshot $name.bmp
mol delete top
}
```

> 脚本开头isoval用来设定等值面的数值，这里对应于绘制ELF=0.8的等值面。
>
> for {set i 1} {$i<=60} {incr i}代表这里要处理编号为0001到0086的cube文件。
>
> 脚本中scale to、rotate x by、translate by分布为调节缩放，旋转，平移的参数。
>
> 对于其它体系应根据实际情况对参数进行适当调整。

启动VMD后在VMD的控制台里面运行source isoall.tcl，在VMD目录下就会输出IRC0001.bmp、IRC0002.bmp...IRC0060.bmp。图像尺寸和当前VMD窗口大小是一致的。



```
color Display Background white
color scale method BGR
set isoval 0.5
axes location Off
for {set i 1} {$i<=60} {incr i} {
set name SP[format %04d $i]
puts "Processing f1_$name.cub and f2_$name.cub..."
mol default style CPK
mol new f1_$name.cub
mol addfile f2_$name.cub

scale to 0.3
rotate x by 20
rotate y by -30
rotate z by -20
translate by 0.000000 0.20000 0.000000

mol modstyle 0 top CPK 0.500000 0.300000 12.000000 10.000000
mol addrep top
mol modstyle 1 top Isosurface $isoval 1 0 0 1 1
mol modcolor 1 top Volume 0
mol scaleminmax top 1 -0.04 0.02
render snapshot $name.bmp
mol delete top
}
```

