/*
 * The throne room of the Lord of Morgul in the Society of Morgul Mages
 *
 * This is also the council master object
 *
 * Created: Olorin, 21-jul-1994
 *
 *    Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 * Olorin, May-November 1996: general revision.
 * Gorboth, April 1999: made it possible for any Nazgul to declare
 *                        allies/enemies of Morgul
 * Chmee, August 2004: some hotfixes to demoting function to make it 'in sync'
 *                     with the idleness system
 *
 * Toby, 5 November 2006: Added mremove. Enables the Nazgul to remove a vote
 *                        they have cast. Suggested by the Nine.
 *
 * Toby, 6 November 2006: Added do_relegate for the King/Queen to use for unfit Nazgul
 *                        Added grant <mage> for the King/Queen and with this added
 *                        checks on scolls that are only for Nazgul and domain wizards.
 *                        The nazgul board was changed accordingly and now actually
 *                        do block non Nazgul players and not valid wizards.
 *                            (Tested and implemented 8 Oct)
 *
 * Toby, 29 June 2007: Fixed with the 'exa plaque' for when a sage is demoted.
 *                     Added some tell_room for examining the reports and stuff.
 *
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types2

inherit "/d/Gondor/morgul/tower/tower.c";
inherit "/d/Gondor/morgul/feeling.c";
inherit "/d/Gondor/common/lib/tail.c";

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

#define MORGUL_NAZGUL_SAVE    (MAGES_DIR + "nazgul_save")
#define MORGUL_SECURITY       (MAGES_DIR + "/log/morgul_security")
#define ME_DOMAINS            ({ "Gondor", "Mordor", "Shire" })
#define REASON_RESIGN         "Resignation"
#define REASON_RELEGATE       "Relegated by the King of Minas Morgul"
#define NULL 0
#define LORD 2
#define NAZGUL 1
#define NOT_NAZGUL 0
#define FULL_COUNCIL 9

#define HE(x)   ((x)->query_pronoun())
#define HIS(x)  ((x)->query_possessive())
#define HIM(x)  ((x)->query_objective())

public  string  list_complaints();
public  string  list_mages();
public  string  list_records();
public  string  print_votes(string which);
public  int     check_nazgul();
public  mixed demote_nazgul( string name, string reason = "unknown" ); 
mixed   promote_nazgul(string name);
void    remove_sage(mixed player);

static object On_Throne = 0;
string *Nazgul = ({}), Lord_Nazgul, *Sage = ({}), *Friends = ({ }), *Foes = ({ });
mapping Votes = ([]), Lord_Votes = ([]);

#define DEBUGT(x)            find_player("toby")->catch_msg(x + "\n");

public void create_morgul_tower_room()
{
object  board;
string  name;

    set_level( 5 );
    set_room_type( "large hall" );
    set_extra_long( "This is the throne room of the Lord of Morgul, First "+
        "Servant of Sauron, Lord of the Nazgul. In this room the Nazgul "+
        "discuss the future of the Society of the Morgul Mages and other "+
        "such matters. Prominent in the room is the throne of the King; "+
        "behind it the Kings cabinet. There is a bulletin board bolted on "+
        "the wall. Next to the board is a plaque with a list of all "+
        "Servants of the Dark Lord; below it is a small desk on which the "+
        "warden deposits reports that he receives from members of the "+
        "Society. On the other side of the board there is a scroll on "+
        "which the Nine keep some records. Standing in front of the wall "+
        "opposite of the board is a chest. A doorway to the north leads "+
        "back into the staircase at the centre of the tower, a second one "+
        "south into the library of the Nazgul." );

    add_exit( "/d/Gondor/guilds/morgulmage/rooms/tower_5c", "north", 0, 0 );
    add_exit( "/d/Gondor/guilds/morgulmage/rooms/nazgul_library", "south", check_nazgul, 0 );

    add_prop( ROOM_I_LIGHT, 1 );
    add_prop( ROOM_I_NO_CLEANUP, 1 );

    add_walls();
    add_floor();
    add_roof();
    add_item( ({ "plaque", "list" }), list_mages );
    add_cmd_item( ({ "plaque", "list" }), "read", list_mages );

    add_item( ({ "scroll", "records" }), list_records );
    add_cmd_item( ({ "scroll", "records" }), ({ "read", "tail" }),
        list_records );

    add_item( ({ "reports", "desk" }), list_complaints );
    add_cmd_item( ({ "reports" }), ({ "read", "tail" }), list_complaints );

    add_item( ({ "throne", "dais" }),
        "A black throne is raised on a dias, looking down at the doorway. "+
        "The throne is hewn from dark rock. On the sides are many bas "+
        "reliefs carved into the stone, depicting scenes of the First "+
        "Age of Middle Earth. Behind the throne is the Kings cabinet.\n" );
    add_item( ({ "reliefs", "relief", "bas reliefs", "bas relief",
        "scenes", "scene" }),
        "You run your hand admiringly over the bas relief carved into the "+
        "throne. All in all there are seven different scenes depicted.\n" );
    add_item( ({ "first bas relief", "first relief", "first scene" }),
        "The first scene depicts a horde of orcs slaughtering a group "+
        "of Laiquendi in a sylvan glade.\n" );
    add_item( ({ "second bas relief", "second relief", "second scene" }),
        "The second bas reliefs shows a Balrog dismembering a group of "+
        "terrified dwarves." );
    add_item( ({ "third bas relief", "third relief", "third scene" }),
        "This scene shows the great wolf Anfauglir ravaging Doriath.\n" );
    add_item( ({ "fourth bas relief", "fourth relief", "fourth scene" }),
        "Here Glaurung, the first of the Uruloki, the fire drakes of "+
        "the North, is routing the forces of the Quendi in the Nirnaeth "+
        "Arnoediad, the Fifth Battle of Beleriand.\n" );
    add_item( ({ "fifth bas relief", "fifth relief", "fifth scene" }),
        "Here is depicted the death of Feanor at the hands of Gothmog, "+
        "Lord of the Balrogs in the Dagor-nuin-Giliath, second of "+
        "the Battles of Beleriand.\n" );
    add_item( ({ "sixth bas relief", "sixth relief", "sixth scene" }),
        "The sixth bas relief shows the torment of Maedhros upon the peak "+
        "of Thangorodrim.\n" );
    add_item( ({ "seventh bas relief", "seventh relief", "seventh scene" }),
        "The last bas relief shows Melkor Bauglir on His Throne in "+
        "Angband wearing His Iron Crown with the three silmarils.\n" );

    setuid();
    seteuid(getuid());
/*
    if (!present( "board", this_object() ))
    {
        board = clone_object( GUILD_DIR+ "obj/nazgul_board" );
        board->move( this_object() );
    }
*/
    restore_object( MORGUL_NAZGUL_SAVE );

    clone_object( MAGES_DIR+ "obj/dagger_chest")->move( this_object(), 1 );
    clone_object( MAGES_DIR+ "obj/kings_cabinet")->move( this_object(), 1 );
    clone_object( "/d/Gondor/clubs/anghoth/obj/anghoth_admin" )->
        move( this_object(), 1 );
}

/*
 * Function name: query_nazgul
 * Description  : Return the list of the Nazgul names.
 * Returns      : Array of strings with the names.
 */
public string *query_nazgul()
{
    return ({ })+ Nazgul;
}

/*
 * Function name: query_is_nazgul
 * Description  : Is this player one of the nazgul?
 * Arguments    : name or object pointer to player.
 * Returns      : 1 or 2 - nazgul level if nazgul
 *                0 - not a nazgul
 *                -1 - error
 */
public int query_is_nazgul( mixed player )
{
    if (objectp( player ))
    {
        player = player->query_real_name();
    }
    else if (stringp( player ))
    {
        player = lower_case( player );
    }
    else
    {
        return -1;
    }
    if (player == Lord_Nazgul)
    {
        return 2;
    }
    if (member_array( player, Nazgul ) > -1)
    {
        return 1;
    }
    return 0;
}

