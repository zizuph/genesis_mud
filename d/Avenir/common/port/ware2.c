// file name:        /d/Avenir/common/port/ware2.c
// creator(s):       Ilyian
// revision history: Boriska
//		     Zielia 2008- added search
// purpose:
// note:
// bug(s):
// to-do:  

#include <tasks.h>
#include <ss_types.h>

#include "port.h"

inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";

#define TENT "/d/Avenir/inherit/tent"

private static int tents;

void
create_room()
{ 
    seteuid(getuid());
 
    set_short("immigrant housing");
    set_long("A rather large room crudely carved from the dark stone of the "+
        "cavern, it resembles a barracks in design, if not in upkeep. Two "+
        "rows of bunks form a center aisle, apparently added some time "+
        "after the sleeping shelves cut into the walls. Bundles, packs, "+
        "and boxes clutter the space, making it feel cramped despite "+
        "the high ceiling. Through the doorway to the north is swirling "+
        "mist and dark, roiling water.\n");
  
    add_item(({ "wall", "walls" }),
	     "These walls are crudely cut. Only the most cursory "+
             "attempt has been made to make them flat. Sleeping "+
             "shelves have been cut into the walls.\n");
    add_item(({"bunks", "bunk", "center aisle", "aisle" }),
            "Bunks are piled three-high in two long rows that form "+
            "an aisle down the middle of the room.\n");
    add_item(({ "shelf", "shelves", "sleeping shelf", "sleeping shelves" }),
	     "The shelves are large enough for a single person to lay "+
             "down in order to sleep.\n");
    add_item(({"bundles", "bundles", "packs", "box", "boxes" }),
            "A sad collection of items belonging to the immigrants "+
            "seeking refuge in Sybarus.  None of it looks of parti"+
            "cular value.\n");
    add_item(({"ceiling", "high ceiling"}), 
            "It is quite high, and cude vaguely domed-shaped, probably "+
            "to try to stabilize the stone overhead so it doesn't crash "+
            "to the floor.\n");

    add_item(({"floor", "stone"}),
            "It is just a rough stone floor,\n");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    set_tell_time(70);
 
    add_tell("A gust of wind whistles past.\n");
    add_tell("The scent of unwashed bodies is unbearably strong.\n");
    add_tell("The wind howls through the doorway, making a " +
	     "ghostly noise, and stirring up some dust.\n"); 
    add_tell("You hear the distant sound of a foghorn.\n");

    IN; LIGHT;
  
    add_exit(PORT+"port6","north");

    add_npc(PORT + "mon/immigrant_g", 3);
    add_npc(PORT + "mon/immigrant_e", 3);
}

void
reset_room()
{
    if (tents && !random(4))
	tents -= 1;
}


/*
 * Function name: do_search
 * Description:   Search results for add_items in the Dark.
 *                Gives general experience 100 each for max of  
 *                5 successful searches per login.
 * Returns:       string for success
 */
public string 
do_search(object player, string str)
{
    object ob;

    str = lower_case(str);
    
    /* What I can find*/    
    if (!parse_command(str, ({}), "'bundles' / 'packs' / 'box' / 'boxes'"))
    {
        return "";
    }    
    
    /* Stuff has already been found here */   
    if (tents > 2)
        return "";    

    /* Do I have the simple awareness to find something
     * and the wisdom to recognize it as being of value?
     */
    if (player->resolve_task(TASK_SIMPLE, ({ TS_WIS, SS_AWARENESS,})) < 0)
        return "";    

    ob = clone_object(TENT);
    ob->move(player, 1);
  
    tents += 1;         
    
    return "You find "+LANG_ASHORT(ob)+".\n";
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}
