/*
 * /d/Ansalon/guild/kender_occ/kender_soul.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Soul for the Secret Society of Uncle Trapspringer
 * This soul holds the special skills of the Secret Society
 *
 * Commands found in other files:
 * Sling special -  /d/Ansalon/guild/kender_occ/sling.c
 * Taunt special -  /d/Ansalon/guild/kender_occ/taunt.c
 * Taunt list    -  /d/Ansalon/guild/kender_occ/taunt_list.c
 * Dodge special -  /d/Ansalon/guild/kender_occ/dodge.c
 * Shadow        -  /d/Ansalon/guild/kender_occ/kender_shadow.c
 * Emotions      -  /d/Ansalon/guild/kender_occ/emotions.c
 * Guild item    -  /d/Ansalon/guild/kender_occ/obj/gitem.c
 * Songs         -  /d/Ansalon/guild/kender_occ/songlist.c
 *
 * See /d/Ansalon/guild/kender_occ/info/dir_list for a listing of 
 * directories.
 *
 * Gwyneth, June - September 1999
 * Modification log:
 * Gwyneth, January 2001 - General cleanup and recode and various changes
 *                         to specials. See included files for details.
 * 
 */

/**
 * Navarre February 4th 2007
 * - Added Lady title for Everylady of the Infinite Trails
 * - Added Lady title for Lady of the None
 * 
 * NOTE: When adding a title, be sure to update /help/titles also.
 */

#pragma save_binary

inherit "/cmd/std/command_driver";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "guild.h"
#include "/d/Ansalon/common/defs.h"
#include "wimpy_check.c"
#include "emotions.c"
#include "sling.c"
#include "dodge.c"
#include "taunt.c"

#define DELAY       9.0
#define FAERIE_ROOM (KGROOM + "faerie_tree")
#define MOREOBJ     "/obj/more"
#define TEMP_ROOM   (KGROOM + "faerie_temp")

/*
 * Function name : get_soul_id
 * Description   : Give a name for this soul
 * Returns       : string - the soul's id
 */
string
get_soul_id()
{
    return "Secret Society";
}

/*
 * Function name : query_cmd_soul
 * Description   :   identify this as a valid cmdsoul
 * Returns       :       1
 */
int
query_cmd_soul()
{
    return 1;
}

/*
 * Function name : query_cmdlist
 * Description   : Get the commands available on this soul and
 *                 their corresponding function names.
 * Returns       : mapping - a mapping that maps command names
 *                 to function names.
 */
mapping
query_cmdlist()
{
    return ([

      "borrow" : "borrow",
      "collect" : "collect",
      "dodge" : "dodge_special",
      "kdodge" : "dodge_special",
      "help" : "help",
      "kangry" : "kangry",
      "kblush" : "kblush",
      "kbow" : "kbow",
      "kbow2" : "kbow2",
      "kchew" : "kchew",
      "kclap" : "kclap",
      "kcry" : "kcry",
      "kdance" : "kdance",
      "kdiscard" : "kdiscard",
      "kembrace" : "kembrace",
      "kenlist" : "kenlist",
      "kexcuse" : "kexcuse",
      "kfidget" : "kfidget",
      "kfind" : "kfind",
      "kflip" : "kflip",
      "kgiggle" : "kgiggle",
      "kgrin" : "kgrin",
      "khide" : "khide",
      "khug" : "khug",
      "kinspect" : "kinspect",
      "kintro" : "kintro",
      "kjab" : "kjab", 
      "klaugh" : "klaugh",
      "klisten" : "klisten",
      "kmagic" : "kmagic",
      "kmimic" : "kmimic",
      "kmischief" : "kmischief",
      "knod" : "knod",
      "kpreen" : "kpreen",
      "kpull" : "kpull",
      "kroad" : "kroad",
      "krummage" : "krummage",
      "ksad" : "ksad",
      "ksay" : "ksay",
      "kshake" : "kshake",
      "kshuffle" : "kshuffle",
      "kskip" : "kskip",
      "ksleeve" : "ksleeve",
      "ksolemn" : "ksolemn",
      "kspin" : "kspin",
      "kstifle" : "kstifle",
      "kswing" : "kswing",
      "kthink" : "kthink",
      "ktired" : "ktired",
      "ktitle" : "ktitle",
      "kview" : "kview",
      "kwave" : "kwave",
      "tiptoe" : "autoquiet",
      "autoquiet" : "autoquiet",
      "sling" : "sling",
      "taunt" : "taunt_special",
      "wander" : "wander",
      "kcall" : "call_faerie",

    ]);
}

