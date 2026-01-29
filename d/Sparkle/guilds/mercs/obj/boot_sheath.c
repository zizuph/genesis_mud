/*
 * boot sheath, by Morrigan 10/2001
 *
 * Adapted from golden scabbard code by Olorin.
 *  
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "../merc.h"

#include "/d/Krynn/common/defs.h"

#define BSHEATH_SUBLOC   "_merc_bootsheath_subloc"
#define WEAPONS_O_OWNER   "_weapons_o_owner"

public int do_remove_silently();

static object  Worn = 0;
object gBoots, gShadow;

/*
 * Function   : query_worn()
 * Description: Am I worn?
 * Returns    : the object who wears me
 */
public object
query_worn()
{
    return Worn;
}

/*
 * Function   : query_sheathed()
 * Description: Is anything sheathed in me?
 * Returns    : the object that is sheathed in me or 0
 */
public mixed
query_sheathed()
{
    if (sizeof(all_inventory(this_object())))
        return all_inventory(this_object())[0];

    return 0;
}

/*
 * Function   : filter_weapon()
 * Arguments  : x: the object to test
 * Description: Test an object to see if it is a weapon
 * Returns    : true if it is a weapon, false if it is not
 */
static int
filter_weapon( object x )
{
    return (function_exists( "create_object", x ) == "/std/weapon");
}

/*
 * Function   : filter_sword()
 * Arguments  : x: the object to test
 * Description: Test an object to see if it is a sword
 * Returns    : true if it is a sword, false if it is not
 */
static int
filter_knife( object x )
{
    return (x->query_wt() == W_KNIFE);
}

public int
can_i_drop()
{
    if (query_worn())
        return 1;

    return 0;
}

public string
short_desc()
{
    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots) && gBoots->query_worn() != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots))
	return "sheath tied around the "+gBoots->short();
    else if (query_worn())
	return "sheath tied around an ankle";
    else
        return "black leather sheath";
}

public string
short_other()
{
    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots) && gBoots->query_worn() != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots))
	return "sheath tied around "+environment(this_object())->query_possessive()+
	    " "+gBoots->short();
    else if (query_worn())
	return "sheath tied around "+environment(this_object())->query_possessive()+
	    " ankle";
    else
        return "black leather sheath";
}

public string
short_me()
{
    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots) && gBoots->query_worn() != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots))
	return "sheath tied around your "+gBoots->short();
    else if (query_worn())
	return "sheath tied around your ankle";
    else
        return "black leather sheath";
}

public string
long_desc()
{
    string tmp;

    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots) && gBoots->query_worn() != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots))
        tmp = "It has been tied around the "+gBoots->short()+", and can be "+
	    "untied at any time.\n";
    else if (query_worn())
	tmp = "It has been tied around the ankle, and can be untied at any "+
	    "time.\n";
    else
        tmp = "It can be tied around an ankle or a pair of worn boots.\n";

    return "This is a slender sheath made of black leather. A small imprint "+
	"of a dragon has been worked into the leather. The back of the sheath "+
	"has a leather thong, which presumably would be used to attach it to "+
	"something. The size of the sheath is such that only a dagger or knife "+
	"would be able to fit inside of it.\n"+tmp+"";
}

/*
 * Function   : create_container()
 * Description: create a container object
 * Returns    : void
 */
public void
create_container()
{
    set_name("sheath");
    set_adj(({"black", "leather"}));
    add_name(({"boot-sheath", "bootsheath"}));
    add_name("_merc_boot_sheath_");
    set_short("@@short_desc");
    set_long("@@long_desc");
    add_prop( OBJ_M_NO_SELL, 1 );
    add_prop( OBJ_I_NO_DROP, "@@can_i_drop");
    add_prop( CONT_I_WEIGHT,  500 );
    add_prop( CONT_I_VOLUME,  500 );
    add_prop( CONT_I_MAX_WEIGHT, 50000 );
    add_prop( CONT_I_MAX_VOLUME, 25000 );
    add_prop(OBJ_I_VALUE, 250);
    add_prop( CONT_I_TRANSP, 1 );
    add_prop( CONT_I_RIGID,  0 );
    add_prop( CONT_M_NO_INS, "You may use 'bsheath' to put a knife into the "+
	"sheath.\n" );
    setuid();
    seteuid(getuid());
}

