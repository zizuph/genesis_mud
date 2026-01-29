/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";
inherit "/std/act/action";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>

#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/defs.h"

void    return_object(object obj, object from);

string *hints;

void
create_monster() 
{
  set_name(({"drunkard","drunk"}));
  set_race_name("human");
  set_adj(({"drunken","smelly"}));
  set_gender(0);
  set_alignment(15);
  set_long("This is a smelly rohirrim man, seemingly constantly drunk.\n"+
	   "His long, blond hair is unkempt, and he has a dirty, five-day\n"+
	   "old beard, and seems to be thinking only about one thing: Beer.\n");
  default_config_npc(28);
  set_base_stat(SS_CON,45);
  set_hp(600);
  set_skill(SS_WEP_KNIFE, random(10)+40);
  set_skill(SS_PARRY,45);
  set_skill(SS_DEFENCE,50);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  set_chat_time(7);
  set_act_time(7);
  add_act("burp");
  add_act("say I think I'll have another beer.");
  add_act("hiccup");
  add_act("say Hey, why don't you buy me a beer, friend?");
  add_act("say It would be nice with a beer now.");
  add_act("say I think life would be worsche without alcohol.");
  add_act("say Perschonally I don't think there'sch ever gonna be a war.");
  add_act("burp");
  add_act("hiccup");
  add_act("say I don't like the thought of a war though.");
  add_act("sigh");
  add_act("say I really wouldn't mind a beer now.");
  add_act("drink beer");
  add_act("say How about buying me a beer, pal?");
  add_act("buy beer");
  add_act("drink beer");
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Oh, a beer would be fine now.","buy beer","drink beer","say Ah...that's better!"}));  
}

void
setup_hints()
{
  hints = ({
    "The Gondorian Rangers have their Guildhouse in the Druedain Forest!",
    "You might be able to enter Edoras at night through the sewers!",
    "If you're tired of walking, you could travel by horse-wagon to Minas Tirith!",
    "Take it from me: The Gondorian Rangers are the best trackers around!",
    "Be careful with the herbs you find in the wilderness, might be poison!",
    "Wanna find the Gondorian Rangers? Find their track in the Druedain Forest!",
    "Be careful when adventuring in the White Mountains! There are trolls there!",
    "When you find a golden ring here in Edoras, give it to Funohed in the Sleeping Stallion. He has lost his ring!",
    "Bands of dunlendings are attacking farms in the vales north of the White Mountains.",
    });

  return;
}

void
get_armed()
{
  object wep, coins;
  seteuid(getuid(this_object()));
  wep = clone_object(WEP_DIR + "dagger");
  wep->move(this_object());
  command("wield knife");
  coins = MONEY_MAKE_CC(120);
  coins->move(this_object());
  setup_hints();
}

/* solemnian prestige */
query_knight_prestige() {return -1;}

int
give_hint(object player)
{
  string name,hint;
  int i;
  name = player->query_real_name();
  i = random(sizeof(hints));
  hint = hints[i];
  set_act_time(2);
  seq_addfirst("do_things",({"whisper "+name+" Thanks, pal! Let me tell you something...",
    "drink beer","whisper "+name+" "+hint,"hiccup","smile "+name,"burp"}));
  set_act_time(8);
  return 1;
}

void
return_object(object obj, object from)
{
  string s1;

  if (obj->id("coin"))
  {
    command("giggle");
    command("bow " + from->query_real_name());
    command("say Thanks a lot, I will liquify this coin!");
    return;
  }
  command("say Ah, nah! I don't want that!");
  obj->move(from);
  write(process_string(QCTNAME(TO)) + " gives back the "+obj->short()+" to you.\n");
  say(QCTNAME(TO) +" gives "+LANG_ADDART(obj->query_name())+" to "+
    QTNAME(TP) + ".\n");
  return;
}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj, from);
  if(!from || !living(from)) return;
  if(obj->query_name() == "beer" || (obj->query_name() == "drink" && present("beer",TO)))
    {
      set_alarm(5.0, 0.0, &give_hint(from));
      return;
    }
  else
  {
    set_alarm(1.0, 0.0, &return_object(obj, from));
    return;
  }
}
