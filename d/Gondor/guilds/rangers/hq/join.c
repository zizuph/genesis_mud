#pragma save_binary
/*
 * /d/Gondor/guilds/rangers/hq/join.c
 *
 * Joining code for the Rangers of the Westlands.
 *
 * Original Ranger code developed and conceived by Elessar
 *
 * New version coded by: Gwyneth and Alto, 2001-2002
 * Modifications:
 *   Tigerlily, January 2004, added toggle for join process
 *       so that apprentice join process is intercepted
 *       until the gm re-opens for new players
 *       (in rangers.h redefine RANGERS_NOT_OPEN_FOR_JOIN to FALSE)
 *   Gwyneth, 3 May 2004: Changed by order of the Steward to
 *                        by orders from above as the Rangers aren't
 *                        as a whole under the command of the Steward.
 *                        Removed cloning of spellbook. That is obtained
 *                        elsewhere, and the apprentice must find it.
 *   Rohim, Aug. 2004--added an alarm reset function
 *   Tigerlily, Aug. 2004--changed question formats, added logs for
 *                        documenting questions/answers, save var when
 *                        players complete test
 *              Aug. 20, 2004- Fixed bug in start_question to check
 *                        for eligibility
 *              Aug. 26, 2004-removed a call to remove_tried from 
 *                        query_joined
 *              Sept. 24, 2004--added check to have full ranger vouch
 *                        for player prior to allowing them to take
 *                        Amaron's test for apprentice 
 */

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <math.h>
#include <std.h>
#include <stdproperties.h>

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#define JOINING_RANGERS               "_joining_rangers"
#define RANGER_I_RECEIVED_INSTRUCTION "_ranger_i_received_instruction"
#define RANGER_I_ANSWERED_NUM         "_ranger_i_answered_num"
#define RANGER_S_QUESTION_ID          "_ranger_s_question_id"
#define RANGER_I_CAN_JOIN             "_ranger_i_can_join"
#define TWO_DAYS                      144000  /* 40 hours */
#define THREE_DAYS                    259200
#define TWO_WEEKS                     1209600



/* Global Variables */
static int    gAlarm = 0;
static object gRecruiter;
static object gQuestor;
static string gConfirm = "";
mapping       gAnswers   = ([]);
string *      gAskedQuestions = ({});
mapping       gQuestions = ([]);
mapping       gTried = ([]);
mapping       gVouchers = ([]);
string *      gPassedTest = ({});

/* Prototypes */
public void   reset_room();
public void   create_gondor();
public int    check_joining();
public string exa_book();
public int    join_rangers(string str);
public void   amaron_command(string str);
public void   amaron_script();
public void   give_items(object player);
public int    leave_rangers(string str);
public int    read_chapter(string str);
public void   remove_tried(string name);
public int    query_tried(string name);
public int    take_test(string str);
public void   start_test(object player);
public int    start_question(string str);
public void   tell_question(string question_id, object who);
public string random_question();
public int    answer_question(string answer);
public int    check_right_answer(string name, string answer);
public void   refresh_questions();
public void   question_time_out(object player);
public int    get_name(string name);
public void   get_question(string question, string name);
public void   get_answers(string answers, string question, string name);
public void   add_question(string answers, string question, string name);
public int    remove_question(string name);
public int    query_question(string name);
public int    submit_question(string str);
public void   do_submit(string yes_no, string question);
public void   init();
public int    vouch(string str);
public int    add_voucher(string vouchee, string voucher);
public int    remove_voucher(string vouchee);
public string query_voucher(string vouchee);
public int    unvouch(string vouchee);


/* Function name: reset_room
 * Description  : Adds Amaron the recruiter to the room if not there.
 */
public void
reset_room()
{
    ::reset_room();

    if (!objectp(gRecruiter))
    {
        gRecruiter = clone_object(RANGERS_NPC + "amaron");
        gRecruiter->arm_me();
        gRecruiter->move(this_object());
    }
}

/* Function name: create_gondor
 * Description  : Initialize the room
 */
public void
create_gondor()
{
    set_short("the Recruitment Hall of the Rangers of Gondor");
    set_long("You are standing in a white walled hall with burning torches "
        + "lining the walls. On the north wall, above a wooden altar, hangs "
        + "a large black banner. "
        + "Upon the altar there is a large, gilt-leather book. The main "
        + "hall of the guildhouse is to the south.\n");

    hideout_add_items();

    add_item(({"torch", "torches"}), "The torches are all burning brightly, "
        + "and all are fastened to the wall.\n");
    add_item(({"altar", "wooden altar"}), "It is a wooden altar, the sides "
        + "covered with deer hides. Carved into the wood in Elven letters "
        + "you read the word 'Orome'. Upon the altar, seemingly held there "
        + "by crawling plants, is a large gilt-leather book.\n");
    add_item(({"hide", "hides", "deer hide", "deer hides"}), "The rangers "
        + "are skilled in woodlore and hunting. The placing of the hides "
        + "upon the wooden altar represents the reverence of the Westland "
        + "Rangers for the bounty of Arda.\n");
    add_item(({"letters", "elven letters"}), "They spell 'Orome'.\n");
    add_item(({"plants", "plant", "crawling plant", "crawling plants"}),
        "Crawling plants grow up and around the wooden altar.\n");
    add_item(({"banner", "black banner", "large banner", "large black banner"}),
        "Upon the black banner is embroidered with silver threads a "
        + "white tree surrounded by seven stars.\n");
    add_item(({"thread", "threads", "silver threads", "tree", "white tree",
        "stars", "seven stars"}), "Upon the black banner is embroidered "
        + "a white tree surrounded by seven stars.\n");
    add_item(({"wall", "walls"}), "The walls are made of white polished stone "
        + "slabs, neatly fitted among each other. This is excellent "
        + "craftsmanship.\n");
    add_item(({"white stone", "polished stone", "slab", "slabs", "stone slabs"}),
        "White stone slabs, highly polished to a gleam in the torchlight, "
        + "make up the walls of the room.\n");
    add_item(({"west wall"}), "It bears a poster. You should read it.\n");
    add_item(({"north wall"}), "It bears a large black banner.\n");
  
    add_item(({"book", "gilt-leather book", "large book"}), exa_book);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_exit(RANGERS_HQ_DIR + "boardhall", "south", check_joining, 2, 1);
    reset_room();
    restore_object(MASTER);
}

/* Function name: check_joining
 * Description  : Doesn't allow a joiner to leave the room.
 * Returns      : 1 if unable to leave the room, 0 if able to
 */
