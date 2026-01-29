/*
 * A Hat Pin
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";
inherit "/lib/commands.c";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

 void
 create_object()
 {
	 set_name("pin");
	 set_adj("brass");
	 add_adj("hat");
	 set_short("brass hat pin");
	
	 
	 set_long("At a bit more than a hand in length, this pin is long enough "
		+ "to hurt. It's sharp on one end and has a cut-glass ruby handle "
		+ "on the other. It would be useful for a hobbit woman to use if "
		+ "wanted to keep her hat on her head. Whoever lost this pin must "
		+ "really miss it!\n");

	add_item( ({"handle", "cut-glass handle", "ruby handle"}),
		"The handle is large enough to grasp between your thumb and a couple "
		+ "of fingers so that you can carefully manipulate the pin and not "
		+ "accidentally poke yourself.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 50);
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VALUE, 2);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_poke", "poke");
	
 }
 
 //Go poke someone! 
 int
 do_poke(string str)
 {
	 object* targ;
	 if(!strlen(str))
	 {
		 notify_fail("Poke whom with your hat pin?\n");
		 return 0;
	 }
	
	 targ = parse_this(str, " %l 'with' [the] [brass] [hat] 'pin' ");
	 if(!sizeof(targ))
	 {
		 notify_fail("Poke whom with your hat pin?\n");
		 return 0;
	 }
	 else
	 {
		 actor("You poke",targ," with your " + query_short() + ". Ouch!\n");
		 all2actbb(" pokes",targ," with " + HIS_HER(TP) + " " 
			+ query_short() + ". Ouch!\n");
		targetbb(" pokes you with " + HIS_HER(TP) + " " + query_short()
			+ ". Ouch!\n",targ);
		return 1;
	 }
 }
 
 string query_recover() 
{ 
    return MASTER + ":"; 
}
