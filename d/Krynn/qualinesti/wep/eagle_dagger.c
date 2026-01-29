/*
 * File : eagle_dagger.c
 *
 * INFO:
 * Eagle-shaped dagger - a magic dagger wielded randomly by Qualthas.
 * Its hit/pen increase if player succeed to master it while wielding
 * or later by using 'gaze into eyes of the eagle' command, but hit/pen
 * decrease if he fails. The values change each time the player wields/
 * masters it.
 * Wielding depends on skill but mastering on wisdom, intelligence and
 * discipline of the player.
 *
 * Blizzard, 02/2003
 *
 * Cotillion, 2004-10-13
 * - Fixed ::did_hit
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <options.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Krynn/solamn/splains/local.h"

int gMastered, gBites;
int look_into_eyes(string str);

int fail_master(object ob);
int master_one(object ob);
int dagger_mastered(object ob);

// Normal hit and pen.
#define TO_HIT  35
#define TO_PEN  34
// Hit and pen after unsuccessful mastering.
#define MIN_HIT 28
#define MIN_PEN 27
// Hit and pen after successful mastering.
#define MAX_HIT 40
#define MAX_PEN 40

int     alarm1_id, alarm2_id, alarm3_id, alarm4_id, alarm5_id, alarm6_id;

void
create_weapon()
{
    set_name(({"knife", "dagger"}));
    set_short("wide eagle-shaped dagger");
    set_adj( ({"engraved", "eagle-shaped", "wide", "eagle" }) );
    set_long("The dagger's blade is 15 inches long, crafted from a white " +
        "metal. The hilt is a heavily engraved electrum. The blade " +
        "of unusal shape as flowing curves mix with pointed ones in a way " +
        "sculptor would picture the grace of a noble fencer, graceful yet " +
        "deadly. All length of this weapon images an eagle, pommel " +
        "presenting a predator head that look almost alive, its eyes being " +
        "polished drops of a black onyx, the neck provides grip, and " +
        "outstretched claws are the guard of the dagger. As your sight " +
        "travels from that side, you notice that strange shape of the blade " +
        "is stylized for a wing of this predator striking its victim. It " +
        "surely would take a great skill for a proper use of this " +
        "magnificant weapon.\n");
    add_item(({ "pommel", "head" }),
        "Despide a cold and hard material used in making of the pommel, " +
        "an excellence of the sculptor made it into image of a bird's " +
        "head.\n" +
        "  There is something distrubing about polished black onyx gems " +
        "residing in its eyesockets. It makes the head look somewhat alive " +
        "and a razor sharp beak only adds to the feeling." +
        "\n  Something urges you to gaze into the black onyx eyes.\n\n");
    add_item(({ "onyx gems", "gems", "eyes", "drops" }),
        "The eyes of this electrum eagle are made of polished black onyx " +
        "gems, and as you carefully inspect them, you notice some kind of " +
        "dimmed light at their depths.\n");

    set_wf(TO);

    set_hit(TO_HIT);
    set_pen(TO_PEN);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    set_wt(W_KNIFE);

    set_keep(1);
    set_likely_dull(0);
    set_likely_break(0);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VALUE, 10);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "The eagle-shaped dagger is a powerful " +
        "artifact. It has magicaly increased hit and pen. The player " +
        "can master it and if he succeed the hit/pen increase but if he " +
        "fails the hit/pen are lowered. Wielding requirements : " +
        "SS_WEP_KNIFE at least superior craftsman (60); " +
        "The mastering depends on int, wis and dis. \n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"Only skilled people are able to use this excellent weapon.\n", 5,
              "The dagger seems to be alive and its will resists the wielder " +
              "sometimes. Only strong minded and brave people are able to " +
              "to control it.\n", 20,
              "Those who gazed into the black onyx eyes and managed to calm the " +
              "dagger, find it a very dangerous and deadly weapon. Those who " +
              "failed may be disappointed.\n", 40 }) );

    seteuid(getuid(TO));
}

/* Function name  : init
 * Description    : Initialize some weapon related actions.
 */
