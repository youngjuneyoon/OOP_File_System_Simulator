# lab5_base

## Test cases for 1 (testing ls/ ls -l command)

(case 1)
command "ls"
command "ls -l"

We first created an image file, a text file, and a directory. Called ls -l command to check the size of each file, got size 0 for all three.
Then, we called cd command to enter the directory, created a text file, an image file, and a directory.
Called ls command to check if the list of files display correctly. The output showed all the files We created. After that, we called cd .. command to go back
to the root. Called cat command on image file and text file to add file contents (:wq). ("Hello, World" for the text file and "X X X X X3" for the image file)
Called ls -l command to check if the sizes of files changed. The size of files changed (10, 4, 24 respectively)

(case 2)

command "ls random text"

In order to check if random strings entered after the command, we added "random text" after the line. 
It returned "command failed", a cmd output which indicates it is an invalid command.

(case 3)

command "ls       -l"

In order to check if strings in between "ls" and "-l" could cause a problem or not, we added a few whitespaces.
It returned "command failed", a cmd output which indicates it is an invalid command.


##Test cases for 2 (testing rm command)

(case 1)
command: created t.txt, then
<rm t.txt>
successfully removes the text file.

(case 2)
command :created dir1, then
<rm dir1>
successfully removes the directory file.

(case 3)
command: created dir1, and created image.img inside the dir1 directory, then
<rm dir1>
does not delete the directory file, which is an intended behavior. 

(case 4)
command: same plot with case 3, but this time, the command was
<rm dir1 -r>
successfully deletes the dir1 with image.img file. 

(case 5)
command: created dir1, and inside the dir1, t.txt and dir2 created. And inside the dir2, i.img was created, and then 
go back to root folder, and then
<rm dir1 -r>
successfully removes all of the files inside dir1 including dir1 itself. 

(case 6)
command: we created upto root/dir1/dir2/dir3. After going back to the root folder, then
<rm dir1 -r>
successfully removes all of the files inside dir1 including dir1 itself. 


##Test cases for 3 (testing cat command)

(case 1)

command "cat test.txt"
command "cat sample.img"
command "cat dir1"

First, created an image file, a text file, and a directory. Called cat command to each file.
When the command was called to directory file, it returned cmd output: "Only Text file and Image file can be edited" "command failed"

(case 2)

command "cat test.txt -a"
command "cat sample.img -a"
command "cat dir1 -a"

Then, we called cat append command (cat -a) to each file. Since only text file supports such functionality, 
append command returned "Img file cannot be appended", "command failed", "Only Text file can be appended" when called to img file and directory file.

(case 3)

command "cat test.txt" -> "I am writing on this file" -> ":wq" -> "cat test.txt" -> ":wq" -> "cat test.txt" -> ":wq"
command "cat sample.img" -> "X X X X X3" -> ":wq" -> "cat sample.img" -> ":wq" -> "cat sample.img" -> ":wq"

Since cat command without "-a" should enable users to overwrite on the same file with command ":wq" and exit without saving with command ":q",
We wanted to test if the command saves the empty space successfully when ":wq" command is called without any additional input for file content.
Text file behaved as we expected but Image file returned an error, "vector subscript out of range". In order to handle this error, we decided to change the
design pattern of our code. In ImageFile.cpp, write() method originally does not return success when the size of input data (vector<char>) is 0.
We modified the if statement to return success (Line 33) to make sure the command does not return vector subscript out of range error. 

(case 4)

command "cat test.txt" -> "Exiting without save testing" -> ":q" -> "ds test.txt"
command "cat sample.img" -> "X  X2" -> ":q" -> "ds sample.img"

In order to check if ":q" command behaves as we expected, we inserted well-formed inputs into both files and hit the ":q" command.
Both displayed nothing and returned no error because ":q" command should not save any inputs and return success.



##Test cases for 4 (testing ds command)

(case 1)

command "ds"
command "ds <filename> -d"

First, created an image file, a text file, and a directory. Called cat command on image file and text file.
Added contents in text and image file ("Testing" for text file and "X  X2" for image file), :wq to save.
Called DS command on image, text and directory file. Calling ds on directory file didn't return anything, but image file and text file both returned
the contents that were added with cat command. ("Testing" and "X  X" printed in the board size 2 x 2)

(case 2)

command "ds <filename> -d    a"

