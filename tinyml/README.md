# micro:bit de TinyML♪: Project files for TinyML

## 概要
本ディレクトリは，**micro:bit de TinyML♪** のサンプルプログラム構築に必要な，ニューラルネットワークモデル作成・学習用のプロジェクトファイルやデータファイルを提供します．

## 特徴
- SONY社の[Neural Network Console(NNC)](https://github.com/sony/neural-network-console) 用プロジェクトファイルをデータセット設定済で同梱．

## ソースコード管理状況
> **Current Version: v0.1.0**  
> 本バージョンにおける主要ファイルの管理状態およびライセンス区分は以下の通りです．

| ファイル名 | 状態 (Status) | 出典 / 備考 | ライセンス |
| :--- | :--- | :--- | :--- |
| `tpc2025_sample.sdcproj` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `tpc2025_sample_train.csv` | **New** | ゆざ (@yuza-lab) | Apache 2.0 |
| `tpc2025_sample_valid.csv` | **New** | ゆざ (@yuza-lab) | Apache 2.0 |
| `MainRuntime_inference.c` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `MainRuntime_inference.h` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `MainRuntime_parameters.c` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |
| `MainRuntime_parameters.h` | **Original** | Sony Group Corporation / 自動生成 (NNC v3.3.9140.33008) | Apache 2.0 |

### 状態の定義
- **Original**: 出典元から取得したままの未改造状態
- **Modified**: 出典元のコードをベースに，本プログラム用に改変を実施
- **New**: ゆざ (@yuza-lab) により新規に書き起こされたソース

> **Note**: 各ファイルの具体的なライセンス条項については，ソースファイル冒頭のヘッダコメントをご確認ください．

## 利用方法
本プロジェクトファイルの利用には，**NNC** が正常にセットアップされている必要があります．

### 1. 本リポジトリの配置
本リポジトリに含まれるソースコードを，ローカル環境へ配置します．
* **コピー元: tinyml/nnc/ 内の全データ**
* **コピー先: C:/tmp/dev/nnc/**

### 2. プロジェクトファイルの読み込み
**A.** NNCを起動し，HOME `プロジェクト` → `プロジェクトを開く` から手順1の `tpc2025_sample.sdcproj` を選択します．  

**B.** 手順2-A後，編集画面に遷移し， `[I-A-R-A-S-B]` の各ブロックが積まれたニューラルネットワークモデルが表示されれば，読込成功です．  

**C.** 手順2-Bが成功していれば，同時にデータセットも本サンプル版が設定済となっています．  

**D.** あとは諸々操作し，「エクスポート→NNB (NNabla C Runtime file format)」を済ませ，`c_source/` ディレクトリに含まれる次の4ファイルをmicro:bit開発環境で使用します．  
 `MainRuntime_inference.c` 
 `MainRuntime_inference.h` 
 `MainRuntime_parameters.c` 
 `MainRuntime_parameters.h` 

## バージョン履歴
- **v0.1.0 (2026-01-29)**
  - リポジトリの初期構成作成．

## ライセンス
本プログラムはマルチライセンスで構成されています．
- 引用・転載しているソースコード：各提供元のライセンス（T-License 2.2等）に従います．
- 本プログラム独自の成果物および改変部分：**Apache License 2.0** を適用します．
詳細は各ファイルのヘッダを参照してください．

---
**Maintainer:** ゆざ (@yuza-lab)
