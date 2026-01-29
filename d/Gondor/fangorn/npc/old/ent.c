/* 
 * /d/Gondor/fangorn/npc/huorn.c  
 *
 * An ent of Fangorn Forest
 *
 * Alto, 15 May 2001
 *
 *  Modification Log:
 *    22 Jan 03 - ents now hide after cloning. Alto
 *    22 Jan 03 - general beef up of stats. Alto
 *    28 Jan 03 - ents now hide again if they unhide to fight. Serif
 *    28 Jan 03 - ents are gagged when hidden. Serif
 *    28 Jan 03 - lowered stats somewhat so ents can be attacked. Serif
 *    01 Feb 03 - ent kills now logged in /d/Gondor/log/ent_kills
 */

#pragma strict_types

inherit "/std/monster";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <money.h>
#include <tasks.h>


#include "/d/Gondor/defs.h"


/* Define some attack and hitloc id's */

#define A_L_FIST   0
#define A_R_FIST   1
#define A_L_ROOT   2
#define A_R_ROOT   3

#define H_HEAD    0
#define H_TRUNK   1
#define H_RARM    2
#define H_LARM    3
#define H_RLEG    4
#define H_LLEG    5

#define FANGORN_DIR "/d/Gondor/fangorn/"

static  object  Victim;
object  huorn;

string  alignlook();
string  alignlook2();
void    add_gems();
void	hide_me();

#define HAMMER_TASK	TASK_ROUTINE
#define HAMMER_SKILLS	({ TS_DEX, TS_STR })
#define HAMMER_VICTIM_SKILLS	({ TS_DEX })

#define HAMMER_RATE	25
#define HAMMER_PEN	60

static int     hammer_rate  = HAMMER_RATE,
               hammer_pen   = HAMMER_PEN;

void
set_hammer_rate(int i) { hammer_rate = i; }

void
set_hammer_pen(int i)  { hammer_pen = i; }


public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj(alignlook());
    add_adj(alignlook2());
    set_pname("ents");
    set_name("ent");

    set_race_name("ent");

    set_long("The creature appears to be half man and half tree! He is "
        + "at least fourteen feet tall, with branch-like arms and "
        + "leaf-like hair. His skin is covered with a thick bark-like "
        + "substance which looks like it would protect him very well. "
        + "The most impressive thing about him, however, are his eyes, "
        + "which are wise, patient, and echo millennia of sorrow and "
        + "joy.\n");

    rnd = random(60);
    default_config_npc(250+rnd/2);
    set_base_stat(SS_DIS, 250 + rnd);
    set_alignment(50+rnd*10);

    set_gender(0);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_LOC_SENSE, 100);
    set_skill(SS_TRACKING, 100);

    add_prop(LIVE_I_SEE_DARK, 200);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_exp_factor(50);
    set_m_out("rumbles");
    set_m_in("rumbles in");

    set_chat_time(8);
    add_chat("I am a shepherd of trees.");
    add_chat("Have you seen the Entwives? Many many years have gone by since "
        + "last I set eyes upon them.");
    add_chat("Do not harm these trees!");
    add_chat("For an ent, I am rather hasty. I left the Entmoot "
        + "after only a day!");
    add_chat("Let us not be hasty now. Were I hasty, I might have crushed "
        + "you underfoot for entering my forest.");
    add_chat("I have no love of dwarves, with their axes!");
    add_chat("I detest goblins and orcs, the burarum, killers of trees!");
    add_chat("I suspect young Saruman is up to no good. Well we shall "
        + "see about that!");
    add_chat("These trees have been my wards since they were saplings.");
    add_chat("This forest is not a place for the likes of you. The trees "
        + "are suspicious of those who go about on two legs.");
    add_chat("Ware the Huorns! They are not so forgiving as I am.");
    add_chat("I would give you my name, but it might take several weeks "
        + "to say it all in my language.");
    add_chat("I hope you are not planning to cut down any of these "
        + "trees. Hroom!");
    add_chat("Do not risk getting entangled in the woods of Laurelindorinan, "
        + "these days called Lothlorien.");
    add_chat("Some of these trees are wide awake, and a few are, well, ah, "
        + "well, getting Entish!");
    add_chat("Many of my kindred are growing sleepy, going tree-ish, as "
        + "you might say.");

    set_act_time(7);
    add_act("emote trumpets a deep woodwind note.");
    add_act("emote says: Hrum!");
    add_act("emote says: Hroom!");
    add_act("emote says: Hoom!");
    add_act("stretch");
    add_act("smile");
    add_act("emote looks fondly at the trees with many old memories "
        + "apparent in his eyes.");
    add_act("emote peers suspiciously at you.");

    set_cact_time(2);
    add_cact("emote trumpets a painful high-pitched note.");
    add_cact("emote thunders: How dare you harm my trees! Hroom!");
    add_cact("emote thunders: Fangorn is not a place for tree-killers! Hrum!");
    add_cact("emote growls: Unfortunately for you, I am a hasty ent.");
    add_cact("emote grumbles: Do not touch the trees in my forest.");

    add_gems();

    set_alarm(0.2, 0.0, &hide_me());

    refresh_mobile();
}

