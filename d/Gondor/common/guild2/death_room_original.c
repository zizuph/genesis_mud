/*
 * /d/Gondor/common/guild2/death_room.c
 *
 * The room where one can join the Morgul Mages
 * - at the same time the master object of the guild
 *
 * Created: Olorin, 05-jan-1994
 *
 * Copyright (c) 1997 by Christian Markus
 *
 * Modification Log:
 * 20-Jan-1997, Olorin: General revision.
 *  8-Mar-1998, Mercade: Punishment of players not logged in.
 *
 * Feb, 8 2006 Altrus:
 * Changed the joining code to query_race_name instead of query_race
 * to allow certain masked races to join. The forbidden races are listed
 * in a changed list in the morgul_defs.h. This was to allow the presence
 * of orcs who are base-elf bodies.
 *
 * Jan 5, 2007 Toby:
 * Added support to store the rank of mages and the time it was last updated.
 * This is a helpful tool for the Nine to monitor the status of the Society.
 *
 *
 *
 * Functions available for Call here:
 *
 *    - query_mages
 *    - query_is_mage      (str)
 *    - query_morgul_level (str)
 *    - query_mage_title   (str) [Outdated]
 *    - print_mage_list          [Erronous due to query_mage_title outdate]
 *    - query_male_titles
 *    - query_female_titles
 *    - query_male_nazgul_titles
 *    - query_female_nazgul_titles
 *    - query_sage_titles
 *    - query_mage_names
 *    - query_mage_name    (str)
 *    - query_mage_rank    (str)
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <time.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_titles.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

#define  MORGUL_S_SPONSOR         "_morgul_s_sponsor"
#define  MEMBER_LIST              (GUILD_DIR + "morgul_mages")
#define  MORGUL_I_DEATH_WARNING   "_morgul_i_death_warning"
#define  MORGUL_I_SAGE            (GUILD_DIR + "throne_room")

/*
 *      Prototypes:
 */
private void    punish_mage(object mage);

public  int     check_exit();
public  void    first_death(string str);
public  void    second_death(string str);
public  void    third_death(string str);
public  int     get_sponsor(string name);

public string query_sage_title(object mage);
int    update_mage_rank(object mage);
int    query_mage_rank(string mage);

public void incr_ISE_counter();
public int query_ISE_counter();
public void reset_ISE_counter();

/*
 *      Global variables:
 *
 * Mages       - list of names of the morgul mages.
 * Mage_Names  - index is player name, value is mage name.
 * Mage_Ranks  - index is players name, value is the numerical value of current rank  
 * Punishments - punishments of players not logged in. Index is player name.
 *               Values: ({ name of punisher, punishment, reason })
 * SulambarCharges - Remaining charges for the Sulambar spell
 *                   Values: ({ last age at recharge, number of charges remain })
 */
string *Mages = ({ });
mapping Mage_Names = ([ "olorin" : "Annatar", ]);
mapping Mage_Ranks = ([ ]);
mapping Punishments = ([ ]);
mapping SulambarCharges = ([ ]);

static public int _Idleness_System_Error_counter = 0;

/*
 * load titles into a global variable at creation: this saves cpu time!
 */
static  string *Male_Titles   = MORGUL_AS_MALE_TITLES,
*Female_Titles = MORGUL_AS_FEMALE_TITLES,
*Male_Nazgul_Titles   = MORGUL_AS_MALE_NAZGUL_TITLES,
*Female_Nazgul_Titles = MORGUL_AS_FEMALE_NAZGUL_TITLES,
*Sage_Titles   = MORGUL_AS_SAGE_TITLES;


#define DEBUGT(x)            find_player("toby")->catch_msg(x + "\n");



/*
 * Function name: create_morgul_tower_room
 * Description:   room creator for tower rooms
 */
