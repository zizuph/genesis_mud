inherit "/std/room";
inherit "/d/Calia/sea/water_base";
#define ROCK "/d/Calia/sea/level_1/rock.c"

#include <macros.h>
#include <stdproperties.h>

void
create_room()
{

	::create_surface_room();

   add_item((({"rock", "granite rock", "large rock",
      "boulders", "line of boulders"})),
      "There is a line of boulders extending into the sea "+
      "just to the north of you. A particularly large granite "+
      "rock, with a flat rounded top is in front of you. "+
      "It looks like you might be able to climb it.\n");
   add_tell("You hear someone singing a beautiful, haunting melody. "+
      "You can't quite make out the words though.\n");
}

void
init()
{
    ::init();
    add_action("climb_rock", "climb");
}


int
climb_rock(string str)
{

    object tp = this_player();

    notify_fail("Climb what?\n");
    if (str== "rock" || str == "granite rock" ||
      str == "rock" || str == "boulder" || str == "the rock")
        {
            tp->catch_msg("You climb up the rock.\n");
            tell_room(environment(tp), QCTNAME(tp)+
                " leaves, climbing the rock.\n", tp);
            tp->move_living("M", ROCK, 1);
            tell_room(environment(tp), QCTNAME(tp)+" climbs up "+
                "the rock.\n", tp);
            return 1;
        }
    return 0;
}