/*
 * Function   : enter_env
 * Description: merges duplicate items, happens sometimes.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    remove_name("_merc_boot_sheath_");

    if (present("_merc_boot_sheath_", ENV(TO)))
    {
        set_alarm(1.0,0.0, &remove_object());
	    return;
    }

    add_name("_merc_boot_sheath_");
}

/*
 * Function   : do_msheath()
 * Arguments  : str: the string that follows the verb 'msheath'
 * Description: Sheathe a weapon in this item
 * Returns    : true if the weapon is sheathed, false if it is not
 */
public int
do_msheath( string str )
{
    int     result;
    object *sword, tp, here;

    tp = this_player();
    here = environment( tp );
    
    if (!str)
    {
        sword = tp->query_weapon( -1 );
    }
    else
    {
        sword = filter( FIND_STR_IN_OBJECT( str, tp ), "filter_weapon",
            this_object() );
    }

    sword = filter( sword, "filter_knife", this_object() );

    if (sizeof( sword ) != 1)
    {
        notify_fail( "Sheathe which knife?\n" );
        return 0;
    }

    if (sizeof( all_inventory( this_object() ) ))
    {
        notify_fail( "You cannot sheathe your "+ sword[0]->short()+
        ", there is already "+ LANG_ASHORT(all_inventory(this_object())[0])+
        " in the "+ short()+ ".\n" );
        return 0;
    }

    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	gBoots = 0;

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

    if (objectp(gBoots) && gBoots->query_worn() != tp)
    {
        tp->catch_msg("You sheath your "+sword[0]->short()+" in the "+
	    short_me()+" that you are carrying.\n");
        tell_room(here, QCTNAME(tp)+" sheathes "+tp->query_possessive()+
	    " "+sword[0]->short()+" in the "+short_other()+" that "+
	    tp->query_pronoun()+" is carrying.\n", tp);
    }
    else if (!objectp(gBoots) && query_worn() != tp)
    {
        tp->catch_msg("You sheath your "+sword[0]->short()+" in the "+
	    short_me()+" that you carry.\n");
        tell_room(here, QCTNAME(tp)+" sheathes "+tp->query_possessive()+
	    " "+sword[0]->short()+" in the "+short_other()+".\n", tp);
    }
    else if (query_verb() == "bsheath")
    {
        tp->catch_msg( "You kneel briefly, sheathing your "+ 
	    sword[0]->short()+ " in the "+short_me()+".\n" );
        tell_room( here, QCTNAME( tp )+ " kneels briefly, sheathing "+ 	               	    tp->query_possessive()+ " "+
            sword[0]->short()+ " in the "+short_other()+" before standing "+
            "again.\n", tp );
    }
    else
    {
        tp->catch_msg( "Reaching down with your hand, you bring your foot "+
	    "up and sheath your "+ sword[0]->short()+ " quickly in the "+
	    short_me()+".\n" );
        tell_room( here, "Reaching down with "+tp->query_possessive()+" hand, "+
	    QCTNAME( tp )+ " brings "+tp->query_possessive()+" foot up and "+
	    "sheaths a "+sword[0]->short()+ " quickly in the "+
	    short_other()+".\n", tp );
    }

    add_prop( CONT_M_NO_INS, "You may use 'bsheath' to put a knife into "+
	"the sheath.\n" );

    return 1;
}

