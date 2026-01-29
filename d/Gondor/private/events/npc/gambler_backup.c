/*
 * Copyright (C) October 1, 2000
 *
 * This piece of code is the intellectual property of the Genesis wizard
 * Stern and may not be used or copied in any form without his explicit 
 * permission.
 *
 */

/*
 * /d/gondor/private/events/npc/gambler.c
 *
 * This is the game initiating npc for the Gondor events.
 */


inherit "/std/monster";

#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/private/events/events.h"

#define RELAY       (EVENTOBJ + "gambler_relay")
#define DIE         "/d/Gondor/common/dwarf_guild/obj/die"
#define MY_NAME     "gaiton"
#define MY_TITLE    "the Incredible Gambler from Pelargir"
#define MY_HEIGHT   175
#define MY_VOLUME   70000
#define MY_WEIGHT   70000
#define AV_STAT     80

#define MAX_TEXTS 60  /* max nr of lines in TEXT */
#define TEXT ({"I won a horse once.", \
               "Games are my life!", \
               "I love a good game.", \
               "Step right up!", \
               "You look like you enjoy a good game.", \
               "I won the Gladiator Chest once, but almost got " + \
                   "my head chopped off when I went to collect my prize.", \
               "I am unbeatable. I won the beard off a Neidar once.", \
               "I won the Rangers' tree. Now what are they going to hug?", \
               "I won the Way of the Dragon. " + \
                   "One wonders what Way the Monks go now.", \
               "I won the Rockfriends Teddy Bear. But they threw " + \
                   "a tantrum when I tried to take him away.", \
               "I once won a weekend arrangement in the dungeons " + \
                   "below Minas Morgul.", \
               "I'm the best. I won the teeth of a vampire only last week.", \
               "I won the Air, Wind and Fire. Now what are the " +    \
                   "Elementalists going to focus on?", \
               "You want to know what happened to Angmar Army? " + \
                   "I won the key to their hideout and locked them all up.", \
               "And umm.. the Khiraa,... No, you don't want to know.", \
               "I won a mansion in Terel only a week ago.", \
               "I won the Monument of the Fallen from a Calian Warrior. ",  \
               "I won a Dragon from a Dragon Army General!",          \
               "I won a shop in Flotsam", \
               "I won a knight's scabbard once.", \
               "I won Wayreth Tower, but I haven't managed to find it yet.", \
               "I won the Vingaard Keep, but they won't let me in.", \
               "I won a set of kitchen knives from a shadowy elf.", \
               "I won the Muse from an unfortunate Minstrel only yesterday.", \
               "I won a mage's pink boxers (yes, it's really true!).", \
               "Don't fear the Cadets. I won their donk!", \
               "I won a Red Dragon Army Sergeant, but I gave him back.", \
               "Winning from kender is senseless. " + \
                   "You keep losing your winnings.", \
               "Hey, Mister, wanna play a game?", \
               "Hey, Lady, let's play!", \
               "Play for one gold coin!", \
               "We need four or more players.", \
               "Introduce and give me a gold coin to play.", \
               "I don't play with people I don't know.", \
               "Get three more players and tell me when you are ready.", \
               "I don't give money back.", \
               "So who are playing?", \
               "Okay, let's start. We'll play a scavenger hunt!\n", \
               "You have 90 minutes.", \
	       "You have an hour.", \
               "First one back with all of the following items wins:", \
               "Something Something rusty, something green, " + \
                   " something polished, something clean.", \
               "Something copper, something silver, something gold, " + \
                   "something platinum. Coins don't count.", \
               "Something old, something blue, something glittering, " + \
                   "something spiked.", \
               "Something dull, something white, something suede, " +  \
                   "something leather.", \
               "Something mat, something green, a red berry, " + \
                   "something empty.", \
               "Something dried, something fresh, something that " + \
                   "comes in a pair, something tempered.", \
               "Something a hobbit would like, something a goblin " + \
                   "would like, a straw, a cape.", \
               "A medallion, something grey, something mithril, " + \
                   "something touched by battle.", \
               "An empty oil-flask, a bottle, some water, some liquor.", \
               "A sausage, some bread, a blue gem, a flower.", \
               "A ring, a red stone, a rusty weapon, an iron armour.", \
               "A horn, a feather, a black pearl, some water.", \
               "Four meats from different animals. They may be turned " + \
                   "into dishes.", \
               "Five different beers.", \
               "Five different containers.", \
               "Okay, let's start. We'll have a Team Building Event. " + \
                   "The Gods above know we can use some team building.", \
               "I need at least 2 contestants. Every contestant will " + \
                   "create as big a team as possible. The biggest team " + \
                   "wins.", \
               "You have 10 minutes.", \
               "I'm busy with a game right now. Come back later." })

