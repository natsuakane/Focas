#!/bin/zsh

# コピー元のファイル名を指定
SOURCE_FILE="build/focas"

# コピー先のディレクトリを指定
DEST_DIR="/usr/local/bin"

# ファイルが存在するか確認
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file $SOURCE_FILE not found."
    exit 1
fi

# 管理者権限でファイルをコピー
sudo cp "$SOURCE_FILE" "$DEST_DIR"

# コピーが成功したか確認
if [ $? -eq 0 ]; then
    echo "File $SOURCE_FILE successfully copied to $DEST_DIR"
    # PATHを更新（必要な場合）
    export PATH=$PATH:$DEST_DIR
    echo "PATH updated. New executables should now be available."
else
    echo "Error: Failed to copy file."
    exit 1
fi