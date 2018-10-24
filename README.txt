				  tlcc - TL Language Compiler
what is it
tlcc is a complier written by c language which could finish lexical analysis, parsing and generate assembly code for TL language program. 
You could find a subfolders /workdir and all source files in the main folder.
At the same time, tlcc_o was generated at the same time and it provide constant propagation optimaization.
	
How to generate tlcc and tlcc_o in workdir
In the main folder, you will see several files. main.c is the C source code file to generate telco, and main_optimization.c is to generate tlcc_o. At the same time, we also provide the makefile. If you make any changes, you could simple generate new tlcc and tlcc_o to the workdir through it.
In the workdir subfolder, you could find a build.sh script. You could run it directly and it will call makefile in the main folder to generate the new tlcc and tlcc_o.

How to use tlcc to compile TL language program
After tlcc was generated in workdir, you could start compiling through it.
In the workdir folder, we provide a exec.sh script to simplify the procedure. You could run the exec.sh with the target program together, for example: ./exec.sh test.tl . Since we did not provide additional argument for tlcc so far, running the script would have the same effect as ./tlcc test.tl .
In the workdir, we provided several TL language program for testing. test.tl and simple1.tl are two regular TL program without any error in them. error.tl and type-error1.tl are two TL program with lexical error in them.
tlcc_o should be executed manually with commander line such as $./tlcc_o test.tl. It will finish the compilation with constant propagation optimization.  
	
How to review the result
After you started running tlcc or tlcc_o with target program, result could be reviewed in several ways.
If the target program has no lexical and syntax error in it. tlcc would output the whole token list in the screen and write the whole list to token.txt in the workdir. AST file would be generated with the same name too. Type check and annotation were also finished already. Whole result could be reviewed in the AST file.
If the targe program does have some lexical error in it. tlcc would output the error information in the screen and write the whole error information to scanner_error.txt in the workdir. At the same time, all regular token would be output to the token.txt too.
After AST file was generated without semantic error, tlcc or tlcc_o would transfer target program into assembly program. Result could be executed with QtSpin. 

     
Contacts
If you find any bug or mistake happened at the running time, please contact Jin Han sni550@my.utsa.edu . Thanks!
     