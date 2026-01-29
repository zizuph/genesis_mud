/*
 *  /d/Gondor/minas/npc/throne_room_guard.c
 *      Modified from /d/Gondor/minas/npc/citadel_guard.c
 *      Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";


#include "/d/Gondor/minas/lib/porter_defs.h"
#include <language.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define INNER_MINAS "/d/Gondor/minas"

string  alignlook();
string  alignlook2();
int try_attack();
static  object  Victim;


#define HIT_TASK	TASK_ROUTINE
#define HIT_SKILLS	({ TS_DEX, TS_STR })
#define HIT_VICTIM_SKILLS	({ TS_DEX })

#define HIT_RATE	25
#define HIT_PEN	60

static int     hit_rate  = HIT_RATE,
               hit_pen   = HIT_PEN;

void
set_hit_rate(int i) { hit_rate = i; }

void
set_hit_pen(int i)  { hit_pen = i; }


public void
create_monster()
{
    int rnd;

    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj(alignlook());
    add_adj(alignlook2());
    set_pname("guards");
    set_name("guard");
    set_race_name("human");
    set_long("This guard is one of the Guards of the Citadel. He is robed "
        + "in black and has a strange, high-crowned helmet with wings of "
        + "seabirds set above the long, close-fitting cheek-guards. Upon his "
        + "black surcoat you can see the embroidered image of a white tree "
        + "in blossom beneath a silver crown and many-pointed stars. This is "
        + "emblem of the heirs of Elendil, and none except the Guards of "
        + "the citadel wear it now.\n");

    set_alignment(400+random(80));
    rnd = random(60);
    default_config_npc(150+rnd/2);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_WEP_SWORD, random(10)+100);
    set_skill(SS_WEP_POLEARM, random(10)+100);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENCE,100);

    set_exp_factor(150);

    set_aggressive(&try_attack());
    set_attack_chance(100);

    set_cact_time(2);
    add_cact("emote shouts: You shall get death as a boon for your audacity!");
    add_cact("emote shouts: How dare you lay hands on the Ruling Steward?");
    add_cact("growl");
    add_cact("emote shouts: For Gondor!");
    add_cact("emote shouts: For Minas Tirith!");
    add_cact("emote shouts: Defend the Steward!");
    add_cact("emote shouts: Your head will be atop the city gates, scoundrel!");


    arm_me();

    refresh_mobile();


}

public void
arm_me() 
{
    FIX_EUID;
    clone_object(WEP_DIR + "halberd")->move(TO);
    command("wield halberd");
    clone_object(ARM_DIR + "gchainmail")->move(TO);
    command("wear chainmail");
    clone_object(ARM_DIR + "winghelm")->move(TO);
    command("wear helm");
    clone_object(OBJ_DIR + "tower_surcoat")->move(TO);
    command("wear surcoat");
}

string
alignlook() 
{
    string *alignlooks =
                 ({"tall", "portly", "short", "grim",
                   "muscular", "well-built", "lean", "experienced", "angry", 
                   "dangerous","handsome","aristocratic","lordly", "arrogant", 
                   "proud"});
    return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
    string *alignlooks2 =
                 ({"eager", "brown-bearded", "silver-haired",
                   "pale", "clean-shaven", "long-nosed", "strong-willed", 
                   "sharp-eyed","thoughtful","clever", 
                   "skilled"});
    return ONE_OF_LIST(alignlooks2);
}


int
try_attack()
{
    if (TP->query_wiz_level())
    {
        return 0;
        
    }


    if (TP->query_npc())
        {
        return 0;
        }

    else
    {
        command("assist steward");
    }
    return 0;
}


int
special_attack(object victim)
{
    int     result,
            er,
            wr;
    mixed   hr = ({ -1, 0, 0, 0 });
    string  wmsg = 0,
            vmsg,
            he = TO->query_pronoun(),
            his = TO->query_possessive(),
            vhim = victim->query_objective(),
            npc = TO->query_nonmet_name(),
            vhis = victim->query_possessive();
    object  *weapons, halberd;

    remove_prop(LIVE_I_ATTACK_DELAY);

    if (random(100) > hit_rate)
        return 0;

    weapons = TO->query_weapon(-1);
    halberd = weapons[0];

    if ( !halberd->id("halberd") )
        return 0;

    // check if we hit

    result = resolve_task(HIT_TASK, HIT_SKILLS,
        victim, HIT_VICTIM_SKILLS);

    er = (100 - ((2*victim->query_encumberance_weight() +
                    victim->query_encumberance_volume())/3));
    wr = (100 * query_prop(OBJ_I_WEIGHT)) / victim->query_prop(OBJ_I_WEIGHT);
    result += (100 * (wr - er)) / HIT_TASK;

    if (result <= 0)
        add_attack_delay(MIN(5, -result/5 + 1), 1);
    else
    {
        if (result < 10)
            result = 10;
        else if (result > 90)
            result = 90;
        hr = victim->hit_me(F_PENMOD(HIT_PEN, result), W_BLUDGEON, TO, -1);
    }

    switch(hr[0])
    {
        case -1:
            vmsg = ", but misses completely. " + CAP(he) + " tries "
                + "desparately to recover his balance!";
            break;
        case 0..4:
            vmsg = ", but it is deflected with only minor damage.";
            wmsg = ", but it is deflected with only minor damage.";
            break;
        case 5..9:
            vmsg = ", and narrowly grazes your head.";
            wmsg = ", and narrowly grazes " + vhis + " head.";
            break;
        case 10..19:
            vmsg = ", but at the last minute feints to one side. The halberd "
                + "slices cleanly into your leg.";
            wmsg = ", but at the last minute feints to one side. The halberd "
                + "slices cleanly into " + vhis + " leg.";
            break;
        case 20..34:
            vmsg = " in a wide arc and brings it crashing down onto your " 
                + hr[1] + ".";
            wmsg = " in a wide arc and brings it crashing down onto " + vhis 
                + " " + hr[1] + ".";
            break;
        case 35..49:
            vmsg = " and expertly jabs it through your defences.";
            wmsg = " and expertly jabs it through "
                + vhis + " defences.";
            break;
        case 50..59:
            vmsg = ", pivots on his heel and plunges it painfully into your "
                + "left leg.";
            wmsg = ", pivots on his heel and plunges it painfully into " 
                + vhis + " left leg.";
            break;
        case 60..79:
            vmsg = ", burying it deeply into your shoulder before ripping "
                + "it out again.";
            wmsg = ", burying it deeply into " + vhis + " shoulder before "
                + "ripping it out again.";
            break;
        case 80..99:
            vmsg = " and manages to run you completely through! Gore sprays "
                + "in all directions.";
            wmsg = " and manages to run " + vhim + " completely through! Gore "
                + "sprays in all directions.";
            break;
        default:
            vmsg = ", shaving off hunks of skin, blood and bone.";
            wmsg = ", shaving off hunks of skin, blood and bone.";
            break;
    }

    if (!strlen(wmsg))
        wmsg = vmsg;
    victim->catch_msg("The " + npc + " swings his halberd at you" + vmsg + "\n");
    tell_watcher("The " + npc + " swings his halberd at " + QTNAME(victim) 
        + wmsg + "\n", TO, victim);

    if (victim->query_hp() <= 0)
        victim->do_die(TO);
    return 1;
}

/*
 * Function name:   start_follow
 * Description:     Start following the enemy.
 * Arguments:       The object to follow.
 */
public void
start_follow(object ob)
{
    object *follower,
            shadow;

    if (!objectp(ob) || !objectp(present(ob, ENV(TO))) || 
	(ob != query_attack()) || (Victim == ob))
	return;

    if (pointerp(follower = ob->query_follower()))
    {
	if (member_array(TO, follower) < 0)
	    ob->add_follower(TO);
    }
    else
    {
	shadow = clone_object(GONDOR_FOLLOW_SHADOW);
	shadow->follow(ob, TO);
    }
    Victim = ob;
}

public varargs void
remove_victim(object victim)
{
    if (objectp(victim) && (Victim != victim))
	return;
    Victim = 0;
}



/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    ::attack_object(ob);
    start_follow(ob);
}


void
do_die(object killer)
{
    tell_room(ENV(TO), "The guard crumples to the ground in agony and "
       + "shouts: Would that I had another life to give for the glory "
       + "of Gondor!\n");

    command("give key to guard");
    command("give sword to guard");
    command("give rod to guard");

    ::do_die(killer);
}




/* Knights will loose prestige on this one */
public int query_knight_prestige() { return -30; }

