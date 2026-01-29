/* camp11.c
 * An elven encampment in the Qualinesti forest.
 * There is an oak with a sharpshooter sitting on it.
 * 
 * Blizzard, 01/2003
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "../local.h"

inherit CAMPBASE;

#define OAK_ROOM  CDIR + "oak2.c"

string            branch_desc();
int               climb(string args);

object            elf1, elf2, elf3;

string
query_sniper_room()
{
    return OAK_ROOM;
}

void
reset_qualinesti_room()
{
    int i = random(10);

  /* There is 50% chance for setting 3 elves and 50% for setting 2 elves. */
    
    if (!elf1)
    {
        elf1 = clone_object(STD + "elf_base");
        elf1->move(TO);
    }
    if (!elf2)
    {
        elf2 = clone_object(STD + "elf_base");
        elf2->move(TO);
    }
    if ( i > 4 )
    {
        if (!elf3)
        {
            elf3 = clone_object(STD + "elf_base");
            elf3->move(TO);
        }
    }

}

public void
create_camp()
{
    add_my_desc("\nYou see a big oak standing here.\n");
	
    add_item(({"oak", "tree", "big tree", "big oak"}),
        "This oak, with a wide and hide stretched branches, looks " +
        "quite old. It makes a nice place for a lookout.\n");
    add_item(({"branches", "foliage" }), &branch_desc());
  
    OUTSIDE;
	
    add_exit(CDIR + "camp4.c", "south", 0, 1);
	
    reset_qualinesti_room();
    
}

/*
 * Function:    query_range_targets
 *
 * Description: Returns information about adjacent rooms
 *              that you can reach with missile weapons
 *              from this room.
 *
 * Arguments:   (object) The person that wishes to fire
 *              into an adjacent room.
 *
 * Returns:     An array with the following content. If
 *              there is more then one room accessible
 *              from this room, each room pads their
 *              values to the array.
 *
 * ({ path to remote room,
 *    matching pattern with parse_command syntax,
 *    description of remote room,
 *    description of this room as seen from remote room
 *  })
 *
 */
                  
mixed
query_range_targets(object archer)
{
   seteuid(getuid(this_object()));
   (OAK_ROOM)->load_me();
   return ({    (OAK_ROOM),
       "[on] [the] 'oak' / 'tree'",
       "in the oak",
       "the camp below" });
}

void
init()
{   
    ::init();
    add_action(climb, "climb");
}

int
climb(string args)
{
    if (args != "up" && args != "oak" && args != "tree")
    {
        notify_fail("Climb oak?\n");                        
        return 0;
    }
           
    write("You climb up the trunk of the oak.\n");
    tell_room(this_object(), QCTNAME(this_player()) +
        " climbs up the trunk of the oak.\n", ({ this_player() }));
    tell_room(OAK_ROOM, QCTNAME(this_player()) + " arrives from below.\n",
        ({ this_player() }));
    this_player()->move_living("M", OAK_ROOM);
    return 1;
}

string
branch_desc()
{
    object *seen;
    
    seen = FILTER_LIVE((OAK_ROOM)->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());
            
    if (sizeof(seen))
    {
        return "The branches stretches far over your head.\n" +
            "You see " + COMPOSITE_LIVE(seen) + " standing on one " +
            "of the solid branches high above you.\n";
    }
    else
    { 
        return "The branches stretches far over your head.\n";
    }
}
                                                                                                                                                        
                       

