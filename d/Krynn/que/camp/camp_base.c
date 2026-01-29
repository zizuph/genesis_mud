/* Updated June 5th 2006 by Navarre.
 * The Rooms didn't update properly.
 * Their reset function didn't get called.
 * I added a call to reset_camp_room in this file.
 * Everything works fine now.
 */

#include "local.h"
#include CLOCKH
#include <cmdparse.h>
#include <ss_types.h>

/* Inherit the Krynn room */
inherit OR_FILE
inherit CONQUER_BASE


#define CREATE "create_camp_room"
#define RESET  "reset_camp_room"

string gExtra_night_long, gSpecial_short;

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */


void
auto_reset_move_hook(object ob)
{
    ob->set_aggressive(1);
    ob->set_color("red");
    all_inventory(ob)->set_color("red");
}



int
block()
{
    mixed ob = FIND_STR_IN_OBJECT("draconians",TO);
    int i, sum = 0;

    if (ob)
    {
	for(i=0;i<sizeof(ob);i++)
	  if (CAN_SEE_IN_ROOM(ob[i]) && CAN_SEE(ob[i],TP))
	    sum += ob[i]->query_stat(SS_STR);

	
	i = (random(sum) > random(TP->query_stat(SS_DEX)));
	if (i)
	{
	    ob[0]->command("say No chance, buster!");
	    write("You are prevented from going this way!\n");
	}
	return i;
    }

	/* no good. must check every object in ob, not just one... 
	ob = TP->check_seen(ob/*[0]*);
	ob -= ({ 0 });
	if (sizeof(ob))
	{
	    ob[0]->command("say No chance, buster!");
	    ob[0]->command("say Only over my corpse!");
	    return 1;
	}
    
    return 0;*/
}

/*
public varargs int
add_block_exit(string place, string cmd, mixed efunc, mixed tired, mixed non_obvious)
{
    ::add_exit(place, cmd, "@@block@@", tired, non_obvious);
}
*/

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    set_area_name(WAR_AREA_NORTH_ABANASINIA);
    call_other(TO, CREATE);
}

public void
reset_camp_room(){}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    string current_army = ARMYMASTER->army_in_area(TO->query_area_name());

    if (current_army == "Free People" || current_army == "Red Dragonarmy")
      call_other(TO, RESET);
    else
      reset_conquer_room();

    reset_camp_room();	
}


public void
set_night_long(string str)
{
    gExtra_night_long = str;
}

public void
set_special_short(string str)
{
    gSpecial_short = str;
}


public string
long_desc(string long)
{
    string str, desc;

    str = (gSpecial_short ? gSpecial_short : short()) +
      ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
              desc = "The sun is rising above the tents, beginning " +
	             "a new day. " + long;
              break;
	case TOD_DAY:
	      desc = "The sun is standing high above the tents, giving off " +
		     "a pleasant warmth. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking below the horizon, the tents are " +
		     "casting long shadows across the plains. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
		     " and " + C(LUNITARI) + ", is shining onto the tents " +
		     "allowing you to see your surroundings. " +
		       (gExtra_night_long ? gExtra_night_long : long);
	      break;
    }

    str += desc;

    return str;
}

varargs public mixed
long(string str)
{
    string new_long = ::long(str);

    if (!str)
      new_long = long_desc(new_long);

    return new_long;
}

void
init()
{
    ::init();
    init_conquer();
}