public int
check_joining()
{
    if (TP->query_prop(JOINING_RANGERS) || TP->query_prop(RANGER_S_QUESTION_ID))
    {
        write("Patience! The Master Ranger is speaking to you!\n");
        return 1;
    }
    return 0;
}


/* Function name: reset_questor
 * Description  : The questor is not present. Lets reset.
 */
public void
reset_questor()
{
    gQuestor = 0;
    remove_alarm(gAlarm);
    gAlarm = 0;
}


/* Function name: exa_book
 * Description  : Shows the book's index
 * Returns      : string - the index of the book
 */
public string
exa_book()
{
     return "The large book bound in gilt-leather looks quite new.\n"+
        "You open to the index page, and read:\n"+
        "  The Tome of the Rangers of the Westlands.\n"+
        "  Available chapters:\tWelcome,\n"+  
        "                     \tRules of the Rangers,\n"+
        "                     \tJoining the Rangers,\n"+
        "                     \tLeaving the Rangers,\n"+
        "  More information can be gained in the library.\n";
}

/* Function name: check_not_eligible
 * Description  : Checks if the player is allowed to join the Rangers,
 *                but not if they've taken the test yet.
 * Arguments    : object who - the player to test
 * Returns      : 1 if not eligible, 0 if eligible
 */
public int
check_not_eligible(object who)
{
    string name = capitalize(who->query_real_name());
    string *expelled = ({});

    if (RANGERS_NOT_OPEN_FOR_JOIN)
    {
        amaron_command("say New apprentices are not accepted " +
            "at this time by orders from above!");
        return 1;
    }

    if (!objectp(who))
    {
        return 1;
    }

    if (!objectp(gRecruiter))
    {
        write("Master Ranger Amaron is not present!\n");
        return 1;
    }

    if (RANGERS_MEMBER(who))
    {
        amaron_command("chuckle");
        amaron_command("say But your name is already written in the book!");
        return 1;
    }
    
    if (member_array(capitalize(who->query_real_name()), gPassedTest) != -1)
    {
        amaron_command("say You have already passed the test. All you " +
            "need to do now is sign the book!");
        return 1;
    }

    if (member_array(who->query_race_name(), BANNED_RACE) != -1)
    {
        /* This will give for example, Hobgoblins aren't welcome here! */
        amaron_command("say " + LANG_PWORD(capitalize(who->query_race_name())) +
            " aren't welcome here!");
        return 1;
    }
    
    if (who->query_guild_style_lay() == "thief") 
    {
        amaron_command("grumble");
        amaron_command("say We do not trust thieves. You aren't welcome here!");
        return 1;
    }
    
    if (who->query_alignment() < ALIGN_JOIN)
    {
        amaron_command("grumble");
        amaron_command("say Your heart is tainted. You aren't welcome here!");
        return 1;
    }
    
    if (MANAGER->query_is_outlaw(name))
    {
        amaron_command("scowl");
        amaron_command("say The Rangers don't accept outlaws into their " +
            "ranks!");
        return 1;
    }
   
    if (MANAGER->query_notorious_outlaw(name))
    {
        amaron_command("scowl");
        amaron_command("say The Rangers don't accept notorious outlaws " +
            "into their ranks! Get out of here now!");
        return 1;
    }
    
    if (MANAGER->query_banished(name))
    {
        amaron_command("frown");
        amaron_command("say You have been banished from joining by the " +
            "Ranger Council!");
        return 1;
    }
    // can't take test if a member of occ guild
    if (stringp(who->query_guild_name_occ()))
    {
        amaron_command("frown");
        amaron_command("say You are already a member of another guild!");
        return 1;
    }

    expelled = MANAGER->query_to_be_expelled(name);
    if(sizeof(expelled))
    {
        if (expelled[1])
        {
            amaron_command("frown");
            amaron_command("say Hmm... you have previously been expelled.");
            amaron_command("say Apparently for '" +expelled[0]+ "'.");
            amaron_command("say You will need to be unexpelled by someone " +
                "from the Ranger Council before you can join.");
            return 1;
        }
    }

    if (MANAGER->query_no_rejoin(name))
    {
/*
        amaron_command("say It has been less than two months since " +
            "you left the guild! You may try to rejoin after " +
            ctime(MANAGER->query_no_rejoin_time(name)) + ".");
*/
        amaron_command("say It has been less than a month since " +
            "you left the guild!");
        return 1;
    }

    /* Must be at least an adventurer to join */
    if (who->query_average_stat() < 55)
    {
        amaron_command("emote smiles indulgently");
        amaron_command("say You need to grow a little before you are " +
            "ready to become a ranger.");
        return 1;
    }
    
    if (query_tried(name) > 1)
    {
        amaron_command("say You have tried to join too recently. You " +
            "may try again after " + ctime(query_tried(name)) + ".");
        return 1;
    }
    
//else
    return 0;
}

/* Function name: join_rangers
 * Description  : The function called when a player tries to sign the
 *                book to become an Apprentice.
 * Arguments    : string str - the argument as entered by the apprentice
 *                             Should be book
 * Returns      : 1 if successful, 0 if not
 */
