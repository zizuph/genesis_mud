/*
 * An herb jar for the Foaming Mug Quest
 * /d/Shire/eastroad/western/foam_mug_up.c
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/container";
inherit "/lib/keep";


#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>



 void
 create_container()
 {
	 string adj1 = "small";
	 string adj2 = "herb";
	 string name = ("jar");
	 
	 set_name("_still_herb_jar");
	 add_name(name);
	 add_adj(TP->query_met_name());
	 add_adj(TP->query_met_name() + "'s");
	 add_adj(TP->query_met_name() + "s");
	 set_adj(adj1);
	 add_adj(adj1);
	 add_adj("distillery");
	 set_short(TP->query_met_name() + "'s " + adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " is a very small jar, big enough "
		+ "for a dozen or so herbs. It has a picture of a foaming mug of "
		+ "beer on it, reminding you that this jar needs to be returned to "
		+ "The Foaming Mug in Waymeet. There is a label on the back.\n");
		
	add_item("label", "@@exa_label@@");
	add_cmd_item("label", "read", "@@exa_label@@");

	setuid();
	seteuid(getuid());
	
	add_prop(CONT_I_WEIGHT, 250);
	add_prop(CONT_I_MAX_WEIGHT, 1000);
	add_prop(CONT_I_VOLUME, 250);
	add_prop(CONT_I_MAX_VOLUME, 1000);
	add_prop(OBJ_M_NO_BUY, 1);
	
	add_prop(OBJ_M_NO_SELL, 1);
	add_prop(OBJ_I_VALUE, 1728);
	set_keep(1);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_discard", "discard");
 }
 

 public int
 query_jar_full()
 {
	 int berry = 0;
	 object *inv;
	 int i = 0;
	 inv = all_inventory(this_object());
	 
	 for (i=0; i<sizeof(inv); i++)
	 {
		 if(inv[i]->id("juniper_berry"))
		 {
			return(inv[i]->num_heap());
		 }
	 }
	 
 }
 
 string
 exa_label()
 {
	 return("The label reads:\n"
		+ "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n"
		+ "| Please return this jar to Tarlas at the Foaming |\n" 
		+ "| Mug Inn in Waymeet. If this is not your jar,    |\n"
		+ "| please just <discard> it.                       |\n"
		+ "| Thanks!                                         |\n"
		+ "|                                                 |\n"
		+ "| --Tarlas                                        |\n"
		+ "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
 }
	 
 int
 do_discard(string str)
 {
	 if(str == "jar" | str == "herb jar")
	 {
		 write("You toss the " + query_short() + " on the ground and "
			+ "it breaks into many, many tiny pieces.\n");
		say(QCTNAME(TP) + " tosses the " + query_short() + " on the "
			+ "ground, and it breaks into many, many tiny pieces.\n");
		remove_object();
		return 1;
	 }
	 else
	 {
		 notify_fail("Discard what? The jar?\n");
		 return 0;
	 }
 }