/*
 * A balloon
 *
 * --Raymundo, Jan 2020
 * The main point of this balloon is that players will willingly put their
 * lips on an animals large intestine. You're welcome, Genesis.
 * 
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#define BLOWN 	"i'm_blown_up"
#define TIED 	"i'm_tied_into_shape"
#define ADJ2	({"red", "yellow", "blue", "black", "purple", "pink", "green"})
#define ADJ1	({"long", "stubby", "thick", "squiggly"})

string name, adj1, adj2, extra;
 void
 create_object()
 {
	 adj1 = ONE_OF_LIST(ADJ1);
	 adj2 = ONE_OF_LIST(ADJ2);
	 name = "balloon";
	 
	 set_name(name);
	 add_name("balloon");
	 set_adj(adj1);
	 add_adj(adj1);
	 set_short(adj1 + " " + adj2 + " " + name);
	 set_long("@@my_long@@");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 1000);
	add_prop(OBJ_I_WEIGHT, 20);
	add_prop(OBJ_I_VALUE, 1);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_blow", "blow");
	 add_action("do_tie", "tie");
	 add_action("do_pop", "pop");
	 add_action("do_smell", "smell");
 }
 
 //That barnyard aroma
 int
 do_smell(string str)
 {
	 if(str == name | str == "balloon")
	 {
		 say(QCTNAME(TP) + " places " + HIS_HER(TP) + " nose next to the "
			+ "end of the " + name + " and inhales. " + CAP(HE_SHE(TP))
			+ " looks like " + HE_SHE(TP) + " just smelled the inside of a "
			+ "toilet!\n");
		write("You place your nose next to the opening of the " + name
			+ ". Ugh! It smells like shit!\n");
		return 1;
	 }
	 else
	 {
		 return 0;
	 }
 }
 //blows up the balloon. changes its long description (with the add prop)
 int
 do_blow(string str)
 {
	 if(!strlen(str))
	 {
		 notify_fail("Blow up what? The balloon?\n");
		 return 0;
	 }
	if(parse_command(str, TO, "[up] [the] 'balloon' ") )
	{
		if(TO->query_prop(BLOWN))
		{
			write("The balloon is already blown up!\n");
			return 1;
		}
		add_prop(BLOWN, 1);
		write("You blow up the balloon.\n");
		say(QCTNAME(TP) + " blows up the " + name + ".\n");
		return 1;
	}
	else
	{
		notify_fail("Blow up what? The balloon?\n");
		return 0;
	}
 }
 
 //The shape you tie it into
 void
 tie_balloon()
 {
	
	 int x;
	 x = (random(4));
	 switch(x)
	 {
		 case 0:
		 name = "balloon horse";
		 add_name("horse");
		
		 extra = ("You see a long nose, some small ears, four legs, and a tail. "
			+ "0h! This is a horse balloon animal!\n");
		 break;
		 
		 case 1:
		 name = "balloon eagle";
		 add_name("eagle");
		 
		 extra = ("You see a beak, two wings, and some tail feathers. Oh! This is "
			+ "an eagle balloon animal!\n");
		break;
		
		 case 2:
		 name = "balloon orc";
		 add_name("orc");
		 
		 extra = ("You see an ugly hooked nose, claw-like fingers, and a face "
			+ "not even a mother could love. Oh! This is an orc balloon animal!\n");
		break;
		
		 case 3:
		 name = "balloon fish";
		 add_name("fish");
		 
		 extra = ("You see a mouth, some gills, and a few fins. Oh! This is a "
			+ "fish balloon animal!\n");
		break;
		 
	 }
		add_adj("balloon");
		adj1 = "hand-tied";
		write("You tie the balloon into a " + name + ".\n");
		 say(QCTNAME(TP) + " ties the balloon into a " + name + ".\n");
		
		//reset the short description to match the animal.		 
		 set_short(adj1 + " " + adj2 + " " + name); 
		 return ;
 }
		 
 //Tie the balloon
 int
 do_tie(string str)
 {
	 if(!strlen(str))
	 {
		 notify_fail("Tie what? The balloon?\n");
		 return 0;
	 }
	 if(parse_command(str, TO, "[up] [the] 'balloon' [into] [a] [shape] ") )	
	 {
		 if(!TO->query_prop(BLOWN))
		 {
			 notify_fail("You need to blow up the balloon first!\n");
			 return 0;
		 }
		 if(TO->query_prop(TIED))
		 {
			 notify_fail("The balloon is already tied into a cute "
				+ "animal shape!\n");
				return 0;
		 }
		 add_prop(TIED, 1);
		set_alarm(1.0, 0.0, tie_balloon);
		 return 1;
	 }
	 else
	 {
		 notify_fail("Tie what? The balloon?\n");
		 return 0;
	 }
 }
 //pop the balloon
 int
 do_pop(string str)
 {
	 if(!TO->query_prop(BLOWN))
	 {
		 notify_fail("You can't pop the balloon if it's not blown up!\n");
		 return 0;
	 }
	 if(str == "balloon" | str == "animal" | str == name)
	 {
		 write("You pop the " + name + "!\n");
		 say(QCTNAME(TP) + " pops the " + name + "!\n");
		 remove_object();
		 return 1;
	 }
	 else
	 {
		 notify_fail("Pop what? The balloon?\n");
		 return 0;
	 }
 }
 
 //long description
 string
 my_long()
 {
	 if(TO->query_prop(TIED))
	 {
		 return("This balloon looks like it was made from a goat's large "
			+ "intestine. The balloon has been tied into the shape of a "
			+ "cute little animal. " + extra + "Be careful so you don't "
			+ "pop it!\n");
	 }
	 if(TO->query_prop(BLOWN))
	 {
		 return("The " + name + " has been blown up so that it sticks "
			+ "straight out like an arrow or staff. It looks very much like a "
			+ "goat's large intestine. Come to think of it, there's enough "
			+ "balloon here that you could tie it into a shape.\n");
	 }
	 else
	 {
		 return("The " + name + " is flacid and useless. It has the shape and "
			+ "smell of a goat's large intestine. It has been painted " + adj2 
			+ ". You should "
			+ "probably blow it up.\n");
	 }
 }
 
 //short description
 string
 my_short()
 {
	 return(adj1 + " " + adj2 + " " + name);
 }