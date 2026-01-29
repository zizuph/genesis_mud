/* 
 * /d/Ansalon/guild/society/room/joinroom.c
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
 * The room where you join the Secret Society of Uncle Trapspringer.
 * It's not exactly the best or neatest code, so copy at your own risk!
 * 
 * Coded by Gwyneth sometime in 1999
 * Cleaned up slightly by Gwyneth January 2001
 */
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>

inherit KENDERMORE_IN;

#define PLAYER_I_IS_ON_LOG   "_player_i_is_on_log"
#define SAVE_FILE            MASTER
#define KENDER_ALLOWED_ME_IN "_kender_allowed_me_in"
#define CLOSED 0

static int on_log;
static object don_box, elder;

string no_attack();
int wall_check();
int k_check();
int k_allow();

void
reset_kendermore_room()
{
    setuid();
    seteuid(getuid(this_object()));

    if(!don_box)
    {
        don_box = clone_object(KGOBJ + "box");
        don_box->move(this_object());
    }

    if(!objectp(elder))
    {
        elder = clone_object("/d/Ansalon/private/entrance/npc/elder");
        elder->move(this_object());
    }
}

void
create_kendermore_room()
{
    set_short("Curious cluttered room");
    set_long("This is the outer room of what seems to be some sort of " + 
        "guild. The carpet is plush and as green as meadow grass. " + 
        "The walls are painted in such a way that you feel as if you " + 
        "are actually outdoors. A forest seems to spread out on the " + 
        "northern wall, while a lake glitters to the west. A road winds " + 
        "into view on the eastern wall, continuing on towards mountains " + 
        "to the south. The ceiling is a beautiful sky blue, with a few " + 
        "wispy white clouds. A bench, which looks an awful lot like an " + 
        "old log, has been set here for the weary traveller. A small " + 
        "table in the form of a moss covered stump sits beside the bench. " +
	"A slight shimmer radiates off the east wall.\n");
    add_item(({"table", "small table", "stump", "moss stump",
        "moss covered stump"}), "A tattered book is fastened to the " + 
        "table.\n");
    add_item(({"book", "tattered book"}), "This is a tattered book with " + 
        "some pages missing. Parts of it are still readable.\n");
    add_item(({"pages", "page"}), "They are yellow and worn.\n");
    add_item(({"carpet", "plush carpet"}), "It looks much like a carpet " + 
        "of meadow grass. Perhaps you could rest here if you are tired.\n");
    add_item(({"wall", "walls"}), "The way these walls have been painted " + 
        "shows great talent. The scenes around you seem to move when you're " + 
        "not looking directly at it.\n");
    add_item(({"forest", "trees", "pine trees", "northern wall", "north wall"}),
        "A wild green forest of pine trees holds infinite mysteries within " + 
        "its depths.\n");
    add_item(({"lake", "west wall", "western wall"}), "The lake looks very " +
        "peaceful. Its calm waters have hardly a ripple to mar its smooth " + 
        "surface.\n");
    add_item(({"road", "eastern wall", "east wall"}), "The road looks dusty " + 
        "and well travelled. It winds out of view in two directions.\n");
    add_item(({"mountains", "south wall", "southern wall"}), "The " +
        "mountains reach toward the sky in grand majesty. A few clouds " + 
        "crown their peaks.\n");
    add_item(({"ceiling", "sky"}), "You stare into the infinite depths of " + 
        "the blue sky, interupted only by wispy white clouds.\n");
    add_item(({"clouds", "wispy clouds", "wispy white clouds", "white clouds"}),
        "They hang lazily in the sky.\n");
    add_item(({"bench", "old log", "log"}), "It looks very comfortable for " + 
        "a log.\n");

    add_exit(KGROOM + "po", "southwest", &k_check());
    add_exit(KGROOM + "courtyard", "south", &k_allow());
    add_exit(KGROOM + "board_room", "southeast", &k_check());
    add_exit(KROOM + "street32", "north", 0);
    add_exit(KGROOM + "faerie_tree", "east", &wall_check(), 0, 1);

    add_prop(ROOM_M_NO_ATTACK, &no_attack());
    add_prop(ROOM_M_NO_MAGIC_ATTACK, &no_attack());

    setuid();
    seteuid(getuid(this_object()));
    restore_object(SAVE_FILE);

    clone_object(KGOBJ + "intro_board")->move(this_object());

    on_log = 0;
    
    reset_kendermore_room();
}

