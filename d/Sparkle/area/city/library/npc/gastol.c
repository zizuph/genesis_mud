/*
 *  /w/petros/sparkle/library/npc/gastol.c
 *
 *  Gastol is the gnomish restorer for the Library of Sparkle
 *  
 *  Created by Petros, April 2008
 */
#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <ss_types.h>
#include "/d/Sparkle/sys/quests.h"
#include "defs.h"

// Inheritance 
inherit SPARKLE_NPC_BASE;

// Prototypes
public void             create_sparkle_npc();
public string           help_answer();
public string           liquid_answer();
public void             liquid_answer_part_2(object player);
public void             liquid_answer_part_3(object player);
public void             liquid_answer_part_4(object player);
public void             liquid_answer_part_5(object player);
public void             react_lemon(object obj, object to);
public void             react_kidney(object obj, object to);
public void             load_receiving_log();
public void             make_liquid_part_1(object player);
public void             make_liquid_part_2(object player);
public void             make_liquid_part_3(object player);
public void             make_liquid_part_4(object player);
public void             make_liquid_part_5(object player);
public void             make_liquid_part_6(object player);

// Global Variables
mapping receiving_log;

/*
 * Function name: is_valid_room
 * Arguments  : str - the path of the room
 * Returns   : 1 = can be used in the pathfinding, 0 if not
 */
public int is_valid_room(string str)
{
    if (wildmatch(LIBRARY_ROOM_DIR + "*", str))
    {
        return 1;
    }
    
    return 0;
}

/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    set_name("gastol");
    set_living_name("gastol");
    set_race_name("gnome");
    set_adj("busy");
    set_adj("stocky");
    set_short("busy stocky gnome");
    set_gender(G_MALE);
    set_long("The stocky gnome looks like he's extremely occupied.\n");

    set_stats(({ 60, 60, 60, 80, 40, 80 }));
    
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 120);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    // Set up the id so that file operations will work
    setuid(); 
    seteuid(getuid());
    
    // Initialize the mapping
    load_receiving_log();
}

public void
load_receiving_log()
{
    if (file_size(LIBRARY_QUEST_DIR + "receiving_log.o") > 0)
    {
        receiving_log = restore_map(LIBRARY_QUEST_DIR + "receiving_log");
    }
    else
    {
        receiving_log = ([ "lemon" : ({ }),
                           "kidney" : ([ ]) ]);
    }
}

public void
save_receiving_log()
{
    save_map(receiving_log, LIBRARY_QUEST_DIR + "receiving_log");
}

/*
 * Function name:       default_answer
 * Description  :       give an answer to unknown questions.
 */
public string
default_answer()
{
    string question;
    
    question = query_question();
    switch (question)
    {
    case "liquid":
    case "restoring liquid":
        liquid_answer();
        break;
        
    case "rat":
    case "sewer rat":
    case "sewers":
    case "sewer":
        say_to_player("I hear that the sewers underneath the Library are "
                    + "full of sewer rats.", this_player());    
        break;
        
    case "lemon":
    case "lemons":
        say_to_player("I know that lemons grow in the City of Sparkle "
                    + "somewhere, but I don't know where.", 
                      this_player());
        break;
        
    case "librarian":
    case "librarian":
    case "head librarian":
        say_to_player("Yeah, Nikolon's the Head Librarian. Has me doing "
                    + "some work for him. Now stop bothering me so that "
                    + "I can do some work.", this_player());
        break;
        
    case "kidney":
    case "kidneys":
    case "agent":
    case "powerful agent":
        say_to_player("I don't know what those rats down there are "
                    + "eating, but I discovered some time ago that their "
                    + "kidneys contain something that when combined with "
                    + "lemon juice, becomes a powerful restoring agent.",
                      this_player());
        break;
                
    default:
        say_to_player("Can't you see I'm working here? Go bother "
                    + "someone else, like the Head Librarian.",
                      this_player());
        command("emote mutters to himself and returns to his work."); 
    }
         
    return "";
} 

