#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include ARND_MEET

#define DEBUG(x)    find_player("ashlar")->catch_msg("RANTEAM: " + x + "\n")

static object *team = ({ });
static int teamsize = 0;
static string table = "";

void
reset_neraka_room()
{
    object t;
    int i,j,dm;
    string this_quarter,file;
    
    team -= ({ 0 });

    if (sizeof(team) == teamsize)
        return;

    while (sizeof(team) < teamsize)
    {
        file = GET_RANDOM_NAME(table);
        this_quarter = this_object()->query_quarter();
        t = this_object()->clone_npc(file, this_quarter);
        if (!t)
        {
            DEBUG("Error in cloning from " + table);
            return;
        }
        team += ({ t });
    }

    for (i=0,j=-1,dm=0; i < teamsize; i++)
    {
        int tmp = team[i]->query_stat(SS_DIS);
        if (tmp > dm)
        {
            dm = tmp;
            j = i;
        }
    }

    for (i=0; i < teamsize; i++)
    {
        if (i != j)
            team[j]->team_join(team[i]);
    }
}

void
set_team_size(int s)
{
    teamsize = s;
}

int
query_team_size()
{
    return teamsize;
}

varargs void
set_random_table(string t, int ismaster)
{
    if (ismaster)
        table = GET_RANDOM_NAME(t);
    else
        table = t;
}

string
query_random_table()
{
    return table;
}
