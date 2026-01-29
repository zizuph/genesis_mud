/*
 * /d/Gondor/ithilien/npc/haradrim1.c
 *
 * Quest Master for Herbs and Stewed Rabbit
 *  copied from Damrod
 *  This Haradrim handles the quest for evil characters
 *
 * Olorin, October 93
 *
 * Revision history:
 * Exchanged call-outs for set-alarms. 960610 /Arren
 */
inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/elessar/lib/evilkill.h"

#define WEAPON		(WEP_DIR + "haradscim")
#define ARMOUR1		(ARM_DIR + "haradcloak")
#define ARMOUR2		(ARM_DIR + "haradshield")
#define ARMOUR3		(ARM_DIR + "corslet")

object  tasker;
int     fire_alert;

void
create_monster()
{
  set_name("haradrim");
  add_name(({"officer","leader","man","soldier","mercenary","haradrim1"}));
  set_race_name("human");
  set_gender(0);
  set_adj("black-skinned");
  set_adj("strong");
  set_stats(({ 70+random(10), 70+random(10), 75+random(10), 70+random(10), 60+random(10), 80+random(10) }));
  set_hp(7000);
  set_mana(1000);
  set_skill(SS_WEP_SWORD,80+random(15));
  set_skill(SS_PARRY,60+random(10));
  set_skill(SS_DEFENCE,60+random(10));
  set_skill(SS_UNARM_COMBAT,60+random(10));
  set_skill(SS_CLIMB,100);
  set_skill(SS_AWARENESS,100);
  set_alignment(-600-random(50));
  set_aggressive(1);
  set_long("@@long_func");
  add_prop(LIVE_I_NEVERKNOWN,1);
  add_prop(CONT_I_HEIGHT,190);
  add_prop(CONT_I_WEIGHT,87000);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  add_chat("I wonder when we will attack Minas Tirith!");
  add_chat("Aye, curse the Rangers!");
  add_chat("I'd like to be back home in Harad!");
  add_chat("We will teach a lesson to those cursed Dunedain!");
  add_chat("A warm meal would be nice now.");
  add_chat("I have a task to do.");
  add_chat("Could you do us a favour?");
  set_cact_time(1);
  set_default_answer(VBFC_ME("default_answer"));
  add_ask(({"help"}), "say Yes, we could need help. Please ask for a task!", 1);
  add_ask(({"favour","favor","task","quest","job","tasks","quests","jobs"}),VBFC_ME("give_task"));
  add_ask(({"for favour","for favor","for task","for quest","for job","for tasks","for quests","for jobs"}),
    VBFC_ME("give_task"));
  add_ask(({"about favour","about favor","about task","about quest","about job","about tasks","about quests","about jobs"}),
    VBFC_ME("give_task"));
  add_ask(({"meal","rabbit","stewed","herbs","warm","coney"}),VBFC_ME("inform_meal"));
  add_ask(({"about meal","about rabbit","about stewed","about herbs","about warm","about coney"}),VBFC_ME("inform_meal"));
  add_ask("gondor",VBFC_ME("inform_gondor"));
  add_ask("ithilien",VBFC_ME("inform_ithilien"));
  add_ask("rangers",VBFC_ME("inform_rangers"));
  add_ask(({"duty","errand"}),VBFC_ME("inform_duty"));
  add_ask(({"southrons","haradrim"}),VBFC_ME("inform_southrons"));
  add_ask(({"harad","south","kingdoms","umbar"}),VBFC_ME("inform_harad"));
  add_ask(({"lord","dark lord","sauron"}),VBFC_ME("inform_sauron"));
  add_ask(({"orcs"}), VBFC_ME("inform_orcs"));
  add_ask(({"enemies","enemy"}), VBFC_ME("inform_enemies"));
  add_ask(({"road"}), VBFC_ME("inform_road"));
  add_ask(({"fire","campfire","firewood"}),VBFC_ME("inform_fire"));
  add_prop("_ithilien_thicket_found_rock",1);
  add_prop("_ithilien_thicket_look_branch",1);
  fire_alert = 0;
  enable_reset();
}

