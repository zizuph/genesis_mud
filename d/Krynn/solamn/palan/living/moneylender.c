/* created by Aridor 01/18/94 */

#include "/ss_types.h"
#include <macros.h>
#include "../local.h"
#include <money.h>
#define CITY_GUARD     PALACE + "office15"

inherit "/lib/trade.c";
inherit M_FILE


/*prototypes*/
int my_intro(string s1, string s2);
int my_bow(string s1, string s2);
string my_answer();

int no_intro = 0,
    no_bow = 0;


void
create_krynn_monster()
{
    set_living_name("colin");
    set_name("colin");
    set_race_name("human");
    add_adj("greedy");
    set_adj("slick");

    set_long("This is Colin, the Moneylender.\n");
    set_title("the Moneylender.");
    
    set_stats(({100, 100, 100, 200, 200, 100}));
    set_hp(6000);

    set_default_answer(VBFC_ME("my_answer"));
    add_ask(({"lend","lending","money"}),VBFC_ME("mo_money"));

    trig_new("%s 'introduces' %s","my_intro");
    trig_new("%s 'bows' %s", "my_bow");

    config_default_trade();
}

init_living()
{
  ADA("lend");
  ADA("repay");
}

erase_no_bow() { no_bow = 0; }

int
my_bow(string s1, string s2)
{
  if (!no_bow)
    {
      call_out("command", 1, "bow");
      no_bow = 1;
      call_out("erase_no_bow",6);
      return 1;
    }
  return 1;
}

erase_no_intro() { no_intro = 0; }

int
my_intro(string s1, string s2)
{
  if (!no_intro)
    {
      call_out("command", 1,"introduce me");
      no_intro = 1;
      call_out("erase_no_intro",6);
      return 1;
    }
  return 1;
}

string
my_answer()
{
  call_out("command",1,"shrug");
  call_out("command",3,"say I cannot help you with that.");
  return "";
}


call_the_guards(string aggressor, string dummy)
{
  object hitem, *thigy = all_inventory(E(TO));
  int i;
  for (i = 0; i < sizeof(thigy); i++)
    if ((thigy[i]->vbfc_short() == aggressor[4..strlen(aggressor)]) ||
	(thigy[i]->vbfc_short() == aggressor))
      hitem = thigy[i];
  CITY_GUARD->load_me();
  CITY_GUARD->help_i_need_help(hitem);
}

attacked_by(object who)
{
    ::attacked_by(who);
    command("shout HELP! Help ME! I am being attacked!");
    CITY_GUARD->help_i_need_help(who);
}

/* Function name: lend
 * Description:   give out money to the player,
 *                to get our money back !-) we give out an (invisible)
 *                lending object that calls the Liquidator of Debts :)
 *                if the player 'accidently' forgets to repay.
 * Arguments:     str: did the player specify what or how to lend?
 * Returns:       1 if command recognized
 *                0 if not
 */
lend(string str)
{
  int amount, i, test;
  string type, dummy;
  object lendobj;
  string *money_types = MONEY_TYPES;
  NF("Lend how much money?\n");
  if (!str || str == "")
    return 0;
  for(i=0; i<sizeof(money_types);i++)
    {
      test = sscanf(str,"%i " + money_types[i] + " coin%w", amount, dummy);
      if (test == 2)
	break;
    }
  
  if (i == sizeof(money_types))
    return 0;
  type = money_types[i];
  if (!amount)
    return 0;
  lendobj = clone_object(OBJ + "lend_obj");
  lendobj->initialize_the_lending_object(amount,TP->query_age());
  lendobj->move(TP, 1);
  give(amount,TP,str,0,0,0);

}

/* Function name: repay
 * Description:   someone actually wants to repay his debts??
 *                well, we won't keep him! ;-)
 *                he/she can specify to repay only parts of
 *                the debt, too, of course.
 * Arguments:     str: did the player specify what or how to repay?
 * Returns:       1 if command recognized
 *                0 if not
 */
repay(string str)
{

}


/* Function name: mo_money
 * Description:   tell anyone who's interested about our money we 
 *                have to give away.
 * Arguments:     none
 * Returns:       string: what we say.
 */
mo_money()
{
  return "I can lend you some!\n";
}