private void
create_morgul_tower_room()
{
    restore_object(MEMBER_LIST);

    set_level(2);
    set_room_type("great hall");
    set_name("Morgul_Mage_Master");
    set_extra_long("The hall is devoid of decorations and furniture " +
      "except for a large black stone slab in the back of the hall. " +
      "The hall continues to the south.");

    add_floor();
    add_no_roof();
    add_walls();

    add_item(({"stone","stone slab","altar","slab"}), BSN(
        "The stone slab is about four feet high, eight feet long, and " +
        "four feet broad. It was hewn from the same rock as the stones " +
        "that make the walls and the floor. On the smooth surface are " +
        "dark brown stains. If you are a servant of the Dark Lord, you " +
        "can beg for a new robe at this altar if you have lost your " +
        "old one. If you should decide to leave the Society, you can " +
        "come here to betray its Lord Sauron."));
    add_item(({"stain","stains","blood","blood stains","brown stains",
        "dark stains"}), BSN(
        "On top of the stone slab are dark brown stains. They look " +
        "like dried blood."));
    add_item(({"hall","great hall"}), BSN(
        "Except for the altar, the hall is devoid of decorations and " +
        "furniture. The walls are also almost featureless, the seams " +
        "between the stone blocks are hardly visible. The roof is hidden " +
        "in the darkness above. The hall continues further to the south, " +
        "where a doorway is visible."));
    add_item(({"door","entrance","doorway","exit"}), BSN(
        "The doorway in the southern half of the hall is leading out " +
        "onto the staircase."));

    add_prop(ROOM_I_LIGHT,1);
/*
    add_prop( ROOM_M_NO_ATTACK,
        "The Power of the Dark Lord prevents your attack.\n" );
    add_prop( ROOM_M_NO_MAGIC_ATTACK,
        "The Power of the Dark Lord prevents your attack.\n" );
*/
    add_prop( ROOM_I_NO_CLEANUP, 1 );

    add_exit( "/d/Gondor/guilds/morgulmage/rooms/tower_2n" ,"south", check_exit, 0 );

    /* Allow players to use the "mlist" command even when paralyzed. */
    CMDPARSE_PARALYZE_ALLOW_CMDS( ({ "mlist" }) );
    
    IDLENESS->start_idling();
    return;
}

public int
do_beg(string str)
{
    int     nl;
    object  robe;

    if (TP->query_guild_name_occ() != GUILD_NAME)
        return 0;

    if (!strlen(str) ||
        !parse_command(str, ({}), "[for] [a] [new] 'robe'"))
    {
        NFN0("Beg for what?");
    }

    if (present(MORGUL_S_GUILD_OBJECT, TP))
    {
        write("You have a robe! Why should you want to anger the Dark Lord "
          + "by begging for a new one?\n");
        return 1;
    }

    robe = clone_object(MAGES_DIR + "mage_robe");
    if (robe->move(TP))
        robe->move(TP, 1);
    write( "Since you have lost your robe, the Dark Lord listens to your "+
           "begging.\nA large black robe materializes out of the air. You "+
           "grab it.\n");
    say( "A large black robe materializes out of the air.\n" +
        QCTNAME(TP) + " grabs it quickly.\n" );

    return 1;
}

public int 
accept_player( object player )
{
 string  race = player->query_race_name();

/*
    notify_fail( "The Lord of Morgul doesn't accept any new member!\n" );
    return 0;
 */

    if (member_array(race, MORGUL_AS_ILLEGAL_RACE_NAME) > -1)
    {
        notify_fail( "The Lord of Morgul does not accept "+
            LANG_ADDART( player->query_race_name() )+ " into his service!");
        return 0;
    }
    if (player->query_guild_style( "cleric" ))
    {
        notify_fail( "The Lord of Morgul does not tolerate clerics in his "+
            "service!" );
        return 0;
    }
    if (player->query_alignment() > MORGUL_I_ALIGN_JOIN)
    {
        notify_fail( "The Lord of Morgul accepts only servants devoted to "+
            "darkness!" );
        return 0;
    }

    return 1;
}

public int
do_join( string str )
{
    notify_fail( capitalize( query_verb()) + " what?" );
    if (!strlen( str ))
    {
        return 0;
    }
    if (!parse_command( lower_case( str ), ({ }),
        "[the] 'service' [of] [the] [dark] [lord]" ))
    {
        return 0;
    }
    notify_fail( "You are already one of the Morgul Mages." );
    if (this_player()->query_guild_name_occ() == GUILD_NAME)
    {
        return 0;
    }
    if (!accept_player( this_player() ))
    {
        return 0;
    }
    tell_room( this_object(), "You feel a dark terrible power arriving "+
        "somewhere close to the altar, but you cannot see anything. " );
    say( QCTNAME( this_player() )+ " seems terrified and looks around "+
        "like searching for something.\n" );
    write( "A menacing voice whispers in your head:\n"+ break_string(
        "So you want to enter the Service of Sauron, the Dark Lord? "+
        "Few mortals do so of their own free will, and of those few "+
        "hardly none dare to come here to offer their service, nor do "+
        "they know what to expect! And the Dark Lord is suspicious of "+
        "them, for He detests traitors!\n", 70, "    ") + break_string(
        "Therefore, the Dark Lord demands utmost fealty and allegiance "+
        "and He demands your life before you may serve Him!\n", 70, "    ")+
      "    Three times I will ask you, and three times will you answer!\n\n"+
      "The dark voice asks you:\n" + break_string(
        "What gift will you receive before you will be allowed to join our " +
        "ranks?\n", 70, "    ") + 
      "    Answer me now!\n> ");
    input_to( first_death );
    return 1;
}

