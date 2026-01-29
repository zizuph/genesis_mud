/*
 *  /d/Emerald/blackwall/delrimmon/npc/captain.c
 *
 *  This orc is one of the more powerful members of the
 *  roving bands which are loosely controlled by the
 *  Darklings. This one commands a group of orcs he
 *  has lead to this cave, who are wreaking havoc on
 *  the Valley of Del Rimmon in their crude way.
 *
 *  Copyright (c) September 2001, by Cooper Sherry (Gorboth)
 *  
 *  2021-01-02 - Cotillion
 *  - Switched from write_file to log_file to rotate logs.
 *  - Made elite weapons use clone_unique
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/npc/blackwall_orc";
inherit "/lib/unique";

#include <const.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define    THIS_LOG     ("del_rimmon/akugla")
#define    DR_WEP       ("/d/Emerald/blackwall/delrimmon/obj/wep/")
#define    DR_ARM       ("/d/Emerald/blackwall/delrimmon/obj/arm/")
#define    ELITE        ( ({ DR_WEP + "wr_sword", \
                             DR_WEP + "r_axe", \
                             DR_WEP + "d_sword", \
                             DR_WEP + "wraith_bane_polearm", \
                             DR_WEP + "osword", \
                             DR_WEP + "wraith_bane" \
                        }) )


/* prototypes */
public void          create_blackwall_orc();
public void          add_blackwall_emotes();
public string        outpost_answer();
public string        discover_answer();
public string        reward_answer();
public string        climber_answer();
public string        door_answer();
public string        sign_answer();
public int           special_attack(object enemy);
public varargs int   heave(object victim); 
public varargs void  arm_me();
public void          captain_gem();
public void          run_away();
public void          attacked_by(object attacker);


/* global variables */
public object        Weapon; /* the elite weapon he has */


/*
 * function name:        create_blackwall_orc
 * description  :        set up the npc with isengard presets
 */
public void
create_blackwall_orc()
{
    set_name("akugla");
    add_name("del_rimmon_akugla");
    add_name("captain");
    set_gender(G_MALE);
    set_adj( ({ "huge", "black" }) );
    set_short("huge black orc captain");
    set_long("Huge and towering, this is one of the largest orcs"
      + " you have seen. His hulking frame is strapped by great"
      + " and powerful-looking muscles which twist with his every"
      + " movement. He carries himself as if he were some sort of"
      + " captain, ruling over his lesser orcs with terrible wrath"
      + " and violence.\n");


    set_stats(({175+random(10), 245+random(10), 280+random(10),
                125+random(10), 55+random(10), 145+random(10)}));
    set_alignment(-500);

    set_all_attack_unarmed(60, 60);
    set_all_hitloc_unarmed(40); // 40 pts of armour for all hitlocs
    set_hitloc_unarmed(A_BODY, 70, 45, "body"); // 70 pts for body

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);

    set_whimpy(0);  /* this guy is proud and fearless */

    FIX_EUID

    captain_gem();
} /* create_blackwall_orc */

/*
 * Function name:        add_blackwall_emotes
 * Description  :        we redefine this function to add special
 *                       actions for the captain alone
 */
public void
add_blackwall_emotes()
{
    set_chat_time(15 + random(15));
    add_chat("If these pathetic orcs don't stop their belly-"
      + "aching, I'll send them back to camp in pieces!");
    add_chat("The elves built these fortresses for a reason,"
      + " and it wasn't just to train troops!");
    add_chat("Soon I'll discover what went on here, and then"
      + " I'll have my reward!");
    add_chat("If only I could open those accursed doorways!");

    set_cchat_time(5 + random(10));
    add_cchat("See? I am your master now, maggot!");
    add_cchat("You're less a challenge than my brother's wife!");
    add_cchat("I shall paint this cavern with your blood!");
    add_cchat("Your broken body will improve my mood greatly!");
    add_cchat("No weapon, and still I break you like a twig!");

    set_act_time(15 + random(15));
    add_act("swear");
    add_act("emote paces back and forth along the ledge.");
    add_act("grumble");

    set_cact_time(2 + random(2));
    add_cact("emote repositions himself on the ledge and taunts"
      + " you.");
    add_cact("shout You pathetic orcs shall pay dearly for letting"
      + " this fool disturb me!");
    add_cact("emote laughs at you as he comes in for another"
      + " attack.");
    add_cact("roar");

    add_ask( ({ "fortresses", "fortress", "fort", "forts",
                "outpost", "outposts", "structure",
                "structures" }),
        VBFC_ME("outpost_answer"));
    add_ask( ({ "discover", "discovery", "mystery", "what went on",
                "secret", "secrets" }),
        VBFC_ME("discover_answer"));
    add_ask( ({ "reward", "rewards" }),
        VBFC_ME("reward_answer"));
    add_ask( ({ "climb", "climber", "climbers", "tall rock",
                "peak", "tall peak" }),
        VBFC_ME("climber_answer"));
    add_ask( ({ "door", "doors", "doorway", "doorways" }),
        VBFC_ME("door_answer"));
    add_ask( ({ "sign", "signs", "symbol", "symbols" }),
        VBFC_ME("sign_answer"));
} /* add_blackwall_emotes */



