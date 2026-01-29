/*
 * A token for the novelty shop
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#define SPIN "_i_can_spin_the_wheel"

	string adj1 = "small";
	string adj2 = "brass";
	string name = "token";
	
 void
 create_object()
 {
	 
	 
	 set_name("_novel_token");
	 add_name(name);
	 set_adj(adj1);
	 add_adj(adj1);
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " bears the stamp of "
		+ "Waymeet's novelty shop--a moustache! You could use "
		+ "it to spin the wheel in the shop.\nIf you no longer "
		+ "need the token, you can discard it.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VALUE, 1);
	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_M_NO_GIVE, 1);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_discard", "discard");
 }
 
 //here we remove_object() and remove_prop so the player can pay the fee in the novelty shop later if he wants to.
 int
 do_discard(string str)
 {
	 if( (str == name) | (str == (adj1 + " " + name)) | (str == (adj2 + " " + name)) | (str == (adj1 + " " + adj2 + " " + name)))
	 {
		 write("You discard the " + query_short() + ".\n");
		 say(QCTNAME(TP) + " discards the " + query_short() + ".\n");
		 TP->remove_prop(SPIN);
		 TO->remove_object();
		 return 1;
	 }
	 else
	 {
		 notify_fail("Discard what? The " + name + "?\n");
		 return 0;
	 }
 }
 