public void 
first_death(string str)
{
    string  poss = TP->query_possessive();
    say(QCTNAME(TP) + " seems to be fighting a battle in "+poss+" mind.\n" + 
      CAP(TP->query_pronoun()) + " has a strained look and is mumbling under "+poss+" breath.\n");

    str = LOW(str);
    if (str != "death")
    {
        write("The dark voices screams in your head:\n" + 
          "    GO AWAY, FOOL!\n" +
          "    The only gift the Lord of Gifts has to give you is ...\n" +
          "     ... DEATH!!!\n");
        return;
    }
    write("The dark voice chuckles:\n" + break_string(
        "Yes, that is why He once called himself Anna-Tar, the Lord of Gifts!\n", 70, "    ") +
      "The menacing voice asks you the second question:\n" + break_string(
        "What will be your fate when the Dark Lord or one of His servants " +
        "will find you unfit for His service, because you turned towards " +
        "the accursed so-called 'good' or became a cleric, or because you " +
        "withstand His Power like the detested dwarves or halflings or the " +
        "accursed elves?\n", 70, "    ") +
      "    Answer me now!\n> ");
    input_to(second_death);
    return;
}

public void 
second_death(string str)
{
    say(QCTNAME(TP) + " is still mumbling and seems to be far away in thoughts.\n");

    str = LOW(str);
    if (str != "death")
    {
        write("The dark voices screams in your head:\n" +
          "    GO AWAY, FOOL!\n" +
          "    The only fate you can expect is ...\n" +
          "     ... DEATH!!!\n");
        return;
    }
    write("The dark voice whispers:\n" +
      "    Yes, expect only death, since only death you will meet!\n" + break_string(
        "Know, that the head of the Society, the Lord of the Nazgul, once was a " +
        "mortal worm like you are now, and although an undead now, still " +
        "is not immortal like the creators of the world.\n", 70, "    ") +
      "The dark voice asks you the third question:\n" + break_string(
        "What will you receive out of the hand of the Lord of the Nazgul, " +
        "with sound reason or without, with warning or without, if you " +
        "should ever dare to disobey or displease him?\n", 70, "    ") +
      "    Answer me now!\n> ");
    input_to(third_death);
    return;
}

public void 
third_death(string str)
{
    say(QCTNAME(TP) + " seems to be lost for this world, dreaming in far away spheres.\n");

    str = LOW(str);
    if (str != "death")
    {
        write("The dark voices screams in your head:\n" +
          "    GO AWAY, FOOL!\n" +
          "    The only thing you will receive is ...\n" +
          "     ... DEATH!!!\n");
        return;
    }
    write("The dark voice hisses:\n" +
      "    Yes! Death, Death, DEATH!!!!!\n" + break_string(
        "Death, Obedience, complete and utter Allegiance to the Dark Lord " +
        "and His appointed servants! Do not expect power or secrets, " +
        "the Dark Lord takes and gives like He pleases, and it pleases Him " +
        "more to take than to give!\n", 70, "    ") +
      "The threatening voice asks again:\n" +
      "    Now I must know, which servant of the Dark Lord will " +
      "assist you?\n> ");
    say(QCTNAME(TP) + " decided to forsake life and to enter the service of the Dark Lord.\n" + 
      CAP(TP->query_pronoun()) + " wants to join the Society of Morgul Mages!\n");
    input_to(get_sponsor);

    return;
}

public int 
get_sponsor(string name)
{
    object  sponsor,
    death_flag;

    name = lower_case(name);

    if (!objectp(sponsor = present(name,TO))) 
    {
        write("Where is one that is to show you the path of shadow?\n");
        return 0;
    }

/*    if (sponsor->query_guild_name_occ() != GUILD_NAME)
    {
        write(sponsor->query_name() + " is not one of the servants of Melkor!\n");
        return 0;
    }
*/

    sponsor->add_prop(MORGUL_S_SPONSOR, TP->query_real_name());
    death_flag = clone_object(GUILD_DIR + "obj/death_flag");
    death_flag->set_initiate(TP->query_real_name(), name);
    death_flag->move(TP, 1);

    tell_room(TO, 
      "A dark menacing voice says:\n" +
      "    " + QCTNAME(TP) + " has chosen " + CAP(name) + " to make " +
      TP->query_objective() + " meet Death!\n" +
      "    Now I, Sauron, King of the World and Lord of the Darkness,\n" +
      "    order you, "+CAP(name)+", to convey "+TP->query_name()+" from life to death\n" +
      "    so that "+TP->query_pronoun()+" may join us in the service of Melkor.\n");
    return 1;
}

private void
add_to_list(string initiate)
{
    if (!sizeof(Mages))
        Mages = ({ });

    if (member_array(initiate, Mages) == -1)
        Mages += ({ initiate });
    else
        write_file(MORGUL_LOG, "ERROR: " + CAP(initiate) + " joins the Mages, " +
          "but is already listed as member!\n");
    save_object(MEMBER_LIST);
}

