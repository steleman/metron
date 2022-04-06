`include "metron_tools.sv"

// Modules can call init() on their submodules.

module Submod
(
  input logic clock,
  output logic[7:0] tock
);
/*public:*/

  initial begin /*init*/
    sub_reg = 3;
  end

  always_comb begin /*tock*/
    tock = sub_reg;
  end

/*private:*/
  logic[7:0] sub_reg;
endmodule

module Module
(
  input logic clock
);
/*public:*/

  initial begin /*init*/
    /*submod.init()*/;
  end

/*private:*/

  Submod submod(
    // Inputs
    .clock(clock),
    // Outputs
    .tock(submod_tock)
  );
  logic[7:0] submod_tock;

endmodule