public int
finished_restore_quest(object player)
{
    return player->test_bit("Sparkle", 
                            LIBRARY_RESTORE_GROUP, 
                            LIBRARY_RESTORE_BIT);
}

/*
 * Function name:       help_answer
 * Description  :       response to an add_ask
 */
public string
help_answer()
{ 
    // Gastol is a vital part of the Book Restorer Quest. He's the
    // one that gives the player information about the special
    // restoring liquid and how to make it.
    if (finished_restore_quest(this_player()))
    {
        say_to_player("Nikolon tells me he got the restorer liquid "
                    + "already. Now leave me to my work!",
                      this_player());
        command("emote returns to his work.");
        return "";
    }
    
    default_answer();
    return "";
}

/* 
 * Function name:       job_answer
 * Description  :       response to add_ask
 */
public string
job_answer()
{
    say_to_player("My job? What does it look like I'm doing? I'm the "
                + "official book Restorer here at the Library. I'm "
                + "helping Nikolon the Head Librarian with some stuff, "
                + "so go bother someone else.", this_player());
    return "";
    
} // job_answer

public string
liquid_answer()
{     
    if (finished_restore_quest(this_player()))
    {
        say_to_player("Nikolon tells me he got the restoring liquid "
                    + "already. Now leave me to my work!",
                      this_player());
        command("emote returns to his work.");
        return "";                    
    }
    
    set_busy(1);
    say_to_player("Ahh, did Nikolon send you? Alright, I admit it. I ran "
                + "outta that restoring liquid. He probably didn't tell "
                + "you what I needed either.", this_player());
    command("sigh resignedly");
    set_alarm(6.0, 0.0, &liquid_answer_part_2(this_player()));
    return "";    
}

public void
liquid_answer_part_2(object player)
{
   if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
    
    player->catch_tell("\n");
    say_to_player("You're not the first person to come to me about this, "
                + "but I hope you can help me get the things that I need. "
                + "There are basically two components that I need in "
                + "order to make the liquid.", player);
    command("emote takes out his spectacles and looks intently at a piece "
          + "of paper on his desk.");                
    set_alarm(6.0, 0.0, &liquid_answer_part_3(player));
}

public void
liquid_answer_part_3(object player)
{
   if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
    
    player->catch_tell("\n");
    say_to_player("The first component most everyone knows about. Lemon "
                + "juice is one of the best ways to restore old "
                + "documents. There are some lemons being grown "
                + "in the city somewhere. I'll just need one ripe "
                + "one.", player);
    command("emote glances down at the paper he's reading before "
          + "continuing.");                
    set_alarm(6.0, 0.0, &liquid_answer_part_4(player));
}

public void
liquid_answer_part_4(object player)
{
   if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
    
    player->catch_tell("\n");
    say_to_player("The second component may be a bit more difficult to "
                + "get. I need the kidneys of sewer rats to extract "
                + "a special compound that they have. Mind you, the "
                + "kidneys I need can't be from any old rat. It must be "
                + "from a sewer rat, and I need ten of them.", player);
    set_alarm(6.0, 0.0, &liquid_answer_part_5(player));
}
                
public void
liquid_answer_part_5(object player)
{
   if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
    
    player->catch_tell("\n");
    say_to_player("You can find these rats in the sewer system beneath "
                + "the city. The adventurer who brought it to me before "
                + "said something about there being rats underneath the "
                + "Library.", player);
    player->catch_tell("\n");                
    say_to_player("Just give me the lemon and the ten sewer rat kidneys "
                + "and I'll whip up some restoring liquid for you to "
                + "bring to Nikolon. Until then, let me get back to me "
                + "work.",
                  player); 
    command("emote returns to his work and ignores you.");
    set_busy(0);
}

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
        return;
    }
    
    if (cannot_see_person(to))
    {
        command("say I wonder who gave me these?");
        ::return_object(obj, to);
        return;
    }
        
    if (is_busy())
    {
        say_to_player("I'm a bit busy at the moment. Here, take this back"
                      , to);        
        ::return_object(obj, to);
        return;
    }

    if (finished_restore_quest(to))
    {
        say_to_player("You have already helped me enough, so I "
                    + "don't need anything from you.", to);
        ::return_object(obj, to);
        return;
    }
    
    if (present("_library_restoring_liquid", ({ to }) 
                                             + deep_inventory(to)))
    {
        say_to_player("I've already given you a restoring liquid to "
                    + "give to Nikolon! Move along now.", to);
        ::return_object(obj, to);
        return;
    }
    
    if (obj->id("_library_rooftop_lemon"))
    {
        set_alarm(0.5, 0.0, &react_lemon(obj, to));
        return;
    }

    if (IS_LEFTOVER_OBJECT(obj)
        && obj->query_race() == "sewer rat"
        && obj->query_organ() == "kidney")
    {
        set_alarm(0.5, 0.0, &react_kidney(obj, to));
        return;
    }
    
    // If it's not one of the items accepted, default to the
    // sparkle npc behavior, which is to return it.
    ::return_object(obj, to);
}

