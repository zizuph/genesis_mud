/*
 *  coded by Amelia 10/97
 *  rope bridge over chasm
 *  
*/

inherit "/d/Earthsea/std/room";

#pragma no_clone
#pragma strict_types

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/sys/properties.h"
#include "defs.h"
inherit ROOM_TELL;



void
create_earthsea_room()
{

    set_short("A hanging bridge");


    set_long(break_string("A white mist swirls "+
	"all around you, making it impossible to "+
	"see more than a few feet in any direction. "+
	"As you look beneath your feet through "+
	"the thin strands of rope, you feel a dizzying sense of vertigo "+
	"and sense that it is a very long way down into the abyss. "+ 
	"Moisture condenses on the rope, making it slippery. "+
	"Far below you hear the roar of a maelstrom.\n", 70));
    add_item((({"bridge", "rope bridge"})),
      "The bridge looks rather insubstantial and appears to have been "+
      "hurriedly constructed.\n");
    add_item((({"rift","abyss", "deep rift"})),
      "You cannot see all the way down due to the fog, however, you "+
      "can hear the rush of water in a maelstrom far below.\n");
    add_item((({"mist", "swirling mist"})),
      "Clouds of mist envelop the bridge, making it difficult to see "+
      "what lies ahead.\n");
    add_item((({"cliff edge", "edge"})),
      "You are tempted to go back to the cliff edge, just so as to "+
      "have solid earth beneath your feet.\n");
    add_item((({"rope", "ropes"})),
      "The rope appears quite thin but is surprisingly strong and "+
      "flexible.\n");
    add_item("maelstrom", "Although you cannot see the maelstrom, "+
      "you hear the loud rush of swirling waters far below.\n");


    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);



    set_tell_time(120);
    add_tell("The bridge sways perilously under your feet.\n");
    add_tell("Clouds of white mist swirl around you, obscuring your "+
      "view.\n");
    add_tell("The roaring maelstrom far below makes a roaring sound.\n");
    add_tell("Your foot slips on the damp rope, you almost fall!\n");
    add_exit(BRIDGE + "bridge1", "south", 0, 2, 0);
    add_exit(BRIDGE + "bridge3", "north", 0, 2, 0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
	start_room_tells();
	ob->catch_msg("As you step forward, the bridge sways "+
	  "dangerously under your feet.\n");
    }
}
