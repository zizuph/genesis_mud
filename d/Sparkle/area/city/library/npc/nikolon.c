/*
 *  /w/petros/sparkle/library/npc/nikolon.c
 *
 *  Nikolon is the head librarian of the Library of Sparkle
 *  
 *  Created by Petros, March 2008
 *
 * Modification Log:
 *   April 18, 2011 (Gorboth)
 *     Added functionality for Sparkle Tourmasters quests
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
// Pathfinding prototypes
public void             alert_hour_change_hook(int hour);
public int              is_valid_room(string str);
// Quest related prototypes
public string           help_answer();
public string           project_answer();
public string           projects_answer();
public void             projects_answer_part_2(object player);
public void             projects_answer_part_3(object player);
public string           census_answer();
public void             census_answer_part_2(object player);
public void             census_answer_part_3(object player);
public string           liquid_answer();
public string           restoration_answer();
public void             restoration_answer_part_2(object player);
public void             restoration_answer_part_3(object player);
public void             reward_player_sign_quest(object player);
public void             reward_player_restore_quest(object player);
public int              finished_sign_quest(object player);
public int              finished_restore_quest(object player);
public int              check_remaining_quests(object who);
// Actions related prototypes
public void             set_room_actions();
public void             add_circulation_acts();
public void             add_headoffice_acts();
public void             add_bedroom_acts();

// Global Variables

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
 * Function name:       project_answer
 * Description  :       Handles when the player asks about the project.
 *                      This will handle the cases when the player has
 *                      completed the quests as well.
 * Arguments    :       none
 * Returns      :       string
 */
public string
project_answer()
{
    int sign_finished, restore_finished;
    
    sign_finished = finished_sign_quest(this_player());
    restore_finished = finished_restore_quest(this_player());
    if (sign_finished && !restore_finished)
    {
        return restoration_answer();
    }    
    else if (restore_finished && !sign_finished)
    {
        return census_answer();
    }
    else if (restore_finished && sign_finished)
    {
        say_to_player("You have been a tremendous help to the Genesis "
                    + "Library already. I have no more projects that I "
                    + "need help with at this time.", this_player());
        return "";
    }
    else
    {
        say_to_player("Which project are you interested in learning more "
                    + "about? The census project or the book restoration "
                    + "project?", this_player());
        return "";
    }
}

/* 
 * Function name:       projects_answer
 * Description  :       Nikolon talks about his projects when asked about
 *                      them.
 * Arguments    :       none
 * Returns      :       string
 */
public string
projects_answer()
{
    set_busy(1);
    say_to_player("Ahh.. it's good to find others who are interested in "
                + "assisting with the projects here in the Library.",
                  this_player());
    say_to_player("I'm currently working on a couple of things.", 
                  this_player());
    command("$emote pauses.");
    set_alarm(6.0, 0.0, &projects_answer_part_2(this_player()));
    return "";
}

/* 
 * Function name:       projects_answer_part_2
 * Description  :       Part of the projects answer
 * Arguments    :       player - player being talked to
 * Returns      :       nothing
 */
public void
projects_answer_part_2(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }

    player->catch_tell("\n");
    command("$emote smiles broadly.");
    if (finished_sign_quest(player))
    {
        say_to_player("You already know about the census project since "
                    + "you helped me so much on it.", player);
    }
    else
    {    
        say_to_player("One of the projects I'm working on is a census of "
                    + "the adventurers of Genesis.", player);
        command("$emote gestures broadly.");
    }
    set_alarm(6.0, 0.0, &projects_answer_part_3(player));
}

/* 
 * Function name:       projects_answer_part_2
 * Description  :       Part of the projects answer
 * Arguments    :       player - player being talked to
 * Returns      :       nothing
 */
public void
projects_answer_part_3(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }

    this_player()->catch_tell("\n");
    if (finished_restore_quest(player))
    {
        say_to_player("My second project is already known to you. I am "
                    + "still currently working with Gastol to uncover the "
                    + "contents of those documents. Thank you so much for "
                    + "your help in that endeavor.", player);        
    }
    else
    {
        command("$emote furrows his brow slightly and continues.");
        say_to_player("The other project I'm working on involves ancient "
               + "documents that were discovered during the construction "
               + "of the Library.", player);
    }
    say_to_player("Feel free to ask me about either of these projects.",
                  player);
    set_busy(0);
}

