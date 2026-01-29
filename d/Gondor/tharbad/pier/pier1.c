/*
 * /d/Gondor/tharbad/pier/pier1.c
 *
 * Modification log:
 * 20-Jan-97, Olorin: ROOM_I_NO_CLEANUP
 * 12-Jun-2006, Tapakah - Temporary disable until line transfers to GH
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room";

#include "/d/Gondor/common/lib/gs_include.c"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HARD_TO_CLIMB    8

inherit "/d/Genesis/gsl_ships/lib/pier";

public void    reset_room();

static object  Ship,
               Sign;

public void    climb();

public void
create_room()
{
   set_short("a ruined pier in Tharbad, in the south of Eriador");
   set_long(BSN("You are on what used to be a pier on the River Gwathlo. "+
         "Other than the water, you see little sign that ships land here. "+
         "It is rumored, though that a ship from elven city of Grey Havens comes here "+
        "from time to time. To the north, you see fords and the ruins of Tharbad, " +
        "and to the southwest, the riverbank extends towards the sea."));
   add_prop(ROOM_I_NO_CLEANUP,1);
   add_exit(THARBAD_DIR + "ford/f01",   "northeast", climb, 2);
   add_exit(THARBAD_DIR + "pier/pier2", "southwest", 0, 2);
   add_item(({"pier","piers","water","river"}), BSN(
         "The pier you are standing on seems in satisfactory condition, especially "+
         "compared to the other around. The river water is clear and blue and "
         +"flows southwest towards the sea."));
   add_pier_entry(MASTER_OB(TO), "Tharbad", "Cabotage to Grey Havens");
   initialize_pier();
   reset_room();
}

public void
reset_room()
{
	::reset_room();
	return;
   if (!objectp(Ship))
   {
      Ship = clone_object(SHIP_DIR + "ship4");
      Ship->start_ship();
   }
   if (!objectp(Sign))
   {
       Sign = clone_object(SHIP_DIR + "vingaard_sign");
       Sign->move(TO);
   }
}

public int
climb()
{
    object tp = TP;
    int    climb_try = (HARD_TO_CLIMB / 2 + random(HARD_TO_CLIMB) + 1),
           skill = tp->query_skill(SS_CLIMB);

    if (skill < climb_try)
    {
        tp->reduce_hit_point(climb_try - skill);
        write("As you try to climb over the ruins, you stumble and momentarily lose your footing.\n");
        say(QCTNAME(tp) + " stumbles.\n");
        return 1;
    }

    write("You climb over the rubble.\n");
    return 0;
}