public int
join_rangers(string str)
{
    int ret;
    object who = this_player();
    string name = this_player()->query_real_name();
    string capname = capitalize(name);
    object rshadow;
    
    if (RANGERS_NOT_OPEN_FOR_JOIN)
    {
        amaron_command("say New apprentices are not accepted " +
            "at this time by orders from above!");
        return 1;
    }

    if (!strlen(str))
    {
        notify_fail("Sign the book?\n");
        return 0;
    }

    str = lower_case(str);
 
    if (!parse_command(str, ({}), "[my] [name] [in] [the] 'book'"))
    {
        notify_fail("Sign the book?\n");
        return 0;
    }
    
    
    if (who->query_wiz_level())
    {
        write("Wizards must add the shadow and soul to themselves.\n");
        return 1;
    }
    
    if (who->query_prop(RANGER_I_RECEIVED_INSTRUCTION))
    {
        amaron_command("say I've told you what you need to do! Please " +
            "'start' when you are ready, and when nobody else is " +
            "taking the test.");
        return 1;
    }
    
    if (member_array(capitalize(name), gPassedTest) == -1)
    {
        amaron_command("peer shrewdly " + OB_NUM(who));
        amaron_command("say You have not passed my test yet! If you " +
            "can answer my three questions, then I will accept " +
            "you as an Apprentice Ranger. Be warned! This test is one " +
            "you must do on your own, or risk punishment from above, as " +
            "this is considered a quest.");

        if (!present(gQuestor))
        {
            reset_questor();
        }
        
        if (gAlarm != 0)
        {
            set_alarm(1.0, 0.0, &amaron_command("say However, someone " +
                "else is taking the test right now. Please wait until " +
                "they are done."));
            return 1;
        }

        start_test(who);
        return 1;
    }

    /* Checks are all passed, let's attempt to shadow. */
    rshadow = clone_object(RANGERS_SHADOW);
    ret = rshadow->shadow_me(who, "occupational", RANGERS_STYLE, 
        RANGERS_GUILD_NAME);

    switch(ret)
    {
    case 1:
        /* The player has been successfully shadowed. */
        write("You sign the book.\n");
        say(QCTNAME(who) + " signs the book.\n");

        set_alarm(1.0, 0.0, &amaron_script());

        /* Add the name to the manager. */
        MANAGER->add_ranger(who->query_real_name(), "apprentice");
        who->set_skill(SS_REWARDED, 1);
        gPassedTest -= ({ capname });
        save_object(MASTER);

        MANAGER->rlog(RANGERS_LOG, capitalize(name) + " joined.");
        MANAGER->rlog(APPRENTICE_LOG, capitalize(name) + " successfully " +
            "passed Amaron's tests and now is an apprentice ranger!");
        //purge the name from the voucher list
        remove_voucher(capitalize(name));
        return 1;
    case -4:
        /* The player has an occupational guild already, or */
        /* one of his existing guilds has blocked this one. */
        write("Your other guilds prohibit you from joining this one!\n");
        break;
    default:
        /* Shadowing error */
        write("You were unable to enter the Rangers due to " +
            "a problem in the fabric of space. Contact the " +
            "guildmaster or make a bug report.\n");
    }

    /* We couldn't shadow the player, so remove the shadow object */
    rshadow->remove_shadow();
    MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(name) + 
        " tried to join the guild, but couldn't.");
    return 1;
}

/* Function name: amaron_command
 * Description  : Function making it simpler to force Amaron to do things.
 * Arguments    : string str - the command you want Amaron to perform
 */
public void
amaron_command(string str)
{
    gRecruiter->command(str);
}


/* Function name: amaron_script
 * Description  : The script Amaron does when joining a Ranger
 */
public void
amaron_script()
{
    object player;

    player = this_player();

    player->add_prop(JOINING_RANGERS, 1);

    amaron_command("say So you believe you have the strength, the discipline, "
        + "the will and the courage to become a Ranger of the Westlands?");
    set_alarm(2.0, 0.0, &amaron_command("emote rubs his chin thoughtfully."));
    set_alarm(5.0, 0.0, &amaron_command("say We shall certainly see. "
        + "Yes we shall."));
    set_alarm(8.0, 0.0, &amaron_command("emote glances at the leather-gilt "
        + "book."));
    set_alarm(11.0, 0.0, &amaron_command("say Nice penmanship. At least you can "
        + "read and write. A good start! But can you learn the ways of the "
        + "forest ..."));
    set_alarm(14.0, 0.0, &amaron_command("say Or the lore of herbs ..."));
    set_alarm(17.0, 0.0, &amaron_command("say Or the will of the Valar?"));
    set_alarm(19.0, 0.0, &amaron_command("emote sighs thoughtfully."));
    set_alarm(22.0, 0.0, &amaron_command("say So many of our apprentices "
        + "never do."));
    set_alarm(25.0, 0.0, &amaron_command("emote gazes to the East. His "
        + "expression "
        + "momentarily clouds, but then brightens as if the sun has come "
        + "out once again."));
    set_alarm(30.0, 0.0, &amaron_command("say With each new recruit, there is "
        + "fresh hope. Indeed we have very high hopes for you."));
    set_alarm(35.0, 0.0, &amaron_command("say Take this scroll. It contains "
        + "enough guidance to help you find your new bunk, in addition "
        + "to some other useful information. You may also find this cloak "
        + "and other items rather useful."));

    set_alarm(39.0, 0.0, &give_items(player));

    set_alarm(43.0, 0.0, &amaron_command("say Good luck to you, young "
        + "ranger. May the light of Elbereth illuminate your path!"));
    set_alarm(44.0, 0.0, &amaron_command("emote lowers his gaze briefly as "
        + "he bows gracefully."));
    set_alarm(45.0, 0.0, &player->remove_prop(JOINING_RANGERS));
    set_alarm(45.0, 0.0, &player->remove_prop(RANGER_I_CAN_JOIN));
}

/* Function name: give_items
 * Description  : Gives the guild items to a new recruit
 * Arguments    : object player - the player to give the items to
 */
public void
give_items(object player)
{
    setuid();
    seteuid(getuid());

    clone_object(RANGERS_OBJ + "join_scroll.c")->move(player);
    clone_object(RANGERS_OBJ + "brown_cloak.c")->move(player);

    player->catch_tell("You are handed a scroll and a brown cloak. "
        + "You also suddenly notice a small ring in your hand.\n");
    tell_room(this_object(), QCTNAME(player) + " is handed a scroll and "
        + "a brown cloak.\n", player);
}

/* Function name: leave_rangers
 * Description  : Allows a Ranger to leave the guild
 * Arguments    : string str - the argument as entered by the player
 * Returns      : 1 if successful, 0 if not
 */
