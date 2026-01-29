/* 
 * /d/Gondor/minas/npc/spectral_guard.c  
 *
 * spectral guardian in the hallows
 *
 * Alto, 19 May 2001
 *
 */

#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

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
#include "/d/Gondor/minas/lib/porter_defs.h"
#include "/d/Gondor/minas/lib/spectre_riddles.c"


/* Define some attack and hitloc id's */

#define A_INSWORD  0
#define A_INMACE   1
#define A_SHRIEK   2
#define A_SCREAM   3

#define H_HEAD   0
#define H_BODY   1
#define H_RGARM  2
#define H_LGARM  3
#define H_RGHAND 4
#define H_LGHAND 5

object actor, *inv;
string  alignlook();
string  alignlook2();
int try_attack();
static  object  Victim;


#define RIP_TASK	TASK_ROUTINE
#define RIP_SKILLS	({ TS_DEX, TS_STR })
#define RIP_VICTIM_SKILLS	({ TS_DEX })

#define RIP_RATE	25
#define RIP_PEN	60

static int     rip_rate  = RIP_RATE,
               rip_pen   = RIP_PEN;

void
set_rip_rate(int i) { rip_rate = i; }

void
set_rip_pen(int i)  { rip_pen = i; }

static object *Guard = allocate(6);

object actor, *inv;


public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj(alignlook());
    add_adj(alignlook2());
    set_pname("spectres");
    set_name("spectre");
    add_name("guard");

    set_race_name("spectre");

    set_long("This is the spectre of a long-dead ruler of Minas Tirith. "
        + "His long sleep has apparently been disturbed.\n");

    rnd = random(60);
    default_config_npc(150+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(400+rnd*10);

    set_gender(0);
    set_skill(SS_UNARM_COMBAT,100+random(10));
    set_skill(SS_DEFENCE,100+random(10));
    set_skill(SS_PARRY,100+random(10));
    set_skill(SS_BLIND_COMBAT, 100+random(10));
    set_skill(SS_AWARENESS, 100+random(10));

    set_m_out("flies shrieking");
    set_m_in("thunders shrieking in");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);


    add_prop(LIVE_I_SEE_DARK, 200);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_exp_factor(150);

    set_aggressive(&try_attack());
    set_attack_chance(100);

    set_act_time(2);
    add_act("emote fades slowly in and out of existence.");
    add_act("emote howls furiously.");
    add_act("emote fixes his piercing spectral gaze upon you.");
    add_act("emote drifts up into the shadows until all you see are "
        + "his glowing eyes.");
    add_act("emote gathers deep shadows about himself.");
    add_act("emote moans softly.");

    set_cact_time(5);
    add_cact("emote shrieks in fury.");
    add_cact("emote seems to be everywhere at once.");
    add_cact("emote howls a battlecry in an ancient tongue.");
    add_cact("emote gives out a piercing cry. The walls shake and the ground "
        + "trembles beneath your feet.");
    add_cact("emote fades into the shadows. Instantly he is behind you.");

    refresh_mobile();

}

string
alignlook() 
{
    string *alignlooks =
                 ({"gaunt", "terrible", "tragic", "massive",
                   "etherial", "wispy", "ferocious", "stately", "grim", 
                   "ghastly","emaciated","terrifying","haggard", "horrid", 
                   "ghostly"});
    return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
    string *alignlooks2 =
                 ({"tall", "short", "muscular",
                   "fat", "ancient", "wise", "towering", 
                   "rotting","decomposing","bone-white", 
                   "dull-red"});
    return ONE_OF_LIST(alignlooks2);
}


int
try_attack()
{
    actor = TP->query_real_name();
    inv = all_inventory(TP);

    if (TP->query_wiz_level())
    {
        return 0;
        
    }

    if (TP->query_prop(ANSWERED_ALL_RIDDLES))
        {
        return 0;
        }

    if (TP->query_npc())
        {
        return 0;
        }

    else
    {
        command("assist spectre");
    }
    return 1;
}

/*
 * Add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */

