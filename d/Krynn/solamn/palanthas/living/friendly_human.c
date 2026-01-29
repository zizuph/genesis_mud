/*
 * Mortis 02.2006
 *
 * Calls chief constable in the palace to arrest
 * players who attack npcs in the city.
 *
 */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include "../local.h"

inherit M_FILE

object guardhome = find_object(CITY_GUARD);

void
create_krynn_monster()
{
}

void
attacked_by(object who)
{
	switch (random(5))
	{
		case 0:
			command("shout Alarm!  ALARM!  Call the constable!");
			break;
		case 1:
			command("shout Help!  Hagen, help!  Anyone!");
			break;
		case 2:
			command("shout Call the constable!  Murderer on the loose!");
			break;
		case 3:
			command("shout MURDER!  I am being murdered!  Please help!");
			break;
		default:
			command("shout HELP! Help ME! I am being attacked!");
			break;
	}

	guardhome->help_i_need_help(who, E(TO));

	::attacked_by(who);
}