/*
 * Function name: query_is_sage
 * Description  : Is this player a Sage, Archmage of Morgul, retired Nazgul?
 * Arguments    : name or object pointer to player.
 * Returns      : 1 - is a Sage
 *                0 - not a Sage
 *               -1 - error
 */
public int query_is_sage( mixed player )
{
    if (objectp( player ))
    {
        player = player->query_real_name();
    }
    else if (stringp( player ))
    {
        player = lower_case( player );
    }
    else
    {
        return -1;
    }

    if (member_array( player, Sage ) > -1)
    {
        return 1;
    }
    return 0;
}

/*
 * Function name: query_lord_nazgul
 * Description  : Returns the name of the Lord Nazgul
 * Returns      : the name.
 */
public string query_lord_nazgul()
{
    return Lord_Nazgul;
}

/*
 * Function name: promote_lord_nazgul
 * Description  : Promote someone to Lord of the Nazgul
 * Arguments    : name - name of the player to promote.
 * Returns      : true or string as error message if failure,
 *                or 0 if success.
 */
private mixed promote_lord_nazgul( string name )
{
 object candidate;

    if (strlen( Lord_Nazgul ))
    {
        return capitalize( Lord_Nazgul )+
            " is King of Morgul, Lord of the Nazgul!";
    }
    if (member_array( name, Nazgul ) < 0)
    {
        return "There is none of the Nazgul of that name!";
    }
    candidate = find_player( name );
    if ( (!objectp( candidate )) || (!objectp( present( candidate ))) )
    {
        return "The candidate must be present in this room!";
    }
    Lord_Nazgul = name;
    candidate->set_nazgul( LORD );
    clone_object( MAGES_DIR+ "obj/morgul_crown" )->move( candidate, 1 );
    setuid();
    seteuid( getuid() );
    save_object( MORGUL_NAZGUL_SAVE );
    write_file( MORGUL_RECORDS, "NAZGUL: "+ capitalize( name )+
        " was promoted to Lord of the Nazgul, "+ ctime( time() )+ ".\n" );
    return 0;
}

/*
 * Function name: demote_lord_nazgul
 * Description  : Demote the Lord of the Nazgul
 * Arguments    : name - the name of the Lord
 * Returns      : true or string as error msg if failure,
 *                0 if success
 */
private mixed demote_lord_nazgul( string name )
{
 object  pl, crown;
 string  vb = " was demoted ";

    if (name != Lord_Nazgul)
    {
        return capitalize( name )+ " is not Lord of the Nazgul!";
    }
    if (Lord_Nazgul == this_player()->query_real_name())
    {
        vb = " resigned ";
        this_player()->set_nazgul( NAZGUL );
    }
    else if (objectp( pl = find_player( name ) ))
    {
        pl->set_nazgul( NAZGUL );
    }
    Lord_Nazgul = 0;
    setuid();
    seteuid( getuid() );
    save_object( MORGUL_NAZGUL_SAVE );

    write_file( MORGUL_RECORDS, "NAZGUL: "+ capitalize( name )+ vb+
        "as Lord of the Nazgul! "+ ctime( time() )+ ".\n" );

    if (objectp( crown = present( MORGUL_MORGUL_CROWN, pl ) ))
    {
        pl->catch_tell( "Your "+ crown->query_short()+ " starts to glow "+
            "and then disappears.\n");   
        tell_room( this_object(), "The "+ crown->query_short()+ " of "+
            QTNAME( pl )+ " starts to glow and then disappears.\n", pl );
        crown->remove_object();
    }
    return 0;
}

/*
 * Function name: promote_nazgul
 * Description  : Promote someone to Nazgul.
 * Arguments    : name - the name of the candidate.
 * Returns      : true or string as error msg if failure, 0 if success
 */
private mixed promote_nazgul( string name )
{
 object *mages, candidate;

    if (sizeof( Nazgul ) == FULL_COUNCIL)
    {
        return "There is no ring left to create a new Nazgul!";
    }
    mages = MORGUL_MASTER->query_mages();
    if (member_array( name, mages ) == -1)
    {
        return "There is no Servant of the Dark Lord of that name!";
    }
    candidate = find_player( name );
    if (!objectp( candidate ) || !present( candidate, this_object() ))
    {
        return "The candidate must be present in this room!";
    }

    if(member_array( name, Sage ) > -1)
        Sage -= ({ name });

    Nazgul += ({ name });
    setuid();
    seteuid( getuid() );
    write_file( MORGUL_RECORDS, "NAZGUL: "+ capitalize( name )+
        " was transformed into a Nazgul, "+ ctime( time() )+ ".\n" );
    save_object( MORGUL_NAZGUL_SAVE );
    candidate->set_nazgul( NAZGUL );
    candidate->set_race_name( "wraith" );



    if (IDLENESS->add_new_nazgul( name ) == -1)
    {
        write_file( "/d/Gondor/log/bugs", ctime( time() )+ " Function add_new_nazgul() in "+
            "IDLENESS returned a failure code. (Failure code: -1)\n" );
    }
    return 0;
}


/*
 * Function name: demote_nazgul
 * Description  : Demote a Nazgul.
 * Arguments    : name   - the name of the Nazgul.
 *                reason - reason for the log.
 * Returns      : string as error msg or true if failure, 0 if success
 */
private mixed demote_nazgul( string name, string reason = "unknown" )
{
 int I_temp1, I_temp2, pot;
 object pl;

    if (member_array( name, Nazgul ) == -1)
    {
        return capitalize( name ) + " is not one of the Nazgul!\n";
    }
    
    Nazgul -= ({ name });
    if (Lord_Nazgul == name)
    {
        Lord_Nazgul = 0;
    }
    if ((sizeof( Nazgul ) < 3) && (Lord_Nazgul != 0))
    {
        STORAGE->send_message( Lord_Nazgul, "Since there was not enough "+
            "ringwraiths to support your reign you lost your crown!\n" );
        demote_lord_nazgul( Lord_Nazgul );
    }
    setuid();
    seteuid( getuid() );
    save_object( MORGUL_NAZGUL_SAVE );

    write_file( MORGUL_RECORDS, "NAZGUL: "+ capitalize( name )+
        " was demoted, reason: "+ reason+ ", "+ ctime( time() )+ ".\n" );

    if (objectp( pl = find_player( name ) ))
    {
        pl->set_nazgul( NOT_NAZGUL );
                                /*Let him or her be an Archmage           */
        I_temp1 = sizeof( MORGUL_MASTER->query_male_titles() );
        I_temp2 = pl->query_morgul_level();

        if (reason == REASON_RESIGN)
        {
            pot = I_temp1- I_temp2;
            pl->set_morgul_penalty( pl->query_morgul_penalty()+ pot );

            Sage += ({ name });

            setuid();
            seteuid( getuid() );
            save_object( MORGUL_NAZGUL_SAVE );
        }
                                /*In principle the guy (or gal) should get
                                  the rank (s)he had before ascension. It
                                  should work this way in most cases except
                                  the one when a mage was an Archmage. Since
                                  the rank of Archmage is a reward it
                                  shouldn't be assigned for someone who
                                  idled out.                              */
        else if (I_temp2 >= I_temp1)
        {
                                /*I always had problems with understanding
                                  this freaky MM penalty system. The
                                  following lines are set just 'in case'  */
            if (pl->query_morgul_penalty() >= I_temp1)
            {
                pl->set_morgul_penalty( I_temp1- 2 );
            }
            else
            {
                pl->set_morgul_penalty( pl->query_morgul_penalty()- 2 );
            }
        }
    }

    if (IDLENESS->stop_loging( name ) == -1)
    {
        write_file( "/d/Gondor/log/bugs", "Function stop_logging() in "+
            "IDLENESS returned a failure code. "+ ctime(time())+ "\n" );
    }
    pl->set_race_name( pl->query_race() );
    return 0;
}