public varargs int
add_mage(string newmage, string sponsor_name)
{
    object  shadow,
    robe,
    newbie;
    int     result;

    if (!stringp(newmage))
        return 0;
    if (!objectp(newbie = find_player(newmage)))
        return 0;
    if (!present(newbie,TO))
        return 0;

    NFN("For unknown reasons you are not able to join the guild.");
    shadow = clone_object(GUILD_SHADOW);
    if ((result = shadow->shadow_me(newbie, GUILD_TYPE,
          GUILD_STYLE, GUILD_NAME)) != 1)
    {
        SECURITY->do_debug("destroy", shadow);
        return 0;
    }

    newbie->clear_guild_stat(SS_OCCUP);
    newbie->remove_skill(SS_MORGUL_PENALTY);
    newbie->set_bit(MORGUL_GROUP, MORGUL_MAGE_BIT);
    if (!present("morgul_guild_object", newbie))
    {
        robe = clone_object(GUILD_DIR + "mage_robe");
        robe->init_arg();
        if (robe->move(newbie))
            robe->move(newbie, 1);
    }
    newbie->init_occ_shadow("");
    add_to_list(newmage);
    write_file(MORGUL_LOG, "MORGUL MAGES: " + newbie->query_name() +
      " joined the Morgul Mages sponsored by "+CAP(sponsor_name)+
      ". " + ctime(time()) + ".\n");
    write("You are now a member of the Society of Morgul Mages!\n");
    return 1;
}

public int
do_list(string arg)
{
    string str;

    if ((arg != "guild") && (arg != "guilds"))
    {
        NFN("List what? Your guilds perhaps?");
        return 0;
    }

    str = TP->list_mayor_guilds();
    if (strlen(str))
        write("You are member of following guilds.\n" + str);
    else
        write("You are not member of any guilds.\n");

    return 1;
}

private void
remove_from_list(string traitor)
{
    traitor = LOW(traitor);

    if (MORGUL_NAZGUL_MASTER->query_is_nazgul(traitor))
        MORGUL_NAZGUL_MASTER->demote_nazgul(traitor, "left mages");

    if (member_array(traitor, Mages) < 0)
        write_file(MORGUL_LOG, "ERROR: " + CAP(traitor) + " leaves the Mages, " 
          + "but is not listed as a member!\n");
    else
    {
        Mages -= ({ traitor });
        Mage_Names = m_delete(Mage_Names, traitor);
        Mage_Ranks = m_delete(Mage_Ranks, traitor);
		m_delkey(SulambarCharges, traitor);
        save_object(MEMBER_LIST);
    }
}

/*
 * Function name: remove_shadow
 * Description:   do the actual removal of the shadow, soul,
 *                skills, guild stat
 * Arguments:     mage - object pointer to player
 *                punish - punish the mage for leaving
 * Returns:       1/0 - success/failure
 */
private int
remove_shadow(object mage, int punish)
{
    int     result;
    object  robe;

    if (!(result = mage->remove_guild_occ()))
        return 0;

    mage->clear_bit(MORGUL_GROUP, MORGUL_MAGE_BIT);
    mage->clear_guild_stat(SS_OCCUP);
    mage->remove_skill(SS_MORGUL_PENALTY);
    mage->remove_cmdsoul(MORGUL_SOUL_FILE);
    mage->update_hooks();

    if (objectp(robe = present("morgul_guild_object", mage)))
    {
        mage->catch_msg("Your "+robe->query_short()+" bursts out in flames and disappears.\n");
        tell_room(ENV(mage), "The "+robe->query_short()+" of "+
          QTNAME(mage)+" bursts out in flames and disappears.\n", mage);
        robe->remove_object();
    }
    if (punish)
        punish_mage(mage);
    return 1;
}

/*
 * Function name: kill_mage
 * Description:   kill the mage to punish him or her
 * Argument:      mage - object pointer to mage
 */
private void
kill_mage(object mage)
{
/*
 CLOSE
    mage->set_default_start_location(mage->query_def_start());
    return;
 END CLOSE
*/
    if (stringp(mage->query_guild_name_occ()))
    {
        write_file(MORGUL_LOG, "DEBUG: kill_mage called for " +
            mage->query_name() + ", member of " +
            mage->query_guild_name_occ() + "! " + ctime(time()) + "\n");
        return;
    }

    if (!objectp(present(mage, TO)))
    {
        mage->catch_msg("You are summoned by a powerful spirit.\n");
        mage->move_living("X", TO);
    }
    mage->heal_hp(- mage->query_max_hp() - 100);
    mage->do_die(TO);
}

/*
 * Function name: punish_mage
 * Description:   punishment for leaving the guild
 * Argument:      mage - object pointer to mage
 */
private void
punish_mage(object mage)
{
    mage->setup_skill_decay();

    set_alarm(0.0, 0.0, &kill_mage(mage));
}

/*
 * Function name: remove_mage
 * Description:   remove a mage from the guild
 *                punish the mage, write an log entry
 * Arguments:     mage   - the player object
 *                punish -  0: don't punish
 *                          1: left the guild
 *                          3: removed from the guild
 *                         -1: expelled from the guild
 *                reason -  a string to write to the log file
 * Returns:       1/0 - success/failure
 */
