/*
 * cave06.c
 *
 * A cave room.  The stones have no real meaning for now.
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 *
 * Lilith - Jan 2022: Added an exit to/from the avalanche at old vamp villa,
 *              which is near the moors. This is a closer location than the 
 *              previous location, which was the mountain near the underdark.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";
#include "/sys/ss_types.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "A cold wind blows from a gap in the wall high up near the "+
		"ceiling. A pile of small stones has been left in the corner.\n");

    DARK;

    add_item(({"pile", "stones"}),
        "The stones form an arrow pointing north.\n");
    add_item(({"wind"}),
      "A wind howls in from the shadows and through the tunnel, pushing "
      +"you north, toward the entrance.\n");
    add_item(({"gap", "ceiling", "wall"}), "There is a gap in the wall "
      +"near the ceiling. A strong wind blows from it, howling like a "
      +"wolf.\n");	  

    add_exit(MOUNTAIN_DIR + "goblincave/cave05", "north");
    add_exit(MOUNTAIN_DIR + "goblincave/cave07", "east");
}


int do_up(string str)
{
    notify_fail("What?\n");
    
    if (!strlen(str))
    {
        return 0;
    }

    if (parse_command(str,({})," [up] [through] [the] 'gap' / 'opening' [in] "+
      "[the] [wall] / [ceiling]"))
    {
        if (TP->query_skill(SS_CLIMB) > 25)
        {
            write("You heave yourself up through the gap in the wall.\n\n");
            TP->move_living("up through a gap in the wall", 
			"/d/Terel/guilds/vamp/room/avalanche5");
            return 1;
        }
			
        write("You try climbing through the gap in the wall you don't have the "+
            "skills.\n\n");
        say(QCTNAME(TP) +" tries to climb through the gap in the wall, but can't.\n");
        return 1;
    }
    
    return 0;
}

public void init()
{
    ::init();
    
    add_action(do_up, "enter");
    add_action(do_up, "climb");
}