/*
 * Function name: do_resign
 * Description  : Resign as Nazgul.
 * Arguments    : str - command line argument
 * Returns      : 1/0 - success/failure
 */
public int do_resign( string str )
{
 int nl;
 mixed result;
 object tp = this_player();
 string name = tp->query_real_name();

    str = lower_case( str );

    if ((nl = tp->query_nazgul()) < NAZGUL)
    {
        notify_fail( "You cannot resign!\n" );
        return 0;
    }

    else if (nl == NAZGUL)
    {
        if (str != "as nazgul")
        {
            notify_fail( "Do you wish to resign as Nazgul?\n" );
            return 0;
        }

        if (member_array( name, Nazgul ) < 0)
        {
            write_file( MORGUL_LOG, "ERROR: "+ capitalize( name )+
                " resigns as Nazgul, but does not hold this rank! "+
                ctime( time() )+ ".\n" );
        }
        if (result = demote_nazgul( name, REASON_RESIGN ))
        {
            if (stringp( result ))
            {
                notify_fail( result+ "\n" );
            }
            else
            {
                notify_fail( "There was a bug! Please make a bug "+
                    "report!\n" );
            }
            return 0;
        }
        write( "You resign as Nazgul!\n" );
        say( QCTNAME( tp )+ " resigns as Nazgul!\n" );
    }
    else if (nl == LORD)
    {
        if ((str != "as lord of the nazgul") && 
            (str != "as lady of the nazgul")) 
        {
            notify_fail( "Do you wish to resign as "+ 
                ((tp->query_gender() == G_FEMALE) ? "Lady" : "Lord")+
                " of the Nazgul?\n" );
            return 0;
        }
        if (name != Lord_Nazgul)
        {
            write_file( MORGUL_LOG, "ERROR: "+ capitalize( name )+
                " resigns as Lord of the Nazgul, but does not "+
                "hold this rank! "+ ctime( time() )+ ".\n" );
        }
        if (result = demote_lord_nazgul( name ))
        {
            if (stringp( result ))
                notify_fail( result+ "\n" );
            else
                notify_fail( "There was a bug! Please make a bug "+
                    "report!\n" );
            return 0;
        }
        write( "You resign as Lord of the Nazgul!\n" );
        say( QCTNAME( tp )+ " resigns as Lord of the Nazgul!\n" );
    }
    return 1;
}

/*
 * Function name: do_relegate
 * Description  : Relegate a Nazgul.
 * Arguments    : str - command line argument
 * Returns      : 1/0 - success/failure
 */
public int do_relegate( string str )
{
    int nl;
    mixed result;
    object tp = this_player();
    string victim, name = tp->query_real_name(), which, which_str = "the Nazgul";

    if ( tp->query_nazgul() < LORD )
    {
        notify_fail( "What?\n" );
        return 0;
    }

    str = lower_case( str );

    if (!strlen( str ) || (sscanf( str, "%s as %s", victim, which ) != 2))
    {
        notify_fail( "Relegate whom as Nazgul or Archmage?\n" );
        return 0;
    }

    if(!victim)
    {
        notify_fail( "Which of the Nazgul or Archamges do you desire to relegate?\n");
        return 0;
    }

    if(!which)
    {
        notify_fail( "Relegate an Archmage or a Nazgul?\n");
        return 0;
    }


    if(which == "nazgul")
    {
        if (member_array( victim, Nazgul ) == -1)
        {
            notify_fail( capitalize( victim ) + " is not one of the Nazgul!\n");
            return 0;
        }
    
        if( name == victim )
        {
            notify_fail( "You can not relegate yourself!\n");
            return 0;
        }


        if (member_array( victim, Nazgul ) < 0)
        {
            write_file( MORGUL_LOG, "ERROR: "+ capitalize( name )+
                " tried to relegate "  +capitalize( victim )+ 
                " from the Nazgul, but does not hold the power! "+
                ctime( time() )+ ".\n" );
        }


        if (result = demote_nazgul( victim, REASON_RELEGATE ))
        {
            if (stringp( result ))
            {
                notify_fail( result+ "\n" );
            }
            else
            {
                notify_fail( "There was a bug! Please make a bug "+
                    "report!\n" );
            }
            return 0;
        }
    }
    else if(which == "archmage")
    {
        if(!query_is_sage(victim))
        {
            notify_fail( capitalize( victim ) + " is not an Archmage!\n");
            return 0;
        }
        which_str = "being an Archmage";
        remove_sage(victim);
    }

    IDLENESS->increase_activity( this_player(), RELEGATE );
    write( "You relegate " +capitalize( victim )+ " from " +which_str+ "!\n" );
    say( QCTNAME( tp )+ " relegates " +capitalize( victim )+ " from " +which_str+ "!\n" );
    return 1;
}

void remove_sage(mixed player)
{
    int level, new_level, mpen, delta;
 
    if (objectp( player ))
    {
        player = player->query_real_name();
    }
    else if (stringp( player ))
    {
        player = lower_case( player );
    }

    if(!query_is_sage(player))
    {
        return;
    }

    tell_room( environment(find_player(player)), QCTNAME( find_player(player) )+ 
           " stumbles and suddenly looks weaker.\n", find_player(player) );
    find_player(player)->catch_tell( "You stumble and realize you are no longer an Archmage of Morgul!\n" );

    level = find_player(player)->query_morgul_level();
    mpen  = find_player(player)->query_morgul_penalty();

    if(find_player(player)->query_morgul_level() == 25)
    {
        delta = 2;
    }
    else if(find_player(player)->query_morgul_level() == 24)
    {
        delta = 1;
    }
    else
    {
        delta = 0;
    }

    Sage -= ({ player });

    setuid();
    seteuid( getuid() );
    save_object( MORGUL_NAZGUL_SAVE );
    find_player(player)->set_morgul_penalty( mpen - delta );
}


public int is_wizard( string name )
{
    return (SECURITY->query_wiz_rank( lower_case( name ) ) > WIZ_MORTAL );
}

/*
 * Function name: list_mages
 * Description  : Print the member list.
 * Returns      : The output.
 */
