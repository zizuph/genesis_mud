inherit "/std/room";
#include <stdproperties.h>

object *gargoyl_arr;

reset_room()
{
    while(sizeof(gargoyl_arr) < 4)
	gargoyles();
}

gargoyles()
{
    object ob;
    ob = clone_object("/d/Terel/mecien/mountains/gargoyle");
    /*
	ob->move(this_object());
    */
    ob->move_living("xx", this_object());

    if (!gargoyl_arr)
	gargoyl_arr = ({ ob });
    else
	gargoyl_arr += ({ ob });
}

create_room()
{
    set_short("Dark Cavern");
    set_long(
 "A shadowed cavern, filled with columns of ice, sharp stalagmites\n"
+"and stalagtites. The rock seems to have a coal base, which mixes\n"
+"with melted ice and creates pool of fetid black water.\n"
	     );
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Terel/mecien/mountains/dcliff", "out", 0);
    reset_room();
}
