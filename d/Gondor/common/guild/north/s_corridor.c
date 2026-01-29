/*
 *	/d/Gondor/common/guild/north/c_corridor.c
 *
 *	The company office of the Rangers of the North.
 *
 *	Modification log:
 *	19-Feb-1997, Olorin:	Changed includes to inherits.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "lib/ranger_defs.h"
#include "northern_hq.h"

public void
create_gondor()
{
    object door;

    set_short("the southern corridor");
    set_long(BS("You're in the southern corridor. On the north wall you see "+
        "a wonderful tapestry. In sconces at regular intervals are torches. "+
        "To the east is an arched opening, to the south a door, and to the west " +
        "the shop.\n"));

    add_item("tapestry",BS("On the tapestry is a hero from the First Age. "+
        "You see Earendil the sea-farer, sailing his ship Vingilot, standing "+
        "at the prow of his ship. On his brow is a shining jewel, one of the "+
        "three Silmarils, and he gazes towards the horizon.\n"));
    add_item("opening","The opening leads into the great hall.\n");
    TORCHES;
    SCONCES;
    WALLS;

    add_exit(RANGER_NORTH_DIR+"shop","west",0);
    add_exit(RANGER_NORTH_DIR+"great_hall","east",0);

    clone_object(RANGER_NORTH_DIR+"obj/c_door_in")->move(TO);
}

public int 
get_new_key(string str)
{
    if (!strlen(str) || ((str != "office") && (str != "office key")) )
	return 0;
    if (!NORTH_MASTER->is_officer(TP->query_real_name()) && !TP->query_wiz_level()) 
	return 0;
    if(present("_Office_Key",TP))
    {
	NF("You already have an office key!\n");
	return 0;
    }
    FIX_EUID;
    clone_object(RANGER_NORTH_DIR + "obj/officekey")->move(TP);
    write("You get a key to the council-room.\n");
    return 1;
}

    
public void 
init()
{
    ::init();

    add_action(get_new_key, "get_key");
    add_action(get_new_key, "get");
}