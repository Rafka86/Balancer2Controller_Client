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

## 構成

ライブラリを構成するファイルは以下の3つです。
<dl>
	<dt>bcontroller.h</dt>
		<dd>各機能を担う関数と、センサの情報格納用の構造体を宣言している。</dd>
	<dt>bcontroller.c</dt>
		<dd>各関数の実装を行っているソースファイル。</dd>
	<dt>packet.h</dt>
		<dd>通信に使用するパケット構造体を宣言している。</dd>
</dl>

## 機能

Clientとして利用できる関数を紹介していきます。

### Connect関数

```c
int Connect(const char* addr, const int port);
```

サーバーと接続を試みる関数です。
失敗した場合はその原因を標準エラー出力に出力します。

* 引数
	- `const char* addr` : **Server**が実行されているマシンのIPアドレス(IPv4)
	- `const int port` : **Server**がListenしているポート番号
* 戻り値
	- 接続の可否を示す値。
		接続に失敗した場合は`EXIT_FAILURE`、成功した場合は`EXIT_SUCCESS`が返される。

