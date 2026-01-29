/*
 *    /d/Gondor/ithilien/emyn-arnen/obj/scabbard
 *
 *    Copyright (c) 1997 by Christian Markus
 *
 *     Part of the reward for solving the Battlestandard quest.
 *
 *    Olorin
 *
 *    Modification log:
 *    22-Feb-97, Olorin : Added logging.
 *    13-Apr-98, Gnadnar: Mask enter_env(), similar to current
 *               mask of leave_env().
 *    31-May-01, Chmee  : Added support for MM narusse spell.
 *
 *    September 2002, Modified by Finwe as a common leather scabbard 
 *    for swords, sold in a leather shop. The scabbard does not reload, 
 *    have any magical capabilities, and can be stolen. Thanks to Gondor!
 *
 *    11-Jul-11, Lavellan: Fixed value.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container.c";

#include "/d/Shire/cypress/sys/defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define SCABBARD_SUBLOC   "_faerie_scabbard_subloc"
#define WEAPONS_O_OWNER   "_weapons_o_owner"
#define SCABBARD          (OBJ_DIR + "sh_scab_s.c")

static object  Worn = 0;

public void
create_container()
{
    setuid(); seteuid(getuid());

    set_name( "scabbard" );
    add_name( "_faerie_scabbard" );
    set_short( "leather scabbard" );
    set_adj( ({"tooled", "leather"}) );
    set_long( "A tooled leather scabbard. It is designed to hold a " +
        "sword when the weapon is not in use. The tooling is expertly " +
        "done along the edges of both sides of the scabbard. Inside " +
        "the scabbard is a leather label.\n" );

    add_item(({"label", "leather label"}), "It is sewn inside scabbard. " +
        "There are some words on it.\n");
    add_cmd_item(({"words", "label", "leather label", "instructions"}),
        "read", "@@read_label@@");

    add_prop( CONT_I_WEIGHT,  2000 );
    add_prop( CONT_I_VOLUME,  2000 );
    add_prop( CONT_I_MAX_WEIGHT, 50000 );
    add_prop( CONT_I_MAX_VOLUME, 25000 );
    add_prop( CONT_I_TRANSP, 1 );
    add_prop( CONT_I_RIGID,  0 );
//    add_prop(OBJ_I_VALUE,300 + random(70));
    add_prop(OBJ_I_VALUE, 150 );
    add_prop( CONT_M_NO_INS, "You may sheathe a sword when the " +
        "weapon is not in use.\n" );
}

static int
filter_weapon( object x )
{
    return (function_exists( "create_object", x ) == "/std/weapon");
}

static int
filter_sword( object x )
{
    return (x->query_wt() == W_SWORD);
}

public int
do_sheathe( string str )
{
 int     result;
 object *sword;

//    tp = this_player();
    
    if (!str)
    {
        sword = TP->query_weapon( -1 );
    }
    else
    {
//        sword = filter( FIND_STR_IN_OBJECT( str, tp ), "filter_weapon",
        sword = filter( FIND_STR_IN_OBJECT( str, TP ), "filter_weapon",
            this_object() );
    }
    sword = filter( sword, "filter_sword", this_object() );

    if (sizeof( sword ) != 1)
    {
        notify_fail( "Sheathe which sword?\n" );
        return 0;
    }

    if (sizeof( all_inventory( this_object() ) ))
    {
        notify_fail( "You cannot sheathe your "+ sword[0]->short()+
        ", there is already "+ LANG_ASHORT(all_inventory(this_object())[0])+
        " in the "+ short()+ ".\n" );
        return 0;
    }

    if ( sword[0]->query_wielded() == TP )
    {
        sword[0]->unwield_me();
        if ( sword[0]->query_wielded() == TP )
        {
            notify_fail( "You cannot unwield your "+
                sword[0]->short()+ ".\n" );
               return 0;
        }
    }

    remove_prop( CONT_M_NO_INS );
    if (result = sword[0]->move( this_object() ))
    {
        switch (result)
        {
        case 1:
            notify_fail( "Your "+ sword[0]->short()+ " is too heavy for "+
            "the "+ short()+ ".\n" );
            break;
        case 8:
            notify_fail( "Your "+ sword[0]->short()+ " is too large for "+
            "the "+ short()+ ".\n" );
            break;
        default:
            notify_fail( "Strangely, you cannot sheathe your "+
                sword[0]->short()+ " in the "+ short()+ ".\n" );
            break;
        }
        return 0;
    }
    if(objectp( environment( TP ) ))
    {
        environment( TP )->update_light( 1 );
    }
    TP->catch_msg( "You confidentally sheathe your "+ sword[0]->short()+ ".\n" );
    tell_room( environment( TP ), QCTNAME( TP )+ " confidentally sheathes "+
        TP->query_possessive()+ " "+ sword[0]->short()+ ".\n", TP );
    add_prop( CONT_M_NO_INS, 1 );

    return 1;
}

public int
do_draw( string str )
{
 object *sword, here;
 mixed res;

    here = environment( TP );

    if (!str)
    {
        sword = all_inventory( this_object() );
    }
    else
    {
        sword = FIND_STR_IN_OBJECT( str, this_object() );
    }
    if (!sizeof( sword ))
    {
        if (!str)
        {
            notify_fail( "The "+ short()+ " is empty!\n" );
        }
        else
        {
            notify_fail( "There isn't a "+ str+ " in the "+ short()+ "!\n" );
        }
        return 0;
    }
    TP->catch_msg( "You gallantly draw your "+ sword[0]->short()+ 
        " from your "+short()+" and try to wield it.\n" );
    tell_room( here, QCTNAME( TP )+ " gallantly draws "+ 
        HIS_HER(TP)+ " "+sword[0]->short()+ " from "+ HIS_HER(TP)+ 
        " "+short()+"and tries to wield it.\n", TP );
    if (sword[0]->move( TP ))
    {
        sword[0]->move( TP, 1 );
    }
    
    if (stringp( res = sword[0]->command_wield() ))
    {
        write( res );
    }

    return 1;
}

public int
do_wear( string str )
{
 object *sc;

    if (!str)
    {
        notify_fail( "Wear what?\n" );
        return 0;
    }

    sc = FIND_STR_IN_OBJECT(str, TP);

    if (member_array( this_object(), sc ) == -1)
    {
        notify_fail( "Do you want to wear the " + short() + " ?\n" );
        return 0;
    }

    if (objectp( Worn ))
    {
        notify_fail( "You already were the "+short()+".\n" );
        return 0;
    }

    if (member_array( SCABBARD_SUBLOC, TP->query_sublocs() ) > -1)
    { 
        if (str != "all")
        {
            write( "You already wear another scabbard!\n" );
            return 1;
        }
        return 0;
    } 

    TP->add_subloc( SCABBARD_SUBLOC, this_object() );
    write( "You wear the "+ short()+ " around your hips.\n" );
    say( QCTNAME( TP )+ " wears the "+ short()+ " around "+
        HIS_HER(TP)+ " hips.\n" );
    add_prop( OBJ_M_NO_DROP, "You must remove the "+short()+" first.\n" );
    Worn = TP;

/*Do not display in the inventory.          */
    set_no_show_composite( 1 );
    return (str != "all" ? 1 : 0);
}

