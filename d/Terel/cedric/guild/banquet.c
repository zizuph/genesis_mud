#pragma save_binary

inherit "/std/room.c";
inherit "/lib/pub.c";

#include "/d/Terel/cedric/guild/guild_defs.h"
#include <stdproperties.h>

/*
 * The Minstrel Guild Headquarters: The Banquet Hall.  
 * Fine foods and drinks are served...at a price.
 * Jorl 2/93
 */

object monger;

int
check_enter()
{
    if (MEMBER(TP()) || TP()->query_wiz_level())
    {
	TP()->catch_msg("You pass through the great hall and enter the inner "
	+ "sanctum.\n");
	return 0;
    }
    else
	TP()->catch_msg(("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n"));
    return 1;
}

init()
{
    ::init();
    init_pub();
}

reset_room()
{
    if (!monger) {
        monger = clone_object(GUILD + "Npcs/rm");
        monger -> move(TO());
    }
}

/*
 * Function:	fix_drink
 * Description:	masks fix_drink() in /lib/pub, which this room inherits.
 *		The purpose is to filter out the special drink of lemon
 *		tea which minstrels can buy here. The tea is only a
 *		mild drink but it heals the vocal damage minstrel singers
 *		may sustain. I had to do it this way so that the tea would
 *		inherit a different object.
 */
object
fix_drink(mixed data)
{
    object ob;

    if ((string) data[0] == "tea")
    {
	ob = clone_object(GUILDOBJ+"tea");
	ob->set_name(data[0]);
	ob->set_adj(data[1]);
	ob->set_soft_amount(data[2]);
	ob->set_alco_amount(data[3]);
	ob->set_short(data[5]);
	ob->set_pshort(data[6]);
	ob->set_long(data[7]);
	ob->add_prop(HEAP_I_UNIT_VOLUME, data[2] + data[3]);
	ob->add_prop(HEAP_I_UNIT_WEIGHT, data[2] + data[3]);
	ob->add_prop(HEAP_I_UNIT_VALUE, data[4]);
	
	return ob;
    }
    else
	return ::fix_drink(data);
}


create_room()
{
    set_short("The Grand Banquet Hall of the Minstrels");
    set_long(BS("This grand hall is where minstrels, weary from the "
    + "chores of entertaining princes, nobles, and paupers alike, come "
    + "to refresh themselves in the company of friends.  Several long "
    + "stone tables are here as well as some padded benches for your "
    + "dining comfort.\n") +  "\n              MENU        \n"
        + "   Watery ale               6 cc\n" 
        + "   Elderberry wine         20 cc\n" 
        + "   Warm brandy             50 cc\n"
        + "   Hearty rum             150 cc\n\n"
	+ "   Soothing lemon tea     80 cc\n\n"  
        + "   Venison stew            15 cc\n"
        + "   Leg of lamb             90 cc\n" 
        + "   Pheasant under glass   220 cc\n\n");

    
    add_item(({"table", "tables"}), BS("These beautiful stone tables are carved "
    + "from a rich black granite, their surfaces kept polished to a reflective "
    + "shine.\n"));
    add_item(({"bench", "benches", "chair", "padded bench"}), BS("The dark oaken wood "
    + "for these comfortable benches comes from the enchanted forest.  They look "
    + "quite soft.\n"));

    add_exit(GUILD+"nice", "east");
    add_exit(GUILD+"training", "southwest", "@@check_enter");
    add_prop(ROOM_I_INSIDE, 1);
    
    add_cmd_item("menu", ({"examine", "exa", "read"}), ({"@@read", "@@read", "@@read"}));
    
    add_drink(({"ale", "ales", "watery", "watery ale"}),
        "ale", "watery", 250, 2, 6, 0, 0,
        "It's a bit weak but it quenches your thirst.\n", 0);
    add_drink(({"wine", "wines", "elderberry", "elderberry wine"}),
        "wine", "elderberry", 200, 10, 20, 0, 0,
        "It's bouquet is intoxicating.\n", 0);
    add_drink(({"brandy", "warm", "brandys", "warm brandy"}),
        "brandy", "warm", 150, 25, 50, 0, 0,
        "This ought to warm your toes.\n", 0);
    add_drink(({"rum", "rums", "hearty", "hearty rum"}),
        "rum", "hearty", 150, 50, 150, 0, 0,
        "It's imported from a tropical island.\n", 0);
    add_drink(({"tea", "teas", "soothing", "lemon", "soothing lemon tea",
	      "lemon tea"}), "tea", ({"soothing", "lemon"}),
	      100, 0, 80, 0, 0,
	      "It's rumored that lemon tea is good for the voice.\n", 0);

    add_food(({"stew", "stews", "venison", "venison stew"}), 
        "stew", "venison", 25, 15, "bowl of venison stew", 
        "bowls of venison stew", 
        "The aroma reminds you of mom's home cookin'.\n", 0);
    add_food(({"leg", "legs", "lamb", "leg of lamb"}), 
        ({"lamb", "leg"}), 0, 75, 90, "leg of lamb", "legs of lamb", 
        "This is a succulent-looking piece of meat.\n", 0);
    add_food(({"pheasant", "pheasants", "pheasant under glass"}), 
        "pheasant", "cooked", 200, 220, "pheasant under glass", 
        "pheasants under glass", "A meal fit for a king!\n", 0);
         
    reset_room();
}

int
read(string str)
{
    write("\n              MENU        \n"
                + "   Watery ale               6 cc\n" 
                + "   Elderberry wine         20 cc\n" 
                + "   Warm brandy             50 cc\n"
                + "   Hearty rum             150 cc\n\n"  
                + "   Venison stew            15 cc\n"
                + "   Leg of lamb             90 cc\n" 
                + "   Pheasant under glass   220 cc\n\n");
        return 1;
}
