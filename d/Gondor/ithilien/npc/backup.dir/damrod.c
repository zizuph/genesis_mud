/*
 * /d/Gondor/ithilien/npc/damrod.c
 *
 * Quest Master for Herbs and Stewed Rabbit
 *
 * Olorin, April 93
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

public  string  inform_meal();
public  int     arrest(object player);
public  int     badge_test(object player);
public  int     ranger_test(object player);
int quest_done(object player);
int no_rabbit(object pot, object player);
int no_rabbit_herb(object pot, object meal, object player);
int not_stewed(object pot, object player);
int poisoned(object pot, object player);
int no_salt(object pot, object meal, object player);
int no_herb(object pot, object meal, object player);
int no_stew_herb(object pot, object meal, object player);
int extra_herb(object pot, object meal, object player, string extra_herb_name);
int not_hot(object pot, object meal, object player);
public  void    return_item(object ob, object from);
void make_fire(object player);
void reject_item(object *arr);
void tell_ask(object player);
void tell_fire(object player);
void test_quest_done(object *arr);
void eating(object meal);
void eating2(object meal);
void eating3(object meal);
void do_attack(object victim);
void help_friend(object ob);
void call_faramir(object player);
void come_faramir(object player);
void light_fire(object player);
void eat_no_reward(object *arr);

object  tasker;
int     fire_alert;
int     cf_aid,
        cof_aid,
        lf_aid;

void
create_monster()
{
  set_name("damrod");
  add_name("man");
  add_name("ranger");
  add_name("dunadan");
  set_living_name("damrod");
  set_title("the Sergeant of the Rangers of Ithilien");
  set_race_name("human");
  set_gender(0);
  set_adj("grey-eyed");
  set_adj("strong");
  set_stats(({ 70+random(10), 70+random(10), 75+random(10), 70+random(10), 60+random(10), 80+random(10) }));
  set_base_stat(SS_OCCUP, 66);
  set_hp(7000);
  set_mana(1000);
  set_skill(SS_WEP_SWORD,80+random(15));
  set_skill(SS_PARRY,60+random(10));
  set_skill(SS_DEFENCE,60+random(10));
  set_skill(SS_UNARM_COMBAT,60+random(10));
  set_skill(SS_CLIMB,100);
  set_skill(SS_AWARENESS,100);
  set_skill(SS_BRAWLING,80+random(20));
  set_skill(SS_HEARING,80+random(20));
  set_alignment(600+random(50));
  set_aggressive(1);
  set_long("@@long_func");
  add_prop(CONT_I_HEIGHT,190);
  add_prop(CONT_I_WEIGHT,87000);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  add_chat("Faramir is the Captain of the Rangers of Ithilien.");
  add_chat("Aye, curse the Southrons!");
  add_chat("We seldom come so far afield, but we have an errand here.");
  add_chat("We will teach a lesson to those cursed Southrons!");
  add_chat("A warm meal would be nice now.");
  add_chat("Beautiful Ithilien, oh why had you to fall under the power of the Enemy!");
  add_chat("I have a task to do.");
  add_chat("Could you do us a favour?");
  add_chat("The Southrons come marching up the ancient roads to swell the hosts of the Dark Tower.");
  set_cact_time(1);
  add_cact("brawl");
  set_default_answer(VBFC_ME("default_answer"));
  add_ask(({"favour","favor","task","quest","job","tasks","quests","jobs"}),VBFC_ME("give_task"));
  add_ask(({"for favour","for favor","for task","for quest","for job","for tasks","for quests","for jobs"}),
    VBFC_ME("give_task"));
  add_ask(({"about favour","about favor","about task","about quest","about job","about tasks","about quests","about jobs"}),
    VBFC_ME("give_task"));
  add_ask(({"meal","rabbit","stewed","warm","coney"}),VBFC_ME("inform_meal"));
  add_ask(({"about meal","about rabbit","about stewed", "about warm","about coney"}),VBFC_ME("inform_meal"));
  add_ask(({"recipe", "ingredients", }), VBFC_ME("inform_recipe"));
  add_ask(({"herbs", "about herbs", }), VBFC_ME("inform_herbs"));
  add_ask("name",VBFC_ME("introduce_me"));
  add_ask("gondor",VBFC_ME("inform_gondor"));
  add_ask("ithilien",VBFC_ME("inform_ithilien"));
  add_ask("north",VBFC_ME("inform_north"));
  add_ask(({"faramir","captain"}), "say Faramir is our Captain! He leads now in all perilous ventures.",1);
  add_ask("rangers",VBFC_ME("inform_rangers"));
  add_ask(({"duty","errand"}),VBFC_ME("inform_duty"));
  add_ask(({"southrons","haradrim"}),VBFC_ME("inform_southrons"));
  add_ask(({"harad","south","kingdoms","umbar"}),VBFC_ME("inform_harad"));
  add_ask(({"enemy","evil","sauron"}),VBFC_ME("inform_enemy"));
  add_ask(({"orcs"}), VBFC_ME("inform_orcs"));
  add_ask(({"enemies",}), VBFC_ME("inform_enemies"));
  add_ask(({"road"}), VBFC_ME("inform_road"));
  add_ask(({"fire","campfire","firewood"}),VBFC_ME("inform_fire"));
  add_prop("_ithilien_ridge_found_rock",1);
  add_prop("_ithilien_ridge_look_branch",1);
  fire_alert = 0;
  enable_reset();
}

public void
reset_monster()
{
  fire_alert = 0;
  tasker = 0;
}

public void
arm_me()
{
    FIX_EUID;

    clone_object(RANGER_DIR + "ramulet")->move(TO);
    command("wear amulet");

    clone_object(RANGER_DIR + "spells/obj/pigeon_ob")->move(TO);
    set_alarm(1.0, 0.0, &command("whistle for pigeon"));

    clone_object("/d/Gondor/ithilien/obj/rlsword")->move(TO);
    command("wield longsword");

    clone_object("/d/Gondor/ithilien/obj/rcloak")->move(TO);
    clone_object("/d/Gondor/ithilien/obj/rhood")->move(TO);
    clone_object("/d/Gondor/ithilien/obj/rgauntlets")->move(TO);
    command("wear all");
    command("wear hood");
    command("mask me");
}

string
long_func()
{
  return BS("He is a pale-skinned man, dark of hair, with grey eyes, and a proud and sad " +
  "face. You realize that he must be one of the Dunedain of the South, a man of the line of the Lords " +
  "of Westernesse. \n");
}

public int
send_pigeon()
{
  object pigeon;

  if(!(pigeon = present("pigeon",TO))) 
  {
    command("whistle for pigeon");
    return 0;
  }
  
  tell_room(ENV(TO), QCTNAME(TO) + " gives a message to " + TO->query_possessive() + " pigeon.\n");
  tell_room(ENV(TO),
    "The white carrier pigeon flaps its wings and flies up to the sky.\n");
  tell_room(ITH_DIR + "nforest/ridge2",
    BS("Suddenly, you notice a pigeon flying from the top of one of the two " +
    "giant cedars standing to the west. \n"));
  pigeon->remove_object();
  return 1;
}
  
public int
check_player(object player)
{
  if (IS_EVIL(player) || player->query_prop("_no_pass_to_ithilien"))
  {    
    command("say Die, foul creature!");
    do_attack(player);
    return 0;
  }
  else if(!badge_test(player))
  {
    command("say We will not answer any of your questions!");
    return 0;
  }
  else
    command("unmask me");
  return 1;
}

public int
badge_test(object player)
{
  object badge;

  if(ranger_test(TP)) return 1;
  if(!(badge = present("_ithilien_badge",player)))
  {
    command("mask me");
    command("say You are here without the leave of the Steward of Gondor,");
    command("say " + player->query_nonmet_name() + "!");
    arrest(TP);
    return 0;
  }
  else if(badge->query_prop("_ithilien_leave_name") != player->query_real_name())
  {
    command("mask me");
    command("say That badge doesn't belong to you!");
    write(QCTNAME(TO) + " takes away your badge.\n");
    badge->move(TO);
    say(QCTNAME(TO) + " takes away a badge from " + QCTNAME(TP) + ".\n");
    command("emote breaks the badge.");
    badge->remove_object();
    TP->add_prop("_no_pass_to_ithilien",1);
    command("say Die, foul spy!");
    do_attack(player);
    return 0;
  }
  else if(player->query_prop("_no_pass_to_ithilien"))
  {
    command("mask me");
    command("say You are here against the Law of the Steward of Gondor!");
    command("say There is only one punishment, ");
    command("say and that is death!");
    do_attack(player);
    command("say Die, traitor!");
    return 0;
  }
  else
    return 1;
}

public string
default_answer()
{
  if(!check_player(TP)) return "";
  command("say I do not know what you are talking about, " + TP->query_race_name() + ".");
  return "";
}

public string
introduce_me()
{
  if (!check_player(TP)) return "";
  command("unmask me");
  command("say My name is Damrod.");
  command("hail " + TP->query_real_name());
  command("introduce me");
  return "";
}

public string
give_task()
{
    int q;
    if (!TP->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT)) 
        set_alarm(4.0, 0.0, inform_meal);
    else 
        command("say I'm sorry - I have no more tasks for you.");
    return "";
}

string
inform_meal()
{
  if(!check_player(TP)) return ""; 
  command("unmask me");
  if (TP->test_bit("Gondor",GONDOR_GROUP, RABBIT_STEW_BIT))
  {
    command("say I'm afraid you cannot help us anymore!");
    return "";
  }
  command("sigh");
  command("say Can't you smell the herbs?");
  command("emote hungrily licks his lips.");
  command("say We have been on duty here on this cedar for two days.");
  command("say We'd both love to have a warm meal.");
  command("say Perhaps some stewed rabbit, with some herbs, ");
/*
  command("say perhaps some carrots or potatoes, ");
*/
  command("say and don't forget the salt. Never try to make a ");
  command("say stew without salt! It wouldn't work!");
  command("say If you need help with the fire, then ask me.");
  TP->add_prop("_damrod_rabbit_start",1);
  return "";
}