/*
 * Prototypes.
 */
void add_act_cact();
string ask_stuff();

/*
 * Global variables.
 */
static int busy = 0;
static int logging = 0;
static string logfile;

/*
 * Function name: create_monster
 * Description  : Constructor. Called when this NPC is cloned. 
 */
void
create_monster()
{
    if (!IS_CLONE)
    {
        return;
    }

    ::create_monster();
    setuid();
    seteuid(getuid());

    set_name(MY_NAME);
    add_name( ({ "gambler" }) );
    set_living_name(MY_NAME);
    set_race_name("human");
    set_adj("fun-loving");
    add_adj("ever-smiling");
 
    set_long("He is a fun-loving ever-smiling male human.\n" +
        "He is famous in the City of Pelargir and beyond.\n" +
        "He looks like he enjoys a game of practically anything " +
        "if it makes a few coins.\n");

    set_title(MY_TITLE);

    set_gender(G_MALE);
    set_alignment(-200);
    add_prop(CONT_I_HEIGHT, MY_HEIGHT);
    add_prop(CONT_I_WEIGHT, MY_WEIGHT);
    add_prop(CONT_I_VOLUME, MY_VOLUME);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(LIVE_I_NON_REMEMBER,1);
    add_prop(NPC_I_NO_LOOKS, 1);   /* don't want his looks shown */
    add_prop(OBJ_I_NO_ATTACK, 1);  /* servant is protected from attacks */
    set_base_stat(SS_STR, AV_STAT); /* since he doesn't fight only */
    set_base_stat(SS_DEX, AV_STAT); /* average stat matters for title */
    set_base_stat(SS_CON, AV_STAT);
    set_base_stat(SS_WIS, AV_STAT);
    set_base_stat(SS_INT, AV_STAT);
    set_base_stat(SS_DIS, AV_STAT);
    set_skill(SS_CLIMB, 100);
    set_skill(SS_SWIM,  100);
    set_skill(SS_TRACKING, 100); 
    set_skill(SS_SNEAK,  100);
    set_skill(SS_HIDE,  100);
    set_skill(SS_LOC_SENSE, 100);
    set_skill(SS_TRADING, 100);
    set_skill(SS_ACROBAT, 100);
    set_skill(SS_FR_TRAP, 100);
    set_skill(SS_LANGUAGE, 100);
    set_skill(SS_LANG_COMMON, 100);
    set_skill(SS_ACROBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_RIDING, 100);
    set_skill(SS_ANI_HANDL, 100);
    set_skill(SS_APPR_MON, 100);
    set_skill(SS_APPR_OBJ, 100);
    set_skill(SS_APPR_VAL, 100);
    add_act_cact();
    add_ask(({"help", "game", "task", "hunt", "quest" }), ask_stuff);    
    reset_monster();
}

/*
 * Function name: query_option
 * Description  : Use this to emulate the echo option.
 * Arguments    : int option - the option to check.
 * Returns      : int 1/0 - true/false.
 */
int
query_option(int option)
{
   if (option == OPT_ECHO)
   {
        return 1;
   }
   return 0;
}


/*
 * Function name: npcspeak
 * Description  : Deals with action "npcspeak"
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
npcspeak(string str)
{
    int line;  
  
    if (!strlen(str))
    {
        notify_fail("Syntax: npcspeak <number>\n");
        return 0;
    }
    line = atoi(str);
    if (line <= 0)
    {
         notify_fail("Syntax: npcspeak <number>\n");
         return 0;
    }
    if (line > MAX_TEXTS)
    {
         notify_fail("There are not that many lines.\n");
         return 0;
     }
 
     command("say " + TEXT[line - 1]);
     return 1;
}

/*
 * Function name: reset_actions
 * Description  : remove previous actions and speech
 */
void
reset_actions()
{
    monster_act       = ({ });
    monster_act_left  = ({ });
    monster_chat      = ({ });
    monster_chat_left = ({ });
}