public int
leave_rangers(string str)
{
    object who = this_player();
    string name;

    if (!strlen(str))
    {
        notify_fail("Erase your name from the book?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, ({}), "[my] 'name' [from] [the] [book]"))
    {
        notify_fail("Erase your name from the book?\n");
        return 0;
    }
    else if (!RANGERS_MEMBER(who))
    {
        write("You do not notice your name in the book. If you are " +
            "a Ranger, please make a bug report.\n");
        return 1;
    }

    name = who->query_real_name();

    if (gConfirm != name)
    {
        write("Are you sure you wish to erase your name from the " +
            "book and leave the Rangers? Erase your name again if " +
            "you are sure.\n");
        gConfirm = name;
        return 1;
    }

    write("You scratch your name from the book.\n");
    MANAGER->remove_ranger(name);
    who->expel_ranger("Left voluntarily");
    return 1;
}

/* Function name: read_chapter
 * Description  : Lets a player read the book 
 * Arguments    : string str - the chapter to read
 * Returns      : 1 if successful, 0 if not
 */
public int
read_chapter(string str)
{

    if (!strlen(str)) 
    {
        NF("Read what?\n");
        return 0;
    }

    switch (LOW(str))
    {
    case "book":
        write("You open the book to the index page, and read:\n" +
            "  The Tome of the Rangers of the Westlands.\n" +
            "  Available chapters:\tWelcome,\n" +
            "                     \tRules of the Rangers,\n" +
            "                     \tJoining the Rangers,\n" +
            "                     \tLeaving the Rangers,\n" +
            "  More information can be gained in the library.\n");
        say(QCTNAME(TP) + " reads the index page of the large " +
            "gilt-leather book.\n");
        break;

    case "welcome":
        write("\nWELCOME!\n\n" +
            "Welcome to the Guild Hall of the Rangers of the Westlands!\n\n" +
            "And congratulations on finding this place! By doing so, " +
            "you have proven a beginning talent as a pathfinder and " +
            "scout, in other words some of the talents needed for becoming " +
            "a Ranger. Be proud of your passing this initial test!\n\n" +
            "The Rangers are a part of the fighting forces of the Free " +
            "Peoples of Middle-earth. Founded by the Dunedain as scouts " +
            "and guerrillas, the Rangers now accept representatives of " +
            "all the Free Peoples, to defend Gondor, and to retake " +
            "Ithilien and Arnor from the minions of the Dark Lord.\n\n" +
            "The struggle is tough, for the Enemy's forces are numerous " +
            "and strong, and at times only the hope of " +
            "the return of the King keeps our spirit up. " +
            "But the lands are beautiful, and the hope of renewed peace and " +
            "prosperity is great enough inspiration to keep us going.\n\n" +
            "To succeed in this guild, you should be a good " +
            "roleplayer, without ambitions of becoming a powerful hero. " +
            "You should also be familiar with Master J.R.R. Tolkien's " +
            "great trilogy, 'The Lord of the Rings', for it is out of " +
            "that saga the Rangers have been shaped, and it is in the " +
            "likeness of that saga that these lands have been made.\n\n" +
            "You must have high moral standards, and a will to learn " +
            "and to defend the Free Peoples and fight the Enemy. And you " +
            "will also, above all, need to learn patience.\n\n");
        say(QCTNAME(TP)+" reads the welcome-page in the gilt-leather book.\n");
        break;
    case "rules":
    case "rules of the rangers":
        write("Rules for the Rangers of the Westlands.\n\n" +
            HANGING_INDENT("  1.  To serve the Free People by fighting " +
            "against the Evil One, his agents and minions.\n", 6, 0) +
            HANGING_INDENT("  2.  To swear fealty and service to Gondor, " +
            "and to the Lord and Steward of the realm.\n", 6, 0) +
            HANGING_INDENT("  3.  To keep and defend secrets of Gondor " +
            "from falling in wrongful hands, by protecting Gondor with " +
            "your life.\n", 6, 0) +
            HANGING_INDENT("  4.  No mage may be a Ranger of Gondor. To " +
            "have such a profession, allowing offensive spells, you will " +
            "have to leave the guild.\n", 6, 0) +
            HANGING_INDENT("  5.  Kender and goblins are not allowed to " +
            "become Rangers.\n", 6, 0) +
            HANGING_INDENT("  6.  Those elves who acknowledge not the " +
            "authority of the Valar, but spite them by having sworn " +
            "allegiance to a spawn of Ungoliante are not permitted to " +
            "join the ranks of the Rangers of the Westlands.\n", 6, 0) +
            HANGING_INDENT("  7.  No ranger shall engage in thievery.\n", 6, 0));
        say(QCTNAME(TP)+" reads the rules of the Rangers of the Westlands.\n");
        break;
    case "joining":
    case "join":
    case "joining the rangers":
        write("\nJoining the Rangers of the Westlands.\n\n" +
            "As the Rules state, no mage, kender, goblin, or dark elf may " +
            "become a Ranger of Gondor.\n\n" +
            "You are hereby advised to read the chapter about leaving the " +
            "Rangers of the Westlands before you join.\n\n" +
            "In order to join you will first need a full ranger to vouch " +
            "for you before Amaron. Amaron will decide whether you are " +
            "eligible for joining, by looking into your heart and by " +
            "asking you three questions, which you much answer correctly. " +
            "If you pass the test, Amaron will allow you to sign the book.\n\n " +
            "Be absolutely sure you want " +
            "to do this, for the penalty of changing your mind is not " +
            "small. You will then be given a ring as physical proof of your " +
            "membership of the Rangers of the Westlands, and a scroll " +
            "telling you more about the services and privileges this " +
            "membership makes available to you.\n\n" +
            "After joining, you will be a Ranger Apprentice, learning the " +
            "ways of Rangers until you are found ready to join a Company.\n\n");
            say(QCTNAME(TP) + " reads the chapter about joining the Rangers " +
                "of the Westlands.\n");
            break;
    case "leaving":
    case "leave":
    case "leaving the rangers":
        write("\nLeaving the Rangers of the Westlands.\n\n" +
            HANGING_INDENT("  1.  If you manage to join the Rangers of the " +
            "Westlands, you are probably not a kender or a goblin. If, " +
            "however, you pick a new body after being killed, and become " +
            "a kender or a goblin, you will automatically be expelled from " +
            "the guild.", 6, 0) +
            HANGING_INDENT("  2.  The Captains, at their discretion, may " +
            "expel you from the guild for unacceptable behavior.", 6, 0) +
            HANGING_INDENT("  3.  If you feel this guild is not the right " +
            "guild for you, you may leave the guild by erasing your name " +
            "from this book.\n", 6, 0) + "All the three items above will " +
            "remove you from the Guild of the Rangers of the Westlands.\n\n" + 
            "However, leaving the guild will not be free of consequence. " +
            "You will lose all privileges offered by the Guild, which " +
            "includes the right to wear a token of your guild membership, " +
            "and use of the facilities within the headquarters of the Guild. " +
            "As well, you may find yourself considerably weaker.\n\n");
        break;

    default:
        return 0;
    }

    return 1;
}

/* Function name: remove_tried
 * Description  : Removes a player from the tried question list
 * Arguments    : string name - the player to remove from the list
 */
public void
remove_tried(string name)
{
    if (!strlen(name))
        return;

    name = capitalize(name);
    if (member_array(name, m_indexes(gTried)) == -1)
        return;

    gTried = m_delete(gTried, name);
    save_object(MASTER);
    return;
}

/* Function name: query_tried
 * Description  : Has this player tried to answer the question before?
 * Arguments    : string name - the player's name
 * Returns      : int - the time to try again
 */
public int
query_tried(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gTried)) == -1)
        return 0;
    // Remember that they tried once before
    // but let them try again
    if (time() >= gTried[name])
    {
/*
        remove_tried(name);
        save_object(MASTER);
*/
        return 1;
    }

    return gTried[name];
}

/* Function name: take_test
 * Description  : Allows a recruit to get instructions for taking the test
 * Arguments    : string str - as entered by the player, should be 'test'
 * Returns      : 1 for success, 0 for failure
 */