private int
remove_mage(object mage, string reason, int punish = 0)
{
    int     result;
    string  name;

    name = mage->query_real_name();
    if (strlen(name) &&
    pointerp(Punishments[name]))
    {
        Punishments = m_delete(Punishments, name);
        save_object(MEMBER_LIST);
    }

    if (mage->query_guild_name_occ() != GUILD_NAME)
        return 0;
    if (result = remove_shadow(mage, punish))
    {
        remove_from_list(mage->query_real_name());
        write_file(MORGUL_LOG, "MORGUL MAGES: " + mage->query_name()
          + " left the Morgul Mages. Reason: " + reason
          + " (" + punish + "). " + ctime(time()) + ".\n");
        write_file( MORGUL_RECORDS, mage->query_name()+ " left the Morgul "+
            "Mages. Reason: "+ reason+ ctime( time() )+ ".\n" );
        mage->catch_msg("The Lord of Morgul removes you from the "
          + "Society of Morgul Mages!\n");
    }
    else
    {
        write_file(MORGUL_LOG, "MORGUL MAGES: " + mage->query_name()
          + " failed to leave the Morgul Mages. Reason: " + reason
          + " (" + punish + "). Result: " + result + ". "
          + ctime(time()) + ".\n");
    }

    return result;
}

public int
do_leave(string str)
{
    NFN("Betray whom?");
    if (!strlen(str))
        return 0;

    str = LOW(str);
    if ((str != "sauron") && (str != "morgul") && (str != "guild") &&
      (str != "mages") && (str != "morgul mages"))
        return 0;

    NFN("But you are no member of our guild.");
    if (TP->query_guild_name_occ() != GUILD_NAME)
        return 0;

    if (remove_mage(TP, "Betrayed the Society", 1))
        write("You left the Society of Morgul Mages.\n");
    else
        write("There was a strange error, I'm afraid you are stuck with us.\n");

    return 1;
}

/*
 * Function name: check_exit
 * Description:   clean up when a player leaves the room (VBFC)
 * Returns:       0
 */
public int 
check_exit()
{
    object  flag;

    if (objectp(flag = present("_morgul_death_flag", TP)))
        flag->remove_object();
    TP->remove_prop(MORGUL_I_DEATH_WARNING);

    return 0;
}

public int 
do_sacrifice(string str)
{
 int i,j;
 object victim, heart, *livings;

    notify_fail( capitalize(query_verb()) + " whom?");
    if (!strlen(str))
        return 0;

    str = lower_case( str );

    if ((str == "being" || str == "me" || str == "self" ||
        str == "life" || str == "myself") ||
        (str == this_player()->query_real_name()))
    {
        notify_fail( "If you are seeking Death, enter the service of "+
            "the Dark Lord!\n" );
        return 0;
    }

    notify_fail( "There is no " + str + " here." );
    if (!objectp( victim = present(str,TO) ))
    {
        return 0;
    }

    notify_fail( "That is not alive!" );
    if (!living( victim ))
    {
        return 0;
    }
    
    notify_fail( victim->query_name() + " is not yet ready to die in order "+
        "to enter the service of Melkor!" );
    if (!present( "_morgul_death_flag", victim ))
    {
        return 0;
    }
    
    notify_fail( "You have not been elected to sacrifice " +
        victim->query_name() + "!" );
    if (this_player()->query_prop( MORGUL_S_SPONSOR ) !=
        victim->query_real_name())
    {
        return 0;
    }
    this_player()->remove_prop( MORGUL_S_SPONSOR );

    IDLENESS->increase_activity( this_player(), SACRIFICE );
    
    write( "With your bare hands, you tear open the ribcage of " +
        victim->query_the_name( this_player() ) + ".\n" +
        "From the still living body, you rip the bloody heart.\n");
    tell_room( this_object(), "With " + this_player()->query_possessive() +
        " bare hands, " + QCTNAME( this_player() ) +
        " tears open the ribcage of " + QTNAME( victim ) + ".\n" +
        "From the still living body, " + this_player()->query_pronoun() +
        " rips the bloody heart.\n", ({victim, this_player()}) );
    victim->catch_msg( "With " + this_player()->query_possessive() +
        " bare hands, " + QCTNAME( this_player() ) +
        " tears open your ribcage.\nStrangely, you feel no pain.\n" +
        "Distantly, you watch " + this_player()->query_objective() +
        " ripping the heart out of your body.\n" );
    heart = clone_object( "/std/leftover" );
    heart->leftover_init( "heart", victim->query_race_name() );
    heart->set_decay_time( 120 );
    heart->set_long( "This is the bloody heart of " +
        LANG_ADDART( victim->query_race_name()) + ".\n" );
    if (heart->move( this_player() ))  
    {
        if (heart->move( this_object() ))
        {
            heart->move(this_object(), 1);
        }
    }
    
    victim->heal_hp( - victim->query_max_hp() - 100 );
    victim->do_die( this_player() );

    livings = FILTER_OTHER_LIVE( all_inventory( this_object() ) );
    j = sizeof( livings );
    for (i=0;i<j;i++)
    {
        IDLENESS->increase_activity( livings[i], SACRIFICE*2/3 );
    }
    
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_join, "enter");
    add_action(do_sacrifice, "sacrifice");
    add_action(do_leave, "betray");
    add_action(do_list, "list");
    add_action(do_sacrifice, "kill");
    add_action(do_beg, "beg");
}