public void
cr_configure()
{
    add_attack(40+random(5),40+random(5),W_IMPALE,10,A_INSWORD);
    add_attack(40+random(15),40+random(5),W_BLUDGEON,30,A_INMACE);
    add_attack(40+random(5),40+random(5),W_SLASH,20,A_SHRIEK);
    add_attack(40+random(10),40+random(5),W_SLASH,40,A_SCREAM);

    add_hitloc(({25+random(15),20+random(10),15+random(5)}),10,
        "spectral head",H_HEAD);
    add_hitloc(({25+random(5),15+random(5),20+random(10)}),50,
        "spectral body",H_BODY);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "spectral right arm",H_RGARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "spectral left arm",H_LGARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "spectral right hand",H_RGHAND);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "spectral left hand",H_LGHAND);

}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_INSWORD:return "ephemeral longsword";
    case A_INMACE:return "flickering battlehammer";
    case A_SHRIEK:return "horrid shriek";
    case A_SCREAM:return "painful scream";
    }
    return "mind"; /* should never occur */
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
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
            npc = TO->query_nonmet_name(),
            he = TO->query_pronoun(),
            his = TO->query_possessive(),
            vhim = victim->query_objective(),
            vhis = victim->query_possessive();

    remove_prop(LIVE_I_ATTACK_DELAY);

    if (random(100) > rip_rate)
        return 0;

    // check if we hit

    result = resolve_task(RIP_TASK, RIP_SKILLS,
        victim, RIP_VICTIM_SKILLS);

    er = (100 - ((2*victim->query_encumberance_weight() +
                    victim->query_encumberance_volume())/3));
    wr = (100 * query_prop(OBJ_I_WEIGHT)) / victim->query_prop(OBJ_I_WEIGHT);
    result += (100 * (wr - er)) / RIP_TASK;

    if (result <= 0)
        add_attack_delay(MIN(5, -result/5 + 1), 1);
    else
    {
        if (result < 10)
            result = 10;
        else if (result > 90)
            result = 90;
        hr = victim->hit_me(F_PENMOD(RIP_PEN, result), W_BLUDGEON, TO, A_INMACE);
    }

    switch(hr[0])
    {
        case -1:
            vmsg = ", but misses completely. " + CAP(he) + " howls angrily.";
            break;
        case 0..4:
            vmsg = ", but makes only a minor scratch.";
            wmsg = ", but makes only a minor scratch.";
            break;
        case 5..9:
            vmsg = ", and manages to startle you slightly.";
            wmsg = ", and manages to startle " + vhim + " slightly.";
            break;
        case 10..19:
            vmsg = " with a howling shriek. Your face goes white and your "
                + "breath catches in your throat.";
            wmsg = " with a howling shriek. " + CAP(vhis) + " face goes white and "
                + vhis + " breath catches in " + vhis + " throat.";
            break;
        case 20..34:
            vmsg = " and tears open a ragged gash in your " + hr[1] + ".";
            wmsg = " and tears open a ragged gash in " + vhis 
                + " " + hr[1] + ".";
            break;
        case 35..49:
            vmsg = " and rakes painfully at your eyes.";
            wmsg = " and rakes painfully at "
                + vhis + " eyes.";
            break;
        case 50..59:
            vmsg = " and throws you painfully against the wall.";
            wmsg = " and throws " + vhim + " painfully against the wall.";
            break;
        case 60..79:
            vmsg = ", reaching into your chest with a translucent hand. "
                + "He gives your heart a painful squeeze!";
            wmsg = ", reaching into " + vhis + " chest with a translucent "
                + "hand. He gives " + vhis + " heart a painful squeeze!";
            break;
        case 80..99:
            vmsg = ", shrieking so loudly that your heart stops beating.";
            wmsg = ", shrieking so loudly that " + vhis + " heart stops "
                + "beating.";
            break;
        default:
            vmsg = " and tears the skin of your face to shreds.";
            wmsg = " and tears the skin of " + vhis + " face to shreds.";
            break;
    }

    if (!strlen(wmsg))
        wmsg = vmsg;
    victim->catch_msg("The " + npc + " rips into you" + vmsg + "\n");
    tell_watcher("The " + npc + " rips into " + QTNAME(victim) 
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

    tell_room(ENV(TO), "The spectre shrieks in agony and fades away.\n");

    ::do_die(killer);
}