/***** ask routines below here *****/



/*
 * Function name:       outpost_answer
 * Description  :       respond to questions about outposts
 * Returns      :       null string ... response is gen'd via command()
 *
 * add_ask( ({ "fortresses", "fortress", "fort", "forts",
 *             "outpost", "outposts", "structure",
 *             "structures" }),
 */
public string
outpost_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The elves may be idiots, but they never build"
          + " anything without a good reason!");
        break;
    case 1:
        command("say There has simply got to be something here!");
        break;
    case 2:
        command("say There is a mystery hidden in these outposts,"
          + " and I intend to figure out what it is!");
        break;
    }
    return "";
} /* outpost_answer */



/*
 * Function name:       discover_answer
 * Description  :       respond to questions about discovery
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({ "discover", "discovery", "mystery" }),
 */
public string
discover_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The elves cannot hide their secrets from me!");
        break;
    case 1:
        command("say Soon, it will not be a mystery anymore!");
        break;
    case 2:
        command("say I'll tell you nothing! The secrets are mine!");
        break;
    }
    return "";
} /* discover_answer */


/*
 * Function name:       reward_answer
 * Description  :       respond to questions about a reward
 * Returns      :       null string ... response is gen'd via command()
 */
public string
reward_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Oh, the Darklings will reward me well!");
        break;
    case 1:
        command("say If these fools don't shape up, I'll kill them"
          + " and take the reward all for myself!");
        break;
    case 2:
        command("say Yes, there will be a reward, and it will be mine!");
        break;
    }
    return "";
} /* reward_answer */


/*
 * Function name:       door_answer
 * Description  :       respond to questions about the doors
 * Returns      :       null string ... response is gen'd via command()
 */
public string
door_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The climbers found a second door above the"
          + " waterfall!");
        break;
    case 1:
        command("say No handles, no hinges, nothing! These elves"
          + " are total idiots!");
        break;
    case 2:
        command("say Damnation! How I wish we could open them!");
        break;
    }
    return "";
} /* door_answer */


/*
 * Function name:       climber_answer
 * Description  :       respond to questions about the climbers
 * Returns      :       null string ... response is gen'd via command()
 */
public string
climber_answer()
{
    switch (random(3))
    {
    case 0:
        command("say A second doorway, and the strange signs! I wish"
          + " I could see them with my own eyes.");
        break;
    case 1:
        command("say If I knew how to climb, I'd be up there myself!");
        break;
    case 2:
        command("say The signs that they saw on the tall peak ... what"
          + " could they be?");
        break;
    }
    return "";
} /* climber_answer */


/*
 * Function name:       sign_answer
 * Description  :       respond to questions about signs and symbols
 * Returns      :       null string ... response is gen'd via command()
 */
