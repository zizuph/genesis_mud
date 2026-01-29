// file name:   /d/Avenir/common/outpost/obj/crate.c
// creator(s): 	Kazz   June 1995
// updates:	June 1995
// purpose: 	Quest crate to be moved onto cart.c
// bug(s):	
// to-do:	
//		* Add a stinky property to the person who pushes the crate on
//		      to the cart.
//		* add command (in a crate) to push a special crate onto cart.
//		  * if not strong enough, add check for warehouse boss to help
//		* it will start in the port warehouse.
// note:        This is just a modified version of:
//		         /d/Avenir/common/port/obj/std_crate
//		This crate is created in outpost/fort6 & moved to port/ware

inherit "/d/Avenir/common/port/obj/std_crate";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/cart.h"


#define DEBUG

#ifdef DEBUG
#define D(x) find_player("kazz")->catch_msg("crate debug: " + (x))
#else
#define D(x) ;
#endif


// This crate is the same as one of Ilyian's crates that ends up in
// the outpost warehouse, but this one actually exists in the port,
// and can be moved down to the outpost with the outpost cart.

init()
{

    add_action( "do_push", "push" );
    
} // init()


void
create_container()
{
    ::create_container();
    
    // remove this name so Jarod won't pick it up and carry to outpost.
    remove_name( "std_crate_ware" );

    // so the player knows this is the one that nobody will move
    set_adj( "putrid" );
    set_adj( "smelly" );

} // create_container()


// push the crate onto the outpost cart.
int
do_push( string str )
{
    object cart;
    object warehouse_boss;
    string crate_check;
    
    NF( "Push the crate how?\n" );
    if (!parse_command( str, this_object(),
			"[the] %w 'on' / 'onto' [the] 'cart' [tray]",
			crate_check )) {
	if (crate_check != "crate")
		NF( "Push what?\n" );
        return 0;
    }

    // verify the cart is in the same room to push the crate onto
    cart = present( AVENIR_CART_ID, ENV(TO) );
    if (!cart) {
	write( "Cart? What cart?\n" );
	tell_room( QCTNAME(TP) +" seems confused.\n" );
	return 1;
    }
    
    // if strong enuf, go ahead and push...
    if (STR(TP) > 50) {
	write( "You manage to push the crate onto the cart.\n" );
	tell_room( QCTNAME(TP) +" pushes the crate onto the cart.\n" );
	cart->set_crate_on_cart( TO );
//	OUTPOST_WAREHOUSE_SOURCE->query_cart()->set_crate_on_cart( TO );
    } else {
	write( "The crate is too heavy for you to move.\n" );
	tell_room( QCTNAME(TP) +" pushes on the crate.\n" );
	
	// the warehouse boss will help if he iss alive.
	warehouse_boss = present( "sysiphus", ENV(TO) );
//	warehouse_boss = PORT_WAREHOUSE_SOURCE->query_sisyphus();
	if (objectp(warehouse_boss)) {
	    warehouse_boss->command( "say Hey!" );
	    warehouse_boss->command( "You're actually taking that crate?" );
	    warehouse_boss->command(
			   "That thing stinks so bad I'll even help you." );
            write( QCTNAME(warehouse_boss) +" walks over "+
		   "and grimaces at the smell. He pushes the crate with one "+
		   "arm it slides onto the cart!\n" );
	    tell_room( QCTNAME(warehouse_boss) +" walks over and helps "+
		       QCTNAME( TP ) +" push the crate onto the cart.\n" );
	    cart->set_crate_on_cart( TO );
	}	 
    } // if STR > 50

    // add a stinky smell to this player
    // ** UNFINISHED **
    
    return 1;
} // do_push()
