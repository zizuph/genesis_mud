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
 */

#include "local.h"
#include <composite.h>
#include <language.h>
#include <money.h>

#define  SAVE_FILE    ("/d/Krynn/common/warfare/recruit/" + implode(explode(gHouseArmy," "),""))
#define  TESTING      1

string gHouseArmy = "Knights";
int    gFund = 0;
int    gAutomaticRecruit = 0;

/*prototypes*/
void do_automatic_recruit();
void restore_gFund();

/* Redefine this function if you want only special people to be able to recruit.
 * Returns: 0 = Not allowed to recruit
 *          1 = Allowed to recruit
 * Default is 0
 */
int
hook_allowed_to_recruit(object who)
{
    if (!who)
      return 1;
    if (who->query_name() == "Milan")
      return 1;
    if (who->query_wiz_level())
      return 0;
    return 0;
}


/* Redefine this function if you want only special people to be able to raise funds.
 * Returns: 0 = Not allowed to raise funds
 *          1 = Allowed to raise funds
 * Default is 1
 */
int
hook_allowed_to_raise_funds(object who)
{
    if (who->query_name() == "Milan")
      return 1;
    if (who->query_wiz_level())
      return 0;
    return 1;
}


int *
minimized_coins(int num)
{
    int *ret = ({0,0,0,0});

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

    return sprintf("%2d Platinum, %2d Gold, %2d Silver and %2d Copper",
		   mini[3], mini[2], mini[1], mini[0]);
}



void
set_army(string str)
{
    gHouseArmy = str;
}

static void
set_automatic_recruit()
{
    if (gHouseArmy == "Free People")
      gAutomaticRecruit = 1;
}

int
query_automatic_recruit()
{
    return gAutomaticRecruit;
}

int
query_funds()
{
    restore_gFund();
    return gFund;
}

/* We need the following strange looking setup so that objects in other
 * domains are able to write the funds-file after funds have been added.
 */
public nomask void
my_save_gFund(string army, int value)
{
    setuid();
    seteuid(getuid());
    save_map((["gFund":value]), SAVE_FILE);
}
void
save_gFund()
{
    "/d/Krynn/common/warfare/recruit_base"->my_save_gFund(gHouseArmy,gFund);
}

public nomask int
my_restore_gFund(string army)
{
    setuid();
    seteuid(getuid());
    return restore_map(SAVE_FILE)["gFund"];
}
void
restore_gFund()
{
    gFund = (("/d/Krynn/common/warfare/recruit_base")->my_restore_gFund(gHouseArmy,gFund));
}

int
add_fund(int sum)
{
    /* needs a check here who is the calling object. don't want any abuses! */
    restore_gFund();
    if (sum < 0 && -sum > gFund)
      return 0;
    gFund += sum;
    save_gFund();

    return 1;
}

