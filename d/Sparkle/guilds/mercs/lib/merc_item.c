/*
 *  Mercenary Guild Item, by Morrigan 10/2001
 *
 *  Adapted from golden scabbard code by Olorin.
 *
 * Change log:
 * - Updated and moved to Sparkle by Lunatari 2006
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container.c";

#include "merc.h"

#define SCABBARD_SUBLOC   "_merc_scabbard_subloc"
#define WEAPONS_O_OWNER   "_weapons_o_owner"

static object  Worn = 0;
object gOwner, gShield, gStrap_Shadow;
string gType, gLocation;

public void set_location(string s) { gLocation = s; }
public string query_location() { return gLocation; }
public void set_shield(object o) { gShield = o; }

public object query_shield()
{
    if (objectp(gShield) && environment(gShield) == environment(this_object()) &&
	    gShield->query_worn() != environment(this_object()))
	return gShield;

    gShield = 0;
    return gShield;
}

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
 * Function   : query_gOwner()
 * Description: Who is my owner?
 * Returns    : the object who owns me
 */
public object
query_gOwner()
{
    return gOwner;
}

/*
 * Function   : query_type()
 * Description: What type of guild_item am I? Scabbard or holster?
 * Returns    : the string 'scabbard' or 'holster'
 */
public string
query_type()
{
    return gType;
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
 * Function   : setup_merc_item()
 * Description: set up this item for the mercenary who has it
 * Returns    : void
 */
public void
setup_merc_item()
{
    gOwner = environment(this_object());

    set_no_show_composite(0);

    if (MEMBER_CLUB(gOwner) != 0)
    {
	add_name("holster");
	set_short("black leather holster");
	set_long("It is a black leather holster, decorated with the emblem "+
		"of a red dragon. This was given to you when you chose to "+
		"specialize in clubs. In it you can 'mholster' or 'mdraw' your "+
		"club. It can be worn on the side or on the back. If it is worn "+
	        "on the back, you may also 'mstrap' and 'munstrap' a shield to it. "+
	        "You notice in small letters the words 'mhelp'.\n");
        add_prop( CONT_M_NO_INS, "You must use 'mholster'.\n" );
	gType = "holster";
        return;
    }

    if (MEMBER_SWORD(gOwner) != 0)
    {
        add_name("scabbard");
        set_short("black leather scabbard");
        set_long("It is a black leather scabbard, decorated with the emblem "+
		"of a golden lion. This was given to you when you chose to "+
		"specialize in swords. In it, you can 'msheath' or "+
		"'mdraw' your sword. It can be worn on the side or on the "+
		"back. If it is worn on the back, you may also 'mstrap' and "+
		"'munstrap' a shield to it. You notice in small letters "+
		"the words 'mhelp'.\n");
        add_prop( CONT_M_NO_INS, "You must use 'msheath'.\n" );
        gType = "scabbard";
        return;
    }

    add_name("belt");
    set_short("black leather belt");
    set_long("It is a black leather belt, decorated with the emblem "+
	"of a red dragon. This was given to you when you enlisted "+
	"as a mercenary. "+
        "You also notice in small letters the words 'mhelp'.\n");
    add_prop( CONT_M_NO_INS, "You cannot put things in the belt.\n" );
    gType = "belt";
    return;

}

/*
 * Function   : enter_env
 * Description: merges duplicate items, happens sometimes.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    remove_name("_merc_guild_item_");

    if (present("_merc_guild_item_", ENV(TO)))
    {
        set_alarm(1.0,0.0, &remove_object());
	    return;
    }

    add_name("_merc_guild_item_");
}

/*
 * Function   : create_container()
 * Description: create a container object
 * Returns    : void
 */
public void
create_container()
{
    set_name("_merc_guild_item_");
    set_adj(({"black", "leather"}));
    set_long("Mercenary Guild Item.");
    add_prop( OBJ_M_NO_SELL, 1 );
    add_prop( OBJ_I_NO_STEAL, 1 );
    add_prop( OBJ_I_NO_DROP, 1);
    add_prop( CONT_I_WEIGHT,  500 );
    add_prop( CONT_I_VOLUME,  500 );
    add_prop( CONT_I_MAX_WEIGHT, 50000 );
    add_prop( CONT_I_MAX_VOLUME, 25000 );
    add_prop( CONT_I_TRANSP, 1 );
    add_prop( CONT_I_RIGID,  0 );
    add_prop( CONT_M_NO_INS, "You must use 'msheath' or 'mholster'.\n" );
    add_prop( OBJ_S_WIZINFO, "This is the mercenary guild item.\n" );
    setuid();
    seteuid(getuid());

    set_no_show_composite(1);
    set_alarm(1.0, 0.0, "setup_merc_item");
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

static int
filter_armour( object x)
{
    return (function_exists( "create_object", x ) == "/std/armour");
}

/*
 * Function   : filter_sword()
 * Arguments  : x: the object to test
 * Description: Test an object to see if it is a sword
 * Returns    : true if it is a sword, false if it is not
 */
static int
filter_sword( object x )
{
    return (x->query_wt() == W_SWORD);
}

/*
 * Function   : filter_club()
 * Arguments  : x: the object to test
 * Description: Test an object to see if it is a club
 * Returns    : true if it is a club, false if it is not
 */
static int
filter_club( object x )
{
    return (x->query_wt() == W_CLUB);
}

static int
filter_shield(object x)
{
    return (x->query_at() == A_SHIELD);
}

/*
 * Function   : do_mholster()
 * Arguments  : str: the string that follows the verb mholster
 * Description: Holster a club in this item
 * Returns    : true if the weapon is holstered, false if it is not
 */
public int
do_mholster( string str )
{
    int     result;
    object *club, tp;

    tp = this_player();


    NF("What?\n");
    if (query_type() != "holster")
       return 0;

    if (!str)
    {
        club = tp->query_weapon( -1 );
    }
    else
    {
        club = filter( FIND_STR_IN_OBJECT( str, tp ), "filter_weapon",
            this_object() );
    }

    club = filter( club, "filter_club", this_object() );

    if (sizeof( club ) != 1)
    {
        notify_fail( "Holster which club?\n" );
        return 0;
    }

    if (sizeof( all_inventory( this_object() ) ))
    {
        notify_fail( "You cannot holster your "+ club[0]->short()+
        ", there is already "+ LANG_ASHORT(all_inventory(this_object())[0])+
        " in the "+ short()+ ".\n" );
        return 0;
    }

    if ( club[0]->query_wielded() == tp )
    {
        club[0]->unwield_me();
        if ( club[0]->query_wielded() == tp )
        {
            notify_fail( "You cannot unwield your "+
                club[0]->short()+ ".\n" );
               return 0;
        }
    }

    remove_prop( CONT_M_NO_INS );
    if (result = club[0]->move( this_object() ))
    {
        switch (result)
        {
        case 1:
            notify_fail( "Your "+ club[0]->short()+ " is too heavy for "+
            "the "+ short()+ ".\n" );
            break;
        case 8:
            notify_fail( "Your "+ club[0]->short()+ " is too large for "+
            "the "+ short()+ ".\n" );
            break;
        default:
            notify_fail( "Strangely, you cannot holster your "+
                club[0]->short()+ " in the "+ short()+ ".\n" );
            break;
        }
        return 0;
    }
    if(objectp( environment( tp ) ))
    {
        environment( tp )->update_light( 1 );
    }
    tp->catch_msg( "You holster your "+ club[0]->short()+ ".\n" );
    tell_room( environment( tp ), QCTNAME( tp )+ " holsters "+
        tp->query_possessive()+ " "+ club[0]->short()+ ".\n", tp );
    add_prop( CONT_M_NO_INS, 1 );

    return 1;
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
    object *sword, tp;

    tp = this_player();

    NF("What?\n");
    if (query_type() != "scabbard")
	return 0;

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

    NF("What?\n");
    if (query_type() != "holster" && query_type() != "scabbard")
	return 0;

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

/*
 * Function   : do_wear()
 * Arguments  : str: the string that follows the verb 'wear'
 * Description: Wear this item
 * Returns    : True if it is worn, false if it is not
 */
public int
do_wear( string str )
{
    object *sc, tp, ob;

    tp = this_player();

    if (str == "all")
        return 0;

    if (!str)
    {
        notify_fail( "Wear what?\n" );
        return 0;
    }

    if (query_type() != "belt" && parse_command(str, TP,
	" [the] %o [around] [over] [on] [my] 'back' / 'shoulder' / 'shoulders' ", ob))
	set_location("back");
    else if (parse_command(str, TP,
	" [the] %o [around] [over] [on] [my] 'hips' / 'waist' / 'belt' / 'side' / 'hip' ", ob))
	set_location("hips");
    else if (parse_command(str, TP, "[the] %o", ob) && ob == this_object())
        set_location("hips");
    else
        return 0;

/*    if (query_location() == "none")
        set_location("hips");
*/

//    sc = FIND_STR_IN_OBJECT(str, tp);

//    if (member_array( this_object(), sc ) == -1)
    if (ob != this_object())
    {
        notify_fail( "Do you want to wear the "+short()+"?\n" );
        return 0;
    }

    if (objectp( Worn ))
    {
        notify_fail( "You are already wearing it!\n" );
        return 0;
    }

    if (member_array( SCABBARD_SUBLOC, tp->query_sublocs() ) > -1)
    {
        if (str != "all")
        {
            write( "You already wear another "+short()+"!\n" );
            return 1;
        }
        return 0;
    }

    tp->add_subloc( SCABBARD_SUBLOC, this_object() );

    if (query_location() == "back")
    {
        write("You fasten the "+short()+" over your shoulder, securing "+
	    "it on your back.\n");
	say(QCTNAME(tp)+" fastens the "+short()+" over "+tp->query_possessive()+
	    " shoulder, securing it on "+tp->query_possessive()+" back.\n");
    }
    else
    {
        write( "As you fasten the "+short()+" around your waist, it settles "+
	    "comfortably on your hips.\n" );
        say( QCTNAME( tp )+ " fastens "+ short()+ " around "+
        tp->query_possessive()+ " waist.\n" );
    }

    Worn = tp;
                                 /*Do not display in the inventory.          */
    set_no_show_composite( 1 );
    return (str != "all" ? 1 : 0);
}

/*
 * Function   : do_remove()
 * Arguments  : str: the string that follows the verb 'remove'
 * Description: remove this item
 * Returns    : true if the item is removed, false if it is not
 */
public int
do_remove( string str )
{
 object *sc, tp;

    tp = this_player();

    if (str == "all")
        return 0;

    if (!str)
    {
        return 0;
    }

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

    if (query_shield())
    {
        write("You unstrap your "+query_shield()->short()+" from your back.\n");
	    query_shield->set_no_show_composite(0);
        gShield = 0;
    }

    tp->remove_subloc( SCABBARD_SUBLOC );
    write( "You remove the "+ short()+ ".\n" );
    say( QCTNAME( tp )+ " removes the "+ short()+ ".\n" );
    Worn = 0;
                                /*Display back in the inventory.          */
    set_no_show_composite(0);
    return (str != "all" ? 1 : 0);
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
    string data, my_tmp, other_tmp, shield_desc = "";
    object tabard;

    if (query_shield())
    {
        if (tabard = query_shield()->query_tabard_object())
	    shield_desc = ", upon which is strapped a "+tabard->query_crest()[2]+
	        " tabard-covered shield bearing a "+tabard->query_crest()[0]+
		" " + tabard->query_crest()[1];
        else
	    shield_desc = ", upon which is strapped a "+
		query_shield()->short();
    }

    if (query_location() == "back")
    {
	my_tmp = "on your back";
	other_tmp = "on "+on->query_possessive()+" back";
    }
    else
    {
	my_tmp = "on your hip";
	other_tmp = "on "+on->query_possessive()+" hip";
    }

    if (subloc == SCABBARD_SUBLOC)
    {
        if (for_obj != on)
        {
            data = capitalize( on->query_pronoun() ) +
                " is wearing "+ LANG_ASHORT( this_object() )+ " "+
		other_tmp;
        }
        else
        {
            data = "You are wearing "+ LANG_ASHORT( this_object() )+ " "+
		my_tmp;
        }

        return data + shield_desc + ".\n";
    }
    return 0;
}

/*
 * Function   : setup_mercenary()
 * Description: Make sure the person is a mercenary
 * Returns    : void
 */
void setup_mercenary()
{
    object me = environment(this_object());
    string gender;
    string *sublords;
    int size_sublords;

    seteuid(getuid(TO));

    if (MCREST->query_crest_lord(me->query_name()))
    {
        gender = (me->query_gender() == 1 ? "lady" : "lord");
        MCREST->set_lord_gender(me->query_name(), gender);

        /* A lord cannot autocomply to anyone else */
        if (me->query_skill(SS_MERC_AUTOCOMPLY) != 0)
	    me->set_skill(SS_MERC_AUTOCOMPLY, 0);

        /* If following no longer supports the number of sublords a lord has,
	 *    remove them one by one each login until appropriate
	 */
        if (MCREST->query_has_sublords(me->query_name()))
        {
	    if (size_sublords =
	        sizeof(sublords = MCREST->query_sublords(me->query_name())) >
		MCREST->query_max_sublords(me->query_name()))
	    {
                me->catch_tell("Your following no longer supports the number "+
	            "of lords you have serving you!\n");
		MCREST->remove_sublord_member(sublords[size_sublords - 1]);
	    }
        }
    }

    if (!IS_MERC(ENV(TO)) && !ENV(TO)->query_wiz_level())
    {
        if (ENV(TO)->query_real_name() != MERC_GMJUNIOR)
        {
	    write("You are not a mercenary. You may not possess the "+short()+".\n");
	    remove_object();
        }
    }

}

/*
 * Function   : query_recover()
 * Description: Does this item recover? No it doesn't, the autoshadow
 *              loads it manually
 * Returns    : false, because it doesn't recover
 */

public string
query_recover()
{
    return 0;
}

public int
do_strap( string str )
{
    int     result;
    object *armours, *shield, tp;

    tp = this_player();

    NF("What?\n");
    if (query_type() == "belt")
	return 0;

    if (query_location() != "back")
    {
	write("You can only strap a shield to your back.\n");
	return 1;
    }

    if (!str)
    {
        shield = tp->query_armour( -1 );
    }
    else
    {
        shield = filter( FIND_STR_IN_OBJECT( str, tp ), "filter_armour",
            this_object() );
    }

    shield = filter( shield, "filter_shield", this_object() );

    if (sizeof( shield ) != 1)
    {
        notify_fail( "Strap which shield to your back?\n" );
        return 0;
    }

    if (objectp(query_shield()))
    {
        notify_fail( "You cannot strap your "+ shield[0]->short()+
        ", there is already "+ LANG_ASHORT(query_shield())+
        " strapped to the "+ short()+ ".\n" );
        return 0;
    }

    if ( shield[0]->query_worn() == tp )
    {
	shield[0]->remove_me();
        if ( shield[0]->query_worn() == tp )
        {
            notify_fail( "You cannot remove your "+
                shield[0]->short()+ ".\n" );
               return 0;
        }
    }

    set_shield(shield[0]);

    setuid(); seteuid(getuid());

    gStrap_Shadow = clone_object(MOBJ + "strap_shield_sh");
    gStrap_Shadow->set_sheath_object(this_object());
    gStrap_Shadow->shadow_me(query_shield());
    query_shield()->add_prop(OBJ_M_NO_DROP, "You must 'unstrap' the shield "+
	"before you can drop it.\n");
    query_shield()->set_no_show_composite(1);

    if(objectp( environment( tp ) ))
    {
        environment( tp )->update_light( 1 );
    }

    tp->catch_msg( "You strap your "+ shield[0]->short()+ " to your back.\n" );
    tell_room( environment( tp ), QCTNAME( tp )+ " straps "+
        tp->query_possessive()+ " "+ shield[0]->short()+ " to "+
	tp->query_possessive()+" back.\n", tp );

    return 1;
}

public int
do_unstrap( string str )
{
    object shield, *tmp, to, tp, here;
    mixed res;

    tp  = this_player();
    here = environment( tp );

    NF("What?\n");
    if (query_type() != "holster" && query_type() != "scabbard")
	return 0;

    if (!str)
    {
        shield = query_shield();
    }
    else
    {
//        if (sizeof(tmp = FIND_STR_IN_OBJECT( str, this_object() )))
//	    shield = tmp[0];
	shield = query_shield();
    }
    if (!objectp( shield ))
    {
        if (!str)
        {
            notify_fail( "There is no shield strapped to your "+short()+"!\n" );
        }
        else
        {
            notify_fail( "There is no shield strapped to your "+ short()+ "!\n" );
        }
        return 0;
    }

    tp->catch_msg( "You unstrap your "+ query_shield()->short()+ " from "+
	"your back.\n" );
    tell_room( here, QCTNAME( tp )+ " unstraps "+ tp->query_possessive()+ " "+
        query_shield()->short()+ " from "+tp->query_possessive()+" back.\n", tp );

    query_shield()->set_no_show_composite(0);
    query_shield()->remove_prop(OBJ_M_NO_DROP);

    if (objectp(gStrap_Shadow))
        gStrap_Shadow->remove_shadow();

    if (stringp( res = query_shield()->command_wear() ))
    {
        write( res );
    }

    gShield = 0;
    return 1;
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

    seteuid(getuid(TO));
    set_alarm(1.0, 0.0, "setup_mercenary");

    add_action( do_mholster,"mholster" );
    add_action( do_msheath, "msheath"  );
    add_action( do_draw,    "mdraw"    );
    add_action( do_wear,    "wear"     );
    add_action( do_remove,  "remove"   );
    add_action( do_strap,   "mstrap"    );
    add_action( do_unstrap, "munstrap"  );
}