public string list_mages()
{
 int i, j;
 string str = "\n\tListed below are the Servants of the Dark Lord:\n\n"+
              "  \t(Dates represent last update of current rank.)\n\n\t"+
     "The Nine:\n",
    app_str = "",
    *mages = MORGUL_MASTER->query_mages(),
    *apprentices = ({}),
    mage_name,
    *wizards;

    if (strlen( Lord_Nazgul ))
    {
        if (member_array( Lord_Nazgul, mages ) > -1)
        {
            mage_name = MORGUL_MASTER->query_mage_name( Lord_Nazgul );
            if (!strlen( mage_name ))
            {
                mage_name = "";
            }
            else
            {
                mage_name = ", "+ mage_name;
            }
            str += ( "\t - "+ capitalize( Lord_Nazgul )+ mage_name+
               // ", Lord of the Nazgul, King of Morgul.\n" );
                ", Beleg na Nazgul, Heru na Morgul.\n" );
        }
        else
        {
            Lord_Nazgul = 0;
            setuid();
            seteuid( getuid() );
            save_object( MORGUL_NAZGUL_SAVE );
        }
    }
    j = sizeof( Nazgul );
    for (i=0;i<j;i++)
    {
        if (member_array( Nazgul[i], mages ) > -1)
        {
            if (Nazgul[i] != Lord_Nazgul)
            {
                mage_name = MORGUL_MASTER->query_mage_name( Nazgul[i] );
                if (!strlen( mage_name ))
                {
                    mage_name = "";
                }
                else
                {
                    mage_name = ", "+ mage_name;
                }
                str += ("\t - "+ capitalize( Nazgul[i])+ mage_name+
                    ", Nazgul.\n" );
            }
        }
        else
        {
            demote_nazgul( Nazgul[i], "Not a Morgul Mage" );
        }
    }

    mages -= Nazgul;
    wizards = filter( mages, is_wizard );
    mages -= wizards;
                                /*There should be no juniors on the plaque*/
    mages = filter( mages, &not() @ &wildmatch( "*jr", ) );
    j = sizeof( mages );

    str += "\n\tMages:\n";

    for (i=0;i<j;i++)
    {
        mage_name = MORGUL_MASTER->query_mage_name( mages[i] );

        if(!mage_name)
            mage_name = "";

        if (query_is_sage(mages[i]))
        {
            str += sprintf( "\t - %-24s %s", 
                      capitalize(mages[i]) + " ("+ mage_name+ ")" + ",", 
                      MORGUL_MASTER->query_mage_rank(mages[i])) + "\n";
        }        
        else if (strlen( mage_name ))
        {
            str += sprintf( "\t - %-24s %s", 
                      capitalize(mages[i]) + " ("+ mage_name+ ")" + ",", 
                      MORGUL_MASTER->query_mage_rank(mages[i])) + "\n";
        }
        else
        {
            apprentices += ({ mages[i] });
            mages[i] = 0;
        }
    }
    if (sizeof( apprentices ))
    {
        str += "\n\tApprentices:\n";

        j = sizeof( apprentices );

        for (i=0; i < j; i++)
        {
            str += sprintf( "\t - %-12s %s", 
                      capitalize(apprentices[i])+",", 
                      MORGUL_MASTER->query_mage_rank(apprentices[i])) + "\n";
        }
    }

    if(strlen(MORGUL_GUILDMASTER))
    {
        str += "\n\tImmortals:\n";
        str += "\t Guildmaster:\n";
        str += "\t  - " +capitalize(MORGUL_GUILDMASTER)+ " (Tainawath).\n";
        wizards -= ({ MORGUL_GUILDMASTER });
    }
    j = sizeof( wizards );
    for (i=0;i<j;i++)
    {
        mage_name = MORGUL_MASTER->query_mage_name( wizards[i] );
        wizards[i] = capitalize( wizards[i] );
        if (strlen( mage_name ))
        {
            wizards[i] += " ("+ mage_name+ ")";
        }
    }
    if (j != 0)
    {
        str += "\n\t Others:\n";
        str += break_string( COMPOSITE_WORDS( wizards )+ ".\n", 60,
            "\t  - " );
    }

    IDLENESS->increase_activity( this_player(), MINOR_ACTIVITY );
    tell_room(this_object(), QCTNAME(this_player()) + " studies the plaque.\n", this_player());

    return str+ "\n";
}

/*
 * Function name: list_records
 * Description  : Print the file that keeps the logs of demotions and
 *                promotions. 
 * Returns      : ""
 */
public string list_records()
{
    if (!this_player()->query_nazgul() && 
        (SECURITY->query_wiz_rank(this_player()->query_real_name()) < WIZ_NORMAL))
    {
        write( "You do not have the power to read this scroll!\n" );

        tell_room(this_object(), QCTNAME(this_player()) + " tries to access the " +
                  "scroll containg the logs of the Nazgul!\n", this_player());
        return "";
    }

    write( "You read the scroll with the records of punishments and "+
        "rewards:\n" );
    seteuid( getuid() );
    if (query_verb() == "tail")
    {
        tail_file( MORGUL_RECORDS );
    }
    else
    {
        this_player()->more( read_file( MORGUL_RECORDS, 1 ), 0 );
    }  

    IDLENESS->increase_activity( this_player(), MINOR_ACTIVITY );
    tell_room(this_object(), QCTNAME(this_player()) + " scans the scroll containg the logs of the Nazgul.\n", this_player());

    return "";
}

/*
 * Function name: list_complaints
 * Description  : Print the file with the anon complaints.
 * Returns      : ""
 */
public string list_complaints()
{
    if (!this_player()->query_nazgul() && 
        (SECURITY->query_wiz_rank(this_player()->query_real_name()) < WIZ_NORMAL))
    {
        write( "You do not have the power to investigate the reports!\n" );
        tell_room(this_object(), QCTNAME(this_player()) + " tries to access the " +
                  "reports for the Nazguls eyes only!\n", this_player());
        return "";
    }

    if (file_size( MORGUL_COMPLAINTS ) < 1)
    {
        write( "At present, there are no reports on the desk.\n" );
        return "";
    }

    write( "These are the reports that are on the desk:\n" );
    if (query_verb() == "tail")
    {
        tail_file( MORGUL_COMPLAINTS );
    }
    else
    {
        this_interactive()->more( MORGUL_COMPLAINTS, 1 );
    }

    IDLENESS->increase_activity( this_player(), MINOR_ACTIVITY );
    tell_room(this_object(), QCTNAME(this_player()) + " riffle through the pile of reports.\n", this_player());

    return "";
}

/*
 * Function name: do_check
 * Description  : Print the votes for Nazgul or for Lord.
 * Arguments    : str - command line argument.
 * Returns      : 1/0 - success/failure.
 */
public int do_check( string str )
{
 object tp = this_player();
 string which, vb = query_verb();

    str = lower_case( str );

    notify_fail( capitalize( vb )+ " votes for Nazgul or for Lord.\n" );
    if (!strlen( str ))
    {
        return 0;
    }
    if (str == "votes")
    {
        which = "nazgul";
    }
    else if (sscanf( str, "votes for %s", which ) != 1)
    {
        return 0;
    }

    if ((which != "nazgul") && (which != "lord") && (which != "king"))
    {
        return 0;
    }
    if (!tp->query_nazgul() && 
        (SECURITY->query_wiz_rank(tp->query_real_name()) < WIZ_NORMAL))
    {
        notify_fail( "You do not have the power to "+ vb+ " the votes!\n" );
        return 0;
    }

    write( print_votes( which ) );

    IDLENESS->increase_activity( this_player(), MINOR_ACTIVITY );
    return 1;
}

int do_vote( string str )
{
 object *mages;
 string name, which, voter = this_player()->query_real_name(), *voters;

    str = lower_case( str );

    if (!this_player()->query_nazgul())
    {
        notify_fail( "You do not have the power to vote!\n" );
        return 0;
    }

    notify_fail( "Vote for <candidate> for Nazgul or for Lord.\n" );
    if (!strlen( str ))
    {
        return 0;
    }
    if ((sscanf( str, "for %s", name ) == 1) &&
        sizeof( explode( name, " " ) ) == 1)
    {
        which = "nazgul";
    }
    else if (sscanf( str, "for %s for %s", name, which ) != 2)
    {
        return 0;
    }

    if (which == "nazgul")
    {
        if (sizeof( Nazgul ) == FULL_COUNCIL)
        {
            notify_fail( "There is no ring left to create a new Nazgul!\n");
            return 0;
        }
        mages = MORGUL_MASTER->query_mages();
        if (member_array( name, mages ) == -1)
        {
            notify_fail( "There is no Servant of the Dark Lord of that "+
                "name!\n" );
            return 0;
        }
        if (member_array( name, Nazgul ) > -1)
        {
            notify_fail( capitalize( name )+
                " already is one of the Nazgul!\n" );
            return 0;
        }

        if (SECURITY->query_wiz_rank( name ))
        {
            notify_fail( "A Wizard may not become one of the Nazgul!\n" );
            return 0;
        }

        Votes[voter] = name;
        setuid();
        seteuid( getuid() );
        save_object( MORGUL_NAZGUL_SAVE );
        write( "You vote for " + capitalize( name ) +
            " to become one of the Nazgul!\n" );
        say( QCTNAME( this_player() ) + " votes for " + capitalize( name )+
            " to become one of the Nazgul!\n" );
        IDLENESS->increase_activity( this_player(), 2*TYPICAL_ACTIVITY );
        return 1;
    }

    if (which == "lord")
    {
        if (Lord_Nazgul != NULL)
        {
            Lord_Votes = ([]);
            notify_fail( capitalize( Lord_Nazgul )+
                " is Lord of the Nazgul, King of Morgul!\n" );
            return 0;
        }

        if (member_array( name, Nazgul ) == -1)
        {
            notify_fail( "There is none of the Nazgul of that name and " +
                "only a Nazgul can become Lord of the Nazgul!\n" );
            return 0;
        }

        if (sizeof( Nazgul ) < 3)
        {
            notify_fail( "There must be at least three Nazgul before " +
                "there can be a vote for Lord of the Nazgul!\n" );
            return 0;
        }
/*      Why not?
        if (name == voter)
        {
            notify_fail( "You cannot cast your vote for yourself!\n" );
            return 0;
        }
*/     
        if (SECURITY->query_wiz_rank( name ))
        {
            demote_nazgul( name, "wizard" );
            notify_fail( "A Wizard may not be one of the Nazgul!\n" );
            return 0;
        }

        Lord_Votes[voter] = name;
        setuid();
        seteuid( getuid() );
        save_object( MORGUL_NAZGUL_SAVE );
        write( "You vote for " + capitalize( name )+
            " to become Lord of the Nazgul!\n" );
        say( QCTNAME(this_player() ) + " votes for " + capitalize( name )+
            " to become Lord of the Nazgul!\n" );
        IDLENESS->increase_activity( this_player(), MAJOR_ACTIVITY );
        return 1;
    }

    notify_fail( "Vote for <candidate> for Nazgul or for Lord.\n" );
    return 0;
}

