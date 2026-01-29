#pragma strict_types

inherit "/std/monster.c";
inherit "/lib/trade.c";

#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/herb_types.h"

#define NUM sizeof(MONEY_TYPES)

int check_status(string who);
int can_afford(int price);
int cure_poison();
int cure_hp();
void do_thank();

string cure_type, pay_type, get_type, coin_pay_text, coin_get_text;
int must_pay, *money_arr, no_of_poison_cures, no_of_hp_cures;
object patient;

void
create_monster()
{
  if (!IS_CLONE) return;
  set_name("woman");
  set_pname("women");
  add_name("healer");
  set_living_name("ioreth");
  set_race_name("human");
  set_gender(G_FEMALE);
  set_adj("old");
  set_short("old woman");
  set_pshort("old women");
  set_long("This old woman is Ioreth, the eldest of the women who serve in\n"+
    "the Houses of Healing. Her wisdom in healing is exceeded only by her\n"+
    "talkativity.\n");
  set_stats(({ 20, 20, 21, 74, 78, 22 }));
  set_alignment(550);
  set_hp(500);
  set_mana(1000);
  add_prop(CONT_I_WEIGHT,49000);
  add_prop(CONT_I_HEIGHT,160);
  set_skill(SS_UNARM_COMBAT,22);
  set_skill(SS_DEFENCE,15);
  set_skill(SS_ELEMENT_LIFE,86);
  set_skill(SS_ELEMENT_EARTH,56);
  set_skill(SS_FORM_CONJURATION,82);
  set_skill(SS_HERBALISM,76);
  set_skill(SS_ALCHEMY,75);
  set_chat_time(1);
  add_chat("The hands of the king are the hands of a healer,\n"+
    "       and so shall the rightful king be known.");
  add_chat("I hope those murdering devils do not come to this House!");
  add_chat("We do our best in this House with what we have.");
  add_chat("I grew up in Lossarnach, south of Minas Tirith.");
  add_chat("I remember the roses of Imloth Melui when I was a lass.");
  add_chat("The herb-master is in charge of the herbs of healing here.");
  add_chat("Please don't trouble the sick!");
  set_cchat_time(2);
  add_cchat("I am but a defenseless old woman! How can you think of attacking me?");
  add_cchat("Help!");
  add_cchat("What is the meaning of this!?");
  add_cchat("Please stop, please!!");
  add_cchat("Oh no, don't kill me!");
  config_default_trade();
  set_money_give_out(({ 10000, 700, 10, 8 }));
  set_money_give_reduce(({  0,  0,  0,  0 }));
  no_of_poison_cures = 15;
  no_of_hp_cures = 15;
  enable_reset();
}

void
init_living()
{
  add_action("do_pay","pay");
}

void
catch_tell(string str)
{
  string who, what, trash;
  ::catch_tell(str);
  if (str && sscanf(str,"%s says: %s\n", who, what) == 2) {
    what = lower_case(what);
    who = lower_case(who);
    if (sscanf(str,"%s kingsfoi%s", trash, trash) == 2) {
      command("say Kingsfoil, now that's a strange name, and I wonder why 'tis\n"+
        "called so, for if I were a king, I would have plants more bright in\n"+
        "my garden. Still it smells sweet or wholesome when bruised, but I\n"+
        "have never heard it had any great virtue. We have none of it here.");
      command("smile");
      }
    else if (sscanf(str,"%s athela%s", trash, trash) == 2) {
      command("say Athelas? I do not know, I am sure, at least not by that\n"+
        "name. Perchance the herb-master can be asked; he knows all the old names.");
      command("smile");
      }
    else if (sscanf(str,"%s heal%s", trash, trash) == 2) {
      command("say Do you need healing? We can offer some healing here.");
      command("smile "+who);
      command("say If you need our care, please lie down on the bed.");
      }
    }
  else if (sscanf(str,"%s lies down in the bed.", who) == 1) {
    command("say We will see if there is anything we can do, "+who+".");
    check_status(lower_case(who));
    }
}

int
check_status(string who)
{
  object *inv_arr;
  int price, i, n;
  if (!present(who,environment())) return 1;
  patient = present(who,environment());
  inv_arr = all_inventory(patient);
  while (n<sizeof(inv_arr)) {
    if (function_exists("cure_poison",inv_arr[n]))
      price = price + 5 * (inv_arr[n]->query_strength());
    n++;
    }
  if (price) {
    command("say I notice that you have been poisoned, "+
      ((patient->query_gender() == G_MALE) ? "sir" : "mylady")+".");
    command("say We would be glad to cure you from the poison.");
    if (no_of_poison_cures <= 0) {
      command("say Unfortunately I have run out of poison-curing herbs.");
      command("sigh");
      command("say There is nothing I can do with that. Sorry.");
      return 1;
      }
    must_pay = price - (price * 20 * patient->query_skill(SS_TRADING)/100)/100;
    command("say You must pay "+must_pay+" coppers for the service.");
    command("say Herbs are rare and hard to get nowadays.");
    command("sigh");
    cure_type = "poison";
    return 1;
    }
  price = 20*(F_MAX_HP(patient->query_stat(SS_CON)) - patient->query_hp());
  if (price) {
    command("say I can see that you are hurt, "+
      ((patient->query_gender() == G_MALE) ? "sir" : "mylady")+".");
    command("say We would be happy to tend your wounds and heal you fully.");
    must_pay = price - (price * 20 * patient->query_skill(SS_TRADING)/100)/100;
    command("say You will have to pay "+must_pay+" coppers for the service.");
    command("say It is not easy to get the needed medicines nowadays.");
    command("smile");
    cure_type = "hp";
    return 1;
    }
  command("say If there is something wrong with you, I do not think I can\n"+
    "   do anything about it. I am sorry.");
  command("sigh");
  command("comfort "+who);
  return 1;
}