/* 
 * Function name:       census_answer
 * Description  :       Answer when player asks about the census quest
 * Arguments    :       none
 * Returns      :       string
 */
public string
census_answer()
{
    if (present("signature_book", this_player()))
    {
        // Handle the case where the user already has the book.
        say_to_player("You already have the signature book I gave you. "
                    + "You can <return> it to me if you've finished "
                    + "gathering all the signatures.",
                      this_player());
        return "";
    }
    
    if (finished_sign_quest(this_player()))
    {
        say_to_player("Thank you so much for your help with the census "
              + "before. We have been able to make quite a bit of "
              + "progress on it!", this_player());
        return "";
    }
    
    set_busy(1);
    if (file_size(LIBRARY_QUEST_DIR + this_player()->query_real_name() 
                  + ".o") > 0)
    {
        say_to_player("Oh, this appeared in the library a while ago. You "
                    + "must have dropped it! Here you can have it back.",
                      this_player());
    }
    else
    {
        say_to_player("I'm currently taking a census for the Library "
                    + "records.", this_player());
        say_to_player("The purpose of this census is to keep track of who "
                    + "is travelling the Donut.", this_player());
        say_to_player("It really is quite simple. I know you're probably "
                    + "very busy, so I'll just ask you for a small favor.",
                      this_player());
        say_to_player("All you need to do is take this book.", 
                      this_player());
    }
    set_alarm(6.0, 0.0, &census_answer_part_2(this_player()));
    return "";
}

/* 
 * Function name:       census_answer_part_2
 * Description  :       Part of the census answer
 * Arguments    :       player - player being talked to
 * Returns      :       nothing
 */
public void
census_answer_part_2(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
    
    object book;
    
    player->catch_tell("\n");
    book = clone_object(LIBRARY_OBJ_DIR + "signature_book");
    command("$emote reaches into a desk and pulls out a black book.");
    book->move(player, 1);
    book->init_arg(player->query_real_name());
    player->catch_msg(QCTNAME(this_object()) +
	" gives a black signature book to you.\n");
    tell_room(environment(this_object()), QCTNAME(this_object())
            + " gives a black signature book to " + QTNAME(player)
            + ".\n", ({ player, this_object() }));
    set_alarm(6.0, 0.0, &census_answer_part_3(player));
    
    // Log the Beginning of the Signature Quest
    send_debug_message("library_signature_quest", 
        capitalize(player->query_real_name()) + " starts signature "
      + "quest.", SIGNATURE_QUEST_LOG);
}

/* 
 * Function name:       census_answer_part_3
 * Description  :       Part of the census answer
 * Arguments    :       player - player being talked to
 * Returns      :       nothing
 */
public void
census_answer_part_3(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }
    
    this_player()->catch_tell("\n");
    say_to_player("Use that book to request signatures from adventurers "
                + "that you meet.", player);
    say_to_player("I only need you to get me 10 signatures. The "
                + "signatures must come from adventurers of sufficient "
                + "age.", player);
    say_to_player("Do not skew the census data with requests to Wizards. "
        + "They are not travellers of the Donut, they are its "
        + "Stewards!", player);
    say_to_player("When you are done, simply <return> the book to me and "
                + "I will reward you. Good luck!", player);
    set_busy(0);                
}

public string
restoration_answer()
{
    if (finished_restore_quest(this_player()))
    {
        say_to_player("Thank you so much for your help with restoring "
                    + "these ancient documents! I should have some "
                    + "important findings very soon.", this_player());
        command("emote trembles with excitement.");
        return "";
    }
    
    set_busy(1);
    say_to_player("During the construction of the Library, some ancient "
                + "documents were found buried in the foundations of the "
                + "earth. I have been working tirelessly to decipher them.",
                  this_player());
    say_to_player("I think the documents contain some valuable historical "
                + "information about the Donut, and one day I hope to be "
                + "able to publish my work on this!",
                  this_player());
    command("emote pauses.");                 
    set_alarm(6.0, 0.0, &restoration_answer_part_2(this_player()));
    return "";
}

public void
restoration_answer_part_2(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }

    player->catch_tell("\n");
    say_to_player("Gastol, a world renowned restorer, has agreed to come "
                + "here to the Genesis Library and assist me in this "
                + "endeavor.",
                  player);
    say_to_player("Of late, however, he has been complaining about "
                + "missing some important things, and as a result the "
                + "progress on deciphering has slowed down.", player);
    command("frown worriedly");
    set_alarm(6.0, 0.0, &restoration_answer_part_3(player));
}

