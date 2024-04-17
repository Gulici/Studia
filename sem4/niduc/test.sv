module full_adder(input a,b, cin, output s, cout);
    assign S = a ^ b ^ cin;
    assign cout