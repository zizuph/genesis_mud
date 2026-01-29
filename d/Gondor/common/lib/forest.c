/* Forest.h  - A file to include when you want a players tracking or
 * location sense skills to be tested before moving a direction.
 * Remember to set the forest_density - if the skill is higher than this
 * number, the move is a success. To call the skill-test functions, do
 * @@test_track  or @@test_loc from the add_exit.   Elessar, April '92.
 */
#pragma strict_types

#include <macros.h>
#include <ss_types.h>

static int     Forest_Density;

public int
test_track()
{
    if (!objectp(this_player()) || 
        (this_player()->query_skill(SS_TRACKING) >= random(Forest_Density)) )
    {
        write("You succeed in following the path.\n");
        return 0;
    }
    else 
    {
        write("You quickly lose track of the path, and return to where you were.\n");
        say(QCTNAME(this_player())+" lost track of the path, and returned here.\n",this_player());
        return 1;
    }
}

public int
test_loc()
{
    if (!objectp(this_player()) || 
        (this_player()->query_skill(SS_LOC_SENSE) >= random(Forest_Density)))
        return 0;
    else 
    {
        write("You feel disoriented as to what is the correct direction, so " 
            + "you stop in fear of getting lost.\n");
        say(QCTNAME(this_player())+" can't decide which direction to go.\n");
        return 1;
    }
}

public int
set_forest_density(int i)
{
    Forest_Density = i;
}


