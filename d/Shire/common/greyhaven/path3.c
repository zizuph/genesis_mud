inherit "/d/Shire/std/room";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

create_shire_room()
{
   add_prop(ROOM_S_MAP_FILE, "grey_havens.txt");

   set_short("A path along the Gulf of Lhun");
   set_long("This path connects the vast network of docks of the city of "+
   "Grey Havens. South you see the last pier, and to the north lies more "+
   "piers and the city of Mithlond itself. The docks seem well spaced "+
   "in order to prevent overcrowding, and the passenger ferries are "+
   "the farthest out of all.\n");

   add_exit("/d/Shire/common/greyhaven/path2","south",0,1);
   add_exit("/d/Shire/common/greyhaven/pier3","west",0,1);
   // add_exit("/d/Shire/greyhavens/harbour/ghroad1","northeast",0,1,1);

}