/* Function name : borrow
 * Description   : Switches the command borrow for the command steal
 */
int
borrow(string str)
{
    return "/cmd/live/thief"->steal(str);
}

/* Function name : collect
 * Description   : Collects some pebbles from the ground, adds a prop
 *                 to the room to keep track which have had pebbles
 *                 collected from them, and how much.
 * Returns       : Returns 0 on failure, 1 on success.
 */
int
collect(string str)
{
    object pebble, collector;
    int collected, t;
    collector = this_player();
    t = time();

    /* Query the prop that is set in the room when pebbles are collected. */
    collected = (environment(collector)->query_prop("_room_i_pebbles_taken"));

    if ((str == "pebbles") || (str == "pebble")) 
    {
        if (collected > (t - 600) && (collected != 0))
        {
            notify_fail("You find no pebbles.\n");
            return 0;
        }

        /* Only allow mass collecting in outside rooms. */
        if (environment(collector)->query_prop(ROOM_I_INSIDE))
        {
            setuid();
            seteuid(getuid());
            pebble = clone_object(KGOBJ + "pebble");
            pebble->set_heap_size(3);
            pebble->move(collector);

            write("You gather some pebbles from the ground.\n");

            /* Add prop to the room to keep track of how     */
            /* many pebbles have been collected in the room. */
            environment(collector)->add_prop("_room_i_pebbles_taken", t);
            return 1;
        }

        /* Clone the pebbles and give the message. */
        setuid();
        seteuid(getuid());
        pebble = clone_object(KGOBJ + "pebble");
        pebble->set_heap_size(9);
        pebble->move(collector);

        write("You gather some pebbles from the ground.\n");

        /* Add prop to the room to keep track of how     */
        /* many pebbles have been collected in the room. */
        environment(collector)->add_prop("_room_i_pebbles_taken", t);
        return 1;
    }

    notify_fail("Collect what?\n");
    return 0;
}

/* Function name : help
 * Descriptions  : Allows members to read help files.
 * Arguments     : string str - The file to read
 * Returns       : Returns 0 on failure, 1 on success.
 */
int
help(string str)
{
    string subject, filename;

    if (!strlen(str))
        return 0;

    /* Gives the general help file. */
    if (str == "kender")
    {
        setuid();
        seteuid(getuid());
        clone_object(MOREOBJ)->more(KGHELP + "help", 1);
        return 1;
    }

    /* Assign the word that the kender is looking for help on to subject. */
    if (sscanf(str, "kender %s", subject) != 1)
        return 0;

    filename = KGHELP + subject;
    /* Check to see if the file has any content. */
    if (file_size(filename) > 0)
    {
        setuid();
        seteuid(getuid());
        clone_object(MOREOBJ)->more(filename, 1);
        return 1;
    }
    
    /* Failure message if no file with content was found. */
    notify_fail("No help on that subject I'm afraid.\n");
    return 0;
}

/* Function name : can_understand_ksay
 * Description   : Tests to see if a person can understand ksay or not.
 * Arguments     : object target - the one listening to ksay
 * Returns       : 1 if target can understand, 0 if not
 */
