# 你的主文件名
TARGET = Problem
# 编译器选项
LATEXMK = latexmk
# -xelatex: 使用 xelatex 引擎
## -shell-escape: 允许运行外部程序 (minted 或 tikz-externalize 需要)
# -interaction=nonstopmode: 出错也不要停，直接报出来
# -file-line-error: 报错时显示具体行号
FLAGS = -xelatex -interaction=nonstopmode -file-line-error

.PHONY: all clean watch

all: $(TARGET).pdf

$(TARGET).pdf: $(TARGET).tex
	$(LATEXMK) $(FLAGS) $(TARGET).tex

# 自动监控模式：改一下保存，PDF 自动刷新（极其好用！）
watch:
	$(LATEXMK) $(FLAGS) -pvc $(TARGET).tex

clean:
	$(LATEXMK) -C
	rm -f $(TARGET).pdf
