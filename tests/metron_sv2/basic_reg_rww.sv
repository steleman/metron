`include "metron/tools/metron_tools.sv"

// Writing a register multiple times in the same function is OK.

module Module (
  // global clock
  input logic clock
);
/*public:*/

  always_comb begin : tock
    /*tick()*/;
  end

/*private:*/

  always_ff @(posedge clock) begin : tick
    temp=my_reg;
    my_reg <= 0;
    my_reg <= 1;
  end

  logic my_reg;
endmodule