public int
do_remove( string str )
{
 object *sc;

    if (!str)
    {
        return 0;
    }
    
    sc = FIND_STR_IN_OBJECT( str, TP );

    if (member_array( this_object(), sc ) == -1)
    {
        notify_fail( "Do you want to remove the "+short()+"?\n" );
        return 0;
    }

    if (!objectp( Worn ))
    {
        notify_fail( "You are not wearing the "+short()+".\n" );
        return 0;
    }

    TP->remove_subloc( SCABBARD_SUBLOC );
    write( "You remove the "+ short()+ ".\n" );
    say( QCTNAME( TP )+ " removes the "+ short()+ ".\n" );
    remove_prop( OBJ_M_NO_DROP );
    Worn = 0;

/*Display back in the inventory.          */
    set_no_show_composite(0);
    return (str != "all" ? 1 : 0);
}

public void leave_inv( object ob, object to )
{
/*
    if ((calling_function(-1) != "do_draw"))
    {
    }
*/
    if (objectp( ob ))
    {
        ::leave_inv( ob, to );
    }
}

public void
enter_env( object dest, object old )
{
// string  msg;

    ::enter_env( dest, old );

    if (!objectp(old) || !objectp(dest) || !interactive(dest))
    {
        return;
    }
    setuid();
    seteuid( getuid() );

}

public void
leave_env( object old, object dest )
{
    setuid();
    seteuid( getuid() );
        
    TP->remove_subloc( SCABBARD_SUBLOC );
    unset_no_show_composite();
    remove_prop( OBJ_M_NO_DROP );

    ::leave_env( old, dest );

    if (!objectp(dest) || !objectp(old) || !interactive(old))
    {
        return;
    }


}

public string
show_subloc( string subloc, object on, object for_obj )
{
 string data;

    if (subloc == SCABBARD_SUBLOC)
    {
        if (for_obj != on)
        {
            data = capitalize( on->query_pronoun() ) + 
                " is wearing "+ LANG_ASHORT( this_object() )+ ".\n";
        }
        else
        {
            data = "You are wearing "+ LANG_ASHORT( this_object() )+ ".\n";
        }
        return data;
    }
    return 0;
}

void
init()
{
    ::init();

    add_action( do_sheathe, "swsheathe" );
    add_action( do_sheathe, "swshea" );
    add_action( do_draw,    "swdraw"    );
    add_action( do_wear,    "wear"    );
    add_action( do_remove,  "remove"  );
}

public object
query_worn()
{
    return Worn;
}


string
read_label()
{
    return "On the label you read:\n" +
    "     swshea (the) - Sheathe your sword into the scabbard.\n"+
    "     swdraw       - Draw your sword from the scabbard and wield it.\n"+
    "     wear         - Wear the scabbard around your waist.\n"+
    "     remove       - Remove the scabbard from around your waist.\n\n";
}