public void
restoration_answer_part_3(object player)
{
    if (cannot_see_person(player))
    {
        respond_to_player_left_hook(player);
        set_busy(0);
        return;
    }

    player->catch_tell("\n");
    say_to_player("Can you go find Gastol and ask him about the restoring "
                + "liquid that I need? If you bring me the liquid, I will "
                + "reward you. He should be in the Library in his office.", player);             
    say_to_player("That will aid my efforts greatly!", player);
    command("emote finishes and goes back to what he was doing.");

    int avg_stat = player->query_average_stat();
    send_debug_message("library_restorer_quest", 
        capitalize(player->query_real_name()) + " (" + avg_stat + ") "
      + "begins the liquid restorer quest.", RESTORER_QUEST_LOG);
    
    set_busy(0);   
}

public string
liquid_answer()
{
    if (finished_restore_quest(this_player()))
    {
        say_to_player("Thank you so much for bringing me the restoring "
                    + "liquid. It has been immensely useful!", this_player());
        return "";
    }
    
    say_to_player("The restoring liquid can only be created by Gastol, "
                + "our restorer. ",
                  this_player());
    return "";
}

public void
topic_answer(string topic)
{
    string * matching_rooms;
    string room_desc;
    
    command("emote looks through the circulation desk.");
    matching_rooms = LIBRARY_SHELF_MANAGER->query_rooms_with_keywords(topic);
    if (!sizeof(matching_rooms))
    {
        say_to_player("I couldn't find any books with any references "
            + "to " + topic + ".\n", this_player());
        return;
    }
    
    room_desc = "";
    foreach (string roomfile : matching_rooms)
    {
        string short_desc;
        sscanf(roomfile->short(), "Stacks - %s", short_desc);
        if (strlen(room_desc))
        {
            room_desc += " and ";
        }
        room_desc += "'" 
            + implode(map(explode(short_desc, " "), capitalize), " ")
            + "'";
    }
    
    if (sizeof(matching_rooms) > 1)
    {
        say_to_player("You can find reading about that topic in the "
            + "Library stacks in the " + room_desc + " rooms.",
            this_player());      
    }
    else
    {
        say_to_player("You can find reading about that topic in the "
            + room_desc + " Library stack.",
            this_player());
    }
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
    case "rat":
    case "sewer rat":
    case "rats":
    case "sewer rats":
        say_to_player("Nasty little critters. We have to be careful to "
            + "keep them away from these precious books! Some visitors "
            + "have reported seeing them here in the library. I can't "
            + "imagine where though!", this_player());
        break;
    
    case "lemons":
    case "lemon":
    case "lemon tree":
        say_to_player("Lemons? I have smelled them in the morning. I have "
            + "no idea where they might be though. Do you need them for "
            + "something?", this_player());
        break;
    
    case "sufficient age":
        say_to_player("Sufficient age? Hmm.. sometimes it's just difficult "
            + "to tell by looking at them how old they may be. Just ask "
            + "them!", this_player());
        break;
        
    case "projects":
        projects_answer();
        break;
    
    case "first project":
    case "census":
    case "census project":
    case "census of the adventurers":
    case "census of the adventurers of Genesis":
        census_answer();
        break;
        
    case "project":
        project_answer();
        break;
    
    case "second project":    
    case "restoration":
    case "restoration project":
    case "documents":
    case "ancient documents":
    case "ancient documents project":
    case "construction":
    case "book restoration project":
    case "book restoration":
        restoration_answer();
        break;
    
    case "genesis library":
    case "library":
        say_to_player("The Genesis Library is a wonderful place to "
                    + "discover information about the Donut. "
                    + "Make sure you grab an informational packet "
                    + "and read all about it!",
                      this_player());
        break;
      
    case "stacks":
    case "library stacks":
        say_to_player("The stacks are to the east and to the west of "
                    + "here. You can find all sorts of information in "
                    + "each room of the stacks. Each room has specific "
                    + "topics that you can do research on. Oh, and the "
                    + "decorations are nice too!", this_player());
        say_to_player("If you need help finding something in the stacks "
                    + "you can just ask me to 'find' a topic that "
                    + "you are looking for!", this_player());
        break;
    
    case "book":
    case "books":
        say_to_player("The stacks are full of wonderful books filled with "
            + "knowledge! I love spending my time here, and I hope you "
            + "do too!\n", this_player());
        say_to_player("If you want to know about something, you can ask "
            + "me to find something for you. You could, for example, "
            + "<ask nikolon guild> and I'll let you know where you can "
            + "find books on that topic! Feel free to ask me for "
            + "assistance also!\n", this_player());
        break;
        
    case "decorations":
        say_to_player("Each room of the stacks is well decorated. Do let "
                    + "yourself enjoy them!", this_player());
        break;
        
    case "topics":
        say_to_player("Each room of the stacks has a specific topic for "
                    + "you to research. For example, to the east of here "
                    + "you will find guides and tutorials, including the "
                    + "tutorial journal.", this_player());
        break;
    
    case "assistance":
        say_to_player("How can I be of assistance to you? You can find "
                    + "most of what you need to know from the "
                    + "informational packets that you can grab from the "
                    + "dispenser in the circulation room. You can "
                    + "also ask me to 'find' a topic for you!", this_player());
        break;
    
    case "gastol":
    case "restorer":
    case "library restorer":
    case "gastol's office":
        say_to_player("Gastol? He's our resident Restorer. A very famous "
                    + "one at that. He's not very friendly though, so I'd "
                    + "be careful around him. He's usually in his office "
                    + "on the second floor.", this_player());
    
    case "liquid":
    case "restoring liquid":
    case "restorer liquid":
    case "book restoring liquid":
    case "bookrestorer liquid":
        liquid_answer();          
        break;
    
    case "reward":
        say_to_player("If you have completed filling your signature book, "
            + "then simply <return> it to me for your reward!", this_player());
        break;
         
    default:
        string topic;
        if (sscanf(question, "find %s", topic))
        {
            say_to_player("I can help you find information about "
                + topic + "!\n", this_player());
            topic_answer(topic);
            break;
        }
        command("shrug");
        command("say What can I say? I don't know about that.");
        command("say If you want me to find something for you, you could "
            + "\'ask nikolon find <topic>\'.");   
        send_debug_message("nikolon_fail_asks", 
            capitalize(this_player()->query_real_name()) + " failed to "
                + "get info on " + question + ".", NIKOLON_ASKS_LOG);      
    }
    
    return "";
}

