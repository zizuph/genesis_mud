/*
 * /d/Gondor/ithilien/forest/orccamp1.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 *  4-Feb-1997, Olorin:	General revision.
 * 12-Feb-1997, Olorin:	Made firewood into an object.
 * 30-Dec-1997, Gnadnar:	inherit camp.c
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define BLACK_RIDER_ROOM	"/d/Gondor/morgul/blackrider"
#define FIREWOOD_M_GET_NO_TORCH		"_firewood_m_get_no_torch"

private string	exa_fireplace();

static object *Orc = allocate(3),
               Uruk;

public void
create_camp()
{
    set_short("by the campfire in the orc camp in Ithilien");
    set_long("Several tents are set up around a fireplace "
      + "in the centre of the clearing, all looking tattered and torn. "
      + "Some of them have crude paintings of red eyes and molested "
      + "bodies all over them. Further west is a guarding palisade at "
      + "the edge of the clearing. The camp is spread out in all other "
      + "directions.\n");
    add_item( ({"tent", "tents" }), "The tents are tattered and torn, "
      + "and covered with crude paintings and scribblings. The largest "
      + "tent looks a bit more clean. Other kinds of tents reside to "
      + "the east.\n");
    add_item( ({ "fireplace", "campfire", "fire", }), exa_fireplace);
    add_item( ({ "stones", "scorched stones", "blackened stones", 
		 "ring of stones", "ring", }),
	     "The stones have been put on the ground to form " +
		 "a ring. The inside of the stones is blackened " +
		 "from fire.\n");

    add_exit(ITH_DIR + "forest/orccamp2",   "north", 0, 1);
    add_exit(ITH_DIR + "forest/haradcamp2", "east",  check_allow, 1);
    add_exit(ITH_DIR + "forest/orccamp3",   "south", 0, 1);
    add_exit(ITH_DIR + "forest/orcpost2",   "west",  0, 1);

    set_tent_path(ITH_DIR+"forest/orctent1");

    reset_room();

    FIX_EUID
    BLACK_RIDER_ROOM->load_me();
    
    add_orc_camp_tells();
}

public void
reset_room()
{
    object  fire;

    clone_npcs(Orc, NPC_DIR + "reorc", -1.0);
    if (!objectp(Uruk))
	Uruk = clone_npc(Uruk, NPC_DIR + "reuruk");

    if (objectp(fire = present("_firewood")))
	fire->remove_object();
    fire = clone_object(RANGER_DIR + "obj/firewood");
    fire->set_burn_time(3600);
    fire->move(TO);
    Orc[0]->command("emote drops new firewood onto the fireplace.");
    Orc[0]->command("light campfire");
    fire->add_prop(OBJ_M_NO_GET, "You cannot get the @@short:"
		   + file_name(fire) + "@@.\n");
    fire->add_prop(FIREWOOD_M_GET_NO_TORCH, 1);
}


private string
exa_fireplace()
{
    object  fire;

    if (objectp(fire = present("_firewood", TO)))
	return fire->long();

    return "In the middle of the clearing is a fireplace, " +
	       "consisting of a ring of scorched and blackened " +
	       "stones. At present, there is no firewood or fire " +
	       "in the fireplace.";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
