/*
 * Entrance of the Peredhil guild
 * Based on the Orc guild entrance
 * Finwe, February 2009
*/
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/lib/guild_support";
inherit BUILDING_BASE;

#include "/d/Shire/rivendell/local.h"
#include "/d/Shire/sys/defs.h"
#include "pered.h"
#include "pered_titles.h"
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#define MEMBERS_ADJ        0
#define MEMBERS_TITLE    1
#define MEMBERS_LOCALE    2
#define MEMBERS_TIME    3
#define DID_BEG            "_begged_for_sorcery"

/*
 * Global variables.
 *
 * The mapping members has the names of the players as indices and the
 * values are an array with two elements, the family name of the player
 * and the date the player joined.
 */
private mapping members;
static private string *adjs = ADJS;
static private string *titles = TITLES;
static private string *locales = LOCALES;

object magic_human;

void make_npc();

void create_guild_room()
{
// This needs to be cleaned up and better described

    set_short("A spacious lobby");
    set_long("This is a spacious lobby of the Peredhil. It is airy and quiet, and full of light from the hanging lamps and the @@daylight_desc@@ flowing in from the south. A sofa and a couch are set here for visitors to relax on. A fireplace is against the east wall. In one corner is a small niche, holding a large tome.\n");
    add_item("niche",
        "It is cut into a corner and holds a large tome. The niche is round and the back decorated with a motif of a tree.\n");
    add_item(({"window", "windows"}),
        "There are no windows in the foyer.\n");

    add_fireplace();

//    room_add_object("/d/Shire/guild/peredhil/obj/join_book");

   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_CLEANUP,      1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

//   create_guild_support();

   setuid();
   seteuid(getuid());

    restore_object(PERED_SAVE);
    if (!mappingp(members))
    {
        members = ([ ]);
    }

    // Test the validity of the members only at the first day of the month.
    if (atoi(ctime(time())[8..9]) == 1)
    {
        set_alarm(12.0, 0.0, "test_members");
    }

    reset_shire_room();
}

void reset_shire_room()
{
//    make_npc();
}

//void make_npc()
//{
//    if (!magic_human)
//        magic_human = clone_object("/d/Shire/guild/orc_guild/dark_sorcerer");
//    if (!present(magic_human,this_object()))
//        magic_human->move(this_object());
//}

/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());

   if (file_size(PERED_LOG) > LOG_SIZE)
      {
      rename(PERED_LOG, (PERED_LOG + ".old"));
   }

   write_file(PERED_LOG, text);
}

void init()
{
    ::init();

    init_guild_support();

    add_action("do_beg", "proclaim");
    add_action("do_claim", "claim");
    add_action("do_castoff", "cast");
    add_action("request", "request");

}

//do_beg, adds the prop to begin the transformation process.
int do_beg(string str)
{
    object tp = this_player();

    if(str == "lineage")
    {

        if (tp->query_race() != "elf" && tp->query_race() != "human")
        {
            write("You are neither an elf or a human. Only members of those races may proclaim their lineage and become Peredhil, or half-elves.\n");
            return 1;
        }


        if (IS_MEMBER(tp))
        {
            write("You are already a Peredhel. If you want to change your title, you must leave and rejoin to claim a new role or title.\n");
            return 1;
        }

        if (tp->query_guild_member(PERED_TYPE))
        {
            write("You cannot be a member of two racial guilds at the same time!\n");
            return 1;
        }

        if(tp->query_prop(DID_BEG))
        {
            write("You already proclaimed your lineage.\n");
            return 1;
        }

        else
        {
            tp->add_prop(DID_BEG, 1);
            write("You discuss your lineage with the xxx.\n");
            write("xxx takes some notes then turns to several volumes in the room. He opens one up and begins to turn pages looking for your lineage.\n");
            write("xxx looks at you and smiles, then makes some notes in the book.\n");
            write("Smiling, xxx closes the book and says, 'Welcome! It's good to count you among the Peredhil now!'");
            write("\nNow, to complete the transformation, you will need to choose your title.\n");

            return 1;
        }

        return 1;
    }

    else
    {
        write("Proclaim what, your lineage?\n");
        return 1;
    }
}

