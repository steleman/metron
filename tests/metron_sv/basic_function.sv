`include "metron_tools.sv"

// Private const methods should turn into SV functions.

module Module
(
  input logic clock
);
/*public:*/

  always_ff @(posedge clock) begin /*tock*/
    /*tick()*/;
  end

/*private:*/

  always_ff @(posedge clock) begin /*tick*/
    my_reg = my_reg + some_func;
  end

  function logic[7:0] some_func();
    some_func = 3;
  endfuction

  logic[7:0] my_reg;
endmodule

