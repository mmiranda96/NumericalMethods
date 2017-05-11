function[R] = gaussJordan(A, B)
    R = rref([A B]);
endfunction
