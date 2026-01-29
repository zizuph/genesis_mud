/*
 *  The priestess that performs the wedding ceremony
 *							Tricky, Dec 1992
 */

inherit "/std/monster";
inherit "/lib/trade";

#include "defs.h"
#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

#define WEDDING_PRICE 10000

/* How far are we with the ceremony? */

#define WED_NOT_STARTED 0
#define WED_TELL_BRIDE_WITNESS 1
#define WED_WAIT_BRIDE_WITNESS 2
#define WED_TELL_GROOM_WITNESS 3
#define WED_WAIT_GROOM_WITNESS 4
#define WED_TELL_BRIDE 5
#define WED_WAIT_BRIDE 6
#define WED_TELL_GROOM 7
#define WED_WAIT_GROOM 8
#define WED_END_WEDDING 9

//   Prototypes
void accept_yes();

string pay_type,get_type, coin_pay_text, coin_get_text, *sold_arr, *from_arr;
object *given_obj_arr;
int *money_arr, gStatus;
int alarm_id;

/*
 *  Prototypes
 */
void give_back(object what);
object *still_present();


void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_name(({"priestess","ambriel"}));
    set_title("Giollith, High Priestess");
    set_race_name("elf");
    set_living_name("priestess");
    set_adj("high");
    set_short("high priestess");
    set_long("@@my_long");
    set_gender(G_FEMALE);

             /* str dex con int wis dis */
    set_stats(({ 22, 56, 21, 88, 88, 90}));
    set_hp(10000); /* Heal fully */
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_DEFENCE, 47);

    set_aggressive(0);
    set_attack_chance(0);

    set_chat_time(5 + random(6));
    add_chat("@@hint_chat");

    /* Triggers */
/**/trig_new("%w 'says:' %s", "react_say"); /* Does this work? */

    /* Set up the trading system */
    config_default_trade();
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  10,   10 })); /* Max_pay   */
    set_money_give_reduce(({     0,     0,   0,    0 })); /* Threshold */

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(CONT_I_WEIGHT,56000);	/*  56 Kg */
    add_prop(CONT_I_HEIGHT,183);	/* 183 cm */


    gStatus = WED_NOT_STARTED;
}

void
init_living()
{
    add_action("do_pay","pay",0);
}

string
my_long()
{
    string str;

    str = "The priestess is dressed in a almost fluorescent white "
	+ "gown. Her sparkling green eyes can look straight through "
	+ "you, into your heart. The priestess can wed two people, "
	+ "the ceremony is described in the Book of Wedlock.";

    if (gStatus != WED_NOT_STARTED)
	str += " She is currently joining two people in holy matrimony.";

    return break_string(str + "\n", 70);
}

string
wizinfo()
{
    string str;

    str = "The priestess performs the wedding ceremony as it is "
	+ "described in the wedding book.\n";

   return break_string(str, 70);
}

/********************************************************************
 *
 * Player commands
 */

int
do_pay(string str) {
   int i, j;
   object ob, tp;
   string item;

   if (!str)
      return 0;

   /* Check if the player defines what she would like in return. */
   if (sscanf(str, "priestess and get %s",get_type) != 3)
   {
      get_type = "";
      if (str != "priestess")
      {
         notify_fail("You can simply type 'pay priestess'.\n");
         return 0;
      }
   }

   tp = this_player();

   if (can_afford(WEDDING_PRICE, tp))

   return 1;
}

/*
 * TO DO: add randomness
 */
