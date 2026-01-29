/*
 *  The petshop owner, who sells the pets to players.
 */

inherit "/std/monster";
inherit "/lib/trade";

#include "defs.h"
#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define DOG_RACE ({ "beagle", "labrador", "pitbull", "dobermann" })
#define DOG_PRICE ({ 1, 1, 1, 1 })
#define DOG_STATS ({ ({  8,  8,  8, 17, 17,  8 }),\
                     ({ 12, 12, 12, 19, 19, 12 }),\
                     ({ 18, 18, 18, 25, 25, 18 }),\
                     ({ 23, 23, 23, 29, 23, 23 }) })

string pay_type, get_type, coin_pay_text, coin_get_text, *sold_arr;
int *money_arr;

/* Prototypes */
void reset_monster();
int can_afford(int price, string race);

void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"petshop owner", "owner"}));
   set_race_name("owner"); 
   set_adj("petshop");
   set_living_name("_petshop_owner_");
   set_long(break_string(
      "You are looking at the proud owner of the petshop. He has served "
    + "many happy customers and is willing to help you to a dog as "
    + "well.\n",70));

   add_prop(CONT_I_WEIGHT,67000);   /* 67 Kg */
   add_prop(CONT_I_HEIGHT,91);      /* 91 cm */
   add_prop(LIVE_I_NEVERKNOWN,1);

            /* str dex con int wis dis */
   set_stats(({ 22, 27, 23, 12, 14,100}));
   set_skill(SS_UNARM_COMBAT,34);
   set_skill(SS_DEFENCE,34);
   set_pick_up(75);

   set_aggressive(0);
   set_attack_chance(0);
   set_hp(10000); /* Heal fully */

   set_chat_time(14);
   add_chat("Can I be of any help to you?");
   add_chat("Our beagles are really sweet animals.");
   add_chat("Pitbulls are dangerous animals.");
   add_chat("Labradors are excellent companions on the road.");
   add_chat("You can buy a dog here if you want to.");
   add_chat("I sure wouldn't want to be on the wrong side of a Dobermann.");

   /* Triggers */
   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'smirks.\n' %s", "react_smirk");
   trig_new("%w 'sighs' %s", "react_sigh");
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'nods' %s", "react_nod");
   trig_new("%w 'grins' %s", "react_grin");
   trig_new("%w 'giggles' %s", "react_giggle");
   trig_new("%w 'frowns.\n'", "react_frown");
   trig_new("%w 'bows' %s", "react_bow");
   trig_new("%w 'growls.\n' %s", "react_growl");
   trig_new("%w 'growls' %s", "react_growl");
   trig_new("%w 'waves' %s", "react_wave");
   trig_new("%w 'shrugs' %s", "react_shrug");
   trig_new("%w 'spits' %s", "react_spit");
   trig_new("%w 'throws' %w 'head' 'back' 'and' 'cackles' 'with' 'glee!\n' %s",
         "react_cackle");
   trig_new("%w 'falls' 'down' %s", "react_laugh");
   trig_new("%w 'shakes' %w 'head' %s", "react_shake");
   trig_new("%w 'fetches' 'something' 'from' 'another' 'dimension.\n' %s",
         "react_clone");
   trig_new("%w 'patched' 'the' 'internals' 'of' %s", "react_Call");

   /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     0,   0,    0 })); /* Threshold */

   reset_monster();
}

void
reset_monster() {
   sold_arr = ({ });
}

void
init_living() {
   add_action("do_buy","buy",0);
   set_alarm(3.0,0.0,&welcome_player(this_player()->query_gender()));
}

void
welcome_player(int gender) {
   int ran;
   string gen_str, say_str;

   if (this_player()->query_npc())
      return;

   if (gender == G_FEMALE)
      gen_str = "lady";
   else
      gen_str = "sir";

   ran = random(6);
   if (ran == 0)
      say_str = "Welcome to my humble shop, " + gen_str + ".";
   else if (ran == 1)
      say_str = "Be welcome, " + gen_str + ".";
   else if (ran == 2)
      say_str = "Please, do come in, " + gen_str + ".";
   else if (ran == 3)
      say_str = "I am happy to see you here, " + gen_str + ".";
   else if (ran == 4)
      say_str = "Hello, " + gen_str + ". How are you today?";
   else if (ran == 5)
      say_str = "Having a look around, " + gen_str + "?";

   command("say " + say_str);
}
   
      
/********************************************************************
 *
 * Player commands
 */

