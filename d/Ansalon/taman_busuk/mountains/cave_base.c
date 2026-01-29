/*
 *    The base file for Taman Busuk 
 *
 *    mountains_base.c
 *    ----------------
 *
 *    Coded .........: 98/07/23
 *    By ............: Ashlar
 *
 *    Latest update .: 98/07/23
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *
 *    Changes :
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/mountains/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AR_FILE

#define CREATE "create_cave_room"
#define RESET "reset_cave_room"

string
cave_extra()
{
    string s="";
    
    if (this_player()->query_race() == "dwarf")
    {
        if (this_player()->query_skill(SS_AWARENESS) > 35)
        {
            s = "This is a natural cave, but it seems it has " +
            "at some point been worked by dwarven hands. The " +
            "walls bear traces of some sort of markings.\n";
        }
        else
        {
            s = "This is a natural cave, but it may have been " +
            "worked by dwarves at some point.\n";
        }
    }

    return s;
}

string
wall_extra()
{
    string s;
    
    if (this_player()->query_race() == "dwarf")
    {
        s = "The rough walls are mostly natural, but in places " +
        "you can see the telltale signs of mining.\n";
        
        if (this_player()->query_skill(SS_AWARENESS) > 35)
        {
            s += " There are traces of markings on some of the walls, " +
            "but they are very worn and hard to make out.\n";
        }
    }
    else
    {
        s = "The walls are rough and seem untouched.\n";
    }

    return s;
}

string
markings_extra()
{
    if (this_player()->query_race() == "dwarf")
        if (this_player()->query_skill(SS_AWARENESS) > 35)
            return "The markings are far too worn to be readable, but you " +
            "guess it was once some sort of navigational aid.\n";

    return "You find no markings here.\n";
}

void
add_cave_items()
{
    add_item("cave", "This cave is situated under the Taman Busuk " +
    "mountains. @@cave_extra@@");

    add_item("walls", "@@wall_extra@@");

    add_item("markings", "@@markings_extra@@");
}

void
add_camp_items()
{
    add_item(({"campfire","campfires"}),
    "Large campfires around the cavern provides heat and light.\n");

    add_item(({"bedroll","bedrolls"}),
    "The bedrolls merit no further description.\n");

    add_item("equipment",
    "There is various equipment stacked against the walls, most of it " +
    "in a sorry state indeed.\n");
}


/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}


/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    setuid();
    seteuid(getuid());

    call_other(TO, CREATE);

    reset_room();
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

varargs object
clone_npc(string file, int do_not_arm)
{
    object ob;

    if (!stringp(file) || (file == ""))
        return 0;

    ob = clone_object(file);
    if (!objectp(ob))
        return 0;

    if (!do_not_arm && function_exists("arm_me",ob))
        ob->arm_me();

    ob->move_living("xxx",this_object());

    return ob;
}
