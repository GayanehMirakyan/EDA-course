`timescale 1ns / 1ps

module muxTestBench();
    reg clk, rst;
    reg [7:0] a;
    reg [7:0] b;
    reg [7:0] c;
    reg [7:0] d;
    reg [1:0] select;
    reg rd_A, rd_B, rd_C, rd_D, rd_out;
    reg wr_A, wr_B, wr_C, wr_D, wr_out;
    wire [7:0] tempdata_A;
    wire [7:0] tempdata_B;
    wire [7:0] tempdata_C;
    wire [7:0] tempdata_D;
    wire [7:0] dataOut;
    wire [7:0] mux_ans;
    reg popedData;
    reg[7:0] tmp_data;


 fifo ff_A( .clock(clk), .reset(rst), .DATA_IN(a), .DATA_OUT(tempdata_A),
         .write(wr_A), .read(rd_A), .empty(buf_empty_A),
         .full(buf_full_A));


fifo ff_B( .clock(clk), .reset(rst), .DATA_IN(b), .DATA_OUT(tempdata_B),
         .write(wr_B), .read(rd_B), .empty(buf_empty_B),
         .full(buf_full_B));


fifo ff_C( .clock(clk), .reset(rst), .DATA_IN(c), .DATA_OUT(tempdata_C),
         .write(wr_C), .read(rd_C), .empty(buf_empty_C),
         .full(buf_full_C));


fifo ff_D( .clock(clk), .reset(rst), .DATA_IN(d), .DATA_OUT(tempdata_D),
         .write(wr_D), .read(rd_D), .empty(buf_empty_D),
         .full(buf_full_D));


fifo ff_out( .clock(clk), .reset(rst), .DATA_IN(mux_ans), .DATA_OUT(dataOut),
         .write(wr_out), .read(rd_out), .empty(buf_empty_out),
         .full(buf_full_out));

mux8bit mux( .aa(tempdata_A), .bb(tempdata_B), .cc(tempdata_C),
            .dd(tempdata_D), .select(select), .ans(mux_ans));

initial
begin
  clk = 0;
  rst = 1;
  rd_A = 1;
  rd_B = 1;
  rd_C = 1;
  rd_D = 1;
  rd_out = 0;
  wr_A = 0;
  wr_B = 0;
  wr_C = 0;
  wr_D = 0;
  wr_out = 1;
  popedData = 0;
  tmp_data = 0;

  #15 rst = 0;

end

always #5 clk = ~clk;

always @(posedge clk ) begin
  push_A(5+tmp_data);
  push_B(8+tmp_data);
  push_C(10+tmp_data);
  push_D(45+tmp_data);
  select <= tmp_data % 4;
  pop(popedData);
  tmp_data <= tmp_data + 1;
end

task push_A;
input[7:0] data_A;
    if( buf_full_A )
        $display("---Cannot push into A: Buffer Full---");
    else
    begin
        a = data_A;
        $display("Pushed into A ", data_A);
        wr_A = 1;
           @(posedge clk);
           #1 wr_A = 0;
        end
endtask

task push_B;
input[7:0] data_B;

   if( buf_full_B )
        $display("---Cannot push into B: Buffer Full---");
   else
   begin
        b = data_B;
        $display("Pushed into B",data_B);
        wr_B = 1;
           @(posedge clk);
           #1 wr_B = 0;
   end

endtask

task push_C;
input[7:0] data_C;

   if( buf_full_C )
        $display("---Cannot push into C: Buffer Full---");
   else
   begin
        c = data_C;
        $display("Pushed into C",data_C);
        wr_C = 1;
           @(posedge clk);
           #1 wr_C = 0;
   end

endtask

task push_D;
   input[7:0] data_D;

   if( buf_full_D )
        $display("---Cannot push into D: Buffer Full---");
   else
   begin
        d = data_D;
        $display("Pushed into D", data_D);
        wr_D = 1;
           @(posedge clk);
           #1 wr_D = 0;
   end

endtask

task pop;
   output [7:0] data_mux;

   if( buf_empty_out )
        $display("---Cannot Pop: Buffer Empty---", mux_ans);
   else
   begin

        rd_out = 1;
        data_mux = mux_ans;
        $display("-------------------------------Poped ", data_mux);

          @(posedge clk);
          #1 rd_out = 0;

    end
endtask


endmodule