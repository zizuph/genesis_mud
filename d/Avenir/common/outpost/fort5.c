// file name:   /d/Avenir/common/outpost/fort5.c
// creator(s):  Kazz    Feb '95
// last update: Denis, Jul'96: Made the room to inherit /d/Avenir/inherit/room
// purpose:     middle of the fort
// note:	
// bug(s):
// to-do:       

#pragma strict_types
#include "/d/Avenir/common/outpost/outpost.h"
inherit OUTPOST +"fort_base";

int
not_yet()
{
    write("A very large boulder blocks your way.\n");
	say(QCTNAME(this_player()) +" tries to go southeast and nearly "+
        "runs into a very large boulder.\n");
    return 1;
}
	
void create_fort_room()
{
    set_short("the east courtyard");
    set_long("This is the eastern half of the central courtyard of Fort "+
        "Sybarus, and it seems quite busy. "+
        "Small groups of dwarves are conducting training exercises "+
        "accompanied by colourful language and grumbling. "+		
        "Goblin workers can be seen ferrying supplies to the warehouse "+
        "built into the southwest wall of the cavern. "+
        "A tall building with a large banner bearing a trefoil symbol "+
        "rises to the east, and opposite it, across the expanse of the "+
        "courtyard, lies the main entrance to the fort. "+
        "A tall black tower alongside the gate rises up to the cavern "+
        "ceiling, its main feature being a large window. "+
        "To the northeast you can see a large natural archway in the "+
        "cavern wall.\n" );

    add_exit("fort4", "north"); // dining hall
    add_exit("fort7", "northeast"); // To the sea of Sybarus
    //add_exit("fort6", "southwest",0,0,1); // warehouse
    //add_exit("fort1", "northwest", 0,0,1);  // common room
    add_exit("fort3", "west"); // west courtyard
    add_exit("secret/tunnel1", "southeast", not_yet); // toward seaside someday
    add_exit("forge_entry",  "south");  // To the forge complex
    add_exit("shrine_stairs", "up", 0, 0, 1);
	add_exit("shrine_stairs", "east");
	
    add_exit_views();
    add_towers_out();
    add_gate_items();
    add_basic_fort();

    add_npc(MON + "dw_guard", 4);
	
    set_tell_time(30);
    add_tell("A squad of dwarven guards runs past you.\n");
    add_tell("A scent like incense wafts by from somewhere.\n");
    add_tell("A goblin worker arrives from the south.\n");
    add_tell("A goblin worker arrives from the east.\n");
    add_tell("A goblin worker leaves north.");
    add_tell("The sound of metal banging on metal comes from "+
        "the south.\n");
    add_tell("The sound of surf rushing the shoreline comes "+
        "from the northeast.\n");
    add_tell("Sounds of merriment and the scent of food seem "+
        "to come from the north.\n");
    add_tell("A dwarven voice shouts: Come on you lazy sons of "+
        "goats! Move it!");

    add_item(({"window", "tower window" }),
        "The south tower has a window a few floors up. The view "+
        "of the courtyard from up there is probably quite good.\n");
    add_item(({"northeast", "exit", "archway", "natural archway" }),
        "From here, it just looks like a way out of the fort.\n");
    add_item(({"building","east","banner","trefoil","trefoil banner",
        "shrine", "temple", "tall building"}),
        "The building is extremely well-lighted. It has a banner "+
        "with a trefoil on it. The only way to learn more is to "+
        "go inside.\n");
    add_item(({"main entrance"}), "The main entrance to the fort is "+
        "blocked by a large gate with a tower on either side of it.\n");
    add_item(({"goblins", "goblin workers", "workers","crates"}), 
        "Here and there you can see goblin workers hauling crates to "+
        "and fro, keeping the fort and it's defenders well-supplied.\n");
    add_item(({"groups of dwarves","small groups of dwarves", 
        "groups", "small groups", "training dwarves", "trainees"}),
        "Dwarves are training all over the courtyard, practicing "+
        "their military maneouvers in the event of an attack on "+
        "Fort Sybarus.\n");		
    add_item("boulder", "It is a very large boulder. It appears to "+
        "have been rolled into place.\n");
    add_cmd_item(({"boulder"}), ({"move", "lift", "push", "roll"}),
        "It doesn't seem to want to budge.\n");
    add_item(({"sea", "dark sea"}), "You can just catch a glimpse of "+
        "the sea to the northeast.\n");
}
