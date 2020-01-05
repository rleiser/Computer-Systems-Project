
# function to check for differences in 2 files
function testDiff(file1, file2, diffs){

    cmd = "diff " file1 " " file2

    # count how many lines are different
    while ((cmd | getline) > 0)
	diffs += 1

    # if there are no differences in the files, then the C program was successful in simulating the pipe
    if (diffs == 0)
	print "SUCCESS"
    # otherwise, print how many differences there were in the files
    else
	print "FAIL: " diffs " DIFFERENCES"

    close(cmd)
}



BEGIN{

    # create a file with results of the command in pipe form
    cmd1 = "zcat NYSprop.gz | grep '^LEISER '"
    while ((cmd1 | getline) > 0){
	print $0 >"pipeResult.txt"
    }
    close(cmd1)
    close("pipeResult.txt")

    # check the result of the pipe command against the result of the C program
    testDiff("pipeResult.txt", "cResult.txt")

}