We added an extra string after "-d" to check if it returns the same behavior as unformatted display commmand(ds <filename> -d).
The returned cmd output was "Invalid command input", which indicates such command does not exist.

(case 3)

command "ds <filename> -a"

We tested this case to make sure any other inputs other than "-d" at the end does not return the same output as unformatted display command(ds <filename> -d).
The returned cmd output was "Invalid command input", which indicates such command does not exist.


(case 4)

command "touch dir1, cd dir1"
command "touch test.txt, touch sample.img, touch dir2"
command "ds dir1"
command "ds dir1 -d"

We tested this case to make sure if directory file also displays its content when ds commands are called. After a text file, an image file, and a directory
were added to dir1, we called both ds command and ds -d command to the directory. Both commands displayed the same result: "test.txt sample.img dir2" Since
unformatted display command's output is different only when it is called to an image file which contains a well-formatted contents.



##Test cases for 5 (testing cp command)

(case 1)
command: We created dir1, dir2, t.txt and then, 
<cp t.txt root/dir1>-> the program successfully copied the file and put it under a intended directory. 

(case 2)
command: We created dir1, dir2, t.txt and changed the content of t.txt to "hello". Then,
<cp t.txt root/dir1>
<cd dir1>
<ds t.txt> -> the program showed expected behavior. 

(case 3) 
command: We created dir1, dir2, and then
<cp dir1 root/dir2> -> this gave us a "Directory cannot be copied" cout, which is an expected behavior since directory
should not be copied. 

(case 4)
command:
<cp filethatdoesnotexists.txt root/dir1>
-> force quit the program, which is not expected bahavior. 
We fixed this issue by checking the validity of the file first, and if the file path is not valid, the method returned 
error code. 

(case 5)
command:
<cp t.txt root/dirjrjrj>
-> The execute method successfully returned error code. 

(case 6)
command: we created t.txt in root/dir1 and created dir2 in root/. Then, inside dir1 folder
<cp t.txt root/dir2> -> the program successfully copied the file into correct directory. 



##Test cases for 6 (testing sym command)

(case 1)
command:
touch t.txt
touch dir1
touch dir2
sym t.txt root/dir1
sym t.txt root/dir2 -> at this step, program threw an error in ProxyFile::getName(). This error occured since we didn't set a seperate case for symbolic linking the
proxy file. We fixed this issue by dynamically casting the object and based on the result of dynamic casting, we seperated cases.

(case 2)
command:
touch t.txt
touch dir1
touch dir2
touch dir3
sym t.txt dir1 -> at this step, unexpected behavior was detected. The program suppose to not create a additional proxy file when
the path is invalid, but in this case, it created symbolic link with proxy file. Thus, I fixed this by first checking if the new path that
user provided works or not. If the path is invalid (returns nullptr), then before deleting the original file, return an error code. Otherwise,
if the path is valid, the code moves on to the next steps.

(case 3)
command: We created dir1, dir2, dir3 and t.txt. Then,
<sym t.txt root/dir1>
<sym t.txt root/dir2>
<sym t.txt root/dir3>
and it successfully created and added symbolic links to the directory files.

(case 4)
command: we created dir1, and t.txt. Then,
<sym sjhdfkjh root/dir1>
and the program successfully returned the message <file does not exists> and the functionality was not damaged.

(case 5)
command: we created dir1, dir2, and t.txt. and then,
<sym t.txt root/dir1>
<cat t.txt> -> and put string "hello"
<cd dir1>
<ds t.txt> -> and the program also displayed "hello", which is a correct behavior.

(case 6)
command: continued from case 6
<rm t.txt>
<cd ..>
<ds t.txt> -> the program successfully displayed the content of t.txt

(case 7)
we copied an existing proxy file, then modified another proxy file to ensure that the copy was not modified
command: 
<touch file.txt>
<touch dir1>
<touch dir2>
<sym file.txt root/dir1>
<cp file.txt root/dir2>
<cat file.txt> -> and put string "hello"
<ds file.txt> -> confirmed program displayed "hello"
<cd dir1>
<ds file.txt> -> confirmed program also displayed "hello"
<cat file.txt> -> and overwrote proxy file with "hi"
<cd ..>
<cd dir2>
<ds file.txt> -> saw program displayed "hello", which is expected behavior since copied file should not change
