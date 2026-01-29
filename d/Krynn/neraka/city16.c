/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object baaz1, baaz2;

create_tantallon_room()
{
   set_short("Center of Tantallon");
   set_long(BS(
         "You are in the middle of Tantallon. You stand in the southeast " +
         "corner of an opening. A lot of people are running around in " +
         " what appears to be " +
         "circles. The evil in the air is rather strong now. One big tent is " +
         "blocking the way south but the opening stretches out north and " +
         "east." +
         "", SL));
   
   add_item(({"tent", "south tent"}), BS(
         "It's grey and rather big. Ten people could at least stand up in " +
         "it. There is a lot of noise coming from it.", SL));
   add_item("people", BS(
         "At a closer look you see that some are talking to eachothers and " +
         "others are walking quickly cross this place.", SL));
   
   add_exit(TDIR + "city15", "west", 0);
   add_exit(TDIR + "city17", "east", 0);
   add_exit(TDIR + "city12", "north", 0);
   
   set_alarm(1.0,0.0,"reset_room");
}

reset_tantallon_room()
{
   seteuid(getuid(TO));
   if (!present("woman", TO))
      clone_object(MON + "ne_woman")->move_living("xxx", TO);

    if(!objectp(baaz1))
        {
         baaz1 = clone_object("/d/Krynn/std/baaz");
         baaz1->set_color("red");
         BAAZ_COIN1->move(baaz1);
         BAAZ_COIN2->move(baaz1);
         baaz1->move(TO);
    }

    if(!objectp(baaz2))
        {
         baaz2 = clone_object("/d/Krynn/std/baaz");
         baaz2->set_color("red");
         BAAZ_COIN1->move(baaz2);
         BAAZ_COIN2->move(baaz2);
         baaz2->move(TO);
    }
}
