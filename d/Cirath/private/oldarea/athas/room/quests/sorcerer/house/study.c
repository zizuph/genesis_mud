inherit "/std/room";
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
 
create_room()
{
 
    set_short("Study");
    set_long(BSS("This is the templar Pandora's private study, where she "+
		"sits down when she want to read some of her many books. "+
		"There is a desk and a chair here.\n"));
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(HOUS_D + "library","west",0);

    add_item(({"desk", "desk"}), BSS("The desk is large, and used when reading books\n"));
    add_item(({"chair", "chair"}), BSS("The chair is comfortable, but you do not dare to sit on it.\n"));
 
}
