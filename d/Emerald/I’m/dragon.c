/*
 *  /d/Emerald/blackwall/npc/shadow_dragon.c
 *
 *  The Shadow Dragon of Emerald. One of the most fearsome
 *  creatures to survive the end of the Dark Time and the
 *  supremacy of the Elves. This creature rules over the
 *  Blackwall Mountains, worshipped as a God by the beings
 *  who live within its domain. It is also a part of the
 *  quest to join the Blackwall Mountain Clans Race Guild.
 *
 *  Copyright (c) November 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro";

#include <const.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define    THIS_LOG     ("/d/Emerald/log/shadow_dragon")
#define    BELLY        ("/d/Emerald/aod/rooms/belly")

/* global variables */
public mixed         Kneeling = 0; /* player kneeling to be eaten */
public mixed         Sick = 0;     /* player soon to be regurgitated */


/* prototypes */
public string        all_caps(string text);
public void          create_emerald_monster();
public void          add_introduced(string name);
public void          react_intro(object tp);
public void          greet(object who);
public void          add_dragon_emotes();
public int           special_attack(object enemy);
public varargs int   swipe(object victim);
public void          eat_victim(object victim);
public void          run_away();
public mixed         check_kneeling();
public void          do_kneel(string arg);
public void          sacrifice1(object victim);
public void          sacrifice2(object victim);
public void          sacrifice3(object victim);
public void          sacrifice4(object victim);
public void          sacrifice_gone(object victim);
public void          init_living();
public void          regurgitate1(object victim);
public void          regurgitate2(object victim);
public void          regurgitate3(object victim);



/*
 * Function name:        all_caps
 * Description  :        capitalize an entire string.
 *                       Special thanks to Mercade for this function.
 * Arguments    :        string text - the string
 * Returns      :        the capitalized string
 */
public string
all_caps(string text)
{
    return implode(map(explode(text, ""), capitalize), "");
} /* all_caps */


/*
 * function name:        create_emerald_monster
 * description  :        set up the npc with domain presets
 */
public void
create_emerald_monster()
{
    set_name("yogsathoth");
    set_race_name("dragon");

    add_name("_emerald_shadow_dragon");
    add_dragon_emotes();

    set_gender(G_FEMALE);
    set_title("the Devourer, Shadow Dragon of Emerald");

    set_adj( ({ "gigantic", "black", "shadow" }) );
    set_short("gigantic shadow dragon");

    set_long("With a sense of wonder, you look upon"
      + " the towering black shape which fills this area -"
      + " Yogsathoth the Devourer, Shadow Dragon of Emerald."
      + " She suffers the presence of none but those who worship"
      + " her as a God, and even they are seldom spared her"
      + " violence.\n"); 


    /* her stats are godly */
    set_stats( ({ 350+random(150), 400+random(100), 450+random(50),
                  500,             150+random(350), 500 }) );

    set_alignment(-1200); /* lawful evil */

    set_all_attack_unarmed(100, 100); /* godly */
    set_all_hitloc_unarmed(100); // 100 pts of armour for all hitlocs
    set_hitloc_unarmed(A_BODY, 100, 45, "body"); // 100 pts for body

    /* she fights with her body, and sees all */
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);

    set_whimpy(0);  /* beyond fear */

    remove_prop(LIVE_I_NEVERKNOWN);

    FIX_EUID
} /* create_emerald_monster */


/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(this_player()) &&
        CAN_SEE_IN_ROOM(this_object()) &&
        CAN_SEE(this_object(), this_player()) &&
        (!this_player()->query_met(query_name()) ||
          this_player()->query_wiz_level()))
    {
        set_alarm(1.0 + (2.0 * rnd()), 0.0,
                  &react_intro(this_player()));
    }
} /* add_introduced */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
find_living("gorboth")->catch_msg("DEBUG: react_intro called.\n");
    if (!present(tp, environment(this_object())))
    {
        command("emote intones: FOOLISH ARE THEY WHO SPEAK AND DO NOT"
          + " REMAIN TO LISTEN.");
        return;
    }

    command("emote intones: YES, MORTAL, KNOW THE NAME OF THY GOD.");
    command("introduce me");
} /* react_intro */