/* 
 * Function name:       create_monster
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    set_name("nikolon");
    add_name("librarian");
    set_living_name("nikolon");
    set_race_name("human");
    set_adj( ({ "lanky", "light-haired", "head" }) );
    set_short("lanky light-haired librarian");
    set_gender(G_MALE);
    set_long("He looks like the head librarian.\n");

    set_stats(({ 60, 60, 60, 80, 40, 80 }));
    
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 120);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    
    set_act_time(2);
    
    // By default, Nikolon will be in the circulation desk
    // area. we will by default add the circulation actions
    add_circulation_acts();
}

public int
finished_sign_quest(object player)
{
    return player->test_bit("Sparkle", 
                            LIBRARY_SIGN_GROUP, 
                            LIBRARY_SIGN_BIT);
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
    // Nikolon has two quests to offer
    // 1. Signature Signing
    // 2. Book Restoration
    if (!finished_sign_quest(this_player())
        && !finished_restore_quest(this_player()))
    {
        say_to_player("I am so busy trying to run the Library that I "
                    + "barely have time to attend to my projects. If you "
                    + "could help, just ask me about my projects.",
                      this_player());
    }
    else if (finished_sign_quest(this_player())
             && !finished_restore_quest(this_player()))
    {
        say_to_player("Thank you so much for helping with the census "
                    + "already. I do have one other project that I would "
                    + "very much appreciate help with.", this_player());
    }
    else if (finished_restore_quest(this_player())
             && !finished_sign_quest(this_player()))
    {
        say_to_player("Thank you so much for helping to restore the "
                    + "ancient documents. The work on it is progressing "
                    + "quite nicely, thanks to you and Gastol. I do have "
                    + "one other project that I would very much "
                    + "appreciate your help with.", this_player());
    }
    else
    {
        say_to_player("Thank you so much for all your help to me. You "
                    + "have done the Genesis Library a great service "
                    + "that will not be forgotten. Because of you, things "
                    + "are running much more smoothly around here.",
                      this_player());
    }
    return "";        
}

/* 
 * Function name:       job_answer
 * Description  :       response to add_ask
 */
