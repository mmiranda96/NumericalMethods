function [R] = forwardElimination(A, B)
    s = size(A)(1);
    R = [A B];
    for p = 1 : 1 : s
        pivot = R(p,p);
        for i = p + 1 : 1 : s
            fr = R(i, p)
            R(i, :) = R(i, :) - R(p, :) / pivot * fr;
        end
    end
endfunction

function [R] = backwardSubstitution(M)
    s = size(M)(1);
    R = zeros(s, 1);
    for i = s : -1 : 1
        R(i) = M(i, s + 1);
        for j = s : -1 : i + 1
           R(i) = R(i) -  M(i, j) * R(j);
        end
        R(i) = R(i) / M(i, i);
    end
endfunction

function [R] = gauss(A, B)
    R = forwardElimination(A, B);
    R = backwardSubstitution(R);
endfunction

A = [7., 2.; -21., -5.]
B = [16.; 50.]
R = gauss(A, B);
