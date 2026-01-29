inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "/d/Ansalon/goodlund/nethosak/ship/local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

void
create_cabin()
{
    set_short("A cabin inside the wooden ship");
    set_long("You stand in a small wooden cabin. Within the large "+
             "boat know as 'The Gladiator'. This cabin has been "+
             "decorated with maps of the different seas in Krynn. "+
             "A thick wooden table stands in the middle of the cabin.\n");

    add_item("door","This solid wooden door leads up to the " +
      "deck above.\n");
    add_item("table", "A thick wooden table. A few pieces of navigation "+
                      "are scattered over the table.\n");

    add_item("equipment","Since you're not a sailor, you have no idea "+
                         "how to use the different pieces of equipment. "+
                         "So you dicide to leave it alone.\n");

    add_exit(SHIP_D + "deck","up",0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

sounds()
{
    if (random(2))
	return "The ships hull cracks loudly as it sways with the wind.\n";

    return "The ship sails gently though the water.\n";
}


