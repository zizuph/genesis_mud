/* /d/Krynn/common/warfare/recruit_base.c
 *
 * Base of all rooms which allow recruiting of npcs for the warfare system
 *
 * Inherit this file in addition to the standard room base.
 *
 * Copyright by Hans Breckle (Aridor)
 * 03/99
 *
 * Modification history:
 * April 22 - 2000 by Boron - add_fund was private, I changed this so to allow
 *                this room to be inherited into other rooms which pays
 *                to the war indirectly (i.e. by tax)
 * Jun 26, 2001 by Milan - changed recruit command. Players can choose number 
 *		of guards they are recruiting and system decides what guards
 *		are recruited. 
 * June 14, 2004 by Arman - Fixed up the sign and areas/guards command.
 */

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <time.h>

#include "warfare.h"

#define TESTING

string gHouseArmy = "Knights";
static string aob;             /* Army Object */

/* Redefine this function if you want only special people to be able to
 * recruit.
 * Returns: 0 = Not allowed to recruit
 *          1 = Allowed to recruit
 * Default is 0
 */
int
hook_allowed_to_recruit(object who)
{
    if (!who)
      return 1;
    if (who->query_real_name() == "cotillion")
      return 1;
    if (who->query_wiz_level())
      return 0;
    return 0;
}


/*
 * Redefine this function if you want only special people to be able to
 * raise funds.
 * Returns: 0 = Not allowed to raise funds
 *          1 = Allowed to raise funds
 * Default is 1
 */
int
hook_allowed_to_raise_funds(object who)
{
    if (who->query_real_name() == "cotillion")
      return 1;
    if (who->query_wiz_level())
      return 0;
    return 1;
}


int *
minimized_coins(int num)
{
    int *ret = ({ 0, 0, 0, 0 });

    ret[0] = num % 12;
    num = num - ret[0];
    ret[1] = num % 144;
    num = num - ret[1];
    ret[2] = num % 1728;
    ret[3] = num - ret[2];
    ret[1] /= 12;
    ret[2] /= 144;
    ret[3] /= 1728;
    return ret;
}

string
nice_coin_string(int num)
{
    int *mini = minimized_coins(num);

    return sprintf("%d Platinum, %2d Gold, %2d Silver and %2d Copper",
		   mini[3], mini[2], mini[1], mini[0]);
}

string
steel_coin_string(int num)
{
    int *mini = minimized_coins(num);

    return sprintf("%d Steel, %2d Platinum, %2d Gold and %2d Silver",
		   mini[3], mini[2], mini[1], mini[0]);
}

/*
 * Which army does this recruit room belong to?
 */
void
set_army(string str)
{
    gHouseArmy = str;
    aob = ARMYMASTER->query_army(str);
}

/*
 * Add fund interfaces with the army object which keeps track of the funds.
 */
int
add_fund(int sum)
{
    if (sum < 0 && -sum > aob->query_funds())
	return 0;
    
    aob->add_funds(sum);
    
    return 1;
}

string
recruit_text()
{
    return ("\n" +
            "              While the titanic struggle between the forces of Light\n" + 
            "              and Darkness rages on in the battlefields of the War of\n" +
            "              the Lance, you may check the <status> of your armies and\n" +
            "              where they are currently deployed throughout the lands of\n" +
            "              Krynn.\n\n");

            /* Commented out as it is now irrelevant
            "              You may also check the <funds> that have been raised through\n" +
            "              taxing the lands you control for the war effort. These funds\n" +
            "              go directly into the recruitment of your army. The more funds\n" +
            "              in your coffers, the more likely you will attract powerful\n" +
            "              allies to assist you in your efforts. With this command you\n" +
            "              can also see the revenue that is raised each cycle of the\n" +
            "              Krynnish sun for each controlled area.\n\n" +
            "              NOTE: Personal donations cannot be accepted into the war coffers,\n"+
            "              as recruits only accept the most valuable of currency, steel\n" +
            "              coins!\n\n"+ 
	    "recruit guard for <area>            Recruit one or more guards for an area.\n"+
	    "recruit <number> guards for <area>  This is only possible if the area is\n"+
	    "                                    currently under your army's control,\n"+
	    "                                    ie. has been 'conquer'ed first.\n"+
	    "                               NOTE that the spelling for <area> must be\n"+
	    "                                    exactly correct, including uppercase\n"+
	    "                                    letters. Also note that guards which\n"+
	    "                                    have been recruited will be lost\n"+
	    "                                    whenever the time is turned back.\n" +
	    "guards                      Current list of guards and their prices\n" +
	    "areas                       A list of areas which can be used in 'recruit'\n" +
	    "funds                       List the funds collected for recruitment.\n\n");
            */
}

