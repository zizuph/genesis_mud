/*
 *  /d/Sparkle/area/orc_temple/npc/high_priest.c
 *
 *  This is Kerchak - the High Priest of the Dungeons beneath the
 *  Orc Temple in Sparkle. He is the mastermind of the whole operation
 *  and the one responsible for the calamities that have caused
 *  imbuements to be distributed throughout the game. He is also a
 *  major player in the quest down here.
 *
 *  Created Novermber 2010, by Cooper Sherry (Gorboth)
 * 
 *  Modifications
 *    Petros, Feb 2016 - Added a objectp check in the return_object
 *                       method. It was causing many runtimes if
 *                       the person wasn't there or the object was
 *                       no longer there.
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "temple_npc";
inherit "/d/Emerald/lib/aid_npc";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>


/* Prototypes */
public void        create_temple_npc();
public void        introduce(object who);
void               react_intro(object tp);
public string      default_answer();
public void        arm_me();
public void        assist();
public void        ask_for_assistance();
public void        attacked_by(object ob);
public void        run_away();


/*
 * Function name:        create_temple_npc
 * Description  :        The constructor for the monster
 */
public void
create_temple_npc()
{
    set_living_name("kerchak");
    set_name("kerchak");
    set_race_name("half-orc");
    add_name( ({ "priest", ORC_TEMPLE_NPC }) );
    add_adj( ({ "high", "tall", "malevolent" }) );

    set_title("the Great, High Priest of Yog-Sothoth");

    set_short("tall malevolent half-orc");
    set_long("This individual is unlike any you have seen in these dungeons."
      + " Though his face displays all the harsh and cruel features"
      + " of the orcish race, his height is twice that of his"
      + " bretheren, taller even than the average elf. His eyes"
      + " display a shrewdness and cunning, coupled with cold and"
      + " merciless purpose.\n");

    set_stats( ({ 20 + (random(3)),
                  20 + (random(3)),
                  20 + (random(3)),
                  20 + (random(3)),
                  20  + (random(3)),
                  20  + (random(3)) }) );
                  
    set_skill(SS_UNARM_COMBAT,    25);
    set_skill(SS_AWARENESS,       60);
    set_skill(SS_DEFENCE,         25);
    set_skill(SS_SPELLCRAFT,      85);
    set_skill(SS_FORM_CONJURATION,100);
    set_skill(SS_ELEMENT_DEATH,   80);

    remove_prop(LIVE_I_NEVERKNOWN);
    set_default_answer(VBFC_ME("default_answer"));

    set_act_time(10 + random(7));
    add_act("glare");
    add_act("say This time, we must not allow the prisoner to die so"
      + " quickly!");
    add_act("say Do not allow your thoughts to waver. Keep chanting.");
    add_act("say I must speak to the Jailer. These prisoners are far"
      + " to quick to perish.");
    add_act("say O Demon of the Pit, your hunger will be fed!");
    add_act("say Eternal Yog-Sothoth, reveal your hunger and be fed!");
    add_act("emote stands near the pit and chants slowly.");
    add_act("say Soon we shall have the power to destroy all who oppose"
      + " us!");

    add_cact("shout Defiler of the Pit! You shall be food!");
    add_cact("emote mutters a swift incantation and you see his form"
      + " glow briefly.");
    add_cact("say You cannot destroy me, fool. I am linked to the"
      + " hunger of the Beyond!");

    set_dungeon_response( ({
        "These dungeons have served their purpose well!",
        "You have no place here. Begone e'er I see you destroyed!",
        "The dungeons will be remembered as the starting point"
      + " to what we will become." }) );
    set_demon_response( ({
        "You dare speak of the almighty? Be silent or die!",
        "Watch you tongue, or I will have it cut out and fed to"
      + " the Pit!",
        "Your foolishness is astonishing. Name it not!" }) );
    set_prisoner_response( ({
        "The prisoners are essential! We require more soon.",
        "The deaths of these wretched creatures will mean power for"
      + " us!",
        "You yourself look worthy of a cell, fool." }) );
    set_runt_response( ({ "I do not deal with runts. The Jailer can"
      + " handle that part of things." }) );
    set_warrior_response( ({ "The warriors are a rowdy lot, but"
      + " they keep the runts in line." }) );
    set_priest_response(
        ({ "The priests are loyal, and will be rewarded when the"
      + " time comes." }) );
    set_jailer_response("The Jailer is a fool, but he knows better than"
      + " to disobey me.");
    set_hp_response("Are you such a fool that you do not know to"
      + " whom you speak?");
    set_give_response("Do not trouble me with your worthless"
      + " trinkets! I will soon possess items of greater power than"
      + " you can imagine!");
    add_dungeon_asks();

    add_ask( ({ "food", "eat" }), "say I have little need of food"
      + " now that I am linked to the hunger of the Pit.", 1);
    add_ask( ({ "pit" }), "say Do not approach the Pit!", 1);
    add_ask( ({ "haunted", "ghost", "ghosts", "spirit", "spirits" }),
        "say Yes ... some of the spirits have fragmented, but it is"
      + " of little importance.", 1);
    add_ask( ({ "enchanter", "enchanting" }),
        "say Yes, I am a master of enchanting. But I'll teach you"
      + " nothing!", 1);
    add_ask( ({ "karkadelt", "brother" }),
        "say So! You are a pawn of my pathetic brother, are you? Fool!"
      + " You would be better to put your faith in someone of more"
      + " importance than he.", 1);

    set_job_response("You are too simple to understand my purpose!");

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
} /* create_temple_npc */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Where has that fool gone?");
        return;
    }

    command("introduce me");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("glare");
    command("say I have no time for your pathetic queries. Begone!");
    return "";
} /* default_answer */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object(ARM_DIR + "enchanter_robes");
    arm->move(this_object());
    arm = clone_object(OBJ_DIR + "bone_flute");
    arm->move(this_object());

    command("wear all");
} /* arm_me */


