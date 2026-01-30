# micro:bit de TinyML♪

## 概要
本リポジトリは， [TRONプログラミングコンテスト2025](https://www.tron.org/ja/programming_contest-2025/programming_contest_2025_awards/) への出品作 **「micro:bit de TinyML♪」** を一般公開にあたり諸々改善したモノです．  
--  
本作品は，エッジノードAIの一つTinyMLをmicro:bit＋μT-Kernel 3.0の環境で実行させるために必要なPorting Layerを提供するモノです．  
TinyMLとしてSONY社のNeural Network Libraries(略称: NNabla / よみ: なぶら)のオープンソース実行環境NNabla C Runtime(略称: nnablart)を採用．  
μT-Kernel 3.0のソースを改変し，浮動小数点演算ライブラリの実装では生成AIのGemini by Googleに相談しました．  
サンプルとして実装したmicro:bit内蔵加速度センサを利用した姿勢判定アプリは，nnablartの未使用関数組込状態でROM使用量300KB未満…μT-Kernel 3.0の小フットプリントと相まってアプリ開発・チューニングの余地を十分に残しています．  
また，BTRONへの移植も視野に入ります．

## リポリトジ構成
```text
microbit-de-tinyml/
├── application/  <-- micro:bit用
│   ├── ai/       <-- TinyML実行環境＆サンプルプログラム「姿勢判定」
│   └── logger/   <-- TinyML学習データ収集プログラム(TinyML実行環境含まず)
└── tinyml/
    └── nnc/      <-- Neural Network Consoleプロジェクトファイル「姿勢判定」＆データセット
```

## ビルド方法
各ディレクトリの `README.md` を参照してください．

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