public string
inform_fire()
{
    if (!check_player(TP)) 
	return ""; 

    if (fire_alert || TP->query_prop("_left_fire_unattended"))
    {
	command("say Fire?");
	command("peer " + TP->query_real_name());
	command("say I don't want to see any fire here anymore!");
	command("say Someone left a fire unattended at the foot of this tree!");
	if (TP->query_prop("_left_fire_unattended"))
	{
	    command("say And I suspect that it was you!");
	    command("point " + TP->query_real_name());
	}
	command("say That was extremely stupid and endangered our mission!");
	command("say I won't help anyone making a fire anymore!");
    }
    else if(ranger_test(TP))
    {
	command("say As a ranger you ask me how to make a fire?");
	command("gasp");
	command("say Just make a campfire, but take more care ");
	command("say than usually to prevent the fire from smoking.");
	command("say And don't leave the fire unattended!");
	if (!TP->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT))
	    tasker = TP;
    }
    else if (TP->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT))
    {
	command("say Hmmm, no, I don't think I will make a fire for you.");
	command("shrug");
    }
    else if(!TP->query_prop("_damrod_rabbit_asked_fire"))
    {
	command("sigh");
	command("say Why does it always take a ranger to make a simple campfire?");
	command("say Well, I guess I could climb down to make one, ");
	command("say if you have all the ingredients.");
	command("say If you are ready, just ask me again.");
	TP->add_prop("_damrod_rabbit_asked_fire",1);
    }
    else
    {
	if (!TP->query_prop("_damrod_rabbit_start"))
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

public string
inform_gondor()
{
    if (!check_player(TP)) 
	return "";
    command("say Gondor was once the mightiest kingdom in Middle Earth.");
    command("say Now we are at war with the Enemy.");
    command("say Perhaps the days of Gondor are already numbered,");
    command("say and the walls of Minas Tirith are doomed,");
    command("say so great is His strength and malice.");
    command("sigh");
    return "";
}

public string
inform_ithilien()
{
    if (!check_player(TP)) 
	return "";
    command("say Once Ithilien was the Garden of Gondor.");
    command("say But now the dark shadow of Doom lies upon it.");
    command("say Only we rangers are still fighting against the Enemy this side of the Anduin.");
    command("say But we are too few, and the whole land is overrun by the orcs of Mordor.");
    command("spit");
    return "";
}

public string
inform_north()
{
    if (!check_player(TP)) 
	return "";
    command("say In the North was Arnor, the sister-kingdom of Gondor.");
    command("say It was a large and beautiful kingdom. But the damned");
    command("say Witch-king of Angmar attacked, and after a long war");
    command("say destroyed the kingdom totally. What's left there now");
    command("say is an empty land, and a few small villages. Halflings");
    command("say live there, and Rangers protect them from the world.");
    command("smile");
    return "";
}

public string
inform_rangers()
{
    if (!check_player(TP)) 
	return "";
    command("say The rangers of Ithilien are a part of the Gondorian Army.");
    command("say Most of us are descended from folk who lived in Ithilien ");
    command("say at one time, before it was overrun.");
    command("say Secretly, we cross the Anduin to harrass the orcs and ");
    command("say other servants of the Evil One that roam between the ");
    command("say Ephel Duath and the river.");
    command("say Faramir, Son of Lord Denethor, is our Captain.");
    return "";
}

public string
inform_duty()
{
    if (!check_player(TP)) 
	return "";
    command("say Our duty is to protect the Free Peoples against Mordor!");
    command("say When Gondor falls, no one will be able to withstand ");
    command("say any longer!");
    command("say Right now, we are watching the road to the Morannon ");
    command("say to report to our Captain the movements of the enemy.");
    command("sigh");
    command("say We have already been here for two days and two nights!");
    command("say And all that time without a warm meal!");
    return "";
}

public string
inform_southrons()
{
  if(!check_player(TP)) return "";
  command("say Aye, curse the Southrons!");
  command("say They are gone over to the Enemy.");
  command("say Or back to Him - they were ever ready to His will!");
  command("say They come now marching up on the ancient roads ");
  command("say to swell the hosts of the Dark Tower.");
  command("say Yea, up the very roads that craft of Gondor made.");
  command("say But we will teach them a lesson!");
  return "";
}

public string
inform_harad()
{
  if(!check_player(TP)) return "";
  command("say 'Tis said that there were dealings of old ");
  command("say between Gondor and the kingdoms of Harad in the ");
  command("say Far South; though there was never friendship. In those days ");
  command("say our bounds were away south beyond the mouths of the ");
  command("say Anduin, and Umbar, the nearest of their realms, ");
  command("say acknowledged our sway. But that is long since. ");
  return "";
}

public string
inform_enemy()
{
    if (!check_player(TP)) 
        return "";
    command("say Our Enemy is the Evil One of the Dark Tower.");
    command("say He who reigns in Mordor.");
    command("say We are fighting his serfs whereever we can.");
    command("say No orc or goblin, no human bondsman shall ");
    command("say live in peace as long as the White Tower of Minas ");
    command("say Tirith stills stands.");
    return "";
}

public string
inform_orcs()
{
    if (!check_player(TP)) 
        return "";
    command("say Orcs?");
    command("spit");
    command("say They and those cursed Southrons fill up the armies of the Dark Lord.");
    command("say And defile out beautiful Ithilien.");
    command("say In recent days, we've met new breeds, that are less fearful");
    command("say of the light of day.");
    command("say But still, if we only had more men, we could chase them over the hills!");
    command("sigh");
    return "";
}

public string
inform_enemies()
{
    if (!check_player(TP)) 
        return "";
    command("spit");
    command("say Our enemies are the orcs and the men in the service");
    command("say of the Dark Lord. His armies have overrun fair Ithilien,");
    command("say but we will fight them to the death wherever we find them!");
    return "";
}

public string
inform_road()
{
    if (!check_player(TP)) 
        return "";
    command("say From here we are watching the road from the crossroads to the");
    command("say Morannon, the Dark Gate leading into Mordor.");
    command("say The cursed Southrons come now marching up the ancient roads");
    command("say to swell the hosts of the Dark Tower.");
    command("say Yea, up the very roads that craft of Gondor made.");
    command("say And they go ever more heedlessly, we learn");
    command("say thinking that the power of their new master is great enough,");
    command("say so that the mere shadow of His hills will protect them.");
    command("say But soon. we teach them another lesson.");
    command("emote smiles grimly.");
    return "";
}

public void
enter_inv(object ob, object from)
{
    object pot;

    ::enter_inv(ob,from);

    if (!objectp(ob) || !objectp(from) || !interactive(from))
        return;

    if (ob->query_name() == "badge") 
        return;
    if (from->query_prop("_gave_poisoned_food"))
    {
        set_alarm(1.0, 0.0, &reject_item(({ ob, from })));
	return;
    }
    if (!check_player(from))
    {
        set_alarm(1.0, 0.0, &return_item(ob, from));
	return;
    }
    pot = present("_stewed_rabbit_quest_pot",TO);
    if (pot && pot == ob) 
    {
        if(!from->query_prop("_damrod_rabbit_start"))
	{
      	    set_alarm(1.0, 0.0, &return_item(ob, from));
	    set_alarm(4.0, 0.0, &tell_ask(from));
	}
	else if(fire_alert || from->query_prop("_left_fire_unattended"))
	{
	    set_alarm(1.0, 0.0, &reject_item(({ ob, from })));
	    set_alarm(4.0, 0.0, &tell_fire(from));
	}
	else
            set_alarm(1.0, 0.0, &test_quest_done(({ ob, from })));
    }
    else
        set_alarm(1.0, 0.0, &return_item(ob, from));
    return;
}

public void 
return_item(object ob, object from)
{
    if (ob->id("coin"))
    {
        command("peer "+from->query_real_name());
	command("say Thanks a lot. We will use it to buy weapons for our battle.");
	return;
    }
    ob->move(from);
    command("say Thank you, but I don't believe I can use that!");
    write(process_string(QCTNAME(TO),1) + " gives " + LANG_ADDART(ob->query_name()) + " back to you.\n");
    say(QCTNAME(TO) + " gives " + LANG_ADDART(ob->query_name()) + " back to " + QTNAME(from) + ".\n");
}

void
tell_ask(object player)
{
  command("say Perhaps you should ask for a task first?");
  command("peer " + player->query_real_name());
  return;
}

void
tell_fire(object player)
{
  command("say Someone left a fire unattended at the foot of this tree!");
  command("suspicious " + player->query_real_name());
  command("say I suspect that it was you!");
  command("say Anyway, it was very foolish, and endangered us and our mission!");
}

void 
reject_item(object *arr)
{
  object ob, from;

  ob = arr[0];
  from = arr[1];

  if(ob->id("coin"))
    return;
  ob->move(from);
  command("say No, thank you!");
  command("say We won't take anything from you!");
  write(process_string(QCTNAME(TO),1) + " gives " + LANG_ADDART(ob->query_name()) + " back to you.\n");
  say(QCTNAME(TO) + " gives " + LANG_ADDART(ob->query_name()) + " back to " + QTNAME(from) + ".\n");
}

void
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

int
quest_done(object player)
{
  int reward, pexp;
  object meneldil, pot;

  if(!present(player,ENV(TO))) return 0;

  if(meneldil = present("meneldil",ENV(TO)))
    tell_room(ENV(TO), "Finally, " + QTNAME(TO) + " and " + process_string(QTNAME(meneldil),1) +
      " seem to have finished eating.\n");
  else
    tell_room(ENV(TO), "Finally, " + QTNAME(TO) + " seems to have finished eating.\n");
  command("say Hmmm, that was delicious!");
  command("emote licks his lips.");
  command("thank " + player->query_real_name());
  command("shake " + player->query_real_name());
  if(pot = present("pot",TO))
  {
    pot->move(player);
  write(process_string(QCTNAME(TO),1) + " gives " + LANG_ADDART(pot->query_name()) + " back to you.\n");
    say(QCTNAME(TO) + " gives " + LANG_ADDART(pot->query_name()) + " back to " + QTNAME(player) + ".\n");
  }
  if (!player->test_bit("Gondor", GONDOR_GROUP, RABBIT_STEW_BIT)) 
  {
    reward = RABBIT_STEW_EXP;
    pexp = player->query_exp();
    if(pexp < reward)
        reward = pexp;
    player->set_bit( GONDOR_GROUP, RABBIT_STEW_BIT);
    player->adjust_alignment(250);
    player->add_exp(reward,0);
    LOG_QUEST(player, reward, "STEWED RABBIT (RANGERS)");
    tell_object(player,"You feel much more experienced.\n");
    player->remove_prop("_damrod_rabbit_start");
    player->remove_prop("_damrod_rabbit_asked_fire");
  }
  return 1;
}

void
return_pot(object pot, object player)
{
  command("emote shakes his head in disappointment.");
  pot->move(player);
  write(process_string(QCTNAME(TO),1) + " gives " + LANG_ADDART(pot->query_name()) + " back to you.\n");
  say(QCTNAME(TO) + " gives " + LANG_ADDART(pot->query_name()) + " back to " + QTNAME(player) + ".\n");
  return;
}

int
no_rabbit(object pot, object player)
{
  if(!present(player,ENV(TO))) return 0;

  command("peer " + player->query_real_name());
  command("say Well, I had supposed to find at least a rabbit in the pot!");
  return_pot(pot,player);
  command("say Next time, try to put a rabbit into it!");
  return 1;
}

int
not_stewed(object pot, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("peer " + player->query_real_name());
  command("say Couldn't you stew the rabbit?");
  command("say I don't like it like this, eat it yourself!");
  return_pot(pot,player);
  return 1;
}

int
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

int
no_salt(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("peer " + player->query_real_name());
  command("say How can you make a stew without salt?");
  command("sigh");
  command("say Well, it was an attempt, but a stew without salt ... ");
  command("say It's just terrible!");
/* return_pot(pot,player); */
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

int
no_herb(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("peer " + player->query_real_name());
  command("say All around you herbs are growing!");
  command("say And you prepare a stew without using a single one!");
  command("sigh");
/* return_pot(pot,player); */
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

int
no_rabbit_herb(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("emote sniffs at the stew in the pot.");
  command("say Well, almost, but when you cook a rabbit ");
  command("say you should use some fitting herbs!");
  command("say Like basil, savory, or tarragon!");
/* return_pot(pot,player); */
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

int
no_stew_herb(object pot, object meal, object player)
{
  if(!present(player,ENV(TO))) return 0;
  command("emote sniffs at the stew in the pot.");
  command("say Well, almost, but when you prepare a stew ");
  command("say you should use some fitting herbs!");
  command("say Why didn't you try to find some chervil?");
  command("say Or ginger and laurel, perhaps?");
/* return_pot(pot,player); */
  set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
  return 1;
}

public int
no_extra_herb(object pot, object player)
{
    if (!present(player,ENV(TO))) 
        return 0;
    command("emote sniffs at the stew in the pot.");
    command("say Well, almost, but why don't you put some extra ");
    command("say herb into the rabbit stew?");
    return_pot(pot,player);
    command("say Ithilien is so full of herbs, it should be easy ");
    command("say to find some caraway, thyme, or sage! Or perhaps ");
    command("say some marjoram or rosemary?");
    command("say Can't you smell all these herbs?");
    command("say If you don't find those, why don't you try clove or ");
    command("say saffron? Or mint? Or some dill? You might even put ");
    command("say some fennel or oregano into the stew!");
    return 1;
}

int
extra_herb(object pot, object meal, object player, string extra_herb_name)
{
    if (!present(player,ENV(TO))) 
        return 0;
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

int
not_hot(object pot, object meal, object player)
{
    if (!present(player,ENV(TO))) 
        return 0;
    command("emote sniffs at the stew in the pot.");
    command("say That looks rather good!");
    command("say But why isn't it hot anymore?");
    command("sigh");
    command("say Well, one cannot have anything!");
    set_alarm(4.0, 0.0, &eat_no_reward(({ pot, meal, player })));
}

void
eating(object meal)
{
    command("unmask me");
    command("emote sniffs at the stew in the pot.");
    command("sigh");
    command("say Perfect!");
    command("emote starts eating the rabbit stew.");
    set_alarm(5.0, 0.0, &eating2(meal));
}

public void
eating2(object meal)
{
    object meneldil;
    if (objectp(meneldil = present("meneldil",ENV(TO))))
    {
        command("emote shares the rabbit stew with " + process_string(QTNAME(meneldil),1) + ".");
	meneldil->command("unmask me");
    }
    command("say You must be a great cook! This tastes delicious!");
    command("say And the herbs ..... ");
    command("say I can taste " + meal->query_prop("_rabbit_herb_added_to_stew") +
	    " and " + meal->query_prop("_stew_herb_added_to_stew") + "!");
    command("say Perfect!");
    set_alarm(5.0, 0.0, &eating3(meal));
    return;
}

void
eating3(object meal)
{
  object meneldil;
  if(meneldil = present("meneldil",ENV(TO)))
    command("emote and " + process_string(QTNAME(meneldil),1) + " are silently eating the rabbit stew.");
  else
    command("emote is silently eating the rabbit stew.");
  meal->remove_object();
}
  
void
eat_no_reward(object *arr)
{
  object meneldil, pot, meal, player;
  pot = arr[0];
  meal = arr[1];
  player = arr [2];

  if(meneldil = present("meneldil",ENV(TO)))
    command("emote shares the rabbit stew with " + process_string(QTNAME(meneldil),1) + ".");
  command("emote starts eating the rabbit stew.");
  if(meneldil)
    tell_room(ENV(meneldil),process_string(QCTNAME(meneldil),1) + " starts eating the rabbit stew.\n");
  meal->remove_object();
  command("sigh");
  command("say Well, it was nourishing, but to be honest, it wasn't the meal we've been waiting for!");
  if(!present(player,ENV(TO))) return;
  return_pot(pot,player);
  return;
}

public void
init_attack()
{
  if(query_attack() || TO->ranger_test(TP)) return;
  if( IS_EVIL(TP)    || TP->query_prop("_no_pass_to_ithilien"))
  {
    command("say Die, foul creature!");
    set_alarm(2.0, 0.0, &do_attack(TP));
  }
  else if (interactive(TP))
    set_alarm(2.0, 0.0, &badge_test(TP));
}

void
do_attack(object victim)
{
  if(query_attack() || TO->ranger_test(victim)) return;
  if (!present(victim,ENV(TO))) return;
  command("mask me");
  command("kill "+victim->query_real_name());
}

void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    command("mask me");
    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(TO, ob);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (objectp(query_attack()))
        return;

    set_alarm(rnd()*5.0, 0.0, &help_friend(attacker));
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

public int
arrest(object player)
{
    if (player->query_prop("_arrested")) 
        return 0;

    command("say By Order of Denethor, Steward of Gondor, no one ");
    command("say is allowed to walk in Ithilien without his leave!");
    command("say You must stay here until our Captain arrives ");
    command("say to decide your fate!");
    command("say Do not try to escape!");
    player->add_prop("_arrested",1);
    if (!cf_aid || !sizeof(get_alarm(cf_aid)))
        cf_aid = set_alarm(4.0, 0.0, &call_faramir(player));
    return 1;
}

int stop_fleeing(object player)
{
  object meneldil;
  if(!present(player, ENV(TO))) return 1;
  if(player->query_attack())
    return 0;
  else if(player->query_prop("_arrested") == 1)
  {
    write(QCTNAME(TO) + " stops you.\n");
    say(QCTNAME(player) + " tries to climb down, but is stopped by " + QCTNAME(TO) + ".\n");
    command("say We told you to stay here!");
    command("say Don't try to flee again, this is the last warning!");
    player->change_prop("_arrested",2);
  }
  else if(player->query_prop("_arrested") == 2)
  {
    write(QCTNAME(TO) + " stops you.\n");
    say(QCTNAME(player) + " tries to climb down, but is stopped by " + QCTNAME(TO) + ".\n");
    command("say Die, stupid " + player->query_race_name() + "!");
    do_attack(player);
    if(meneldil = present("meneldil",ENV(TO)))
      meneldil->do_attack(player);
  }
  return 1;
}

void
call_faramir(object player)
{
  if (send_pigeon() && !cof_aid)
  {
    cof_aid = set_alarm(rnd()*6.0 + 3.0, 0.0, &come_faramir(player));
    if(!present("pigeon",TO))
      command("whistle for pigeon");
  }
  else if (!cf_aid)
    cf_aid = set_alarm(10.0, 0.0, &call_faramir(player));
  return;
}

void
come_faramir(object player)
{
  object faramir;

  if(!(faramir = find_living("faramir")))
  {
    seteuid(getuid(TO));
    faramir = clone_object(NPC_DIR + "faramir");
  }
  faramir->called_by_damrod(TO);
  return;
}

void
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
  command("gather firewood");
  lf_aid = set_alarm(60.0, 0.0, &light_fire(player));
}

void
light_fire(object player)
{
  object fire;
  if(!(fire = present("firewood",ENV(TO))) && !(fire = present("campfire",ENV(TO))))
  {
    remove_alarm(lf_aid);
    lf_aid = set_alarm(10.0, 0.0, &light_fire(player));
    return;
  }
  fire->add_burn_time(800);
  fire->add_prop(OBJ_M_NO_GET,1);
  command("climb rock");
  command("climb tree");
  command("climb up");
  command("climb up");
  return;
}

public void
fire_alarm()
{
    object *cont;

    command("say Where is that smoke coming from?");
    command("emote curses silently.");
    command("say It will betray us to the orcs!");
    if (objectp(tasker))
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
    if (objectp(tasker))
        command("say But I suspect it was " + QTNAME(tasker));
    return;
}

public int
query_fire_alert()
{
    return fire_alert;
}

/* Solamnian prestige */
public int query_knight_prestige() {return (-5);}

public int
ranger_test(object player)
{
  int iranger;
  if(!player) return 0;
  if(player->query_npc())
  {
    if( present("ranger_guild_object",player)) return 1;
    return 0;
  }
  iranger = (player->query_guild_name_occ() == RANGER_S_GUILD_NAME);
  if(iranger)
     command("unmask me");
  return iranger;
}

void
add_introduced(string person)
{
  object pl;
  pl = find_living(lower_case(person));
  if(!pl || pl->query_npc()) return;
  set_alarm(4.0, 0.0, introduce_me);
}

string
inform_recipe()
{
    if (!check_player(TP))
        return ""; 

    if (!TP->query_prop("_damrod_rabbit_start"))
        return inform_meal();

    command("say Well, you need a rabbit, of course.");
    command("say And some salt, some water, and herbs.");
    command("emote inhales deeply the air of Ithilien, filled with the frangance of herbs.");
    return "";
}

string
inform_herbs()
{
    if (!check_player(TP))
        return ""; 

    if (!TP->query_prop("_damrod_rabbit_start"))
        return inform_meal();

    command("say Well, you can use several herbs.");
    command("say Actually, we are not very picky.");
    command("say You can use just about any herbs that go with rabbit and stews.");
    command("say Just don't put in anything that doesn't fit.");
    return "";
}
