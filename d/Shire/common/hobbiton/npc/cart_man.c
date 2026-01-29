/* 
 * This is a traveling potion salesman made by Merrygrin 
 * Cloned by a call_out() (200 sec. delay) in ~Shire/common/hobbiton/er10
 */
/* he now sells lotsa stuff.    Dunstable, Sept 1994 */
inherit "/std/monster";
inherit "/lib/trade";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "macros.h"
#include "stdproperties.h"
#include "money.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/monster/tobacco.h"

#define NUM         4
#define MY_HOME	HOBBIT_DIR + "er1"
#define MY_PATH {"/d/Shire/common/greyhaven","/d/Shire/common/hobbiton",/d/Shire/michel"}
#define STORE_ROOM  TO
#define SHIRE       "Shire"

//    Prototypes
void no(string str);
void return_introduce(string who);
void reset_intr();

int intro;

/* 
  Init. functions
*/

void
create_monster()
{
  if (!IS_CLONE) return;
  set_name("bobo");
  add_name("salesman");
  set_living_name("_bobo_");
   set_adj(({"strong","tired"}));
  set_race_name("hobbit");
  set_long("This is a traveling salesman. He travels this "
	      + "area trying to sell his stuff."
	      + "  You can try 'cart' to see what is in his cart or"
	      + " you can 'buy item'.\n");
  default_config_npc(30);	/* But we are not supposed to kill him */
  config_default_trade();
  set_hp(50000);
    
  set_act_time(5);
   add_act("shout Sacks for sale!");
   add_act("shout Get your chests right here!");
   add_act("shout I've got herb bags!");
   add_act("say I'm no bank, I don't take gold and platinum coins.");
   add_act("Sometimes I think this is better than farming.");

  set_skill(SS_AWARENESS, 80);
    set_skill(SS_DEFENCE, 100);
   set_skill(SS_UNARM_COMBAT, 100);

   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(LIVE_S_EXTRA_SHORT, " is pulling his cart behind him");
   set_m_out("leaves with his cart");
   set_m_in("arrives, pulling a cart behind him.");

/*  set_monster_home(MY_HOME); */
   set_restrain_path(({"/d/Shire/common/greyhaven","/d/Shire/common/hobbiton","/d/Shire/michel","/d/Shire/common/eastroad"}));
  set_random_move(1);

  seq_new("hubba");
  seq_addfirst("hubba", ({ "@@do_give" }) );

  trig_new("%s 'introduces' %s", "react_introduce");
  trig_new("%s 'Should' 'I' 'kill' 'this' %w %s", "react_negative");

  intro = 1;

}

void
init_living() {
  add_action("do_list","cart");
  add_action("do_buy","buy");
}

void
return_introduce(string who) {
  if (random(4) && present(who, environment())) {
    command("introduce myself to " + who);
    command("introduce grimrock to " + who);
  }
  else {
    command("introduce myself");
    command("introduce grimrock");
  }
}


int
react_introduce(string who, string tmp) {
  object ob;

  if (!intro) return 0;
  intro = 0;
  set_alarm(30.0,0.0,&reset_intr());
/*  if (!who) return 0;
  if (!notmet_me(ob)) return 0;
  if (!random(20)) return 0;*/
  set_alarm(itof(random(3) + 2),0.0,&return_introduce(who));
  return 1;
}

void
no(string str) {
  string *st;

  st = explode(str, ".");
  
  command("say No, this " + st[0] + " might want to trade with me.");
  command("smile");
}

void
react_negative(string str1, string str2, string str3) {
  int t;

  t = random(3);
  set_alarm(itof(t + 2),0.0,&no(str2));
}

do_give() {
   object sack, chest, bag;
  int i;
  
  if (environment()) {
    tell_room(environment(), "Suddenly coppers fall down from the sky.\n");
    seteuid(getuid(this_object()));
    
    for(i=0;i<3;i++) {
   sack = clone_object(OBJ_DIR + "sack");
   sack->move(STORE_ROOM);

   bag = clone_object(OBJ_DIR + "herbbag");
   bag->move(STORE_ROOM);

   chest = clone_object(OBJ_DIR + "chest");
   chest->move(STORE_ROOM);
    }
    

  }
}

/* We want to make a function to add equip */


do_list() {
  object *ob;
  int price,i;

  ob = all_inventory();


   if (sizeof(ob) < 1) {
     write("Sorry, I'm all out of things to sell.\n");
   command("sigh");
   }

  if (sizeof(ob) > 1) {
    write("I've got these items:\n");
  }
  else {
    write("I've got this item.\n");
  }

  for (i = 1;i<sizeof(ob);i++) {
    price = (int)2 * ob[i]->query_prop(OBJ_I_VALUE);
    write(ob[i]->short() + " and I would sell it for " + price + " coppers.\n");
  }

  return 1;

}

/* Test if I was the victim */

attacked_by(ob) {
  object grimrock;

  grimrock = find_living("grimrock");

  if(!grimrock) {
   command("say You don't believe in fair trade, do you?");
   command("kick all");
    command("grin");
   say("The hobbit pushes his cart into the bushes near the road.\n");
    move_living("west", MY_HOME);
    ob->stop_fight(this_object());
   TO->remove_object();
  }
  command("shout That was a big mistake.\n");
  command("shout Grimrock kill this " + ob->query_race_name());



  ob->attack_object(grimrock);
  say(BS(QCTNAME(this_player()) + " attacks the hobbit but the dwarf jumps "
      + " between them and defends his master!!\n"));

}

  
/* 
  The buy code.
*/

do_buy(string str) {
  object buy_ob, *item;
  int price,result,change,i,red;
  
  if(!str) {
    notify_fail(QCTNAME(TO) + " says: Buy what did you say?");
    return 0;
  }
  
  
  item = all_inventory(TO);
  
  if(!parse_command(str, TO, "%o", item)) {
    notify_fail(QCTNAME(TO) + " says: I don't seem to have that item with me.\n"
		+ "You might try again another day.\n");
    return 0;
  }
  
  price = (int)2 * item->query_prop(OBJ_I_VALUE);


  if(TP->query_skill(SS_TRADING)) {
    red = (int)(price * query_skill(SS_TRADING)/200);
    price = (price - red); 
    command("say Ahhh. You drive a hard bargain!");
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
  
  if (change) {
    write("You get, " + change + " as change.\n");
  }

  say("Nice doing business with you.");

  return 1;

}

/* This is for the solamnic Knights */

query_knight_prestige() { return (-6); }

heart_beat(int num) {
  ::heart_beat(num);
  heal_hp(10000);
}

reset_intr() {
  
  intro = 1;

}