public int
take_test(string str)
{
    object tp = this_player();

    if (!strlen(str) && 
      lower_case(str) != "test" && lower_case(str) != "the test")
    {
        notify_fail("Take the test?\n");
        return 0;
    }
    if (RANGERS_MEMBER(tp))
    {
        amaron_command("say You are already a Ranger, so are ineligible " +
            "to take the test.");
        amaron_command("say Ranger hopefuls are given three questions " +
            "to answer. They get three minutes to answer each one. If " +
            "they pass, then I will consider accepting them as an " +
            "Apprentice Ranger. They should receive no help, or risk " +
            "punishment from above, as this is considered a quest.");
        return 1;
    }

    /* Would this player be able to join the Rangers otherwise? */
    if (check_not_eligible(tp))
        return 1;

    if (tp->query_prop(RANGER_I_CAN_JOIN))
    {
        amaron_command("chuckle amusedly");
        amaron_command("say What are you, a glutton for punishment? " +
            "You've passed the test. All you need to do is sign the book!");
        return 1;
    }
    if (!strlen(query_voucher(tp->query_real_name())))
    {
        set_alarm(1.0, 0.0, &amaron_command("say You must be vouched " +
            "for by a full ranger before you can take the test."));
        return 1;
    }
    if (query_tried(tp->query_real_name()) > 1)
    {
        amaron_command("say You have tried to join too recently. You " +
            "may try again after " + 
            ctime(query_tried(this_player()->query_real_name())) + ".");
        return 1;
    }

    amaron_command("peer shrewdly " + OB_NUM(tp));
    amaron_command("say You want to know about the test? If you " +
        "can answer my three questions, then I will consider accepting " +
        "you as an Apprentice Ranger. Be warned! This test is one " +
        "you must do on your own, or risk punishment from above, as " +
        "this is considered a quest.");

    if (!present(gQuestor))
    {
        reset_questor();
    }

    if (gAlarm != 0)
    {
        set_alarm(1.0, 0.0, &amaron_command("say Someone " +
            "else is taking the test right now. Please ask me again " +
            "when they are done."));
        return 1;
     }

     start_test(tp);
     return 1;    
}

/* Function name: start_test
 * Description  : Start the test
 * Arguments    : object player - the player to start the test for
 */
public void
start_test(object player)
{
    int tried = query_tried(player->query_real_name());

    if (!strlen(query_voucher(player->query_real_name())))
    {
        set_alarm(1.0, 0.0, &amaron_command("say You must be vouched " +
            "for by a full ranger before you can take the test."));
        return;
    }

    if (tried > 1)
    {
        amaron_command("say You have tried to join too recently. You " +
            "may try again after " + 
            ctime(query_tried(this_player()->query_real_name())) + ".");
        return;
    }

    /* Keep track that this player has received instructions on the test. */
    this_player()->add_prop(RANGER_I_RECEIVED_INSTRUCTION, 1);

    set_alarm(8.0, 0.0, &amaron_command("say You have ten minutes " +
        "to answer me. When you believe you have the right answer, " +
        "'answer <your answer>'. Your answer should be in the form " +
        "a, b, c or d, or yes/no."));
    set_alarm(13.0, 0.0, &amaron_command("say If you get it right, I will " +
        "ask you two more."));

    if (tried)
        set_alarm(16.0, 0.0, &amaron_command("say Since you have tried " +
            "this before, you would have to wait for two weeks before " +
            "you can try again if you answer incorrectly."));
    else
        set_alarm(17.0, 0.0, &amaron_command("say If you answer " +
            "incorrectly, you will have to wait three days before you can " +
            "try again."));

    set_alarm(20.0, 0.0, &amaron_command("say Let me know when you are " +
        "ready to 'start'."));
    return;
}

/* Function name: start_question
 * Description  : Starts the questioning
 * Arguments    : string str - the argument entered by the player, irrelevant
 * Returns      : 1
 */
public int
start_question(string str)
{
    string question_id, name;
    object tp = this_player();

    name = capitalize(tp->query_real_name());

    /* The test alarm is active. Someone else must be taking the test.
       Let's not cause any confusion by two people taking the same test. */
    if (!present(gQuestor))
    {
        reset_questor();
    }
    
    if (gAlarm != 0)
    {
        set_alarm(1.0, 0.0, &amaron_command("say I'm sorry, someone " +
            "else is taking the test right now. Please wait until " +
            "they are done."));
        return 1;
    }

    if (check_not_eligible(tp))
    {
        return 1;
    }

    if (!strlen(query_voucher(tp->query_real_name())))
    {
        set_alarm(1.0, 0.0, &amaron_command("say You must be vouched " +
            "for by a full ranger before you can take the test."));
        return 1;
    }

    /* This prop keeps track of a player who has been given instructions.
       This prop will be set to -1 if they have been given instructions. */
    if (!tp->query_prop(RANGER_I_RECEIVED_INSTRUCTION))
    {
        set_alarm(1.0, 0.0, &amaron_command("say Test? Did I tell you " +
            "about the test yet? I don't think I did."));
        return 1;
    }

    /* Let's reset the prop now. */
    tp->remove_prop(RANGER_I_RECEIVED_INSTRUCTION);

    /* Remove all the questions from the already asked list. */
    refresh_questions();

    /* Get a question */
    question_id = random_question();

    /* Add tried, remove if the recruit passes the test. */
/*
    if (!query_tried(name))
*/
    if (member_array(name, m_indexes(gTried)) == -1)
        gTried += ([ name : time() + TWO_DAYS + random(28800) ]); /* radom is the 8 hrs missing in def */
    else
        gTried[name] = time() + THREE_DAYS*2;

    save_object(MASTER);

    /* Keep track of the question they were given. */
    tp->add_prop(RANGER_S_QUESTION_ID, question_id);

    set_alarm(0.5, 0.0, &amaron_command("say Excellent! Here is your " +
        "first question."));

    /* Don't let others in the room see it. */
    set_alarm(1.7, 0.0, &tell_question(question_id, tp));

    /* Set the timer. The player has ten minutes from when Amaron
       gives the question to answer it. */
    gAlarm = set_alarm(600.0, 0.0, &question_time_out(tp));
    gQuestor = tp;

    return 1;
}

/* Function name: tell_question
 * Description  : Tells a question to a player without others seeing it.
 * Arguments    : string question_id - the question identifier,
 *                object who - the player to tell the question to
 */
public void
tell_question(string question_id, object who)
{
    say(QCTNAME(gRecruiter) + " whispers something to " +
        QTNAME(who) + ".\n");
    who->catch_tell(gQuestions[question_id] + "\nEnter " +
        "'answer <your answer>' to answer the question.\n");
}

