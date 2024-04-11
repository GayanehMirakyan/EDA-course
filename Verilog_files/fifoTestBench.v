`timescale 1ns / 1ps

module fifoTestBench();
reg clk, rst, wr_en, rd_en;
reg[7:0] buf_in;
reg[7:0] tempdata;
reg[7:0] pushdata;
wire [7:0] buf_out;
integer i, j;

fifo ff( .clock(clk), .reset(rst), .DATA_IN(buf_in), .DATA_OUT(buf_out),
         .write(wr_en), .read(rd_en), .empty(buf_empty),
         .full(buf_full));

initial
begin
   clk = 0;
   rst = 1;
        rd_en = 0;
        wr_en = 0;
        tempdata = 0;
        buf_in = 0;
		  i = 0;
		  
        #15 rst = 0;
end

always @(posedge clk ) begin
		  if(i < 9) begin
		    push(i);
		    pop(tempdata);
			 i = i + 1;
		  end
		  end

always #5 clk = ~clk;

task push;
input[7:0] data;


   if( buf_full )
            $display("---Cannot push: Buffer Full---");
        else
        begin
		     buf_in = data;
           $display("Pushed ",data );
           wr_en = 1;
                @(posedge clk);
                #1 wr_en = 0;
        end

endtask

task pop;
output [7:0] data;

   if( buf_empty )
            $display("---Cannot Pop: Buffer Empty---");
   else
        begin

     rd_en = 1;
     data = buf_out;
     $display("-------------------------------Poped ", data);
          @(posedge clk);
          #1 rd_en = 0;

        end
endtask

endmodule