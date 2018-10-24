#/bin/bash
echo "The compiler: tlcc and tlcc_o would be generated under workdir for compiler"
echo "tlcc is without optimization!"
echo "tlcc_o is optimized with constant propagation now!"
cd ../
make
sleep 1
echo "Now, please run exec.sh to compile test.tl.It will generate un-optimized assembly code file."
echo "Please run tlcc_o to generate optimized code file! Thanks!"
exit