reset_monster()
{
  fire_alert = 0;
  tasker = 0;
}

void
arm_me()
{
    FIX_EUID
    clone_object(WEAPON)->move(TO);
    command("wield all");
    clone_object(ARMOUR1)->move(TO);
    clone_object(ARMOUR2)->move(TO);
    clone_object(ARMOUR3)->move(TO);
    command("wear all");
}

string
long_func()
{
  return BSN("You are looking at a strong black-skinned Haradrim. " +
    "His home is the land Harad far south of Gondor. He looks like " +
    "a soldier or mercenary, and his confident air tells you that he must be " +
    "an officer. He is probably in the service of the Dark Lord. ");
}

do_attack(object victim)
{
  if(query_attack())
    return;
  if (!present(victim,ENV(TO))) return;
    command("mask me");
  command("kill "+victim->query_real_name());
}

check_player(object player)
{
  if(!IS_EVIL(player))
  {    
    command("say Die, foul creature!");
    do_attack(player);
    return 0;
  }
  return 1;
}

default_answer()
{
  if(!check_player(TP)) return "";
  command("say I do not know what you are talking about, " + TP->query_race_name() + ".");
  return "";
}

give_task()
{
  int q;
  if (!TP->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT)) herbs_and_stewed_rabbit();
  else {
    command("say I'm sorry - I have no more tasks for you.");
    }
  return "";
}

inform_meal()
{
  if(!check_player(TP)) return ""; 
  command("unmask me");
  if (TP->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT))
  {
    command("say I'm afraid you cannot help us anymore!");
    return "";
  }
  command("sigh");
  command("say Can't you smell the herbs?");
  command("emote hungrily licks his lips.");
  command("say We have been on duty here on this oak for two days.");
  command("say We'd both love to have a warm meal.");
  command("say Perhaps some stewed rabbit, with some herbs, ");
  command("say and don't forget the salt. Never try to make a ");
  command("say stew without salt! It wouldn't work!");
  command("say If you need help with the fire, then ask me.");
  TP->add_prop("_haradrim1_rabbit_start",1);
  return "";
}

light_fire(object player)
{
  object fire;

  fire = clone_object(RANGER_DIR + "obj/firewood");
  fire->move(ENV(TO));
  command("emote gathers some firewood and stacks it up to make a campfire.");
  fire->add_burn_time(800);
  fire->add_prop(OBJ_M_NO_GET,1);
  command("climb rock");
  command("climb tree");
  command("climb up");
  command("climb up");
  return;
}

make_fire(object player)
{
  if(!present("pot",player))
  {
    command("say Why don't you get a pot first?");
    command("say You cannot make a stew without a pot, can you?");
    command("peer " + player->query_real_name());
    return;
  }
  command("say I'll climb down and will make a fire at the foot of this tree.");
  command("say But take care that the fire doesn't start smoking!");
  command("say And extinguish when you don't need it anymore!");
  tasker = player;
  command("climb down");
  command("climb down");
  command("climb down");
  command("climb down");
  command("emote starts searching for firewood for a campfire.");
  set_alarm(60.0, 0.0, &light_fire(player));
}

inform_fire()
{
  if(!check_player(TP)) return ""; 

  if(fire_alert || TP->query_prop("_left_fire_unattended"))
  {
    command("say Fire?");
    command("peer " + TP->query_real_name());
    command("say I don't want to see any fire here anymore!");
    command("say Someone left a fire unattended at the foot of this tree!");
    if(TP->query_prop("_left_fire_unattended"))
    {
      command("say And I suspect that it was you!");
      command("point " + TP->query_real_name());
    }
    command("say That was extremely stupid and endangered our mission!");
    command("say I won't help anyone making a fire anymore!");
  }
  else if(TP->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT))
  {
    command("cackle");
    command("say Why should I make a fire for you?");
  }
  else if(!TP->query_prop("_haradrim1_rabbit_asked_fire"))
  {
    command("say I will climb down the tree and make a small fire ");
    command("say once you have all the ingredients for the rabbit stew.");
    command("say If you are ready, just ask me again.");
    TP->add_prop("_haradrim1_rabbit_asked_fire",1);
  }
  else
  {
    if(!TP->query_prop("_haradrim1_rabbit_start"))
    {
      command("say What do you want?");
      command("say Why should I make a fire for you?");
      command("say Perhaps you should ask for a task first?");
    }
    else
      set_alarm(2.0, 0.0, &make_fire(TP));
  }
  return "";
}

