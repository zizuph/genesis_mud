/* Western battlement two of the New Vingaard, by Morrigan Dec 96 */

#include <macros.h>
#include "../local.h"

inherit BATTLEMENT;

string
batt_desc()
{
    return "You are at the center of the western wall, on the battlement "+
    "that stretches the entire length. ";
}

public void
create_battlement()
{
    AE(VROOM + "wb3", "north", 0);
    AE(VROOM + "wb1", "south", 0);
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

    tell_room(E(TP), "The draconians float down across the courtyard, landing on "+
      "the balcony of the Inner Keep!\n");
    TP->move(VROOM + "balcony");
    tell_room(E(TP), "A few draconians land here, having floated down from the battlements above!\n");
    team = TP->query_team();
    for (i = 0; i < sizeof(team); i++)
	team[i]->move(VROOM + "balcony");
    return 1;
}

