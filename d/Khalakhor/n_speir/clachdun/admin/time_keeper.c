#include "/d/Khalakhor/sys/time.h"
#include <language.h>

int
filter_players(object player)
{
    if (!environment(player)->query_in_clachdun())
	return 0;

    if (environment(player)->query_in_clachdun_sewers())
	return 0;

    return 1;
}

void
ring_bell(int hour)
{
    int *coords, i;
    object *players;

    players = filter(users(), filter_players);
    if (!sizeof(players))
	return;

    hour = (hour % 12 == 0 ? 12 : hour % 12);

    i = -1;
    while(++i < sizeof(players))
    {
	coords = environment(players[i])->query_local_coords();

	if (coords[0] >= 5 && coords[0] <= 11 &&
	  coords[1] >= 10 && coords[1] <= 16)
	{
	    players[i]->catch_tell("You hear the bell tower ring out "+
	      LANG_WNUM(hour)+" "+ (hour == 1 ? "time" : "times")+ ".\n");
	}
	else if (coords[0] >= 2 && coords[0] <= 14 &&
	  coords[1] >= 7 && coords[1] <= 19)
	{
	    players[i]->catch_tell("You hear a bell toll "+LANG_WNUM(hour)+
	      " " + (hour == 1 ? "time" : "times") + " in the distance.\n");
	}
	else
	{
	    players[i]->catch_tell("You faintly hear a bell toll "+
	      LANG_WNUM(hour) + " "+ (hour == 1 ? "time" : "times") +
	      " in the distance.\n");
	}
    }
}

void
change_hour(int hour)
{
    ring_bell(hour);
}