string
hint_chat()
{
    int ran;
    string name;
    object *people;

    if (gStatus == WED_NOT_STARTED)
    {
	return "Hello there.";
    }

    if (gStatus == WED_TELL_BRIDE_WITNESS)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	gStatus = WED_WAIT_BRIDE_WITNESS;
	return "Who giveth away this bride?";
    }

    if (gStatus == WED_WAIT_BRIDE_WITNESS)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	return "Well " +  capitalize(people[BRIDE_WITNESS]->query_real_name())
	     + "? Do you give her away?";
    }

    if (gStatus == WED_TELL_GROOM_WITNESS)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	gStatus = WED_WAIT_GROOM_WITNESS;
	return "Who giveth away this groom?";
    }

    if (gStatus == WED_WAIT_GROOM_WITNESS)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	return "Well " +  capitalize(people[GROOM_WITNESS]->query_real_name())
	     + "? Do you give her away?";
    }

    if (gStatus == WED_TELL_BRIDE)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	gStatus = WED_WAIT_BRIDE;
	return capitalize(people[BRIDE]->query_real_name())
	     + ", do you take "
	     +  capitalize(people[GROOM]->query_real_name())
	     + "to be your lawful wedded husband?";
    }

    if (gStatus == WED_WAIT_BRIDE)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	return "Well? Do you, "
	     +  capitalize(people[BRIDE]->query_real_name()) + "?";
    }

    if (gStatus == WED_TELL_GROOM)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	gStatus = WED_WAIT_GROOM;
	return capitalize(people[GROOM]->query_real_name())
	     + ", do you take "
	     +  capitalize(people[BRIDE]->query_real_name())
	     + "to be your lawful wedded wife?";
    }

    if (gStatus == WED_WAIT_GROOM)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	return "Well? Do you, "
	     +  capitalize(people[GROOM]->query_real_name()) + "?";
    }

    if (gStatus == WED_END_WEDDING)
    {
	if (!(people = still_present()))
	{
	    gStatus = WED_NOT_STARTED;
	    return "I miss someone. I cannot continue the wedding.";
	}
	return "Then I declare you both as married.";
    }
}

void
catch_tell(string str)
{
    int i, ran;
    string who, what;

    ::catch_tell(str);

    if (gStatus == WED_NOT_STARTED)
	return;

    if (str && sscanf(str, "%s says: %s\n", who, what) == 2)
    {
	react_say(who, what);
    }
}

/*
 * Function name:   still_present
 * Description:	    Returns an array of all people that are involved
 *		    in the wedding of the form
 *
 *		       ({ groom, bride, grooms witness, brides witness })
 *
 *		    or an empty array if one person is missing.
object *
still_present()
{
}

/**************************************************************************
 *
 *  Control the flow of the ceremony by reacting to the things that
 *  are said in the chapel.
 */
int
react_say(string who, string what)
{
    object person;

    if (who)
    {
	if (!(person = present(who)))
	    return 1;
	
        what = lower_case(what);

	switch (gStatus)
	{

	case WED_WAIT_BRIDE_WITNESS:
	    
	    
	    if (str=="i do." || str=="i do" || str == "yes")
	    {
		gStatus = WED_TELL_GROOM_WITNESS;
                alarm_id = set_alarm(1.0,0.0,&accept_yes());
		return 1;
	    }
	    break;

	case WED_WAIT_GROOM_WITNESS:
	    if (str=="i do." || str=="i do" || str == "yes")
	    {
		gStatus = WED_TELL_BRIDE;
		return 1;
	    }
	    break;

	case WED_WAIT_BRIDE:
	    if (str=="i do." || str=="i do" || str == "yes")
	    {
		gStatus = WED_TELL_GROOM;
		return 1;
	    }
	    break;

	case WED_WAIT_GROOM:
	    if (str=="i do." || str=="i do" || str == "yes")
	    {
		gStatus = WED_END_WEDDING;
		return 1;
	    }
	    break;

	default:
	    return 1;
	}
    }
    return 1;
}

void
return_say(string who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
	switch (random(3))
	{
	    case 0:
		command("say Funny, eh " + obj->query_race() + "?");
		break;
	    case 1:
		command("say Ah, " + LANG_PWORD(obj->query_race())
		      + " are such merry people.");
		break;
	    case 2:
		command("giggle");
	}
   }
}

void
accept_yes()
{
    remove_alarm(alarm_id);
    switch (random(3))
    {
	case 0:
	    command("smile");
	    break;
	case 1:
	    command("say Ah, good.");
	    command("smile");
	    break;
	case 2:
	    command("nod");
    }
}
