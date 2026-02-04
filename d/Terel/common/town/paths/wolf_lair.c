inherit "/std/room";
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h";
#include <macros.h>

object *wolf_arr;

reset_room()
{
   while(sizeof(wolf_arr) < 4)
     wolves();
}

wolves()
{
    object ob;
    ob = clone_object(TOWNDIR + "snow_wolf");
    /*
	ob->move(this_object());
    */
    ob->move_living("xx", this_object());

    if (!wolf_arr)
      wolf_arr = ({ ob });
    else
      wolf_arr += ({ ob });
}

create_room()
{
    set_short("Wolves den");
    set_long(break_string("This small clearing has become overrun " +
     "by wolves.  They live here, and anyone that tresspasses here " +
     "may become lunch.  There are several unpenetrable trees to " +
     "the north, and the back entrance to the house is to the west.  " +
     "Death fills the air here.\n", 70));
    add_exit(TOWNDIR + "houses/house6", "west", 0);
    reset_room();
}
