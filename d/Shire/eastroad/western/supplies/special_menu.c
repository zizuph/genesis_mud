/*
 * A special menu
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>


 void
 create_object()
 {
	 string adj1 = "off-white";
	 string adj2 = "vellum";
	 string name = "menu";
	 
	 set_name(name);
	 add_name("vellum");
	 set_adj(adj1);
	 add_adj(adj1);
	 add_adj("special");
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " lists all the drinks "
		+ "you can purchase at the Upstairs Bar in the Foaming "
		+ "Mug. There are words you can read on the menu.\n"
		+ "\nFeel free to return it when you're done.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_I_WEIGHT, 2);
	add_prop(OBJ_I_VALUE, 0);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_read", "read");
	 add_action("do_return", "return");
 }
 
 string
 menu_text()
 {
	 	return( "\n"
	+ "+==============================================+\n"
	+ "|                DRINK MENU                    |\n"
	+ "------------------------------------------------\n"
	+ "| Martini ...................  1 Platinum Coin |\n"
	+ "|                                              |\n"
	+ "+==============================================+\n"
	+ "|                                              |\n"
	+ "|     For Our Most Valued Clients, We Offer    |\n"
	+ "|         A Selection of Premium Liquors       |\n"
	+ "+==============================================+\n"
	+ "|                                              |\n"
	+ "| Whiskey .................... 1 Platinum Coin |\n"
	+ "| Vodka ...................... 1 Platinum Coin |\n"
	+ "| Schnapps ................... 1 Platinum Coin |\n"
	+ "| Brandy ..................... 1 Platinum Coin |\n"
	+ "| White Lightning ............ 1 Platinum Coin |\n"
	+ "| Gin ........................ 1 Platinum Coin |\n"
	+ "|                                              |\n"
	+ "+==============================================+\n");
 }
 
 int
 do_read(string str)
 {
	 if(str == "menu" | str == "special menu" | str == "vellum")
	 {
		 write(menu_text());
		 return 1;
	 }
	 else
	 {
		 notify_fail("Read what? The menu?");
		 return 0;
	 }
 }
 
 int
 do_return(string str)
 {
	 if(str == "menu" | str == "special menu" | str == "vellum")
	 {
		 write("You return your menu to the Foaming Mug.\n");
		 TO->remove_object();
		 return 1;
	 }
	 else
	 {
		 notify_fail("Return what? Your menu?\n");
		 return 0;
	 }
 }