init()
{
    ::init();
    add_action(look_into_eyes, "gaze");

}

/* Function name  : query_mastered
 * Description    : Checks the status of the dagger
 * Returns        : 1    - if mastered
 *                  0    - if not mastered
 */
int
query_mastered()
{
    return gMastered;
}

/* Function name  : look_into_eyes
 * Description    : It starts mastering the dagger.
 */
int
look_into_eyes(string str)
{
    object ob = this_player();

    if ( !strlen(str) || !parse_command(str, ({}),
             "'into' / 'in' [the] [black] [onyx] [eagle] 'eyes'") )
    {
        notify_fail("Gaze into the black onyx eyes?\n", 0);
        return 0;
    }

    if ( query_wielded() != ob )
    {
        notify_fail("You should wield the " + short() + " first.\n");
        return 0;
    }

    if ( gMastered == 1 )
    {
        notify_fail("Nothing happens as you gaze into the onyx eyes of the " +
            "eagle. The dagger has been calmed already.\n");
        return 0;
    }

    alarm2_id = set_alarm(0.5, 0.0, &master_one(ob));

    return 1;

}

int
master_dagger(object ob)
{
    if ( environment(TO) != TO->query_wielded() )
        return 0;

    ob->catch_msg("\nSomething from within a dagger urges you to look " +
        "into the onyx eyes of the eagle.\n");
    tell_room(environment(ob), QCTNAME(ob) + " shudders and " +
        POSSESSIVE(ob) + " eyes seem to be empty for a while.\n", ob);

    if (environment(TO) == ob)
        alarm3_id = set_alarm(2.0, 0.0, &master_one(ob));

    return 1;
}

int
master_one(object ob)
{
    int avg = TP->query_average_stat();

    if ( environment(TO) != TO->query_wielded() )
        return 0;

    if ( TP->resolve_task(TASK_DIFFICULT, ({ SKILL_WEIGHT, 200, SKILL_AVG,
                                                 TS_WIS, TS_INT, TS_DIS, SKILL_END })) > 0 )
    {
        ob->catch_msg("\nAs you stare deeply into eyes of the electrum eagle " +
            "your vision blurs in images of vast spaces, unimaginable beauty " +
            "of flight. You feel the caress of the wind upon your skin and primal " +
            "predator like urges of hunt, you feel your heart start to " +
            "pound and for a moment you are a predator closing on the kill. " +
            "You marvel at clarity of the act and you admire its finish.\n");

        gMastered = 1;
        if (query_wielded() == ob)
            alarm4_id = set_alarm(3.0, 0.0, &dagger_mastered(ob));

        return 1;
    }
    else
    {
        ob->catch_msg("\nAs you stare deeply into eyes of the electrum eagle " +
            "your vision blurs in images of vast spaces, unimaginable beauty " +
            "of flight. You feel the caress of the wind upon your skin and primal " +
            "predatory urges to hunt. You feel your heart start to " +
            "pound and suddenly everything changes...\n");

        gMastered = 0;
        if (query_wielded() == ob)
            alarm5_id = set_alarm(2.0, 0.0, &fail_master(ob));

        return 1;
    }
}

int
fail_master(object ob)
{
    if ( environment(TO) != TO->query_wielded() )
        return 0;

    ob->catch_msg("\nAs a great eagle swoops over you, closing for the kill, " +
        "you gasp in shock but you know you are unable to escape, and then " +
        "comes the ripping pain that surges through your arm and down your " +
        "spine.\n");

    if (query_wielded() == ob)
        alarm6_id = set_alarm(2.0, 0.0, &dagger_mastered(ob));

    return 1;
}

