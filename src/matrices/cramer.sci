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

A = [3., -0.1, -0.2; 0.1, 7., -0.3; 0.3, -0.2, 10.]
B = [7.85; -19.3; 71.4]

R = cramer(A, B)