/*
 * Function name: remove_player_from_guild
 * Description:   this function is called from the shadow to
 *                remove a player from the guild
 * Argument:      player - player object
 *                reason - information for the log
 */
public void
remove_player_from_guild(object player, string reason = 0)
{
    if (remove_mage(player, reason, 3))
        write("You have been removed from the ranks of the Morgul Mages!\n");
}

/*
 * Function name: expel_player_from_guild
 * Description  : Function is called from the Nazgul "expel" command. It
 *                assumes that this_player() is the person who expelled,
 *                should the player not be present.
 * Arguments    : string caster - the nazgul exelling the player.
 *                string name - the name of the player to expel.
 *                string reason - the reason (with the name of the expeller).
 */
public void
expel_player_from_guild(string caster, string name, string reason)
{
    object player;

    player = find_player(name);
    if (objectp(player))
    {
        remove_mage(player, reason, -1);
        return;
    }

    /* Store the punishment for later use. */
    if (!pointerp(Punishments[name]))
    {
        Punishments[name] = ({ caster, MORGUL_PENALTY_EXPEL, reason });
    }
    else
    {
        Punishments[name] += ({ caster, MORGUL_PENALTY_EXPEL, reason });
    }

    /* Remove the person from the membership list. */
    Mages -= ({ name });

    save_object(MEMBER_LIST);
}

/*
 * Function name: expulsion_pending
 * Description  : Returns whether the player should be expelled upon entering
 *                the realms.
 * Arguments    : string name - the name of the player to check.
 * Returns      : string - the name of the person responsible for the
 *                    expulsion, then a colon, then the official log reason.
 */
public string
expulsion_pending(string name)
{
    int index;

    name = lower_case(name);

    if (!pointerp(Punishments[name]))
    {
        return 0;
    }

    /* Loop over all pending punishments. */
    for (index = 1; index < sizeof(Punishments[name]); index += 3)
    {
        /* Expulsion. */
        if (Punishments[name][index] == MORGUL_PENALTY_EXPEL)
        {
            return Punishments[name][index - 1] + ":" +
            Punishments[name][index + 1];
        }
    }

    return 0;
}

public int
filter_mage(object x) 
{ 
    return (x->query_guild_name_occ() == GUILD_NAME); 
}

public void
check_present_mages()
{
    object *present_mages;
    string  name;
    int     i, s,
    n,
    cf = 0;

    present_mages = users();

    for (i = 0, cf = 0, s = sizeof(present_mages); i < s; i++)
    {
        name = present_mages[i]->query_real_name();
        n = member_array(name, Mages);
        if (filter_mage(present_mages[i]))
        {
            if (n == -1)
            {
                add_to_list(name);
                write_file(MORGUL_LOG, "ERROR: " + CAP(name)
                  + " is Morgul mage, " + "but not listed! "
                  + ctime(time()) + "\n");
                cf++;
            }
        }
        else if (n > -1)
        {
            remove_from_list(name);
            write_file(MORGUL_LOG, "ERROR: " + CAP(name)
              + " is no Morgul mage, " + "but listed! "
              + ctime(time()) + "\n");
            cf++;
        }
    }
    if (cf)
        save_object(MEMBER_LIST);
}

public string *
query_mages()
{
 int i, j;

    j = sizeof( Mages );
    for (i=0;i<j;i++)
    {
        if (!SECURITY->exist_player( Mages[i] ))
        {
            write_file( MORGUL_LOG, "ERROR: "+ capitalize( Mages[i] )+ 
                " is not a player.\n");
            Mages -= ({ Mages[i] });
            j--;
            i--;
            save_object( MEMBER_LIST );
        }
    }

    // Pass a copy, not the array!
    return (Mages + ({ }) );
}

/*
 * Function name: query_is_mage
 * Description  : Tests whether a player is registered as mage.
 * Arguments    : string name - the name of the player to test.
 * Returns      : int - if true, the person is a mage.
 */
public int
query_is_mage(string name)
{
    return (member_array(lower_case(name), Mages) > -1);
}