inform_gondor()
{
  if(!check_player(TP)) return "";
  command("spit");
  command("say These damned Gondorians have been waging war against us for ages!");
  command("say But now we will get even!");
  command("grin");
  command("say Not long any more and we will cross the Anduin!");
  command("say Then we will plunder Minas Tirith, and Gondor will be history!");
  command("cackle");
  return "";
}

inform_ithilien()
{
  if(!check_player(TP)) return "";
  command("say Once the cursed Gondorians lived here.");
  command("say But now Ithilien has been freed from them.");
  command("say Once Minas Tirith has been destroyed, we Haradrim will come to Ithilien and settle here!");
  command("smile");
  return "";
}

inform_rangers()
{
  if(!check_player(TP)) return "";
  command("spit");
  command("say Rangers? You mean those dirty tramps from Gondor that can't realize ");
  command("say that they don't have any business here anymore!");
  command("say They are a pain in the ass, but of no consequence.");
  command("say Stupid fools, courting death, nothing more!");
  return "";
}

inform_duty()
{
  if(!check_player(TP)) return "";
  command("sigh");
  command("say We are here on duty on lookout for reinforcements that will come up on the road.");
  command("say We are to warn them that the cursed rangers are planning some crazy ambush.");
  command("say We've been here for two days, because that fool of a Captain probably has forgotten us!");
  return "";
}

inform_southrons()
{
  if(!check_player(TP)) return "";
  command("say We Haradrim have been living in Middle Earth far longer than those cursed Gondorians!");
  command("say Out home is Harad, in the South!");
  command("smile");
  command("say Where the sun always smiles, and where the mightiest men and beasts of the world dwell!");
  command("say We are true allies of the Dark Lord!");
  command("say We are not His servants, we are just combining our forces to destroy Gondor!");
  return "";
}

inform_harad()
{
  if(!check_player(TP)) return "";
  command("say Beautiful Harad, our home, lies south of the Harnen, far south of Ithilien!");
  command("say The mightiest men and beasts of the world dwell there!");
  command("say The Kingdoms of Harad are much older than Gondor!");
  command("say And there has never been friendship between those cursed dunedain and Harad!");
  return "";
}

inform_sauron()
{
  if(!check_player(TP)) return "";
  command("say The Dark Lord is our ally in the war against Gondor.");
  command("say He is helpful, because He has some resources of His own, like the orc bands.");
  command("say But he does not control us, and we only follow him where we want.");
  command("say As long as we fight the same enemy, His help is welcome.");
  return "";
}

string inform_orcs()
{
  if(!check_player(TP)) return "";
  command("say Those orcs stink, and they are foul creatures, but they are useful.");
  command("say After the war, we will destroy them, or chase them away into the north.");
  command("say I have no love for them, but it's nice when they help us kill a few Gondorians!");
  command("say But they are no good, and treacherous!");
  return "";
}

string inform_enemies()
{
  if(!check_player(TP)) return "";
  command("spit");
  command("say We fight the Gondorians and whatever creatures ally with those cursed dunedain!");
  return "";
}

string inform_road()
{
  if(!check_player(TP)) return "";
  command("say We are watching the road the comes up from Harad.");
  command("say It leads further north to Minas Morgul and the Morannon, the Black Gate of Mordor.");
  command("grin");
  command("say Yeah, the cursed dunedain built this little road, and we use it to march up ");
  command("say from Harad to make war on Minas Tirith!");
  command("cackle");
  command("say Serves them right, they built the road to threaten us, now they have to pay for it!");
  return "";
}

return_item(object *arr)
{
  object ob, from;

  ob = arr[0];
  from = arr[1];

  ob->move(from);
  command("say Thank you, but I don't believe I can use that!");
  write(process_string(QCTNAME(TO)) + " gives " + LANG_ADDART(ob->query_name()) + " back to you.\n");
  say(QCTNAME(TO) + " gives " + LANG_ADDART(ob->query_name()) + " back to " + QTNAME(from) + ".\n");
}

