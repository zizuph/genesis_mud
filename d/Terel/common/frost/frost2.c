/* -*- C++ -*- */

/*
 * frost2.c
 *
 * Sorgum 951216
 *
 * Modifications:
 *  Lilith Sept 2008
 *   --updated room desc and the guarded check to allow 
 *     smaller players to leave.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include <ss_types.h>

object Giant;

public void
reset_room()
{
    if (!objectp(Giant))
    {
        Giant = clone_object(FROST2_DIR + "npc/frost_giant");
//        Giant->equip_me();
        Giant->move(TO);
    }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short ("Frosty cavern");
    set_long ("You are in a frosty cavern that is the lair of a " +
	      "frost giant.  The walls are glossy smooth ice "+
              "that is almost mirror-like. A ledge has been "+
              "formed of ice and seems to be large enough "+
              "for a giant to sleep on. Other than that, it "+
              "is entirely barren.\n");

    add_item(({"ice", "ledge"}), "It is made of ice, and rather "+
        "scuffed up. It is so high that you can just barely "+
        "see the surface when you stand on tip-toes. There is "+
        "nothing on it, not even a sleeping giant, which "+
        "you would probably let lie, if it came to such a choice.\n");
    
    add_item(({"walls", "mirror"}), "When you look at the walls "+
        "you can see a distorted reflection of yourself, one "+
        "almost as hideous as a frost giant's.\n");

    add_exit(FROST2_DIR+"frost1","out","@@guarded");

    reset_room();
}

int
guarded()
{
    object giant;
    string name;

    giant = present("giant");
    if(giant && giant->query_name()!="corpse")
    {
        // You are big enough that you are not beneath his notice.
        if(TP->query_stat(SS_STR) > 150 + random(50))
        {
            write("The frost giant notices you trying to leave and blocks the way.\n");
	      say("The frost giant blocks " + QTNAME(this_player()) + "'s way.\n");
            giant->command("say You want out? Fight me, you steaming maggot!");
            return 1;
        }
        else
        {
            write("The frost giant dismisses you as being beneath his notice.\n");
            return 0;
        }
    }
    return 0;
}

