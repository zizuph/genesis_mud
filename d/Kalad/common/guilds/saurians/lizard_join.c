/*
 * Join room of the Lizard guild
 * Based on the Halfling guild of Faerun
 * Mirandus - February 2018
 */
#pragma save_binary
#pragma strict_types

#include "lizards.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>
#include <terrain.h>

inherit GUILD_ROOMS;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#define DLY_PLAYER(t, s) set_alarm(t, 0.0, &write( s ))
#define DLY_TELLR(t, s) set_alarm(t, 0.0, &say( s ))

/*
 * Global variables.
 *
 * The mapping members has the names of the players as indices and the
 * values are an array with two elements, the family name of the player
 * and the date the player joined.
 */
private mapping members;
//   Prototypes
void remove_from_list(string player);

void reset_room()
{
    ::reset_room;
}

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
 void
 set_up_skills()
 {
     create_skill_raise();

     sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 50);
     sk_add_train(SS_BLIND_COMBAT, "fight while blind",
       "blindfighting", 0, 50);
     sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy"
     , 0, 50);
     sk_add_train(SS_LOC_SENSE, "find your way underground", "location sense",
      0, 50);
     sk_add_train(SS_AWARENESS, "be aware of your surroundings", "awareness", 
     0, 60);
     sk_add_train(SS_UNARM_COMBAT, "fight with with claws", "claws", 0, 50);
     sk_add_train(SS_ACROBAT, "dodge blows with lizard like dexterity", "acrobat"
    , 0, 60)
     sk_add_train(SS_GUILD_SPECIAL_SKILL, "disembowel with your claws",
       "disembowel", 80, 100);
    sk_add_train(SS_CLIMB, "climb up rocks quickly","climb", 0, 50);
    sk_add_train(SS_HUNTING, "seek out your prey","hunting", 0, 50);
 }

/*
 * Function name: sk_improve
 * Description:   Required so you can actually learn/improve the skills.
 */
public int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;
    if (!sk || sscanf(sk, "%d", steps))
    {
	    if (!TP->query_guild_member(GUILD_NAME_RACE))
	    {
    	    write("Only Saurians may train here.\n");
	        return 1;
        }
    return sk_list(steps);
    }
    
    tmp = explode(sk, " ");
    if(sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
    skill = implode(tmp[0 .. sizeof(tmp) -2], " ");
    else
    {
	skill = sk;
	steps = 1;
    }

    return ::sk_improve(sk);
}

/*
 * Function name: create_std_lizard()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_std_lizard()
{
    setuid();
    seteuid(getuid());

    set_short("An ancient chamber");
    set_long("This ancient chamber is located deep within the underground " +
        "of Kalad. The space itself feels as though it has existed since " +
        "before time was measurable. There is a sense of awe and desire " +
        "here. Desire to return to base instincts and to let the ancient " +
        "part of your brain let loose. There are words carved into the wall " +
        "of the cavern.\n");

    add_item("wall", "You might be able to read the words here.\n");
    add_cmd_item("words", ({"read", "examine", "exa"}), "@@read_words@@");
    add_exit(LIZGUILD + "testroom", "east");
    
    add_prop(ROOM_I_NO_ATTACK, "Something within you prevents such an "
    +"attack within this place.\n");

    restore_object(GUILD_SAVE);
    if (!mappingp(members))
    {
        members = ([ ]);
    }

    set_up_skills();
    reset_room();
    
}

/*
 * Function name: init()
 * Description  : Initializes the commands for the room.
 */
void 
init()
{
    ::init();

    add_action("do_try",   "invoke");
    add_action("do_break", "forsake");
    add_action("request",  "request");
    add_action("s_history", "shistory");
    init_skill_raise();
    //add_action("action_continue", "continue");
    //add_action("action_stop", "stop");

}

/*
 * Function name: read_words()
 * Description  : The return for reading the sign/words in the room.
 */