string
alignlook() 
{
    string *alignlooks =
                 ({"towering", "gigantic", "massive", "lumbering",
                   "huge", "tall", "ancient", "giant", "weathered", 
                   "grim","hardy","friendly","hasty", "patient", 
                   "alert"});
    return ONE_OF_LIST(alignlooks);
}

string
alignlook2() 
{
    string *alignlooks2 =
                 ({"oak-like", "maple-like", "beech-like",
                   "elm-like", "spruce-like", "pine-like", "sycamore-like", 
                   "willow-like","birch-like","ash-like", 
                   "hickory-like"});
    return ONE_OF_LIST(alignlooks2);
}


string
gem_types() 
{
    string *gemtypes =
                 ({"agate", "amber", "amethyst", "beryl_red",
                   "chalcedony", "coral", "diamond", "emerald", "garnet", 
                   "jade","opal","peridot","ruby", "sapphire", 
                   "moonstone"});
    return ONE_OF_LIST(gemtypes);
}

void
add_gems()
{
    setuid();
    seteuid(getuid());

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);
}

void
hide_me()
{
    this_object()->add_prop(OBJ_I_HIDE, 60+random(30));
    tell_room(ENV(this_object()), "The ent blends in with the trees around it.\n");
    TO->add_prop(LIVE_M_MOUTH_BLOCKED, 1);
    TO->set_act_time(100000);
    TO->set_act_time(100000);
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
    add_attack(40+random(5),40+random(5),W_BLUDGEON,10,A_L_FIST);
    add_attack(40+random(5),40+random(5),W_BLUDGEON,30,A_R_FIST);
    add_attack(40+random(5),40+random(5),W_BLUDGEON,20,A_L_ROOT);
    add_attack(40+random(5),40+random(5),W_BLUDGEON,40,A_R_ROOT);

    add_hitloc(({25+random(15),20+random(10),15+random(5)}),10,
        "massive head",H_HEAD);
    add_hitloc(({25+random(5),15+random(5),20+random(10)}),50,
        "thick trunk",H_TRUNK);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "knotted left arm",H_RARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "knotted right arm",H_LARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "huge root-like left leg",H_RLEG);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "huge root-like right leg",H_LLEG);

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
    case A_L_FIST:return "hammer-shaped left fist";
    case A_R_FIST:return "hammer-shaped right fist";
    case A_L_ROOT:return "gnarled left foot";
    case A_R_ROOT:return "gnarled right foot";
    }
    return "mind"; /* should never occur */
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
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

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    attack_object(ob);
    if (TO->query_combat_time() != 0)
    {
        TO->remove_prop(LIVE_M_MOUTH_BLOCKED);
        set_alarm(600.0, 0.0, &hide_me());
        set_alarm(1200.0, 0.0, &hide_me());
        set_alarm(1800.0, 0.0, &hide_me());
        TO->set_act_time(7);
        TO->set_chat_time(8);
        return;
    }
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
            vhis = victim->query_possessive();

    remove_prop(LIVE_I_ATTACK_DELAY);

    if (random(100) > hammer_rate)
        return 0;

    // check if we hit

    result = resolve_task(HAMMER_TASK, HAMMER_SKILLS,
        victim, HAMMER_VICTIM_SKILLS);

    er = (100 - ((2*victim->query_encumberance_weight() +
                    victim->query_encumberance_volume())/3));
    wr = (100 * query_prop(OBJ_I_WEIGHT)) / victim->query_prop(OBJ_I_WEIGHT);
    result += (100 * (wr - er)) / HAMMER_TASK;

    if (result <= 0)
        add_attack_delay(MIN(5, -result/5 + 1), 1);
    else
    {
        if (result < 10)
            result = 10;
        else if (result > 90)
            result = 90;
        hr = victim->hit_me(F_PENMOD(HAMMER_PEN, result), W_BLUDGEON, TO, A_R_FIST);
    }

    switch(hr[0])
    {
        case -1:
            vmsg = ", but misses entirely. " + CAP(he) + " hooms furiously.";
            break;
        case 0..4:
            vmsg = ", but only manages to scratch you with the rough surface "
                + "of his fists.";
            wmsg = ", but only manages to scratch " + vhim + " with the "
                + "rough surface of his fists.";
            break;
        case 5..9:
            vmsg = ", but only slightly bruises you.";
            wmsg = ", but only slightly bruises " + vhim + ".";
            break;
        case 10..19:
            vmsg = " and crunches " + his + " fists into your " + hr[1] + ".";
            wmsg = " and crunches his fists into " + vhis + " " + hr[1] + ".";
            break;
        case 20..34:
            vmsg = " and smashes his fists heavily into your " + hr[1] + ".";
            wmsg = " and smashes his fists heavily into " + vhis 
                + " " + hr[1] + ".";
            break;
        case 35..49:
            vmsg = " and hammers his massive fists painfully upon "
                + "your " + hr[1] + ".";
            wmsg = " and hammers his massive fists painfully upon "
                + vhis + " " + hr[1] + ".";
            break;
        case 50..59:
            vmsg = " and crushes your head with his fists.";
            wmsg = " and crushes " + vhis + " head with his fists.";
            break;
        case 60..79:
            vmsg = ", tosses you high into the air and tramples you with "
                + "his root-like feet.";
            wmsg = ", tosses " + vhim + " high into the air and tramples " 
                + vhim + "with his root-like feet.";
            break;
        case 80..99:
            vmsg = ", grabs you by the neck and shatters your body against "
                + "several trees.";
            wmsg = ", grabs " + vhim + " by the neck and shatters " + vhis 
                + " body against several trees.";
            break;
        default:
            vmsg = " and tramples you into the ground beneath his feet.";
            wmsg = " and tramples " + vhim + " into the ground beneath his feet.";
            break;
    }

    if (!strlen(wmsg))
        wmsg = vmsg;
    victim->catch_msg("The ent hammers at you" + vmsg + "\n");
    tell_watcher("The ent hammers at " + QTNAME(victim) 
        + wmsg + "\n", TO, victim);

    if (victim->query_hp() <= 0)
        victim->do_die(TO);
    return 1;
}


void
do_die(object killer)
{
    setuid();
    seteuid(getuid());

    huorn = clone_object(FANGORN_DIR + "npc/huorn.c");
    huorn->move(ENV(TO));

    log_file("ent_kills", killer->query_name()
        + " (" + killer->query_average_stat()
        + " stat average, " + killer->query_alignment() 
        + " alignment) killed an innocent " 
        + this_object()->short() + " on " + ctime(time()) + " in " 
        + file_name(environment(this_object())) + ".\n");

    tell_room(ENV(TO), "The ent shrieks so loudly that your ears hurt. "
        + "As it dies, it crumbles into the dust from which it was born.\n");

    ::do_die(killer);
}