/*
 * Function name: greetings 
 * Description:   Redefinition from /d/Genesis/lib/intro to make
 *                the dragon less "polite."
 * Arguments:     object who - the living that introduced to me
 *
 */
public void
greet(object who)
{
    command("intones: YOU ARE KNOWN TO ME, "
      + all_caps(who->query_real_name()) + ". KNEEL BEFORE"
      + " YOUR GOD.");
} /* greet */


/*
 * Function name:        add_dragon_emotes
 * Description  :        the emotes for the beast
 */
public void
add_dragon_emotes()
{
    set_chat_time(15 + random(15));
    add_chat("I AM YOGSATHOTH THE DEVOURER. LOOK UPON ME, YE"
      + " MORTAL, AND DESPAIR.");
    add_chat("WORSHIP ME, ALL YE WHO WALK UPON THE LANDS.");
    add_chat("BEHOLD, YOU ARE COME BEFORE YOUR GOD.");
    add_chat("MY HUNGER SHALL FULFILL YOUR FINAL PURPOSE. KNEEL"
      + " AND FIND COMFORT IN DEATH.");

    set_cchat_time(5 + random(10));
    add_cchat("EVEN AS I REND YOUR FLESH SHALL YOU WORSHIP"
      + " ME.");
    add_cchat("SO, YOU CHOOSE THE RITUAL OF DEATH.");
    add_cchat("THROUGHOUT ETERNITY I HAVE SMOTE DOWN THE PROUD"
      + " IN THEIR CONCEIT. HUMBLE THYSELF, MORTAL.");
    add_cchat("SO IT SHALL COME TO PASS ... YOUR FLESH IN MY"
      + " FLESH. YOUR LIFE SHALL EASE MY HUNGER.");
    add_cchat("PREPARE THYSELF. YOUR FINAL DEED IN LIFE IS DONE.");

    set_act_time(15 + random(15));
    add_act("emote moves her massive frame, and the ground shakes.");
    add_act("emote turns her eyes toward you, their black depths"
      + " peering without feeling into your mind.");
    add_act("emote slowly moves the coils of her tail along the"
      + " floor, scraping deep grooves in the ground.");

    set_cact_time(2 + random(2));
    add_cact("emote opens her mouth, and belches forth a skull-"
      + "tingling roar.");
    add_cact("emote raises to her full height. The sight is"
      + " of such devastating proportion, you almost feel"
      + " nausated.");
    add_cact("narrows her eyes, and shadows seem to crawl at"
      + " you from every direction at once.");

} /* add_dragon_emotes */


/*
 * Function name:        special_attack
 * Description  :        this is the npc's special
 *                       melee attack
 * Arguments    :        object enemy - who the npc fights
 * Returns      :        0 - no special attack
 *                       1 - special attack
 */
public int
special_attack(object enemy)
{
    set_alarm(0.0, 0.0, &swipe(enemy));
    return 1;

} /* special_attack */


/*
 * Function name:        swipe
 * Description  :        this is the npcs's special attack. It is
 *                       the dragon swinging her huge claws at
 *                       the player in an attempt to break their
 *                       body.
 * Arguments    :        object victim - the player
 * Returns      :        integer 1
 */
