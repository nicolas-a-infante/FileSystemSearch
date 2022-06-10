#!/bin/bash

touch testdir/test1
touch testdir/dir1/test4
touch testdir/dir3/test7

echo -e "Here is the initial file structure of testdir"
ls -lai -R testdir/

echo -e "\nHere are all the path-names of each file/directory"
./find testdir

echo -e "\nHere are the path names of specific files/directories found using '-name'"
./find testdir -name test1
./find testdir -name test2
./find testdir -name test3
./find testdir -name test4
./find testdir -name test5
./find testdir -name test6
./find testdir -name test7
./find testdir -name test8
./find testdir -name dir1
./find testdir -name dir2
./find testdir -name dir3

echo -e "\nHere are the path names of specific files/directories found based on their modified time"
echo -e "\nLess than 10 minutes ago:"
./find testdir -mmin -10
echo -e "\nExactly 10 minutes ago"
./find testdir -mmin 10
echo -e "\nMore than 10 minutes ago"
./find testdir -mmin +10

echo -e "\nHere are the path names of specific files/directories found based on their i-nodes"
./find testdir -inum 62523172
./find testdir -inum 62523174
./find testdir -inum 62523177

echo -e "\nThe following files have been deleted"
./find testdir -name test6 -delete
./find testdir -mmin -10 -delete

echo -e "\nHere is the resulting file structure of testdir"
ls -lai -R testdir/

touch testdir/test1
touch testdir/test2
touch testdir/dir1/test3
touch testdir/dir1/test4
touch testdir/dir1/dir2/test5
touch testdir/dir1/dir2/test6
touch testdir/dir3/test7
touch testdir/dir3/test8