string
note_text()
{
    return "";
}

string
read_recruit_sign()
{
    return (recruit_text() + note_text());
}

string
read_recruit_fund_sign()
{
    return (recruit_text() + note_text());

    /*
    return (recruit_text() +
	    "raise <money>               Raise money for the fund.\n\n" +
	    note_text());
    */
}

string
area_info(string area)
{
    int i, k, count;
    string *units;
    object *a_units;
    mapping desc_units = ([ ]);
    string kob, ret;

    kob = ARMYMASTER->query_area(area);
    if (!kob)
	return "";

    ret = sprintf("%s (held for %s)\n", area, CONVTIME(time() -
	kob->query_conquer_time()));
    
    //units = aob->query_recruitable_units(area, 1);
    kob->clean_up_actual_units();
    a_units = kob->query_actual_units();
    
    i = sizeof(a_units);
/*
    while (i--)
    {
        string s = a_units[i]->short();

        if (!desc_units[s])
        {
            desc_units[s] = 1;
        } else {
            desc_units[s] = desc_units[s] + 1;
        }

    }

    units = m_indexes(desc_units);
    i = sizeof(units);
*/
    ret += "Active units: "+i+"\n";
/*
    while (i--)
    {
        ret += sprintf(" %16s: %d units\n", units[i], desc_units[units[i]]);

    }
  */   



/*
    i = -1;
    k = sizeof(units);

    while (++i < k)
    {

	ret += sprintf("  %16s: %d units (%d in reserve)\n",
	    units[i],
	    kob->query_unit_count(units[i]),
	    kob->query_unit_reserve(units[i]));

        /*  Old version. How much the units cost is no longer relevant to players
	ret += sprintf("  %16s: %s\n" +
	    "                    %d units (%d in reserve)\n",
	    units[i],
	    nice_coin_string(aob->query_recruit_price(units[i], area)),
	    kob->query_unit_count(units[i]),
	    kob->query_unit_reserve(units[i]));
    }
*/    
    ret += "\n";

    if (ARMYMASTER->query_peace())
        ret += "While units may have been deployed, the War of the Lance " +
            "has not yet commenced.\nThe battlefields cannot be conquered " +
            "at this point in time.\n";
    
    return ret;
}

int
area(string str)
{
    int i, k;
    string *areas;

    areas = ARMYMASTER->query_areas_of_army(gHouseArmy);
    
    if (stringp(str))
    {
	if (member_array(str, areas) < 0)
	{
	    notify_fail("There is no such area.\n");
	    return 0;
	}
	
	areas = ({ str });
    }

    k = sizeof(areas);
    if (!k)
    {
	notify_fail("The " + gHouseArmy + " does not control any areas!\n");
	return 0;
    }

    write("The " + gHouseArmy + " are currently controlling " + LANG_WNUM(k) +
	(k > 1 ? " areas" : " area") + ".\n");
/*
    if (aob->query_recruits())
	write("There are " + LANG_WNUM(aob->query_recruits()) + " recruits " + 
	    "that can be drafted for service and trained for battle.\n");
    write("\n");
*/    
    i = -1;
    while (++i < k)
    {
	write(area_info(areas[i]));
    }
    return 1;
}

string
area_tax_info(string area)
{
    string kob, ret;
    int tax;

    kob = ARMYMASTER->query_area(area);
    if (!kob)
	return "";

    tax = ((kob->query_tax_base() * aob->query_tax(area) / 100) * (240 / 100));

    ret = sprintf("                    %s has a daily revenue of:\n" +
                  "                    %s.\n\n", area, steel_coin_string(tax));
    
    return ret;
}