/*
 * Function name: do_remove_vote
 * Description  : Removes the vote of a Nazgul for a new Nazgul or Lord
 * Returns      : 1/0, success/failure
 */
int do_remove_vote( string str )
{
 string which, voter = this_player()->query_real_name(), *voters;

    str = lower_case( str );

    if (!this_player()->query_nazgul())
    {
        notify_fail( "You do not have the power to vote or remove votes!\n" );
        return 0;
    }

    notify_fail( "Remove vote for Nazgul or for Lord.\n" );
    if (!strlen( str ))
    {
        return 0;
    }


    if ( sscanf( str, "vote for %s", which) == 1 )
    {

       voters = m_indexes( Votes );

       if (which == "nazgul")
       {
           if (member_array( voter, voters ) == -1)
           {
               notify_fail( "You have not cast a vote for Nazgul!\n" );
               return 0;
           }

           Votes = m_delete(Votes, voter);
           setuid();
           seteuid( getuid() );
           save_object( MORGUL_NAZGUL_SAVE );
           write( "You remove your vote for Nazgul!\n" );
           say( QCTNAME( this_player() ) + " removes " +HIS_HER(this_player())+ 
               " vote for Nazgul!\n" );
           IDLENESS->increase_activity( this_player(), 2*TYPICAL_ACTIVITY );
           return 1;
       }

       voters = m_indexes( Lord_Votes );

       if (which == "lord")
       {

           if (Lord_Nazgul != NULL)
           {
               Lord_Votes = ([]);
               notify_fail( capitalize( Lord_Nazgul )+
                   " is Lord of the Nazgul, King of Morgul!\n" );
               return 0;
           }

           if (member_array( voter, voters ) == -1)
           {
               notify_fail( "You have not cast a vote for Lord Nazgul!\n" );
               return 0;
           }


           Lord_Votes = m_delete(Lord_Votes, voter);
           setuid();
           seteuid( getuid() );
           save_object( MORGUL_NAZGUL_SAVE );
           write( "You remove your vote for Lord of the Nazgul!\n" );
           say( QCTNAME( this_player() ) + " removes " +HIS_HER(this_player())+ 
               " vote for Lord of the Nazgul!\n" );
           IDLENESS->increase_activity( this_player(), 2*TYPICAL_ACTIVITY );
           return 1;
       }

    }
    notify_fail( "Remove vote for Nazgul or for Lord.\n" );
    return 0;
}

/*
 * Function name: check_votes
 * Description  : This function apparently has something with the arrays
 *                mapping Votes and Lord_Votes
 * Arguments    : Apparently a string. Either "nazgul" or "lord".
 * Return values: string - winner of the voting or 0 in the case of negative
 *                answer.
 */
varargs mixed check_votes( string which )
{
 int i, j, n, max = 0;
 string *voted, winner;
 mapping names = ([ ]);

    if (!strlen( which ))
    {
        which = "nazgul";
    }
    
    if (which == "nazgul")
    {
        voted = m_values( Votes );
    }
    else if (which == "lord")
    {
        if (sizeof( Nazgul ) < 3)
        {
            return 0;
        }
        voted = m_values( Lord_Votes );
    }
    else
    {
        return 0;
    }

    j = sizeof( voted );
    for (i=0;i<j;i++)
    {
        if (names[voted[i]])
        {
            if (++names[voted[i]] > max)
            {
                max = names[voted[i]];
            }
        }
        else
        {
            names += ([ voted[i] : 1 ]);
            if (max <= 0)
            {
                max = 1;
            }
        }
    }

    if (max > (sizeof( Nazgul )/ 2))
    {
        while (m_sizeof( names ))
        {                        /*English purists may prefer using
                                  *m_indices() instead of m_indexes. ;-)  */
            if (names[winner = m_indexes( names )[0]] < max)
            {
                names = m_delete( names, winner );
            }
            else
            {
                return winner;
            }
        }
    }
    return 0;
}

/*
 * Function name: print_votes
 * Description  : Apart from printing the votes out this function removes
 *                all votes that weren't cast by nazgul present in
 *                the Nazgul array.
 * Arguments    : string which - can be either "nazgul" or "lord"/"king"
 * Return values: The string with fine printing of who voted for whom
 */
