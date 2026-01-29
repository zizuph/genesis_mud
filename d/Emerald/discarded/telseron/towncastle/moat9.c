inherit "/d/Emerald/tmp/towncastle/moat";
 
#include "default.h"
 
void
create_moat()
{
    add_exit(TCASTLE_DIR + "moat10", "west", 0, 4);
    add_exit(TCASTLE_DIR + "moat8", "east", 0, 4);
}