public string
job_answer()
{ 
    say_to_player("Why, I'm the Head Librarian of the Genesis Library of "
          + "Sparkle! I make sure that this great library is running "
          + "as smoothly as possible.", this_player());
    return "";
    
} // job_answer

/*
 * Function name:       walk_prestep
 * Description  :       Override this method to have the npc perform
 *                      any commands before performing the walk action
 * Arguments    :       direction - direction that npc will go
 *                      room - the current room file
 * Returns      :       nothing
 */
private void
walk_prestep(string direction, string room)
{
    if (room == (LIBRARY_ROOM_DIR + "waiting_room")
        && (direction == "south" || direction == "s"))
    {
        command("$open door");
    }
    else if (room == (LIBRARY_ROOM_DIR + "headoffice")
             && (direction == "north" || direction == "n"))
    {
        command("$open door");
    }
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
    
    switch (hour)
    {
    case 0..5:
    case 12..17:
        if (walk_to_room(LIBRARY_ROOM_DIR + "circulation"))
        {
            command("$yawn");
            clear_act();
        }
        break;
        
    case 6..11:
    case 18..22:
        if (walk_to_room(LIBRARY_ROOM_DIR + "headoffice"))
        {
            command("$emote checks the time.");     
            command("emote changes the sign as he leaves.");
            clear_act();   
        }
        break;

    case 23:
        if (walk_to_room(LIBRARY_ROOM_DIR + "bedroom"))
        {
            command("$stretch");
            command("$emote prepares himself mentally for rest.");
            clear_act();
        }
    }
}

/*
 * Function name:       set_room_actions
 * Description  :       Sets the actions that the npc will have depending
 *                      on the room that they are in.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
set_room_actions()
{
    string roomfile;
    
    roomfile = MASTER_OB(environment(this_object()));

    clear_act();
    switch (roomfile)
    {
    case LIBRARY_ROOM_DIR + "headoffice":
        add_headoffice_acts();
        break;
    
    case LIBRARY_ROOM_DIR + "circulation":
        add_circulation_acts();
        break;

    case LIBRARY_ROOM_DIR + "bedroom":
        add_bedroom_acts();
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
    case LIBRARY_ROOM_DIR + "headoffice":
        // Once he arrives at the headoffice
        command("$emote settles into his office chair and begins to "
              + "pore over the ancient texts.");
        break;
    
    case LIBRARY_ROOM_DIR + "circulation":
        // Once he arrives at the circulation desk, he will settle
        // in and get to work
        command("emote changes the sign.");
        command("$emote settles down at the circulation desk and "
              + "begins his work day.");
        break;
    case LIBRARY_ROOM_DIR + "bedroom":
        // Once he arrives at the bedroom
        command("$emote crawls into his bed and begins resting.");
        break;
    }
    
    set_room_actions();
}

/*
 * Function name:       walk_precondition_hook
 * Description  :       Override this to define something that the npc
 *                      will check before moving onto the next step.
 * Arguments    :       direction - direction the next move is
 *                      roomfile  - current room location
 * Returns      :       0/1 - allow walk step or not
 */
public int
walk_precondition_hook(string direction, string roomfile)
{
    return !is_busy();
}

/* 
 * Function name:       add_circulation_acts
 * Description  :       These are actions that Nikolon should have when
 *                      he is in the circulation room.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
add_circulation_acts()
{
    clear_act();
    add_act("$emote checks the area to see if anyone needs any "
          + "assistance with the Library.");
    add_act("$emote nods off a little while trying to look alert "
          + "and attentive.");
    add_act("$emote attempts to organize the papers on his desk, then "
          + "quickly gives up.");
    add_act("$say Welcome to the Genesis Library! Please, come and have "
          + "a look around.");
    add_act("$say Did you know that you can <browse> many of the "
          + "bookshelves in the stacks?");
    add_act("$say You can find the stacks to the east and to the west "
          + "of here.");
    add_act("$say There are informational packets in the dispenser. "
          + "Please feel free to <grab> one to learn about the Library!");
}

/* 
 * Function name:       add_headoffice_acts
 * Description  :       These are actions that Nikolon should have when
 *                      he is in his office.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
add_headoffice_acts()
{
    clear_act();
    add_act("$emote pores over the ancient documents in front of him.");
    add_act("$emote flips a page in the book that he is holding.");
    add_act("$emote mutters to himself.");
    add_act("$emote looks perplexed at the book he is staring at.");
    add_act("$say I wish someone would help Gastol to restore these "
          + "documents so that I can read them properly.");
}

/* 
 * Function name:       add_bedroom_acts
 * Description  :       These are actions that Nikolon should have when
 *                      he is in his bedroom
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
add_bedroom_acts()
{
    clear_act();
    add_act("$emote turns in his bed restlessly.");
}

/* 
 * Function name:        reward_player_sign_quest
 * Description  :        Function to reward quest xp when the player
 *                       completes the quest
 * Arguments    :        player - player receiving the xp
 * Returns      :        nothing
 */
