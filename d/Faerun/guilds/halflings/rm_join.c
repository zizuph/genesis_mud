/*
 * Join room of the Halflings guild
 * Based on the Orc guild of the Shire
 * Finwe, September 2015
 */
#pragma save_binary
#pragma strict_types

#include "halflings.h"
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>
#include <terrain.h>

inherit GUILD_ROOMS;
inherit "/lib/guild_support";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#define SOFA_CHAIR      "soft leather sofa"
#define COUCH_CHAIR     "large maroon couch"

public string    look_at(string arg);    /* VBFC for chairs */

/*
 * Global variables.
 *
 * The mapping members has the names of the players as indices and the
 * values are an array with two elements, the family name of the player
 * and the date the player joined.
 */
private mapping members;
//   Prototypes
void dest_guild_item(object player);
void remove_from_list(string player);

void reset_room()
{
    ::reset_room;
}

void 
create_guild_room()
{
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    setuid();
    seteuid(getuid());

    set_short("A brightly lit lobby");
    set_long("This is the lobby for the guild of the Halflings of Faerun. It " +
        "is large and well lit. The walls and floor are made of wood. " +
        "Candles are spaced on the walls near the ceiling and fill the " +
        "room with warm light. The floor is polished and clean. A large " +
        "maroon couch and a soft leather sofa are set in the room for " +
        "visitors to sit on. A burnished plaque hangs on a wall.\n");


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item("plaque", "Maybe you should read it.\n");
    add_cmd_item("plaque", ({"read", "examine", "exa"}), "@@read_sign@@");

    restore_object(GUILD_SAVE);
    if (!mappingp(members))
    {
        members = ([ ]);
    }

    add_exit(HALFGLD_DIR + "rm_train", "north", "@@check_member@@");
//    add_exit(HALFGLD_DIR + "rm_kitchen", "east", "@@check_member@@");
    add_exit(HALFGLD_DIR + "rm_board", "south", "@@check_member@@");
    add_exit(VILLAGE_DIR + "rooms/rd01", "west");

//    room_add_object("/d/Faerun/guilds/halflings/join_book");

    add_chair(SOFA_CHAIR,
        "[down] [on] / [in] [the] [soft] [leather] 'sofa'", 4);
    add_item( ({ "sofa"}), &look_at(SOFA_CHAIR) );

    add_chair(COUCH_CHAIR,
        "[down] [on] / [in] [the] [large] [maroon] 'couch'", 4);
    add_item( ({ "couch", }), &look_at(COUCH_CHAIR) );

    reset_room();
}

void 
init()
{
    ::init();

    add_action("do_try",   "proclaim");
    add_action("do_break", "sever");
    add_action("request",  "request");

    init_room_chairs(); /* add chair verbs */

}

string 
read_sign()
{
    return "\n" +
"                                  @@@@@@@@@\n" +
"                             @@@@@@@@@@@@@@@@@@@\n" +
"                          @@@@@@@           @@@@@@@\n" +
"                        @@@@                    @@@@@\n" +
"                      @@@@                         @@@\n" +
"                     @@@                             @@@\n" +
"                   @@@                                @@@\n" +
"                  @@@                                  @@@\n" +
"    +-------------+ |                                   | +-------------+\n" +
"    | +-------------+                                   +-------------+ |\n" +
"    | |                                                               | |\n" +
"    | |         T H E   H A L F L I N G S   O F   F A E R U N         | |\n" +
"    | |                                                               | |\n" +
"    | |    The Halflings of Faerun are a lively group. They follow    | |\n" +
"    | |    their own rules and morals, and are free to act as they    | |\n" +
"    | |    please. This freedom allows all halflings the choice to    | |\n" +
"    | |    follow any path they want, whether it be good, evil, or    | |\n" +
"    | |    anything in between.                                       | |\n" +
"    | |                                                               | |\n" +
"    | |    If you decide to become a halfling, you must:              | |\n" +
"    | |       <proclaim heritage>                                     | |\n" +
"    | |                                                               | |\n" +
"    | |    Should there come a time when you no longer want to be     | |\n" +
"    | |    a halfling, you will need to need to return here and:      | |\n" +
"    | |       <sever ties>                                            | |\n" +
"    | |                                                               | |\n" +
"    | |    If you lose your guild item, it can be replaced by:        | |\n" +
"    | |       <request pendant>                                       | |\n" +
"    | |                                                               | |\n" +
"    | +---------------------------------------------------------------+ |\n" +
"    +-------------------------------------------------------------------+\n\n";


}

public int
query_is_member(string name)
{
    if(members[name])
    {
        return 1;
    }

    return 0;
}

int
check_member()
{
    object tp = this_player();

    if((!tp->query_wiz_level()) && (!IS_MEMBER(tp)))
    {
        write("A large, burly halfling blocks you from going there.\n");
        return 1;
    }
    return 0;
}

nomask private void
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(GUILD_LOG) > LOG_SIZE)
    {
        rename(GUILD_LOG, (GUILD_LOG + ".old"));
    }

    write_file(GUILD_LOG, text);
}