int
dagger_mastered(object ob)
{
    if ( environment(TO) != TO->query_wielded() )
        return 0;

    if (gMastered == 1)
    {
        ob->catch_msg("\nAs you breath deeply you notice the vision ended, " +
            "though you still feel your heart pounding a sheer adrenaline, " +
            "moreover - you feel it is only the beginning of your hunt.\n" +
            "\nThe dagger seems to be calm again.\n");
        tell_room(environment(ob), QCTNAME(ob) + " blinks and " +
            POSSESSIVE(ob) + " eyes look normal again.\n", ob);

        set_hit(MAX_HIT);
        set_pen(MAX_PEN);
        ob->update_weapon(TO);

        return 1;
    }
    else if (gMastered == 0)
    {
        ob->catch_msg("\nAnd suddenly everything is gone, great eagle, " +
            "fear, your blink and look upon your hand wielding the " +
            "dagger. It throbs with pain and you notice that the eagle's " +
            "beak on the pommel is bloodied and your wrist is wounded.\n");
        tell_room(environment(ob), QCTNAME(ob) + " blinks and " +
            POSSESSIVE(ob) + " eyes look normal again. Then " + PRONOUN(ob) +
            " notices that " + POSSESSIVE(ob) + " wrist is bleeding.\n", ob);

        ob->heal_hp(-300);

        set_hit(MIN_HIT);
        set_pen(MIN_PEN);
        ob->update_weapon(TO);

        return 1;
    }
}

/* Function name  : wield
 * Description    : Wield a weapon
 * Arguments      : wep - weapon
 * Returns        : 1      - if wielded
 *                  string - failure message if not wielded
 */
public mixed
wield(object wep)
{
    int skill = 59;

    if (TP->query_skill(SS_WEP_KNIFE) > skill )
    {
        write("You wield the " + short() + " and to your surprise " +
            "it starts to struggle for freedom from your hand!\n");
        say("As " + QTNAME(TP) + " wields the " + short() + ", it starts " +
            "to struggle for freedom from " + POSSESSIVE(TP) + " hand.\n");

        wielder = TP;
        alarm1_id = set_alarm(2.0, 0.0, &master_dagger(wielder));

        return 1;
    }

    return "Something within the " + short() + " seems to resist you.\n";

}

public void
check_active_alarms()
{
    if ( alarm1_id )
        remove_alarm(alarm1_id);

    if ( alarm2_id )
        remove_alarm(alarm2_id);

    if ( alarm3_id )
        remove_alarm(alarm3_id);

    if ( alarm4_id )
        remove_alarm(alarm4_id);

    if ( alarm5_id )
        remove_alarm(alarm5_id);

    if ( alarm6_id )
        remove_alarm(alarm6_id);
}

/* Function name  : unwield
 * Description    : Unwield a weapon
 * Arguments      : wep  - the weapon
 */
int
unwield(object what)
{
    wielder->catch_msg("You release the grip on the eagle's neck.\n");
    say(QCTNAME(wielder) + " releases the grip on the eagle's neck.\n");

    gMastered = 0;

    check_active_alarms();

    set_hit(TO_HIT);
    set_pen(TO_PEN);
    query_wielded()->update_weapon(TO);

    return 0;
}

/* Function name  : feed_me
 * Description    : Sends messages to player when the dagger becomes wilder
 *                  also clears the master, hit, pen and counter when its full
 */