public void
reward_player_sign_quest(object player)
{
    int avg_stat = player->query_average_stat();
    player->catch_tell("Nikolon takes the black signature book.\n");
    if (finished_sign_quest(player))
    {
        player->catch_tell("You get no more experience for helping "
                         + "Nikolon again with the census.\n");
        send_debug_message("library_signature_quest", 
            capitalize(player->query_real_name()) + " (" + avg_stat + ") "
          + "completes the signature quest again, but no xp is granted.", 
            SIGNATURE_QUEST_LOG);        
        return;
    }
    
    command("$thank " + player->query_real_name());
    say_to_player("This is wonderful! You have done a great service to "
                + "the Genesis Library of Sparkle. I won't forget this!",
                  this_player());
    player->set_bit(LIBRARY_SIGN_GROUP, LIBRARY_SIGN_BIT);
    player->add_exp_quest(LIBRARY_SIGN_EXP);
    player->catch_tell("You feel more experienced!\n");
    
    send_debug_message("library_signature_quest", 
        capitalize(player->query_real_name()) + " (" + avg_stat + ") "
      + "is awarded " + LIBRARY_SIGN_EXP + " experience.", 
        SIGNATURE_QUEST_LOG);        
}

/* 
 * Function name:        reward_player_restore_quest
 * Description  :        Function to reward quest xp when the player
 *                       completes the quest
 * Arguments    :        player - player receiving the xp
 * Returns      :        nothing
 */
public void
reward_player_restore_quest(object player)
{    
    command("$thank " + player->query_real_name());
    say_to_player("This is wonderful! You have done a great service to "
                + "the Genesis Library of Sparkle. I won't forget this!",
                  this_player());
    player->set_bit(LIBRARY_RESTORE_GROUP, LIBRARY_RESTORE_BIT);
    player->add_exp_quest(LIBRARY_RESTORE_EXP);
    player->catch_tell("You feel more experienced!\n");
    
    int avg_stat = player->query_average_stat();
    send_debug_message("library_restorer_quest", 
        capitalize(player->query_real_name()) + " (" + avg_stat + ") "
      + "is awarded " + LIBRARY_RESTORE_EXP + " experience.", 
        RESTORER_QUEST_LOG);
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
    if (cannot_see_person(to))
    {
        command("say I wonder who gave me these?");
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
    
    if (obj->id("_library_restoring_liquid"))
    {
        if (obj->get_owner() != to->query_real_name())
        {
            say_to_player("I don't think Gastol gave this liquid to "
                        + "you, but I thank you for bringing this to "
                        + "me.", to);
            obj->remove_object();
            send_debug_message("library_restorer_quest", 
                capitalize(to->query_real_name()) + " attempted to give "
              + "a restoring liquid that belonged to " + obj->get_owner()
              + ".", RESTORER_QUEST_LOG);            
            return;
        }
        obj->remove_object();
        set_alarm(0.5, 0.0, &reward_player_restore_quest(to));
        return;
    }
    
    ::return_object(obj, to);
}


/*
 * Function name:        check_remaining_quests
 * Description  :        See if there are other quests that the player
 *                       can still do here.
 * Arguments    :        object who - the player to check for
 * Returns      :        int 1 - all quests complete
 *                           0 - quests remain unfinished
 */
public int
check_remaining_quests(object who)
{
    if (finished_sign_quest(who) &&
        finished_restore_quest(who))
    {
        return 1;
    }

    return 0;
} /* check_remaining_quests */
