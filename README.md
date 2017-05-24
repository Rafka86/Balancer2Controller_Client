# Balancer2Controller_Client

## 概要

**Balancer2Controller**は，ヴイストン株式会社から発売されている倒立振子制御学習教材
[ビュートバランサー2](https://www.vstone.co.jp/products/beauto_balancer_2/)
をUSBで制御する際に，Linuxからの制御を補助するために開発されたソフトウェアです．

公式から配布されているUSB制御用のSDKはVisualC++向けに作成されているので，
Linuxから制御用のSDKを利用するプログラムを作成することは難しいです．
**Balancer2Controller**はこの仲介を行うのが役割であり，
[クライアントプログラム](https://github.com/Rafka86/Balancer2Controller_Client)
と
[サーバープログラム](https://github.com/Rafka86/Balancer2Controller_Server)
で連携して動作するように作成しました．
連携はソケット通信で行います．イメージ図は以下の様な感じになります．
![schematic_balancer2controller](http://firemiller.net/img/bb2.png)

このRepositoryにあるのは**Client**側のプログラムとなります．
多様なプログラムからクライアント機能を利用できるように，
各種機能を担う関数をライブラリとして纏めており，
現状では，利用者はライブラリのソースファイルを
各自のプログラムソースと同じ場所にコピーし，
同時にコンパイルする形で利用することを想定しています．
将来的には共有ライブラリの形で利用できるように
インストールを行うMakefileを作成する予定です．

## 構成

ライブラリを構成するファイルは以下の3つです．
<dl>
	<dt>bcontroller.h</dt>
		<dd>各機能を担う関数と，センサの情報格納用の構造体を宣言している．</dd>
	<dt>bcontroller.c</dt>
		<dd>各関数の実装を行っているソースファイル．</dd>
	<dt>packet.h</dt>
		<dd>通信に使用するパケット構造体を宣言している．</dd>
</dl>

## 付属のサンプルプログラム

以下のサンプルを作成しました．
動作の確認や，Clientの組み込みの際の参考にしてください．

<dl>
	<dt>client.c</dt>
		<dd>ライブラリの各種機能を対話的に実行します．</dd>
	<dt>keycontrol.c</dt>
		<dd>キーボードの矢印キー”←”または”→”でビュートバランサーの操作を行います．</dd>
	<dt>pidcontrol.c</dt>
		<dd>PID制御で倒立させます．（パラメータは未調整）</dd>
</dl>

この他に通信の確認のためのエコーサーバープログラムを付属させています．

### 実行方法

サンプルプログラムをコンパイルする前に以下の内容のヘッダファイルを
sampleディレクトリ直下に"private.h"という名前で作成する必要があります．

```c
#ifndef _PRIVATE_H_
#define _PRIVATE_H_

#define SERVER_ADDR "[address]"
#define SERVER_PORT [port]

#endif
```

`[address]`と`[port]`はそれぞれ実際に使用する
サーバーのアドレスとポート番号に置き換えてください．

ファイルを作成したら以下のコマンドを実行してください．

```
$ make
```

`$`はプロンプトを表しています．
このコマンドによって各ソースファイルがコンパイルされます．
無事にコンパイルできたら実行してみてください．

## 機能

Clientとして利用できる関数を紹介していきます．

### Connect関数

```c
int Connect(const char* addr, const int port);
```

ソケットを作成し，サーバーとの接続を試みる関数です．
失敗した場合はその原因を標準エラー出力に出力します．
接続の成否を戻り値として返します．

* 引数
	- `const char* addr` : **Server**が実行されているマシンのIPアドレス(IPv4)
	- `const int port` : **Server**がListenしているポート番号
* 戻り値
	- 接続の成否を示す値．
		接続に失敗した場合は`EXIT_FAILURE`，成功した場合は`EXIT_SUCCESS`が返されます．

### Disconnect関数

```c
int Disconnect();
```

サーバーとの接続を切断し，ソケットを破棄する関数です．
失敗した場合はその原因を標準エラー出力に出力します．
切断の成否を戻り値として返します．

* 戻り値
	- 切断の成否を示す値．
		切断に失敗した場合は`EXIT_FAILURE`，成功した場合は`EXIT_SUCCESS`が返されます．

### GetSensorInfos関数

```c
int GetSensorInfos(DataSet* data);
```

ビュートバランサー2の各種センサーのデータを取得することを試みます．
通信に失敗した場合はその原因を標準エラー出力に出力します．
通信の成否は戻り値として返されます．
取得したデータはDataSet構造体に格納されます．
この構造体は以下の様に定義されています．

```c
typedef struct {
	double position;
	double velocity;
	double angle;
	double angular_v;
} DataSet;
```

構造体の各メンバーには以下の様な値が格納されます．
<dl>
	<dt>position</dt>
		<dd>ビュートバランサーの位置[mm]</dd>
	<dt>velocity</dt>
		<dd>ビューとバランサーの速度[mm/s]</dd>
	<dt>angle</dt>
		<dd>本体角度[rad]</dd>
	<dt>anglular_v</dt>
		<dd>本体角速度[rad/s]</dd>
</dl>

この関数自体の引数と戻り値の意味は以下の通りです．

* 引数
	- `DataSet* data` : センサーの情報を格納する変数のポインタ
* 戻り値
	- 通信の成否を示す値．
		通信に失敗した場合は`EXIT_FAILURE`，成功した場合は`EXIT_SUCCESS`が返されます．

### Move関数

```c
int Move(const double spd);
```

ビュートバランサー2を速度を指定して動かす命令を送信します．
通信に失敗した場合はその原因を標準エラー出力に出力します．
通信の成否は戻り値として返されます．

* 引数
	- `const double spd` : ビュートバランサーを動かす速度
* 戻り値
	- 通信の成否を示す値．
		通信に失敗した場合は`EXIT_FAILURE`，成功した場合は`EXIT_SUCCESS`が返されます．

### MoveLeft関数

```c
int MoveLeft();
```

ビュートバランサー2のボタンがある面を右に据えた時に，
左側へ動かす命令を送信します．
通信に失敗した場合はその原因を標準エラー出力に出力します．
通信の成否は戻り値として返されます．

* 戻り値
	- 通信の成否を示す値．
		通信に失敗した場合は`EXIT_FAILURE`，成功した場合は`EXIT_SUCCESS`が返される．

### MoveRight関数

```c
int MoveRight();
```

ビュートバランサー2のボタンがある面を右に据えた時に，
右側へ動かす命令を送信します．
通信に失敗した場合はその原因を標準エラー出力に出力します．
通信の成否は戻り値として返されます．

* 戻り値
	- 通信の成否を示す値．
		通信に失敗した場合は`EXIT_FAILURE`，成功した場合は`EXIT_SUCCESS`が返されます．

### Stop関数

```c
int Stop();
```

ビュートバランサー2のモーターを停止させる命令を送信します．
通信に失敗した場合はその原因を標準エラー出力に出力します．
通信の成否は戻り値として返されます．

* 戻り値
	- 通信の成否を示す値．
		通信に失敗した場合は`EXIT_FAILURE`，成功した場合は`EXIT_SUCCESS`が返されます．
