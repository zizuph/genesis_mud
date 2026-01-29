/*
 *	/d/Gondor/common/guild2/spells/obj/watcher.c
 *
 *	A crow to spy on living targets for the Morgul spell crabandir.
 *
 *	December 1995 by Olorin
 *
 *      Copyright (c) 1995, 1996 by Christian Markus
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";
inherit "/std/act/action.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#undef DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x)	find_player("olorin")->catch_msg("CRABAN: "+(x)+"\n");
#else
#define DEBUG_MSG(x)
#endif

#define TEMP_ROOM	(MORGUL_SPELL_OBJS + "watcher_room")
#define MIN_ANI_HANDL	40
#define MIN_AWARE	40
#define MIN_SPELLCRAFT	20
#define MIN_WIS		60
#define HIS(x)		(x)->query_possessive()
#define HIM(x)		(x)->query_objective()
#define MAX_FAIL	12

       void    watch_target();
public void    remove_craban();
public int     query_time_left();

static object  gMage,
               gTarget,
               gParalyze;
static int     gDuration,
               gFail,
               gWatch,
               gExploded,
               gRemoved;

public void
create_creature()
{
    set_name(({"craban", "crow", "bird", "beast", }));
    set_pname(({"crebain", "crows", "birds", }));
    set_race_name("crow");
    set_adj(({"large", "black", }));
    set_short("black crow");
    set_pshort("black crows");
    set_long("@@long_desc@@");
    set_alignment(-100);

    set_stats(({ 10, 60, 25, 40, 40, 10 }));
    set_whimpy(80);

    set_skill(SS_AWARENESS, 90);
    set_skill(SS_DEFENCE,   40);

    add_prop(CONT_I_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_WEIGHT, 800);
    add_prop(CONT_I_MAX_VOLUME, 800);

    add_prop(OBJ_M_NO_ATTACK, "@@check_attack@@");

    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 5);

    add_prop(MAGIC_I_RES_POISON, 70);
    add_prop(MAGIC_I_RES_MAGIC,  40);
    add_prop(MAGIC_I_RES_AIR,    70);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry something.\n");

    add_prop(LIVE_I_NO_CORPSE,   1);
    add_prop(LIVE_I_UNDEAD,    100);

    add_prop(OBJ_S_WIZINFO, "@@wiz_info@@");

    set_attack_unarmed(0,  5, 15, W_IMPALE,            50, "beak");
    set_attack_unarmed(1, 15, 10, W_SLASH | W_IMPALE,  75, "claws");

    set_hitloc_unarmed(0, ({ 12, 12,  5}),  40, "body");
    set_hitloc_unarmed(1, ({ 15,  5, 15}),  20, "left wing");
    set_hitloc_unarmed(2, ({ 15,  5, 15}),  20, "right wing");
    set_hitloc_unarmed(3, ({ 20, 10,  5}),  10, "head");
    set_hitloc_unarmed(4, ({ 10, 10, 20}),  10, "claws");

    set_tell_active(1);

    set_act_time(30);
    add_act("emote croaks harshly.");
    add_act("emote flaps its wings.");

    set_alarm(0.0, 0.0, &set_m_in("flies into view"));
    set_alarm(0.0, 0.0, &set_m_out("flies away to the"));
}

string
wiz_info()
{
    return BSN(
        "This craban is a demon summoned by the Morgul spell crabandir, "
      + "taking the shape of a bird. The mage who cast the spell can "
      + "see through the eyes of the crow, but cannot control it. The "
      + "crow can be send to spy on any living that is outdoors. It "
      + "cannot follow indoors. It can be attacked only in one case "
      + "out of five. If it wimpies, the demon returns whence it was "
      + "summoned, hurting the attacker. The spell will end in "
      + query_time_left() + " seconds.");
}

mixed
check_attack()
{
    int     seed,
            dummy;

    sscanf(OB_NUM(TO), "%d", dummy);
    seed = dummy;
    sscanf(OB_NUM(TP), "%d", dummy);
    seed += dummy;

#if DEBUG
#else
    if (random(5, seed))
        return "The "+short()+" is flying out of reach. It is "
             + "impossible to attack it.\n";
#endif

    return 0;
}

public string
long_desc()
{
    object  tp = TP;
    string  msg = "This large black crow is a craban out of Mordor where "
                + "these birds are bred to serve the servants of the "
                + "Dark Lord as spies.";

    if ((tp->query_skill(SS_SPELLCRAFT) >
        (MIN_SPELLCRAFT/2 + random(MIN_SPELLCRAFT))) ||
        (tp->query_skill(SS_AWARENESS) > (MIN_AWARE/2 + random(MIN_AWARE))))
        msg += " The crow does not look like a normal beast. Your skilled "
            +  "senses notice the power of Dark Sorcery emanating from "
            +  "the bird.";

    if ((tp->query_skill(SS_ANI_HANDL) >
        (MIN_ANI_HANDL/2 + random(MIN_ANI_HANDL))) &&
        (tp->query_stat(SS_WIS) > (MIN_WIS/2 + random(MIN_WIS))))
    {
        msg += " The eyes of the craban show more intelligence by far "
            +  "than one could expect from a crow. The craban seems "
            +  "to watch ";
        if (gTarget == tp)
            msg += "you";
        else
            msg += gTarget->query_the_name(tp);
        msg += " intently.";
    }

    return BSN(msg);
}

varargs void
explode_crow(object attacker)
{
    int     mana = gMage->query_mana(),
            hp = gMage->query_hp(),
            dam;
    mixed   result;
    string  msg;

    if (!objectp(attacker))
        attacker = query_attack();

    if (!objectp(attacker) || !living(attacker) ||
        !present(attacker, ENV(TO)) || !objectp(gMage))
    {
        remove_craban();
        return;
    }

    dam = MIN(2 * mana, hp);
    dam -= dam * attacker->query_magic_res(MAGIC_I_RES_LIGHT) / 100;

    msg = "The "+short()+" suddenly explodes violently in a cloud of "
      + "black smoke.\n"
      + "From the cloud, a bolt of lightning strikes ";

    tell_room(ENV(TO), msg +QTNAME(attacker)+".\n", ({ TO, attacker }) );
    attacker->catch_msg(msg + "you.\n");

    gMage->catch_msg("The "+short()+" flees from combat, returning to the "
      + "shadows whence you summoned it.\n"
      + "It disappears in a violent explosion, hitting "+QTNAME(attacker)
      + " with a bolt of lighting.\n"
      + "Your awareness returns to your undead body, both weakened by "
      + "the dissipation of energy.\n");
    tell_room(ENV(gMage),
        "The body of "+QTNAME(gMage)+" begins to stir again.\n"
      + CAP(HIS(gMage))+" spirit seems to have returned to "
      + HIS(gMage) + " undead body.\n", gMage);

    result = attacker->hit_me(dam, MAGIC_DT, TO, -1);
    if (pointerp(result) && result[3])
        dam = result[3];
    else
        dam = random(dam);

    log_file("craban", attacker->query_name() + " hit by craban of "
      + gMage->query_name() + " with damage " + dam + " hp on "
      + ctime(time()) + ".\n");
    if (attacker->query_hp() <= 0)
    {
        log_file("craban", attacker->query_name() + " ("
          + attacker->query_average_stat() + ") killed by "
          + "craban of " + gMage->query_name() + " ("
          + gMage->query_average_stat() + ") in "
          + file_name(ENV(attacker)) + ".\n");
        attacker->do_die(TO);
    }

    gMage->add_mana(- dam/4);
    gMage->heal_hp(-dam/2);

    tell_room(ENV(TO), "The black cloud disperses, and leaves no remains.\n",
        TO);

    gExploded = 1;

    remove_craban();
}

public void
remove_object()
{
    if (!gRemoved)
    {
        remove_craban();
        return;
    }

    ::remove_object();
}

/*
 * Function name: remove_craban
 * Description:   end the effect, remove paralyze and stun from mage,
 *                remove crow, prevent recursion errors.
 */
