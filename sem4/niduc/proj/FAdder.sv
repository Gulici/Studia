module FAdder(
	input a,b,c,
	input [3:0]err,
	output sum, cout
);	
	wire wa,wb,wc;
	wire w1,w2,w3;
	
	// mo?liwe uszkodzenie wejscia
	assign wa = 	err == 1 ? 0 : a;
	assign wb = 	err == 2 ? 0 : b;
	assign wc = 	err == 3 ? 0 : c;
	//uszkodzenia bramek
	assign w1 = 	err == 4 ? 0 : wa ^ wb;
	assign sum = 	err == 5 ? 0 : w1 ^ wc;
	assign w2 = 	err == 6 ? 0 : w1 & wc;
	assign w3 = 	err == 7 ? 0 : wa & wb;
	assign cout =  	err == 8 ? 0 : w2 | w3;

endmodule