int
do_pay(string str)
{
  if (!str || str != "healer") {
    write("You may type 'pay healer'.\n");
    return 1;
    }
  if (TP != patient) {
    command("say 'Tis not your turn yet, "+
      ((TP->query_gender() == G_MALE) ? "sir" : "mylady")+".");
    command("smile "+TP->query_real_name());
    return 1;
    }
  if (can_afford(must_pay)) {
    if (cure_type == "hp") {
      tell_room(environment(),"The old woman starts mixing some herbs in a bowl.\n");
      tell_room(environment(),"A younger woman arrives with a bowl of boiling water.\n");
      tell_room(environment(),"The old woman pours the crushed herbs into the water.\n");
      set_alarm(15.0, 0.0, cure_hp());
      return 1;
      }
    if (cure_type == "poison") {
      tell_room(environment(),"The old woman takes some herbs from her pocket and crushes them.\n");
      tell_room(environment(),"A young boy arrives with a pink potion, which he gives her.\n");
      tell_room(environment(),"The old woman pours the herbs in the potion, and starts shaking it.\n");
      set_alarm(10.0, 0.0, cure_poison());
      return 1;
      }
    }
  command("say Oh...you cannot afford it.");
  if (cure_type == "poison" && patient->query_alignment() > 75) {
    command("say Oh well, I will try to help you a little anyway.");
    command("say I will take what you have of money.");
    while (present("coin",patient)) {
      present("coin",patient)->remove_object();
      }
    tell_room(environment(),"The old woman puts some herbs into a pink potion.\n");
    set_alarm(10.0, 0.0, cure_poison());
    return 1;
    }
  return 1;
}

int
cure_hp()
{
  int hp_needed, doses;

  if (environment(patient) != environment(TO)) return 1;
  tell_room(environment(),"The old woman makes "+QTNAME(patient)+" drink the brew.\n",patient);
  patient->catch_msg("The old woman makes you drink the brew. It tastes bitter.\n");
  hp_needed = (patient->query_stat(SS_CON)*patient->query_stat(SS_CON)) - patient->query_hp();
  doses = hp_needed/150;
  no_of_hp_cures -= doses;
  patient->set_hp(patient->query_stat(SS_CON)*patient->query_stat(SS_CON));
  patient->catch_msg("You feel fully healed!\n");
  return 1;
}

int
cure_poison()
{
  int n;
  object *inv_arr;
  if (environment(patient) != environment(TO)) return 1;
  tell_room(environment(),"The old woman makes "+QTNAME(patient)+" drink the pink potion.\n",patient);
  patient->catch_msg("The old woman makes you drink the pink potion. It smells sweet.\n");
  inv_arr = all_inventory(patient);
  while (n<sizeof(inv_arr)) {
    if (function_exists("cure_poison",inv_arr[n]))
      inv_arr[n]->cure_poison(({"all"}),100);
    n++;
    }
  no_of_poison_cures -= n;
  command("smile");
  return 1;
}

int
can_afford(int price)
{
  if (sizeof(money_arr = pay(price, patient, 0, 0, 0, get_type)) == 1)
    return 0;
  coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
  coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
  write("You pay "+coin_pay_text+" to Ioreth the Healer.\n");
  if (coin_get_text)
    write("You get "+coin_get_text+" back.\n");
  return 1;
}

void
react_introduce(string who, string trash) {
  object obj;
  int ran;
  if (obj = present(who, environment())) {
    ran = random(3);
    if (ran == 0)
    {
      command("curtsey "+obj->query_real_name());
      command("introduce myself");
    }
    if (ran == 1)
    {
      command("say Welcome to the Houses of Healing, "+obj->query_name()+".");
      command("introduce myself");
    }
    if (ran == 2)
    {
      command("introduce myself");
      command("say Art thou in need of healing, honoured "+obj->query_name()+"?");
      command("say Then lie down on this bed, so as I may tend to you.");
    }
  }
}

void
reset_monster()
{
  no_of_hp_cures += 3;
  no_of_poison_cures += 2;
}

void
add_hp_herb(int i)
{
  no_of_hp_cures += i;
}

void
add_cure_herb(int i)
{
  no_of_poison_cures += i;
}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj, from);
  if (!from) return;
  if (function_exists("create_herb",obj)) {
    if (obj->query_effect()) {
      if (obj->query_effect()[0] == HERB_HEALING) add_hp_herb(obj->query_effect()[2]/150 + 1);
      if (obj->query_effect()[0] == HERB_CURING) add_cure_herb(1);
      set_alarm(2.0, 0.0, &do_thank());
    }
  }
}

void
do_thank()
{
  command("say I am most grateful for the herb.");
  command("curtsey");
  command("smile");
}

/* Solemnian prestige */
int
query_knight_prestige() {return -7; }