public void
remove_craban()
{
    string  mage_msg = "";

    if (gRemoved++)
        return;

    if (IS_CLONE)
      log_file("craban", ">>>\t"+file_name(TO)+(query_ghost() ? " (dead)" : "")
      + ":\n\tremove_craban() called"
      + (objectp(previous_object()) ? " from "+file_name(previous_object())
      + (objectp(ENV(previous_object())) ? " in " + ENV(previous_object())->query_name()
      + " ("+file_name(ENV(previous_object()))+")" :
        " in the void") : ", but previous_object() not defined")
      + ".\n\tgParalyze " + (objectp(gParalyze) ? "= " + file_name(gParalyze)
      + (objectp(ENV(gParalyze)) ? " in " + ENV(gParalyze)->query_name() : " in the void")
        : "not defined")
      + ".\n\t" + (objectp(gMage) ? "Cast by " + gMage->query_name() : "gMage undefined")
      + ". " + (objectp(gTarget) ? "Target is " + gTarget->query_name() : "gTarget undefined")
      + ".\n\tgExploded = "+gExploded+". gRemoved = "+gRemoved+". "+ctime(time())+".\n");

    if (previous_object() != gParalyze)
        gParalyze->stop_paralyze();
    gMage->remove_stun();

    if (!gExploded)
    {
        gExploded = 1;
        // go peacefully
        if (!query_ghost())
        {
            tell_room(ENV(TO), "The "+short()+" flaps its wings and "
              + "flies up into the sky and away.\n", TO);
            mage_msg = " and the craban returns to the shadows whence "
              + "you summoned it";
        }
        if (objectp(gMage))
        {
            gMage->catch_msg("Your awareness enters your undead "
              + "body again"+mage_msg+".\n");
            tell_room(ENV(gMage), "The body of "+QTNAME(gMage)
              + " begins to stir again.\n"
              + CAP(HIS(gMage))+" spirit seems to have returned to "
              + HIS(gMage) + " undead body.\n", gMage);
            // prevent double messages if remove_craban() is called twice.
            gMage = 0;
        }
    }

    remove_object();
}