/*
 * Function name: npcsilence
 * Description  : Deals with action "npcsilence"
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
npcsilence(string str)
{
    if (strlen(str))
    {
        notify_fail("Syntax: npcsilence\n");
        return 0;
    }
    reset_actions();
    return 1;
}

/*
 * Function name: npcunsilence
 * Description  : Deals with action "npcunsilence"
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
npcunsilence(string str)
{
    if (strlen(str))
    {
        notify_fail("Syntax: npcunsilence\n");
        return 0;
    }
    reset_actions();
    add_act_cact();
    return 1;
}

/*
 * Function name: npcbusy
 * Description  : Deals with action "npcbusy"
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
npcbusy(string str)
{
    if (strlen(str))
    {
        notify_fail("Syntax: npcbusy\n");
        return 0;
    }
    busy = 1;
    return 1;
}

/*
 * Function name: npcunbusy
 * Description  : Deals with action "npcunbusy"
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
npcunbusy(string str)
{
    if (strlen(str))
    {
        notify_fail("Syntax: npcunbusy\n");
        return 0;
    }
    busy = 0;
    return 1;
}

/*
 * Function name: npclog
 * Description  : Deals with action "npclog"
 * Arguments    : string str - the command line argument.
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
npclog(string str)
{
    if (!strlen(str))
    {
        write("Syntax: npclog on / off / <filename>\n");
        write("Current logging: " + (logging ? "on" : "off") + ".\n");
        write("Current filename: " + (strlen(logfile) ? logfile : "not set") +
            "\n");
        return 1;
    }
    switch(str)
    {
    case "on":
        if (!strlen(logfile))
        {
            notify_fail("No log file. Use \"npclog <filename>\" first.\n");
            return 0;
        }
        if (logging)
        {
            notify_fail("Logging is already enabled.\n");
            return 0;
        }
        logging = 1;
        write("Logging enabled.\n");
        write_file(logfile, ctime(time()) + " Logging started.\n");
        return 1;

    case "off":
        if (!logging)
        {
            notify_fail("Logging is not enabled.\n");
            return 0;
        }
        logging = 0;
        write("Logging stopped.\n");
        write_file(logfile, ctime(time()) + " Logging stopped.\n");
        return 1;

    default:
        logfile = EVENTLOG + str;
        write("Logging to file: " + logfile + "\n");
        write("Use \"npclog on\" to start logging.\n");
        return 1;
    }
}

/*
 * Function name: catch_tell
 * Description  : Use this routine to log the same information that gets
 *                sent to the player holding the remove control (but without
 *                the #Gaiton# header added.
 * Arguments    : string str - the text to log.
 */
void
catch_tell(string str)
{
    ::catch_tell(str);
    
    if (logging && strlen(logfile))
    {
        write_file(logfile, str);
    }
}

/*
 * Function name: init_living
 * Description  : When wizards "come close" to the gambler, they get the
 *                commands added.
 */
void
init_living()
{
    ::init_living();
    if (this_player()->query_wiz_level())
    {
        add_action(npcspeak, "npcspeak", 0);
        add_action(npcsilence, "npcsilence", 0);
        add_action(npcunsilence, "npcunsilence", 0);
        add_action(npcbusy, "npcbusy", 0);
        add_action(npcunbusy, "npcunbusy", 0);
        add_action(npclog, "npclog");
    }
}

/*
 * Function name: ask_stuff
 * Description  : deals with general questions
 * Returns      : dummy string
 */
string
ask_stuff()
{
    if (busy) 
    {
       command("smile busily at " + TP->query_real_name());
       command("say I'm rather busy right now. " +
           "If you want to play a game please come back later.");

    }
    else
    {
       command("smile broadly at " + TP->query_real_name());
       command("say Games is my middle name!");  
       command("say Want to play a game?");  
    }
    return "";
}

/*
 * Function name: gender_title
 * Description  : returns the (gender dependent) title of object living.
 * Arguments    : object : living
 * Returns      : string : title
 */
string
gender_title(object living)
{
   int gender;

   gender = living->query_gender();
   switch (gender)
   {
       case G_MALE  : return ("Sir");
       case G_FEMALE: return ("my Lady");
       default      : return ("Ummm...");
   }
}

/*
 * Function name: introduce_me
 * Description  : introduces me
 * Arguments    : string - name of person to intro to
 * Returns      : void
 */
public void
introduce_me(string name)
{
    command("say I'm honoured to meet you, " + 
        gender_title(find_player(name)) + "!");
    command("introduce me to " + name);
    command("smile charm");
}


