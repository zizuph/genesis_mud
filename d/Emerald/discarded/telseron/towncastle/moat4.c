inherit "/d/Emerald/tmp/towncastle/moat";
 
#include "default.h"
 
void
create_moat()
{
    add_exit(TCASTLE_DIR + "moat5", "south", 0, 4);
    add_exit(TCASTLE_DIR + "moat3", "west", 0, 4);
}
