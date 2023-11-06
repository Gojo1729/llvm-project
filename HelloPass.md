# Building LLVM

1. Clone the LLVM repo
2. create a build folder inside `llvm-project/llvm `
3. cd into the above build folder
4. run this command inside the build folder -
5. `cmake -G "Ninja" -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE="Debug" -DLLVM_TARGETS_TO_BUILD="host" -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_PARALLEL_LINK_JOBS=1 ../`
6. make sure you use DLLVM_PARALLEL_LINK_JOBS = 1, as the linking takes lot of memory
7. If you are using WSL, make sure you have 12GB of RAM, update your C:\Users\shivs\.wslconfig 
		`[wsl2]
		`memory=8GB

8. then run wsl --shutdown in powershell, reopen ubuntu terminal
9. inside the build folder after cmake command run `ninja -j 3` , decrease j flag value if you run into memory issue like SIGFAULT issues
10. If successful, clanf will be built inside ./bin  folder inside build
11. compile and run a small c program to check if clang is working or not.

# Hello Pass

This branch implements the code to find:


	• Number of Basic Blocks 
	• Number of Instructions in each basic block 
	• Basic block with max instructions 
	• Basic Block with 2+ successors & predecessors 
	• Basic Block with Max successors & predecessors


1. Take a c file for finding factorial.
2. From llvm-project/llvm/mysrc folder  ../build/bin/clang factorial.c -emit-llvm -S -Xclang -disable-O0-optnone -o fact.ll
3. This will give you llvm IR

After making changes to the 
./llvm-project/llvm/lib/Transforms/Utils/HelloWorld.cpp

inside run function. Run function is called for every function present in the IR - fact.ll

4. ../build/bin/opt -disable-output fact.ll -passes=helloworld - Runs the helloworld pass with the latest changes you made to the code.

5. `../build/bin/opt -passes=dot-cfg fact.ll -disable-output` - Use this to get a flow graph for the given IR file.


# Issues faced.
1. Opt None issue
https://github.com/banach-space/llvm-tutor/issues/33
https://stackoverflow.com/questions/67393329/llvm-doesnt-generate-cfg

Make sure you add -disable-o0-optnone flag while generating LLVM IR. 
Or else you will not get the functions. Basically, with the current instructions, all functions in the output *.ll file are decorated with the optnone attribute. It's documented in https://llvm.org/docs/LangRef.html (search for optnone). The helloworld pass skips all functions decorated with optnone.

2. Don't delete the .ninja_log file in build directory, this will lead to rebuilding the whole source code from the beginning.

3. The opt has been updated with new pass managers, so you need to send the passes as arguments to the opt pipeline.
LLVM (http://llvm.org/):
  LLVM version 18.0.0git
  DEBUG build with assertions.
  Default target: x86_64-unknown-linux-gnu
  Host CPU: znver3