/*
    *Function name: do_claim
    *Description  : claims a title for the player
    *Arguments    : string str - the command line argument.
    *Returns      : int    1/0 - success/failure.
*/
nomask static int do_claim(string str)
{
    object shadow;
    object tp = this_player();
    string adj;
    string title;
    string loc;

    int result;

    if(tp->query_prop(DID_BEG))
    {
        if (!strlen(str))
        {
            notify_fail(capitalize(query_verb()) + " what? To claim a title, you must 'claim <adjective>, <title>, <location>'.\n" +
            "These are the possible choicees:\n\n" +
            "\tAdjectives          Titles          Locations\n" +
            "\t---------------------------------------------\n" +
            "\tBrave               Artist          Beor\n" +
            "\tConfident           Bard            Earendil\n" +
            "\tDashing             Champion        Hador\n" +
            "\tGallant             Defender        Haladin\n" +
            "\tHeroic              Guardian        Thingol\n" +
            "\tHonest              Poet            Tuor\n" +
            "\tMusical             Protector\n" +
            "\tPeaceful            Warrior\n" +
            "\tReckless\n" +
            "\tThoughtful\n" +
            "\tValiant\n\n");
              return 0;
        }

        if (sscanf(str, "%s, %s, %s", lower_case(adj), lower_case(title), lower_case(loc)) != 3)
        {
            notify_fail(capitalize(query_verb()) + " what? To claim a title, you must 'claim <adjective>, <title>, <location>'.\n" +
            "These are the possible choicees:\n\n" +
            "\tAdjectives          Titles          Locations\n" +
            "\t---------------------------------------------\n" +
            "\tBrave               Artist          Beor\n" +
            "\tConfident           Bard            Dior\n" +
            "\tDashing             Champion        Earendil\n" +
            "\tGallant             Defender        Hador\n" +   
            "\tHeroic              Guardian        Haladin\n" + 
            "\tHonest              Poet            Thingol\n" + 
            "\tMusical             Protector       Tuor\n" +    
            "\tPeaceful            Warrior\n" +
            "\tReckless\n" +
            "\tThoughtful\n" +
            "\tValiant\n\n");
              return 0;
        }

        if(member_array(lower_case(adj), adjs) == -1)
        {
            write("The adjective '" + adj + "' is not possible at this time. The possible adjectives:\n\n" +
            "\tAdjectives\n" +
            "\t-----------\n" +
            "\t* Brave\n" +
            "\t* Confident\n" +
            "\t* Dashing\n" +
            "\t* Gallant\n" +
            "\t* Heroic\n" +
            "\t* Honest\n" +
            "\t* Musical\n" +
            "\t* Peaceful\n" +
            "\t* Reckless\n" +
            "\t* Thoughtful\n" +
            "\t* Valiant\n\n");
            return 1;
        }

        if(member_array(lower_case(title), titles) == -1)
        {
            write("The title '" + title + "' is not available. The possible titles are:\n\n"
            "\tTitles\n" +
            "\t-----------\n" +
            "\t* Artist\n" +
            "\t* Bard\n" +
            "\t* Champion\n" +
            "\t* Defender\n" +
            "\t* Guardian\n" +
            "\t* Poet\n" +
            "\t* Protector\n" +
            "\t* Warrior\n\n");
            return 1;
        }

        if(member_array(lower_case(loc), locales) == -1)
        {
            write("The location '" + loc + "' does not exist. The possible locations are:\n\n" +
            "\tLocations\n" +
            "\t----------\n" +
            "\t* Beor\n" +
            "\t* Dior\n" +
            "\t* Earendil\n" +
            "\t* Hador\n" +
            "\t* Haladin\n" +
            "\t* Thingol\n" +
            "\t* Tuor\n\n");
            return 1;
        }

        shadow = clone_object(PERED_SHADOW);

        if ((result = shadow->shadow_me(tp, PERED_TYPE, PERED_STYLE, PERED_NAME)) != 1)
        {
            log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " failed to add shadow with result " + result + ".\n");
              shadow->remove_shadow();

              write("For some reason, you were not not inducted into the guild. Please leave a bug report in this room.\n");

              return 1;
        }

        //write("You seem to have a shadow...\n\n");
        write("The XXX starts to chant something, and the room begins to fill with light.\n\n");
        write("The light grows brighter and brighter, until it blinds you.\n\n");
        write("You close your eyes and shield them with your arms, but it's too late, You are blinded.\n\n");

        if(tp->query_race() == "elf")
            write("Mortality infuses your body, granting you the hardiness and strength of men.\n\n");
        if(tp->query_race() == "human");
            write("You are blessed with wisdom and the beauty of elves.\n\n");
        write("The light fades, leaving you feeling odd and disoriented.\n");

        write("The XXX starts to chant something, and the room begins to fill with light.\n\n");
        write("The light grows brighter and brighter, until it blinds you.\n\n");
        write("You close your eyes and shield them with your arms, but it's too late. You are blinded.\n\n");

        clone_object(PERED_BAND)->move(tp, 1);
        tp->set_clan_name(CAP(adj), CAP(title), CAP(loc));
        //write("Setting clan name - Joinroom.\n");
        set_alarm(3.0,0.0,"init_me",tp);
        log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " + PERED_NAME + ".\n");

        tp->remove_prop(DID_BEG);
        tp->clear_guild_stat(SS_RACE);
        tp->set_guild_pref(SS_RACE, PERED_TAX);
        tp->add_cmdsoul(PERED_SOUL);
        tp->update_hooks();
        //write("Normaly would be adding cmdsoul here...\n");

        members[tp->query_real_name()] = ({ adj, title, loc, tp->query_age(), time() });
        save_object(PERED_SAVE);
        //write("Saving master object...\n");

        return 1;
    }

    else
    {
        write("You must first beg! Beg for it!\n");
        return 1;
    }
}

