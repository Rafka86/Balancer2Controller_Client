# Balancer2Controller_Client

## 概要

**Balancer2Controller**は、ヴイストン株式会社から発売されている倒立振子制御学習教材
[ビュートバランサー2](https://www.vstone.co.jp/products/beauto_balancer_2/)
をUSBで制御する際に、Linuxからの制御を補助するために開発されたソフトウェアです。

公式から配布されているUSB制御用のSDKはVisualC++向けに作成されているので、
Linuxから制御用のSDKを利用するプログラムを作成することは難しいです。
**Balancer2Controller**はこの仲介を行うのが役割であり、
[クライアントプログラム](https://github.com/Rafka86/Balancer2Controller_Client)
と
[サーバープログラム](https://github.com/Rafka86/Balancer2Controller_Server)
で連携して動作するように作成しました。
連携はソケット通信で行います。イメージ図は以下の様な感じになります。
![schematic_balancer2controller](http://firemiller.net/img/bb2.png)

このRepositoryにあるのは**Client**側のプログラムとなります。
多様なプログラムからクライアント機能を利用できるように、
各種機能を担う関数をライブラリとして纏めており、
現状では、利用者はライブラリのソースファイルを
各自のプログラムソースと同じ場所にコピーし、
同時にコンパイルする形で利用することを想定しています。
将来的には共有ライブラリの形で利用できるように
インストールを行うMakefileを作成する予定です。


