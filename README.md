# 自作blinky

## 実機

[nRF5340 MDBT53-1Mモジュールピッチ変換基板](https://www.switch-science.com/products/8658?_pos=3&_sid=0c8c07a88&_ss=r)で動かした。

* [custom board](https://github.com/hirokuma/ncs-custom-board/tree/raytac-base)

## Unit Test

Unity + CMock でのテスト

### 準備

カバレッジ用

```console
$ sudo apt install lcov
```

### テスト実行

カバレッジが計測できた場合、`tests/led/build/lcov-output/index.html`に結果が残っている。

```console
$ ./test_run.sh
```

### ビルドし直したい場合(pristine build)

```console
$ ./test_run.sh -p
```
