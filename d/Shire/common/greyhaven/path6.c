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
      "Grey Havens. North are more piers and the city of Mithlond. "+
      "There is a pier towards the west.\n");



    add_exit("/d/Shire/common/greyhaven/path5","north",0,1);
    add_exit("/d/Shire/common/greyhaven/pier6","west",0,1);
    add_exit("/d/Shire/common/greyhaven/path7","south",0,1);

}
