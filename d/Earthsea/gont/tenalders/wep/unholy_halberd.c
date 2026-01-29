/*
 * unholy halberd
 *  Ten Alders 
 *  Amelia 5/3/97
 *
 * Fixed a bug causing runtime error in present in unwield
 * Put in a fix in case mana should compute as a positive number
 * Amelia 7/18/98
 * Mana consumption and unwield message changed.
 * Made Keepable Ckrik 7/1998
 * Magic Info updated. Ckrik 7/1998
 * ::did_hit added.  Amelia 7/26/98
 * Handle acrobatic miss. Ckrik 11/16/2021
 * Make into spell enhancer Ckrik 2/5/2022 
 *
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define SUBLOC "_unholy_aura_"
#define PLACES ({"left cheek", "right cheek", "right ear", "left ear", \
    "nose", "left thigh", "face", "left calf", "right calf", \
    "left knee", "right knee", "right thigh", "back", "chin", "groin", \
    "buttocks" })
#define HOWS ({ "vigorously", "nastily", "viciously", "evilly", \
    "cruelly", "fiercely", "wickedly", "deftly", "expertly", \
    "brutally", "savagely", "fanatically", "sadistically" })

public void
create_weapon()
{
    set_name("halberd");
    set_pname("halberds");
    set_adj("unholy");
    set_short("unholy halberd");
    set_long("A long-shafted halberd, which " +
        "must be wielded in both hands. It has a razor sharp " +
        "mithril axe blade on the end with a devilish hook behind. " +
        "When the halberd is swung or used in battle, dark " +
        "shadows seem to flow from it creating an aura. " +
        "The long haft is made from ebony, smoothly carved to fit " +
        "the hand and give just the right balanced weight to it. " +
        "The blade glows with a dark unholy light.\n");
    set_default_weapon(40, 49, W_POLEARM, W_BLUDGEON | W_SLASH | W_IMPALE,
        W_BOTH, this_object());
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(41);
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_AIR, SS_ELEMENT_FIRE, SS_ELEMENT_WATER
    }));
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 330);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "death" }) );
    /* As of right now there is no curse, but it will probably be
     * added in the future.
     */
    add_prop(MAGIC_AM_ID_INFO, ({
        "The weapon is cursed.\n", 10,
        "A dark aura surrounds the wielder when the weapon is " +
        "wielded.\n", 20,
        "The dark presence inside the halberd drains the wielder's " +
        "mana when attempting to wield the weapon.\n", 30,
        "However, a wise person might be able to prevent the dark " +
        "presence from leeching his or her mana.\n", 40,
        "The dark presence inside the halberd prevents it from ever " +
        "dulling.\n", 45 }));
    add_prop(OBJ_S_WIZINFO, "This halberd is wielded by " +
        "the karg captain in Ten Alders--Earthsea. The unholy " +
        "presence in the halberd hits for more damage. The " +
        "special is a regular hit, only there for cosmetics. " +
        "Since this weapon is enchanted it does not dull.\n");
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
    int dt, int phit, int dam)
{
    object me, *us;
    string place, how;

    if(random(8))
    {
        return 0;
    }

    // added 7/26/98 == Amelia
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    me = environment(this_object());
    how = HOWS[random(13)];
    place = PLACES[random(16)]; 

    if(random(20) > 13)
    {
        tell_room(environment(me), "Dark shadows swirl around " +
          "the unholy halberd.\n", ({}));
    }

    us = ({ me, enemy });

    switch(phurt)
    {
        case -1:
        case -2:
        case -3:
            enemy->catch_msg(QCTNAME(me) + " swings the " +
                query_short() + " just past your right ear. You hear a " +
                "loud hissing noise.\n");
            me->catch_msg("You barely miss " + QTNAME(enemy) +
                " with a wide swing of your " + query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " swings the " +
                query_short() + " just past " + QTNAME(enemy) +
                ", barely missing " + enemy->query_possessive() +
                " right ear.\n", enemy, us);
        break;

        case 0..1:
            enemy->catch_msg(QCTNAME(me) + " " + how + " slices your " +
                place + " with the " + query_short() +
                ", drawing a trickle of blood.\n");
            me->catch_msg("You " + how + " slice the " + place + " of " +
                QTNAME(enemy) + " with your " + query_short() +
                ", drawing a trickle of blood.\n");
            me->tell_watcher(QCTNAME(me) + " " + how + " slices the " +
                place + " of " + QTNAME(enemy) + " with " +
                me->query_possessive() + " " + query_short() +
                ", drawing a trickle of blood.\n", 
              enemy, us);
        break;

        case 2..3:
            enemy->catch_msg(QCTNAME(me) + " pierces your " + place +
                " with the " + query_short() + ".\n");
            me->catch_msg("You pierce " + QTNAME(enemy) + " in the "+
                place + " with your " + query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " pierces "+ QTNAME(enemy) +
                " in the "+ place + " with the " + query_short() + ".\n",
                enemy, us);
        break;

        case 7..10:
            enemy->catch_msg(QCTNAME(me) + " " + how + " gashes your " +
                place + " with the hook on the back side of the " +
                query_short() + ".\nYou break out in a cold sweat!\n");
            me->catch_msg("You " + how + " gash the " + place + " of " +
                QTNAME(enemy) + " with the hook on the back side of " +
                "the " + query_short() + "!\n" + QCTNAME(enemy) +
                " begins to sweat heavily!\n");
            me->tell_watcher(QCTNAME(me) + " " + how + " gashes the " +
                place + " of " + QTNAME(enemy) +
                " with the hook end of the " + query_short() + "!\n" +
                QCTNAME(enemy) + " begins to sweat heavily!\n",
                enemy, us);
        break;

        case 16..20:
            enemy->catch_msg(QCTNAME(me) + " viciously hacks your head " +
                "with the edge of the " + query_short() + "!\nYou are " +
                "almost decapitated!\n");
            me->catch_msg("You viciously hack at the head of " +
                QTNAME(enemy) + " with your " + query_short() +
                "!\nYou almost succeed in decapitating " +
                enemy->query_objective() + ".\n");
            me->tell_watcher(QCTNAME(me) + " viciously hacks at the " +
                "head of " + QTNAME(enemy) + " with the " +
                query_short() + "!\n" + QCTNAME(enemy) +
                " is almost decapitated!\n", enemy, us);
        break;

        default:
            enemy->catch_msg(QCTNAME(me) + " " + how + " slashes your " +
                place + " with the blade of the " + query_short() +
                ".\n");
            me->catch_msg("You " + how + " slash " + QTNAME(enemy) +
                "'s " + place + " with the blade of your " +
                query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " " + how +
                " slashes the " + place + " of " + QTNAME(enemy) + ".\n",
                enemy, us);
        break;
    }

    if(enemy->query_hp() <= 0)
    {
        enemy->catch_msg("You die screaming!\n" +
            "As your soul leaves its body, the last thing you see " +
            "are the black shapes of the Nameless Ones, coming to " +
            "collect you!\n");
        tell_room(environment(me), QCTNAME(enemy) + " dies screaming!\n" +
            "A horrible wailing noise trails off into the distance...\n",
            ({ enemy }));
        enemy->do_die(me);

        return 1;
    }

    return 1;
}

