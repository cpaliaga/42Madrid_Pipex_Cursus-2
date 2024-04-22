#!/usr/bin/sh

valgrind --leak-check=yes ./pipex infile "cat" "hostname" outfile

echo "TEST 01 con cat y hostname"
< infile cat | hostname > outfileA
./pipex infile "cat" "hostname" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 02 con grep 1 y head -2"
< infile grep 1 | head -2 > outfileA
./pipex infile "grep 1" "head -2" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 03 con grep 1 y wc -w"
< infile grep 1 | wc -w > outfileA
./pipex infile "grep 1" "wc -w" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 04"
< infile noexisting | wc > outfileA
./pipex infile "noexisting" "wc" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 05 t26"
< infile cat | noexisting > outfileA
./pipex infile "cat" "noexisting" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 06"
< infile wc -w | cat > outfileA
./pipex infile "wc -w" "cat" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 07"
< infile grep 1 | tr '1' '2' > outfileA
./pipex infile "grep 1" "tr '1' '2'" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 08 t29+30"
< infile wc -l | /bin/cat > outfileA
./pipex infile "wc -l" "/bin/cat" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 09 con grep 1 y wc -w sin entorno"
env -i < infile grep 1 | wc -w > outfileA
env -i  ./pipex infile "grep 1" "wc -w" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile

echo "TEST 10”
env -i < infile noexisting | wc > outfileA
env -i ./pipex infile "noexisting" "wc" outfile
diff outfileA outfile
ls -la outfileA && ls -la outfile
cat outfileA && cat outfile
rm outfileA && rm outfile