tell_ask(object player)
{
  command("say Perhaps you should ask for a task first?");
  command("peer " + player->query_real_name());
  return;
}

tell_fire(object player)
{
  command("say Someone left a fire unattended at the foot of this tree!");
  command("suspicious " + player->query_real_name());
  command("say I suspect that it was you!");
  command("say Anyway, it was very foolish, and endangered us and our mission!");
}

reject_item(object *arr)
{
  object ob, from;

  ob = arr[0];
  from = arr[1];

  ob->move(from);
  command("say No, thank you!");
  command("say We won't take anything from you!");
  write(process_string(QCTNAME(TO)) + " gives " + LANG_ADDART(ob->query_name()) + " back to you.\n");
  say(QCTNAME(TO) + " gives " + LANG_ADDART(ob->query_name()) + " back to " + QTNAME(from) + ".\n");
}

quest_done(object player)
{
  int reward, pexp;
  object haradrim2, pot;

  if(!present(player,ENV(TO))) return 0;

  if(haradrim2 = present("haradrim2",ENV(TO)))
    tell_room(ENV(TO), "Finally, " + QTNAME(TO) + " and " + QTNAME(haradrim2) + " seem to have finished eating.\n");
  else
    tell_room(ENV(TO), "Finally, " + QTNAME(TO) + " seems to have finished eating.\n");
  command("say Hmmm, that was delicious!");
  command("emote licks his lips.");
  command("thank " + player->query_real_name());
  command("shake " + player->query_real_name());
  if(pot = present("pot",TO))
  {
    pot->move(player);
    write(process_string(QCTNAME(TO)) + " gives " + LANG_ADDART(pot->query_name()) + " back to you.\n");
    say(QCTNAME(TO) + " gives " + LANG_ADDART(pot->query_name()) + " back to " + QTNAME(player) + ".\n");
  }
  if (!player->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT)) 
  {
    reward = RABBIT_STEW_EXP;
    pexp = player->query_exp();
    if(pexp < reward) reward = pexp;
    player->set_bit(GONDOR_GROUP, RABBIT_STEW_BIT);
    player->adjust_alignment(-250);
    player->add_exp(reward, 0);
    LOG_QUEST(player, reward, "STEWED RABBIT (HARADRIM)");
    tell_object(player, "You feel much more experienced.\n");
    player->remove_prop("_haradrim1_rabbit_start");
    player->remove_prop("_haradrim1_rabbit_asked_fire");
  }
  return 1;
}

return_pot(object pot, object player)
{
  command("emote shakes his head in disappointment.");
  pot->move(player);
  write(process_string(QCTNAME(TO)) + " gives " + LANG_ADDART(pot->query_name()) + " back to you.\n");
  say(QCTNAME(TO) + " gives " + LANG_ADDART(pot->query_name()) + " back to " + QTNAME(player) + ".\n");
  return;
}

no_rabbit(object pot, object player)
{
  if(!present(player,ENV(TO))) return 0;

  command("peer " + player->query_real_name());
  command("say Well, I had supposed to find at least a rabbit in the pot!");
  return_pot(pot,player);
  command("say Next time, try to put a rabbit into it!");
  return 1;
}

not_stewed(object pot, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("peer " + player->query_real_name());
  command("say Couldn't you stew the rabbit?");
  command("say I don't like it like this, eat it yourself!");
  return_pot(pot,player);
  return 1;
}

poisoned(object pot, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("glare " + player->query_real_name());
  command("say That rabbit stinks incredibly!");
  command("say Do you want to poison us?");
  if(pot->query_dirty())
  {
    command("say I don't know where you found that pot, ");
    command("say but you should have cleaned it before cooking in it!");
  }
  else
  {
    command("say What poisoned water did you use to cook that rabbit?");
  }
  return_pot(pot,player);
  command("say Go now, and don't come back with another rabbit!");
  command("say We don't have any hunger any more for what you can prepare!");
  player->add_prop("_gave_poisoned_food",1);
  return 1;
}
  
