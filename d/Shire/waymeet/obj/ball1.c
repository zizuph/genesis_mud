/*
 * A Ball
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
	 set_name("ball");
	 set_adj("brown");
	 add_adj("leather");
	 set_short("brown leather ball");
	
	 
	 set_long("Perfectly round and surprisingly heavy, the " + query_short()
		+ " looks like exactly the sort of thing a few kids would play with. "
		+ "Normally a ball like this would be made from a pig's bladder, "
		+ "inflated with air, and then wrapped in leather, but this ball "
		+ "belongs to a hobbit child, and a pig's bladder ball is way too "
		+ "big for hobbits. As a result, this ball was likely made from "
		+ "a goat or lamb bladder.\n");

	add_item( ({"bladder"}), "You can't see the bladder. It's inside the "
		+ "ball. However, you notice that the ball is quite firm, indicating "
		+ "that the bladder still holds air well.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 500);
	add_prop(OBJ_I_WEIGHT, 500);
	add_prop(OBJ_I_VALUE, 1);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_throw", "throw");
	 add_action("do_throw", "toss");
	 add_action("do_throw", "fling");
	 add_action("do_bounce", "bounce");
	
 }
 
 //bounce the ball!
 int
 do_bounce(string str)
 {
	 if(str == "ball")
	 {
		 write("You bounce the ball up and down a few times. It's fun "
			+ "to play games!\n");
		say(QCTNAME(TP) + " bounces the ball up and down a few times. "
			+ CAP(HE_SHE(TP)) + " looks like " + HE_SHE(TP) 
			+ " is really having run playing a game!\n");
		return 1;
	 }
	 else
	 {
		 notify_fail("Bounce what? The ball?\n");
		 return 0;
	 }
 }
 
 //Play catch!
 int
 do_throw(string str)
 {
	 object* targ;
	 if(!strlen(str))
	 {
		 say(QCTNAME(TP) + " throws the ball up in the air and catches it.\n");
		 notify_fail("You toss the ball up in the air and catch it. "
			+ "But wouldn't it be fun to play catch with someone else?\n");
		 return 0;
	 }
	
	 targ = parse_this(str, " [the] [brown] [leather] 'ball' [at] [to] %l ");
	 if(!sizeof(targ))
	 {
		 notify_fail("Throw the ball to whom?\n");
		 return 0;
	 }
	 else
	 {
		 actor("You throw the " + query_short()
			+ " to",targ,".\n");
		 all2actbb(" throws the " + query_short() + " to",targ,".\n");
		targetbb(" throws the " + query_short() + " to you.\n",targ);
		int try_catch = (random(3));
		if(try_catch == 0)
		{
			tell_room(environment(targ[0]), QCTNAME(targ[0]) +
				" tries to catch the ball but fails! " + CAP(HE_SHE(targ[0]))
				+ " drops the ball!\n", targ[0]);
			targ[0]->catch_tell("You try to catch the ball but fail! You drop "
				+ "the ball!\n");
			TO->move(environment(targ[0]));
			return 1;
		}
		else
		{
		TO->move(targ[0]);
		return 1;
		}
	 }
 }
 
 string query_recover() 
{ 
    return MASTER + ":"; 
}