/*
 * Function   : do_draw()
 * Arguments  : str: the string that follows the verb mdraw
 * Description: draw a sheathed/holstered weapon from this object
 * Returns    : true if a weapon is drawn, false if one is not
 */
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

    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots) && gBoots->query_worn() != tp)
    {
        tp->catch_msg("You draw your "+sword[0]->short()+" from the "+
	    short_me()+" that you are carrying.\n");
        tell_room(here, QCTNAME(tp)+" draw "+tp->query_possessive()+
	    " "+sword[0]->short()+" from the "+short()+" that "+
	    tp->query_pronoun()+" is carrying.\n", tp);
    }
    else if (!objectp(gBoots) && query_worn() != tp)
    {
        tp->catch_msg("You draw your "+sword[0]->short()+" from the "+
	    short_me()+" that you carry.\n");
        tell_room(here, QCTNAME(tp)+" draws "+tp->query_possessive()+
	    " "+sword[0]->short()+" from the "+short_other()+" that "+
	    tp->query_pronoun()+" carries.\n", tp);
    }
    else if (query_verb() == "bdraw")
    {
        tp->catch_msg( "You kneel briefly, drawing your "+ 
	    sword[0]->short()+ " from the "+short_me()+" before you stand "+
	    "again.\n" );
        tell_room( here, QCTNAME( tp )+ " kneels briefly, drawing "+ 	                           tp->query_possessive()+ " "+ sword[0]->short()+ 
	    " from the "+short_other()+" before standing again.\n", tp );
    }
    else
    {
        tp->catch_msg( "Reaching down with your hand, you bring your foot "+
	    "up and draw your "+ sword[0]->short()+ " quickly from the "+
	    short_me()+".\n" );
        tell_room( here, "Reaching down with "+tp->query_possessive()+" hand, "+
	    QCTNAME( tp )+ " brings "+tp->query_possessive()+" foot up and "+
	    "draws a "+sword[0]->short()+ " quickly from the "+
	    short_other()+".\n", tp );
    }

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

/*
 * Function   : do_wear()
 * Arguments  : str: the string that follows the verb 'wear'
 * Description: Wear this item
 * Returns    : True if it is worn, false if it is not
 */
public int
do_wear( string str )
{
    int i;
    object *sc, tp, *armours;

    tp = this_player();

    if (!str)
    {
        notify_fail( "Wear what?\n" );
        return 0;
    }

    if (str == "all")
	return 0;

    sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array( this_object(), sc ) == -1)
    {
        notify_fail( "Do you want to wear the "+short()+"?\n" );
        return 0;
    }

    if (objectp( Worn ))
    {
        notify_fail( "You are already wearing it!\n" );
        return 0;
    }

    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	do_remove_silently();

    if (member_array( BSHEATH_SUBLOC, tp->query_sublocs() ) > -1)
    { 
        if (str != "all")
        {
            write( "You already wear another "+short()+"!\n" );
            return 1;
        }
        return 0;
    } 

    if (sizeof(armours = tp->query_armour(-1)))
    {
        for (i=0;i<sizeof(armours);i++)
	    if (armours[i]->query_at() == A_FEET)
		gBoots = armours[i];
    }

    if (objectp(gBoots) && gBoots->query_worn() == tp)
    {
        gShadow = clone_object(MOBJ + "boot_sh");
        gShadow->set_sheath_object(this_object());
        gShadow->shadow_me(gBoots);

        write("You tie the sheath around your "+
	    gBoots->short()+".\n");
	say(QCTNAME(tp)+" ties the sheath around "+
	    tp->query_possessive()+" "+gBoots->short()+".\n");
    }
    else
    {
        gBoots = 0;
        write( "You tie the sheath around your ankle.\n" );
        say( QCTNAME( tp )+ " ties the sheath around "+
            tp->query_possessive()+ " ankle.\n" );
    }

    tp->add_subloc( BSHEATH_SUBLOC, this_object() );

    Worn = tp;
                                 /*Do not display in the inventory.          */
    set_no_show_composite( 1 );
    return 1;
}

