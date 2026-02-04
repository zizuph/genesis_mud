/* 
This is a traveling potion salesman made by Merrygrin 
*/

#include "macros.h"
#include "stdproperties.h"
#include "money.h"
#include "/sys/ss_types.h"
#include <defs.h>

#define BS(x)       break_string(x, 77)
#define TP          this_player()
#define TO          this_object()
#define NUM         4
#define MY_HOME     "/d/Shire/common/hobbiton/phouse"
#define MY_PATH     "/d/Shire/common/hobbiton"
#define STORE_ROOM  this_object()
#define SHIRE       "Shire"

inherit STDWALKMONSTER;
inherit "/lib/trade";



/* 
  Init. functions
*/

create_walk_monster() {
  if (!IS_CLONE) return;
  set_name("gorge");
  add_name("salesman");
  set_living_name("gorge");
  set_adj("small");
  set_race_name("hobbit");
  set_long(BS("This is a traveling salesman. He travels this "
	      + "area trying to sell his stuff."
	      + "You can try 'list' to see what he is selling or"
	      + " you can 'buy <colour> potion'.\n"));
  set_short("salesman");
  default_config_npc(30);	/* But we are not supposed to kill him */
  config_default_trade();
  set_hp(50000);
    
  add_act("shout Potions for sale!");
  add_act("shout Fine newly brewed potions for sale!");
  add_act("shout Cheap potions!");
  set_act_time(15);

  set_skill(SS_AWARENESS, 80);

  set_my_home(MY_HOME);
  set_my_path(MY_PATH);

  seq_new("hubba");
  seq_addfirst("hubba", ({ "@@do_give" }) );

  trig_new("%s 'introduces' %s", "react_introduce");
  trig_new("%s 'Should' %s", "react_negative");

}

init_living() {
  add_action("do_list","list");
  add_action("buy","buy");
}

return_introduce(who) {
  if (random(4) && present(who, environment())) {
    command("introduce myself to " + who);
    command("introduce grimrock to " + who);
  }
  else {
    command("introduce myself");
    command("introduce grimrock");
  }
}


react_introduce(who, tmp) {
  object ob;

/*  if (!who) return 0;
  who = lower_case(who);
  ob = present(who, environment());
  if (!ob) return 0;
  if (!notmet_me(ob)) return 0;
  if (!random(20)) return 0;*/
  call_out("return_introduce", random(3) + 2, who);
  return 1;
}

no(str) {
  string *st;

  st = explode(str, ".");
  
  command("say No this " + st[0] + " might want to trade with me.");
  command("smile");

}

react_negative(str1,str2) {
  string *str;
  int t;

  str = explode(str2, " ");
  t = random(3);
  call_out("no", t + 2, str[3]);
}

do_give() {
  object pot;
  int i;
  
  if (environment()) {
    tell_room(environment(), "Suddenly coppers fall down from the sky.\n");
    seteuid(getuid(this_object()));
    give(5000, this_object());
    command("get all");
    
    for(i=0;i<6;i++) {
      pot = clone_object(STAND_OBJ + "ipotion");
      pot->move(STORE_ROOM);
      pot = clone_object(STAND_OBJ + "mpotion");
      pot->move(STORE_ROOM);
    }
    
    pot = clone_object(STAND_OBJ + "ppotion");
    pot->move(STORE_ROOM);

  }
}

/* We want to make a function to add potions */


do_list() {
  object *ob;
  int price,i;

  ob = all_inventory();

  if (!parse_command("potion", this_object(), "%i", ob)) {
    command("say Sorry but I don't have anything for sale.");
    return 0;
  }

  if (sizeof(ob) > 1) {
    write("I've got these potions:\n");
  }
  else {
    write("I've got this potion.\n");
  }

  for (i = 1;i<sizeof(ob);i++) {
    price = (int)2 * ob[i]->query_prop(OBJ_I_VALUE);
    write(ob[i]->short() + " and I would sell it for " + price + " coppers.\n");
  }

  return 1;

}

/* Test if I was the wictim */

attacked_by(ob) {
  object grimrock;

  grimrock = find_living("grimrock");

  if(!grimrock) {
    command("shout Shiiit!");
    command("say Sorry but I will leave now.");
    command("grin");
    write("The hobbit opens a vial and quaffs the potion.\n");
    move_living("through a rift in space", MY_HOME);
    ob->stop_fight(this_object());
    remove_object();
  }
  command("shout That was a big misstake.\n");
  command("shout Grimrock kill this " + ob->query_race_name());



  ob->attack_object(grimrock);
  say(BS(QCTNAME(this_player()) + " attackes the hobbit but the dwarf stands "
      + " between them and attacks!\n"));

}

  
/* 
  The buy code.
*/

buy(string str) {
  object buy_ob, *item;
  string what;
  int price,result,change,i,red;
  
  if(!str) {
    notify_fail("Buy what did you say?");
    return 0;
  }
  
  what = str;
  
  item = all_inventory(this_object());
  
  if(!parse_command(str, this_object(), "%o", item)) {
    notify_fail("I don't seem to have that potion with me.\n"
		+ "You might try again another day.\n");
    return 0;
  }
  
  price = (int)2 * item->query_prop(OBJ_I_VALUE);

  if(TP->query_guild_member(SHIRE)) {
    price = (int)(price * 3/4);   /* Give members a 25% reduction. */
    command("say Ahhh. A member of the guild!");
    command("say I'll cut the price for you.");
    command("smile");
  }

  if(TP->query_skill(SS_TRADING)) {
    red = (int)(price * query_skill(SS_TRADING)/200);
    price = (price - red); 
    command("say Ahhh. You drive a hard bargain!.");
    command("sigh");
  }

  result = pay(price, this_player(), "gold", 0, this_object(), "copper");
  if (sizeof(result) == 1) {
    return 0;
  }
  
  if ((int)item->move(TP)) {
    write("You drop the " + item->short() + " on the ground.\n");
    say(BS(QCTNAME(TP) + " drops one " + item->short() +
	   " on the ground.\n"));
    buy_ob->move(environment(TP));
  }
  else {
    write("You get your " + item->short() + ".\n");
    say(QCTNAME(TP) + " buys the " + item->short() + ".\n");
  }
  
  write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
  change = text(result[NUM .. 2 * NUM - 1]);

  seteuid(getuid(TO));
  if(MERRYS_LOG == 1) {
    log_file("potion_man", extract(ctime(time()), 4, 15) + 
	       " " + capitalize(TP->query_real_name()) + " " + item->short()
	       + "\n");
  }

  
  if (change) {
    write("You get, " + change + " as change.\n");
  }

  say("Nice doing buisness with you.");

  return 1;

}

/* This is for the solamnic Knights */

query_knight_prestige() { return (-6); }

heart_beat(int num) {
  ::heart_beat(num);
  heal_hp(10000);
}
