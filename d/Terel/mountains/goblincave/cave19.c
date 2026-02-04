/*
 * cave19.c
 *
 * lower level of the goblin cave
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";

#include <ss_types.h>
#include <stdproperties.h>

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "The room appears to be cleaner than the rooms above.\n");
    
    DARK;
    
    add_exit(MOUNTAIN_DIR + "goblincave/cave18", "west");
    add_exit(MOUNTAIN_DIR + "goblincave/cave22", "east", "@@guarded");
    add_exit(MOUNTAIN_DIR + "goblincave/cave20", "north");
    add_exit(MOUNTAIN_DIR + "goblincave/cave21", "south");
    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin_grd", 2);
}

int
guarded()
{
    if (TP->query_prop(OBJ_I_INVIS))
        return 0;

    object warrior = present("_terel_cave_goblin");
    if (!objectp(warrior))
        return 0;

    if ((TP->query_stat(SS_INT) + TP->query_stat(SS_WIS) -
            random(50)) > (warrior->query_stat(SS_STR) +
            warrior->query_stat(SS_DEX) + random(100)))
    {
        return 0;
    }

    write(warrior->query_The_name(TP) +" lowers "+
        warrior->query_possessive() +" weapon and blocks you "+
        "from continuing east.\n");
    say(QCTNAME(warrior) +" blocks " + QTNAME(TP) +" from heading east.\n");
    return 1;
}