/* Function name: random_question
 * Description  : Get a random question to ask
 * Returns      : string - the question identifier
 */
public string
random_question()
{
    string pick, *questions = m_indexes(gQuestions);

    /* No questions have been added! */
    if (!sizeof(questions))
        return "";

    /* All the questions have been asked, we must refresh it. */
    if (sizeof(questions) == sizeof(gAskedQuestions))
        refresh_questions();

    /* Choose a question */
    pick = one_of_list(questions);

    /* Let's make sure this question isn't on the already asked list. */
    while (member_array(pick, gAskedQuestions) != -1)
        pick = one_of_list(questions);

    /* Add this question to the already picked list. */
    gAskedQuestions += ({ pick });

    return pick;
}

/* Function name: answer_question
 * Description  : Allows a player to answer the current question
 * Arguments    : string answer - as entered by the player
 * Returns      : 1 if successful, 0 if not
 */
public int
answer_question(string answer)
{
    string new_question, name;
    object tp = this_player();

    name = capitalize(this_player()->query_real_name());

    if (!this_player()->query_prop(RANGER_S_QUESTION_ID))
    {
        amaron_command("I have not given you a question.");
        return 1;
    }

    if (!strlen(answer))
    {
        notify_fail("What did you want to answer?\n");
        return 0;
    }

    answer = lower_case(answer);

    // log both question and answer
    MANAGER->rlog(APPRENTICE_LOG, capitalize(tp->query_real_name()) +
        " was asked the following question: \n" + 
        gQuestions[tp->query_prop(RANGER_S_QUESTION_ID)] +
        "\n" + capitalize(tp->query_possessive()) + " answer " +
         "was: " + answer + ".");

    if (strlen(tp->query_prop(RANGER_S_QUESTION_ID)) &&
      check_right_answer(
      tp->query_prop(RANGER_S_QUESTION_ID), answer))
    {
        if (tp->query_prop(RANGER_I_ANSWERED_NUM) < 2)
        {
            remove_alarm(gAlarm); 

            gAlarm = set_alarm(600.0, 0.0, &question_time_out(tp));

            tp->add_prop(RANGER_I_ANSWERED_NUM, 
                tp->query_prop(RANGER_I_ANSWERED_NUM) + 1);
            new_question = random_question();
            tp->add_prop(RANGER_S_QUESTION_ID, new_question);
            amaron_command("say Correct! Your next question is this.");
            tell_question(new_question, tp);
            return 1;
        }
        else
        {
            /* Clear the props added. */
            tp->remove_prop(RANGER_I_ANSWERED_NUM);
            tp->remove_prop(RANGER_S_QUESTION_ID);

            /* Remove the alarm so others can take the test. */
            reset_questor();
            
            /* Allow player to join the guild now! */
            amaron_command("say Congratulations! You have proved yourself " +
                "worthy to become an Apprentice Ranger! You may sign the " +
                "book now.");
            MANAGER->rlog(APPRENTICE_LOG, 
                capitalize(tp->query_real_name()) +
                " passed Amaron's test!");

            /* Track that the player may join before armageddon. */
            tp->add_prop(RANGER_I_CAN_JOIN, 1);
            gPassedTest += ({ name });
            save_object(MASTER);

            /* Remove them from the tried list. */
            remove_tried(name);
            save_object(MASTER);
            return 1;
        }

    }
    else if (strlen(tp->query_prop(RANGER_S_QUESTION_ID)))
    {
        MANAGER->rlog(APPRENTICE_LOG, capitalize(tp->query_real_name()) +
            "'s answer: " + answer + ", was incorrect. " + 
            capitalize(tp->query_real_name()) + " must wait until " +
            ctime(gTried[name]) + " to try again.");

       tp->remove_prop(RANGER_I_ANSWERED_NUM);
       tp->remove_prop(RANGER_S_QUESTION_ID);
       reset_questor();
       amaron_command("say I'm sorry, that's incorrect. You may try " +
           "again after " + ctime(gTried[name]) + ". I suggest " +
           "you study your history.");
       return 1;
    }
    else
    {
        /* Someone is trying to answer who hasn't been given the test. */
        amaron_command("stare annoyed " + OB_NUM(this_player()));
        amaron_command("say to " + OB_NUM(this_player()) + " Please " +
            "wait your turn, and do not provide any help.");
        return 1;
    }

}

/* Function name: check_right_answer
 * Description  : Is this an accepted answer to the question?
 * Arguments    : string name - the question identifier
 *                string answer - the proposed answer
 * Returns      : 1 if successful, 0 if not
 */
public int
check_right_answer(string name, string answer)
{
    if (!strlen(answer) || !strlen(name))
        return 0;

    if (!query_question(name))
        return 0;

    if (member_array(answer, gAnswers[name]) == -1)
        return 0;

    return 1;
}

/* Function name: refresh_questions
 * Description  : restores the list of questions available.
 */
public void
refresh_questions()
{
    gAskedQuestions = ({});
    return;
}


/* Function name: question_time_out
 * Description  : Took too long to answer the question.
 * Arguments    : object player - the player to time out
 */
public void
question_time_out(object player)
{

    string quest = player->query_prop(RANGER_S_QUESTION_ID);

    amaron_command("say I'm sorry, you've taken too long to answer. " +
        "You may try again after " + 
        ctime(query_tried(player->query_real_name())) + ".");
    MANAGER->rlog(APPRENTICE_LOG, capitalize(player->query_real_name()) +
        " was asked the following question: \n" + 
        gQuestions[quest] +
         "\n" + capitalize(player->query_pronoun()) + " did not answer " +
        "in time and must wait until " + 
        ctime(query_tried(player->query_real_name())) + " to try again.");
     reset_questor();
    player->remove_prop(RANGER_S_QUESTION_ID);
    return;
}

/* Function name: vouch
 * Description  : Full ranger must vouch for player for Amaron's
 *                acceptance as an apprentice. Voucher is full ranger,
 *                'vouchee' is the wannabe applicant
 * Arguments    : string: syntax <vouch for name>
 * Returns      : 1/0
 */