public int
query_morgul_level(string mage)
{
    object  player;
    int     morgul_level,
            nlevels = sizeof(Male_Titles),
            morgul_stat;

    mage = LOW(mage);

    if (!(player = find_player(mage)))
    {
        player = SECURITY->finger_player(mage);
    }

    morgul_stat = player->query_stat(SS_OCCUP);

    if (player->query_finger_player())
    {
        player->remove_object();
    }

    if (morgul_stat > 100)
        morgul_stat = 100;

    morgul_level = ((morgul_stat * (nlevels - 1)) / 100);

    return morgul_level;
}

public string
query_mage_title(string mage)
{
    object  player;
    int     is_finger,
    morgul_level,
    nlevels = sizeof(Male_Titles),
    morgul_stat;
    string  morgul_title;

    mage = LOW(mage);

    if (SECURITY->query_wiz_level(mage))
        return "wizard";

    is_finger = 0;
    if (!(player = find_player(mage)))
    {
        player = SECURITY->finger_player(mage);
        is_finger = 1;
    }
    if (!player)
        return "";

    morgul_stat = player->query_stat(SS_OCCUP);
    if (morgul_stat > 100)
        morgul_stat = 100;

    morgul_level = ((morgul_stat * (nlevels - 1)) / 100);

    if (player->query_gender_string() == "female")
        morgul_title = "the " + Female_Titles[morgul_level];
    morgul_title = "the " + Male_Titles[morgul_level];

    if (is_finger)
        player->remove_object();

    return morgul_title;
}

public string
query_sage_title(object mage)
{
    return mage->query_morgul_level();
}

public string
print_mage_list()
{
    string  list,
    *mage_list,
    mage_title;
    int     i = 0,
    s;

    MORGUL_MASTER->check_present_mages();

    list = "These are presently the members of the Society of the Morgul Mages: \n\n";

    mage_list = MORGUL_MASTER->query_mages();

    for (i = 0, s = sizeof(mage_list); i < s; i++)
    {
        mage_title = query_mage_title(mage_list[i]);
        list += "- " + CAP(mage_list[i]) + ", " + mage_title + "\n";
    }
    return list + "\n";
}

public string *
query_male_titles()
{
    return Male_Titles;
}

public string *
query_female_titles()
{
    return Female_Titles;
}

public string *
query_male_nazgul_titles()
{
    return Male_Nazgul_Titles;
}

public string *
query_female_nazgul_titles()
{
    return Female_Nazgul_Titles;
}

public string *
query_sage_titles()
{
    return Sage_Titles;
}

/*
 *      Support for mage names.
 */
public mapping
query_mage_names()
{
    return Mage_Names;
}

public varargs string
query_mage_name(string name)
{
    if (!strlen(name))
        name = TP->query_real_name();
    else
        name = LOW(name);

    return Mage_Names[name];
}

/*
 * Function name: add_mage_name
 * Description:   add a mage name to the mage_names mapping
 * Arguments:     mage - the name of the mage, or an objectpointer
 *                       to the player object of the mage
 *                name - the mage name
 * Returns:       -1   - mage is not a player in the game
 *                -2   - mage is not a Morgul mage
 *                 1   - success
 *                 2   - success, but there was an old mage name
 */
public int
add_mage_name(mixed mage, string name)
{
    int     change;
    object  player;

    if (stringp(mage))
        mage = LOW(mage);
    else if (objectp(mage))
        mage = mage->query_real_name();
    else
        mage = TP->query_real_name();

    player = find_player(mage);

    if (!objectp(player))
        return -1;

    if (!IS_MORGUL_MAGE(player))
        return -2;

    if (stringp(Mage_Names[mage]))
        change = 1;

    Mage_Names[mage] = capitalize(name);
    save_object(MEMBER_LIST);

    return (1 + change);
}

public void
remove_mage_name(string name)
{
    Mage_Names = m_delete(Mage_Names, LOW(name));
    save_object(MEMBER_LIST);
}

/*
 * Security support for the idleness system. It serves as an external
 * reference for the IS selfcheck.
 */
public void incr_ISE_counter()
{
    if (previous_object() == find_object( IDLENESS ))
    {
        _Idleness_System_Error_counter++;
    }
}

public int query_ISE_counter()
{
    return _Idleness_System_Error_counter;
}

public void reset_ISE_counter()
{
    if (previous_object() == find_object( IDLENESS ))
    {
        _Idleness_System_Error_counter = 0;
    }
}

/*
 * Function name: query_sulambar_charges
 * Description  : See how much charges the mage has left for Sulambar
 *              : This function also makes sure the value is recharged.
 * Arguments    : mage - the mage to check for
 * Returns      : a number
 */