string print_votes( string which )
{
 int i, sn = sizeof( Nazgul ), sv;
 string *voters, str ="", winner, mark;

    if (!strlen( which ))
    {
        which = "nazgul";
    }
    if (which == "nazgul")
    {
        str = "\n\tThere "+ (sn == 1 ? "is ":"are ")+ LANG_WNUM( sn )+
            " Nazgul!\n";
        if (sn == FULL_COUNCIL)
        {
            str +=
                "\tThere are only nine rings for mortals doomed to die!\n"+
                "\tWithout a ring to spare, there can be no new Nazgul!\n";
            return str+ "\n";
        }
        else if (sn == 8)
            str +=
                "\tThere are nine rings for mortals doomed to die!\n"+
                "\tSo there is one ring left to create new a Nazgul!\n";
        else
            str +=
                "\tThere are nine rings for mortals doomed to die!\n"+
                "\tSo there are "+ LANG_WNUM( FULL_COUNCIL- sn )+
                " rings left to create new Nazgul!\n";

        voters = m_indexes( Votes );
        sv = sizeof( voters );
                                /*Check if all those who voted are still
                                 *Nazgul!                                 */
        for (i=0;i<sv;i++)
        {
            if (member_array( voters[i], Nazgul ) == -1)
            {
                Votes = m_delete( Votes, voters[i] );
                setuid();
                seteuid( getuid() );
                save_object( MORGUL_NAZGUL_SAVE );
            }
        }
        
        voters = m_indexes( Votes );
        if (sizeof( voters ) == 0)
        {
            return (str+ "\n"+ "\tThere have been no votes cast yet!\n\n" );
        }
        str += "\n\tThe following votes have been cast:\n";
        winner = (string)check_votes( which );
        sv = sizeof( voters );
        for (i=0;i<sv;i++)
        {
            if (winner == Votes[voters[i]])
            {
                mark = "*";
            }
            else
            {
                mark = "";
            }
            str += sprintf( "\t%-12s voted for %1s %-12s\n",
                capitalize( voters[i] ), mark,
                capitalize( Votes[voters[i]] ) );
        }
        if (strlen( winner ))
        {
            str += "\n\t"+ capitalize( winner )+
                " has sufficient votes to be promoted to Nazgul!\n";
            if (IDLENESS->is_idle( winner ))
            {
                str += "\tThe Dark Lord, however, may have some doubts "+
                    "and unless\n\t"+ capitalize( winner )+ " bears the "+
                    "honorary title of the Archmage of Morgul\n\tyour "+
                    "request will be rejected.\n" +
                    "\tWith the power of the Black Master flowing through you,\n\t" +
                    "feeling the bond, you feel certain however that in time\n\t" + 
                    capitalize( winner )+ " will regain the trust of Him.\n\n";
            }
        }
        return str+ "\n";
    }

    else if ((which == "lord") || (which == "king"))
    {
        if (strlen( Lord_Nazgul ))
        {
            str = "\n\t"+ capitalize( Lord_Nazgul )+
                " is Lord of the Nazgul and King of Morgul!\n";
            return str+ "\n";
        }
        str = "\n\tThere "+ (sn == 1 ? "is ":"are ")+ LANG_WNUM( sn )+
            " Nazgul!\n";
        if (sn < 3)
        {
            str +=
                "\tThere must be at least three Nazgul before it is\n"+
                "\tpossible to vote for the Lord of the Nazgul!\n";
            return str+ "\n";
        }

        voters = m_indexes( Lord_Votes );
        sv = sizeof( voters );
                                /*Check if all those who voted are still
                                 *Nazgul!                                 */
        for (i=0;i<sv;i++)
        {
            if (member_array( voters[i], Nazgul ) == -1)
            {
                Lord_Votes = m_delete( Lord_Votes, voters[i] );
                setuid();
                seteuid( getuid() );
                save_object( MORGUL_NAZGUL_SAVE );
            }
        }
        
        voters = m_indexes( Lord_Votes );
        if (sizeof( voters ) == 0)
        {
            return ( str+ "\n\tThere have been no votes cast yet!\n\n" );
        }
        str += "\n\tThe following votes have been cast:\n";
        winner = (string)check_votes( which );
        sv = sizeof( voters );
        for (i=0;i<sv;i++)
        {
            if (winner == Lord_Votes[voters[i]])
                mark = "*";
            else
                mark = "";
            str += sprintf("\t%-12s voted for %1s %-12s\n",
                capitalize( voters[i] ), mark,
                capitalize( Lord_Votes[voters[i]] ) );
        }
        if (strlen( winner ))
        {
            str += "\n\t"+ capitalize( winner )+ " has sufficient votes "+
                "to be promoted to Lord of the Nazgul!\n";
        }
        return str+ "\n";
    }
    return 0;
}

int do_promote( string str )
{
 int nl;
 mixed result;
 object tp = this_player(), mage;
 string vb = query_verb(), name, which;

    str = lower_case( str );

    if (!strlen( str ) || (sscanf( str, "%s to %s", name, which ) != 2))
    {
        notify_fail( capitalize( vb )+ " whom to Nazgul or Lord?\n" );
        return 0;
    }

    if (!(nl = tp->query_nazgul()))
    {
        notify_fail( "You do not have the power to "+ vb+ " anyone to "+
            capitalize( which )+ "!\n" );
        return 0;
    }

    if (sizeof( Nazgul ) == FULL_COUNCIL)
    {
        notify_fail( "There is no ring left to create a new Nazgul!\n" );
        return 0;
    }

    if ((which == "nazgul") && (strlen( Lord_Nazgul )) && (nl < LORD))
    {
        notify_fail( "Only the Lord of the Nazgul may promote a Servant "+
            "of the Dark Lord to Nazgul!\n" );
        return 0;
    }

    mage = find_living( name );
    if (!objectp( mage ) || (mage->query_guild_name_occ() != GUILD_NAME))
    {
        notify_fail( "There is no Servant of the Dark Lord of that name "+
            "in this world!\n" );
        return 0;
    }
    
    if (!present( mage, this_object() ))
    {
        notify_fail( "The candidate must be present in this room!\n" );
        return 0;
    }
/*
    if (IDLENESS->is_idle( mage ) && mage->query_morgul_level() !=
        sizeof( MORGUL_MASTER->query_male_titles() ))
    {
        notify_fail( capitalize( mage->query_real_name() )+
            " didn't regain the trust of the Dark Lord yet!\n" );
        return 0;
    }
*/
    if (which == "nazgul")
    {
        if (name != (string)check_votes( which ))
        {
            notify_fail( capitalize( name )+ " does not have the "+
                "approval of the Dark Lord!\n\tCheck the votes!\n" );
            return 0;
        }

        if ((result = promote_nazgul( name )))
        {
            if (stringp( result ))
            {
                notify_fail( result+ "\n");
            }
            else
            {
                notify_fail( "There was a bug! "+
                    "Please make a bug report!\n" );
            }
            return 0;
        }
        write( "You advance "+ capitalize( name )+
            " into the rank of a Nazgul!\n" );
        tell_room( this_object(), QCTNAME( this_player() )+ " transforms "+
            QTNAME( mage )+ " into a nazgul!\n",
            ({ this_player(), mage, }) );
        mage->catch_tell( "You have been transformed into a Nazgul by "+
            this_player()->query_name()+ ", "+
            this_player()->query_guild_title_occ()+ "!\n" );
        Votes = ([]);
        IDLENESS->increase_activity( this_player(), REWARD );
    }
    else if (which == "lord")
    {
        if (name != (string)check_votes( which ))
        {
            notify_fail( capitalize( name )+ " does not have the approval "+
                "of the Dark Lord!\n\tCheck the votes!\n" );
            return 0;
        }

        if (result = promote_lord_nazgul( name ))
        {
            if (stringp( result ))
            {
                notify_fail( result+ "\n" );
            }
            else
            {
                notify_fail( "There was a bug! Please make a bug "+
                    "report!\n" );
            }
            return 0;
        }
        write( "You promote "+ capitalize( name )+ " to the Lord of the "+
            "Nazgul!\n" );
        if (this_player() != mage)
        {
            mage->catch_tell( "You have been promoted to Lord of the "+
                "Nazgul by "+ this_player()->query_name()+ ", "+
                this_player()->query_guild_title_occ()+ "!\n"+
                "As sign of your rank you receive the Crown of Morgul.\n" );
        }
        Lord_Votes = ([]);
        IDLENESS->increase_activity( this_player(), REWARD );
    }
    else
    {
        notify_fail( capitalize( vb )+ " whom to Nazgul or Lord?\n" );
        return 0;
    }
    setuid();
    seteuid( getuid() );
    save_object( MORGUL_NAZGUL_SAVE );
    return 1;
}

/*
 * Function name: demote_nazgul_alarm
 * Description  : This is called from second_life in the shadow.
 * Arguments    : name - the name of the nazgul to demote
 *                reason - reason for the log
 */
public void demote_nazgul_alarm( string name, string reason = "unknown" )
{
 int i = 1;
 object ob;
 string str;
/*
    str = calling_function();

    if (((("/" + calling_program()) != (MAGES_DIR + "morgul_shadow.c")) ||
        ((str != "second_life") && (str != "force_leave_nazgul"))) &&
        (((("/" + calling_program()) != (MAGES_DIR + "idleness.c"))) ||
        (str != "screen_nazgul")) || 
        ((("/" + calling_program()) != ("/d/Gondor/guilds/morgulmage/mage_shadow.c")) ||
        ((str != "second_life") && (str != "force_leave_nazgul"))) ||
        (("/" + calling_program()) != ("/d/Gondor/guilds/morgulmage/master/master.c")))
    {
        str = "";
        while (objectp( ob = calling_object( --i ) ))
        {
            str += file_name( ob )+ ", "+ calling_program( i )+
                ", "+ calling_function( i )+ ".\n";
        }
        log_file( "debug", ctime( time() )+ ", "+
            calling_object( 0 )->query_name()+ ":\n"+ str );
    }
    else
    { */
        set_alarm( 0.0, 0.0, &demote_nazgul( name, reason ) );
//    }
}

