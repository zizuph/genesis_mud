// file name:     barrow15.c
// creator(s):    Lilith, Aug 2021
// last update:   Lilith Sept 2021: added statserv logging and Sair Wall
//                        
// purpose:       Camp for goblins working in the catacombs
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/barrow_base";
inherit "/d/Avenir/inherit/sair_wall";

#include "/d/Avenir/smis/sys/statserv.h"
#include "../dead.h"

object wall;

string
gob_slide()
{
	write("You enter the steep chute and start sliding rapidly "
	    +"into darkness.\n");
    say("Steps into a hole in the ground and slides out of view!");
	TP->move_living("M", BARROW+"sliding");
	STATSERV_LOG_EVENT("crypt", "Entered crypt from chute");
	
}	

void
create_barrow_room()
{
	add_prop("top_of_chute", 1);
    gob_long(gob_desc[random(sizeof(gob_desc))] 
	    +" "+ gob_desc2[random(sizeof(gob_desc2))]
		+" There is a pile of fresh corpses here, "
		+"near the edge of an opening in the floor.");
    add_item(({"pile","pile of corpses","corpses","fresh corpses", "corpse"}),
	    "These are fresh corpses, newly brought to the Isle by "
		+"the ferryman and his helper, and destined for their "
		+"final resting place in the catacombs.\n");
	add_item(({"opening", "opening in the floor", "chute", "hole"}),
	    "It looks like a rather steep chute. You cannot "
		+"see where it ends from here. Perhaps they slide the corpses "
		+"down it?\n");
    add_cmd_item(({"opening", "chute", "hole"}), 
	    ({"slide"}), "@@gob_slide");
	
    gob_exit("14","west");
    add_exit(BARROW+"sliding", "down", 0, 0, 1);
    add_exit(BARROW+"sliding", "climb", 0, 0, 1);
    add_exit(BARROW+"sliding", "chute", 0, 0, 1);
    add_exit(BARROW+"sliding", "jump", 0, 0, 1);
    add_exit(BARROW+"sliding", "enter", 0, 0, 1);	
	
    reset_domain_room();
    
    add_sair_wall();
	set_sair_dest(({HILL+"cairn", CRYPT +"crypt44", 
	        "/d/Avenir/common/bazaar/extr/centr"}));
    add_item(({"granite wall", "wall", "slab" }), 
	    "The wall is a massive slab "
	    +"of granite, much like all the others in this place. "
		+"It looks like there might be a shape of some sort "
		+"chiseled into it.\n");
	add_cmd_item(({"granite wall", "wall", "slab"}), 
	   ({"feel", "touch", "search"}), sair_search);
}

void
reset_domain_room()
{ 	
    set_searched(0);	
	::reset_domain_room();
}

public void
init()
{
    ::init();
    sair_init();  
}
