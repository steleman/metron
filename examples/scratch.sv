`include "metron/tools/metron_tools.sv"

// Public register member variables get moved to the output port list.

moduleModule (
  // global clock
  input logic clock,
  // output registers
  logic my_reg
);
/*public:*/
  always_comb begin : tock
    /*tick()*/;
  end
  logic my_reg;

/*private:*/
  always_ff @(posedge clock) begin : tick
    my_reg <= my_reg + 1;
  end
endmodule