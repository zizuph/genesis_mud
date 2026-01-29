inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

void
create_ship()
{
   object cap;    
   seteuid(getuid());
   set_cabin(CABIN);
   set_deck(DECK);
   cap = clone_object(CAPTAIN);
   set_captain(cap);
   set_places_to_go(({
            "/d/Ansalon/balifor/flotsam/room/street09",
            ROOM + "sea1",
            ROOM + "sea2",
            ROOM + "sea4",
            ROOM + "sea5",
            /*... to and from Grey Havens ...*/
            SHIRE1,
            SHIRE3,
            GREY_HAVENS,
            SHIRE4,
            SHIRE3,
            SHIRE2,
            SHIRE1,
            /* */
            OPEN_SEA,
            ROOM + "sea1",
}));
   
   set_time_between_stops(({
            23,
            2,
            2,
            2,
            2,
            /*to and from grey havens */
            2,
            2,
            24,
            2,
            2,
            2,
            2,
            /* */
            2,
            2,
            2
}));
   
   set_ticket_id(TICKET_NAME);
   set_name("ship");
   add_name(SHIP_NAME);
   add_adj("grand");
   add_adj("magnificent");
   set_long(break_string("This huge ship sails between Flotsam and " +
             "the Isle of Mithas. It has been designed to sail quickly "+
             "through the waters of the Bloodsea, making it one of the "+
             "fasters ship around. Two tall masts are placed in the "+
             "center of the ship, and the two sails makes the ship "+
             "seem even more great. On the side of the ship, the "+
             "words 'The Gladiator' has been carved.\n",70));
}


board(what)
{
   object ticket, *tmp;
   
   if (!board_enabled)
      return 0;
   if (what && (!sizeof(tmp =
               FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
         this_object() != tmp[0]))
   return 0;
   if (this_player()->query_average_stat() >= 20)
      return ::board(what);
   
   write("You board the ship.\n");
   environment(this_player())->set_dircmd(what);
   this_player()->move_living("boarding the ship", query_deck()[0]);
   return 1;
}