public string
sign_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Aaargh! The elves are taunting me with their"
          + " damned symbols!");
        break;
    case 1:
        command("say I will decipher them! ... but how ... ");
        break;
    case 2:
        command("say I am sure that those symbols are the key to"
          + " all of this!");
        break;
    }
    return "";
} /* sign_answer */


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
    int     attack_type = random(20);
    object  myself      = this_object(),
            room        = environment(myself),
            badness,
           *opponents   = filter(all_inventory(environment(myself)),
                          &operator(==)(, myself) @ &->query_attack());

    if (sizeof(opponents) > 1)
    {
        if (badness = present(BADNESS, room))
        {
            badness->increase_intensity();
        }
        else
        {
            command("emote throws a glowing purple globe from the"
              + " ledge. Upon striking the ground, many ribbons of"
              + " purple energy begin lashing out, striking anyone"
              + " below the ledge with their harmful effects!\n");

            badness = clone_object(DELRIMMON_DIR + "obj/badness");
            badness->move(room);

            return 1;
        }
    }

    if (attack_type < 4)
    {
        set_alarm(0.0, 0.0, &heave(enemy));
        return 1;
    }

    return 0;
} /* special_attack */


/*
 * Function name:        heave
 * Description  :        this is the npcs's special attack. It takes
 *                       the player, and attempts to throw them into
 *                       the nearby rock wall to damage, and potentially
 *                       kill them.
 * Arguments    :        object victim - the player
 * Returns      :        integer 1
 */
public varargs int
heave(object victim)
{
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    mixed  *sdam;
    string *hitloc;
    string  his = victim->query_possessive();
    string  him = victim->query_objective();
    string  he  = victim->query_pronoun();

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

    sdam = victim->hit_me(F_PENMOD(70, 100), W_IMPALE, TO, -1);

    switch(sdam[0])
    {
        case 0:
            victim->catch_msg(QCTNAME(TO) + " lunges at you with"
              + " grasping fingers, but you leap aside!\n");
            say(QCTNAME(TO) + " lunges suddenly toward "
              + QTNAME(victim) + " with grasping fingers, but "
              + QTNAME(victim) + " leaps aside!\n", victim);
            break;
        case 1..5:
            victim->catch_msg(QCTNAME(TO) + " lunges suddenly at you,"
              + " and grabs you by the wrist to throw you hard against"
              + " the wall! You just barely manage to stagger your"
              + " steps to cushion against the blow as your shoulder"
              + " glances against the rocks.\n");
            say(QCTNAME(TO) + " lunges suddenly at " + QTNAME(victim)
              + ", grabbing " + him + " by the wrist to throw "
              + him + " hard against the wall! " + QCTNAME(victim)
              + " just manages to stagger " + his + " steps to"
              + " cushion against the blow as " + his + " shoulder"
              + " glances against the rocks.\n", victim);
            break;
        case 6..20:
            victim->catch_msg(QCTNAME(TO) + " grabs you roughly by"
              + " the arm, and flings you sidelong into the rock wall!"
              + " Pain washes over your entire side as you collide"
              + " with the jagged surface, and you scramble to regain"
              + " your footing.\n");
            say(QCTNAME(TO) + " grabs " + QTNAME(victim) + " roughly"
              + " by the arm, and flings " + him + " sidelong into"
              + " the rock wall! A look of pain crosses " + his
              + " face as " + he + " collides with the jagged surface,"
              + " and quickly attempts to regain " + his
              + " footing.\n", victim);
            break;
        case 21..50:
            victim->catch_msg(QCTNAME(TO) + " grabs you suddenly by"
              + " the throat, and thrusts you against the hard rock"
              + " wall with blinding speed! You senses are blinded"
              + " momentarily by pain as your head and back are pinned"
              + " by his fearsome grip! You twist out of his grasp and"
              + " quickly turn to face him once more.\n");
            say(QCTNAME(TO) + " grabs " + QTNAME(victim) + " suddenly"
              + " by the throat, and thrusts " + him + " against the"
              + " hard rock wall with blinding speed! " + CAP(his)
              + " face blanches as " + his + " head and back are"
              + " pinned by " + QTNAME(TO) + "'s fearsome grip! "
              + QCTNAME(victim) + " twists away and turns quickly"
              + " again to face " + his + " enemy.\n", victim);
            break;
        case 51..99:
            victim->catch_msg(QCTNAME(TO) + " grabs you by the forearm,"
              + " and crosses behind you to drive his other hand into the"
              + " back of your head, driving you face-first into the"
              + " nearby rock wall with terrifying power! All goes black"
              + " for a moment, as pain and numbness wash over your"
              + " senses. Disoriented, you slowly rise to your feet.\n");
            say(QCTNAME(TO) + " grabs " + QTNAME(victim) + " by the"
              + " forearm, crossing behind " + him + " to drive his"
              + " other hand into the back of " + QTNAME(victim) + "'s"
              + " head, driving " + him + " face-first into the nearby"
              + " rock wall with terrifying force! Dazzled by the"
              + " collision, " + QTNAME(victim) + " sprawls to the"
              + " ground and slowly rises, wobbling slightly, to "
              + his + " feet.\n", victim);
            break;
        default:
            victim->catch_msg("With a wild and terrifying yell, "
              + QTNAME(TO) + " lunges for you, grabbing your neck with"
              + " both of his powerful hands! You feel your entire body"
              + " dragged head-first toward the nearby rock wall with"
              + " terrible speed! The last thing you hear is the sound"
              + " of your own skull splitting open.\n");
            say("With a wild and terrifying yell, " + QTNAME(TO)
              + " lunges for " + QTNAME(victim) + ", grabbing " + his
              + " neck with both powerful hands! His muscles rippling"
              + " with animal strength, " + QTNAME(TO) + " hurls "
              + QTNAME(victim) + "'s helpless body forward head-first"
              + " into the jagged rock wall! The gut-churning sound of"
              + " a splitting skull echoes through the cavern, and "
              + QTNAME(victim) + " lies still on the floor.\n", victim);
            break;
    }

    if (victim->query_hp() == 0)
    {
        victim->do_die(TO);
        log_file(THIS_LOG,
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(victim->query_name()) + " was killed by "
      + query_real_name() + "\n");
    }

    return 1;
} /* heave */