string
no_attack()
{
    if (environment(this_player()) != this_object())
       return "";

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " spluttering furiously");
    tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " prepares to attack, but out of nowhere a kender jumps in front of " + 
        this_player()->query_objective() + " and knocks " + 
        this_player()->query_possessive() + " feet out from under " + 
        this_player()->query_objective() + "! " + 
        capitalize(this_player()->query_pronoun()) + " splutters furiously " +
        "as " + this_player()->query_pronoun() + " tries to reach " + 
        this_player()->query_possessive() + " opponent, but the kender " +
        "skips away delighted with his prank.\n", this_player());
    return "You prepare to attack, but out of nowhere a kender " +
        "jumps in front of you and knocks your feet out from " +
        "under you! You splutter furiously as you try to reach " +
        "your opponent, but he skips away from you delighted with " +
        "his prank.\n";
}

int
read(string str)
{
    string filename;
    notify_fail("Read what page? Use 'read page <number>'.\n");
    if (!str)
    {
        return 0;
    }

    switch(str)
    {
        case "book":
        case "index":
            str = "page 1";
        case "page 1":
            write("You turn the book to page one and read " + 
		"what's written there...\n");
	    say(QCTNAME(this_player()) + " turns a page in the book and " + 
		"starts to read.\n");
            filename = (KGTEXT + 1);
            break;
        case "page 2":
            write("You turn the book to page two and read " + 
		"what's written there...\n");
	    say(QCTNAME(this_player()) + " turns a page in the book and " + 
		"starts to read.\n");
            filename = (KGTEXT + 2);
            break;
        case "page 3":
            write("You turn the book to page three and read " + 
		"what's written there...\n");
	    say(QCTNAME(this_player()) + " turns a page in the book and " + 
		"starts to read.\n");
            filename = (KGTEXT + 3);
            break;
        case "page 4":
            write("You turn the book to page four and read " + 
		"what's written there...\n");
	    say(QCTNAME(this_player()) + " turns a page in the book and " + 
		"starts to read.\n");
            filename = (KGTEXT + 4);
            break;
        case "page 5":
	    write("You turn to the page where skills and abilities " + 
		"should be described, only to find that it's missing! " + 
		"A jagged line shows where the page was torn out. In " + 
		"its place, there is a piece of paper with a picture of a " + 
		"kender sneaking up on sleeping dragon.\n");
	    say(QCTNAME(this_player()) + " turns a page in the book and starts " + 
		"to read.\n");
            return 1;
	default:
	    notify_fail("There is no page number " + str + " in this book.\n");
	    return 0;
    }

    if (file_size(filename) > 0)
    {
        setuid();
        seteuid(getuid());
        cat(filename);
    }

    return 1;
}

int
wall_check()
{
    setuid();
    seteuid(getuid(this_object()));

    if (MEMBER(this_player()))
    {
	write("You find just the right place, slip through the " +
            "magic wall and follow the path to a sheltered valley.\n\n");
        return 0;
    }
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    write("You smack right into the wall.\n");
    return 1;
}

int
k_check()
{
    setuid();
    seteuid(getuid(this_object()));

    if (MEMBER(this_player()))
        return 0;

    if (this_player()->query_wiz_level())
        return 0;

    write("Only members are allowed further.\n");
    return 1;
}

int
k_allow()
{
    setuid();
    seteuid(getuid(this_object()));

    if (!MEMBER(this_player()) && 
      (this_player()->query_prop(KENDER_ALLOWED_ME_IN) != 1))
    {
        write("You have to be allowed in by a member first.\n");
        return 1;
    }
    return 0;
}
  
