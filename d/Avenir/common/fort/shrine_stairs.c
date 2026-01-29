// file name:   /d/Avenir/common/outpost/shrine_stairs.c
// creator(s):  Kazz    Feb '95
// last update: Denis, Jul'96: Made the room to inherit /d/Avenir/inherit/room
// purpose:     will lead to a shrine to Sair and Salilus
// note:	
// bug(s):
// to-do:       

#pragma strict_types
#include "/d/Avenir/common/outpost/outpost.h"
inherit OUTPOST +"fort_base";

int do_spin();

void create_fort_room()
{
    set_short("the top of the stairs outside a shrine");
    set_long("From the top of the steps you have a good view of the "+
	    "interior of Fort Sybarus. "+
        "Small groups of dwarves are conducting training exercises "+
        "in the courtyard below. "+
        "A tall black tower alongside the gate rises up to the cavern "+
        "ceiling, its main feature being a large window. "+		
        "A tall building with a large banner bearing a trefoil symbol "+
        "rises to the east. "+
		"Rows of basalt columns that formed naturally as lava cooled "+
        "rise up on either side of the temple entrance. "+		
        "The scent of incense and the sound of humming seems to be "+
        "coming from within. "+
        "\n" );
    add_npc(OUTPOST +"mon/anchorite");

    add_exit("fort5", "down");
    add_exit("shrine", "east", do_spin);

	add_exit_views();
    add_towers_out();
    add_gate_items();
    add_basic_fort();

    add_item(({"window", "tower window" }),
        "The south tower has a window a few floors up. The view "+
        "of the courtyard from up there is probably quite good.\n");
    add_item(({"northeast", "exit", "archway", "natural archway" }),
        "From here, it just looks like a way out of the fort.\n");
    add_item(({"building","east","banner","trefoil","trefoil banner",
        "shrine", "temple", "shrine", "tall building"}),
        "The building is extremely well-lighted. It has a banner "+
        "with a trefoil on it. The doorway for the building has "+
        "octagons and lock-and-key symbols on it."+
        "\n");
    add_item(({"main entrance"}), "The main entrance to the fort is "+
        "blocked by a large gate with a tower on either side of it.\n");
    add_item(({"goblins", "goblin workers", "workers","crates"}), 
	    "Here and there you can see goblin workers hauling crates to "+
        "and fro, keeping the fort and it's defenders well-supplied.\n");
    add_item(({"groups of dwarves","small groups of dwarves", "defenders",
	    "groups", "small groups", "training dwarves", "trainees", "guards"}),
        "Dwarves are training all over the courtyard, practicing "+
        "their military maneouvers in the event of an attack on "+
        "Fort Sybarus.\n");		
    add_item(({"opening", "entrance", "archway", "doorway", "arch", 
	    "spinning"}),
        "The entrance to the temple is a large doorway inscribed with "+
        "octagons and lock and key symbols. Inside the doorway, "+
        "something appears to be spinning.\n");
	add_item(({"columns", "column", "row", "rows of columns", "east wall",
       "basalt columns"}), 
       "Row upon row of hexagonal columns formed naturally by cooling lava "+
       "form a solid, cliff-like wall to the east. A shrine has been built "+
       "into the wall. It has a big trefoil banner above it.\n");
    add_item(({"trefoil", "trefoil banner"}), "The trefoil is the symbol "+
       "of Sybarus, and the banner it is on is visible from both inside and "+
       "outside the fortress.\n");
}

int do_spin()
{
	
    write("You try to go east but the spinning within the doorway "+
        "pushes you backwards.\n");
    return 1;		
}	