inherit "/d/Shire/std/room";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_shire_room()
{
   add_prop(ROOM_S_MAP_FILE, "grey_havens.txt");

   set_short("A path along the Gulf of Lhun");
   set_long("This path connects the vast network of docks of the city of "+
   "Grey Havens. The docks seem well spaced "+
   "in order to prevent overcrowding, and the passenger ferries are "+
   "the farthest out of all. West is a pier.\n");

   add_exit("/d/Shire/common/greyhaven/shore","north",0,1);
   add_exit("/d/Shire/common/greyhaven/path5","south",0,2);
   add_exit("/d/Shire/common/greyhaven/pier4","west",0,1);

}
