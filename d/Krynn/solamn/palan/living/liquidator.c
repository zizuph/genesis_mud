/* created by Aridor 01/21/94 */

#include "/ss_types.h"
#include <macros.h>
#include "../local.h"
#include <money.h>

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
    set_living_name("niloc");
    set_name("niloc");
    add_name("liquidator");
    set_race_name("troll");
    add_adj("deadly");
    set_adj("impressive");

    set_long("This is a huge, enormous, impressive troll. His presence alone " +
	     "makes you feel very uncomfortable, but knowing the reason for it " +
	     "could even make you feel worse.\n");
    set_title("the Liquidator");
    
    set_stats(({300, 200, 300, 20, 20, 300}));
    set_hp(10000);

    set_all_attack_unarmed(30, 40);
    set_all_hitloc_unarmed(40);

    set_default_answer(VBFC_ME("my_answer"));
    add_ask(({"lend","lending","money"}),VBFC_ME("mo_money"));
    add_ask(({"reason"}),VBFC_ME("my_reason"));

    trig_new("%s 'introduces' %s","my_intro");
    trig_new("%s 'bows' %s", "my_bow");

    config_default_trade();
}

/* Function name: set_my_level_factor
 * Description:   set up the liquidator so he
 *                has factor*stats of the person
 *                to liquidate.
 * Arguments:     int factor, object player
 * Returns:       void
 */
void
set_my_level_factor(int factor, object player)
{
  if (!player)
    return;
  set_base_stat(SS_STR, factor * (player->query_base_stat(SS_STR)));
  set_base_stat(SS_DEX, factor * (player->query_base_stat(SS_DEX)));
  set_base_stat(SS_CON, factor * (player->query_base_stat(SS_CON)));
  set_base_stat(SS_DIS, factor * (player->query_base_stat(SS_DIS)));
  set_hp(query_max_hp());
}


init_living()
{
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
  call_out("command",1,"smile stupidly");
  call_out("command",3,"emote roars: What?");
  return "";
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
  command("emote roars: I am collecting unfaid pees, err, unpaid fees!");
  return "";
}


my_reason()
{
  command("emote roars: Well, I am here to liquidate you.");
  command("emote bleaks his fangs.");
  command("emote I'm very good at it!");
  command("emote growls menacingly.");
  return "";
}