int
init_me(object ob)
{
   ob->init_race_shadow();
   return 1;
}

void dest_band(object player)
{
    object band;

    band = present(BAND_ID, player);
    if (objectp(band))
    {
        band->remove_object();
    }
}

/*
* Function name: lower_skill
* Description  : When a member leaves the guild or is kicked out due
*                to a change of race, this function punishes him/her,
*                removes the soul, shadow, etcetera.
* Arguments    : object tp - the object leaving.
*/
nomask private void lower_skill(object tp)
{
    object band;

    tp->set_guild_pref(SS_RACE, 0);
    tp->clear_guild_stat(SS_RACE);
    tp->remove_cmdsoul(PERED_SOUL);
    tp->update_hooks();
    tp->setup_skill_decay();

    /* If the player starts in the guild by default, set this to
   * the default starting location for all players.
   */
    if (tp->query_default_start_location() == START)
    {
        tp->set_default_start_location(tp->query_def_start());
    }

    set_alarm(2.0,0.0,&dest_band(tp));
    {
        band->remove_object();
    }
   /* Remove him/her from the list of members.
   */
    members = m_delete(members, tp->query_real_name());

    setuid();
    seteuid(getuid());

    save_object(PERED_SAVE);

}

void remove_from_list(string player)
{
   player = lower_case(player);
   members = m_delete(members,player);
   setuid(); seteuid(getuid());
   save_object(PERED_SAVE);
}

