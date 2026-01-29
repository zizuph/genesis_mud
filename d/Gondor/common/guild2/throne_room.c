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
 * Eowul, 18 July 2009: Made a temporary copy to log calls to this object and pass 
 *                      them to the new guilds control object.
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
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
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

    add_prop( ROOM_I_LIGHT, 1 );
    add_prop( ROOM_I_NO_CLEANUP, 1 );

    add_walls();
    add_floor();
    add_roof();

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

public void log_obsolete_call()
{
    log_file("mage_obsolete", sprintf("throneroom/%O called by %O/%O\nInteractive: %s\n", 
        calling_function(), calling_object(-1), calling_function(-1),
        (objectp(this_interactive()) ? this_interactive()->query_real_name() : "") ), -1);
}

/*
 * Function name: query_nazgul
 * Description  : Return the list of the Nazgul names.
 * Returns      : Array of strings with the names.
 */
public string *query_nazgul()
{
    log_obsolete_call();
    return MORGUL_MASTER->query_nazgul_names();
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
    log_obsolete_call();
    return MORGUL_MASTER->query_is_nazgul(player);
    /*
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
    */
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
    log_obsolete_call();
    return MORGUL_MASTER->query_lord_nazgul();
    //return Lord_Nazgul;
}

/*
 * Function name: demote_nazgul_alarm
 * Description  : This is called from second_life in the shadow.
 * Arguments    : name - the name of the nazgul to demote
 *                reason - reason for the log
 */
public void demote_nazgul_alarm( string name, string reason = "unknown" )
{
    log_obsolete_call();
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
//        set_alarm( 0.0, 0.0, &demote_nazgul( name, reason ) );
//    }
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

public int query_friend_or_foe( object pl )
{
    log_obsolete_call();
    return MORGUL_MASTER->query_friend_or_foe(pl);
}