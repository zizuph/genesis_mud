 /*
  *  /d/Gondor/common/npc/wolf.c
  *
  * A wolf for the plains of Rohan
  * If you want to clone this wolf somewhere else, then
  * set another restrain path using:
  * wolf->set_restrain_path(<pathname>);
  *
  * Olorin              Feb 1993
  * Modification log:
  * - Made it inheritable, Olorin, June 1995
  *
  */
inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/d/Gondor/common/lib/logkill.c";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_JUMP  1

#define H_HEAD 0
#define H_BODY 1

#define JUMP_TASK	TASK_ROUTINE
#define JUMP_SKILLS	({ TS_DEX, TS_STR })
#define JUMP_VICTIM_SKILLS	({ TS_DEX })

#define JUMP_RATE	25
#define JUMP_PEN	30
#define JUMP_HIT	40
#define BITE_PEN	20
#define BITE_HIT	40

static int     jump_rate  = JUMP_RATE,
               jump_pen   = JUMP_PEN,
               jump_hit   = JUMP_HIT,
               bite_pen   = BITE_PEN,
               bite_hit   = BITE_HIT;

void
set_jump_rate(int i) { jump_rate = i; }

void
set_jump_pen(int i)  { jump_pen = i; }

void
set_jump_hit(int i)  { jump_hit = i; }

void
set_bite_pen(int i)  { bite_pen = i; }

void
set_bite_hit(int i)  { bite_hit = i; }

void
create_wolf()
{
    add_adj(({"grey", "hungry", }));
    set_short("grey wolf");
    set_pshort("grey wolves");

    set_long(BSN("This is a wild wolf, not very large, but dangerous "
      + "nevertheless. He looks rather hungry! He is lean and scrawny "
      + "and has thick, grey fur and sharp fangs."));

    set_aggressive(1);
    set_attack_chance(50);
    set_jump_rate(25);

    set_restrain_path(ROH_DIR + "plains");
}

void
create_creature()
{
    set_name("wolf");
    set_race_name("wolf");

    set_stats(({40+random(30), 30+random(20), 30+random(10), 20, 5, 30}));
    set_alignment(0);

    set_skill(SS_DEFENCE,      17);
    set_skill(SS_UNARM_COMBAT, 66);
    set_skill(SS_AWARENESS,    80);
    set_skill(SS_SWIM,         80);
    set_skill(SS_CLIMB,        40);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);

    create_wolf();

    // us% for fangs < 100 to take jumps into account.
    set_attack_unarmed(A_BITE,  bite_hit, bite_pen, W_IMPALE,   (100-jump_rate) + 10, "fangs");
    set_attack_unarmed(A_JUMP,  jump_hit, jump_pen, W_BLUDGEON,                    0, "body");

    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");

    seq_new("do_first");
    seq_addfirst("do_first",({"@@arm_me","stare","emote peers hungrily at you.","growl"}));

    set_act_time(10);
    add_act("growl");
    add_act("snarl");
    add_act("@@do_emote|growl@@");
    add_act("@@do_emote|peer hungrily@@");
    add_act("@@do_emote|snarl@@");
    add_act("peer hungrily");
    add_act("emote howls loudly.");
}

public void
arm_me()
{
    FIX_EUID
    clone_object(OBJ_DIR + "wolfskin")->move(TO);
    set_m_out("quickly trots");
    set_m_in("stealthily trots into view");
}

string
query_combat_file()
{
    return "/std/combat/cplain";
}

int query_knight_prestige() {return 250;}

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

    if (random(100) > jump_rate)
        return 0;

    // check if we hit

    result = resolve_task(JUMP_TASK, JUMP_SKILLS,
        victim, JUMP_VICTIM_SKILLS);

    er = (100 - ((2*victim->query_encumberance_weight() +
                    victim->query_encumberance_volume())/3));
    wr = (100 * query_prop(OBJ_I_WEIGHT)) / victim->query_prop(OBJ_I_WEIGHT);
    result += (100 * (wr - er)) / JUMP_TASK;

    if (result <= 0)
        add_attack_delay(MIN(5, -result/5 + 1), 1);
    else
    {
        if (result < 10)
            result = 10;
        else if (result > 90)
            result = 90;
        hr = victim->hit_me(F_PENMOD(JUMP_PEN, result), W_BLUDGEON, TO, A_JUMP);
    }

    switch(hr[0])
    {
        case -1:
            vmsg = ", but misses and crashes to the ground. "+CAP(he)+" looks stunned.";
            break;
        case 0..4:
            vmsg = ", but almost misses and barely scratches you.";
            wmsg = ", but almost misses and barely scratches "+vhim+".";
            break;
        case 5..9:
            vmsg = ", but just scratches you.";
            wmsg = ", but just scratches "+vhim+".";
            break;
        case 10..19:
            vmsg = " and tears with "+his+" fangs at your "+hr[1]+".";
            wmsg = " and tears with his fangs at "+vhis+" "+hr[1]+".";
            break;
        case 20..34:
            vmsg = " and sinks his fangs into your "+hr[1]+".";
            wmsg = " and sinks his fangs into "+vhis+" "+hr[1]+".";
            break;
        case 35..49:
            vmsg = " and sinks his fangs deep into your "+hr[1]+".";
            wmsg = " and sinks his fangs deep into "+vhis+" "+hr[1]+".";
            break;
        case 50..59:
            vmsg = " and tears with fangs at your throat.";
            wmsg = " and tears with fangs at "+vhis+" throat.";
            break;
        case 60..79:
            vmsg = ", throws you to the ground and tears with fangs at your throat.";
            wmsg = ", throws "+vhim+" to the ground and tears with fangs at "+vhis+" throat.";
            break;
        case 80..99:
            vmsg = ", throws you to the ground and and sinks "+his+" fangs deep into your throat.";
            wmsg = ", throws "+vhim+" to the ground and and sinks "+his+" fangs deep into "+vhis+" throat.";
            break;
        default:
            vmsg = ", throws you to the ground and and bites through your throat.";
            wmsg = ", throws "+vhim+" to the ground and and bites through "+vhis+" throat.";
            break;
    }
    if (!strlen(wmsg))
        wmsg = vmsg;
    victim->catch_msg("The "+short()+" jumps at you with wide open fangs"+vmsg+"\n");
    tell_watcher("The "+short()+" jumps at "+QTNAME(victim)+" with wide open fangs"+wmsg+"\n", TO, victim);

    if (victim->query_hp() <= 0)
        victim->do_die(TO);
    return 1;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    ::attacked_by(ob);

        query_team_others()->notify_ob_attacked_me(TO, ob);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_team(object ob)
{
    if (!objectp(ob) || objectp(query_attack()) ||
        !present(ob, ENV(TO)) || !interactive(ob) ||
        !CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, ob))
        return;

    command("kill " + ob->query_real_name());
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (objectp(query_attack()))
        return;

    if (random(10))
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &help_team(attacker));
}

public void
check_combat()
{
    object  ob;

    if (objectp(ob = query_attack()))
        // I'm lying. So what? :-)
        query_team_others()->notify_ob_attacked_me(TO, ob);
}

/*
 * Function name: init_attack
 * Description:   Called from init_living() in monster.c
 */
public void
init_attack()
{
    if (objectp(query_attack()))
        return;

    ::init_attack();
    set_alarm(5.0, 0.0, check_combat);
}

public string
do_emote(string what)
{
    object *target;
    string  name;

    target = FILTER_LIVE(all_inventory(ENV(TO)));

    name = ONE_OF_LIST(target)->query_name();

    command(what + " name");
    return "";
}

