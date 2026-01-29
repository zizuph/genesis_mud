inherit "/std/monster";
#include "/d/Gondor/elessar/lib/goodkill.h"
inherit "/std/act/action";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/money.h"

string *hints;

create_monster() 
{
  if (!IS_CLONE)
    return;
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
  set_chat_time(7);
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
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Oh, a beer would be fine now.","buy beer","drink beer","say Ah...that's better!"}));  
}

get_armed()
{
  object wep, coins;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/elessar/obj/wep/dagger");
  wep->move(this_object());
  command("wield knife");
  coins = MONEY_MAKE_CC(120);
  coins->move(this_object());
  setup_hints();
}

enter_inv(obj, from)
{
  ::enter_inv(obj, from);
  if (obj == present("beer",this_object()) && living(from))
    {
      call_out("give_hint",5,from);
      return;
    }
}

give_hint(object player)
{
  string name,hint,i;
  name = player->query_real_name();
  i = random(sizeof(hints));
  hint = hints[i];
  seq_addfirst("do_things",({"whisper "+name+" Thanks, pal! Let me tell you something...",
    "drink beer","whisper "+name+" "+hint,"hiccup","smile "+name,"burp"}));
  return 1;
}

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
    });
}


