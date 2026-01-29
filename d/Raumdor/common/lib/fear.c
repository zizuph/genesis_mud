#include "defs.h"

void
fear(object room, int disLimit = 50, int panic = 50)
{
    int dis;
    int i;
    object *players;

    players = FILTER_PLAYERS(all_inventory(E(TO)));

    for (i=0; i<sizeof(players); i++)
    {
        dis = players[i]->query_stat(SS_DIS);
        players[i]->add_panic(panic);
        if(dis < disLimit 
                || F_PANIC_WIMP_LEVEL(dis) <= players[i]->query_panic())
        {
            players[i]->run_away();
        }
    }
}