public int
has_received_lemon(object player)
{
    if (IN_ARRAY(player->query_real_name(), receiving_log["lemon"]))
    {
        return 1;
    }
    
    return 0;
}

public int
num_received_kidney(object player)
{
    mapping kidney_mapping;
    
    kidney_mapping = receiving_log["kidney"];
    if (!IN_ARRAY(player->query_real_name(), m_indices(kidney_mapping)))
    {
        return 0;
    }
    
    return kidney_mapping[player->query_real_name()];
}

public void
destroy_received(object obj)
{
    obj->remove_object();
}

public object
return_excess_objects(object obj, object to, int amount_needed)
{
    int is_heap, amount;
    string objtext;
    object leftover, extra_objs;

    is_heap = obj->query_prop(HEAP_I_IS);
    amount = (is_heap ? obj->num_heap() : 1);

    if (amount > amount_needed)
    {            
        obj->split_heap(amount - amount_needed);
        leftover = obj->make_leftover_heap();
        extra_objs = obj;
        obj = leftover;
        say_to_player("This is more than enough. Here, take this back.",
                      to);
        ::return_object(extra_objs, to);
    }

    return obj;
}

public void
check_make_liquid(object player)
{
    int amount;
    
    if (has_received_lemon(player)
        && num_received_kidney(player) == 10)
    {
        receiving_log["lemon"] -= ({ player->query_real_name() });
        m_delkey(receiving_log["kidney"], player->query_real_name());
        save_receiving_log();
        say_to_player("You've delivered everything I need now. I'll "
                    + "get to work right away on making the restoring "
                    + "liquid for Nikolon.", player);
        set_busy(1);                    
        set_alarm(3.0, 0.0, &make_liquid_part_1(player));
        return;
    }

    amount = 10 - num_received_kidney(player);
    if (has_received_lemon(player))
    {
        say_to_player("If you fetch me " + amount + " more "
                    + (amount == 1 ? "kidney" : "kidneys")
                    + ", then I'll be able to make the restoring "
                    + "liquid.", player);
        return;
    }
    else
    {
        if (amount > 0)
        {
            say_to_player("If you fetch me " + amount + " more "
                        + (amount == 1 ? "kidney" : "kidneys")
                        + " and a lemon, then I'll be able to make the "
                        + "restoring liquid.", player);
        }
        else
        {
            say_to_player("If you fetch me a lemon, then I'll be able "
                        + "to make the restoring liquid.", player);
        }            
        return;
    }       
}

public void
react_lemon(object obj, object to)
{
    int amount;

    if (has_received_lemon(to))
    {
        ::return_object(obj, to);
        check_make_liquid(to);
        return;
    }
    
    obj = return_excess_objects(obj, to, 1);
        
    receiving_log["lemon"] += ({ to->query_real_name() });
    save_receiving_log();
//    set_alarm(1.0, 0.0, &destroy_received(obj));
    destroy_received(obj);
    
    check_make_liquid(to);
}