public int query_sulambar_charges(object mage)
{
	string	magename;
	int		regenerated_charges;

	// We don't work on non mages
	if(!filter_mage(mage))
		return 0;

	// Check for member, if they dont exist yet, let them start with the max
	// number of charges.
	magename = LOW(mage->query_real_name());
	if(member_array(magename, m_indices(SulambarCharges)) == -1)
		SulambarCharges[magename] = ({ mage->query_age(), MAX_SULAMBAR_CHARGES });

	// See how many charges have regenerated
	regenerated_charges = (mage->query_age() - SulambarCharges[magename][0]) / 
		SULAMBAR_REGEN_TIME;
	if(regenerated_charges > 0) 
	{
		// Reset the time to the new value
		SulambarCharges[magename][0] += (regenerated_charges * 
			SULAMBAR_REGEN_TIME);

		// Make sure we never recharge over the max charges
		if((SulambarCharges[magename][1] + regenerated_charges) > 
			MAX_SULAMBAR_CHARGES)
		{
			regenerated_charges = MAX_SULAMBAR_CHARGES - 
				SulambarCharges[magename][1];
		}

		// Add the charges
		SulambarCharges[magename][1] += regenerated_charges;

		// Store the data
		save_object(MEMBER_LIST);
	}

	return SulambarCharges[magename][1];
}

/*
 * Function name: decrease_sulambar_charge
 * Description  : Remove one of the mage's sulambar charges
 * Arguments    : mage - the object of the mage casting sulambar
 */
void decrease_sulambar_charge(object mage)
{
	string magename;

	// We don't work on non mages
	if(!filter_mage(mage))
		return 0;

	// Check for member, if they dont exist yet, let them start with the max
	// number of charges.
	magename = LOW(mage->query_real_name());
	if(member_array(magename, m_indices(SulambarCharges)) == -1)
		SulambarCharges[magename] = ({ mage->query_age(), MAX_SULAMBAR_CHARGES });

	// Substract the charge
	SulambarCharges[magename][1]--;

	// Store the data
	save_object(MEMBER_LIST);
}

/*
 * Function name: add_sulambar_charge
 * Description  : Remove one of the mage's sulambar charges
 * Arguments    : mage - the object of the mage casting sulambar
 */
void add_sulambar_charge(string magename)
{
    // This is ONLY for Guildmaster and Arches to use if testing the spell!
    // Do NOT call anything but a mage with this spell available.

    magename = lower_case(magename);
   
	// Add the charge
	SulambarCharges[magename][1]++;

	// Store the data
	save_object(MEMBER_LIST);
}

/*
 * Function name: update_mage_rank
 * Description  : Store the mage's rank into the save file (morgul_mages.o)
 *                for use at the Nazguls plaque to keep track of members
 *                ranks in times of idleness.
 * Arguments    : mage - the object of the mage
 * Returns:       -1   - mage is not a player in the game
 *                -2   - mage is not a Morgul mage
 *                 1   - success
 *                 2   - success, an update occured
 */
int update_mage_rank(object mage)
{
    string mage_name = mage->query_real_name();
    int change = 0, rank = mage->query_morgul_level();

    if (!objectp(mage))
        return -1;

    if (!IS_MORGUL_MAGE(mage))
        return -2;

    if (member_array(mage_name, m_indexes(Mage_Ranks)) > -1)
        change++;

    Mage_Ranks[mage_name] = ({ rank, time(), mage->query_gender() });
    save_object( MEMBER_LIST );

    change++;

    find_player("toby")->catch_msg("[Society] Update mage rank for: \t" +
                               "\t" +mage_name + ", rank " + (rank + 1) + 
                               ". (return "+ change + ")\n");
    return change;
}

/*
 * Function name: query_mage_rank
 * Description  : Returns the rank of a player if it has been stored
 * Arguments    : mage - the object of the mage
 * Returns:       The rank if it is listed and the month and year
 *                the rank was written/updated into the file.
 */
string query_mage_rank(string mage_name)
{
    string the_rank;
    int rank;

    mage_name = LOW(mage_name);

    if (member_array(mage_name, m_indexes(Mage_Ranks)) < 0)
        return "No rank available.";

    rank = Mage_Ranks[mage_name][0];

    if( MORGUL_I_SAGE->query_is_sage(mage_name) || rank > 24)
    {
          the_rank = "One of the Archmages (" + 
               TIME2FORMAT(Mage_Ranks[mage_name][1], "mmm yyyy")+ ")";

/*  Later, fix separate function for this when calling to read the plaque
    so that the sages do not see the hidden/under laying rank.

          if(Mage_Ranks[mage_name][2] || rank < 25)
              the_rank += "\n" + sprintf( "\t   %-27s %s", 
                      "   Hidden rank: ", query_female_titles()[rank]);
          else if(rank < 25)
              the_rank += "\n" + sprintf( "\t   %-27s %s", 
                      "   Hidden rank: ", query_male_titles()[rank]);          
*/    }
    else
       if(Mage_Ranks[mage_name][2])
          the_rank = query_female_titles()[rank] +
                     " (" + 
                     TIME2FORMAT(Mage_Ranks[mage_name][1], "mmm yyyy") + ")";
       else
          the_rank = query_male_titles()[rank] +
                     " (" + 
                     TIME2FORMAT(Mage_Ranks[mage_name][1], "mmm yyyy")+ ")";
    
    return the_rank;
}