void
set_mage(object ob)
{
    if (objectp(ob))
        gMage = ob;
}

void
set_paralyze(object ob)
{
    if (objectp(ob))
        gParalyze = ob;
}

void
set_target(object ob)
{
    if (objectp(ob) && living(ob))
        gTarget = ob;
}

void
set_duration(int value)
{
    gDuration = set_alarm(itof(value), 0.0, remove_craban);
}

void
start_watch()
{
    if (!objectp(gMage) || !objectp(gTarget) ||
        !gDuration || !sizeof(get_alarm(gDuration)))
        remove_craban();

    tell_room(ENV(TO),
        "The "+short()+" nods its head solemnly.\n"
      + "The "+short()+" flaps its wings and flies up to the sky.\n", TO);
    move_living("M", TEMP_ROOM, 0, 0);
    gWatch = set_alarm(10.0 + 20.0 * rnd(), 5.0, watch_target);
}

void
watch_target()
{
    object  target_env;
    string  txt;

    if (!objectp(gMage))
    {
        set_alarm(0.0, 0.0, remove_craban);
        return;
    }

    if (!objectp(gTarget) || !objectp(target_env = ENV(gTarget)))
    {
        gMage->catch_msg("Your "+short()+" fails to locate its target "
          + "and flies off.\n"
          + "The spell ends.\n");
        set_alarm(0.0, 0.0, remove_craban);
        return;
    }

    if (MASTER_OB(ENV(TO)) == TEMP_ROOM)
    {
        txt = "You begin to receive a vision from your " + short()
         + " as it flies slowly over the land of " + target_env->query_domain()
         + " looking for " + QTNAME(gTarget) + ".\n";

        if (!target_env->query_prop(ROOM_I_INSIDE) && interactive(gTarget))
        {
            txt += "Your " + short() + " spies " + QTNAME(gTarget)
              + " below and glides down to investigate.\n";
            gMage->catch_msg(txt, gMage);
            tell_room(ENV(TO), "The "+short()+" flies away as if it is "
              + "following someone.\n", TO);
            move_living("M", target_env, 1, 0);
            tell_room(target_env, CAP(LANG_ADDART(short()))
              + " appears overhead and slowly flies about.\n", TO);
        }
        else
            gMage->catch_msg(txt, gMage);
        return;
    }
    if (ENV(TO) != target_env)
    {
        if (!gFail)
            txt = "Your "+short()+" attempts to follow "+QTNAME(gTarget)+".\n";
        else
            txt = "";
        if (target_env->query_prop(ROOM_I_INSIDE) || !interactive(gTarget))
        {
            if (gFail++ > MAX_FAIL)
            {
                txt += "Your "+short()+" fails to locate " + QTNAME(gTarget)
                  + " and flies off.\n"
                  + "The spell ends.\n";
                set_alarm(0.0, 0.0, remove_craban);
            }
            else
            {
                txt += "The "+short()+" has lost " + QTNAME(gTarget) + ".\n"
                  + "It flies slowly over the land of "
                  + target_env->query_domain() + " trying to locate "
                  + HIM(gTarget) + " again.\n";
            }
            gMage->catch_msg(txt, gMage);
        }
        else
        {
            gMage->catch_msg(txt, gMage);
            tell_room(ENV(TO), "The "+short()+" flies away as if it is "
              + "following someone.\n", TO);
            move_living("M", target_env, 1, 0);
            tell_room(target_env, CAP(LANG_ADDART(short()))
              + " appears overhead and slowly flies about.\n", TO);
            gFail = 0;
        }
        return;
    }

    switch (random(9))
    {
        case 0:
            txt = "The "+short()+" circling overhead croaks harshly.\n";
            break;
        case 1:
            txt = CAP(LANG_ADDART(short())) + " circles slowly overhead.\n";
            break;
        case 2:
            txt = CAP(LANG_ADDART(short())) + " flaps its wings slowly, "
                + "staying overhead.\n";
            break;
        case 3:
            txt = CAP(LANG_ADDART(short())) + " flies overhead, watching "
                + "the ground and everyone on it closely.\n";
            break;
        default:
            txt = 0;
            break;
    }
    if (strlen(txt))
        tell_room(target_env, txt, TO);
}