public void
react_kidney(object obj, object to)
{
    int is_heap, amount;
    mapping kidney_mapping;
    
    if (num_received_kidney(to) >= 10)
    {
        ::return_object(obj, to);
        check_make_liquid(to);
        return;        
    }
    
    obj = return_excess_objects(obj, to, 10 - num_received_kidney(to));
    is_heap = obj->query_prop(HEAP_I_IS);
    amount = (is_heap ? obj->num_heap() : 1);
    kidney_mapping = receiving_log["kidney"];
    kidney_mapping[to->query_real_name()] = num_received_kidney(to) 
                                            + amount;
    save_receiving_log();                                            
//    set_alarm(1.0, 0.0, &destroy_received(obj));
    destroy_received(obj);
    
    check_make_liquid(to);
}

public void
make_liquid_part_1(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
        
    command("emote takes a knife out of his pocket and slices "
          + "the lemon in half.");
    command("emote begins to squeeze the juice from the lemon halves "
          + "into a small flask.");
    set_alarm(10.0, 0.0, &make_liquid_part_2(player));
}

public void
make_liquid_part_2(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
        
    tell_room(environment(this_object()), "\n");
    command("emote finishes squeezing the juice from both lemon "
          + "halves.");
    command("emote takes a small towel and wipes his hands.");
    set_alarm(5.0, 0.0, &make_liquid_part_3(player));
}

public void
make_liquid_part_3(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
        
    tell_room(environment(this_object()), "\n");
    command("emote takes a mortar and pestle out and places the "
          + "kidneys into the mortar.");
    command("emote places the mortar on top of a small flame.");
    set_alarm(10.0, 0.0, &make_liquid_part_4(player));
}

public void
make_liquid_part_4(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
        
    tell_room(environment(this_object()), "\n");
    tell_room(environment(this_object()), "The kidneys begin to shrink "
            + "and a murky liquid begins to seep onto the bottom of "
            + "the mortar.\n");
    command("emote takes the mortar off the flame and uses the pestle "
          + "to squeeze more liquids out of the kidneys.");
    set_alarm(10.0, 0.0, &make_liquid_part_5(player));
}

public void
make_liquid_part_5(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
        
    tell_room(environment(this_object()), "\n");
    command("emote pours the liquid into the small flask, stoppers it, "
          + "and begins to shake it vigorously.");
    set_alarm(5.0, 0.0, &make_liquid_part_6(player));
}

public void
make_liquid_part_6(object player)
{
    object liquid;

    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }        
    
    tell_room(environment(this_object()), "\n");
    command("emote finishes shaking the liquid and carefully applies a "
          + "label onto the flask.");
    say_to_player("Please deliver this to Nikolon immediately!", player);
    liquid = clone_object(LIBRARY_OBJ_DIR 
                 + "restoring_liquid");
    liquid->set_owner(player->query_real_name());
    liquid->move(this_object(), 1);
    command("give liquid to " + OB_NAME(player));
    command("emote waves you away and returns to his work.");
    set_busy(0);
}

/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 * Arguments    :       hour - current hour in Sparkle time
 * Returns      :       nothing
 */
public void
alert_hour_change_hook(int hour)
{
    if (is_busy())
    {
        // Don't participate in daily routines when interacting.
        return;
    }
    
    // Gastol spends most of the time in his own office. He spents
    // two hours in the writing room each day.
    switch (hour)
    {
    case 0..21:
        if (walk_to_room(LIBRARY_ROOM_DIR + "restorer"))
        {
            command("stand");
            clear_act();
        }
        break;
        
    case 22..23:
        if (walk_to_room(LIBRARY_ROOM_DIR + "writing_room"))
        {
            clear_act();   
        }
        break;
    }
}

/*
 * Function name:       walk_destination_reached_hook
 * Description  :       Override this to do something when the 
 *                      npc arrives at his destination.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
walk_destination_reached_hook()
{
    string roomfile;
    
    roomfile = MASTER_OB(environment(this_object()));
    switch (roomfile)
    {
    case LIBRARY_ROOM_DIR + "restorer":
        command("$emote settles in and begins to "
              + "intently study ancient texts.");
        break;
    
    case LIBRARY_ROOM_DIR + "writing_room":
        command("sit");
        command("emote begins to do some writing.");
        break;
    }
}