int
feed_me(object enemy, object wielder)
{
    // If the dagger is fully feed it may become wild again.

    if ( gBites >= 50 && random(2))
    {
        wielder->catch_msg("\nAs the vision of the eagle appears in your " +
            "mind your dagger starts to struggle for freedom once " +
            "again.\n\n");
        enemy->catch_msg("The " + short() + " wielded by " + QTNAME(wielder) +
            " struggles in " + POSSESSIVE(wielder) + " hand.\n");
        wielder->tell_watcher("The " + short() + " wielded by " +
            QTNAME(wielder) +
            " struggles in " + POSSESSIVE(wielder) + " hand.\n", enemy);

        /* Set old values of to_hit and to_pen */
        set_hit(TO_HIT);
        set_pen(TO_PEN);
        wielder->update_weapon(TO);

        /* Clear the counter and master */
        gBites = 0;
        gMastered = 0;

        return 1;
    }

    switch (random(4))
    {
    case 0:
        wielder->catch_msg("\nSuddenly, a vision of the eagle ripping the " +
            "flesh of his victim up, appears in your mind.\n\n");
        break;
    case 1:
        wielder->catch_msg("\nA vision of the eagle swooping down on his " +
            "victim and driving his claws deep into its body, appears " +
            "in your mind.\n\n");
        break;
    case 2:
        wielder->catch_msg("\nA vision of the great eagle ripping his " +
            "victim up with the bloodied beak, appears in your mind.\n\n");
        break;
    case 3:
        wielder->catch_msg("\nYou shiver, as the great eagle swoops down " +
            "on his victim and tears it up with the bloodied claws.\n\n");
        break;
    }

    /* The dagger will slowly drain mana from those, who failed to master it
       and will make them unwield it if they are out of mana. */

    if ( gMastered == 0 && wielder->query_mana() < 2 )
    {
        wielder->catch_msg("Being exhausted by the visions, you decide " +
            "to put an end to them.\n");
        tell_room(E(wielder), QCTNAME(wielder) + " seems to be exhausted " +
            "as " + PRONOUN(wielder) + " unwields the " + short() + ".\n",
            wielder);
        wielder->command("$unwield wielded wide dagger");
    }
    else
        if ( gMastered == 0 && wielder->query_mana() > 1 )
            wielder->add_mana(-2);

    gBites += 1;

    return 1;
}