public varargs int
swipe(object victim)
{
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    mixed  *sdam;
    string *hitloc;
    string  his = victim->query_possessive();
    string  him = victim->query_objective();
    string  he  = victim->query_pronoun();
    string  swipe_msg;

    if (!objectp(victim) && !sizeof(enemies))
    {
        return 1;
    }

    if (!objectp(victim))
    {
        victim = enemies[random(sizeof(enemies))];
    }

    if (ENV(victim) != ENV(TO))
    {
        return 1;
    }

    sdam = victim->hit_me(F_PENMOD(100, 100), W_BLUDGEON, TO, -1);
    swipe_msg = QCTNAME(this_object()) + " draws back, and swings"
      + " her massive paw across the room. ";

    switch(sdam[0])
    {
        case 0:
            victim->catch_msg(swipe_msg + "Casting yourself aside,"
              + " the great claws pass just over you, and you are"
              + " rolled sidewise by the great force of wind"
              + " generated by the attack!\n"); 
            say(swipe_msg + QTNAME(victim) + "throws " + him
              + "self out of the way just in time but is still"
              + " knocked over by the force of wind generated by"
              + " the attack!\n", victim);
            break;
        case 1..5:
            victim->catch_msg(swipe_msg + "You swing your body wildly"
              + " to the left, attempting to avoid the attack, but"
              + " one claw knocks your feet out from under you,"
              + " slamming you shoulder-first into the ground!\n");
            say(swipe_msg + QTNAME(victim) + " swings " + his
              + " body wildly to one side, attempting to avoid the"
              + " attack, but one claw knocks " + his + " feet out"
              + " from under " + him + ", knocking " + him
              + " shoulder-first into the ground!\n", victim);
            break;
        case 6..20:
            victim->catch_msg(swipe_msg + "Though you attempt to"
              + " fling your body aside, the blow catches you mid-"
              + " crouch and sends you skidding along the floor,"
              + " tumbling painfully into a heap yards away from"
              + " where you were standing!\n");
            say(swipe_msg + QTNAME(victim) + " crouches to jump out"
              + " of the way and is caught by the blow, sending "
              + him + " skidding along the floor where " + he 
              + " tumbles painfully to a heap yards from where "
              + he + " had been standing!\n", victim);
            break;
        case 21..50:
            victim->catch_msg(swipe_msg + "Before you know what is"
              + " happening, a terrible crushing force sends you"
              + " sailing across the room where you land in a"
              + " painful heap!\n");
            say(swipe_msg + QTNAME(victim) + " is caught by the"
              + " great paw, which sends " + his + " body flying"
              + " across the room as if " + he + " were a rag"
              + " doll!\n", victim);
            break;
        case 51..99:
            victim->catch_msg(swipe_msg + "You turn just in time to"
              + " see the great paw coming at you like an avelanche!"
              + " Terrifying pain crushes into you, sending you"
              + " flying headlong into the rock wall twenty yards"
              + " away! Sliding to the ground, you try to prop"
              + " yourself back up, the room spinning wildly around"
              + " you.\n");
            say(swipe_msg + QTNAME(victim) + " turns just in time"
              + " to see the paw before it hits " + him + ". With"
              + " a sickened sense of awe, you watch as "
              + QTNAME(victim) + " is flung with terrible speed"
              + " into the far wall of the cave, " + his + " head"
              + " smashing directly into the rock! You are certain "
              + he + " is dead, and yet amazingly, " + he + " rises"
              + " staggeringly to " + his + " feet, and stumbles"
              + " back into the fray.\n", victim);
            break;
        default:
            victim->catch_msg(swipe_msg + "Suddenly the world is"
              + " moving in slow motion. You feel yourself turning,"
              + " late - much too late. The sound is drained from the"
              + " room as the great black paw descends upon you. Just"
              + " before it hits, sound and speed return to your senses"
              + " in a rush, as your frame is crushed into the ground,"
              + " most of your bones and your spine breaking in the"
              + " same instant!\n");
            say(swipe_msg + "You realize with horror that "
              + QTNAME(victim) + " is now helpless in the path of"
              + " the oncoming blow. With a feeling of nausea, you"
              + " watch as the great black paw of the dragon slams"
              + " down on " + QTNAME(victim) + " like a meteor,"
              + " utterly crushing " + him + " beneath!\n", victim);
            break;
    }

    if (victim->query_hp() == 0)
    {
        eat_victim(victim);
        victim->do_die(TO);
find_living("gorboth")->catch_msg("DEBUG: do_die called.\n");
    }

    return 1;
} /* heave */


