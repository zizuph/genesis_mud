/*
    goblin_start.c

    This terrainfile manages the hills from within which the link to 
    the Goblin caverns, plus assorted trading posts, etc are. (Or will be)

*/

#pragma save_binary

inherit "/d/Genesis/terrain/hills_lightveg.c";

#include <macros.h>
#include "goblins.h"

int *canyon;
int *canyon_start;
static string climb_dirs;
static string canyon_dirs;
int height;


int in_canyon(int slx, int sly);
int beside_canyon(int slx, int sly);
void describe_floor(int slx, int sly);
void describe_rim(int slx, int sly);

create_mapsquare(int wlx, int wly, int slx, int sly) 
{ 
    string add_desc;

    canyon = ({4, 2, 5, 3, 5, 4, 6, 5, 7, 6, 7, 7, 4, 5, 3, 6, 2, 6 });
    canyon_start = ({3, 2, 3, 3});

    height = random(5)*random(5) + 15;

    ::create_mapsquare(wlx, wly, slx, sly);
    set_exceptions(({ "x.7y.0", "/d/Genesis/start/goblin/caverns/entrance1"}));
    

/*
    set_exceptions(({ "x.7y.7", "/d/Genesis/start/goblin/caverns/entrance1",
        "x.3y.3", "/d/Genesis/start/goblin/wild/trading_post" }));

    if (in_canyon(slx, sly))
        describe_floor(slx, sly);
    else if (beside_canyon(slx, sly))
        describe_rim(slx, sly);
*/
}

int
in_canyon(int slx, int sly)
{
    int i;

    for (i = 0; i <= sizeof(canyon); i += 2)
        if ((slx == canyon[i]) && (sly == canyon[i + 1]))
            return 1;
    return 0;
}

int
beside_canyon(int slx, int sly)
{
    int i;
    int delx, dely;

    for (i = 0; i <= sizeof(canyon); i += 2) {
        delx = slx - canyon[i];
        dely = sly - canyon[i + 1];
        if ((ABS(delx) == 1) && (ABS(dely) == 1))
            return 1;
    }
    return 0;
}

find_dirs( int slx, int sly)
{
    canyon_dirs = "broken";
    climb_dirs = "broken";
}
describe_floor(int slx, int sly)
{
    find_dirs(slx, sly);
    set_long(BSN("You are standing on the floor of a small canyon. " +
        "The walls rise " + height + " meters above you.  You might climb " +
        "the walls to the " + climb_dirs + " or you can continue in the " +
        "canyon to the " + canyon_dirs + "."));
}

describe_rim(int slx, int sly)
{
    find_dirs(slx, sly);
    set_long(BSN("You are standing on the rim of a small canyon. " +
        "The walls drop many meters before you.  You might climb " +
        "down to the " + climb_dirs + "."));

}