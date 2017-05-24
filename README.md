# Balancer2Controller_Client

## 概要

**Balancer2Controller**は、ヴイストン株式会社から発売されている倒立振子制御学習教材
[ビュートバランサー2](https://www.vstone.co.jp/products/beauto_balancer_2/)
をUSBで制御する際に、Linuxからの制御を補助するために開発されたソフトウェアです。

公式から配布されているUSB制御用のSDKはVisualC++向けに作成されているので、
Linuxから制御用のSDKを利用するプログラムを作成することは難しい。
**Balancer2Controller**はこの仲介を行うのが役割であり、
[クライアントプログラム](https://github.com/Rafka86/Balancer2Controller_Client)
と
[サーバープログラム](https://github.com/Rafka86/Balancer2Controller_Server)
で連携して動作するように作成した。