int
can_understand_ksay(object target)
{
    if(MEMBER(target))
    {
        return 1;
    }
    else if(target->query_wiz_level())
    {
        return 1;
    }
    else if(target->query_race_name() == "kender" &&
       target->query_skill(SS_LANGUAGE) > 49)
    {
        return 1;
    }
    else if(target->query_race_name() == "gnome" &&
            target->query_skill(SS_LANGUAGE) > 59)
    {
        return 1;
    }    
    else if(target->query_skill(SS_LANGUAGE) > 64)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Function name : ksay
 * Description   : Allow a kender to say something in the kender
 *                 tongue with a large chance of only being
 *                 understood by other kender.
 * Arguments     : string str - the string to ksay
 * Returns       : 1 on success, 0 on failure
 */
int
ksay(string str)
{
    int i, size, j, new_size;
    mixed *oblist;
    string *v_list = ({ "a", "e", "i", "o", "u", "y" });
    string *c_list = ({ "b", "c", "d", "f", "g", "h", "j", "k",
                        "l", "m", "n", "p", "q", "r", "s", "t",
                        "v", "w", "x", "z" });
    string *v_clist = ({ "A", "E", "I", "O", "U", "Y" });
    string *c_clist = ({ "B", "C", "D", "F", "G", "H", "J", "K",
                        "L", "M", "N", "P", "Q", "R", "S", "T",
                        "V", "W", "X", "Z" });
    string *new_str, alt_str;

    if(!strlen(str))
    {
        notify_fail("Say what in the secret kender tongue?\n");
        return 0;
    }

    oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));

    for(i = 0, size = sizeof(oblist); i < size; i++)
    {
        if(!can_understand_ksay(oblist[i]))
        {
            new_str = explode(str, "");

            for(j = 0, new_size = sizeof(new_str); j < new_size; j++)
            {
                if(member_array(new_str[j], v_list) != -1)
                {
                    new_str[j] = v_list[random(sizeof(v_list))];
                }
                else if(member_array(new_str[j], c_list) != -1)
                {
                    new_str[j] = c_list[random(sizeof(c_list))];
                }
                else if(member_array(new_str[j], v_clist) != -1)
                {
                    new_str[j] = v_clist[random(sizeof(v_clist))];
                }
                else if(member_array(new_str[j], c_clist) != -1)
                {
                    new_str[j] = c_clist[random(sizeof(c_clist))];
                }
            }

            alt_str = implode(new_str, "");
            break;
        }
    }

    write("You speak in your secret kender tongue: " + str + "\n");
    for(i = 0, size = sizeof(oblist); i < size; i++)
    {
        if(!can_understand_ksay(oblist[i]))
        {
            oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) + 
                " speaks in a secret kender tongue: " + alt_str + "\n");
        }
        else
        {
            oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) + 
                " speaks in a secret kender tongue: " + str + "\n");
        }
    }

    return 1;
}

/* Function name : ktitle
 * Description   : Allow a Kender to substitute their guild title for
 *                 one on a set list, regain their guild title, or turn
 *                 any title off.
 * Arguments     : string str - The title to change to.
 * Returns       : Returns 0 on failure, 1 on success.
 */
