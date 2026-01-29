/*
 *  /d/Genesis/start/human/town/square.c
 *
 *  Created long ago by Styles at CD.
 *
 *  Modification log:
 *
 *    Feb-2008: Included quest vendor code
 *              Included different defs.h file to allow for the
 *                code necessary for the quest vendor. (Gorboth)
 *
 *	  Nov 2008:	Someone had broken the room so I comented out some
 *				  defenitions that are defined in ../defs.h anyway.
 *				Also commented out the /d/Spakle...defs.h file since
 *				  the two are conflicting.
 *				Finally I included the vendor defenitions needed here.
 *				(Styles)
 *
 *
 *
 */


#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>


#include "../defs.h"
//#include "/d/Sparkle/area/city/defs.h"




/* Definitions */
//#define  TP					(this_player())
//#define  TO					(this_object())
//#define  NF(x)				(notify_fail(x))
//#define  HUMAN_DIR			("/d/Genesis/start/human/")
//#define  TOWN_DIR				(HUMAN_DIR + "town/")

#define NEW_SPARKLE_OBJ_DIR		"/d/Sparkle/area/city/obj/"
#define VENDORNAME				("_sparkle_quest_vendor")
#define MARKETDAY				"Wednesday"
#define BELLSOUND				" "
#define TELL_STY(x)				find_living("styles")->catch_tell( \
                                  ctime(time()) + BELLSOUND + x + "\n")




/* Prototpyes */
public void			enter_inv(object ob, object from);
public void			leave_inv(object ob, object to);
public void			check_market();
public int			prevent_rat();
public string		exa_well();




void
create_room()
{
    set_short("market square");
    set_long("\nYou're standing in a market square.\n"+
        "Many farmers and merchants are trying to sell their crops " +
        "and goods. Better keep a firm hand on your purse. There " +
        "is a fresh water well in the middle of the square. The " +
        "harbour is east of here, the shop is south and the road " +
        "towards the gates is leading west. On the north side of the "+
		"square, the treasury of Genesis is located.\n");

    add_item( ({ "office", "treasury" }), "On the north side of the " +
        "square, the office of the treasurer of Genesis is located. " +
        "In the treasury, the records of the treasurer are kept.\n");

    add_item("square","It is a quite ordinary market square.\n");

    add_item("well","The well seems old and well used. Nevertheless "+
        "it is kept in good working order. Peering down into the "+
        "darkness of the well, you see a reflection in the water "+
        "surface far down below.@@exa_well@@\n");

	add_item(({"reflection", "surface", "water"}),
		"The reflection in the water surface is at least ten meters "+
        "down. Free falling is not advised but you might be able to "+
        "climb down if you are skilled and brave enough...\n");

    add_item("shop","The shop is probably one of the major places "+
       "of commerce in this region. It should be able to supply you "+
       "with the items you need although the price may at times be "+
		"high.\n");

    add_item("people","Oh they're just commoners. "+
			 "Nothing special about them.\n");

    add_exit("road4", "west");
    add_exit("shop", "south");
    add_exit("pier4", "east");
    add_exit("bank", "north", prevent_rat);

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_cmd_item( ({ "from well", "water" }), "drink",
        "You take a sip of water from the well.\n" );

    
	room_add_object("/d/Genesis/obj/donation/column", 1);
    room_add_object("/d/Sparkle/area/city/auction/obj/tent", 1);

 /*
    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
  */
}





/*
 * Function name:	prevent_rat
 * Description:		We don't want rats, rodents or mice in the bank.
 * Returns:			int 1/0 - if true, it's a rodent we don't want.
 */
public int
prevent_rat()
{
    return this_player()->id("rat") || this_player()->id("rodent") || this_player()->id("mouse");
}


public string
exa_well()
{
	TELL_STY(TP->query_real_name() +" examined the well.\n");
	return"";
}


/*
 * Function name:	climb_down
 * Description:		
 * Returns:			1 or 0. Success or failure.
 */
public int
climb_down(string str)
{

    if (str != "down")
    {
        NF("Exactly where do you want to climb?\n");
		TELL_STY(TP->query_real_name() +" tried to <climb> ["+ str +"] in the marketplace.\n");
        return 0;
    }

    if (TP->query_skill(SS_CLIMB) > random(30))
	{
		write("You climb down into the well.\n");
        say( QCTNAME(TP) +" goes down the well.\n");
		TP->move_living("M", TOWN_DIR + "well");
		
		TELL_STY(TP->query_real_name() +" climbed down the well.\n");
	}
    else
    {
        write("You don't seem to be able to get a good hold. "+
			  "You fall down into the well.\n");
		say( QCTNAME(TP) +" falls down into the well.\n");
		TP->move_living("M", TOWN_DIR + "well");
		
        TP->heal_hp(-100);
        if (TP->query_hp() <= 0)
            TP->do_die(TO);
        else
            write("Ouch! That really hurt.\n");
		
		TELL_STY(TP->query_real_name() +" (HPB:"+ TP->query_hp() +") fell down the well.\n");
    }

    return 1;
}


public int
drop_stuff(string str)
{
	// I haven't gotten around to implementing the code for dropping
	// things into the well. Non living objects should end up in
	// the pool object while livings has to climb or fall down by
	// themselves. Also, make sure that the pool is loaded.
	// -Styles.

	if (str == "test")
	{
		object well_room = find_object(
			"/d/Genesis/start/human/town/well.c");
		object pool = well_room->query_pool();

		if (!pool)
			write("DEBUG: No pool loaded.\n");
		else
			write("DEBUG: "+ file_name(pool) + "\n");
		return 1;
	}

	return 0;  
}




/*
 * Function name:	init
 * Description:		
 * Returns:			
 */
public void
init()
{
    ::init();

    add_action(climb_down, "climb");
	add_action(drop_stuff, "drop");

}





/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * I am redefining this function to allow for the market to show up
 * at the beginning of each Wednesday and leave when that Wednesday
 * is over.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob->id(VENDORNAME))
    {
        check_market();
    }
} /* enter_inv */





/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * I am redefining this function to allow for the market to show up
 * at the beginning of each Wednesday and leave when that Wednesday
 * is over.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!ob->id(VENDORNAME))
    {
        check_market();
    }
} /* leave_inv */






/*
 * Function name:        check_market
 * Description  :        See if it is the correct day for the Market
 *                       to come to town. It happens only on the
 *                       day defined by MARKETDAY in the defs.h file.
 */
public void
check_market()
{
    object  market;

    if (!objectp(market = present(VENDORNAME, this_object())))
    {
        if (ctime(time())[0..2] == MARKETDAY[0..2])
        {
            room_add_object(NEW_SPARKLE_OBJ_DIR + "questvendor");
            tell_room(this_object(),
                "A cart laden with many supplies rolls suddenly into"
              + " the square followed by another, and another. Vendors"
              + " soon crowd the street on all corners, setting up"
              + " tables and displaying their wares. One erects a"
              + " large kiosk and loudly proclaims, \"The "
              + MARKETDAY + " Market is now open for business! May"
              + " it be a profitable day for all!\"\n");
        }
    }
    else
    {
        if (ctime(time())[0..2] != MARKETDAY[0..2])
        {
            set_alarm(1.0, 0.0, &market->goodbye());
        }
    }
} /* check_market */




