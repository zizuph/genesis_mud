/* forest5.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include "../local.h"

inherit FORESTBASE;
object animal;

void
reset_qualinesti_room()
{
    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }
    
}

public string
do_climb_tree(string where)
{
    if ( TP->query_skill(SS_CLIMB) < 10 )
    {
        write("It seems to be too difficult for you. You feel much better " +
            "standing firmly on the ground.\n");
        return "";
    }
    
    write("Using the strong branches as a grip, you climb up the big " +
        "vallenwood tree.\n");
    TP->move_living("climbing up the big vallenwood tree", 
        FDIR + "vallenwood_tree", 0, 0);
    
    return "";
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest4.c", "west", 0, 2);
    add_exit(FDIR + "forest6.c", "south", 0, 2);
    add_exit(FDIR + "path4.c", "southwest", 0, 2);

    add_item(({ "big tree", "big vallenwood tree", "vallenwood tree" }),
        "One of the vallenwood trees stretches its thick branches " +
        "high above the stream to the east.\n");
        
    add_cmd_item(({ "big tree", "vallenwood tree", "big vallenwood tree" }),
        "climb", do_climb_tree);
           
    reset_qualinesti_room();

}
