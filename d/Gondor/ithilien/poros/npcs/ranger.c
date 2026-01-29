/*
 *   /d/Gondor/ithilien/poros/npcs/ranger.c
 *
 *   This is a ranger scout sent to find the secret corsair base.
 *
 *   Talisan,  February 1996
 *   Modified September 28, 2001 by Serif: fixed some typos in chats.
 *   Tigerlily, modified inheritance for recode
 *    June 2004
 */

#pragma strict_types

inherit "/d/Gondor/guilds/rangers/npc/npc_ranger";

#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define QUIT_REACT(x) ({"shout Better luck next time, "+x+"!"})

//	Protoypes
void    help_friend(object ob, object friend);
void    test_can_see(object victim);
void    get_money();

//	Global variables
int attack_alarm;

string *
random_color()
{
    switch(random(7))
    {
    case 0:
      return ({ "scarred", "dark-haired" });
      break;
    case 1:
      return ({ "calm", "grey-eyed" });
      break;
    case 2:
      return ({ "tall", "dunadan" });
      break;
    case 3:
      return ({ "strong", "dunadan" });
      break;
    case 4:
      return ({ "muscular", "dark-eyed" });
      break;
    case 5:
      return ({ "young", "lean" });
      break;
    case 6:
      return ({ "slender", "dunadan" });
      break;
    }
}

public void
create_ranger()
{
    int rnd = random(10);

    string  *color;
    color = random_color();

    seteuid(getuid(TO));
    set_name("ranger");
    add_name("man");
    set_width_desc("very skinny");
    add_name("_poros_ranger");
    add_adj(color);
    set_race_name("human");
    set_long(BSN("This individual looks like he has traveled for many "
      + "days without rest. Although tired and a little ragged, the "
      + "man seems quite used to it. By his clothes and manner he can "
      + "be marked as one of the secretive Rangers of Ithilien, an "
      + "undoubtably capable opponent if provoked."));

    default_config_npc(85+rnd);
    set_base_stat(SS_DEX, 100+rnd);
    set_base_stat(SS_CON, 90+rnd);
    set_base_stat(SS_DIS, 90+rnd);
    set_skill(SS_WEP_SWORD, 85+rnd);
    set_skill(SS_DEFENCE, 70+rnd);
    set_skill(SS_PARRY, 70+rnd);
    set_skill(SS_BRAWLING, 90+rnd);
    set_skill(SS_AWARENESS, 80+rnd);

     set_gender(G_MALE);
    set_alignment(300+random(250));
    set_company_no(1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 170 +random(30));
    add_prop(CONT_I_WEIGHT, 75000 +random(30*500));
    add_prop(CONT_I_VOLUME, 70000 +random(30*500));


    set_cchat_time(1 +random(2));
    add_cchat("Flee for your life, dog of Sauron!");
    add_cchat("Gondor will never fall!");
    add_cchat("Taste my steel, corsair spy!");
    add_cchat("You will not find Rangers easy prey, foolish one!");
    add_cchat("By Isildur! We will not be defeated!");

    set_act_time(2+random(5));
    add_act("track");
    add_act("rstudy");
    add_act("suspicious");
    add_act("rtroubled");
    add_act("rdirt");
    add_act("grsay The Black Drake corsairs won't be raiding "
      + "for much longer!");
    add_act("grsay Once we find them, we'll send a squad to "
      + "wipe them out.");
    add_act("grsay Let's hurry up and find this hideout...          "
      + "        then get the report back to the Captain.");
    add_act("grsay Damn the bloody corsairs! Their base must be close by...");
    add_act("@@make_fire@@");

    set_cact_time(1);
    add_cact("brawl");
    add_cact("disarm");

    set_pick_up(75);
    set_tell_active(1);
    trig_new("%w 'leaves' 'the' 'realms.\n'", "react_quit");
}

public void
arm_me()
{
    get_company_token();
    clone_object(WEP_DIR + "r_brsword")->move(TO);
    command("wield all");

    clone_object(ARM_DIR + "dlboots")->move(TO);
    clone_object(ARM_DIR + "drcloak")->move(TO);
    clone_object(ARM_DIR + "studl")->move(TO);
    command("wear all");

    get_money();
}