public int check_nazgul()
{
    if (this_player()->query_nazgul() || this_player()->query_wiz_level())
    {
        return 0;
    }
    write( "Only nazgul are permitted to enter the library!\n" );
    return 1;
}

public int query_friend_or_foe( object pl )
{
 string name = pl->query_real_name();

    if (member_array( name, Friends ) > -1)
    {
        return -1;
    }
    if (member_array( name, Foes ) > -1)
    {
        return  1;
    }
    return 0;
}

void leave_inv( object ob, object to )
{
    ::leave_inv( ob, to );

    if (!objectp( ob ))
    {
        return;
    }
    if (living( ob ) && ob->query_prop( "_On_Throne" ))
    {
        write( "You rise from your Dark Throne.\n" );
        say( QCTNAME( ob )+ " rises from the Dark Throne.\n" );
        ob->remove_prop( LIVE_S_EXTRA_SHORT );
        ob->remove_prop( "_On_Throne" );
        On_Throne = 0;
    }
}

public void enter_inv( object ob, object from )
{
 int wizrank;
 string  name;

    ::enter_inv( ob, from );

    if (!objectp( ob ) || !interactive( ob ))
    {
        return;
    }
    name = ob->query_real_name();
    if (!(wizrank = SECURITY->query_wiz_rank( name )))
    {
        return;
    }
    if (member_array( SECURITY->query_wiz_dom( name ), ME_DOMAINS ) >= 0)
    {
        return;
    }
    if (wizrank > WIZ_NORMAL)
    {
        return;
    }

    log_file(MORGUL_SECURITY, capitalize( name )+ " tried to enter "+
        "the Throne room on: "+ ctime( time() )+ ".\n" );
    ob->catch_tell( "You are not welcome here.\n" );
    set_alarm( 0.0, 0.0, &ob->move_living( "back", from ) );
}


/**************************************************************
 *    Commands enabled by init()                              *
 **************************************************************/

int do_sit( string str )
{
 object  tp = this_player();

    if (!str)
    {
        notify_fail( "Sit where?\n" );
        return 0;
    }
    if (str != "throne" && str != "on throne")
    {
        notify_fail( "Sit on the throne, perhaps?\n" );
        return 0;
    }

    if (tp->query_prop( "_On_Throne" ))
    {
        notify_fail( "But you are already sitting on the throne!\n" );
        return 0;
    }

    if (objectp( On_Throne ))
    {
        if (!present( On_Throne, this_object() ) ||
            !(On_Throne->query_prop( "_On_Throne" )))
        {
            On_Throne->remove_prop( "_On_Throne" );
            On_Throne = 0;
        }
        else
        {
            notify_fail( QCTNAME( On_Throne )+
                " is already sitting on the throne!\n" );
            return 0;
        }
    }

    if (tp->query_nazgul() < LORD)
    {
        write( "As you lower yourself to the Dark Throne, the gaze of the "+
            "Red Eye falls upon you, and you quickly rise again.\n" );
        say( QCTNAME( tp )+ " tries to sit on the Dark Throne, but "+
            HE( tp )+ " quickly rises again, trembling for fear.\n" );
        return 1;
    }

    write( "You sit down on your throne.\n" );
    say( QCTNAME( tp )+ " sits down on "+ HIS(tp)+ " Dark Throne.\n", tp );
    On_Throne = tp;
    tp->add_prop( "_On_Throne", 1 );
    tp->add_prop( LIVE_S_EXTRA_SHORT, ", sitting on "+ HIS( tp )+
        " Dark Throne" );
    IDLENESS->increase_activity( this_player(), EMOTION );
    return 1;
}

int do_rise( string str )
{
 object tp = this_player();
 string vb = query_verb();

    if (vb == "stand" && str != "up")
    {
        notify_fail( capitalize( vb )+ " what? Up?\n" );
        return 0;
    }

    if (!tp->query_prop( "_On_Throne" ) && On_Throne != tp)
    {
        notify_fail( "But you are not sitting on the throne!\n" );
        return 0;
    }
 
    write( "You rise from your Dark Throne.\n" );
    say( QCTNAME( tp )+ " rises from "+ HIS( tp )+ " Dark Throne.\n", tp );
    tp->remove_prop( "_On_Throne" );
    tp->remove_prop( LIVE_S_EXTRA_SHORT );
    On_Throne = 0;
    return 1;
}

int do_recline( string str )
{
 object tp = this_player();

    if (tp != On_Throne)
    {
        return 0;
    }
    write( "You recline thoughtfully upon your Throne.\n" );
    say( "The Lord of the Nazgul reclines thoughtfully upon "+
        HIS( On_Throne )+ " Dark Throne.\n" );
    IDLENESS->increase_activity( this_player(), EMOTION );
    return 1;
}

int do_inspect( string str )
{
 object tp = this_player(), *objs, *live, *dead;

    if (tp != On_Throne)
    {
        return 0;
    }
    if (!str)
    {
        notify_fail( "Inspect what?\n" );
        return 0;
    }

    if (!parse_command( str, this_object(), "%l", objs ))
    {
        notify_fail( "You cannot find any "+ str+ " here.\n" );
        return 0;
    }

    objs = NORMAL_ACCESS( objs, 0, 0 );
    objs -= ({ tp });
    if (!sizeof( objs ))
    {
        notify_fail( "You cannot find any "+ str+ " here.\n" );
        return 0;
    }

    write( "You sit forward on your throne, inspecting "+
        COMPOSITE_LIVE( objs )+ " carefully.\n" );
    objs->catch_tell( "The Lord of the Nazgul sits forward on "+
        HIS( On_Throne )+ " Dark Throne, scrutinizing you carefully.\n" );
    say( "The Lord of the Nazgul sits forward on "+ HIS( On_Throne )+
        " Dark Throne, inspecting "+ COMPOSITE_LIVE( objs )+
        " carefully.\n", ({ tp })+ objs );
    IDLENESS->increase_activity( this_player(), EMOTION );
    return 1;
}

int do_grant( string str )
{
    object  tp = this_player();
    object  mage;

    if ( tp->query_nazgul() < LORD )
    {
        notify_fail( "What?\n" );
        return 0;
    }

    if ( !str )
    {
        notify_fail( "Grant what Mage access to the Throne Room?\n" );
        return 0;
    }

    mage = find_player(lower_case(str));

    if ( !mage )
    {
        notify_fail( "Grant what Mage access to the Throne Room?\n" );
        return 0;
    }

    if(mage->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        notify_fail( "There is no use in granting a mere Apprentice access " +
           "to your throne room. it can not reach the upper levels of the Tower!\n" );
        return 0;
    }

    write_file( MORGUL_RECORDS, this_player()->query_name()+ " grants "+
        mage->query_name()+ " access to " +HIS_HER(mage)+ " throne room "+
        " ("+ ctime( time() )+ ").\n" );

    write( "You grant " +mage->query_name()+ " access to your throne room!\n" );
    mage->add_prop( MORGUL_S_THRONE_GRANT, 1 );
    IDLENESS->increase_activity( this_player(), EMOTION );
    return 1;
}


/*
 * Function name: do_declare
 * Description  : declare a player to be friend or foe of Minas Morgul
 * Arguments    : string arg - the command argument:
 *                declare <name> to be <friend|foe> of morgul
 * Returns      : 1/0
 */