/*
 * Function name:        assist
 * Description  :        When assisting other goblins that get attacked,
 *                       we display what is happening.
 */
public void
assist()
{
    command(one_of_list( ({
        "shout Fool! You dare to assault the Pit?",
        "emote turns on you with eyes of annoyance and hatred.",
        "shout This one will feed the Pit with flesh!",
        "shout Your drippings will moisten the tongue of the Pit!" }) ) );
} /* assist */


/*
 * Function name:        ask_for_assistance
 * Description  :        When we need assistance from other goblins,
 *                       this happens.
 */
public void
ask_for_assistance()
{
    command(one_of_list( ({
        "shout This fool must die!",
        "shout Kill this one and carve it slowly!",
        "emote gestures for his minions.",
        "shout You dare to face me?!" }) ) );
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
 * Function name:        special_attack
 * Description  :        every so often we'll do a special attack
 * Arguments    :        object enemy - the person we're attacking
 * Returns      :        int 0 - don't do the special
 *                           1 - do the special attack
 */
public int
special_attack(object enemy)
{
    int     attack_type = random(10); /* 10% chance to do special */
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    string *visions = ({
                "You envision your own spine being pulled from your"
              + " torso!",
                "The image of your own skull split in two slams through"
              + " your mind!",
                "You picture yourself ripping out your own tongue with"
              + " bloody fingernails!",
                "You see yourself clawing at your own eye-sockets,"
              + " pulling out webbed nets of bloody discharge!",
                "A vision of you forcing the point of a sharp blade"
              + " up under your chin, through your mouth, and into"
              + " your brain sears your thoughts!" });
    int     damage;

    if (attack_type)
    {
        return 0;
    }

    tell_room(environment(this_object()), QCTNAME(this_object()) + 
        " shouts: Mighty Yog-sathoth! Feed your hunger!\n\n"
      + "A hideous throbbing moan sounds from the pit, tearing at the"
      + " souls of any it despises!\n\n");

    foreach(object victim: enemies)
    {
        damage = 25 + random(25);

        victim->catch_tell(one_of_list(visions) + "\n");
        victim->catch_tell("You feel less healthy!\n\n");
        tell_room(environment(this_object()), QCTNAME(victim)
          + " screams in mindless terror!\n", victim);
        
        /* No resistances apply here. This is the power of a god-like
         * arch-demon flaying the very soul of the victim with madness.
         */
        victim->heal_hp(-damage);

        write_file(LOG_DIR + "priest_fight", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(victim->query_name()) + " was mind-whipped for "
          + damage + " damage.\n");

        if (victim->query_hp() == 0)
        {
            victim->do_die(this_object());
            write_file(LOG_DIR + "priest_fight", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(victim->query_name()) + " was KILLED by"
              + "Yog-sathoth!\n");
        }
    }

    return 1;
} /* special_attack */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 *                though in this case, we do not want a death,
 *                but merely a defeat.
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    if (environment(this_object())->id("_demon_pit"))
    {
        tell_room(environment(this_object()), 
            QCTNAME(this_object()) + " staggers back from the mortal"
          + " wound, saying: Fool! Your actions are meaningless! Yog-Sothoth"
          + " will give me new flesh, and I shall destroy everything you"
          + " hold dear!\n\n" + QCTNAME(this_object()) + " dives into the"
          + " pit, where you hear a terrible sucking and throbbing moan."
          + " A moment later, his corpse is spit out of the pit to land"
          + " at your feet.\n");
    }
    else
    {
        tell_room(environment(this_object()), 
            QCTNAME(this_object()) + " staggers back from the mortal"
          + " wound, saying: Fool! Your actions are meaningless! Yog-Sothoth"
          + " will give me new flesh, and I shall destroy everything you"
          + " hold dear!\n\n" + QCTNAME(this_object()) + " utters a"
          + " harsh and swift prayer, and then writhes in terrible"
          + " agony as a strange and terrifying moan sounds from"
          + " beneath the floor. When you look again, he lies dead"
          + " at your feet.\n");
    }

    if (living(killer))
    {
        tell_object(killer, 
            "You defeated " + this_object()->query_the_name(killer) + ".\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " defeated " +  query_objective() + ".\n",
           ({ this_object(), killer }));
    }

    write_file(LOG_DIR + "killed_priest", 
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(killer->query_name()) + " killed"
      + " the High Priest.\n");
} /* notify_death */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    if (!objectp(obj))
    {
        command("say Hmm... I seem to have lost something.");
        return;
    }
    if (!objectp(to))
    {
        command("say Hmm... I wonder where they went.");
        command("ponder");
        return;
    }
    if (query_race_name() == "goblin" && obj->id("coin"))
    {
        command("grin greed");
        command("say I accept your donation.");
        return;
    }

    if (obj->id("key"))
    {
        command("say You should not have this!");
        command("say I will return it to the Jailer.");
        return;
    }

    if (obj->id(QUEST_FLUTE))
    {
        command("say Miserable fool! You shall not have this!");
        command("curse");
        return;
    }

    if (obj->id(QUEST_WEAPON))
    {
        command("say You have stolen this! Stay away from the"
          + " things of this dungeon, fool!");
        command("slap " + OB_NAME(to));
        return;
    }

    command("say " + Give_Response);
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * Function name: run_away
 * Description:   Runs away from the fight
 *
 * We mask this to prevent the High Priest from abandoning his post
 */
public void
run_away()
{
    command("emote takes stock of his grave peril.");
    command("shout Yog-Sothoth protects me even now, fool!");
} /* run_away */
