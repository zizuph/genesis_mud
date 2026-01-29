/*
 *  /d/Sparkle/guilds/new_merc/event/goblin_bloater.c
 *
 *  The exploding goblin attacker for the raid on Sparkle that will
 *  lead to the opening of the Free Mercenary Guild. This guy is like
 *  a time bomb that has a chance of going off if he gets too hurt. If
 *  he blows, he hurts everyone in the room and sends them flying out
 *  the various exits.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Emerald/lib/aid_npc";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <filepath.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "../merc_defs.h"


/* Prototypes */
public void        create_monster();
public void        arm_me();
public int         special_attack(object enemy);
public void        bomb_explode();
public void        add_crater();
public void        do_log(object ob, string logtxt);
public void        throw_victim(object victim);
public void        notify_death(object killer);

/* Global Variables */
public int         Already_Exploding = 0;
public string      Goblin_Type = "bloater";

/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_name("goblin");
    set_race_name("goblin");
    add_name( ({ "bloater", EVENT_GOBLIN }) );
    add_adj( ({ "goblin" }) );

    set_short("goblin bloater");
    set_long("A more wretched creature than this you have rarely seen!"
      + " Hideously fat and bloated flesh baloons out from every"
      + " direction of his naked body. It almost looks like he is about"
      + " to burst!\n");

    set_stats( ({ 100 + (random(30)),
                  100 + (random(25)),
                  100 + (random(30)),
                  5   + (random(20)),
                  5   + (random(20)),
                  100 + (random(40)) }) );
                  
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_AWARENESS,    80);
    set_skill(SS_DEFENCE,      100);

    add_act("burp");
    add_act("emote waddles awkwardly around.");
    add_act("say ... urp ... hhhhh ...");
    add_act("emote pauses and looks like he might throw up.");

    add_cact("emote almost falls over.");
    add_cact("emote pauses and holds his gut.");
    add_cact("emote belches mightily!");

    /* We assist other goblins who get attacked. */
    set_give_aid(1);

    set_aggressive(1, 100);
} /* create_monster */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
} /* arm_me */


/*
 * Function name:        special_attack
 * Description  :        every so often we'll do a special attack
 * Arguments    :        object enemy - the person we're attacking
 * Returns      :        int 0 - don't do the special
 *                           1 - do the special attack
 */
public int
special_attack(object enemy)
{
    int     attack_type = random(5); /* 20% chance to do special */
    mixed  *targets = filter(all_inventory(environment(
                       this_object())), &->id(EVENT_GOBLIN));
    string  bite_loc;
    int     bite_damage;
    object  target = one_of_list(targets);

    if (Already_Exploding)
    {
        return 0;
    }

    command("shout Bloat gonna blow!!");
    command("emote tosses a vial of clear liquid into his mouth and"
      + " bites down with an audible crunch.");

    set_alarm(2.0, 0.0, &bomb_explode());
    Already_Exploding = 1;

    return 1;
} /* special_attack */


/*
 * Function name:        assist
 * Description  :        When assisting other goblins that get attacked,
 *                       we display what is happening.
 */
public void
assist()
{
    /* Too spammy otherwise */
    if (random(7))
    {
        return;
    }

    command(one_of_list( ({
        "shout Bloat help brother!",
        "emote staggers to assist his friend.",
        "shout You make bloat angry!",
        "emote belches in outrage!" }) ) );
} /* assist */


/*
 * Function name:        ask_for_assistance
 * Description  :        When we need assistance from other goblins,
 *                       this happens.
 */
public void
ask_for_assistance()
{
    /* Too spammy otherwise */
    if (random(7))
    {
        return;
    }

    command(one_of_list( ({
        "emote wheezes for help!",
        "shout Bloat in trouble, here!",
        "emote waves his tiny arms around in desperation.",
        "shout Runt! Help Bloat!!!" }) ) );
} /* ask_for_assistance */


/*
 * Function name:       attacked_by
 * Description:         This routine is called when we are attacked.
 * Arguments:           ob: The attacker
 *
 * Mask to allow for assistance from other goblins.
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    get_assistance(ob);
} /* attacked_by */


/*
 * Function name:        bomb_explode
 * Description  :        cause the bundle to explode, damaging all
 *                       livings in the room, and throwing them
 *                       in the direction of a random exit
 *                       KABOOM!!
 */
