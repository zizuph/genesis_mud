// file name:   /d/Avenir/common/holm/shore/sh16.c
// creator(s):  Lilith, April 97
// revisions:
// purpose:
// note:        This room clones a seamonster when someone 
//              tries to enter the pool.         
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/shore/shore_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}



/* Now create the room.  */
void create_shore_room()
{
    set_short("Intertidal pool set into the rocks");
    set_long("Huge, craggy rocks embrace an intertidal pool of "+
        "spectacular beauty. Crustose algae and lichen line the "+
        "stones, partially concealing the symbols engraved into "+
        "them. Waves thunder over the rocks, sending water "+
        "and spray into the air. The pool's surface is dark "+
        "and mirror-like, reflecting the diffuse light of the "+
        "Source.\n");
    add_item(({"algae", "lichen"}), "There are several different "+
        "types of algae and lichen growing on the rocks.\n");
    add_item(({"rocks", "rock"}), "These rocks tower above you, "+
        "a palisade against which the waves thunder in timeless "+
        "antagonism. There are symbols engraved into the rocks, "+
        "partially concealed by the profusion of algae and lichen.\n");
    add_item(({"symbols", "symbol", "lines", "wavy lines"}),
        "Most of the symbols carved into the stone are short wavy "+
        "lines. Here and there you can see a strangely fluid rune "+
        "glittering in the stone.\n");
    add_item(({"rune", "runes"}), 
        "The same rune is repeated at odd intervals with the wavy-"+
        "line symbol. The rune is strangely fluid, it seems to "+
        "writhe before your eyes, constantly shifting, yet not.\n");
    add_exit("sh14", "northeast", 0);
    add_exit("sh18", "southeast", 0);
    reset_domain_room();
}

/*
 * Function name: do_dive
 * Description:   Do we dive into the pool?
 * Returns:       0 - no; 1 - yes.
 */
int do_dive(string str)
{
    object tp = this_player();

    if (!str)
        return 0;

    if (str == "water" || str == "in water" || str == "into water" ||
        str == "pool" ||  str == "in pool" || str == "into pool" ||
        str == "intertidal pool" || str == "in intertidal pool" || 
        str == "into intertidal pool")
    {
        tp->catch_msg("You dive into the pool.\n");
        tp->move_living("by diving into the pool", SHORE + "pool", 1, 0);        
        return 1;
    }
    return 0;
}

void init()
{
    ::init();
    add_action(do_dive, "dive");
    add_action(do_dive, "jump");
    add_action(do_dive, "enter");
}
