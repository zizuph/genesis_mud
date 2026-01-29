inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

public int no_command();

void
create_object()
{
    seteuid(getuid());
    set_name("dust");
    add_name("faery_dust");
    set_short("faery dust");
    set_long("Faery dust that comes from various faery creatures. " +
      "It often causes confusion to non-elfin creatures it " +
      "comes in contact with.\n");

    set_no_show();

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
}

init()
{
    ::init();
}

public int
do_confused(string str)
{
    string verb;
    string *not_allowed;

    not_allowed = ({"north","n","east","e","west","w",
      "south","s","southeast","se","northwest","nw",
      "northeast","ne","southwest","sw"});

    verb = query_verb();
    if(member_array(verb, not_allowed) == -1)
	return 0;
    else
	return no_command();

    return 1;
}



void
no_command()
{
    string str;
    object player = TP;


    switch(random(15))
    {
    case 0:
	str = "west";
	break;
    case 1:
	str = "north";
	break;
    case 2:
	str = "east";
	break;
    case 3:
	str = "south";
	break;
    case 4:
	str = "giggle";
	break;
    case 5:
	str = "laugh maniac";
	break;
    case 6:
	str = "eeks";
	break;
    case 7:
	str = "kill thing";
	break;
    case 8:
	str = "shout Run away!";
	break;
    case 9:
	str = "leave";
	break;
    case 10:
	str = "options wimpy brave";
	break;
    case 11:
	str = "drop all";
	break;
    case 12:
	str = "scream";
	break;
    case 13:
	str = "cower";
	break;
    }

    player->command(str);
    return;
}

void
remove_dragon_effect()
{
    write("Your heads clears, and you no longer " +
      "feel quite so confused.\n");
    remove_object();
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if(TP->query_prop(LIVE_I_UNDEAD) > 0)
    {
	write("Being undead, you are unaffected by the confusion spell.\n");
	return;
    }

    set_alarm(500.0, 0.0, "remove_dragon_effect");
    set_alarm(20.0, 10.0, "no_command");
}