string 
read_words()
{
    return "\n"+                 
"  +-------------+ |-----------------------------------| +-------------+\n" +
"  | +-------------+-----------------------------------+-------------+ |\n" +
"  | |                                                               | |\n" +
"  | |                                                               | |\n" +
"  | |    This place is sacred to us. The Saurian Race of Kalad.     | |\n" +
"  | |                                                               | |\n" +
"  | |    It is here that we are born. That we die. That we learn.   | |\n" +
"  | |                                                               | |\n" +
"  | |    It is here that we were once legion but now are broken.    | |\n" +
"  | |                                                               | |\n" +
"  | |    We are the most ancient race. We've lived since time       | |\n" +
"  | |    began. We are the base instincts of fight or flight.       | |\n" +
"  | |    We have been, we are, and we will forever be.              | |\n" +
"  | |                                                               | |\n" +
"  | |    If you decide to become a Saurian, you must:               | |\n" +
"  | |       <invoke ancestry>                                       | |\n" +
"  | |                                                               | |\n" +
"  | |    Know that to become a Saurian you must not only be bound   | |\n" +
"  | |    by race, but by your layman as well.                       | |\n" +
"  | |                                                               | |\n" +
"  | |    Should there come a time when you no longer want to be     | |\n" +
"  | |    a Saurian, you will need to need to return here and:       | |\n" +
"  | |       <forsake bonds>                                         | |\n" +
"  | |                                                               | |\n" +
"  | |    If you lose your guild item, it can be replaced by:        | |\n" +
"  | |       <request necklace>                                      | |\n" +
"  | |                                                               | |\n" +
"  | |    Should you wish to learn more of us, you can use           | |\n" +
"  | |      <shistory> to hear our story.                            | |\n" +
"  | |                                                               | |\n" +
"  | +---------------------------------------------------------------+ |\n" +
"  +-------------------------------------------------------------------+\n\n";


}

/*
 * Function name: query_is_member()
 * Description  : Checks to see if the player is a member
 * Arguments    : string - The players name
 *                Returns 1 if a member, 0 if not.
 */
public int
query_is_member(string name)
{
    if(members[name])
    {
        return 1;
    }

    return 0;
}

/*
 * Function name: check_member()
 * Description  : Checks to see if the player is a member
 * Arguments    : Returns 1 if a member, 0 if not.
 */