void
catch_msg(mixed str, object from_player)
{
    ::catch_msg(str, from_player);

    if ((from_player == TO) || !objectp(gMage))
        return;
    gMage->catch_msg("Through the eyes of the craban you see:\n");
    gMage->catch_msg(str, from_player);
}

void
enter_env(object to, object from)
{
    string  message = "";
    object *inv,
           *ld,
            tp;

    ::enter_env(to, from);

    if (!objectp(to) || !objectp(from))
        return;

    if (!objectp(gMage))
    {
        remove_craban();
        return;
    }

    if (!objectp(to) || (MASTER_OB(to) == TEMP_ROOM))
        return;

    if (present(gTarget, to))
    {
        message += "Through the eyes of the craban you see:\n"
          + to->long();
        inv = FILTER_CAN_SEE(all_inventory(to), gMage);
        inv -= ({ TO });
        tp = this_player();
        set_this_player(gMage);
        if (sizeof(ld = FILTER_DEAD(inv)))
            message += CAP(COMPOSITE_DEAD(ld)) + ".\n";
        if (sizeof(ld = FILTER_LIVE(inv)))
            message += capitalize(COMPOSITE_LIVE(ld)) + ".\n";
        set_this_player(tp);
        gMage->catch_msg(message, gMage);
    }
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    set_alarm(0.0, 0.0, &ob->catch_msg(
        "The "+short()+" croaks threateningly.\n"
      + "You feel the power of Dark Sorcery emanating from the bird.\n"
      + "Horrified, you realize that this is no normal beast, it "
      + "is a demon summoned from the realm of shadows by "
      + "the Black Magic of Mordor.\n"));
}

public int
query_time_left()
{
    mixed   info;
    if (pointerp(info = get_alarm(gDuration)))
        return ftoi(info[2]);
    return -1;
}

public void
run_away()
{
    explode_crow();
}

public int
query_see_special_msg()
{
    return 1;
}

