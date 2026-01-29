/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 * Tigerlily: May 31, 2004: updated for ranger recode
 */
inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/guilds/rangers/rangers.h"

void help_friend(object ob);
void do_attack(object victim);
void return_item(object *arr);
int ranger_test(object player);

void
create_monster()
{
  set_name("meneldil");
  add_name(({"sniper","man","ranger","dunadan"}));
  add_name("ranger");
  add_name("dunadan");
  /* set_living_name("meneldil");*/
  set_title("the Master Tracker of the Rangers of Ithilien");
  set_race_name("human");
  set_gender(0);
  set_adj("silent");
  set_adj("strong");
  set_stats(({ 65+random(10), 70+random(10), 75+random(10),
      60+random(10), 60+random(10), 80+random(10) }));
  set_base_stat(SS_OCCUP, 62);
  set_hp(7000);
  set_skill(SS_WEP_SWORD,80+random(15));
  set_skill(SS_PARRY,60+random(10));
  set_skill(SS_DEFENCE,60+random(10));
  set_skill(SS_UNARM_COMBAT,60+random(10));
  set_skill(SS_CLIMB,100);
  set_skill(SS_AWARENESS,100);
  set_skill(SS_BRAWLING,80+random(20));
  set_skill(SS_HEARING,80+random(20));
  set_alignment(500+random(50));
  set_aggressive(1);
  set_long("@@long_func");
  add_prop(CONT_I_HEIGHT,190);
  add_prop(CONT_I_WEIGHT,87000);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  add_chat("Two days on duty in this tree, and no warm meal!");
  add_chat("I'd love to eat a boiled coney now!");
  add_chat("Stewed rabbit, with a few herbs, perhaps some taters or carrots!");
  add_chat("Too bad we have to stay on the lookout.");
  add_chat("The whole day there have been Haradrim on the march north.");
  add_chat("Our forefathers built the road, and now our enemies are "+
    "marching on it.");
  add_chat("Curse the Southrons!");
  add_chat("Of late we have learned that the Enemy has been among "+
    "the Southrons.");
  add_chat("There was never friendship between Gondor and the "+
    "kingdoms of Harad in the South.");
  add_chat("The Southrons have gone over to the Enemy, as so many "+
    "have done in the East.");
  add_chat("The cursed Southrons are marching on the very roads that "+
    "the craft of Gondor made.");
  add_act("sigh");
  add_act("emote deeply breathes the air, full with the smell of many "+
    "herbs and flowers.");
  add_act("emote peers intently in the direction of the road.");
  add_act("emote seems to think longingly of a warm meal.");
  set_cact_time(1);
  add_cact("brawl");
  set_default_answer(VBFC_ME("default_answer"));
  add_ask("name",VBFC_ME("introduce_me"));
  add_ask("rangers",
    BS(QCTNAME(TO) + " says: We Rangers of Ithilien "+
    "are fighting the armies of the Evil One.\n"));
  add_ask("duty",
    BS(QCTNAME(TO) + " says: We have to observe the road running "+
    "towards the Morannon " +
    "and to report all movements on the road to our Captain.\n"));
}

arm_me()
{
    object amulet,wep,arm1,arm2,arm3,bow,quiver;
    seteuid(getuid(this_object()));

#ifndef NEW_RANGERS_OPEN
    clone_object(RANGER_DIR + "ramulet")->move(TO, 1);
    clone_object(RANGER_DIR + "spells/obj/pigeon_ob")->move(TO, 1);
#endif

#ifdef NEW_RANGERS_OPEN
    clone_object(RANGERS_OBJ + "roi_amulet")->move(TO,1);
    clone_object(RANGERS_SPELL + "obj/pigeon_ob")->move(TO, 1);
#endif
  command("wear amulet");
  wep = clone_object(ITH_DIR + "obj/rlsword");
  wep->move(this_object());
  command("wield longsword");
  arm1 = clone_object(ITH_DIR + "obj/rgauntlets");
  arm1->move(this_object());
  command("wear gauntlets");
  arm3 = clone_object(ITH_DIR + "obj/rhood");
  arm3->move(this_object());
  command("wear hood");
  command("mask me");
  arm2 = clone_object(ITH_DIR + "obj/rcloak");
  arm2->move(this_object());
  command("wear cloak");
  bow = clone_object(ITH_DIR + "obj/bow");
  bow->move(TO);
  quiver = clone_object(ITH_DIR + "obj/quiver");
  quiver->move(TO);
}

introduce_me()
{
  if( IS_EVIL(TP)    || TP->query_prop("_no_pass_to_ithilien"))
  {
    command("say Die, foul creature!");
    do_attack(TP);
    return "";
  }
  command("unmask me");
  command("say My name is Meneldil.");
  command("hail " + TP->query_real_name());
  command("introduce me");
  return "";
}

string
long_func()
{
  return break_string("He is a pale-skinned man, dark of hair, "+
    "with grey eyes, and a proud and sad face. You realize that he "+
    "must be one of the Dunedain of the South, a man of the line of "+
    "the Lords of Westernesse. \n",70);
}

enter_inv(object ob, object from)
{
  object pot;

  ::enter_inv(ob,from);

  if (!from) return;
  if(!interactive(from)) return;
  set_alarm(1.0, 0.0, &return_item(({ ob, from })));
  return;
}

void
return_item(object *arr)
{
  object ob, from;

  ob = arr[0];
  from = arr[1];

  ob->move(from);
  command("say No, thanks, I'm not allowed to take anything!");
  from->catch_msg(QCTNAME(TO) + " gives " +
      LANG_ADDART(ob->query_name()) + " back to you.\n");
  say(QCTNAME(TO) + " gives " + LANG_ADDART(ob->query_name()) +
      " back to " + QTNAME(from) + ".\n");
  if(present("damrod",ENV(TO)))
    command("say If you want to give us something, then give it to Damrod!"); 
  return;
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
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    set_alarm(rnd()*5.0, 0.0, &help_friend(attacker));
}
void
help_friend(object ob)
{
  if (ob && !query_attack() && present(ob, environment()))
  {
    command("say Die, foul creature!");
    TO->do_attack(ob);
  }
}
public void
init_attack()
{
    if(query_attack()) return;

    if(IS_EVIL(TP) || TP->query_prop("_no_pass_to_ithilien"))
    {
        set_alarm(2.0, 0.0, &do_attack(TP));
    }
}

void
do_attack(object victim)
{
  if(query_attack() || IS_RANGER(victim)) return;
  if (!present(victim,environment(this_object()))) return;
  command("mask me");
  command("kill "+victim->query_real_name());
}

default_answer()
{
  if( IS_EVIL(TP)    || TP->query_prop("_no_pass_to_ithilien"))
  {
    command("say Die, foul creature!");
    do_attack(TP);
    return "";
  }
  command("say I do not know what you are talking about, " +
      TP->query_race_name() + ".\n");
  return "";
}

/* Solemnian prestige */
query_knight_prestige() {return (-4);}

int
ranger_test(object player)
{
    int iranger = 0;
    if(!player) 
        return 0;
    if(player->query_npc())
    {
        if(present("ranger_guild_object",player)) 
            return 1;
        return 0;
    }
    if (IS_RANGER(player))
    {
        command("unmask me");
        iranger = 1;
    }
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

void
init_living()
{
    ::init_living();
    set_size_descs("tall", "lean");
}
