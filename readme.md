### 程序用途
    BNO055在Edsion上可以借由Intel官方UPM轻松地获取位姿数据,为了在其他平台使用BNO055的数据,需要将数据从Edison上转发出去.
    由于Edison自带wifi模块,所以通过网络传输非常合适.
### server端
    在电脑上运行,开启8888端口监听数据.
### client端
    在Edison上运行,将从BNO055读到的数据通过网络转发出去.
### 程序参考链接
    http://www.binarytides.com/server-client-example-c-sockets-linux/
