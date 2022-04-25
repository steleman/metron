#include "metron_tools.h"

// X Writing field sig1 changed state from CTX_SIGNAL to CTX_INVALID

class Module {
 public:
  void tock1() { sig1 = sig2; }

  void tock2() { sig2 = sig1; }

  void tock3() { sig1 = 0; }

 private:
  logic<8> sig1;
  logic<8> sig2;
};
