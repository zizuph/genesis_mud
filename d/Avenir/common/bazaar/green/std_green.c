
// Standard room for green  (/d/Avenir/common/bazaar/green/std_green.c)
// creator(s):   Tepisch Sept 1994
// last update: Ilyian, 21 April. Changed decriptions, fixed typos.
// purpose:     Inheritable room for garden rooms in the Bazaar Green
//
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include "/d/Avenir/common/bazaar/bazaar.h"

varargs void
make_the_room(string extra_long)
{
    if (!extra_long) { extra_long = "\n"; }

    set_name("On the Bazaar island green");

    LONG("This is a rather quiet and peaceful place compared to the rest of "
       +"the island. Plants and bushes of all sorts grow around you, "
       +"carefully tended so they do not get out of hand. "
        + extra_long);

    AI(({"market","bazaar"}), "You can hear more than see the "
      +"bazaar. Sounds of merchants hawking their wares reached your "
      +"ears here, and even surrounded by the fragrant plants, you "
      +"can still smell the odor of sweat and urine from the marketplace.\n");
   AI(({"bush", "bushes"}), "It has some kind of berries on it.\n");
   AI(({"plant", "plants"}), "The plants are strange varieties, like "
      +"nothing you have ever seen on the surface. How they can "
      +"grow under this watery half-light is beyond you, although "
      +"they do look quite hardy.\n");
   AI(({"rock", "rock wall", "wall"}), "It is a natural formation "+
      "of the dark volcanic rock which has enriched the soil.\n");
   ACI("berry", "pick", "You can't seem to reach.\n");
   ACI(({"wall", "rock", "stone"}), ({"climb", "climb up"}), "You "+
     "decide not to risk breaking your precious neck.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    IN
    LIGHT
}

//I add this routine to recognise the place to bury the bones of the
//shipcaptain. Glinda june -95.

int
query_uw_bury_place()
{
   return 1;
}
