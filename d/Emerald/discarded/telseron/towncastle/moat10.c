inherit "/d/Emerald/tmp/towncastle/moat";
 
#include "default.h"
 
void
create_moat()
{
    add_exit(TCASTLE_DIR + "moat11", "north", 0, 4);
    add_exit(TCASTLE_DIR + "moat9", "east", 0, 4);
}