int
do_buy(string str) {
   int i;
   object pet, certificate, tp;
   string item;

   if (!str)
      return 0;

   /*   Check if the player defines what she wants to pay with
    *   and what you would like in return.
    */
   if (sscanf(str, "%s for %s and get %s",item,pay_type,get_type) != 3)
   {
      get_type = "";
      /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item, pay_type) != 2)
      {
         pay_type = "";
         item = str;
      }
   }

   tp = this_player();
   item = lower_case(item);
   if ((i = member_array(item, DOG_RACE)) == -1)
   {
      if (item == "doggymeal" || item == "meal")
      {
         if (can_afford(20, "doggymeal"))
         {
            if ((pet = clone_object(STAND_OBJ + "doggymeal"))->move(tp))
            {
               command("say You cannot carry that doggymeal.");
               command("say I'll lay it on the counter.");
               pet->move(environment());
            }
            else
               command("say Here you are, one nutricious doggymeal.");
         }
         else
            command("say Harumph... No money, no doggymeal!");

      }
      else
         command("say I don't have any " + item + " for sale, "
               + (tp->query_gender() ? "lady" : "sir") + ".");
      return 1;
   }

   if (can_afford(DOG_PRICE[i], DOG_RACE[i]))
   {
      if (present("_pet_certificate_", tp))
      {
         command("say You already own a dog, "
          + (tp->query_gender() ? "lady" : "sir") + ".");
         return 1;
      }
      command("say Okay, you will get your " + DOG_RACE[i]
          + " in a moment, "
          + (tp->query_gender() ? "lady" : "sir") + ".");
      command("say With it goes this certificate of ownership.");
      command("say You just need to fill in your and the dog's name.");

      certificate = clone_object(STAND_OBJ + "certificate");
      certificate->set_owner_name(tp->query_real_name());
      certificate->set_dog_race(DOG_RACE[i]);
      certificate->set_dog_stats(DOG_STATS[i]);
      certificate->set_dog_total_time(0);

      write(process_string(QCTNAME(this_object()))
          + " gives you a certificate.\n"
          + "You fill in your name, but leave the dog's name blank.\n");
      say(QCTNAME(this_object()) + " gives " + QCTNAME(tp)
        + " a certificate.\n"
        + QCTNAME(tp) + " scribbles something on the certificate.\n");

      certificate->move(tp);
      certificate->lock_object(); /* Make undroppable etc. */

      command("say The dog will be yours when you fill in the name.");
      return 1;
   }
   
   return 0;
}

/*
 *  Test if this_player can afford the price, and perform
 *  the money transactions.
 */
int
can_afford(int price, string race) {
   object tp;

   tp = this_player();

   /* Try to take the money */
   if (sizeof(money_arr = pay(price, tp, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 2)
      {
         command("say You have not got any " + pay_type
          + " coins, " + (tp->query_gender() ? "lady" : "sir") + ".");
         return 0;
      }
      if (money_arr[0] == 1)
      {
         command("say I think that " + race + " is too "
          + "expensive to pay for in " + pay_type + " coins only, "
          + (tp->query_gender() ? "lady" : "sir") + ".");
         return 0;
      }
      else
      {
         command("say I think that " + race + " is too expensive for you, "
          + (tp->query_gender() ? "lady" : "sir") + ".");
         return 0;
      }
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You buy the " + race + " and pay " + coin_pay_text + ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back.\n");
   return 1;
}

string
wizinfo()
{
   return "Guess what? This man sells dogs! :-)\n";
}

/********************************************************************
 *
 *  Some feelings to make the shopowner more vivid.
 *  The feelings are split in two parts: the part that is called by
 *  a trigger function, and a part that is called after a random time.
 *  This is done to get a feeling of reality in the game.
 */

int
react_sigh(string who, string dummy) {
   if (who) {
 call_out("return_sigh", 3, who);
      who = lower_case(who);
      return 1;
   }
}

void
return_sigh(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Why are you depressed, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("comfort " + who);
      if (ran == 2)
         command("say Is life tough for you, " + obj->query_nonmet_name()
               + "?");
   }
}

int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_smile", 3, who);
      return 1;
   }
}

void
return_smile(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Life is great, isn't it, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("smile at " + who);
      if (ran == 2)
         command("say It is great to see you smiling, " + obj->query_nonmet_name()
               + ".");
   }
}

int
react_smirk(string who) {
   if (who) {
      who = lower_case(who);
      call_out("return_smirk", 3, who);
      return 1;
   }
}

void
return_smirk(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I sense irony, " + obj->query_nonmet_name()
               + "...");
      if (ran == 1)
         command("smirk");
      if (ran == 2)
         command("grin at " + who);
   }
}

int
react_grin(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_grin", 3, who);
      return 1;
   }
}

void
return_grin(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say What cunning plan have you forged, "
                     + ((obj->query_gender() == G_MALE) ? "master" : "lady")
               + "?");
      if (ran == 1)
         command("grin");
      if (ran == 2)
         command("say Get that grin off your face, "+ obj->query_race_name() + ".");
   }
}

int
react_introduce(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_introduce", 3, who);
      return 1;
   }
}

