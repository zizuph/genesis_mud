
/*
*    coded by Amelia
*    the rock which the mermaid sits on;)
*    coded 8/7/95
*/


inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

void
reset_room()
{
    object mm = present("mermaid", TO);

    seteuid(getuid(TO));
    if (!objectp(mm))
        {
            mm = clone_object(MERMAID);
            mm->move(TO);
        }
}

void
create_room()
{

    ::create_room();
    set_short("A large rock in the sea");
    set_long("This is a large granite rock that juts out "+
        "above the water, and it's fairly dry here. "+
        "You have an excellent view of the harbour area "+
        "to the north, and the sea extends all the way to the horizon. "+
        "Way to the southeast you see a large mountain. Back to "+
        "the east is the white sandy beach. This rock is "+
        "part of a line of rocks that extends out into the "+
        "sea.\n");


   add_item((({"rock", "line of rocks", "granite rock"})),
      "The large, somewhat flat granite rock you are sitting on "+
      "is part of a line of rocks, which extends out from the "+
      "shore into the sea. It forms a natural barrier for the "+
      "harbour.\n");
   add_item((({"sea", "water"})),
      "The blue-green Calian sea is all around you. The "+
      "water appears very clear, but darker blue as it gets "+
      "deeper. You can safely dive back in from this rock.\n");
   add_item((({"harbour", "harbour area"})),
     "To the north you can see the harbour area of Gelan, "+
      "where ships arrive and leave every now and then. "+
      "There is a lot of activity there.\n");
   add_item((({"mountain", "large mountain"})),
      "Far to the southeast, mighty Kyrus dominates the horizon.\n");
   add_item((({"beach", "white sandy beach"})),
      "At some distance to the east you see the shoreline "+
      "and white sandy beach.\n");

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
}

void
init()
{
    ::init();
    add_action("dive_in", "climb");
    add_action("dive_in", "dive");
}


int
dive_in(string str)
{
    object tp = this_player();

    notify_fail("Dive where?\n");
   if (str == "down" || str == "in" || str == "in water" ||
      str == "back" || str == "down rock")
        {
            write("You dive back into the water.\n");
            tell_room(environment(tp), QCTNAME(tp)+
                " dives back into the water.\n", tp);
            tp->move_living("M", BACK_IN_WATER, 1);
            write("Splash!\n");
            tell_room(environment(tp), "Splash! "+QCTNAME(tp)+
                " dives in.\n", tp);
            return 1;
        }
    return 0;
}
