## 目覚ましソード

### 部品表

| 部品名 | 型番 | 価格 | 個数 | 秋月電子のリンク |
| ---    | ---  | ---  | ---  | ---       |
| 3軸加速度センサモジュール | AE-ADXL335 | 750 | 1 | https://akizukidenshi.com/catalog/g/g107234/ |
| RGB LED| OSTCXBTHC1E | 250 | 1 | https://akizukidenshi.com/catalog/g/g103565/ |
| LED 用放熱基盤 | OSMCPCB5050A | 40 | 1 | https://akizukidenshi.com/catalog/g/g103751/ |
| Nch パワーMOSFET | 2SK4017(Q) | 30 | 3 | https://akizukidenshi.com/catalog/g/g107597/ |
| サーボモーター | 0825DP | 2960 | 2 | https://akizukidenshi.com/catalog/g/g117063/ |
| ACアダプター(5V/3A) | AD-D50P300 | 1100 | 1 | https://akizukidenshi.com/catalog/g/g108311/ |
| ブレッドボード用2.1mm標準DCジャックDIP化キット | AE-DC-POWER-JACK-DIP | 100 | 1 | https://akizukidenshi.com/catalog/g/g105148/ |
| ブレッドボード | BB-102 | 300 | 2 | https://akizukidenshi.com/catalog/g/g109257/ |
| ジャンパワイヤ− (AWG26) | ((7/0.16) AWG26x9) | 440 | 1 | https://akizukidenshi.com/catalog/g/g118293/ |
| Arduino Uno | 互換品でも可 | - | 1 | - |
| Raspberry Pi 3 | スピーカー端子・USB端子があるSBCならなんでも | - | 1 | - |
| ダイソーのスピーカー | - | 330 | 1 | - |
| ダイソーのスポンジ剣 | - | 110 | 2 | - |

### 配線

詳細は回路図を参照

Arduino は Raspberry Pi の USB に接続して使用する．
また，スピーカーは Raspberry Pi のオーディオ端子に接続する．

※ スピーカーのノイズがひどい場合はスピーカーの電源を外部電源から取ると改善する

### 環境構築（Raspberry Pi）

```
$ pip install -r ./raspberrypi/requirements.txt
```

### 実行方法

Raspberry Pi 側で `raspberrypi/main.py` を実行
```
$ python ./raspberrypi/main.py [path/to/wave/file] [path/to/serial/device]
```