public mixed
wield(object what)
{
    object tp = this_player();
    int mana, wis = tp->query_stat(SS_WIS);

    if(wis < 60)
    {
        return "You are not wise enough to wield the " +
            query_short() + ".\n";
    }

    //Mana consumption is 200 to 400 - the wielder's wisdom. Ckrik 7/1998
    mana = -1 * (200 + random(200) - wis);

    if(tp->query_mana() > -1 * mana)
    {
        tp->catch_msg("A dark aura surrounds you as you wield the " +
            query_short() + ".\nYou hear a loud crash of thunder!\n");
        tell_room(environment(tp), "As " + QTNAME(tp) + " wields " +
            "the " + query_short() + ", " + tp->query_pronoun() + " is " +
            "shrouded in a dark aura!\nYou hear a loud crash of " +
            "thunder!\n", ({ tp }));
        tp->add_subloc(SUBLOC, this_object());
        tp->catch_msg("You feel mentally drained as you wield the " +
            query_short() + "!\n");
        tp->add_mana(mana);

        return 0;
    }

    return "Your mind is not strong enough to wield the " +
        query_short() + ".\n";
}

public int
unwield()
{
    object wielder = query_wielded(), tp;

    if(!wielder || wielder != (tp = this_player()))
    {
        return notify_fail("You don't wield the " +
            query_short() + ".\n");
    }

    /*
    tp->remove_subloc(SUBLOC);
    tp->catch_msg("As you unwield the "+query_short()+
        ", the dark aura dissipates and the world looks brighter.\n");
    return 1;
    */

    tp->catch_msg("The dark aura sticks to you!\n");

    return 0;
}

public string
show_subloc(string subloc, object wielder, object for_obj)
{
    string str;

    if(wielder->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if(for_obj == wielder)
    {
        return "You are shrouded in a dark unholy aura.\n";
    } else {
        return capitalize(wielder->query_pronoun()) +
            " is shrouded in a dark unholy aura.\n";
    }
}

public int
swing_it(string str)
{
    object tp = this_player(), to = this_object();

    if(id(str) && (!present(to, tp)))
    {
        tp->catch_msg("You don't have the halberd.\n");
        return 1;
    }

    if(id(str) && (!query_wielded()))
    {
        tp->catch_msg("You do not wield the halberd.\n");
        return 1;
    }

    if(id(str))
    {
        tp->catch_msg("As you swing the " + query_short() +
            " wildly about your head, dark shadows emanate from it, " +
            "filling the area and surrounding you in a dark aura.\n");
        tell_room(environment(tp), QCTNAME(tp) + " swings the " +
            query_short() + " wildly about " + tp->query_possessive() +
            " head, and shadows emanate from the blade and surround " +
            tp->query_objective() + "!\n", ({ tp }));
        return 1;
    }

    return notify_fail("Swing what? Are you a monkey?\n");;
}


public void
init()
{
    ::init();
    add_action(swing_it, "swing");
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
