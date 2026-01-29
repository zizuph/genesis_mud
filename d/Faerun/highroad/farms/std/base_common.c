/*
 * Base common file for Farms
 * Finwe, November 2005
 *
 *Updated typo "and" when finding 
 *an egg
 *--Clyptas, July 2018
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

int iEggFound = 0;
int iMaxEggs = 6;

/*
 * search routine to find eggs in the farm
 */
mixed do_search(object searcher, string str)
{
    int awareness;
    object egg;
 
    setuid(); 
    seteuid(getuid());

//    if (iEggFound >= MAX_EGGS_NEST)
    if (iEggFound >= iMaxEggs)
        return 0;

    if (!strlen(str))
        return 0; 

    if (!parse_command(str, ({}),
       "'nests' / 'nest' / 'here' [for] [chicken] [egg] [eggs]"))
//    "[nests] [nest] [for] [chicken] [egg] [eggs]"))
        return 0;
 
    awareness = searcher->query_skill(SS_AWARENESS);
    if ((awareness + random(10)) > 15)
    {
        egg = clone_object(FOBJ_DIR + "egg");
        iEggFound += 1;
        say(QCTNAME(searcher) + " finds an egg.\n", searcher);
        if (egg->move(searcher))
        {
            if (egg->move(TO))
                egg->move(TO, 1);
        }

        return "You find an egg and quickly snatch it from a nest!\n";
    }

    return 0;
}