string
recruit_text()
{
    return ("Syntax:\n" +
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
}

string
note_text()
{
    return ("NOTE: 20/10/99: The testing phase is over, the real war has begun. There are\n" +
	    "                no new changes in the system, and basically you will not see\n" +
	    "                any difference to before.\n" +
	    "      07/10/99: The Gods will declare the War of the Lance over as soon as\n" +
	    "                one year (Krynn time) has passed without any new conquest.\n" +
	    "                At that time, the standard reset procedure will set in,\n" +
	    "                recording the current state as well as resetting the clock.\n" +
	    "                There will be no new commands to aid you in detecting when an\n" +
	    "                area has been conquered, you will need to keep track yourselves.\n" +
	    "\n" +
	    "   If you still encounter problems or bugs, please mail Ansalon and Krynn wizards.\n" +
            "   Ideas and suggestions are still welcome.\n");
}

string
read_recruit_sign()
{
    return (recruit_text() + note_text());
}

string
read_recruit_fund_sign()
{
    return (recruit_text() +
	    "raise <money>               Raise money for the fund.\n\n" +
	    note_text());
}

void
init_recruit()
{
    add_action("recruit","recruit");
    add_action("guards","guards");
    add_action("areas","areas");
}

void
init_recruit_raise()
{
    add_action("raise","raise");
}

void
init_recruit_funds()
{
    add_action("funds","funds");
}

void
init_recruit_complete()
{
    init_recruit();
    init_recruit_funds();
    init_recruit_raise();
}

/* kept for backwards compatability */
void
init_recruit_fund()
{
    init_recruit_complete();
}

string
current_costs()
{
    string ret = "Costs for guards are currently:\n";
    string *npcs = ARMYMASTER->npc_string_list(gHouseArmy);
    string *areas = ARMYMASTER->query_areas_of_army(gHouseArmy);
    int i,j, price;

    for(i=0;i<sizeof(areas);i++)
    {
	j = ARMYMASTER->npcs_still_to_clone(areas[i]);
	ret += (areas[i] + ": (" + j + " guard" + (j == 1 ? "" : "s") + " still in reserve)\n");
	for(j=0;j<sizeof(npcs);j++)
	{
	    price = ARMYMASTER->calc_price_for_npc(areas[i],npcs[j]);
	    ret += (sprintf("%16s: %5dcc  (%s)\n",npcs[j], price, nice_coin_string(price)));
	}
    }
    ret += ("\n");
    return ret;
}


int
recruit(string str)
{
    string npc, area, *npcs, *recruited = ({});
    int number, money, cost = 0, silent = 0;

    if (!this_player())
	silent = 1;

    if (!this_object()->hook_allowed_to_recruit(this_player()))
    {
	if (!silent)
	    write("You do not have permission to recruit guards.\n");
        return 1;
    }

    if (!str || str == "")
    {
	if (!silent)
	    write(current_costs());
	return 1;
    }

    //recruit guard for <area>
    //recruit <number> guards for <area>
    if (sscanf(str, "guard for %s", area) == 1)
    {
	number = 1;
    }
    else if (sscanf(str, "%d for %s", number, area) != 2)
    {
	notify_fail("Recruit guard for <area>                or\n"+
		    "Recruit <number> guards for <area>.\n");
	return 0;
    }

    /* Check if all entries are valid */
    if (member_array(area,ARMYMASTER->query_areas()) < 0)
    {
	notify_fail("Recruit: Area invalid.\n");
	return 0;
    }

    /* Check if the area is indeed the correct one. */
    if (ARMYMASTER->army_in_area(area) != gHouseArmy)
    {
	notify_fail("This area does not seem to be under the protection of the " +
		gHouseArmy + ". Therefore, you cannot recruit anyone for this territory.\n");
	return 0;
    }

    if (1 > number || number > 100)
    {
	notify_fail("It is possible to recruit only 1 - 100 guards at a time.\n");
	return 0;
    }

    npcs = ARMYMASTER->npc_string_list(gHouseArmy);
    
    while (number > 0)
    {
	// here we can select probability and even awailable guards 
	// for diferent areas
	npc = ONE_OF(npcs); // now all are as likely as other

	money = ARMYMASTER->recruit_npc(area, npc);
	if (!money)
	{
	    if (!silent)
		write("Recruit: Strange.... Unable to test the recruiting!\n");
	    number = 0;
	}
	else if (!add_fund(-money))
	{
	    if (!silent)
		write("Recruit: Ended with insufficient funds.\n");
	    number = 0;
	}
	else if (!ARMYMASTER->recruit_npc(area,npc,1))
	{
	    if (!silent)
		write("Recruit: Strange.... Unable to recruit!\n");
	    number = 0;
	}
	else
	{
	    recruited += ({ npc });
	    cost += money;
	    number--;
	}
    }

    if (!silent)
    {
	write("You used " + nice_coin_string(cost) +
	    " coins from funds and recruited " + COMPOSITE_WORDS(recruited) + 
	    " for the " + area + ".\n");
	say(QCTNAME(TP) + " disposed some funds for recruitment of new guards.\n");
    }
    return 1;
}



int
guards(string str)
{
    string *npcs = ARMYMASTER->npc_string_list(gHouseArmy);
    
    write("The possible guards are:\n" +
	  COMPOSITE_WORDS(npcs) + ".\n\n" +
	  current_costs());

    return 1;
}


int
areas(string str)
{
    string areas = COMPOSITE_WORDS(ARMYMASTER->query_areas());
    string careas = COMPOSITE_WORDS(ARMYMASTER->query_areas_of_army(gHouseArmy));
    write("The possible Areas are:\n" +
	  (areas == "" ? "None" : areas) + ".\n\n" +
	  "Currently, these areas are under your control:\n" +
	  (careas == "" ? "None" : careas) + ".\n");
    return 1; 
}

int
funds(string str)
{
    int fund = query_funds();
    write("The funds for recruitment of new guards currently consists of:\n" +
	  "     " + fund + " copper coins\n" +
	  "---------------------------\n" +
	  "This is equal to: " + nice_coin_string(fund) + ".\n");
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

    set_alarm(1.0,0.0,do_automatic_recruit);
    
    return 1;
}


void
delay_automatic_recruit(int num, string area)
{
//    string *npcs;
//    string npc;

    if (num > 0)
    {
//	npcs = ARMYMASTER->npc_string_list(gHouseArmy);
//	npc = npcs[random(sizeof(npcs))];
//	add_fund(ARMYMASTER->calc_price_for_npc(area,npc));
	if (!recruit("guard for " + area))
	  log_file("armymaster","Recruit_base: Error from do_automatic_recruit:\n" +
		   "    recruit(\"guard for " + area + "\") failed!\n");
	set_alarm(0.5,0.0,&delay_automatic_recruit(num - 1,area));
    }
}

/* Do the recruiting automatically. */
void
do_automatic_recruit()
{
    int i,j;
    string *areas;
    string *npcs;
    string npc,area;
    int num_to_clone;

    object player = this_player();

    if (!gAutomaticRecruit)
      return;

    set_this_player(0);

    areas = ARMYMASTER->query_areas_of_army(gHouseArmy);
    npcs =  ARMYMASTER->npc_string_list(gHouseArmy);

    /*
    for(i=0;i<40;i++)
    {
	if (!sizeof(areas) || !sizeof(npcs))
	  continue;

	area = areas[random(sizeof(areas))];
	npc = npcs[random(sizeof(npcs))];
	if (query_funds() < ARMYMASTER->calc_price_for_npc(area,npc))
	  continue;
	if (!recruit(npc + " for " + area))
	  log_file("armymaster","Recruit_base: Error from do_automatic_recruit:\n" +
		   "    recruit(\"" + npc + " for " + area + "\") failed!\n");
    }
    */

    for(i=0;i<sizeof(areas);i++)
    {
	num_to_clone = 10 + (ARMYMASTER->rooms_in_area(areas[i]) / 10) - 
	  ARMYMASTER->npcs_still_to_clone(areas[i]);
	if (num_to_clone <= 0)
	  continue;
	
	if (10 + ARMYMASTER->rooms_in_area(areas[i]) / 10 <
	    ARMYMASTER->npcs_total_in_area(areas[i]))
	  num_to_clone /= 10;
	if (num_to_clone <= 0)
	  num_to_clone = 1;
	if (num_to_clone > 30)
	  num_to_clone = 30;

	set_alarm(0.0,0.0,&delay_automatic_recruit(num_to_clone,areas[i]));
    }
    set_this_player(player);
}