public void
bomb_explode()
{
    object *victims = FILTER_LIVE(all_inventory(environment(this_object())));
    int     i;

    setuid();
    seteuid(getuid());

    tell_room(environment(this_object()),
        "KABOOOOOOM!!!\n"
      + "The goblin bloater explodes in a great ball of flame, sending"
      + " everything in the room flying!\n");
    tell_players_in_same_subdir(environment(this_object()),
        "A thunderous boom echoes suddenly throughout the area.\n");

    while (i < sizeof(victims))
    {
        if (victims[i]->query_wiz_level())
        {
            victims[i]->catch_msg("Your wizard status protects you"
                                + " from the blast.\n");
        }
        else if (victims[i]->id(EVENT_GOBLIN))
        {
            if (victims[i] != this_object())
            {
                victims[i]->command("emote flattens himself on the ground"
                  + " to avoid the blast.");
            }
        }
        else
        {
            throw_victim(victims[i]);
        }

        i++;
    }

    add_crater();
    this_object()->remove_object();
} /* bomb_explode */


/*
 * Function name:        add_crater
 * Description  :        adds an impact crater to the room. :-)
 */
public void
add_crater()
{
    object  crater;

    setuid();
    seteuid(getuid());

    crater = clone_object("/std/object");
    crater->set_name("hole");
    crater->add_name( ({ "crater", "mark", "area", "earth" }) );
    crater->add_adj( ({ "large", "blasted" }) );
    crater->set_short("large area of blasted earth");
    crater->set_pshort("large areas of blasted earth");
    crater->set_long(
        "Various debris of rocks and dirt splay outward from"
      + " this area of blasted earth. It would appear as if"
      + " a violent explosion of some form ripped into the ground"
      + " and immediate area here.\n");
    crater->add_prop(OBJ_M_NO_GET, 1);
    crater->move(environment(this_object()));
} /* add_crater */


/*
 * Function name:        throw_victim
 * Description  :        livings in the vicinity of the explosion
 *                       are thrown out a random exit by the blast
 * Arguments    :        object victim -- the person being thrown
 */
public void
throw_victim(object victim)
{
    object  room = environment(this_object());
    mixed   oroom;
    int     n;
    int    damage;

    setuid();
    seteuid(getuid());

    victim->catch_msg("You are thrown violently backwards by the"
      + " blast, and land on hard ground a good distance away.\n");

    n = random(sizeof(room->query_exit()) / 3);
    oroom = room->query_exit()[n*3];

    if (objectp(oroom))
    {
        oroom = file_name(oroom);
    }

    tell_room(oroom, "With a frightened yell, " + QNAME(victim)
      + " comes flying through the air, crashlanding just"
      + " beside you!\n");
    victim->move_living("M", oroom, 1, 1);
    tell_room(room, QCTNAME(victim) + " is flung violently "
      + room->query_exit()[n*3+1] + "wards by the blast!\n");

    damage = 300 + random(300);
    victim->reduce_hit_point(damage);

    if (interactive(victim))
    {
        do_log(victim, " hit by blast.  Damage: " + damage);
    }

    if (victim->query_hp() <= 0)
    {
        victim->do_die(this_object());

        if (interactive(victim))
        {
            do_log(victim, " DIED FROM THE BLAST");
        }
    }

} /* throw_victim */


/*
 * function name:        do_log
 * description  :        helps us log unpleasantries that happen
 *                       to players
 * arguments    :        object ob -- the player
 *                       string logtxt -- what happened
 */
public void
do_log(object ob, string logtxt)
{
    write_file(LOG_DIR + "explosions",
       TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
     + ctime(time())[11..18] + ") "
     + capitalize(ob->query_real_name()) 
     + logtxt + "\n");

    return;
} /* do_log */


/*
 * Function name:        notify_death
 * Description  :        Notify onlookers of my death
 * Arguments    :        object killer - the object that killed me
 *
 * We redefine this so that Gorboth can get notifications of who is
 * dying where and by whom.
 */
public void
notify_death(object killer)
{
    ::notify_death(killer);

    TELL_G(" -*-*-*-* A " + Goblin_Type + " was killed by "
      + capitalize(killer->query_real_name()) + " at "
      + FILE_NAME(MASTER_OB(environment(this_object()))) + "!");
} /* notify_death */