int
funds(string str)
{
    int fund = aob->query_funds();
    int i, k;
    string *areas;

    areas = ARMYMASTER->query_areas_of_army(gHouseArmy);

    write("\nThe war coffers currently contain: " + steel_coin_string(fund) + 
          "\n\n");

    k = sizeof(areas);
    if (!k)
    {
	write("The " + gHouseArmy + " does not control any areas, so " +
          "is raising no revenue through tax!\n\n");
	return 1;
    }

    i = -1;
    while (++i < k)
    {
	write(area_tax_info(areas[i]));
    }


    /*    Changed the funds list so that it displays steel coinage

    write("The funds for recruitment of new guards currently consists of:\n" +
	  "     " + fund + " copper coins\n" +
	  "---------------------------\n" +
	  "This is equal to: " + nice_coin_string(fund) + ".\n");
    */

    return 1;
}


int
raise(string str)
{
    mapping acc;
    int     index;
    int     deposit_flag;
    int     amount = 0;
    string  user;
    string  coin_spec, except_spec;
    mixed   coin_arr, except_coin_arr;

#ifndef TESTING
    if (this_player()->query_wiz_level())
    {
        notify_fail("There is no need for you to raise funds.\n");
        return 0;
    }
#endif

#ifdef TESTING
    if (!this_player()->query_wiz_level())
    {
        notify_fail("It is currently not possible to this.\n");
        return 0;
    }
#endif

    if (!this_object()->hook_allowed_to_raise_funds(this_player()))
    {
	write("You do not have permission to raise funds.\n");
        return 1;
    }

    if (!strlen(str))
    {
        notify_fail("You have to specify an amount of money.\n");
        return 0;
    }

    if (!parse_command(str, ({}), 
        "%s 'except' [for] %s", coin_spec, except_spec))
    {
        coin_spec = str;
        except_coin_arr = allocate(SIZEOF_MONEY_TYPES);
    }
    else
    {
        except_coin_arr = MONEY_PARSE(except_spec);

        if (!pointerp(except_coin_arr))
	{
            notify_fail("Except for what?\n");
            return 0;
	}
    }

    coin_arr = MONEY_PARSE_OB(coin_spec, this_player());

    if (!pointerp(coin_arr))
    {
        notify_fail("Raise what?\n");
        return 0;
    }

    for (index = 0; index < sizeof(coin_arr); index++)
    {
        if (except_coin_arr[index])
	{
            if (except_coin_arr[index] == -1) /* Except all <type> coins */
	    {
                /* We don't want to deposit any coins of this type */
                coin_arr[index] = 0;
	    }
            else /* Except <number> <type> coins */
	    {
                /* We don't want to deposit a specified number of coins of
                 * this type.
                 */
                coin_arr[index] -= except_coin_arr[index];
	    }
	}

        if (coin_arr[index] < 1)
	{
            continue;
	}

        if (MONEY_MOVE(coin_arr[index], MONEY_TYPES[index], this_player(), 0))
        {
            write("You don't have that many " + MONEY_TYPES[index] + 
                " coins.\n");
            continue;
        }

	deposit_flag = 1;
	amount += coin_arr[index]*ftoi(pow(12.0,itof(index)));
	add_fund(amount);
    }

    if (!deposit_flag)
    {
        write("No money raised.\n");
        return 1;
    }
    
    write("You raised " + MONEY_TEXT(coin_arr) + " as funds.\n");
    say(QCTNAME(this_player()) +
        " raises some funds for the recruitment of guards.\n");

    this_player()->reward_warfare_fundraise(amount, gHouseArmy);
    
    return 1;
}

public int
recruit(string str)
{
    int count;
    string area, guard;

#ifdef TESTING
    if (!this_player()->query_wiz_level())
    {
        notify_fail("It is currently not possible to this.\n");
        return 0;
    }
#endif
    
    notify_fail("Recruit 'guard' for 'area'?\n");
    if (!stringp(str) ||
	!parse_command(str, ({ }), "%s 'for' %s", guard, area))
	return 0;

    return aob->recruit_unit(area, guard, 1);
}

void
init_recruit()
{
#ifdef WARFARE_ENABLED
    add_action(area, "status");
    // add_action(funds, "funds");
    // add_action(raise, "raise");
    // add_action(recruit, "recruit");
#endif
}
      
