inherit "/d/Emerald/tmp/towncastle/moat";
 
#include "default.h"
 
void
create_moat()
{
    add_exit(TCASTLE_DIR + "moat2", "east", 0, 4);
    add_exit(TCASTLE_DIR + "moat12", "south", 0, 4);
}
