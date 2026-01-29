// file name:        /d/Avenir/common/bazaar/admin/baz_adminp.c
// creator(s):       Lilith, Sept 1997
// purpose:          For placing objects on the admin area

#include "admin.h"
#include "/d/Avenir/smis/smis.h"

inherit SMIS_MODULE_PLACER;

void create_placer()
{
    set_module_id("baz_adminp");
    set_module_description("Placer for the bazaar admin center.");
    disable_notifications_autoset();

    set_location_npc(BAZ_ADMIN  + "a1",   BAZAAR + "NPCS/a_punisher");
    set_location_npc(BAZ_ADMIN  + "a3",   BAZAAR + "NPCS/grd");
    set_location_npc(BAZ_ADMIN  + "a5",   BAZAAR + "NPCS/man1");
    set_location_npc(BAZ_ADMIN  + "a8",   BAZAAR + "NPCS/gatekeeper3");
    set_location_npc(BAZ_ADMIN  + "a10",  BAZAAR + "NPCS/wom1");
    set_location_npc(BAZ_ADMIN  + "a19",  BAZAAR + "NPCS/wom1");
    set_location_npc(BAZ_ADMIN  + "a11",  BAZAAR + "NPCS/a_punisher");
    set_location_npcs(BAZ_ADMIN + "fount",  ({ BAZAAR + "NPCS/wom1",
                                          BAZAAR + "NPCS/grd",  
                                          BAZAAR + "NPCS/wom1"}));
    set_location_npcs(BAZ_ADMIN + "a13",  ({ BAZAAR + "NPCS/grd",
                                          BAZAAR + "NPCS/man1",  
                                          BAZAAR + "NPCS/wom1"}));
    set_location_npcs(BAZ_ADMIN + "b1",  ({ BAZAAR + "NPCS/a_punisher",
                                          BAZAAR + "NPCS/prisoner",  
                                          BAZAAR + "NPCS/a_punisher"}));
    set_location_npcs(BAZ_ADMIN + "b2",  ({ BAZAAR + "NPCS/a_punisher",
                                          BAZAAR + "NPCS/prisoner",  
                                          BAZAAR + "NPCS/prisoner"}));
    set_location_npcs(BAZ_ADMIN + "b3",  ({ BAZAAR + "NPCS/a_punisher",
                                          BAZAAR + "NPCS/herk",  
                                          BAZAAR + "NPCS/pab",  
                                          BAZAAR + "NPCS/nill",  
                                          BAZAAR + "NPCS/trimto",  
                                          BAZAAR + "NPCS/inquis_defile"}));
    set_location_npcs(BAZ_ADMIN + "b5",  ({ BAZAAR + "NPCS/a_punisher",
                                          BAZAAR + "NPCS/prisoner",  
                                          BAZAAR + "NPCS/inquisitor"}));
    set_location_npcs(BAZ_ADMIN + "b6",  ({ BAZAAR + "NPCS/a_punisher",
                                          BAZAAR + "NPCS/a_punisher",  
                                          BAZAAR + "NPCS/prisoner"}));
    set_location_npcs(BAZ_ADMIN + "b7",  ({ BAZAAR + "NPCS/inquisitor",
                                          BAZAAR + "NPCS/a_punisher",  
                                          BAZAAR + "NPCS/prisoner"}));
    set_location_npcs(BAZ_ADMIN + "b8",  ({ BAZAAR + "NPCS/grd",
                                          BAZAAR + "NPCS/grd"}));
    set_location_npcs(BAZ_ADMIN + "b9",  ({ BAZAAR + "NPCS/grd",
                                          BAZAAR + "NPCS/grd"}));
    set_location_npcs(BAZ_ADMIN + "t1",  ({ BAZAAR + "NPCS/a_punisher",
                                          BAZAAR + "NPCS/a_punisher",  
                                          BAZAAR + "NPCS/a_punisher",
                                          BAZAAR + "NPCS/prisoner",
                                          BAZAAR + "NPCS/prisoner"}));
    set_location_npcs(BAZ_ADMIN + "t2",  ({ BAZAAR + "NPCS/inquisitor",
                                          BAZAAR + "NPCS/adjudicator",  
                                          BAZAAR + "NPCS/prisoner"}));
    set_location_npcs(BAZ_ADMIN + "t3",  ({ BAZAAR + "NPCS/inquisitor",
                                          BAZAAR + "NPCS/adjudicator",  
                                          BAZAAR + "NPCS/prisoner"}));
    set_location_npcs(BAZ_ADMIN + "t4",  ({ BAZAAR + "NPCS/inquisitor",
                                          BAZAAR + "NPCS/adjudicator",  
                                          BAZAAR + "NPCS/prisoner"}));
/* Bridge to the City, etc */
    set_location_npcs(BAZ_ADMIN + "a18",  ({ CITY + "mon/dahrol",
                                          CITY + "mon/dej-minha1",
                                          BAZAAR + "NPCS/defender_l",  
                                          BAZAAR + "NPCS/defender",
                                          "/d/Avenir/common/mon/phrynos"}));

    
    set_location_commands(BAZ_ADMIN + "fount", 
        ({"drink", MASTER, "do_drink", "sip", MASTER, "do_drink",
          "enter", MASTER, "do_dive", "dive", MASTER, "do_dive",
          "jump", MASTER, "do_dive"}));
}

/*
 *  Commands added via set_location_commands
 *
 * Function name: do_dive
 * Description:   Do we dive into the pool?
 * Returns:       0 - no; 1 - yes.
 */
int
do_dive(string str)
{
    if (!strlen(str))
        return notify_fail("Dive into what?\n");

    if (!parse_command(str, ({ }),
        "[into] [the] 'fountain' / 'pool'"))
        return notify_fail("You can't do that.\n");

    // In they go! Must be a good day to die.
    write("You jump into the fountain.\nThe shockingly cold water "+ 
        "makes you gasp as you come into contact with it.\nYou "+
        "get right back out again.\n");
    say(QCTNAME(this_player()) + " jumps into the fountain, "+
	"then hurriedly gets out again.\n");

    return 1;
}

/*
 * Function name:  do_drink
 * Description:    Do we drink from the water?
 * Returns:        0 - no; 1 - yes.
 */
int
do_drink(string str)
{
    if (!strlen(str))
        return notify_fail("Drink what?\n");
        
    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'fountain' / 'pool'"))
        return notify_fail("You can't do that.\n");

    if (!this_player()->drink_soft(200, 1))
    {
	write("You are sloshing enough as it is, you cannot "+
	    "drink anymore!\n");
	return 1;
    }

    write("You kneel at the fountain's edge and scoop up a handful "+
        "of water, drinking greedily.\n");
    say(QCTNAME(this_player()) + " drinks from the fountain.\n");
    this_player()->drink_soft(200, 0);
    return 1;
} 
