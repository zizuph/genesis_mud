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
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define SCABBARD_SUBLOC   "_scabbard_subloc"
#define SCABBARD_MASTER   (ITH_DIR + "emyn-arnen/obj/scabbard_master")
#define WEAPONS_O_OWNER   "_weapons_o_owner"
#define SCABBARD          "d/Gondor/ithilien/emyn-arnen/obj/scabbard.c"
static object  Worn = 0;

public void
create_container()
{
    set_name( "scabbard" );
    add_name( "_emyn_arnen_scabbard" );
    set_short( "golden scabbard" );
    set_adj( ({"golden", "ancient"}) );
    set_long( "A valuable scabbard, probably very ancient. "
    + "It is made from wood plated with pure gold. In the "
    + "scabbard you can sheathe a sword, and from it you "
    + "can draw it again when you have to fight. You can "
    + "also wear it, and later remove it again.\n" );

    add_prop( OBJ_M_NO_SELL, 1 );
    add_prop( OBJ_I_NO_STEAL, 1 );
    add_prop( CONT_I_WEIGHT,  2000 );
    add_prop( CONT_I_VOLUME,  2000 );
    add_prop( CONT_I_MAX_WEIGHT, 50000 );
    add_prop( CONT_I_MAX_VOLUME, 25000 );
    add_prop( CONT_I_TRANSP, 1 );
    add_prop( CONT_I_RIGID,  0 );
    add_prop( CONT_M_NO_INS, "If you want to insert a sword into the "+
        "scabbard, then try to 'sheathe' it!\n" );
    add_prop( MAGIC_AM_MAGIC, ({ 5, "enchantment" }) );
    add_prop( OBJ_I_RES_FIRE, 40 );
    add_prop( MAGIC_AM_ID_INFO,
        ({
         5, "This "+ short()+ " has been magically protected against "+
            "fire.\n",
        10, "You wonder why someone cared about making this item "+
            "fire resistant.\n",
        }) );
    add_prop( OBJ_S_WIZINFO, "This scabbard is part of the quest reward "+
        "for retrieving the battlestandard of the Witchking of Angmar. It "+
        "can be used to sheathe a sword. The scabbard will auto_load and "+
        "it can not be sold in shops, but it can be lost, dropped, given "+
        "away. This scabbard can also support a Morgul spell narusse.\n" );
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
 object *sword, tp;

    tp = this_player();
    
    if (!str)
    {
        sword = tp->query_weapon( -1 );
    }
    else
    {
        sword = filter( FIND_STR_IN_OBJECT( str, tp ), "filter_weapon",
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

    if ( sword[0]->query_wielded() == tp )
    {
        sword[0]->unwield_me();
        if ( sword[0]->query_wielded() == tp )
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
    if(objectp( environment( tp ) ))
    {
        environment( tp )->update_light( 1 );
    }
    tp->catch_msg( "You sheathe your "+ sword[0]->short()+ ".\n" );
    tell_room( environment( tp ), QCTNAME( tp )+ " sheathes "+
        tp->query_possessive()+ " "+ sword[0]->short()+ ".\n", tp );
    add_prop( CONT_M_NO_INS, 1 );

    return 1;
}

public int
do_draw( string str )
{
 object *sword, to, tp, here;
 mixed res;


    tp  = this_player();
    here = environment( tp );

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
            notify_fail( "Your "+ short()+ " is empty!\n" );
        }
        else
        {
            notify_fail( "There is no "+ str+ " in your "+ short()+ "!\n" );
        }
        return 0;
    }
                                /*These checks are not as complex as those
                                  in the wield function but then I don't
                                  expect an octupus using the scabbard or
                                  feet-wielded (sic!) weapons.            */
    if (this_player()->query_tool( W_BOTH ))
    {
        notify_fail( "Both of your hands are occupied!\n" );
        return 0;
    }
    else
    {
        switch (sword[0]->query_hands())
        {
        case W_LEFT:
            if (this_player()->query_tool( W_LEFT ))
            {
                notify_fail( "Your left hand is occupied!\n" );
                return 0;
            }
            break;
        case W_RIGHT:
            if (this_player()->query_tool( W_RIGHT ))
            {
                notify_fail( "Your right hand is occupied!\n" );
                return 0;
            }
            break;
        case W_BOTH:
            if ((this_player()->query_tool( W_RIGHT )) || (this_player()->query_tool( W_LEFT )))
            {
                notify_fail( "You haven't got enough spare hands!\n" );
                return 0;
            }
            break;
        }
    }
    tp->catch_msg( "You draw your "+ sword[0]->short()+ "!\n" );
    tell_room( here, QCTNAME( tp )+ " draws "+ tp->query_possessive()+ " "+
        sword[0]->short()+ ".\n", tp );
    if (sword[0]->move( tp ))
    {
        sword[0]->move( tp, 1 );
    }
    
    if (stringp( res = sword[0]->command_wield() ))
    {
        write( res );
    }

    return 1;
}

public string
query_auto_load()
{
    setuid();
    seteuid( getuid() );
    SCABBARD_MASTER->check_owner( environment( this_object() ));
    return MASTER + ":";
}

public int
do_wear( string str )
{
 object *sc, tp;

    tp = this_player();
    if (!str)
    {
        notify_fail( "Wear what?\n" );
        return 0;
    }

    sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array( this_object(), sc ) == -1)
    {
        return 0;
    }

    if (objectp( Worn ))
    {
        notify_fail( "You are already wearing the " + short() + "!\n" );
        return 0;
    }

    if (member_array( SCABBARD_SUBLOC, tp->query_sublocs() ) > -1)
    { 
        if (str != "all")
        {
            write( "You already wear another scabbard!\n" );
            return 1;
        }
        return 0;
    } 

    tp->add_subloc( SCABBARD_SUBLOC, this_object() );
    write( "You wear the "+ short()+ " around your hips.\n" );
    say( QCTNAME( tp )+ " wears the "+ short()+ " around "+
        tp->query_possessive()+ " hips.\n" );
    add_prop( OBJ_M_NO_DROP, "Remove the scabbard first!\n" );
    Worn = tp;
                                 /*Do not display in the inventory.          */
    set_no_show_composite( 1 );
    return (str != "all" ? 1 : 0);
}