public void
add_introduced(string name)
{
    /* This function is called automatically in someone when he is being
     * introduced' to. For this NPC it is defined to introduce himself
     * to the person that is introduced to him.
     */
    set_alarm(2.0, 0.0, &introduce_me(name));
}

/*
 * Function name: add_act_cact
 * Description  : Add the speech and actions.
 */
void
add_act_cact()
{
    reset_actions();

    set_chat_time(15 + random(10));
    add_chat("I won a horse once.");
    add_chat("Games are my life!");
    add_chat("Step right up!");
    add_chat("You look like you enjoy a good game.");
    add_chat("I love a good game.");
    add_chat("I won the Gladiator Chest once, but almost got " + 
        "my head chopped off when I went to collect my prize!");
    add_chat("I won the Way of the Dragon. " + 
        "One wonders what Way the Monks go now.");
    add_chat("I am unbeatable. I won the beard off a Neidar once.");
    add_chat("I won the Rangers' tree. Now what are they going to hug?");
    add_chat("I'm the best. I won the teeth of a vampire only last week.");
    add_chat("I won a mansion in Terel only a week ago.");
    add_chat("I won the Monument of the Fallen from a Calian Warrior.");
    add_chat("I won a Dragon from a Dragon Army General!");
    add_chat("I won a shop in Flotsam with a card game.");
    add_chat("I won a knight's prestigeous scabbard with a game of chess.");
    add_chat("I won Wayreth Tower, but I haven't managed to find it yet.");
    add_chat("I won the Vingaard Keep in a scavenger hunt, " +
        "but they won't let me in.");
    add_chat("I won the Muse from an unfortunate Minstrel only yesterday.");
    add_chat("I won a mage's pink boxers (yes, it's really true!).");
    add_chat("Don't fear the Cadets. I won their donk!");
    add_chat("I won the Rockfriends Teddy Bear. But they threw " +
        "a tantrum when I tried to take him away.");
    add_chat("I won a Red Dragon Army Sergeant, but I gave him back.");
    add_chat("I won a set of knives from a shadowy elf.");
    add_chat("Winning from kender is senseless. " +
        "You keep losing your winnings.");
    add_chat("I once won a weekend arrangement in the dungeons " +
        "below Minas Morgul.");
    add_chat("I won the Air, Wind and Fire. Now what are the " +
        "Elementalists going to focus on?");
    add_chat("You want to know what happened to Angmar Army? " +
        "I won the key to their hideout and locked them all up.");
    add_chat("I won a mithril locket from Elsach just a few days ago.");
    add_chat("I won a medallion from Elsach just a few days ago.");
    add_chat("I almost won Miclo's platinum ring just a few days ago.");
    add_chat("I won a helm with two long curved platinum horns from Tauron.");


    set_act_time(15 + random(10));
    add_act("roll dice");
    add_act("toss dice");
    add_act("smile broadly");
    add_act("smile");
    add_act("smile wealthily");
    add_act("smile confidently");
    add_act("scratch chin");
    add_act("emote counts his winnings.");
    add_act("twinkle");
    add_act("smile greedily");
    add_act("emote ponders about a new game.");
    add_act("emote throws some dice up in the air and catches them again.");
    add_act("sneeze");
    add_act("emote shuffles some cards.");
    add_act("emote looks around for new contestants.");

}

/*
 * Function name: enter_inv
 * Description  : Everything that enters into our inventory
 *                automagically becomes unstealable.
 * Arguments    : object ob - the object that enters.
 *                object from - where the object came from.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    ob->add_prop(OBJ_M_NO_STEAL, 1);
}

/*
 * Function name: leave_inv
 * Description  : Everything that leaves our inventory
 *                stealable again.
 * Arguments    : object ob - the object that leaves.
 *                object to - where the object goes to.
 */
void
leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
 
   ob->remove_prop(OBJ_M_NO_STEAL);
}


/*
 * Function name: reset_monster
 * Description  : Reset the gambler with his possessions
 */
void
reset_monster()
{
    object die;
    object relay;

    setuid();
    seteuid(getuid());

    die = present("die", this_object());
    if (!objectp(die))
    {
        die = clone_object(DIE);
        die->move(this_object());
        die = clone_object(DIE);
        die->move(this_object());
    }

    relay = present("gambler_relay", this_object());
    if (!objectp(relay))
    {
        relay = clone_object(RELAY);
        relay->move(this_object());
    }
}
