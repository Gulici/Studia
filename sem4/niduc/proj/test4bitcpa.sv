module test4bitcpa;
	reg [3:0] A;
	reg [3:0] B;
	reg cin;
	reg [3:0] err_tab [0:3];
	
	wire [3:0] sum;
	wire cout;
	
	CPA_4bit cpa(A,B,cin,err_tab,sum,cout);
	
	initial begin 
	err_tab[0] = 0;
	err_tab[1] = 0;
	err_tab[2] = 0;
	err_tab[3] = 0;
	
	A = 1; B =15; cin = 0;
	#10; 
	$display("A=%d B=%d S=%d cout=%b", A,B,sum,cout);
	end

endmodule