int
occjoin(string str)
{
    object sh;
    mixed why;

    notify_fail("Follow what? Kender ways?\n");
    if (!str)
        return 0;

    if (str != "kender ways")
        return 0;

    if (!this_player()->test_bit("Ansalon",3,0))
    {
        notify_fail("You must prove yourself before joining this guild.\n");
        log_file(KEN_LOG, extract(ctime(time()), 4, 15) + " " +
            this_player()->query_name() + " tried to join the guild, but " + 
            "hadn't done the quest.\n", 500000);

        return 0;
    }
 
    if (VMASTER->query_banished(this_player()->query_real_name()))
    {
        notify_fail("You have been banished from the guild, and need to " + 
            "find a member to help you become unbanished.\n");
        log_file(KEN_LOG, extract(ctime(time()), 4, 15) + " " + 
            this_player()->query_name() + " tried to join the guild, " +
            "but was banished.\n");
        return 0;
    }


 //   if (!VMASTER->query_invited(this_player()->query_real_name()))
 //   {
//      notify_fail("You need to be invited to join the guild first. Please " + 
//         "'request invitation'. You will either be invited or not " + 
//         "within one week. After one week, you can ask a member to " +
//         "invite you, as you may only request an invitation one " +
//        "time.\n");
//       return 0;
//  }

    if (this_player()->query_alignment() < -239)
    {
        notify_fail("You are too evil to be trusted in the Secret " +
            "Society of Uncle Trapspringer!\n");
        return 0;
    }

    if (this_player()->query_race_name() != "kender")
    {
        notify_fail("Only kender can be members of this guild!\n");
        return 0;
    }

    if (this_player()->query_guild_style_lay() == "thief")
    {
        notify_fail("A thief! You disgrace the Kender name!\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    /* Clone the shadow */
    sh = clone_object(KENDERG_SHADOW_N);

    /* Try to add the shadow to the player */
    switch (sh->add_occ_shadow(this_player()))
    {
    case 1:
        /* We have successfully shadowed the player, so we're set */
        write("You eagerly step forward with a bounce in your step.\n " + 
            "You declare your intentions to follow the ways of " +
            "the Secret Society of Uncle Trapspringer.\n");
        say(QCTNAME(this_player()) + " steps forward, a bounce in " + 
            this_player()->query_possessive() + " step. " + 
            capitalize(this_player()->query_pronoun()) + " declares " + 
            this_player()->query_possessive() + " intention to follow " +
            "the ways of the Secret Society of Uncle Trapspringer!\n");
        write("Welcome to the Secret Society of Uncle Trapspringer!\n");
        write("A young kender runs up and hands you a string of " + 
            "beads.\n");

        log_file(KEN_LOG, extract(ctime(time()), 4, 15) + " " +
            this_player()->query_name() + " joined the guild.\n", 500000);
        VMASTER->add_member(this_player()->query_real_name());
        return 1;

    case -4:
        /* The player has an occ guild already, or one of his existing
        * guilds has blocked this one.
        */
        write("Your other guilds prohibit your joining this one!\n");
        break;

    default:
        /* Some error in shadowing */
        write("An error has prevented you from joining.\n");
        break;
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    log_file(KEN_LOG, extract(ctime(time()), 4, 15) + " " +
        this_player()->query_name() + " tried to join the guild, " + 
        "but couldn't.\n", 500000);

    return 1;
}

int
leave_guild(string str)
{
    notify_fail("Leave the guild?\n");
    if (!str)
        return 0;

    if (str != "the guild")
        return 0;

    if (!this_player()->query_guild_name_occ(GUILD_NAME))
    {
        notify_fail("But you aren't a member of this guild!\n");
        return 0;
    }

    if (!this_player()->remove_occ_kender(this_player(), "left"))
    {
	write("You did not leave the guild. Please bug report.\n");
	return 1;
    }

    write("You decide to leave the Secret Society of Uncle Trapspringer!\n");
    write("You feel the carefree feeling of a kender fall away from you, " + 
        "and a weakness infuses your being.\n");
    say(QCTNAME(this_player()) + " decides to leave the Secret Society!\n");
    log_file(KEN_LOG, extract(ctime(time()), 4, 15) + " " + 
        this_player()->query_name() + " decided to leave the guild.\n", 500000);
    return 1;
}

int
log_sit(string str)
{
    if ((str == "on bench") || (str == "on log"))
    {
        if (!on_log)
        {
            write("You sit down on the old log to rest your weary feet.\n");
            say(QCTNAME(this_player()) + " sits down on the old log, resting " + 
            this_player()->query_possessive() + " weary feet.\n");
            this_player()->add_prop(PLAYER_I_IS_ON_LOG, 1);
            this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting on an old " +
                "log");
            on_log = 1;
            return 1;
        }

        if (on_log)
        {
            if (!this_player()->query_prop(PLAYER_I_IS_ON_LOG))
            {
                write("There's not enough room left on the old log for you " + 
                "to sit down.\n");
                say(QCTNAME(this_player()) + " eyes the old log with a sigh.\n");
                return 1;
            }

            if (this_player()->query_prop(PLAYER_I_IS_ON_LOG))
            {
                write("You are already seated!\n");
                return 1;
            }
        }
    }

    if ((str == "in grass") || (str == "on carpet"))
    notify_fail("Sit on what?\n");
    return 0;
}

int
stand_up(string str)
{
    if ((str == "up") || (!str))
    {
        if (this_player()->query_prop(PLAYER_I_IS_ON_LOG))
        {
            write("You stand up from the log, feeling refreshed and ready " + 
                "for travel.\n");
            say(QCTNAME(this_player()) + " stands up from the log, looking " +
                "very refreshed.\n");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            this_player()->remove_prop(PLAYER_I_IS_ON_LOG);
            on_log = 0;
            return 1;
        }

        if (!this_player()->query_prop(PLAYER_I_IS_ON_LOG))
        {
            notify_fail("First you must be seated in order to stand!\n");
            return 0;
        }
    }

    notify_fail("Stand up?\n");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!living(ob))
        return;

    if (ob->query_prop(PLAYER_I_IS_ON_LOG))
    {
        ob->catch_tell("You stand up from the log, feeling refreshed and " + 
            "ready for travel.\n");
        ob->tell_watcher(QCTNAME(ob) + " stands up from the log, looking " + 
            "very refreshed.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop(PLAYER_I_IS_ON_LOG);
        on_log = 0;
        return;
    }

    return;
}    

int
request_invit(string str)
{
    notify_fail("Request an invitation?\n");
    if (!str)
        return 0;

    if (str != "an invitation" && str != "invitation")
        return 0;

     
    if (VMASTER->query_requested(this_player()->query_real_name()))
    {
        notify_fail("You've already requested an invitation. Contact a " +
            "member for another invitation.\n");
        return 0;
    }

    if (CLOSED)
    {
        notify_fail("The guild's not open yet, please try again at a " +
            "later date.\n");
        return 0;
    }

    if (MEMBER(this_player()))
    {
//      notify_fail("But you're already a member! If you want to invite " +       // Navarre May 18th 2013.
//          "someone into the guild, call a vote on it in the voting room.\n");
        notify_fail("But you're already a member!\n");
        return 0;
    }

    if (VMASTER->query_invited(this_player()->query_real_name()))
    {
        notify_fail("You've already been invited!\n");
        return 0;
    }

    if (VMASTER->query_enemy(this_player()->query_real_name()))
    {
        notify_fail("You've been declared an enemy of the guild. Contact " +
            "a member to get removed.\n");
        return 0;
    }

    if (VMASTER->query_banished(this_player()->query_real_name()))
    {
        notify_fail("You've been banished from joining the guild. Contact " +
            "a member to get removed.\n");
        return 0;
    }

//  elder->command("say You have requested an invitation to join the Kender " + 
//      "guild. If you don't know any members, now is the time to start to " + 
//      "get to know your potential guildmates! Return in a week's time " + 
//      "for your answer.\n");

//    elder->start_invite(this_player()->query_real_name());
    elder->command("$say Since when does a kender need an invitation " +
                   "to do anything?!\n");
    elder->command("$grin merrily");
    return 1;
}

int
allow_in(string str)
{
    object *oblist;

    oblist = PARSE_THIS(str, "%l");

    notify_fail("Allow who to pass into the courtyard?\n");
    if (!strlen(str))
        return 0;

    if (!sizeof(oblist))
        return 0;

    if (sizeof(oblist) > 1)
    {
        notify_fail("One at a time please!\n");
        return 0;
    }

    if (!MEMBER(this_player()))
    {
        notify_fail("Only members can allow people to pass.\n");
        return 0;
    }

    else
    {
        if(VMASTER->query_enemy(oblist[0]->query_real_name()))
        {
            notify_fail("You can't allow an enemy into the guild!\n");
            return 0;
        }

        if(VMASTER->query_banished(oblist[0]->query_real_name()))
        {
            notify_fail("This person has been banished from the guild, " +
                "and may not enter.\n");
            return 0;
        }

        write("You allow " + oblist[0]->query_name() + " to pass into the " + 
            "courtyard.\n");
        oblist[0]->catch_tell(this_player()->query_The_name(oblist[0]) + 
            " allows you to pass south into the courtyard.\n");
        say(QCTNAME(this_player()) + " allows " + QTNAME(oblist[0]) + 
            " into the courtyard.\n", ({ oblist[0], this_player() }));
        
        oblist[0]->add_prop(KENDER_ALLOWED_ME_IN, 1);
    }

    return 1;
}

int
new_gitem(string str)
{
    if(present("kender_guild_emblem", this_player()))
    {
        notify_fail("You already have beads. To exchange them for " +
            "a different kind, visit the sleeping quarters.\n");
        return 0;
    }

    if(this_player()->query_login_time() > 
      (this_player()->query_login_time() + 60))
    {
        notify_fail("Please wait a minute after entering the " +
            "realms to try to recover a set of beads.\n");
        return 0;
    }

    if(MEMBER(this_player()))
    {
        setuid();
        seteuid(getuid(this_object()));
        clone_object(GUILD_EMBLEM)->move(this_player(), 1);
        write("You find that you've lost your beads, so " +
            "you pick up a new strand.\n");
        tell_room(this_object(), QCTNAME(this_player()) + 
            " takes a new strand of beads\n", this_player());
    }
    else
    {
        write("You must be a member of this guild to take " +
            "a new strand of beads! Contact a wizard if you are a " +
            "member.\n");
    }

    return 1;

}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(VMASTER->query_invited(ob->query_real_name()))
    {
        set_alarm(0.5, 0.0, &ob->catch_tell("Welcome " +
            ob->query_name() + "! You " +
            "have been invited to join the Secret Society of " +
            "Uncle Trapspringer!\n"));
    }
    
    if (MEMBER(ob) && ob->query_updated_kender_guild() != 2017)
    {
        setuid();
        seteuid(getuid(this_object()));
        
        if (ob->remove_guild_occ())
        {
            object *gitems, shadow = clone_object(KENDERG_SHADOW_N);
            if (shadow->add_occ_shadow(ob) != 1)
            {
                ob->catch_msg("Something went horribly when affixng the new " +
                "kender shadow, please contact wizards of Krynn.\n");
                return;
            }
            
            ob->remove_cmdsoul(GUILD_CMDSOUL);
            ob->update_hooks();
            
            if (sizeof(gitems = filter(all_inventory(ob), &operator(!=)(,0) @
                                &function_exists("setup_beads",))) > 1)
                foreach(object item: gitems) { item->remove_object(); }
            
            ob->catch_msg("\n" +
            "*************************************************************\n" +
            "\nYou have learnt new things!! You should probably read the " +
            "kender help files for more information on what has changed!\n\n" +
            "*************************************************************\n");
        }
    }
}

void
init()
{
    ::init();
    add_action(read, "read"); 
    add_action(occjoin, "follow");
    add_action(leave_guild, "leave");
    add_action(log_sit, "sit");
    add_action(stand_up, "stand");
    add_action(request_invit, "request");
    add_action(allow_in, "allow");
    add_action(new_gitem, "recover");
}


void
list_save()
{
    setuid();
    seteuid(getuid(this_object()));
    save_object(SAVE_FILE);
}

