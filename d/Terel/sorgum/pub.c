/* -*- C++ -*- */

/*
 * pub.c
 *
 * Copied from /doc/examples/trade/pub.c by Vader, and adpated
 * for use in the Terel domain.  Modified on 6/27/92
 *
 * Modified by Sorgum 960101
 */

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/lib/pub";

/*
 * Function name: query_object_list
 * Description:   return list of object to clone at each reset.
 */
public string*
query_object_list()
{
    return ({"/d/Terel/common/town/barkeep",
	     "/d/Terel/common/town/old_man"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room ();
    set_short("Big Rock Pub");
    set_long("This is the Big Rock Pub, by far one "+
	     "of the finest establishments on the continent.  It is " +
	     "frequented by everyone in Calathin, plus many a traveler.  " +
	     "There are paintings all around of all the great people " +
	     "that have visited this pub.  There are many tables here " +
	     "where the patrons sit, chat, and get wasted.  There is a " +
	     "menu posted on the south wall.\n");

    add_item(({"table", "tables"}),
	     "These tables have seen a lot of use over the years.\n");

    add_item(({"paintings", "painting", "pictures", "picture"}), 
	     "You see the unmistakable likenesses of such great ones " +
	     "as\n" +
	     "Lord Sorgum\n" +
	     "Sir Azireon\n" +
	     "Dame Mortricia\n" +
	     "Sir Dust\n" +
	     "Sir Cedric\n" +
	     "Dame Napture\n" +
	     "Sir Janus\n" +
	     "Sir Redhawk\n" +
	     "Master Tintin\n" +
	     "Honourable Fatty\n" +
	     "Proctor Mecien\n");

    add_item(({"menu"}), "@@menu_descrip");
    add_cmd_item("menu", ({"read", "list"}), ({"@@read_menu", "@@read_menu"}));
    add_exit("/d/Terel/common/town/square3_4", "north", 0);

    add_drink (({"beer", "beers"}), /* ids */
	       ({"beer", "beers"}), /* names */
	       "silver",            /* adj */
	       100,                 /* soft */
	       4,                   /* alco */
	       12,                  /* price */
	       0,                   /* short */
	       0,                   /* pshort */
	       "It's a small beer, oddly, silver in color.\n", 0);

    add_drink (({"special", "specials"}),    /* ids */
	       ({"special", "specials"}),    /* names */
               "terellian",                  /* adj */
	       62,                           /* soft */
	       25,                           /* alco */
	       70,                           /* price */
	       0,                            /* short */
	       0,                            /* pshort */
	       "A Special brew made exclusivly at the Big Rock Pub.\n", 0);

    add_drink (({"chonyak", "chonyaks"}),    /* ids */
	       ({"chonyak", "chonyaks"}),    /* names */
	       "fine",                       /* adj */
	       40,                           /* soft */
	       2,                            /* alco */
	       10,                           /* price */
	       0,                            /* short */
	       0,                            /* pshort */
	       "A full snifter of chonyak\n", 0);

    add_drink (({"whiskey", "whiskeys"}),    /* ids */
	       ({"whiskey", "whiskeys"}),    /* names */
	       "green",                      /* adj */
	       84,                           /* soft */
	       50,                           /* alco */
	       260,                          /* price */
	       0,                            /* short */
	       0,                            /* pshort */
	       "A fine whiskey, with a peculiar green colour.\n");

    add_drink (({"coffee",}),    /* ids */
	       ({"coffee",}),    /* names */
	       "strong",                      /* adj */
	       84,                           /* soft */
	       -50,                           /* alco */
	       100,                          /* price */
	       0,                            /* short */
	       0,                            /* pshort */
	       "A strong coffee, with a delicious fragrance.\n");    
    
    INSIDE;

   reset_room();

}

/*
 * Function name: menu_descrip
 * Description:   VBFC for the menu
 * Returns:       what is written on the menu
 */
public string
menu_descrip ()
{
    return ("   A Silver Beer             12 cc\n" +
	    "   A Snifter of Chonyak      10 cc\n" +
	    "   A Terellian Special       70 cc\n" +
	    "   A Green Whiskey          260 cc\n");
}

/*
 * Function name: read_menu
 * Description:   Handle the read action for the menu
 * Returns:       1/0
 */
public int
read_menu ()
{
    write(menu_descrip());
    say(QCTNAME(this_player()) + " reads the menu on the south wall.\n");
    return 1;
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); 
    init_pub();
}

/*
 * Function name: pay_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 */
void
pub_hook_player_buys(object ob, int price)
{
    ::pub_hook_player_buys(ob, price);

    ob->add_prop(OBJ_M_NO_SELL, "No one has issued you a license " +
                 "to sell alcoholic beverages!\n");
}
