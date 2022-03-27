// RISC-V SiMPLE SV -- Toplevel
// BSD 3-Clause License
// (c) 2017-2019, Arthur Matos, Marcus Vinicius Lamar, Universidade de Brasília,
//                Marek Materzok, University of Wrocław

`ifndef RVSIMPLE_TOPLEVEL_H
`define RVSIMPLE_TOPLEVEL_H

`include "config.sv"
`include "constants.sv"
`include "example_data_memory_bus.sv"
`include "example_text_memory_bus.sv"
`include "metron_tools.sv"
`include "riscv_core.sv"

module toplevel
(
  input logic clock,
  input logic reset,
  output logic[31:0] o_bus_read_data,
  output logic[31:0] o_bus_address,
  output logic[31:0] o_bus_write_data,
  output logic[3:0]  o_bus_byte_enable,
  output logic  o_bus_read_enable,
  output logic  o_bus_write_enable,
  output logic[31:0] o_inst,
  output logic[31:0] o_pc
);
 /*public:*/
  /*logic<32> o_bus_read_data;*/
  /*logic<32> o_bus_address;*/
  /*logic<32> o_bus_write_data;*/
  /*logic<4>  o_bus_byte_enable;*/
  /*logic<1>  o_bus_read_enable;*/
  /*logic<1>  o_bus_write_enable;*/
  /*logic<32> o_inst;*/
  /*logic<32> o_pc;*/

  //----------------------------------------

  initial begin : init
    /*core.init();*/
    /*text_memory_bus.init();*/
    /*data_memory_bus.init();*/
  end

  //----------------------------------------

  always_comb begin : tock
    logic[31:0] inst;
    logic[31:0] write_data;
    logic write_enable;
    text_memory_bus_address = core_pc;
    inst = text_memory_bus_read_data;

    core_inst = inst;
    /*core.tock_decode(inst);*/
    core_inst = inst;
    /*core.tock_alu(inst);*/
    core_inst = inst;
    /*core.tock_next_pc_select(inst);*/
    core_inst = inst;
    core_bus_read_data = data_memory_bus_read_data;
    data_memory_bus_address = core_bus_address2;
    data_memory_bus_read_enable = core_bus_read_enable2;
    /*core.tock_writeback(inst, data_memory_bus.read_data(core.bus_address2(), core.bus_read_enable2()));*/

    core_inst = inst;
    write_data = core_bus_write_data2;
    write_enable = core_bus_write_enable2;

    data_memory_bus_address = core_bus_address2;
    data_memory_bus_write_enable = write_enable;
    data_memory_bus_byte_enable = core_bus_byte_enable2;
    data_memory_bus_write_data = write_data;
    core_inst = inst;
    /*data_memory_bus.tocktick(
      core.bus_address2(),
      write_enable,
      core.bus_byte_enable2(inst),
      write_data
    );*/

    core_reset = reset;
    core_inst = inst;
    /*core.tocktick_pc(reset, inst);*/
    core_inst = inst;
    /*core.tocktick_regs(inst);*/
    o_inst = inst;
    data_memory_bus_address = core_bus_address2;
    data_memory_bus_read_enable = core_bus_read_enable2;
    o_bus_read_data = data_memory_bus_read_data;
    o_bus_address = core_bus_address2;
    o_bus_write_data = write_data;
    core_inst = inst;
    o_bus_byte_enable = core_bus_byte_enable2;
    o_bus_read_enable = core_bus_read_enable2;
    o_bus_write_enable = write_enable;
    o_pc = core_pc;
  end

  //----------------------------------------

 /*private:*/
  riscv_core core(
    // Inputs
    .clock(clock),
    .inst(core_inst), 
    .bus_read_data(core_bus_read_data), 
    .reset(core_reset), 
    // Outputs
    .bus_write_data2(core_bus_write_data2), 
    .bus_byte_enable2(core_bus_byte_enable2), 
    .bus_read_enable2(core_bus_read_enable2), 
    .bus_write_enable2(core_bus_write_enable2), 
    .bus_address2(core_bus_address2), 
    .pc(core_pc)
  );
  logic[31:0] core_inst;
  logic[31:0] core_bus_read_data;
  logic core_reset;
  logic[31:0] core_bus_write_data2;
  logic[3:0]  core_bus_byte_enable2;
  logic  core_bus_read_enable2;
  logic  core_bus_write_enable2;
  logic[31:0] core_bus_address2;
  logic[31:0] core_pc;

  example_text_memory_bus text_memory_bus(
    // Inputs
    .clock(clock),
    .address(text_memory_bus_address), 
    // Outputs
    .read_data(text_memory_bus_read_data)
  );
  logic[31:0] text_memory_bus_address;
  logic[31:0] text_memory_bus_read_data;

  example_data_memory_bus data_memory_bus(
    // Inputs
    .clock(clock),
    .address(data_memory_bus_address), 
    .read_enable(data_memory_bus_read_enable), 
    .write_enable(data_memory_bus_write_enable), 
    .byte_enable(data_memory_bus_byte_enable), 
    .write_data(data_memory_bus_write_data), 
    // Outputs
    .read_data(data_memory_bus_read_data)
  );
  logic[31:0] data_memory_bus_address;
  logic data_memory_bus_read_enable;
  logic data_memory_bus_write_enable;
  logic[3:0] data_memory_bus_byte_enable;
  logic[31:0] data_memory_bus_write_data;
  logic[31:0] data_memory_bus_read_data;

endmodule;

`endif  // RVSIMPLE_TOPLEVEL_H

