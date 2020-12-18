# Matlab-MEX

This repository contains personal experiments about mixing Matlab with C and parallel C code for higher performance.

For now, the only sample is an adjustable median filter function (PolishMatrix.m) with its equivalents in plain C (_CPolishMatrix.c_) and parallel C code with OpenMP (_ParCPolishMatrix.c_). Both C versions share the ad-hoc SimpleMedian code.

## Compiling the MEX files

The plain C version:

```matlab
mex CPolishMatrix.c SimpleMedian.c CFLAGS="\$CFLAGS -std=c99 -O2"
```

The parallel C version:

```matlab
mex ParCPolishMatrix.c SimpleMedian.c CFLAGS="\$CFLAGS -std=c99 -fopenmp -O2"  LDFLAGS="\$LDFLAGS -fopenmp"
```

## Sample benchmark and correctness comprobation

Test in old Matlab 2012a running in an Intel Core i5 660 @ 3.33 GHz (2 physical cores) and 8GB of RAM:

```matlab
>> matrix = rand(250, 300);
>> tic; filteredA = PolishMatrix(matrix, 1); toc;
Elapsed time is 0.993706 seconds.
>> tic; filteredB = CPolishMatrix(matrix, 1); toc;
Elapsed time is 0.042421 seconds.
>> tic; filteredC = ParCPolishMatrix(matrix, 1); toc;
Elapsed time is 0.036890 seconds.
>> isequal(filteredA, filteredB)

ans =

     1

>> isequal(filteredA, filteredC)

ans =

     1

>> tic; filteredA = PolishMatrix(matrix, 2); toc;
Elapsed time is 1.061068 seconds.
>> tic; filteredB = CPolishMatrix(matrix, 2); toc;
Elapsed time is 0.134028 seconds.
>> tic; filteredC = ParCPolishMatrix(matrix, 2); toc;
Elapsed time is 0.060522 seconds.
>> isequal(filteredA, filteredB)

ans =

     1

>> isequal(filteredA, filteredC)

ans =

     1

>> tic; filteredA = PolishMatrix(matrix, 3); toc;
Elapsed time is 1.186367 seconds.
>> tic; filteredB = CPolishMatrix(matrix, 3); toc;
Elapsed time is 0.278319 seconds.
>> tic; filteredC = ParCPolishMatrix(matrix, 3); toc;
Elapsed time is 0.130497 seconds.
>> isequal(filteredA, filteredB)

ans =

     1

>> isequal(filteredA, filteredC)

ans =

     1

```

## License

This code can be used by anyone interested at it as long as this original source is referred: N.C. Cruz, University of Almería, Spain.

## Acknowledgements

* Many thanks to the author of the following _Walking Randomly_'s post: [Parallel MATLAB with openmp mex files](http://walkingrandomly.com/?p=1795)
* Many thanks to Pascal Getrever for writing his MEX coding guide: [Writing MATLAB C/MEX Code](https://es.mathworks.com/matlabcentral/fileexchange/27151-writing-matlab-c-mex-code?s_tid=prof_contriblnk)

