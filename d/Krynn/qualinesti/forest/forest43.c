/* forest43.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

int     exit_check();
string  my_desc();
object  animal;

void
reset_qualinesti_room()
{

    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }
    
}

void
create_forest()
{
    add_my_desc("@@my_desc");

    OUTSIDE;

    add_exit(FDIR + "forest39.c", "north", 0, 2);
    add_exit(FDIR + "forest40.c", "northeast", 0, 2);
    add_exit(FDIR + "forest44.c", "east", 0, 2);
    add_exit(FDIR + "qpath1.c", "southwest", "@@exit_check", 2);

    reset_qualinesti_room();
    
}

string 
my_desc()
{
    if ( TP->query_wiz_level()  || TP->test_bit("krynn", 1, 19) )
        return "There seem to be a path leading southwest.\n";
    
    return "\n";
}

int 
exit_check()
{
    if ( TP->query_wiz_level() || TP->test_bit("krynn", 1, 19) )
        return 0;

    write("You force your way through the bushes in " + 
        query_verb() + " direction. However, after some time you " +
        "find your own tracks and you realize you have been walking " +
        "around in circles.\n");
    return 1;
         
}
    
        