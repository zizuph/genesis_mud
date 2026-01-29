inherit "/std/door";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_door()
{
    set_name("door");
    set_adj("large");
    add_adj("iron");
    set_other_room(RHUN+"rhosgobel_quests/citadel/grey_room");
    set_door_id("_rhun_citadel_door");
    set_open(0);
    set_lock(1);
    set_door_desc("This is a large, heavy iron door in the "+
        "citadel cellar.\n");
    set_open_desc("This large, heavy iron door is ajar.\n");
    set_closed_desc("A securely-shut large iron door.\n");
    set_door_name(({"door","iron door","large door","large iron door"}));
    set_key(38000001);
}
