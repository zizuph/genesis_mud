inherit "/d/Emerald/tmp/towncastle/moat";
 
#include "default.h"
 
void
create_moat()
{
    add_exit(TCASTLE_DIR + "by_moat", "north", 0, 4);
    add_exit(TCASTLE_DIR + "moat3", "east", 0, 4);
    add_exit(TCASTLE_DIR + "moat1", "west", 0, 4);
}
