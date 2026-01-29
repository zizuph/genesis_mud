#include "soul.h"

#include <composite.h>
#include <options.h>
#include <ss_types.h>
#include <filter_funs.h>

int
asay(string str)
{
    object *oblist;
    object *dummies = ({});
    int i;

    if (!strlen(str))
    {
	notify_fail("What do you wish to say in the ancient tongue?\n");
	return 0;
    }
    
    oblist = FILTER_PLAYERS(all_inventory(environment(this_player())) -
        ({ this_player() }));
    
    if (this_player()->query_option(OPT_ECHO))
    {
        write("You speak in the tongue of your ancestors: " + str + "\n");
    }

    for (i = 0; i < sizeof(oblist); i++)
    {
	if ((oblist[i]->query_skill(SS_LANGUAGE) > 49) ||
	    (oblist[i]->query_kot_member()))
	{
	    oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) +
                " speaks in an ancient, foreign tongue, but you manage to " +
                "translate.\n" + capitalize(PROTP) + " says: " + str + "\n");
	}
	else
	{
	    oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) +
                " speaks in an ancient, foreign tongue, leaving you " +
                "utterly confused.\n");
	    dummies += ({ oblist[i] });
	}
    }

    if (sizeof(dummies))
    {
	this_player()->catch_tell(COMPOSITE_ALL_LIVE(dummies) + " " +
            ((sizeof(dummies) > 1) ? "give" : "gives") +
            " you a blank look of confusion.\n");
    }

    return 1;
}
