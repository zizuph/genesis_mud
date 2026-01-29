/*
 * Code for the grate under the wall
 * -- Finwe, November 2005
 */

#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

inherit "/d/Gondor/std/room";

int bent_bars_start = 1;
int bars_bent = bent_bars_start;
int min_str = 102;  // ironlike

string check_bars()
{
    if(bars_bent == 0)
    {
        return "The bars are thin and straight.\n";
    }
    else 
    {
        return "The bars are thin and look bent. You can probably wriggle between them.\n";
    }
}

int bend_bars()
{
    if(TP->query_stat(SS_STR) == min_str)
    {
        write("You grunt and groan, and slowly bend the bars.\n");
        bars_bent = 1;
        return 1;
    }
    else
    {
        write("You grunt and groan, but the bars remain in place.\n");
        return 1;
    }
}


reset_room()
{
    ::reset_room();
    bars_bent = bent_bars_start;
}