/*
 * Function   : do_remove()
 * Arguments  : str: the string that follows the verb 'remove'
 * Description: remove this item
 * Returns    : true if the item is removed, false if it is not
 */
public int
do_remove_silently()
{
    if (!objectp(Worn))
	return 0;

    this_player()->remove_subloc( BSHEATH_SUBLOC );
    Worn = 0;
                                /*Display back in the inventory.          */
    set_no_show_composite(0);

    if (objectp(gBoots) && gBoots->query_sheath_object() == this_object())
	gShadow->remove_shadow();

    gBoots = 0;
    return 0;
}

public int
do_remove( string str )
{
    object *sc, tp;

    tp = this_player();

    if (!str)
        return 0;

    if (str == "all")
	return 0;
    
    sc = FIND_STR_IN_OBJECT( str, tp );

    if (member_array( this_object(), sc ) == -1)
    {
        notify_fail( "Do you want to remove the "+short()+"?\n" );
        return 0;
    }

    if (!objectp( Worn ))
    {
        notify_fail( "You are not wearing it!\n" );
        return 0;
    }

    tp->remove_subloc( BSHEATH_SUBLOC );

    if (objectp(gBoots) && gBoots->query_worn() == tp)
    {
	write("You untie the sheath and remove it from your "+
	    gBoots->short()+".\n");
	say(QCTNAME(tp)+" unties the sheath and removes it from "+
	    tp->query_possessive()+" "+gBoots->short()+".\n");
    }
    else
    {
        write( "You untie the sheath and remove it from your ankle.\n" );
        say( QCTNAME( tp )+ " unties the sheath and removes it from "+
	    tp->query_possessive()+" ankle.\n" );
    }

    Worn = 0;
                                /*Display back in the inventory.          */
    set_no_show_composite(0);

    if (objectp(gBoots) && gBoots->query_sheath_object() == this_object())
	gShadow->remove_shadow();

    gBoots = 0;
    return 1;
}

/*
 * Function   : show_subloc()
 * Arguments  : subloc: the string subloc
 *              on: the object the subloc is attached to
 *              for_obj: the object who is viewing the subloc
 * Description: Show a subloc message
 * Returns    : the string of the subloc
 */
public string
show_subloc( string subloc, object on, object for_obj )
{
    string data;

    if (objectp(gBoots) && environment(gBoots) != environment(this_object()))
	do_remove_silently();

    if (objectp(gBoots) && gBoots->query_worn() != environment(this_object()))
	do_remove_silently();

    if (subloc == BSHEATH_SUBLOC)
    {
        if (for_obj != on)
        {
            data = "";
        }
        else
        {
            if (objectp(gBoots) && gBoots->query_worn() == on)
		if (query_sheathed())
  	            data = "You have a "+query_sheathed()->short()+" in your "+
			"boot sheath.\n";
		else
		    data = "You have a sheath tied around your boots.\n";
            else if (query_worn())
		if (query_sheathed())
		    data = "You have a "+query_sheathed()->short()+" in your "+
			"ankle sheath.\n";
		else
		    data = "You have a sheath tied around your ankle.\n";
        }
        return data;
    }
    return 0;
}

/*
 * Function   : init()
 * Description: initialize this object
 * Returns    : void
 */
void
init()
{
    ::init();

    add_action( do_msheath, "bsheath");
    add_action( do_draw,    "bdraw"    );
    add_action( do_msheath, "bsheath2");
    add_action( do_draw,    "bdraw2"    );
    add_action( do_wear,    "tie"    );
    add_action( do_remove,  "untie"  );
    add_action( do_wear,    "wear"    );
    add_action( do_remove,  "remove"  );

}

string
query_auto_load()
{
    if (IS_MERC(environment(this_object())))
	return MASTER_OB(this_object())+":";

    return 0;
}

public int
remove_object()
{
    if (objectp(gShadow))
        gShadow->remove_shadow();

    ::remove_object();
}