void
get_money()
{
    MONEY_MAKE_CC(10 + random(10))->move(TO);
    MONEY_MAKE_SC(10 + random(5))->move(TO);
}

int
query_knight_prestige() {return -1000;}

/*
 * Function Name:  attacked_by
 * Description:    This function is called when somebody attacks this object.
 * Arguments:      ob- the attacker
 */

void
attacked_by(object ob)
{
    object  room = ENV(TO),
           *arr;

    ::attacked_by(ob);

    arr = filter(all_inventory(room), &->id("_poros_ranger"));
    arr->notify_ob_attacked_me(TO, ob);
}

/*
 * Function Name:    notify_ob_attacked_me
 * Description:      This is called when someone attacks a team member.
 * Arguments:        friend- my teammate
 *                   attacker- the attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;
    if (random(10))
        set_alarm(5.0, 0.0, &help_friend(attacker,TO));
}

void
do_attack(object victim)
{
    if (objectp(query_attack()))
        return;
    if (victim->query_npc())
        return;
    if (!present(victim,ENV(TO)))
        return;
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
    {
        command("shout Where is he? I can't see him!");
        return;
    }
    command("kill "+victim->query_real_name());
}

/*
 * Function Name:    help_friend
 * Description:      Help my friends by attacking thier attacker.
 * Arguments:        attacker- The person who attacked my friend.
 */
void
help_friend(object ob, object friend)
{
    if (objectp(ob) && !objectp(query_attack()) &&
        present(ob, ENV(TO)) && CAN_SEE(TO, ob) && F_DARE_ATTACK(TO, ob))
    {
        command("shout Foolish move, "+ob->query_race_name()+"!");
        do_attack(ob);
    }
}

int
check_attack(object player)
{
    object  room,
            attacker,
           *arr;

    attacker = player->query_attack();
    if (CAN_SEE(TO, player) && (objectp(attacker) && attacker->id("_poros_ranger")))
    {
      do_attack(player);
      room = ENV(TO);
      arr = filter(all_inventory(room), &->id("_poros_ranger")) - ({ TO });
      arr->order_attack_enemy(TO, player);
      return 1;
    }
      return 0;
}

public void
init_attack()
{
    if (query_attack())
      return;
    if (!interactive(TP))
      return;
//    check_attack(TP);
}

void
loot_corpse()
{
    command("get all from corpse");
}

int
notify_you_killed_me(object player)
{
    set_alarm(2.0, 0.0, loot_corpse);
    if (player->query_npc())
      return 1;
    seteuid(getuid(TO));
    log_file("goodkill",player->query_name()+" ("+player->query_average_stat()
      + ") was killed by "+TO->query_name()+" on "+ctime(time())+" ("
      + file_name(ENV(TO))+").\n");
      return 1;
}

void
test_can_see(object victim)
{
    if (!present(victim, ENV(TO)))
    {
      remove_alarm(attack_alarm);
      attack_alarm = 0;
      return;
    }
    if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, victim))
    {
        remove_alarm(attack_alarm);
        attack_alarm = 0;
        do_attack(victim);
    }
}

void
remove_surplus(object ob)
{
    command("wear all");
    if (!sizeof(query_weapon(-1)))
    command("wield weapon");
    if (!objectp(ob->query_worn()) && !objectp(ob->query_wielded()))
      ob->remove_object();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!objectp(ob) || !objectp(from))
      return;
    if (!query_prop(NPC_M_NO_ACCEPT_GIVE))
      return;
    if (query_encumberance_weight() > 80 ||
        query_encumberance_volume() > 80)
      set_alarm(1.0, 0.0, &remove_surplus(ob));
}

void
react_quit(string who)
{
    command("get all");
    if (random(2))
    command(ONE_OF_LIST(QUIT_REACT(who)));
}

public void
make_fire()
{
    object  env = ENV(TO);

    if (TO->query_prop(OBJ_I_HIDE)) 
        return;
    if (!objectp(env))
        return;

    if (env->query_prop(ROOM_I_INSIDE))
        return;

    if (present("firewood", env) && (random(4)))
    {
        command("light fire");
        return;
    }

    if (present("firewood", TO))
    {
        command("drop firewood");
    }
    command("gather firewood");

    return;
}

void
init_living()
{
    ::init_living();
    set_size_descs("tall", "lean");
}
