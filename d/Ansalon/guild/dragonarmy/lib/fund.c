/* Code for fund commands */
#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../guild.h"
#include <macros.h>

int
fundrising(string str)
{
    int fund, day;

    if (str != "status" && str != "report")
    {
	NF("Fundrising what? Status or report?\n");
	return 0;
    }

    day = TP->query_age();
    day /= 30; // minutes
    day /= 60; // hours
    day /= 24; // days
    fund = TP->query_skill(SS_DRAGONARMY_FUND);
    day = fund / day;

    if (str == "status")
    {
	TP->catch_tell("You have collected "+fund+" platinum coins in total which is ");
	if (day == 0)
	    TP->catch_tell("less than your days here.\n");
	else
	    TP->catch_tell("about "+day+" per day.\n");
    }
    else
    {
	TP->catch_tell("You report: I have collected "+fund+
	    " platinum coins in total which is ");
	tell_room(E(TP), QCTNAME(TP)+" reports: I have collected "+fund+
	    " platinum coins in total which is ", TP);
	if (day == 0)
	    tell_room(E(TP), "less than my days here.\n");
	else
	    tell_room(E(TP), "about "+day+" per day.\n");
    }

    return 1;
}