int
ktitle(string str)
{
string *new_titles = ({"Blacksmith of the Disappearing Hammer", 
                     "Grander Master of the Knights",
                     "Grander Mistress of the Knights",
                     "Higher Justice of Solamnia",
                     "Emperor of the Highbulp Clan",
                     "Empress of the Highbulp Clan",
                     "September Doctor of Music", 
                     "Close Personal Friend of Gu", 
                     "Pouchlift-Er, the Wiggly Fingered Magician", 
                     "Caring Treehugger of Gondor", 
                     "Dancer of the Borrowed Veil", 
                     "High Bunnyrabbit of Calia", 
                     "King of the Bloodsuckers",
                     "Queen of the Bloodsuckers",
                     "Chatterer of the Valar",
                     "Sundazed Tonguebiter of Athas",
                     "Arena Oversweeper",
                     "Exhaling Warrior of the Onion of Shadows",
                     "Final Sludge of the Army of Grandma",
                     "Mightiest Boogerslayer of the Kneeslapper Clan",
                     "Musclebrained Mercenary of the Pink Lizardarmy",
                     "New Iguana Rider of the Purple Lizardarmy",
                     "Tightwad of the Poor Bastard's Club",
                     "Wheezing Geezer of the Old Timer's",
                     "LooseScrewOfTheTinkerers",
                     "Hyperactive Sugar Adept of the Popsicle " + 
                     "Vision, Child Priest of the Candy Order",
                     "Pretentious Junk Collector of Sanction",
                     "Legendary Dragonpoker of Kendermore",
                     "King Priest of Hylo",
                     "Queen Priestess of Hylo",
                     "Deaf Knight of Dargaard",
                     "Wizard of the Bright Blue Robes",
                     "Beloved Wanderer of Krynn",
                     "Soothing Tongue of Sincerity",
                     "Revered Son of Fizban",
                     "Revered Daughter of Fizban",
                     "Wandering Plague of Thorbardin",
                     "Hand that Roams",
                     "Lord of the None",
                     "Lady of the None",
                     "Boisterous General of the Army of Elfnoggin",
                     "Hide and Seek Champion of Kendermore",
                     "Everlord of the Infinite Trails of Wonder and Magic",
                     "Everlady of the Infinite Trails of Wonder and Magic",
                     "Invisible Ticklemonster Champion of Kendermore",
                     "Holder of Falling Objects and Watcher of Pouches " +
                         "with Holes",
                     "Lollipop Licker of the Little People Clan",
                     "Conjurer of Mystical Faerie Magic",
		     "Master Taunter of Kendermore",
		     "Mistress Taunter of Kendermore",
		     "Epic Head Whomper for Hire",
		     "Key of Many Doors",
		     "Learned Candy-Eater of Gelan",
		     "Legendary Paradox of the High Candy Seas",
		     "Brightest Rainbow-colored Stone of the Elementals",
		     "Deckpuppy of the High Candy Seas",
		     "Knight of the Lollipop",
                     "Sell-Sword of Sparkle",
                     "Mythological Warrior of Kendermore",
                     "Epic Lady of the Rent-A-Swords",
                     "Epic Lord of the Rent-A-Swords",
		     "Mid-Afternoon Lady of Fizban",
		     "Mid-Afternoon Lord of Fizban",
                     "Acorn of the Sprit Square, Bringer of Sugar " +
                     "and Spirit of the Matches",
                     "Big Mouth of the Onion Warriors of Sillybarus",
                     });

    int i, sz;
    object liv, tag;
    string old_title;

    tag = present("_kender_name_tag", this_player());
    liv = this_player();
    old_title = (this_player()->query_title());

    /* No argument given, no title set. */
    if (!strlen(str))
    {
        notify_fail("Set your title to what?\n");
        return 0;
    }

    /* Wizards can set their own titles. */
    if (liv->query_wiz_level())
    {
        notify_fail("Wizards can set their title themselves.\n");
        return 0;
    }

    /* Turn titles off. */
    if (str == "none")
    {
        liv->add_prop("_ken_new_title", "");
        write("You will now show no title.\n");
        return 1;
    }

    /* Set title to the normal guild title. */
    if (str == "normal")
    {
        liv->add_prop("_ken_new_title", "normal");
        write("You will now show your normal title.\n");
        return 1;
    }

    if(!objectp(tag))
    {
        notify_fail("You don't have a new nametag! All you can do now is " +
            "set your title to 'none' or 'normal'.\n");
        return 0;
    }

    /* Set title to one from the list. */
    for (i = 0, sz = sizeof(new_titles) ; i < sz ; i++)
    {
        if (str == new_titles[i])
        {
           liv->add_prop("_ken_new_title",new_titles[i]);
           write("You will now show " + new_titles[i] + " as " + 
               "your title.\n");
           tag->remove_object();
           return 1;
        }
    }
    return 0;
}