void
return_introduce(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
      {
         command("say Nice to meet you, " + obj->query_name() + ".");
         command("bow to " + who);
      }
      if (ran == 1)
      {
         command("bow to " + who);
      }
      if (ran == 2)
      {
         command("say Be welcome, " + obj->query_race_name() + ".");
         command("bow to " + who);
      }
   }
}

int
react_nod(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_nod", 3, who);
      return 1;
   }
}

void
return_nod(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I'm glad you agree, "
               + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 1)
         command("pat " + who);
      if (ran == 2)
         command("say Indeed, " + obj->query_race_name_name() + ".");
   }
}

int
react_shake(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      call_out("return_shake", 3, who);
      return 1;
   }
}

void
return_shake(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say So you disagree, " + obj->query_race_name() + "?");
      if (ran == 1)
         command("say I agree with you, "
               + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         command("say Why do " + LANG_PWORD(obj->query_race_name())
               + " always disagree?");
   }
}

int
react_laugh(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_laugh", 3, who);
      return 1;
   }
}

void
return_laugh(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Very funny indeed...");
      if (ran == 1)
         command("laugh");
      if (ran == 2)
         command("giggle");
   }
}

int
react_growl(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_growl", 3, who);
      return 1;
   }
}

void
return_growl(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You frighten me with your growling, " + obj->query_race_name()
               + "...");
      if (ran == 1)
         command("say Why so hostile, " + obj->query_race_name() + "?");
      if (ran == 2)
         command("frown");
   }
}

int
react_cackle(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      call_out("return_cackle", 3, who);
      return 1;
   }
}

void
return_cackle(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You sound like a duck, " + obj->query_race_name() + ".");
      if (ran == 1)
         command("say " + capitalize(LANG_PWORD(obj->query_race_name()))
               + " cackle very often.");
      if (ran == 2)
         command("giggle");
   }
}

int
react_shrug(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_shrug", 3, who);
      return 1;
   }
}

void
return_shrug(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Is there anything you " + LANG_PWORD(obj->query_race_name())
               + " do know?");
      if (ran == 1)
         command("say Don't look at me... I don't know either!");
      if (ran == 2)
         command("shrug");
   }
}

int
react_bow(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_bow", 3, who);
      return 1;
   }
}

void
return_bow(string who) {
   command("bow " + who);
}

int
react_wave(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_wave", 3, who);
      return 1;
   }
}

void
return_wave(string who) {
   command("wave");
}

int
react_frown(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_frown", 3, who);
      return 1;
   }
}

void
return_frown(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Is something wrong, " + obj->query_race_name());
      if (ran == 1)
         command("say It wasn't my fault!");
      if (ran == 2)
         command("say I had nothing to do with it, I assure you!");
   }
}

int
react_spit(string who, string str) {
   string where;
   if (who) {
      who = lower_case(who);
      if (str[strlen(str)-2] == '.')
         str = str[0..strlen(str)-3];
      else
         str = str[0..strlen(str)-2];

      call_out("return_spit", 3, ({who,str}));
      return 1;
   }
}

void
return_spit(string *arr) {
   string who, where;
   object obj;
   int ran;

   who = arr[0];
   where = arr[1];
   if (obj = present(who, environment())) {
      ran = random(4);
      if (ran == 0)
         command("say Damn " + LANG_PWORD(obj->query_race_name()) + "!");
      if (ran == 1)
         command("say Hey! Don't do that! Don't spit in here!");
      if (ran == 2)
         command("say Hey! Don't spit " + where + "!");
      if (ran == 3)
         command("say " + capitalize(LANG_PWORD(obj->query_race_name()))
               + " are such rude people!");
   }
}

int
react_giggle(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_giggle", 3, who);
      return 1;
   }
}

return_giggle(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Funny, eh " + obj->query_race_name() + "?");
      if (ran == 1)
         command("say Ah, " + LANG_PWORD(obj->query_race_name())
               + " are such merry people.");
      if (ran == 2)
         command("giggle");
   }
}


int
react_clone(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_clone", 3, who);
      return 1;
   }
}

return_clone(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("gasp");
      if (ran == 1)
      if (ran == 1)
      {
         command("say You are mightier than I am!");
         command("grovel " + who);
      }
      if (ran == 2)
      {
         command("say Honour to the great "
               + obj->query_race_name() + " conjurer!");
         command("grovel " + who);
      }
   }
}

int
react_Call(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_Call", 3, who);
      return 1;
   }
}

return_Call(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
      {
         command("grovel " + who);
         command("say Please leave me in one piece, mighty "
                + obj->query_race_name() + " wizard!");
         command("shiver");
      }
      if (ran == 1)
      {
         command("say Hail to the mighty one!");
         command("grovel " + who);
      }
      if (ran == 2)
         command("gasp");
   }
}

