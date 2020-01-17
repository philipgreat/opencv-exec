#!/bin/bash
rsync -avz ./*.py  -e "ssh -p 4422" philip@t420.doublechaintech.cn:~/resin-3.1.12/webapps/ROOT/upload/
rsync -avz ./*.jpg  -e "ssh -p 4422" philip@t420.doublechaintech.cn:~/resin-3.1.12/webapps/ROOT/upload/
#scp -P 4422 *.py   philip@t420.doublechaintech.cn:~/resin-3.1.12/webapps/ROOT/upload/
echo "upload done"
ssh -p 4422 philip@t420.doublechaintech.cn "cd ~/resin-3.1.12/webapps/ROOT/upload && python3 dectect.py "
open http://t420.doublechaintech.cn:2080/upload/output01.jpg