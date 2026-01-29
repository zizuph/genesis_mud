/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/common/lib/logkill.c"

void    get_armed();
string  tell_herb();
string  inform();

void
create_monster() 
{
  set_living_name("funohad");
  set_name("funohad");
  add_name(({"herbalist","man"}));
  set_race_name("human");
  set_adj(({"old","white-haired"}));

  set_long(BSN("This is an old, white-haired rohirrim man. "+
    "Because of his age, he is very weak and weary. " +
    "Dont let his age and strength fool you though. " +
    "With your skilled eyes, you can see that he is a worthy " +
    "opponent to anyone in a fight. " +
    "Perhaps you could ask him if you can 'help' him?"));
  default_config_npc(40+random(20));
  set_base_stat(SS_STR,35);
  set_base_stat(SS_DEX,180);
  set_base_stat(SS_CON,100);
  set_skill(SS_WEP_AXE, random(10)+80);
  set_skill(SS_DEFENCE, random(10)+80);
  set_skill(SS_PARRY, random(10)+70);
  set_skill(SS_UNARM_COMBAT, random(10)+90);
  set_skill(SS_BLIND_COMBAT, random(10)+80);
  set_alignment(300+random(100));
  set_act_time(5);
  set_chat_time(15);
  add_act("smile");
  add_chat("Now how do I do this?");
  add_chat("I really must finish this before the orcs arrive.");

  add_cchat("Get out of here, you filthy scum!");
  add_cchat("You won't get away with this, you know!");
  add_ask(({"do you need help?","help"}),VBFC_ME("inform"));
  add_ask("berries",VBFC_ME("tell_herb"));
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","present me",
  	"say Are you good with fruits and berries, "
      + TP->query_race_name() + "?"}));  
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}

void
get_armed()
{
  FIX_EUID
  clone_object(EDORAS_DIR + "obj/funoaxe")->move(TO);
  clone_object(EDORAS_DIR + "obj/robe")->move(TO);
  command("wear armour");
}

void
attacked_by(object ob)
{
  ::attacked_by(ob);
  command("wield axe");
  command("say You slimy bastard! Why this attack on me?");
  command("shout HELP! Help me against this " + ob->query_race_name() + "!");
}

void
inform3(string who)
{
  command("say If you can bring some here, I will reward you greatly. ");
  command("smile hopeful");
  return;
}

void
inform2(string who)
{
  command("say I'm looking for some very rare berries.");
  command("say I have already looked everywhere, but it's hopeless!");
  command("sigh deeply");
  command("say Rumours are that they might be found close to Dunharrow!");
  set_alarm(20.0, 0.0, &inform3(who));
  return;
}

string
inform()
{
  string who = TP->query_real_name();

  if(TP->test_bit("Gondor",TOUR_GROUP,ROWAN_BERRIES_BIT))
  {
    command("say I don't think that you can help me a second time.");
    return "";
  }
  command("smile");
  command("say Well, if you have the skill, you might be able to help me.");
  command("sigh deeply");
  set_alarm(10.0, 0.0, &inform2(who));
  return "";
}

string
tell_herb()
{
  if(TP->test_bit("Gondor",TOUR_GROUP,ROWAN_BERRIES_BIT))
  {
    command("say Why would you care about my berries again?");
    command("peer at " + TP->query_name() );
    return"";
  }
  command("say The berries?");
  command("say It's told that they grow close to Dunharrow! ");
  command("say When I heard about them from my father, as a young lad, I thought it was just children fairytale.");
  command("say Now I know better though.");
  command("say To me they are invaluable!");
  return"";
}

void
do_thank(object player)
{
  string plname;
  plname = player->query_real_name();
  set_act_time(1);
  LOG_QUEST(player, 0, "DUNHARROW ROWAN BERRIES - ONCE MORE");
  seq_clear("do_things");
  command("say Ah!");
  seq_addfirst("do_things",({"smile at "+plname,"say The berries!",
     "say You found them again? Well done!", "peer at " + plname, 
     "say I guess I have to be thankfull, but it wasnt really needed!",
  	 "think","say Well, thanks, and goodbye!"}));
  player->remove_prop("picked");
}

void
do_add_exp(object player)
{
  string plname;
  seteuid(getuid(TO));
  player->set_bit(TOUR_GROUP,ROWAN_BERRIES_BIT);
  plname = player->query_real_name();
  player->add_exp(ROWAN_BERRIES_EXP,0);
  LOG_QUEST(player, ROWAN_BERRIES_EXP, "DUNHARROW ROWAN-BERRIES");
  tell_object(player,"You feel more experienced.\n");
  player->remove_prop("picked_red_berries");
  command("smile "+plname);
  command("say The berries!");
  command("say You found the berries! This is great news for me!");
  command("hug " + plname);
  command("say I'll be forever grateful for this!");
  command("thank " + plname);
}

void
do_reward(object player)
{
  string plname;
  plname = player->query_real_name();
  set_act_time(1);
  seq_clear("do_things");
  do_add_exp(player);
  command("wave");
}

void
quest_done(object player)
{
  if(player->test_bit("Gondor",TOUR_GROUP,ROWAN_BERRIES_BIT))
    do_thank(player);
  else
    do_reward(player);        
}  

void
do_thank_sus(object player)
{
  string plname;
  plname = player->query_real_name();
  set_act_time(1);
  LOG_QUEST(player, 0, "DUNHARROW ROWAN-BERRIES cheated");
  seq_clear("do_things");
  command("say Ah!");
  seq_addfirst("do_things",({"say The berries!", "peer at " + plname, 
     "say Where did you get theese berries?", "say I have been looking for them all over Rohan!",
     "say Don't tell me that you found it, I know that that is not true!",
     "glare at " + plname,"say I think you should leave Rohan now! ",
     "say And remember, we don't like strangers here in Rohan!"}));
}

int
not_finder(object player)
{
  do_thank_sus(player);
  return 1;
}

void
not_herb(string item_name)
{
  string s1;
  if(item_name == "coin" || sscanf(item_name, "%s coin", s1) == 1)
  {
    command("say Why, thank you, my dear " + TP->query_race_name() + "!");
    command("bow " + TP->query_real_name());
    command("chuckle");
    return;
  }
  command("sigh");
  command("say What shall I do with this " + item_name + "?");
  command("say I don't need it!");
  command("drop " + item_name );
}
  
void
enter_inv(object obj, object from)
{
  string obj_name;
  obj_name = obj->query_name();

  ::enter_inv(obj, from);  

  if (!from)
    return;

  command("examine " + obj_name);
  if (obj->id("berries_from_dunharrow") && from->query_prop("picked_red_berries"))
  {
    set_alarm(2.0, 0.0 &quest_done(from));
    return;
  }
  if (obj->id("berries_from_dunharrow") && !from->query_prop("picked_red_berries"))
  {
    set_alarm(2.0, 0.0 &not_finder(from));
    return;
  }
  if (!obj->id("berries_from_dunharrow"))
  {
    set_alarm(2.0, 0.0 &not_herb(obj_name));
    return;
  }
}
