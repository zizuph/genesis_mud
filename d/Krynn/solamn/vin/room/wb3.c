/* Western battlement three of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"
#include <macros.h>

inherit BATTLEMENT;

string
batt_desc()
{
    return "You are on the western battlement of the Keep, far to the south "+
    "lies the southwest tower. Strangely, there is no northwestern "+
    "tower. ";
}

public void
create_battlement()
{
    AE(VROOM + "nwtowerup", "north", 0);
    AE(VROOM + "wb2", "south", 0);
}

void init()
{
    add_action("do_float", "float");
    ::init();
}

int do_float()
{
    object *team;
    int i;
    if (TP->query_race_name() != "draconian")
	return 0;
    team = TP->query_team();

    tell_room(E(TP), "The draconians float down into the inner courtyard of the Keep!\n");
    TP->move(VROOM + "inner_court");
    tell_room(E(TP), "A few draconians land here, having floated "+
      "down from the battlements!\n");

    for (i = 0; i < sizeof(team); i++)
	team[i]->move(VROOM + "inner_court");
    return 1;
}

