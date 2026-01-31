# micro:bit de TinyML♪: Orientation Classification for TinyML

## 概要
本プログラムは， **micro:bit de TinyML♪** のサンプルプログラム「姿勢判定」を含んだ，TinyML実行環境です．  
TinyMLとして [NNabla C Runtime](https://github.com/sony/nnabla-c-runtime/) を使用します．

## 特徴
- micro:bit内蔵の加速度センサデータを取得し，TinyMLで姿勢判定を行い結果をコンソール出力します．
- [TRONWAREの連載記事「micro:bitでμT-Kernel 3.0を動かそう」](https://www.t-engine4u.com/info/mbit/index.html)の第12回記事のサンプルプログラム(VOL.207掲載)を原典としています．
- TinyMLモジュール(≒NNabla C Runtime)必須です．
- サンプルプログラムの機能を最小限に抑えており，ユーザ独自のアプリケーションへ容易に置換できます．

## ソースコード管理状況
> **Current Version: v0.93.0**  
> 本バージョンにおける主要ファイルの管理状態およびライセンス区分は以下の通りです．

| ファイル名 | 状態 (Status) | 出典 / 備考 | ライセンス |
| :--- | :--- | :--- | :--- |
| `iic.h` | **Original** | Personal Media Corporation (384_mbit_list.zip) / ※再配布について個別許諾済|(個別許諾)|
| `iic_reg.c` | **Original** | Personal Media Corporation (384_mbit_list.zip) / ※再配布について個別許諾済|(個別許諾)|
| `nrf5_iic.c` | **Original** | Personal Media Corporation (384_mbit_list.zip) / ※再配布について個別許諾済|(個別許諾)|
| `app_main.c` | **Modified** | T3 WG of TRON Forum (384_mbit_list.zip)  / ※再配布について個別許諾済|(個別許諾)|
| `config.h` | **Modified** | TRON Forum (release_30005, commit: c976801) | T-License 2.2 |
| `syslib.h` | **Modified** | TRON Forum (release_30005, commit: c976801) | T-License 2.2 |
| `MainRuntime_inference.c` | **Modified** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `MainRuntime_inference.h` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `MainRuntime_parameters.c` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `MainRuntime_parameters.h` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `pltm_fmath.c` | **New** | ゆざ (@yuza-lab) | Apache 2.0 |
| `pltm_fmath.h` | **New** | ゆざ (@yuza-lab) | Apache 2.0 |
| `pltm_malloc.h` | **New** | ゆざ (@yuza-lab) | Apache 2.0 |
| `pltm_stat.h` | **New** | ゆざ (@yuza-lab) | Apache 2.0 |
| `pltm_syscall.c` | **New** | ゆざ (@yuza-lab) | Apache 2.0 |

### 状態の定義
- **Original**: 出典元から取得したままの未改造状態
- **Modified**: 出典元のコードをベースに，本プログラム用に改変を実施
- **New**: ゆざ (@yuza-lab) により新規に書き起こされたソース

> **Note**: 各ファイルの具体的なライセンス条項については，ソースファイル冒頭のヘッダコメントをご確認ください．

## ビルド方法
本プログラムのビルドには，**μT-Kernel 3.0のクロスコンパイル環境** および **micro:bit用ソースコード** が正常にセットアップされている必要があります．
これに加え，TinyMLライブラリとして `NNabla C Runtime` (v1.38.0推奨) を使用します．
以下，開発環境（`mtkernel_3/` ディレクトリ等）が既に存在する前提で，本リポジトリの導入手順を説明します．

#### ビルド前の重要な注意事項
> [!CAUTION]
> **ファイルの配置（上書き）について**  
> 以下の手順では既存環境へのファイル上書きを伴います．**作業前に必ずコピー先（ローカル環境）のバックアップを取得してください．**
> また，本手順で配置する `makefile` はTinyML用にカスタマイズされているため，`app_main.c` でTinyMLを使用しない場合でもライブラリがリンクされる構成となっています．

### 1. TinyML (NNabla C Runtime) の導入
GitHubより [nnabla-c-runtime-1.38.0.zip](https://github.com/sony/nnabla-c-runtime/archive/refs/tags/v1.38.0.zip) をダウンロード・展開し，以下の手順でローカル環境へ配置してください．

**A. インクルードファイルの配置**
* **コピー元**: `(展開ディレクトリ)/include/nnablart/`
* **コピー先**: `mtkernel_3/include/nnablart/` (ディレクトリごとコピー)

**B. ソースコードの配置**
* **コピー元**: `(展開ディレクトリ)/src/`
* **コピー先**: `mtkernel_3/lib/nnabla_c_runtime/src/` (ディレクトリごとコピー)
  * ※事前に `lib/` ディレクトリ内に `nnabla_c_runtime/` ディレクトリを新規作成してください．

<details>
<summary>配置後の構成確認（クリックして展開）</summary>

```text
mtkernel_3/
├── include/
│   └── nnablart/       <-- 手順Aで配置
└── lib/
    └── nnabla_c_runtime/
        └── src/        <-- 手順Bで配置 (functions, nnablart, runtime等を含む)
```
</details>

### 2. 本リポジトリ（Porting Layer）の配置
本リポジトリに含まれるソースコードを，ローカル環境へ配置します．
* **コピー元: application/ai/app_sample/ 内の全ファイル**
* **コピー先: mtkernel_3/app_sample/**

### 3. ビルド設定・ヘッダファイルの配置
ビルドに必要な設定ファイル等を適切な場所へ配置します．

**A. ライブラリヘッダ (syslib.h / config.h)**
* **コピー元**: `application/ai/include/tk/syslib.h` --> **コピー先**: `mtkernel_3/include/tk/`
* **コピー元**: `application/ai/config/config.h` --> **コピー先**: `mtkernel_3/config/`

**B. Makefile (ビルド定義)**
* **コピー元**: `application/ai/build_make/makefile`
* **コピー先**: `mtkernel_3/build_make/`

**C. ビルド用サブディレクトリ設定 (subdir.mk) TinyMLのビルドに必要な定義ファイルを配置します．**
* **コピー元**: `application/ai/build_make/mtkernel_3/lib/nnablart/` (ディレクトリごと)
* **コピー先**: `mtkernel_3/build_make/mtkernel_3/lib/`

<details>
<summary>配置後の構成確認（クリックして展開）</summary>

```text
mtkernel_3/
├── app_sample/       <-- 手順2で更新
└── build_make/
    ├── makefile      <-- 手順3-Bで更新
    └── mtkernel_3/
        └── lib/
            └── nnablart/  <-- 手順3-Cで配置
```
</details>

## サンプルプログラムのニューラルネットワークモデル(NN)を差し替える方法

> [!TIP]
> **ヒント: NNの入出力構成について**  
> NNを差し替える際，本サンプルと異なる入出力構成をとる場合は関連処理も適宜書き換えてください．  

> [!TIP]
> **ヒント: 実行直後の `HardFault` について**  
> NN差替後に `HardFault` が発生する場合， `nnablart_mainruntime_allocate_context()` 実行時であれば，NNの入力サイズが過大な可能性があります．
> NNCに戻りNNの構成見直しをして要求メモリサイズの圧縮を図ってください．  
> `micro:bit v2.2` は，RAMサイズが128KBです．

1. NNCでエクスポートした `c_source/` ディレクトリ内の次の4ファイルをeclipseのプロジェクトディレクトリ `app_sample/` に上書コピーしてください．  
 `MainRuntime_inference.c` 
 `MainRuntime_inference.h` 
 `MainRuntime_parameters.c` 
 `MainRuntime_parameters.h` 

2. 1のファイルのうち `MainRuntime_inference.c` に対し2箇所編集を行ってください．  
- 先ずは他の `#include` に先立ち次の1行を追記してください．

```c
#include "pltm_malloc.h"    // ←この行を追記

#include "MainRuntime_inference.h"
```

- 次に重複処理を無効化するため，下の記述を見つけてコメントアウトしてください．

```c
/* コメントアウト処理後
void *(*rt_variable_malloc_func)(size_t size) = malloc;
void (*rt_variable_free_func)(void *ptr) = free;

void *(*rt_malloc_func)(size_t size) = malloc;
void (*rt_free_func)(void *ptr) = free;
*/
```

## バージョン履歴
- **v0.1.0 (2026-01-29)**
  - リポジトリの初期構成作成．
- **v0.93.0 (2026-01-31)**
  - MainRuntime_inference.c: uT-Kernel 3.0 への適合
  - app_main.c: TinyML姿勢判定実行機能を実装
  - pltm_xxx.xxx: [Porting Layer for TinyML] ファイル群追加(5 files)

## ライセンス
本プログラムはマルチライセンスで構成されています．
- 引用・転載しているソースコード：各提供元のライセンス（T-License 2.2等）に従います．
- 本プログラム独自の成果物および改変部分：**Apache License 2.0** を適用します．
詳細は各ファイルのヘッダを参照してください．

---
**Maintainer:** ゆざ (@yuza-lab)
