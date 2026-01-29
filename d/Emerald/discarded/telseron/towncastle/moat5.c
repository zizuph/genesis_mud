inherit "/d/Emerald/tmp/towncastle/moat";
 
#include "default.h"
 
void
create_moat()
{
    add_exit(TCASTLE_DIR + "moat6", "south", 0, 4);
    add_exit(TCASTLE_DIR + "moat4", "north", 0, 4);
}
