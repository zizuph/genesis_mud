// file name:   /d/Avenir/common/outpost/obj/cart.c
// creator(s): 	Kazz   June 1995
// updates:	June 1995
// purpose: 	Quest tool to move a box from the pier warehouse to outpost.
// bug(s):	
// to-do:	Ideas below might make it too tough for small players.
//		? if dex too low, cart may escape over port Ledge (ilyian)
//		? increase fatigue from pushing

inherit "/std/container";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/cart.h"

#define DEBUG

#ifdef DEBUG
#define D(x) find_player("kazz")->catch_msg("cart debug: " + (x))
#else
#define D(x) ;
#endif

int has_a_crate = 0;
int crate_is_strapped = 0;
object crate;


init()
{
    ::init();
    add_action( "do_push", "push" );
    add_action( "do_dump", "dump" );
    add_action( "do_dump", "tip" );
    add_action( "do_strap", "strap" );
    add_action( "do_unstrap", "unstrap" );

} // init()


//create_object()
create_container()
{
    set_name( "cart" );
    add_name( AVENIR_CART_ID );
    set_short( "@@cart_short@@" );
    set_long(  "@@cart_long@@" );
    
//    add_prop(OBJ_I_WEIGHT, 150000);
//    add_prop(OBJ_I_VOLUME, 60000);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop (CONT_I_MAX_WEIGHT, 5000000);
    add_prop (CONT_I_MAX_VOLUME, 2000000);

    // tho this doesn't clone anything, I think it is needed so that if
    //   the push command loads a room, that room can clone it's objects.
    seteuid(getuid());	

} // create_object()


// return the proper string for use in set_short();
string
cart_short()
{

    if (has_a_crate)
        if (crate_is_strapped)
    		return "metal cart with a crate strapped to it";
        else
    		return "metal cart with a crate on it";
    else
    	return "metal cart";

} // cart_short()


// return the proper string for use in set_long();
string
cart_long()
{
    if (has_a_crate) {
        if (crate_is_strapped)
		return "This cart has a large crate sitting on the flat tray "+
		       "at the bottom, "+
			"connected near the two wheels. "+
	       		"A long sturdy handle rises up from the "+
         	     "bottom and two leather straps hold the crate tightly.\n";
	else
		return "This cart has a large crate sitting on the flat tray "+
			"at the bottom, "+
			"connected near the two wheels. "+
	       		"A long sturdy handle rises up from the "+
	       		"bottom and two leather strap hangs loosely.\n" ;
    } else
    	return "This cart has a large flat tray at the bottom, "+
			"connected near the two wheels. "+
	       		"A long sturdy handle rises up from the "+
	       		"bottom and two leather strap hangs loosely.\n";
} // cart_long()


// push the crate cart to different rooms.
int
do_push( string str )
{
    string push_dir;
    int    num_exits;
    int    i;
    mixed  *exits;
    string next_room;
    
    NF( "Push what?\n" );

    if (!parse_command(str, this_object(), "[the] 'cart' %w", push_dir))
        return 0;

    NF( "Push the cart where?\n" );

    // check code for boulder in Krynn graveyard  (ie. 'push stone n')
    exits = environment(TO)->query_exit();
    for (i = 1; i<sizeof(exits); i +=3) {
	if (exits[i] == push_dir) {
	    next_room = exits[i - 1];
	    
	    // ready to move... make sure the crate is strapped in!
	    if (has_a_crate && !crate_is_strapped) {
		TP->catch_msg( "You start to push the cart, but the crate "+
			       "tumbles off it!\n" );
		say( QCTNAME(TP) +" pushes the cart but "+
			   "a crate falls off the cart.\n" );
		
		// move crate from cart to this room.
		crate->move( ENV(TO) );
		has_a_crate = 0;
		
		return 1;
	    }
	    
	    if (!move( next_room )) {
		// valid direction, so allow the push.
		TP->catch_msg( "You manage to tip the cart back onto the "+
			       "wheels and roll it.\n" );
		say( QCTNAME(TP) +" pushes the cart "+ push_dir +".\n",
			   TP );
		TP->move_living( "M", next_room, 0, 0, );
		tell_room( next_room, QCTNAME(TP) +
			   " arrives pushing a cart.\n", TP );
		return 1;
	    }
	}
    } // for
    
    return 0;
} // do_push()


// dump the crate off the cart.
int
do_dump( string str )
{
    NFN( " what?\n" );
    
    if (!parse_command(str, this_object(),
		       "[the] 'crate' 'off' [the] 'cart'" ))
        return 0;

    if (!has_a_crate) {
	TP->catch_msg( "There is nothing on the cart!\n" );
	return 1;
    }
    
    if (crate_is_strapped) {
	/* complain */
	TP->catch_msg( "You tip the cart around, but the crate won't come "+
		       "off the cart. You only succeed in making yourself "+
		       "tired.\n" );
	say( QCTNAME(TP) + " jostles the cart around and ends up "+
		   	"looking tired.\n", TP );
    } else {
	/* succeed */
	TP->catch_msg( "You tip the cart slightly, and the crate slips off "+
		       "of the cart.\n" );
	say( QCTNAME(TP) + " dumps the crate off of the cart.\n", TP );
	has_a_crate = 0;
	
	// move crate from cart to this room.
	crate->move( ENV(TO) );
    }
    
    return 1;
} // do_dump()


// strap the crate to the cart.
int
do_strap( string str )
{
    NF( "Strap what?\n" );
    
    if (!parse_command(str, this_object(),
		       "[the] 'crate' 'on' / 'to' 'cart'" ))
        return 0;

    if (!has_a_crate) {
	TP->catch_msg( "There is no crate ready for strapping!\n" );
	return 1;
    }
    
    if (crate_is_strapped) {
	/* complain */
	TP->catch_msg( "The crate is already strapped onto the cart!\n" );
	say( QCTNAME(TP) + " studies the cart briefly.\n", TP );
    } else {
	/* succeed */
	TP->catch_msg( "You gather up the loose ends of the leather strap "+
		       "and tightly secure the crate to the cart.\n" );
	say( QCTNAME(TP) + " straps a crate to the cart.\n", TP );
	crate_is_strapped = 1;
    }
    
    return 1;

} // do_strap()


// unstrap the crate.
int
do_unstrap( string str )
{
    if (!parse_command(str, this_object(), "[the] 'crate'" ))
        return 0;

    if (!has_a_crate) {
	TP->catch_msg( "There is nothing strapped to the crate!\n" );
	return 1;
    }
    
    if (crate_is_strapped) {
	/* succeed */
	TP->catch_msg( "You loosen the cart straps from around the cart.\n" );
	say( QCTNAME(TP) + " unstraps the crate on the cart.\n", TP );
	crate_is_strapped = 0;
    } else {
	/* complain */
	TP->catch_msg( "The crate is already strapped onto the cart!\n" );
	say( QCTNAME(TP) + " studies the cart briefly.\n", TP );
    }
    
    return 1;
} // do_unstrap()


// used for externals calls, after a crate has been pushed onto the cart.
// Note: pushing a crate on the crate is controlled by the crate, not the cart
void
set_crate_on_cart( object new_crate )
{
    new_crate->move( TO );
    crate = new_crate;
    has_a_crate = 1;
} // set_crate_on_cart()

