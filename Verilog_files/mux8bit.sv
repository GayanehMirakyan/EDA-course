
module mux8bit(input [7:0] aa , 
               input [7:0] bb , 
         input [7:0] cc, 
         input [7:0] dd ,
         input [1:0] select,
               output reg [7:0] ans);

  always @(aa or bb or cc or dd or select) begin
    case(select)
    2'b00: begin ans <= aa; end
    2'b01: begin ans <= bb; end
    2'b10: begin ans <= cc; end
    2'b11: begin ans <= dd; end
    endcase
  end
  
endmodule


module fifo #(parameter DEPTH=8, DATA_WIDTH=8) (
  input clock,
  input reset,
  input write,
  input read,
  input [DATA_WIDTH - 1 : 0] DATA_IN,
  output reg empty,
  output reg full,
  output reg [DATA_WIDTH - 1 : 0] DATA_OUT);
  
  reg [$clog2(DEPTH) - 1 : 0] write_ptr, read_ptr;
  reg [DATA_WIDTH - 1 : 0] fifo[DEPTH];
  reg [$clog2(DEPTH) - 1 : 0] count;
  initial begin
    full <= 0;
    empty <= 1;
    count <= 0;
  end
  
  always @(posedge clock)
  begin
        
    if(reset)
      begin
        write_ptr <= 0;
        read_ptr <= 0;
        DATA_OUT <= 0;
        count <= 0;
      end
    else 
        begin
         if(write & !full)
          begin
            fifo[write_ptr] <= DATA_IN;
            write_ptr <= write_ptr + 1;
            count <= count + 1;
          end
          else if (read & !empty)
          begin
            DATA_OUT <= fifo[read_ptr];
            read_ptr <= read_ptr + 1;
            count <= count - 1;
          end
       end
  end

  always @(write_ptr or read_ptr)  begin
  
    full <= (count == DEPTH);
    empty <= (count == 0);
        
  end


endmodule