/*
* Function name: do_try
* Description  : When a elf wants to join the guild, this function
*                makes them a member.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_try(string str)
{
    object tp = this_player();
    object shadow;
    int    result;

    if (!strlen(str) || str != "heritage")
    {
        write(str + "\n");
        notify_fail("What do you want to become, a halfling?\n");
        return 0;
    }

    if (tp->query_race() != "hobbit")
    {
        write("You silly " + tp->query_race() + ". Only hobbits may " +
            "become a Halfling of Faerun.\n");
        return 1;
    }

// check if player is a member already
    if (IS_MEMBER(tp))
    {
        write("You are already a halfling.\n");
        return 1;
    }

    if (tp->query_guild_member(GUILD_TYPE))
    {
        write("You cannot be a member of two racial guilds at a time.\n");
        return 1;
    }

    shadow = clone_object(GUILD_SHADOW);

    if ((result = shadow->shadow_me(tp, GUILD_TYPE, 
        GUILD_STYLE, GUILD_NAME)) != 1)
    {
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) +
            " failed to add shadow with result " + result + ".\n");
        shadow->remove_shadow();
        write("Something terrible has happened to your shadow. Please leave a " +
            "bug report in this room.\n");
    return 1;
    }

    set_alarm(3.0,0.0,"init_me",tp);

// logs the join
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " joined the " +
        GUILD_NAME + ".\n");

// creates the guild item
    clone_object(GUILD_ITEM)->move(tp, 1);

// joining message
    write("A warm glow fills you and a single beam of light envelopes you.\n");
    write("In the light you see the face of of a strong female halfling " +
        "with red-golden hair. She smiles happily at you and offers you " +
        "a pendant. You reach out and take it from her.\n");
    write("The light fades away ...\n");

    say("A single beam of light falls on " + QTNAME(tp) + ". " + 
        CAP(HE_SHE(tp)) + " reaches into the light and grabs something.\n");
    say("The light fades away ...\n");

    tp->clear_guild_stat(SS_RACE);
    tp->set_guild_pref(SS_RACE, GUILD_TAX);
    tp->add_cmdsoul(GUILD_SOUL);
    tp->update_hooks();
// changes descr to a halfling.
    tp->set_race_name("halfling");

    members[tp->query_real_name()] = ({tp->query_age(), time() });
    save_object(GUILD_SAVE);

    return 1;
}


int 
init_me(object ob)
{
    ob->init_race_shadow();
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
    tp->set_guild_pref(SS_RACE, 0);
    tp->clear_guild_stat(SS_RACE);
    tp->remove_cmdsoul(GUILD_SOUL);
    tp->update_hooks();
    tp->setup_skill_decay();

   /* If the player starts in the guild by default, set this to
    * the default starting location for all players.
    */
    if (tp->query_default_start_location() == START)
    {
        tp->set_default_start_location(tp->query_def_start());
    }

    set_alarm(2.0,0.0,&dest_guild_item(tp));

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

void 
dest_guild_item(object player)
{
    object pendant;

    pendant = present(MEDALLION_NAME, player);
    pendant->remove_object();
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
    object pendant;
    int    result;

    if (str != lower_case("ties"))
    {
        notify_fail("Do you want to leave the Halflings? You must " +
            "<sever ties>.\n");
        return 0;
    }

    if (!IS_MEMBER(tp))
    {
        write("You cannot leave the " + GUILD_NAME + ". You were never " +
            "a member of the guild.\n");
        return 1;
    }

    if ((result = tp->remove_guild_race()) != 1)
    {
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) +
            " failed to remove shadow with result " + result + ".\n");

        write("You are unable leave the " + GUILD_NAME + ". Please leave a " +
            "bugreport in this room about this. Thanks.\n");
        return 1;
    }

    pendant = present(GUILD_ITEM_ID, tp);
    pendant->remove_object();
    write("A dark cloud rolls in. A cold wind blows around the room, " +
        "almost knocking you down. Your pendant suddenly gets hot and " +
        "bursts into flames.\n" +
        "Then nothing ...\n");

    say("A dark cloud rolls in. A cold wind blows around the room, " +
        "almost knocking " + QTNAME(TP) + " to the ground. Something " +
        "bursts into flame.\n");

    lower_skill(tp);
    tp->set_race_name("hobbit");

    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " left the " +
        GUILD_NAME + ".\n");
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

    if (str != "pendant")
    {
        notify_fail("Request what? A new pendant?\n");
        return 0;
    }

    if (!IS_MEMBER(tp))
    {
        write("You are not a member of the " + GUILD_NAME + ".\n");
        return 1;
    }

    if (objectp(present(GUILD_ITEM_ID, tp)))
    {
        write("You already have a pendant. You don't need two.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(GUILD_ITEM)->move(tp, 1);

    write("A new pendant appears before you. You reach out and take it.\n");
    say(QCTNAME(tp)  + " stretches out " + HIS_HER(tp) + " hand and takes " +
        "a pendant floating in the air.\n");
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
    tp->catch_msg("\nYou are no longer a hobbit. You cannot claim " +
        "yourself a member of the " + GUILD_NAME + " anymore. You are " +
        "expelled from the guild.\n");

    lower_skill(tp);
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " (race " +
        tp->query_race_name() + ") was kicked out.\n");
}


/*
 * Function name:   look_at
 * Description  :   VBFC to describe chair/sofa + occupants
 * Arguments    :   string arg -- what's being looked at
 *                  null str -> it's the room
 * Returns      :    string -- the description
 */
public string
look_at(string arg)
{
    switch ( arg )
    {
        case SOFA_CHAIR:
            return "The sofa is large and made of leather. It is overstuffed " +
                "a beige color. The sofa looks very comfortable and plush " +
                "and will seat four.\n" + 
                sitting_on_chair(SOFA_CHAIR, this_player(), 0);
            break;
        case COUCH_CHAIR:
            return "The couch is made of maroon colored fabric. It is soft " +
                "and plush looking and will seat four.\n" +
                sitting_on_chair(COUCH_CHAIR, this_player(), 0);
            break;
    }
} /* look_at */



int
block_room()
{
    if (this_player()->query_wiz_level()) 
    {
        write("\n\nYou enter an area that is not open to mortals.\n\n\n");
        return 0;
    }
    
    write("The door is currently closed and locked.\n");
    return 1;
}