/* Function name : autoquiet 
 * Description   : Turns autoquiet(autosneak) on or off, works with
 *                 the shadow. Taken from Ranger stealth with Elessar's
 *                 permission, changed messages. The rest of the  
 *                 autoquiet code is in the shadow.
 * Arguments     : string str - on/off
 * Returns       : Returns 0 on failure, 1 on success
*/

int
autoquiet(string str)
{
    int old_as = this_player()->query_autosneak();
    int new_as;

    /* Set failure message. */
    notify_fail("Quiet how?\n");

    /* No sneaking if skipping */
    if ((this_player()->query_m_in() == "skips in, topknot swinging") ||
        (this_player()->query_m_in() == "skips in, whistling a happy tune"))
        {
            notify_fail("It's too difficult to sneak and skip at the same time.\n");
            return 0;
        }

    /* If there's no argument, toggle autosneak. */
    if (!str)
      this_player()->set_autosneak(!old_as);

    /* Turn autosneak on. */
    else if (str == "on" || str == "yes")
      this_player()->set_autosneak(1);

    /* Turn autosneak off. */
    else if (str == "off" || str == "no")
      this_player()->set_autosneak(0);

    else
      return 0;

    new_as = this_player()->query_autosneak();

    /* Give appropriate messages for turning autosneak on and off. */
    if (new_as)
      write("You concentrate on being very very quiet.\n");
    else
      write("You quit worrying about how quiet you are.\n");

    return 1;
}

/* Function name : wander_away
 * Description   : Gives wander messages, moves the wanderer, and 
 *                 detracts mana/fatigue.
 * Arguments     : string dest - Destination, object room - From
 * Returns       : 1
 */
public int
wander_away(string dest, object room)
{
    /* Fail to wander if they aren't in the original room */
    if (environment(this_player()) != room)
    {
        write("You decide not to wander after all.\n");
        return 0;
    }

    /* The messages seen by the kender and watchers in both rooms. */
    write("When nobody is watching, you quietly wander away.\n");
    LSAYBB("You look away from ", " for a moment, " +
        "and when you turn back, " + this_player()->query_pronoun() + " is gone.");
    LTELL_ROOMBB(dest, this_player(), "You turn your head slightly, and " +
        "notice that ", " has wandered in from " +
        "somewhere.", 1);

    /* Move the kender to the destination. */
    this_player()->move_living("M", dest, 1);

    /* Subtract a bit of mana and fatigue. */
    this_player()->add_mana(-15);
    this_player()->add_fatigue(-5);
    return 1;
}

/* Function name : wander
 * Description   : Kender have an uncanny ability to disappear when
 *                 you're least expecting them to. It appears to the
 *                 watcher that the kender has just wandered away
 *                 while they weren't looking...
 *                 Checks to see if the kender is allowed to wander.
 * Arguments     : string str - Direction to wander
 * Returns       : Returns 0 on failure, 1 on success
*/

