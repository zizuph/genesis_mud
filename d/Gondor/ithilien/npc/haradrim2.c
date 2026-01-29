/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

#define WEAPON		(WEP_DIR + "haradscim")
#define ARMOUR1		(ARM_DIR + "haradcloak")
#define ARMOUR2		(ARM_DIR + "haradshield")
#define ARMOUR3		(ARM_DIR + "corslet")

void return_item(object *arr);
void help_friend(object ob);
void do_attack(object victim);

void
create_monster()
{
  set_name("haradrim");
  add_name(({"sniper","soldier","mercenary","man","haradrim2"}));
  set_race_name("human");
  set_gender(0);
  set_adj("silent");
  set_adj("black-skinned");
  set_stats(({ 65+random(10), 70+random(10), 75+random(10),
    60+random(10), 60+random(10), 80+random(10) }));
  set_hp(7000);
  set_skill(SS_WEP_SWORD,80+random(15));
  set_skill(SS_PARRY,60+random(10));
  set_skill(SS_DEFENCE,60+random(10));
  set_skill(SS_UNARM_COMBAT,60+random(10));
  set_skill(SS_CLIMB,100);
  set_skill(SS_AWARENESS,100);
  set_alignment(-500-random(50));
  set_aggressive(1);
  set_long("@@long_func");
  add_prop(CONT_I_HEIGHT,190);
  add_prop(CONT_I_WEIGHT,87000);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  add_chat("Two days on duty in this tree, and no warm meal!");
  add_prop(LIVE_I_NEVERKNOWN,1);
  add_chat("I'd love to eat a boiled coney now!");
  add_chat("Stewed rabbit, with a few herbs, perhaps some taters or carrots!");
  add_chat("Too bad we have to stay on the lookout.");
  add_chat("Two days we've been waiting for the reinforcements to arrive!");
  add_chat("Gondor built the road, but Harad's armies are marching on it!");
  add_chat("Curse the Rangers!");
  add_chat("Soon we will plunder Minas Tirith!");
  add_chat("Finally we will destroy cursed Gondor!");
  add_chat("The Dark Lord is our ally, with His help, Gondor will fall soon!");
  add_chat("These cursed tramps that calls themselves rangers "+
    "keep ambushing us!");
  add_act("sigh");
  add_act("emote deeply breathes the air, full with the smell of "+
    "many herbs and flowers.");
  add_act("emote peers intently in the direction of the road.");
  add_act("emote seems to think longingly of a warm meal.");
  set_default_answer(VBFC_ME("default_answer"));
}

void
arm_me()
{
    FIX_EUID
    clone_object(WEAPON)->move(TO);
    command("wield all");
    clone_object(ARMOUR1)->move(TO);
    clone_object(ARMOUR3)->move(TO);
    clone_object(ARMOUR2)->move(TO);
    command("wear all");
    clone_object(ITH_DIR + "obj/bow")->move(TO);
    clone_object(ITH_DIR + "obj/quiver")->move(TO);
}

string
long_func()
{
  return BSN("You are looking at a black-skinned soldier. "+
    "He looks like an experienced fighter. He is a mercenary "+
    "in the army of the Dark Lord, serving in the armies that "+
    "are to overrun Gondor.");
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
  if(present("haradrim1",ENV(TO)))
    command("say If you want to give us something, then give it to the boss!"); 
  return;
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
  if(!IS_EVIL(TP))
  {
    set_alarm(2.0, 0.0, &do_attack(TP));
  }
}

void
do_attack(object victim)
{
  if(query_attack())
    return;
  if (!present(victim,environment(TO))) return;
  command("kill "+victim->query_real_name());
}

default_answer()
{
  if(!IS_EVIL(TP))
  {
    command("say Die, foul creature!");
    do_attack(TP);
    return "";
  }
  command("say I do not know what you are talking about, " +
    TP->query_race_name() + ".");
  if(present("haradrim1",ENV(TO)))
  {
    command("say Ask the boss here, perhaps he can help you!");
    command("point officer");
  }
  return "";
}

/* Solemnian prestige */
query_knight_prestige() {return (120);}