public void
auto_wear_scabbard()
{
    if (member_array( SCABBARD_SUBLOC, this_player()->query_sublocs() ) > -1)
        return;
    else
        do_wear(OB_NAME(this_object()));
}

public int
do_remove( string str )
{
 object *sc, tp;

    tp = this_player();
    if (!str)
    {
        return 0;
    }
    
    sc = FIND_STR_IN_OBJECT( str, tp );

    if (member_array( this_object(), sc ) == -1)
    {
        notify_fail( "Do you want to remove the scabbard?\n" );
        return 0;
    }

    if (!objectp( Worn ))
    {
        notify_fail( "You are not wearing it!\n" );
        return 0;
    }

    tp->remove_subloc( SCABBARD_SUBLOC );
    write( "You remove the "+ short()+ ".\n" );
    say( QCTNAME( tp )+ " removes the "+ short()+ ".\n" );
    remove_prop( OBJ_M_NO_DROP );
    Worn = 0;
                                /*Display back in the inventory.          */
    set_no_show_composite(0);
    return (str != "all" ? 1 : 0);
}

public void leave_inv( object ob, object to )
{
    if ((calling_program(-1) != SCABBARD) ||
        (calling_function(-1) != "do_draw"))
    {
        if (ob->query_flame_blade())
        {
            ob->dispel_spell_effect();
        }
    }
    if (objectp( ob ))
    {
        ::leave_inv( ob, to );
    }
}

public void
enter_env( object dest, object old )
{
 string  msg;

    ::enter_env( dest, old );

    if (!objectp(old) || !objectp(dest) || !interactive(dest))
    {
        return;
    }
    setuid();
    seteuid( getuid() );

    SCABBARD_MASTER->check_owner( dest );
    msg = dest->query_name();
    if (!living( old ))
    {
        msg += " picked up the scabbard from "+ file_name( old );
    }
    else if (interactive( old ))
    {
        msg += " got the scabbard from "+ old->query_name();
    }
    else
    {
        msg += " got the scabbard from "+ old->query_name()+ " ("+
            file_name(old)+ ")";
    }
    msg += ". "+ ctime(time())+ ".\n";
    log_file( "scabbard", msg );
}

public void
leave_env( object old, object dest )
{
 object *sword, owner;
 string  msg;
        
    this_player()->remove_subloc( SCABBARD_SUBLOC );
    unset_no_show_composite();
    remove_prop( OBJ_M_NO_DROP );

    sword = all_inventory( this_object() );
    if (sizeof( sword ))
    {
        if (sword[0]->query_flame_blade())
        {
            owner = sword[0]->query_prop( WEAPONS_O_OWNER );
            if (objectp( owner ))
            {
                sword[0]->dispel_spell_effect();
            }
        }
    }
    ::leave_env( old, dest );

    if (!objectp(dest) || !objectp(old) || !interactive(old))
    {
        return;
    }

    setuid();
    seteuid( getuid() );

    SCABBARD_MASTER->remove_owner( old );
    msg = old->query_name();
    if (!living( dest ))
    {
        msg += " dropped the scabbard in "+ file_name( dest );
    }
    else if (interactive( dest ))
    {
        msg += " gave the scabbard to "+ dest->query_name();
    }
    else
    {
        msg += " gave the scabbard to "+ dest->query_name()+ " ("+
            file_name(dest)+ ")";
    }
    msg += ". "+ ctime(time())+ ".\n";
    log_file( "scabbard", msg );
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

public int query_recover()
{
    return 0;
}

void
init()
{
    ::init();

    add_action( do_sheathe, "sheathe" );
    add_action( do_draw,    "draw"    );
    add_action( do_wear,    "wear"    );
    add_action( do_remove,  "remove"  );
}

public object
query_worn()
{
    return Worn;
}

/* Function name: init_arg
 * Description  : Called when autoloading. Sets an alarm to auto-wear
 * Arguments    : string arg - the auto-load argument
 */
public void
init_arg(string arg)
{
    set_alarm(1.5, 0.0, auto_wear_scabbard);
}