public int
vouch(string str)
{
    object voucher = this_player();
    object vouchee;
    string vouchee_name, voucher_name;
    
    
    if (!present("amaron"))
    {
        notify_fail("Amaron must be present to witness " +
            "the voucher.\n");
        return 0;
    }

    //test for voucher
    if (!RANGERS_FULL_MEMBER(voucher))
    {
        notify_fail("You must be a full ranger to vouch for an " +
            "apprentice candidate.\n");
        return 0;
    }
    //tests for vouchee
    if (!strlen(str))
    {
        notify_fail("Vouch for whom?\n");
        return 0;
    }

    if (!parse_command(str, ({}), " [for] %s ", vouchee_name))
    {
        notify_fail("Vouch for whom?\n");
        return 0;
    }

    if (strlen(query_voucher(vouchee_name)))
    {
        notify_fail(capitalize(vouchee_name) + " has already " +
            "been vouched for.\n");
        return 0;
    }

    if (!strlen(vouchee_name))
    {
        notify_fail("Vouch for whom?\n");
        return 0;
    }

    vouchee = present(vouchee_name, this_object());
    if (objectp(vouchee) && !interactive(vouchee))
    {
        notify_fail("You can only vouch for players!\n");
        return 0;
    }
    if (!objectp(vouchee))
    {
        notify_fail("You must know the applicant well for whom " +
            "you vouch before Amaron, and the applicant " +
            "must be present with you for Amaron to " +
            "evaluate him/her.\n");
        return 0;
    }

    voucher_name = capitalize(voucher->query_real_name());
    //verify that vouchee is eligible to take test

    if (check_not_eligible(vouchee))
    {
        notify_fail(capitalize(vouchee_name) + " is not " +
           "eligible to join the rangers at this time.\n");
        return 0;
    }

    //successful -- add mapping to gVouchers
    if (!add_voucher(vouchee_name, voucher_name))
    {
        notify_fail("You are unable to vouch for " +
            capitalize(vouchee_name) + " for some reason.\n");
        return 0;
    }

    MANAGER->rlog(APPRENTICE_LOG, capitalize(voucher_name) + 
        " vouched for " + capitalize(vouchee_name) + " before " +
        "Amaron, to allow " + vouchee->query_objective() +
        " to take the test for entrance.");
    MANAGER->rlog(RANGERS_LOG, capitalize(voucher_name) + 
        " vouched for " + capitalize(vouchee_name) + " before " +
        "Amaron, to allow " + vouchee->query_objective() +
        " to take the test for entrance.");
    amaron_command("emote writes something in his notebook.");
    write(capitalize(vouchee_name) + " has been added to " +
        "the list of vouched-for applicants.\n");
    return 1;
}

/* Function name: unvouch
 * Description  : Rangers decides to remove voucher for wannabe
 * Arguments    : string: syntax <unvouch [for] name>
 * Returns      : 1/0
 */
unvouch(string vouchee)
{ 
    string name;
    object tp = this_player();
    string voucher_name = capitalize(tp->query_real_name());


    if (!strlen(vouchee))
    {
        notify_fail("Unvouch for whom?\n");
        return 0;
    }
    if (!parse_command(vouchee, ({}), " [for] %s ", name))
    {
        notify_fail("Unvouch for whom?\n");
        return 0;
    }

    if (!strlen(name))
    {
        notify_fail("Unvouch for whom?\n");
        return 0;
    }
    if (!strlen(query_voucher(name)))
    {
        notify_fail("There is no voucher listed for " +
            name + ".\n");
        return 0;
    }
    name = capitalize(name);

    if (voucher_name != gVouchers[name] &&
        !IS_GONDOR_WIZARD(tp))
    {
        notify_fail("Only the ranger who vouched for " +
            "the applicant can remove his/her voucher.\n");
        return 0;
    }

    if (!remove_voucher(name))
    {    
        notify_fail("You were unable to remove the voucher " +
            "for some reason.\n");
        return 0;
    }
    MANAGER->rlog(APPRENTICE_LOG, capitalize(voucher_name) + 
        " removed the voucher for " + capitalize(name) + 
        " before Amaron.");
    MANAGER->rlog(RANGERS_LOG, capitalize(voucher_name) + 
        " removed the voucher for " + capitalize(name) + 
        " before Amaron.");
    amaron_command("emote writes something in his notebook.");
    write("You removed the ranger voucher for " + name + ".\n");
    return 1;

}
/* Function name: add_voucher
 * Description  : adds a couplet of [vouchee:voucher]
 *                to the voucher mapping
 * Arguments    : string vouchee (ranger wannabe),
 *                string voucher (full ranger who is
 *                making the voucher)
 * Returns      : 1/0
 */
public int 
add_voucher(string vouchee, string voucher)
{
    string vouchee_name, voucher_name;

    if (!strlen(vouchee) || !strlen(voucher))
    {
        return 0;
    }
    vouchee_name = capitalize(vouchee);
    voucher_name = capitalize(voucher);
    gVouchers += ([ vouchee_name : voucher_name ]);
    save_object(MASTER);
    return 1;
}

/* Function name: remove_voucher
 * Description  : Remove a voucher for a wannabe
 * Arguments    : string: syntax <remove name (of wannabe)>
 * Returns      : 1/0
 */
public int
remove_voucher(string vouchee)
{
    string name;

    if (!strlen(vouchee))
        return 0;

    name = capitalize(vouchee);
    if (member_array(name, m_indexes(gVouchers)) == -1)
    {
        return 0;
    }

    gVouchers = m_delete(gVouchers, name);
    save_object(MASTER);
    return 1;
}

/* Function name: query_voucher
 * Description  : Returns the ranger's name who vouched for
 *                wannabe
 * Arguments    : name of wannabe
 * Returns      : name of voucher if exists, else empty string
 */
public string    
query_voucher(string name)
{
    string vouchee;
    vouchee = capitalize(name);
    if (member_array(vouchee, m_indexes(gVouchers)) == -1)
    {
        return "";
    }
    return gVouchers[vouchee];
}

/*************ADD NEW QUESTION CODE STARTS HERE***************/

/* Function name: get_name
 * Description  : Get the question name, the identifier, from the
 *                submitter.
 * Arguments    : string name - the argument entered by the player
 * Returns      : 1 if successful, 0 if not
 */
public int
get_name(string name)
{
    if (!strlen(name))
    {
        notify_fail("Which question do you want to add?\n");
        return 0;
    }

    if (!this_player()->query_wiz_level() ||
      SECURITY->query_wiz_dom(this_player()->query_real_name()) != "Gondor")
    {
        notify_fail("You aren't allowed to add questions. You may " +
            "submit them here though.\n");
        return 0;
    }

    if (query_question(name))
    {
        notify_fail("There is already a question with that name.\n");
        return 0;
    }


    write("Enter the question. Hit return when done or ~q to quit.\n");
    input_to(&get_question(, name));
    return 1;
}

/* Function name: get_question
 * Description  : Gets the question text from the submitter.
 * Arguments    : string question - the question text
 *                string name - the question identifier
 */
