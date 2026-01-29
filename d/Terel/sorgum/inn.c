/* -*- C++ -*- */

/*
 *  Calathin Inn,
 *  based on the original Hobbiton Bakery.
 *  Modified by Vader  on 920703
 *  Modified by Sorgum on 960101
 */

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
    return ({"/d/Terel/common/town/inn_keep"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Calathin Inn");
    set_long("You are now in the Inn of Calathin.  Never will you find " +
	     "a finer example of quality food and service.  There are many " +
	     "tables here, where people from all over the world have dined " +
	     "on the famous Beaver Stew.  No one really knows exactly what " +
	     "ingredient gives it its taste. The entire building is made " +
	     "from finely polished and carved wood, with a gothic skylight " +
	     "casting shadows of many different colours across the room.  " +
	     "There is a menu on a table that you can read.  " +
	     "There is also a large chair at one of the tables.\n");

    add_item(({"table", "tables"}),
	     "They are made of solid oak, and are covered by tablecloths.\n");
    
    add_item(({"skylight", "gothic skylight"}),
	     "It depicts several angels with musical instruments.\n");
    
    add_item(({"menu"}), "@@price_long");
    add_cmd_item("menu", "read", "@@read");

    add_item(({"chair", "large chair"}),
	     "A rather large chair, covered in dust from lack " +
	     "of recent use.  It is made from leather, and has the " +
	     "word 'Fatty' stitched into the back of it.\n");

    INSIDE;
    
    add_food (({"stew", "stews"}), /* ids */
	      ({"stew", "stews"}), /* names */
	      "beaver",            /* adj */
	      150,                 /* ammount */
	      30,                  /* price */
	      0,                   /* short */
	      0,                   /* pshort */
	      "A thick bowl of stew, made from fresh beaver.\n", 0);

    add_food (({"pie", "pies"}), /* ids */
	      ({"pie", "pies"}), /* names */
	      "turkey",          /* adj */
	      93,                /* ammount */
	      70,                /* price */
	      0,                 /* short */
	      0,                 /* pshort */
	      "A large portion of turkey pie!  Your favourite!\n", 0);

    add_food (({"surprise", "surprises"}), /* ids */
	      ({"surprise", "surprises"}), /* names */
	      "squirrel",                  /* adj */
	      70,                          /* ammount */
	      30,                          /* price */
	      0,                           /* short */
	      0,                           /* pshort */
	      "This is a mixture of fresh squirrel meat, and grain!\n", 0);

    add_food (({"jerky", "jerky strip", "jerky strips"}), /* ids */
	      ({"jerky", "jerky strip", "jerky strips"}), /* names */
	      "strip",                                    /* adj */
	      15,                                         /* ammount */
	      12,                                         /* price */
	      0,                                          /* short */
	      0,                                          /* pshort */
	      "A long strip of jerky, made from a local animal.\n", 0);

    add_exit ("/d/Terel/common/town/square2_4", "north", 0);
    reset_room ();
	      
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 *                Also call init_pub() to set up the pub.
 */
public void
init()
{
    ::init();
    init_pub();
}

/*
 * Function name: read
 * Description:   Handle the read action for the menu
 * Returns:       1/0
 */
public int
read (string str)
{
    write ("The menu reads:\n\n" +
	   "Beaver Stew .................165 Copper coins\n" +
	   "Turkey Pie .................. 70 Copper Coins\n" +
	   "Squirrel Surprise ........... 30 Copper Coins\n" +
	   "Jerky Strip ................. 12 Copper Coins\n");
    return 1;
}

