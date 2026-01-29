 
/*
 * Initial graveyard
 *
 *  Look at the graves to pass beyond added by Napture.
 */

/*
 * Re-described and Re-Vamped by Alaron July 26, 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
#define PLAYER_FOUND_EXIT "_found_lonely_grv"
 
void
reset_room()
{
    object bat;
    int    i;
 
    bat=present("bat");
    if (bat)
        return;
    i = random(5);
    while (i-->0) {
        bat=clone_object( GRAVEYARD_DIR + "npc/bat");
        bat->move_living("into a room", this_object());
    }
}
 
void create_room()
{
    set_short("Dark Graveyard");
    set_long("  You stand in a mirky gray loneliness. All around you "+
	     "there is utter, deathly silence surrounded by the slow-"+
	     "drifting dark fog. The ground is damp and compresses "+
	     "with each step you take, leaving a lonely trail through "+
	     "this dark and eerie graveyard. Large headstones are "+
	     "scattered about the field in seemingly random order, their "+
	     "broken and tattered faces a testament to the abandonment "+
	     "this graveyard has suffered.\n   You can see the steps of "+
	     "a dark, ruined church hiding in the mists to the west "+
	     "while the graveyard sprawls out in hills and dunes "+
	     "in all other directions.\n\n");

    add_exit(GRAVEYARD_DIR + "graveyard4", "north", 0);
    add_exit("@@lonely_exit", "east", "@@desceast");
    add_exit(GRAVEYARD_DIR + "steps", "west",  0);
    add_exit(GRAVEYARD_DIR + "graveyard2", "south", 0);
 
    add_item(({"grave", "graves", "grave stone", "grave stones",
               "east graves"}),
	     "The graves are neglected and ruined. Most of the thick "+
	     "headstones are cracked or broken, and all of them are "+
	     "covered in thick moss and riddled with moisture erosion "+
	     "stains. They are everywhere, scattered in random patterns. "+
	     "It looks like it could take forever to search the graves "+
	     "for a name that looked familiar. Half of the names on the "+
	     "headstones have already eroded away.\n");
 
    add_item( ({"fog", "mist"}),
            "It is a dark and eerie fog. It seems to hang over the area "+
            "like a blanket, stifling the life of the place.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_graves");
 
    reset_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob))
        if (from)
            if (from->query_short() == "Church south of the ocean inlet")
                write("\nYou find yourself feeling lost in the mist and "+
		      "fog which looms heavily over the graveyard.\n");
            else if (from->query_short() == "Lonely Graveyard")
		write("\nYou step back into the main section of "+
		      "the graveyard, feeling the sense of loneliness "+
		      "and despair begin to overtake you.\n");
            else if (from->query_short() == "Dark Graveyard")
		write("\nFeeling dazed and lost in the mists of the "+
		      "graveyard you wander about through the graves "+
		      "but don't manage to find a clear enough path "+
		      "and end up right back where you started.\n");
		

}

string
search_graves(object player, string str)
{
    if (str!="grave" && str!="grave stone" && str!="grave stones" &&
        str!="graves" && str!="for grave" && str!="east graves")
            return 0;
    if (TP->query_prop(PLAYER_FOUND_EXIT))  {
        return "You only find what you found before.\n";
    }
    TP->add_prop(PLAYER_FOUND_EXIT, 1);
    
    return "After searching through the graves intently, you now notice "+
	"a new, clearer path to the east.\n";
}
 
lonely_exit()
{
    if (TP->query_prop(PLAYER_FOUND_EXIT))
        return GRAVEYARD_DIR + "graveyard";
    return GRAVEYARD_DIR + "graveyard1";
}
 
 


int
desceast()
{
    if (!TP->query_prop(PLAYER_FOUND_EXIT))
       write("You manage to get lost in the mist, unable to find a "+
             "clear path through the graves, so you end up where you "+
             "started.\n");
    return 0;
}