public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
    int phit, int dam)
{
    object blinding;
    string tmp, wound_adj;
    int not_npc = !(wielder->query_npc());

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if ( enemy->query_humanoid() && !enemy->query_prop(LIVE_I_NO_BODY) )
    {
        tmp = ({ "shoulder", "neck", "stomach", "chest", "right arm",
                     "left arm", "right leg", "left leg", "head", hdesc })[random(10)];
    }
    else
        tmp = ({ hdesc, "head" })[random(2)];

    if ( phurt == -1 || phurt == -2 )
    {
        if ( not_npc && !wielder->query_option(OPT_GAG_MISSES) )
        {
            wielder->catch_msg("You thrust at the " + tmp + " of " +
                QTNAME(enemy) + " with your " + short() + ", but your " +
                "attack has no result.\n");
        }
        if (interactive(enemy) && !enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(QCTNAME(wielder) + " thrusts at your " + tmp +
                " with " + POSSESSIVE(wielder) + " " + short() +
                ", but causes no damage.\n");
        }
        wielder->tell_watcher(QCTNAME(wielder) + " thrusts at the " + tmp +
            " of " + QTNAME(enemy) + " with " + POSSESSIVE(wielder) + " " +
            short() + ", but causes no damage.\n", enemy);

        return 1;

    }

    //    enemy->add_panic(3 + (phurt / 7));

    switch (phurt)
    {
    case 0:
        wielder->catch_msg("The tip of your " + short() + " barely tickles " +
            "the " + tmp + " of " + QTNAME(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " barely tickles your " + tmp +
            " with a tip of " + POSSESSIVE(wielder) + " " + short() + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " barely tickles the " + tmp +
            " of " + QTNAME(enemy) + " with a tip of " + POSSESSIVE(wielder) +
            " " + short() + ".\n", enemy);
        break;
    case 1..4:
        wielder->catch_msg("You graze the " + tmp + " of " + QTNAME(enemy) +
            " with a tip of your " + short() + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " grazes your " + tmp +
            " with a tip of " + POSSESSIVE(wielder) + " " + short() + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " grazes the " + tmp +
            " of " + QTNAME(enemy) + " with a tip of " + POSSESSIVE(wielder) +
            " " + short() + ".\n", enemy);
        break;
    case 5..9:
        wound_adj = ({ "shallow", "light", "minor", "mediocre" })[random(4)];

        wielder->catch_msg("You open a " + wound_adj + " wound in the " +
            tmp + " of " + QTNAME(enemy) + " with a wide blade of your " +
            "eagle-shaped dagger.\n");
        enemy->catch_msg(QCTNAME(wielder) + " opens a " + wound_adj  +
            " wound in your " + tmp + " with a wide " +
            "blade of " + POSSESSIVE(wielder) + " eagle-shaped.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " opens a " + wound_adj +
            " wound " +
            "int the " + tmp + " of " + QTNAME(enemy) + " with a wide blade " +
            "of " + POSSESSIVE(wielder) + " eagle-shaped dagger.\n", enemy);
        break;
    case 10..16:
        wielder->catch_msg("You skillfully pass the enemy's " +
            "defenses and cut " + POSSESSIVE(enemy) + " " + tmp +
            " with your " + short() + " severely.\n");
        enemy->catch_msg(QCTNAME(wielder) + " skillfully passes your " +
            "defenses and cuts your " + tmp + " with " + POSSESSIVE(enemy) +
            " " + short() + " severely.\n");
        wielder->tell_watcher(QCTNAME(wielder) +
            " skillfully passes the enemy's " +
            "defenses and cuts " + POSSESSIVE(enemy) + " " + tmp + " with the" +
            short() + " severely.\n", enemy);
        break;
    case 17..25:
        wielder->catch_msg("You pierce the " + tmp + " of " + QTNAME(enemy) +
            " with your " + short() + " wickedly.\n");
        enemy->catch_msg(QCTNAME(wielder) + " pierces your " + tmp +
            " with " + POSSESSIVE(wielder) + " " + short() + " wickedly.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " pierces the " + tmp + " of " +
            QTNAME(enemy) + " with " + POSSESSIVE(wielder) + " " + short() +
            " wickedly.\n", enemy);
        break;
    case 26..39:
        wound_adj = ({ "bleeding", "serious", "deep",
                           "badly looking" })[random(4)];

        wielder->catch_msg("You slash at " + QTNAME(enemy) +
            " with your " + short() + " opening a " + wound_adj + " wound in " +
            POSSESSIVE(enemy) + " " + tmp + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " slashes at you with " +
            POSSESSIVE(wielder) + " " + short() + " opening a " + wound_adj +
            " wound in your " + tmp + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " slashes at " + QTNAME(enemy) +
            " with " + POSSESSIVE(wielder) + " " + short() + " opening a " +
            wound_adj + " wound in " + POSSESSIVE(enemy) + " " + tmp + ".\n",
            enemy);
        break;
    case 40..54:
        wielder->catch_msg("You cunningly feint and stab " + QTNAME(enemy) +
            " in the " + tmp + " with your " + short() + " savagely.\n");
        enemy->catch_msg(QCTNAME(wielder) + " cunningly feints and stabs " +
            "you with " + POSSESSIVE(wielder) + " " + short() + " in the " +
            tmp + " savagely.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " cunningly feints and stabs " +
            QTNAME(enemy) + " with " + POSSESSIVE(wielder) + " " + short() +
            " in the " + tmp + " savagely.\n", enemy);
        break;
    case 55..99:
        wielder->catch_msg("You bury your " + short() + " into the " +
            tmp + " of " + QTNAME(enemy) + " to the hilt.\n");
        enemy->catch_msg(QCTNAME(wielder) + " buries " + POSSESSIVE(wielder) +
            " " + short() + " into your " + tmp + " to the hilt\n");
        wielder->tell_watcher(QCTNAME(wielder) + " buries " + POSSESSIVE(wielder) +
            " " + short() + " into the " + tmp + " of " + QTNAME(enemy) +
            " to the hilt.\n", enemy);
        break;
    default:
        wielder->catch_msg("You massacre the " + tmp + " of " +
            QTNAME(enemy) + " with a horrifying swing of your " + short() +
            ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " massacres your " + tmp +
            " with a horrifying swing of " + POSSESSIVE(wielder) + " " +
            short() + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " massacres the " + tmp + " of " +
            QTNAME(enemy) + " with a horrifying swing of " +
            POSSESSIVE(wielder) + " " + short() + ".\n", enemy);
        break;

    }

    /* If the hit is strong enough there is a chance that dagger becomes
       wilder */
    if ( dam > 60 && !random(3) )
    {
        wielder->catch_msg("The pommel of the dagger struggles slightly " +
            "in your hand.\n");
        feed_me(enemy, wielder);

    }

    return 1;
}