/*
* Function name: remove_player_changed_race
* Description  : Whenever a member changes his/her race (s)he is
*                mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void remove_player_changed_race(object tp)
{
   tp->catch_msg("\nYour body, being not of elven-kind, can no longer be sustained by dark sorcery in the form of an orc. Therefore you do not " +
      "belong in the " + PERED_NAME + " any more. You " +
      "are being expelled from the guild.\n");

   lower_skill(tp);
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") was kicked out.\n");
}

/*
* Function name: remove_player_low_alignment
* Description  : Whenever the alignment of a player is too low, the player
*                is mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void remove_player_high_alignment(object tp)
{
   tp->catch_msg("\nSo you are no longer devoted to bringing about the subjegation of the Free Peoples? Then there is no place for you in the " + PERED_NAME + " any more. " +
      "You are being expelled from the guild.\n");

   tp->set_race_name(tp->query_race());
   lower_skill(tp);

   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
}

/*
* Function name: do_cast
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_castoff(string str)
{
   object tp = this_player();
   object band;
   int result;
   int death_number;
   int health;
    if (str != "off" && str != "off sorcery" && str != "off the sorcery")
    {
        notify_fail("Cast? Cast off the sorcery?\n");
        return 0;
    }

   if (!IS_MEMBER(tp))
      {
      write("You cannot cast off the sorcery, as it holds no sway over you.\n");
      return 1;
   }

   if ((result = tp->remove_guild_race()) != 1)
      {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to remove shadow with result " + result + ".\n");

      write("You cannot seem to cast off the vile sorcery! However, everyone who " +
         "wishes so, should be able to do so. Please leave a bugreport " +
         "in this room.\n");

      return 1;
   }

   write("You feel much pain as the magic that held your twisted form is ripped from you, leaving you weak and frail...\n");

   tp->set_race_name(tp->query_race());
   lower_skill(tp);

   band = present(BAND_ID, tp);

    if (objectp(band))
    {
        band->remove_object();
        write("Your iron arm band suddenly catches fire, then is completely vanished!\n");
    }

   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      PERED_NAME + ".\n");

//    health = tp->query_hp();
//    tp->heal_hp(- (health - 1));

    return 1;
}

/*
* Function name: request
* Description  : Members who have lost their circlet, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int request(string str)
{
    if (str != "arm band")
    {
        notify_fail("Request what? A new arm band?\n");
    return 0;
    }

    if (!IS_MEMBER(TP))
    {
        write("You are not a member of this guild. You have no " +
            "right to an arm band.\n");
    return 1;
    }

    if (objectp(present(BAND_ID, TP)))
    {
        write("You already have an arm band. You don't need two.\n");
    return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(PERED_BAND)->move(TP, 1);

    write("A small orc rushes into the room and hands you another arm band and leaves.\n");
    say(" A small orc rushes into the room and hands " +QCTNAME(TP)  + " an iron arm band and leaves.\n");

    return 1;
}

public string query_clan_name(string name)
{
   if (!members[name])
      {
      return "";
   }

   return "the " + members[name][MEMBERS_ADJ] + " " + members[name][MEMBERS_TITLE] + " of " + members[name][MEMBERS_LOCALE];
}

string read_plaque(string str)
{

    return " \n __________________________________________________________\n"+
            "|O  _____________________________________________________ O|\n"+
            "|  /                                                     \\ |\n"+
            "| |                  BE FOREWARNED!!                     | |\n"+
            "| |          Orcs do not take betrayal lightly.          | |\n"+
            "| |       If you join, and later decide to reject        | |\n"+
            "| |     that which you have become, or do not remain     | |\n"+
            "| |     sinister enough for the sorcery to bind you,     | |\n"+
            "| |       whatever happens to you then is on your        | |\n"+
            "| |        own head. You have been fairly warned.        | |\n"+
            "| |        Ask the wretched human about leaving.         | |\n"+
            "| \\______________________________________________________/ |\n"+
            "|O                                                        O|\n"+
            " ----------------------------------------------------------\n\n";
}