public int do_declare( string arg )
{
 string name, what, reason, msg;

    if (this_player()->query_nazgul() < NAZGUL || !arg)
    {
        notify_fail( "Only one of the Nine may declare someone to be "+
            "a friend or foe of Minas Morgul!\n");
        return 0;
    }

    if (this_player()->query_nazgul() < NAZGUL)
    {
        notify_fail( "Only one of the Nine may declare someone to be "+
            "a friend or foe of Minas Morgul!\n");
        return 0;
    }

    if (!strlen( arg ) || !parse_command( lower_case( arg ), ({ }), 
        "%w 'to' 'be' %s 'of' [the] [dark] [minas] 'morgul' / 'lord' "+
        "'because' %s", name, what, reason ))
    {
        notify_fail( "Syntax: Declare <name> to be <friend|foe|beneath "+
            "notice> of Minas Morgul because <reason>\n" );
        return 0;
    }
    write( "Name: "+ name+ ", what: "+ what+ "\n" );
    switch (what)
    {
    case "friend":
    case "ally":
        if (!SECURITY->exist_player( name ))
        {
            notify_fail( "You have never heard about anyone of the name "+
                capitalize( name )+ "!\n" );
            return 0;
        }
        if (member_array( name, MORGUL_MASTER->query_mages() ) > -1)
        {
            notify_fail( capitalize( name )+ " is a member of the Society "+
                "of Morgul Mages!\nYou cannot declare a member of the "+
                "Society as "+ what+ " of Minas Morgul!\n" );
            return 0;
        }
        Friends += ({ name });
        msg = LANG_ADDART( what );
        break;
    case "foe":
    case "enemy":
        if (!SECURITY->exist_player( name ))
        {
            notify_fail( "You have never heard about anyone of the name "+
                capitalize( name )+ "!\n" );
            return 0;
        }

        if (member_array( name, MORGUL_MASTER->query_mages() ) > -1)
        {
            notify_fail( capitalize( name )+ " is a member of the Society "+
                "of Morgul Mages!\nYou cannot declare a member of the "+
                "Society as "+ what+ " of Minas Morgul!\n" );
            return 0;
        }
        Foes += ({ name });
        msg = LANG_ADDART( what );
        break;
    case "worthless":
    case "beneath notice":
                                /*The King can remove any name from
                                 *the lists.                              */
        Friends -= ({ name });
        Foes -= ({ name });
        msg = what;
        break;
    default:
        notify_fail(" Syntax: Declare <name> to be <friend|foe|beneath "+
            "notice> of Minas Morgul\n" );
        return 0;
    }    

    write( "You declare "+ capitalize( name )+ " to be "+ msg+
        " of Minas Morgul!\n" );
    say( QCTNAME( this_player() )+ " declares "+ capitalize( name )+
        " to be "+ msg+ " of Minas Morgul!\n" );

    write_file( MORGUL_RECORDS, this_player()->query_name()+ " declares "+
        capitalize( name )+ " to be "+ msg+ " of Minas Morgul because "+
        reason+ " ("+ ctime( time() )+ ").\n" );
    IDLENESS->increase_activity( this_player(), MAJOR_ACTIVITY );
    setuid();
    seteuid( getuid() );
    save_object( MORGUL_NAZGUL_SAVE );
    return 1;
}

/*
 * Function name: do_list
 * Description  : list the names of the players declared
 *                friend or foe of Minas Morgul
 * Arguments    : string arg - the command argument:
 *                list <friend|foe>
 * Returns      : 1/0
 */
public int do_list( string arg )
{
    switch (arg)
    {
    case "friends":
    case "friend":
    case "allies":
    case "ally":
        if (!sizeof( Friends ))
        {
            write( "\tFeared be the Dark Lord!\n"+
                "\tNone have been declared to be His allies!\n" );
        }
        else
        {
            write( break_string( "These are the names of those who have "+
                "been declared to be allies of the Dark Lord and of "+
                "Minas Morgul:\n", 50, "\t" )+ 
                break_string( COMPOSITE_WORDS( map( Friends, capitalize ) )+
                ".\n", 50, "\t" ) );
        }
        break;
    case "enemies":
    case "enemy":
    case "foes":
    case "foe":
        if (!sizeof( Foes ))
        {
            write("\tPraised be the Dark Lord!\n"+
                "\tNone have been declared to be His enemies!\n");
        }
        else
        {
            write( break_string( "These are the names of those who have "+
                "been declared to be foes of the Dark Lord and of "+
                "Minas Morgul:\n", 50, "\t" )+ 
                break_string( COMPOSITE_WORDS( map( Foes, capitalize ) )+
                ".\n", 50, "\t" ) ); 
        }
        break;
    case "all":
    case "friends and foes":
        do_list( "friends" );
        do_list( "foes" );
        break;
    default:
        notify_fail( "Syntax: List <friends|foes>\n" );
        return 0;
    }
    IDLENESS->increase_activity( this_player(), MINOR_ACTIVITY );
    return 1;
}

public void init()
{
    ::init();

    add_action( do_vote,        "vote" );
    add_action( do_remove_vote, "mremove" );
    add_action( do_check,       "check" );
    add_action( do_check,       "read" );
    add_action( do_promote,     "promote" );
    add_action( do_resign,      "resign" );
    add_action( do_declare,     "declare" );
    add_action( do_list,        "list" );
    // For the King/Queen:
    add_action( do_sit,         "sit" );
    add_action( do_rise,        "stand" );
    add_action( do_rise,        "rise" );
    add_action( do_recline,     "recline" );
    add_action( do_inspect,     "inspect" );
    add_action( do_relegate,    "relegate" );
    add_action( do_grant,       "grant" );
}



/****************************************************
 *                 WIZARDS FUNCTIONS                *
 *                                                  *
 *  (Remember to set to private when done testing)  *
 ***************************************************/
void create_sage(mixed player)
{
    if (objectp( player ))
    {
        player = player->query_real_name();
    }
    else if (stringp( player ))
    {
        player = lower_case( player );
    }

    if(query_is_sage(player))
    {
        write("But " +capitalize( player )+ " is already an Archmage of Morgul!\n");
        return;
    }

    write( "You make " +capitalize( player )+ " an Archmage of Morgul!\n" );
    tell_room( this_object(), QCTNAME( this_player() )+ " makes " +
           capitalize( player )+ " an Archmage of Morgul!\n",
            ({ this_player(), find_player(player), }) );
    find_player(player)->catch_tell( "You have been made an Archmage of Morgul!\n" );

    Sage += ({ player });

    setuid();
    seteuid( getuid() );
    save_object( MORGUL_NAZGUL_SAVE );
}


void remove_sage_admin(mixed player)
{
    if (objectp( player ))
    {
        player = player->query_real_name();
    }
    else if (stringp( player ))
    {
        player = lower_case( player );
    }

    if(member_array( player, Sage ) > -1)
    {
	    write( "You remove " +capitalize( player )+ " from the ranks of the Archmages of Morgul!\n" );
	    tell_room( this_object(), QCTNAME( this_player() )+ " removes " +
	           capitalize( player )+ " from the ranks of the Archmages of Morgul!\n",
	            ({ this_player(), find_player(player), }) );
	    find_player(player)->catch_tell( "You have been removed from the ranks of the Archmages of Morgul!\n" );
	
	    Sage -= ({ player });
	
	    setuid();
	    seteuid( getuid() );
	    save_object( MORGUL_NAZGUL_SAVE );
    }
    else
    {
        write("But " +capitalize( player )+ " is not an Archmage of Morgul!\n");
        return;
    }
}

private mixed create_nazgul(string who)
{
    mixed result;

    result = promote_nazgul(who);
    return result;
}

void add_nazgul(string who)
{
    Nazgul += ({ who });
}

void add_lord_nazgul(string who)
{
   Lord_Nazgul = who;
	    setuid();
	    seteuid( getuid() );
	    save_object( MORGUL_NAZGUL_SAVE );
}
