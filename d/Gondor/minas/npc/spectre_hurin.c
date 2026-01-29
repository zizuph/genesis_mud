/* 
 * /d/Gondor/minas/npc/spectre_hurin.c  
 *
 * Spectre of Hurin, Guardian of the House of Stewards
 *
 * Alto, 19 April 2001
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

#define INNER_MINAS "/d/Gondor/minas"



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

object actor, guard, *inv;

public void wizard_greeting();

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


public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj("floating");
    add_adj("angry");
    set_name("Hurin");
    set_pname("spectres");
    add_name("spectre");
    add_name("steward");
    add_name("ghost");
    add_name("hurin");
    set_title("of Emyn Arnen, Founder and Guardian of the House of Stewards");

    set_race_name("spectre");

    set_long("This is the spectre of Hurin of Emyn Arnen, founder of "
        + "the House of Stewards. His restless spirit awakens when "
        + "the peace of the Tomb is broken. The ghost harbours no ill "
        + "for those who know and love Gondor well, and come bearing the "
        + "token of the tombs. He is almost entirely transparent, and only "
        + "the upper half of his body can be seen floating above you.\n");

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

    remove_prop(LIVE_I_NEVERKNOWN);

    add_prop(LIVE_I_SEE_DARK, 200);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_exp_factor(150);


    set_act_time(2);
    add_act("emote fades slowly in and out of existence.");
    add_act("emote howls furiously.");
    add_act("emote fixes his piercing spectral gaze upon you.");
    add_act("emote drifts up into the shadows until all you see are "
        + "his glowing eyes.");
    add_act("emote gathers deep shadows about himself.");
    add_act("emote moans softly.");

    set_chat_time(2);
    add_chat("Death is so lonely .. so cold.");
    add_chat("Woe unto those who would violate my sleep.");
    add_chat("Behold my children, those who lie here were Stewards all.");
    add_chat("It is agony to awaken. I long for the darkness of sleep.");
    add_chat("To walk in the sun once again .. ah, but such is no longer "
        + "for me.");


    set_cact_time(2);
    add_cact("emote shrieks in fury.");
    add_cact("emote seems to be everywhere at once.");
    add_cact("emote howls a battlecry in an ancient tongue.");
    add_cact("emote calls to the dead: Arise! Arise! Death to those who "
        + "would violate our sleep!");
    add_cact("emote gives out a piercing cry. The walls shake and the ground "
        + "trembles beneath your feet.");
    add_cact("emote fades into the shadows. Instantly he is behind you.");

    clone_object(INNER_MINAS + "/obj/steward_door_key.c")->move(TO);


    refresh_mobile();

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
        "ghostly head",H_HEAD);
    add_hitloc(({25+random(5),15+random(5),20+random(10)}),50,
        "ghostly body",H_BODY);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "ghostly right arm",H_RGARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "ghostly left arm",H_LGARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "ghostly right hand",H_RGHAND);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "ghostly left hand",H_LGHAND);

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
    case A_INSWORD:return "ghostly transparent longsword";
    case A_INMACE:return "ghostly transparent mace";
    case A_SHRIEK:return "ghastly shriek";
    case A_SCREAM:return "horrifying scream";
    }
    return "mind"; /* should never occur */
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
}

void
init_living()
{
   ::init_living();
   add_action("answer_riddle", "answer");
}


/* Set up the reaction of NPC to player */

public void
return_bow(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(2))
    {
    case 0:
        command("bow solemnly");
	       break;
    case 1:
        command("bow grim");
    default:
        break;
    }
}


public void
emote_hook(string emote, object actor, string adverb = "")
{
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
        {
        case "bow":
	           set_alarm(2.0, 0.0, &return_bow(actor));
	           break;
        }
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}

/* Leave Wizards Alone */

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;

    set_alarm(2.0, 0.0, "wizard_greeting", victim);
}

void
lock_door()
{
    command("close door");
    command("lock door with key");
}

string
wizard_greeting()
{

    actor = TP->query_real_name();
    inv = all_inventory(TP);

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
        return "";


    if (TP->query_wiz_level())
    {
        command("say Greetings, Wizard.");
        command("bow " + actor);
        command("say I will leave you in peace.");
        return "";
        
    }

    if (!sizeof(filter(inv, &->id("_token_of_tombs_"))))
        {
        command("peer furiously " + actor);
        command("say to " + actor + " You do not bear the token! Your death "
            + "for entering this place unbidden will be painful and slow.");
        set_alarm(1.0, 0.0, &lock_door());
        command("kill " + actor);
        return "";
        }

    if (TP->query_prop(ANSWERED_ALL_RIDDLES))
        {
        command("say Greetings, servant of the Tombs.");
        command("bow " + actor);
        command("say I will leave you to your work.");
        return "";
        }

    if (TP->query_prop(MISSED_A_RIDDLE))
        {
        command("say Die, imposter.");
        set_alarm(1.0, 0.0, &lock_door());
        command("kill " + actor);
        return "";
        }


    else
    {
        command("poke " + actor);
        command("say You bear the token, but are you true?");
        set_alarm(1.0, 0.0, &lock_door());
        set_alarm(1.0, 0.0, &riddles_answer());
        set_alarm(120.0, 0.0, &first_riddle_attack());
    }
    return "";
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
    victim->catch_msg("The floating angry spectre rips into you" + vmsg + "\n");
    tell_watcher("The floating angry spectre rips into " + QTNAME(victim) 
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

    guard = clone_object(INNER_MINAS + "/npc/spectral_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/spectral_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/spectral_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/spectral_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/spectral_guard");
    guard->move(ENV(TO));

    guard = clone_object(INNER_MINAS + "/npc/spectral_guard");
    guard->move(ENV(TO));

    command("scream");
    command("sigh");

    tell_room(ENV(TO), "The spectre shrieks in agony and fades away.\n");


    ::do_die(killer);
}