/*
 * Function name:        arm_me
 * Description  :        give the npc armour and weapons
 */
public varargs void
arm_me()
{
    object     plate;

    Weapon = clone_unique(ONE_OF_LIST(ELITE), 14, DR_WEP + "longsword");
    Weapon->move(this_object());

    plate = clone_unique(DR_ARM + "midnight", 8, DR_ARM + "platemail", 1, 66);
    plate->move(this_object());

    clone_object(DR_ARM + "bone_shield")->move(TO);
    clone_unique(DR_ARM + "black_skull", 15, DR_ARM + "helmet", 1)->move(TO);

    command("wear all");
} /* arm_me */


/*
 * Function name:        captain_gem
 * Description  :        give the captain a better gem than the other
 *                       orcs
 */
public void
captain_gem()
{
    object gem;

    if (!random(2))
    {
        gem = clone_object("/d/Genesis/gems/obj/diamond_black");
        gem->move(this_object());
    }
} /* captain_gem */


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
              + " Darklings already know of your sins! They will"
              + " send others, and then you will pay for them!\n"
              + QCTNAME(this_object()) + " collapses, and his"
              + " eyes glaze over.\n");
    }

    if (living(killer))
    {
        tell_object(killer, 
            "You killed the huge black orc captain.\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " killed " +  query_objective() + ".\n",
           ({ this_object(), killer }));
    }

    log_file(THIS_LOG, killer->query_name() + " ("
      + killer->query_average_stat() + ") killed Akugla, "
      + ctime(time()) + ".\n\tWeapon acuired = "
      + Weapon->short() + ".\n");
} /* notify_death */


/*
 * Function name:        run_away
 * Description  :        we mask the fun from /std/living/combat.c to
 *                       keep him from ever leaving the ledge.
 */
public void
run_away()
{
    command("cackle");
    command("shout I'll never flee, you pathetic fools!");

    return;
} /* run_away */


/*
 * Function name:        notify_you_killed_me
 * Description  :        Called when this npc kills something. We want
 *                       our ogres to do what ogres do.
 * Arguments    :        object player: the one who was killed
 * Returns      :        1
 */
public int
notify_you_killed_me(object player)
{
    log_file(THIS_LOG,
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(player->query_name()) + " was killed by "
      + query_real_name() + "\n");

    return 1;
} /* notify_you_killed_me */


/*
 * Function name:        attacked_by
 * Description  :        Lets keep track of who attacks us for now
 * Arguments    :        object attacker - who is attacking us?
 */
public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    log_file(THIS_LOG, 
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(attacker->query_name()) + " attacked"
      + " Akugla.\n");
} /* attacked_by */
