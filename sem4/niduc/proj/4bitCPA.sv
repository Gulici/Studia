module CPA_4bit(
	input [3:0] A,
	input [3:0] B,
	input cin,
	input [3:0] err_tab [0:3],
	output [3:0] S,
	output cout);
	
	wire [3:0] c;
	
	FAdder fa0(A[0],B[0],cin,err_tab[0],S[0],c[0]);
	FAdder fa1(A[1],B[1],c[0],err_tab[1],S[1],c[1]);
	FAdder fa2(A[2],B[2],c[1],err_tab[2],S[2],c[2]);
	FAdder fa3(A[3],B[3],c[2],err_tab[3],S[3],cout);
	
endmodule