/*
 * Function name:        eat_victim
 * Description  :        The dragon eats what she kills!
 * Arguments    :        object victim - the soon-to-be-dead player
 */
public void
eat_victim(object victim)
{
    string  him = victim->query_objective();

    victim->catch_msg("Though you are nearly unconscious, you"
      + " see that you are being lifted by a great and powerful"
      + " force high above the ground. As your vision steadies,"
      + " you see before you the terrible face of the dragon,"
      + " her eyes appraising you without malice or pity.\n");
    say("The dragon lifts the broken body of " + QTNAME(victim)
      + " from the ground, and holds " + him + " directly in"
      + " front of great pitiless eyes.\n", victim);

    command("emote intones: NOW YOU SHALL KNOW YOUR GOD, MORTAL.");

    victim->catch_msg("The great mouth opens to display a dizzying"
      + " array of white teeth before a gaping blackness. Suddenly,"
      + " you are thrust toward the blackness, and devoured!\n");
    say("The dragon opens its mouth, and bites " + QTNAME(victim)
      + " in half! Chewing slowly, she then devours the rest of "
      + him + "!\n", victim);

    victim->do_die(TO);

    set_alarm(1.0, 0.0, tell_room(environment(this_object()),
        QTNAME(victim) + " has been eaten by "
      + QTNAME(this_object()) + "!\n"));
} /* eat_victim */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    if (environment(this_object())->id("_del_rimmon_captain_room"))
    {
        tell_room(environment(this_object()), 
            QCTNAME(this_object()) + " cries out: Fool! The"
              + " Darklings already know of your sins! They will"
              + " send others, and then you will pay for them!\n"
              + QCTNAME(this_object()) + " falls from the ledge"
              + " to the ground, and his eyes glaze over.\n");
    }
    else
    {
        tell_room(environment(this_object()),
            QCTNAME(this_object()) + " cries out: Fool! The"
              + " Darklings already know of your sings! They will"
              + " send others, and then you will pay for them!\n"
              + QCTNAME(this_object()) + " collapses, and his"
              + " eyes glaze over.\n");
    }

    if (living(killer))
    {
        tell_object(killer, 
            "You killed " + query_the_name(this_object()) + ".\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " killed " +  query_objective() + ".\n",
           ({ this_object(), killer }));
    }

//  write_file(THIS_LOG, killer->query_name() + " ("
//    + killer->query_average_stat() + ") killed Akugla, "
//    + ctime(time()) + ".\n\tWeapon acuired = "
//    + Weapon->short() + ".\n");
} /* notify_death */


/*
 * Function name:        run_away
 * Description  :        we mask the fun from /std/living/combat.c to
 *                       keep her from ever wimpying.
 */
public void
run_away()
{
    command("blink slow");
    command("emote intones: YOU CANNOT BRING FEAR TO A GOD, MORTAL.");

    return;
} /* run_away */


/*
 * Function name:        check_kneeling
 * Description  :        a sanity check to see if Kneeling actually
 *                       represents a person in the same room as the
 *                       dragon.
 * Returns      :        mixed - Kneeling if here,
 *                               0 otherwise
 */
public mixed
check_kneeling()
{
    if (!Kneeling)
    {
        return 0;
    }

    if (environment(Kneeling) != environment(this_object()) )
    {
        Kneeling = 0;
    }

    return Kneeling;
} /* check_kneeling */


/*
 * Function name:        do_kneel
 * Description  :        allow the player to kneel before the dragon
 *                       as a sacrificial offering.
 * Arguments    :        string arg - what the player typed
 * Return       :        1 - success, 0 - failure 
 */
