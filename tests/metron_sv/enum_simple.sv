`include  "metron_tools.sv"

// Most kinds of C++ enum declarations should work.

// bad
// enum { FOO, BAR, BAZ };
// typedef enum logic[1:0] { FOO=70, BAR=71, BAZ=72 } blem;
// typedef enum { FOO, BAR=0, BAZ=1 } blem;

// good
// OK enum { FOO, BAR, BAZ } blem;
// enum { FOO=0, BAR=1, BAZ=2 } blem;
// typedef enum { FOO, BAR, BAZ } blem;
// typedef enum { FOO=0, BAR=1, BAZ=2 } blem;
// typedef enum logic[1:0] { FOO, BAR, BAZ } blem;
// typedef enum logic[1:0] { FOO=0, BAR=1, BAZ=2 } blem;

// enum struct {} ? same as enum class

module Module
(
  input logic clock
);
 /*public:*/
  enum simple_enum1 { A1, B1, C1 };
  enum simple_enum2 { A2 = 2'b01, B2 = 8'h02, C2 = 3 };

  enum { A3, B3, C3 } anon_enum_field1;
  enum { A4 = 0b01, B4 = 0x02, C4 = 3 } anon_enum_field2;

  enum class enum_class1 { A5, B5, C5 };
  enum class enum_class2 { A6 = 2'b01, B6 = 8'h02, C6 = 3 };

  // This is currently broken in TreeSitter
  // enum class typed_enum : int { A7 = 0b01, B7 = 0x02, C7 = 3 };

  typedef enum logic[7:0] {A8 = 2'b01, B8 = 8'h02, C8 = 3} sized_enum;

  function void tock();
    simple_enum1 e1;
    simple_enum2 e2;
    enum_class1 ec1;
    enum_class2 ec2;
    sized_enum se1;

    simple_enum1 e1 = A1;
    simple_enum2 e2 = B2;
    anon_enum_field1 = C3;
    anon_enum_field2 = A4;
    enum_class1 ec1 = enum_class1::B5;
    enum_class2 ec2 = enum_class2::C6;
    // typed_enum te1 = typed_enum::A7;
    sized_enum se1 = sized_enum::B8;
  endfuction
endmodule;


