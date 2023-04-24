while (true)
do
  cat "./testHttp.txt" | nc -q 0 -nvlp 1234
done