eat_no_reward(object *arr)
{
  object haradrim2, pot, meal, player;
  pot = arr[0];
  meal = arr[1];
  player = arr [2];

  if(haradrim2 = present("haradrim2",ENV(TO)))
    command("emote shares the rabbit stew with " + process_string(QTNAME(haradrim2)) + ".");
  command("emote starts eating the rabbit stew.");
  if(haradrim2)
    tell_room(ENV(haradrim2),process_string(QTNAME(haradrim2)) + " starts eating the rabbit stew.\n");
  meal->remove_object();
  command("sigh");
  command("say Well, it was nourishing, but to be honest, it wasn't the meal we've been waiting for!");
  if(!present(player,ENV(TO))) return;
  return_pot(pot,player);
  return;
}

no_salt(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("peer " + player->query_real_name());
  command("say How can you make a stew without salt?");
  command("sigh");
  command("say Well, it was an attempt, but a stew without salt ... ");
  command("say It's just terrible!");
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

no_herb(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("peer " + player->query_real_name());
  command("say All around you herbs are growing!");
  command("say And you prepare a stew without using a single one!");
  command("sigh");
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

no_rabbit_herb(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("emote sniffs at the stew in the pot.");
  command("say Well, almost, but when you cook a rabbit ");
  command("say you should use some fitting herbs!");
  command("say Like basil, savory, or tarragon!");
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

no_stew_herb(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("emote sniffs at the stew in the pot.");
  command("say Well, almost, but when you prepare a stew ");
  command("say you should use some fitting herbs!");
  command("say Why didn't you try to find some chervil?");
  command("say Or ginger and laurel, perhaps?");
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

int
extra_herb(object pot, object meal, object player, string extra_herb_name)
{
  if(!present(player,ENV(TO))) return 0;
  command("emote sniffs at the stew in the pot.");
  command("say Well, almost, but why did you put in " + extra_herb_name + "?");
  command("emote shakes his head.");
  command("say You know, some herbs are just right for stews, ");
  command("say like chervil, ginger, or laurel. Others are right whenever ");
  command("say you are preparing rabbit meat, like basil, savory, and tarragon.");
  command("say But to put " + extra_herb_name + " into a rabbit stew, ");
  command("say that's some strange taste!");
  command("sigh");
  command("say Well, one cannot have anything!");
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

not_hot(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("emote sniffs at the stew in the pot.");
  command("say That looks rather good!");
  command("say But why isn't it hot anymore?");
  command("sigh");
  command("say Well, one cannot have anything!");
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
}

eating3(object meal)
{
  object haradrim2;
  if(haradrim2 = present("haradrim2",ENV(TO)))
    command("emote and " + process_string(QTNAME(haradrim2)) + " are silently eating the rabbit stew.");
  else
    command("emote is silently eating the rabbit stew.");
  meal->remove_object();
}

eating2(object meal)
{
  object haradrim2;
  if(haradrim2 = present("haradrim2",ENV(TO)))
  {
    command("emote shares the rabbit stew with the " + haradrim2->query_nonmet_name() + ".");
    haradrim2->command("unmask me");
  }
  command("say You must be a great cook! This tastes delicious!");
  command("say And the herbs ..... ");
  command("say I can taste " + meal->query_prop("_rabbit_herb_added_to_stew") +
    " and " + meal->query_prop("_stew_herb_added_to_stew") + "!");
  command("say Perfect!");
  set_alarm(5.0, 0.0, &eating3(meal));
  return;
}

eating(object meal)
{
  command("unmask me");
  command("emote sniffs at the stew in the pot.");
  command("sigh");
  command("say Perfect!");
  command("emote starts eating the rabbit stew.");
  set_alarm(5.0, 0.0, &eating2(meal));
}

test_quest_done(object *arr)
{
  object ob, player, meal;
  string extra_herb_name;

  ob = arr[0];
  player = arr[1];

  if (!(meal=present("rabbit",ob)))
    no_rabbit(ob, player);
  else if(meal->query_adj() != "stewed")
    not_stewed(ob, player);
  else if(meal->query_prop("_poisoned"))
    poisoned(ob,player);
  else if(!meal->query_prop("_salt_added_to_stew"))
    no_salt(ob, meal, player);
  else if(!meal->query_prop("_herb_added_to_stew"))
    no_herb(ob, meal, player);
  else if(!meal->query_prop("_rabbit_herb_added_to_stew"))
    no_rabbit_herb(ob, meal, player);
  else if(!meal->query_prop("_stew_herb_added_to_stew"))
    no_stew_herb(ob, meal, player);
  else if(extra_herb_name = meal->query_prop("_extra_herb_added_to_stew"))
    extra_herb(ob,meal,player,extra_herb_name);
  else if(meal->query_prop("_not_hot_any_more"))
    not_hot(ob,meal,player);
  else
  {
    set_alarm(1.0, 0.0, &eating(meal));
    set_alarm(15.0, 0.0, &quest_done(player));
  }
  return;
}

public void
init_attack()
{
  if(query_attack())
    return;
  if(!IS_EVIL(TP))
  {
    command("say Die, foul creature!");
    set_alarm(2.0, 0.0, &do_attack(TP));
  }
}

void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(TO, ob);
}

void
help_friend(object ob)
{
  if (ob && !query_attack() && present(ob, ENV(TO)))
  {
    command("say Die, foul creature!");
    do_attack(ob);
  }
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    set_alarm(itof(random(5)), 0.0, &help_friend(attacker));
}

herbs_and_stewed_rabbit()
{
  set_alarm(4.0, 0.0, inform_meal);
  return;
}

int
stop_fleeing(object player)
{
  object haradrim2;
  if(!present(player, ENV(TO))) return 1;
  if(player->query_attack())
    return 0;
  write(process_string(QCTNAME(TO)) + " stops you.\n");
  say(QCTNAME(player) + " tries to climb down, but is stopped by " + QCTNAME(TO) + ".\n");
  command("say Die, stupid " + player->query_race_name() + "!");
  do_attack(player);
  if(haradrim2 = present("haradrim2",ENV(TO)))
    haradrim2->do_attack(player);
  return 1;
}

fire_alarm()
{
  object *cont;

  command("say Where is that smoke coming from?");
  command("emote curses silently.");
  command("say It will betray us to the orcs!");
  if(tasker)
    tasker->add_prop("_left_fire_unattended", 1);
  fire_alert = 1;
  
  command("climb down");
  command("climb down");
  command("climb down");
  command("climb down");
  command("extinguish fire");
  command("climb rock");
  command("climb tree");
  command("climb up");
  command("climb up");
  command("say I extinguished that fire!");
  command("say Let's hope that no one noticed the smoke!");
  command("say If I only knew who left that fire unattended!");
  if(tasker)
    command("say But I suspect it was " + process_string(QTNAME(tasker)));
  return;
}

query_fire_alert()
{
  return fire_alert;
}

/* Solamnian prestige */
query_knight_prestige() {return (150);}

enter_inv(object ob, object from)
{
  object pot;

  ::enter_inv(ob,from);

  if(!ob) return;
  if(!from) return;
  if(!interactive(from)) return;
  if(from->query_prop("_gave_poisoned_food"))
  {
    set_alarm(1.0, 0.0, &reject_item(({ob, from})));
    return;
  }
  if(!check_player(from))
  {
    set_alarm(1.0, 0.0, &return_item(({ob, from})));
    return;
  }
  pot = present("_stewed_rabbit_quest_pot",TO);
  if (pot && pot == ob) 
  {
    if(!from->query_prop("_haradrim1_rabbit_start"))
    {
      set_alarm(1.0, 0.0, &return_item(({ob, from})));
      set_alarm(4.0, 0.0, tell_ask);
    }
    else if(fire_alert || from->query_prop("_left_fire_unattended"))
    {
      set_alarm(4.0, 0.0, &tell_fire(from));
    }
    else
      set_alarm(1.0, 0.0, &test_quest_done(({ob, from})));
  }
  else
    set_alarm(1.0, 0.0, &return_item(({ob, from})));
  return;
}
