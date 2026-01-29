inherit "/d/Emerald/tmp/towncastle/moat";
 
#include "default.h"
 
void
create_moat()
{
    object gate;
 
    add_exit(TCASTLE_DIR + "moat9", "west", 0, 4);
    add_exit(TCASTLE_DIR + "moat7", "east", 0, 4);
 
    gate = clone_object(TCASTLE_DIR + "doors/gate_b");
    gate->move(this_object());
}
