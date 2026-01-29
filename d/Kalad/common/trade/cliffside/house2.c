/*     Created by:      
 *     Location:        
 *     Modified:        Toby, 970919 (fixed typo)
 */

inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("A House");
set_long("This house is actually quite large comparatively speaking. "
        +"There is no furniture here though. Just some open cabinets. "
        +"There are also some stairs leading up.\n");
add_item(({"cabinets","cabinet"}),"Inside the cabinet you find "
                                    +"some jars and some rotten food.\n");
add_item(({"jars"}),"The jars are quite dusty and out of date.\n");
add_item(({"food"}),"The food is all very rotten and covered in maggots.\n");
add_exit(TRADE(cliffside/cliffside6),"south");
add_exit(TRADE(cliffside/house2floor),"up");
add_prop(ROOM_I_INSIDE,1);
hear_bell = 2;
}