public void
get_question(string question, string name)
{
    if (!strlen(question))
    {
        write("No question entered. Enter the question again. Hit " +
            "return when done or ~q to quit.\n");
        input_to(&get_question(, name));
        return;
    }

    if (question == "~q")
    {
        write("You change your mind.\n");
        return;
    }

    write("Enter the possible answers to the question. You may enter " +
        "more than one by separating them with commas. Hit enter when " +
        "done or ~q to quit.\n");
    input_to(&get_answers(, question, name));
    return;
}

/* Function name: get_answers
 * Description  : Get all possible answers for a question from submitter.
 * Arguments    : string answers - a string of answers separated by commas
 *                string question - the question text
 *                string name - the question identifier
 */
public void
get_answers(string answers, string question, string name)
{
    if (!strlen(answers))
    {
        write("You must provide at least one answer. Enter the " +
            "possible answers to the question. You may enter more " +
            "than one by separating them with commas. Hit enter when " +
            "done or ~q to quit.\n");
        input_to(&get_answers(, question, name));
        return;
    }

    if (answers == "~q")
    {
        write("You change your mind.\n");
        return;
    }

    write("You add the question " + name + " with the content:\n" +
        question + "\n and answers: " + answers + ".\n");
    
    add_question(answers, question, name);
    return;
}

/* Function name: add_question
 * Description  : Add the question to the mappings and save_object.
 * Arguments    : string answers - a string of answers separated by a comma
 *                string question - the text of the question
 *                string name - the question identifier
 */
public void
add_question(string answers, string question, string name)
{
    int i, size;
    string *answer_array;

    if (!strlen(answers) || !strlen(question) || !strlen(name))
        return;

    answer_array = explode(answers, ",");

    for (i = 0, size = sizeof(answer_array); i < size; i++)
    {
        if (extract(answer_array[i], 0, 0) == " ")
            answer_array[i] = answer_array[i][1..strlen(answer_array[i])];
        if (extract(answer_array[i], -1) == " ")
            answer_array[i] = answer_array[i][0..strlen(answer_array[i])-1];

        answer_array[i] = lower_case(answer_array[i]);
    }

    name = lower_case(name);
    gQuestions += ([ name : question ]);
    gAnswers += ([ name : answer_array ]);
    save_object(MASTER);
    return;
}

/* Function name: remove_question
 * Description  : Remove a question by its identifier.
 * Arguments    : string name - the question identifier
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_question(string name)
{
    if (!strlen(name))
    {
        notify_fail("Which question do you want to remove?\n");
        return 0;
    }

    if (!this_player()->query_wiz_level() ||
      SECURITY->query_wiz_dom(this_player()->query_real_name()) != "Gondor")
    {
        notify_fail("You aren't allowed to remove questions.\n");
        return 0;
    }

    name = lower_case(name);

    if (!query_question(name))
    {
        notify_fail("There is no such question called " + name + ".\n");
        return 0;
    }

    gQuestions = m_delete(gQuestions, name);
    gAnswers = m_delete(gAnswers, name);
    save_object(MASTER);
    return 1;
}

/* Function name: query_question
 * Description  : Is this question already on the list?
 * Arguments    : string name - the question identifier
 * Returns      : 1 if successful, 0 if not
 */
public int
query_question(string name)
{
    if (!strlen(name))
        return 0;

    name = lower_case(name);

    if (member_array(name, m_indexes(gQuestions)) != -1)
        return 1;
}

/* Function name: submit_question
 * Description  : Allows an officer to submit a question for
 *                consideration by the GM, Lord and Steward of Gondor
 * Arguments    : string str - the text to submit
 * Returns      : 1 if successful, 0 if not
 */
public int
submit_question(string str)
{
    if (!MANAGER->query_is_council(this_player()->query_real_name()))
    {
        notify_fail("Only officers may submit a question.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("What did you want to submit? Be sure to submit " +
            "the question and the answers.\n");
        return 0;
    }

    write("Are you sure you wish to submit the following question and " +
        "answers?\n" + str + "\nYes, no or ~q to quit? ");
    input_to(&do_submit(, str));
    return 1;
}

/* Function name: do_submit
 * Description  : Does the actual submission
 * Arguments    : string yes_no - Should be yes or no
 *                string question - the question and answers to submit
 */
public void
do_submit(string yes_no, string question)
{
    yes_no = lower_case(yes_no);
    if (yes_no == "yes" || yes_no == "y")
    {
        write("You submit your question and answers. Your question will " +
            "be reviewed for suitability.\n");

        MANAGER->rlog(RANGERS_WIZ_LOG, 
            capitalize(this_player()->query_real_name()) +
            " submitted the following:\n" + question);
        return;
    }

    write("You decide not to submit after all.\n");
    return;
}

/*************ADD NEW QUESTION CODE ENDS HERE***************/

/* Function name: wiz_bypass
 * Description  : Allows a wizard to approve a player for joining the
 *                Rangers without them having to answer the questions
 *                or wait any period of time. It only adds a prop, though,
 *                so the player must sign the book during that reboot.
 * Arguments    : string name - the player to allow
 * Returns      : 1/0 - success/failure
 */
public int
wiz_bypass(string name)
{
    object who;

    if (SECURITY->query_wiz_dom(this_player()->query_real_name()) != "Gondor" &&
      SECURITY->query_wiz_rank(name) <= WIZ_LORD)
        return 0;

    if (!strlen(name))
    {
        notify_fail("Allow who?\n");
        return 0;
    }

    who = find_player(lower_case(name));

    if (!objectp(who))
    {
        notify_fail("There is no " + capitalize(name) + " logged in.\n");
        return 0;
    }

    who->add_prop(RANGER_I_CAN_JOIN, 1);
    MANAGER->remove_no_rejoin(name);
    write("You allow " + capitalize(name) + " to join the Rangers by " +
        "just signing the book.\n");
    who->catch_tell("You have been allowed to join the Rangers by " +
        "signing the book. Please do so before Armageddon.\n");
    MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(name) + " allowed to join " +
        "by " + capitalize(this_player()->query_real_name()));
    return 1;
}

/* Function name: init
 * Description  : Add actions to the player.
 */
public void
init()
{
    ::init();

    add_action(&join_rangers(),    "sign");
    add_action(&leave_rangers(),   "erase");
    add_action(&read_chapter(),    "read");
    add_action(&get_name(),        "add");
    add_action(&submit_question(), "submit");
    add_action(&answer_question(), "answer");
    add_action(&take_test(),       "take");
    add_action(&start_question(),  "start");
    add_action(&wiz_bypass(),      "allow");
    add_action(&vouch(),           "vouch");
    add_action(&unvouch(),         "unvouch");
}
