module testAdder;
	reg a,b,cin;
	wire sum, cout;
	byte err_in;
	byte sum_ok;
	
	FAdder add(a,b,cin,err_in,sum,cout);
	

	initial begin
	assign sum_ok = a+b+cin; 
	//$monitor ("ERROR: %d a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b",err_in, a,b,cin,sum,cout);
	for(err_in = 0; err_in <= 8; err_in++) begin
	$display ("USZKODZENIE nr: %0d", err_in);
	a = 0; b = 0; cin = 0;
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout)); 
	a = 1; b = 0; cin = 0;
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout));  
	a = 0; b = 1; cin = 0;
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout));  
	a = 1; b = 1; cin = 0;
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout));  
	a = 0; b = 0; cin = 1; 
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout));   
	a = 1; b = 0; cin = 1;
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout));  
	a = 0; b = 1; cin = 1;
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout));  
	a = 1; b = 1; cin = 1;
	#10;
	$display("a=%0b b=%0b c_in=%0b, S=%b, c_out=%0b  %0d / %0d",a,b,cin,sum,cout,sum_ok,(sum+2*cout)); 
	end
	end
endmodule
