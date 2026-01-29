/* Ashlar, 30 Sep 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include "../guild/guild.h"
#include DL_CLOCK

inherit TEMPLE_BASE;

object servant;

void
servant_greet_member(object p)
{
    string str,str2;

    switch(GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str = "Greetings upon this late hour";
        break;
        case EARLY_MORNING:
        case MORNING:
            str = "Good morrow";
        break;
        case NOON:
            str = "Good day";
        break;
        case AFTERNOON:
            str = "Good afternoon";
        break;
        case EVENING:
            str = "Good evening";
        break;
    }

    switch(p->query_priest_level())
    {
    	case 0:
    	    str2 = "sir";
    	    if (p->query_gender() == G_FEMALE)
    	        str2 = "madam";
    	    break;
    	case 1:
    	    str2 = "revered priest";
    	    if (p->query_gender() == G_FEMALE)
    	        str2 += "ess";
	    break;
	case 2:
	    str2 = "my gracious ";
	    if (p->query_gender() == G_FEMALE)
	        str2 += "lady";
            else
                str2 += "lord";
            break;
    }
    
    if (objectp(p) && (E(p) == E(servant)))
    {
    	servant->command("bow deeply " + OB_NAME(p));
    	servant->command("say " + str + ", " + str2 + ".");
    }
}

void
reset_neraka_room()
{
    if (!objectp(servant))
    	servant = clone_npc(NNPC + "servant");
}

string
long_descr()
{
    return "This is a circular chamber in the lower level of the " +
    "temple. This is where the Priests of Takhisis come to rest. " +
    "As a member of the guild, you can <start here> if you want to.\n";
}

void
create_neraka_room()
{
    set_short("circular resting chamber");
    set_long("@@long_descr");

    add_temple_items();
    add_item("chamber","@@long_descr");

    reset_room();

    add_exit(NTEMPLE + "d1", "east");
    add_exit(NTEMPLE + "store", "northeast");
    add_exit(NTEMPLE + "prefs", "south");
}

int
start(string str)
{
    if (str != "here") 
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You are not a Priest of Takhisis, and cannot start here.\n");
        return 1;
    }

    if (this_player()->set_default_start_location(GUILD_START))
    {
        write("You will now start here.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
}