int
wander(string str)
{
    mixed func, *funcs, wd;
    int i, sz;
    string *exits, ex, *dests, dest;
    object room;

    /* Find the environment of the kender. */
    room = (environment(this_player()));

    /* Find the commands to exit the room (out, north, south, in...) */
    exits = (room->query_exit_cmds());

    /* Find the destination rooms. */
    dests = (room->query_exit_rooms());

    /* Find any functions called when a player goes through an exit. */
    funcs = (room->query_exit_functions());

    /* Set up failure message. */
    notify_fail("Wander where?\n");

    /* No argument. */
    if (!str)
        return 0;

    /* Give a greater chance of sneaking for those with higher sneak skill. */
    if (this_player()->query_skill(SS_SNEAK) < random(101))
    {
        notify_fail("You don't think you can wander away very quietly.\n");
        return 0;
    }

    /* Shortcuts */
    if (str == "w")
        str = "west";
    if (str == "n")
        str = "north";
    if (str == "s")
        str = "south";
    if (str == "e")
        str = "east";
    if (str == "ne")
        str = "northeast";
    if (str == "se")
        str = "southeast";
    if (str == "nw")
        str = "northwest";
    if (str == "sw")
        str = "southwest";
    if (str == "u")
        str = "up";
    if (str == "d")
        str = "down";

    for (i = 0, sz = sizeof(exits) ; i < sz ; i++)
    {
        func = funcs[i];
        ex = exits[i];

        /* Find if the argument matches one of the room's exits. */
        if (str == exits[i])
        {
            /* See if the kender is too tired to wander. */
            if (this_player()->query_fatigue() <=4)
            {
                notify_fail("You are too tired to move in that " + 
                    "direction.\n");
                return 0;
            }

            /* Check if the kender has enough mana to wander. */
            if (this_player()->query_mana() <= 14)
            {
                notify_fail("You can't think straight enough to wander " +
                    "off without anyone noticing.\n");
                return 0;
            }

            /* Resolve the exit VBFC */
            wd = room->check_call(func); 

            /* If you can't pass, don't pass. */
            if (wd != 0) 
            {
                if (wd >= 1)
                {
                    notify_fail("");
                    return 0;
                }
            }

            if ((this_player()->query_mana() > 14) &&
              (this_player()->query_fatigue() > 4))
            {
                dest = dests[i];
                /* Set a small delay before wandering. */
                if (this_player()->query_skill(SS_SNEAK) < 80)
                    set_alarm(1.0, 0.0, &wander_away(dest, room));
                else
                    set_alarm(0.5, 0.0, &wander_away(dest, room));
                return 1;
            }
        }
    }
    return 0;
}

/*
 * Function name: get_faerie
 * Description  : summons a player's faerie
 * Arguments    : object who - the player
 */
public void
get_faerie(object who)
{
    int size, i;
    object *faeries, faerie;

    /* Find all faeries in the game */
    faeries = find_living("faerie", 1);
    size = sizeof(faeries);
    if (size)
    {
        for (i = 0; i < size; i++)
        {
            if (faeries[i]->query_owner() == this_player()->query_real_name())
            {
                faerie = faeries[i];
                break;
            }
        }
    }

    if (!objectp(faerie))
    {
        FAERIE_ROOM->recall_faerie(this_player());
        return;
    }
    else
    {
        if (file_name(environment(faerie)) == TEMP_ROOM)
        {
            write("Your faerie is a bit busy now.\n");
            return;
        }
        else
        {
            faerie->fly_to_owner();
            return;
        }
    }
}

/*
 * Function name: call_faerie
 * Description  : Begins the faerie summonging
 * Arguments    : string str - arguments used
 * Returns      : 1 - success 0 failure
 */
public int
call_faerie(string str)
{
    int i, size, faeriep;
    object *oblist;

    if (!strlen(str))
    {
        notify_fail("Call your faerie?\n");
        return 0;
    }

    str = lower_case(str);

    if (str != "faerie" &&
      str != "my faerie")
    {
        notify_fail("Call your faerie?\n");
        return 0;
    }

    oblist = all_inventory(this_player());
    oblist = FILTER_RACE(oblist, "faerie");

    size = sizeof(oblist);
    for (i = 0; i < size; i++)
    {
        if (oblist[i]->query_owner() == this_player()->query_real_name())
        {
            faeriep = 1;
            break;
        }
    }

    if (faeriep)
    {
        notify_fail("Your faerie is already here!\n");
        return 0;
    }

    write("You close your eyes tight and silently call your " +
        "faerie friend.\n");
    say(QCTNAME(this_player()) + " closes " + 
        this_player()->query_possessive() + " eyes tight and " +
        "furrows " + this_player()->query_possessive() + " brow.\n");

    set_alarm(DELAY, 0.0, &get_faerie(this_player()));
    return 1;
}