public int
do_kneel(string arg)
{
    if (strlen(arg))
    {
find_living("gorboth")->catch_msg("DEBUG: do_kneel: arg = "+arg+"\n");
        if (!parse_command(arg, ({}),
            "[before] [the] [gigantic] [black] [shadow]"
          + " 'dragon' / 'yogsathoth'"))
        {
find_living("gorboth")->catch_msg("DEBUG: not acceptable arg, dropping.\n");
            return 0;
        }
    }

    if (check_kneeling())
    {
        if (Kneeling == this_player())
        {
            write("You are already kneeling before the dragon!\n");
            return 1;
        }

        this_player()->catch_msg(QCTNAME(Kneeling) + " is already"
          + " kneeling before the dragon. You'll have to wait your"
          + " turn.\n");
        return 1;
    }

    if (Sick)
    {
        write("The dragon looks to have a bit of an upset stomach at the"
          + " moment. Perhaps now is not the time.\n");
        return 1;
    }

    write("You present yourself as a sacrifice before the dragon, and"
      + " kneel.\n");
    tell_room(environment(this_object()),
        QCTNAME(this_player()) + " kneels before the dragon, offering "
      + this_player()->query_objective() + "self as a sacrifice!\n",
        this_player());

    Kneeling = this_player();

    set_alarm(2.0, 0.0, &sacrifice1(this_player()) );
    return 1;
} /* do_kneel */


/*
 * Function name:        sacrifice1
 * Description  :        The first in a series of warnings for the player
 */
public void
sacrifice1(object victim)
{
    if (!check_kneeling())
    {
        sacrifice_gone(victim);
        return;
    }

    victim->catch_msg("The dragon lowers her gaze, and studies you. You"
      + " feel your heart begin to beat faster.\n");
    tell_room(environment(this_object()),
        "The dragon lowers her gaze to study " + QTNAME(victim) + ".\n",
        victim);

    set_alarm(10.0, 0.0, &sacrifice2(victim));
    return;
} /* sacrifice1 */


/*
 * Function name:        sacrifice2
 * Description  :        The second in a series of warnings for the player
 */
public void
sacrifice2(object victim)
{
    if (!check_kneeling())
    {
        sacrifice_gone(victim);
        return;
    }

    command("emote intones: YOU WORSHIP ME. YES, THIS IS AS IT SHOULD"
      + " BE. REMAIN STILL, THAT YOU MAY KNOW YOUR GOD.");
    victim->catch_msg("You feel sweat beginning to trickle down your"
      + " cheeks.\n");

    set_alarm(10.0, 0.0, &sacrifice3(victim));
    return;
} /* sacrifice2 */


/*
 * Function name:        sacrifice3
 * Description  :        The final warning for the player
 */
public void
sacrifice3(object victim)
{
    if (!check_kneeling())
    {
        sacrifice_gone(victim);
        return;
    }

    command("emote draws herself up to her full height, and opens her"
      + " mouth wide. Her long neck arches back, poised to strike.");
    victim->catch_msg("Your eyes dart up, and you know that the dragon"
      + " will devour you if you do not flee.\n\nRun! Flee or be"
      + " eaten! GO NOW!!\n");
    tell_room(environment(this_object()),
        QCTNAME(victim) + "'s eyes dart up, and you see that "
      + victim->query_pronoun() + " is thinking of dashing out of"
      + " the room while there is yet a chance.\n", victim);

    set_alarm(15.0, 0.0, &sacrifice4(victim));
    return;
} /* sacrifice3 */


/*
 * Function name:        sacrifice4
 * Description  :        The player is eaten and by the dragon. If
 *                       the player is a goblin, they survive the
 *                       ordeal and end up in the dragon's belly.
 */