int
check_member()
{
    object tp = this_player();

    if((!tp->query_wiz_level()) && (!IS_MEMBER_RACE(tp)))
    {
        write("You do not feel you can pass.\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: log_guild()
 * Description  : Adds events to the guild log.
 * Arguments    : string - The text to be added to the log.
 */
nomask private void
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(GUILD_LOG + "lizard_guild") > LOG_SIZE)
    {
        rename(GUILD_LOG + "lizard_guild", (GUILD_LOG + "lizard_guild.old"));
    }

    write_file(GUILD_LOG + "lizard_guild", text);
}

/*
* Function name: do_try
* Description  : When one wants to join the guild, this function
*                makes them a member.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_try(string str)
{
    object tp = this_player();
    object race_shadow, lay_shadow;
    object paralyze_object;
    int    result;

    if (!strlen(str) || str != "ancestry")
    {
        notify_fail("If you seek to reclaim your ancient ancestry, you "
        +"would be wise to <invoke ancestry>\n");
        return 0;
    }

    if(tp->query_race() != "human" && -1 == member_array(tp->query_race_name()
        , VALID_SUBRACES) )
    {
        write("I am sorry but " + tp->query_race() + " are not welcome to " +
            "become a Saurian of Kalad.\n");
        return 1;
    }

    // check if player is a member already
    if (IS_MEMBER_RACE(tp))
    {
        write("You are already a Saurian.\n");
        return 1;
    }
    // check if player is a member already - In case something bugged bad
    // and they are a member of the layman, but not race...
    if (IS_MEMBER_LAY(tp))
    {
        write("You are already a Saurian.\n");
        return 1;
    }

    // Racial slot needs to be free.
    if (tp->query_guild_member(GUILD_TYPE_RACE))
    {
        write("You cannot be a member of two racial guilds at a time.\n");
        return 1;
    }

    // So does the Layman slot.
    if (tp->query_guild_member(GUILD_TYPE_LAY))
    {
        write("You cannot be a member of two layman guilds at a time.\n");
        return 1;
    }

    //Clone the shadows - Most guild stuff is in Layman Shadow.
    race_shadow = clone_object(GUILD_SHADOW_RACE);
    lay_shadow = clone_object(GUILD_SHADOW_LAY);

    // Make sure the shadows apply properly.
    if ((result = race_shadow->shadow_me(tp, GUILD_TYPE_RACE, 
        GUILD_STYLE_RACE, GUILD_NAME_RACE)) != 1)
    {
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) +
            " failed to add shadow with result " + result + ".\n");
        race_shadow->remove_shadow();
        write("The Anointed one has not heard your prayers. Please leave a " +
            "bug report in this room.\n");
    return 1;
    }

    if ((result = lay_shadow->add_lay_shadow(this_player())) != 1)
    {
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) +
            " failed to add shadow with result " + result + ".\n");
        lay_shadow->remove_shadow();
        write("The Anointed one has not heard your prayers. Please leave a " +
            "bug report in this room.\n");
    return 1;
    }

    //initialize the player.
    set_alarm(3.0,0.0,"init_me",tp);

    // logs the join
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " joined the " +
        GUILD_NAME_LAY + ".\n");

    // creates the guild item
    clone_object(GUILD_ITEM)->move(tp, 1);

    // joining movie
    if (!present("_saurian_join_paralyze_object_", tp))
    {
       paralyze_object = clone_object(LIZGUILD + "saurian_paralyze_object");
       paralyze_object->move(tp, 1);
       set_alarm(12.5,0.0,&paralyze_object->remove_object());
        
    DLY_PLAYER(2.0,"As the words pass your lips you feel an excruciating "
    + "pain wash over you.\n\n\nYou drop to your knees as your bones break "
    + "and reform.\n\n");
    DLY_PLAYER(8.0,"As the pain blurs your eyes you see someone approach "
    + "and place a necklace over your head.\n\n\nThey say: 'These teeth "
    + "represent those who came before us. Those who led the way.'\n\n\n");
    DLY_PLAYER(12.5,"You are only dimly aware of the changes that happen "
    +"to you. Your skin begins to change colour and become scaled, your "
    +"blood grows cold within your veins.\n\n\nYour hands grow into claws, "
    +"your teeth extend and you face changes shape.\n\n\nYour tongue is "
    +"ripped in half and your nose inverts. Just as you feel you can take "
    +"no more, the pain subsides.\n\nYou arise. Altogether different.\n\n");

    DLY_TELLR(2.0,QTNAME(tp) + " drops to the ground in excruciating pain! "
    +"A Saurian approaches and presents a tooth necklace to "+QTNAME(tp)+
    ".\n\n");
    DLY_TELLR(8.0,QTNAME(tp) + " transforms before your eyes into a beast "
    +"of ancient proportions. Writhing on the floor in pain "+QTNAME(tp)+
    " is broken before being built again into something altogether "
    +"different.\n\n");
    DLY_TELLR(12.5,QTNAME(tp) + " ceases to exist in their original form. "
    +"They've become something truly ancient. Clawed, scaled, and "
    +"cold-blooded "+ QTNAME(tp) + " has become a thing of nightmares.\n\n");
    }

    //Clear the stats and appl the racial ones. Layman applied in Shadow.
    tp->clear_guild_stat(SS_RACE);
    tp->set_guild_pref(SS_RACE, GUILD_TAX_RACE);
    
        
    // changes descr to a lizard.
    //tp->set_race_name("saurian");
    //tp->add_prop(LIVE_I_SEE_DARK,1);
    

    members[tp->query_real_name()] = ({tp->query_age(), time() });
    save_object(GUILD_SAVE);

    return 1;
}


int 
init_me(object ob)
{
    ob->init_race_shadow();
    ob->init_lay_shadow();
    return 1;
}

/*
* Function name: lower_skill
* Description  : When a member leaves the guild or is kicked out due
*                to a change of race, this function punishes him/her,
*                removes the soul, shadow, etcetera.
* Arguments    : object tp - the object leaving.
*/
nomask private void
lower_skill(object tp)
{
    object necklace;
    
    //Reset the player when they leave.
    tp->set_guild_pref(SS_RACE, 0);
    tp->clear_guild_stat(SS_RACE);
    tp->remove_lay_member();
    tp->setup_skill_decay();

   /* If the player starts in the guild by default, set this to
    * the default starting location for all players.
    */
    if (tp->query_default_start_location() == START)
    {
        tp->set_default_start_location(tp->query_def_start());
    }

    //Remove the necklace
    necklace = present(MEDALLION_NAME, tp);
    necklace->remove_object();

    /* Remove him/her from the list of members. */
    remove_from_list(tp->query_real_name());
}

void 
remove_from_list(string player)
{
    player = lower_case(player);
    members = m_delete(members,player);
    setuid(); seteuid(getuid());
    save_object(GUILD_SAVE);
}

/*
 * Function name: do_break
 * Description  : This is a waste of memory since no-one would ever
 *                consider leaving a guild like this, or would they?
 *                Just for the completeness, this function takes care
 *                of a voluntary leave.
 * Arguments    : string str - the command line argument
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_break(string str)
{
    object tp = this_player();
    object necklace;
    int    result;

    if (str != lower_case("bonds"))
    {
        notify_fail("Do you want to leave the Saurians? You must " +
            "<forsake bonds>.\n");
        return 0;
    }

    if (!IS_MEMBER_LAY(tp))
    {
        write("You cannot leave the " + GUILD_NAME_LAY + ". You were never " +
            "a member of the guild.\n");
        return 1;
    }

    if ((result = tp->remove_guild_race()) != 1)
    {
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) +
            " failed to remove shadow with result " + result + ".\n");

        write("You are unable leave the " + GUILD_NAME_RACE + ". Please leave a " +
            "bug report in this room about this. Thanks.\n");
        return 1;
    }

    necklace = present(GUILD_ITEM_ID, tp);
    necklace->remove_object();
    write("You are struck, violently, by a scaled fist. When you awaken "
    +"You have returned to your original form.\n");

    say("Is struck, violently, by a Saurian fist. Before your eyes the " +
        "transformation occurs and " + QTNAME(TP) + " returns to their " +
        "original form.\n");

    lower_skill(tp);
    tp->set_race_name(tp->query_race());

    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " left the " +
        GUILD_NAME_LAY + ".\n");
    return 1;
}

/*
 * Function name: request
 * Description  : Members who have lost their guild item, get it back here.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0    - success/failure.
 */
nomask static int 
request(string str)
{
    object tp = this_player();

    if (str != "necklace")
    {
        notify_fail("Request what? A new necklace?\n");
        return 0;
    }

    if (!IS_MEMBER_RACE(tp))
    {
        write("You are not a member of the " + GUILD_NAME_RACE + ".\n");
        return 1;
    }

    if (objectp(present(MEDALLION_NAME, tp)))
    {
        write("You already have a necklace. You don't need two.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(GUILD_ITEM)->move(tp, 1);

    write("A Saurian approaches and hands you a new necklace. You reach out "
    +"and take it.\n");
    say(QCTNAME(tp)  + " is presented with a new necklace.\n");
    return 1;
}

/*
 * Function name: remove_player_changed_race
 * Description  : Whenever a member changes his/her race (s)he is
 *                mercilessly kicked out the guild by this function.
 * Arguments    : object tp - the object to kick out.
 */
nomask public void
remove_player_changed_race(object tp)
{
    tp->catch_msg("\nYou are no longer suitable. You cannot claim " +
        "yourself a member of the " + GUILD_NAME_RACE + " anymore. You are " +
        "expelled from the guild.\n");

    lower_skill(tp);
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " (race " +
        tp->query_race_name() + ") was kicked out.\n");
}

int
block_room()
{
    if (this_player()->query_wiz_level()) 
    {
        write("\n\nYou enter an area that is not open to mortals.\n\n\n");
        return 0;
    }
    
    write("You cannot enter.\n");
    return 1;
}

/*
 * Function name: s_history()
 * Description  : Presents the history of the Saurian race.
 * Arguments    : None.
 */
 
int
s_history(string history)
{
    switch(history)
    {
    case "final":
    case "Final":
    write("They believe that they are the chosen of their 'god'? They "
    + "will see what it means to be a Saurian. We will not stand idle as they "
    + "push us so hard. We will band together, draw on the power of our "
    + "ancient ancestry and push back.\n");
    return 1;
    break;

    case "present":
    case "Present":
    write("While we developed this culture and community the other races" 
    + "arrived within Kalad. The Dark-Elves, goblins, and worst of amongst "
    + "them, the Humans. Humans began as a fledgling race that was almost "
    + "eradicated from the lands of Kalad. They were able, with support "
    + "from the more developed races, to survive and begin to flourish. "
    + "They proved to be the most ingenious amongst us at warfare and "
    + "destruction. They began to ravage the lands of Kalad for their own "
    + "benefit and to push all other races to the fringes. They developed "
    + "religion that put them above all else. They used this, their 'god' to "
    + "justify the horrors they carried out on other races.\n\nWe were "
    + "pushed, pushed back to where we were born, underground. Here we "
    + "have continued to thrive, as we knew we would. Our hatred for the "
    + "stupidity of the human race has grown and we now stand in direct "
    + "defiance to their utter ignorance.\n\n");
    return 1;
    break;
    
    case "society":
    case "Society":
    write("We descended from various tribes of Saurians. Not tribes in "
    + "the sense that we were separate. Tribes in the way we divided our "
    + "tasks, exploration, and passage of knowledge and the way that things "
    + "got done. We all learn every aspect of Saurian society, but some of "
    + "us descended from those who did so better. As a Saurian you can select "
    + "a Tribal name to identify from whom you descend:\n\n\n"
    + "             Ku'Tathar   - Those who lead us into battle.\n"
    + "             Im'Kazath   - Those who teach our young.\n"
    + "             Ek'Trabal   - Those who pass on our stories.\n"
    + "             Zin'Katar   - Those who teach us to hunt.\n"
    + "             Em'Bratal   - Those who guide our scouts.\n"
    + "             Ath'Takath  - Those who develop our technologies.\n"
    + "             Ik'Bizan    - Those who tend to the hurt and sick.\n"
    + "             Ef'Kamal    - Those who travel to gather knowledge.\n"
    + "             En'Biktal   - Those who see what others cannot.\n"
    + "             Al'Azar     - Those amongst us who knew magic.\n"
    + "             Mith'Kiltar - Those whose name brought fear to enemies.\n"
    + "             Baz'Zin     - Those who prepared us for battle.\n"
    + "             Es'Tik      - Those who knew what others could not.\n"
    + "             Ba'Lia      - Those who led us with wisdom.\n\n");
    return 1;
    break;


    case "history2":
    case "History2":
    write("We eventually learned to fashion tools from the rock around us "
    + "and used these to grow stronger. The puzzle helped our intellect "
    + "grow and we were able evolve into more than the lizards we were.\n\n"
    + "Over the eons before the other races joined us upon this earth. We "
    + "rose up onto our two feet, we developed our tools, we began to form a "
    + "community with customs, lore, shamans, and a past that we shared.\n\n"
    + "Our youngest are the runts who have yet to learn their place. As they "
    + "grow they begin to gather the various herbs and plants that we use "
    + "in our rituals and to enhance our food. Eventually they will learn "
    + "how to hunt with their family and bring the meat that is the key to "
    + "us being sustained.\n\nAs they grow into their own, Saurians all "
    + "train as warriors so that they may protect themselves and our young "
    + "from the threats that exist in the realms. Those amongst us who are "
    + "the most skilled become our scouts. There are those who are respected "
    + "members of each of these groups who help to train our young as they "
    + "grow. And those most Elder amongst us are the most revered.\n\n");
    return 1;
    break;
       
    case "history":
    case "History":
    write("Long ago as the lands of Kalad were just cooling from the molten "
    + "rock that they once were. As water fell from the sky, cooling the "
    + "earth and the vast desert separating Kalad and Cirath was just in "
    + "it's first stages, we were born. The Saurians rose from the ashes "
    + "of the earth. While we did not walk on two legs or have the marvel "
    + "intellect we have now, we remember.\n\nWe remember how the lands "
    + "formed from a wasteland. We remember scrounging to survive the harsh "
    + "waste that was the world. With almost nothing, we flourished. We "
    + "conquered that wasteland and we made it our own.\n\n");
    return 1;
    break;
    
    default:
    write("You can learn more about the history of the Saurians. Visions "
    +"available are:\n\n"
    +"                   History\n"
    +"                   History2\n"
    +"                   Society\n"
    +"                   Present\n"
    +"                   Final\n");
    return 1;
    }

}
