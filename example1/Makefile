
.PHONY: all clean

all: filtered.txt length


filtered.txt:
	grep "sda" example.txt > filtered.txt


length: filtered.txt
	wc -l filtered.txt > length


clean:
	rm -f filtered.txt length

	