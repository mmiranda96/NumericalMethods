function [R] = cramer(A, B)
    s = size(A);
    detS = det(A);
    R = zeros(s(1), 1);
    for i = 1 : s(1)
        t = A(:, i);
        A(:, i) = B;
        R(i) = det(A) / detS;
        A(:, i) = t;
    end
endfunction

A = [1., 2.; 1., -2.]
B = [9.; 1.]
S = cramer(A, B)