public void
sacrifice4(object victim)
{
    if (!check_kneeling())
    {
        sacrifice_gone(victim);
        return;
    }

    command("emote lunges downward, jaw open wide!");
    victim->catch_msg("In an instant, the Dragon swallows you"
      + " whole!\n");
    tell_room(environment(this_object()),
        "In an instant, the dragon swallows " + QTNAME(victim)
      + " whole!\n", victim);
    victim->catch_msg("You feel yourself being forced down through"
      + " the moist throat of the dragon, the powerful neck muscles"
      + " crushing your body as you pass into ... \n");

    victim->move_living("M", BELLY, 1, 0);
    tell_room(environment(victim),
        QCTNAME(victim) + " falls in from above.\n", victim);
    victim->heal_hp(-50000);
    Kneeling = 0;

    if (victim->query_race() != "goblin")
    {
        tell_room(environment(this_object()),
            QCTNAME(victim) + " died.\n"
          + QCTNAME(this_object()) + " ate " + victim->query_objective()
          + "!\n");

        victim->do_die();
        return;
    }

    Sick = victim;
    set_alarm(10.0, 0.0, &regurgitate1(victim));

    return;
} /* sacrifice4 */


/*
 * Function name:        sacrifice_gone
 * Description  :        The dragon reacts to a player who has run
 *                       away after having knelt for sacrifice.
 * Arguments    :        object victim - the player who had knelt
 */
public void
sacrifice_gone(object victim)
{
    string roar_text = "RETURN AT ONCE, "
      + all_caps(victim->query_real_name()) + ". TURN NOT THY BACK"
      + " UPON THY GOD.";
//  string roar_text = capitalize("return at once, "
//    + victim->query_real_name() + ". turn not thy back upon thy"
//    + " god.", 1);

    command("emote pauses, having noticed that her sacrifice has fled.");
    command("emote roars: " + roar_text);

    if (environment(victim) != environment(this_object()) )
    {
        victim->catch_msg("In the distance, you hear the dragon roar: "
          + roar_text + "\n");
    }

    return;
} /* sacrifice_gone */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init_living()
{
    ::init_living();

    add_action(do_kneel, "kneel");
    add_action(do_kneel, "worship");
} /* init_living */


/*
 * Function name:        regurgitate1
 * Description  :        goblins don't agree with the dragon, it will
 *                       throw up the player in a moment
 * Arguments    :        object victim - the player
 */
public void
regurgitate1(object victim)
{
    if (environment(victim) != find_object(BELLY))
    {
        Sick = 0;
        Kneeling = 0;
        return;
    }

    command("emote looks suddenly very ill.");
    victim->catch_msg("The walls and floor around you heave suddenly,"
      + " and you hear a deep rumbling sound.\n");

    set_alarm(10.0, 0.0, &regurgitate2(victim));
} /* regurgitate1 */

/*
 * Function name:        regurgitate2
 * Description  :        goblins don't agree with the dragon, it will
 *                       throw up the player in a moment
 * Arguments    :        object victim - the player
 */
public void
regurgitate2(object victim)
{
    if (environment(victim) != find_object(BELLY))
    {
        Sick = 0;
        Kneeling = 0;
        return;
    }

    command("emote blanches, and grabs her stomach!");
    victim->catch_msg("The rumbling becomes violent, you feel the"
      + " floor beginning to rise, lifting you higher by the"
      + " second!\n");

    set_alarm(10.0, 0.0, &regurgitate3(victim));
} /* regurgitate1 */


/*
 * Function name:        regurgitate3
 * Description  :        goblins don't agree with the dragon, it will
 *                       throw up the player now
 * Arguments    :        object victim - the player
 */
public void
regurgitate3(object victim)
{
    if (environment(victim) != find_object(BELLY))
    {
        Sick = 0;
        Kneeling = 0;
        return;
    }

    tell_room(environment(this_object()), QCTNAME(this_object())
      + " heaves forward suddenly, vomiting violently! To"
      + " your astonishment, you see " + QTNAME(victim) + " fly"
      + " from her mouth, and go sailing through the cave entrance"
      + " to the south!\n");
    victim->catch_msg("With a final spasm, the cave walls slam into"
      + " you from below. Before you know what is happening, a rush"
      + " of images fly past you and you are spewed forth, flying"
      + " through the air, to land outside the cave of the dragon!\n");

    victim->move_living("M", environment(this_object()), 1, 1);

    Kneeling = 0;
    Sick = 0;
} /* regurgitate3 */
