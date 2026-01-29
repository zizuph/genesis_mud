/*
 * A wheel for the novelty shop
 * Took me a while, but I think I like how this works.
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#define SPIN "_i_can_spin_the_wheel"
#define SLOT "_i_put_in_coin"
#define SCAV_DIR 	"/d/Shire/scav_hunt/"
#define OBJ 	({SCAV_DIR + "duster", SCAV_DIR + "cow_bell", WAYM_OBJ_DIR + "balloon_animal", SCAV_DIR + "bubbles", SCAV_DIR + "cigar", SCAV_DIR + "whistle", "/d/Shire/eastroad/western/arm/fake_moustache"})

	string adj1 = "large";
	string adj2 = "round";
	string name = "wheel";
	
	
 void
 create_object()
 {
	 
	 
	 set_name(name);
	 set_adj(adj1);
	 add_adj(adj1);
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " is big and round. On it, you can see "
		+ "pictures painted. There is an arrow that points at one of the "
		+ "pictures. You can see a slot on the stand just under the wheel. "
		+ "You can spin it.\n");
	add_item("slot", "The slot is big enough for you to insert a token into it.\n");
	add_item( ({"picture", "pictures"}), "There are several different pictures here. "
		+ "They seem to represent items you could get from spinning the wheel!\n");
	add_item( ({"arrow", "arrows"}), "The arrow will point at the item you win. "
		+ "Spin the wheel to see how it works.\n");
	add_item("stand", "The stand is about as big as your two fists put together. "
		+ "It holds the wheel up.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 100000);
	add_prop(OBJ_I_WEIGHT, 100000);
	add_prop(OBJ_I_VALUE, 1);
	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_M_NO_GIVE, 1);
	add_prop(OBJ_M_NO_GET, 1);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_insert", "insert");
	 add_action("do_spin", "spin");
 }
 //Insert a token in order to spin the wheel.
 int
 do_insert(string str)
 {
	 object *inv;
	 int i = 0;
	 inv = all_inventory(this_player());
	 if(TP->query_prop(SLOT)) //Can't insert a token if you already have one inserted.
	 {
		 write("You've already inserted a token into the slot. Go ahead and spin the wheel!\n");
		 return 1;
	 }
	 for (i=0; i<sizeof(inv); i++)
	 {
		 if(inv[i]->id("_novel_token"))
		 {
			 if(!strlen(str))
			{
            notify_fail("Insert what? The token? Into the slot?\n");
            return 0;
			}
			if (parse_command(str, TO, "[the] 'token' [into] [in] [the] [slot] ") )
			{
				if(TP->query_prop(SLOT))
				{
					write("You have already put a token in the slot. Just spin "
						+ "the wheel.\n");
						return 1;
				}
				write("You insert your token into the slot. You can now spin the wheel.\n");
				say(QCTNAME(TP) + " inserts a token into the slot.\n");
				inv[i]->remove_object();
				TP->remove_prop(SPIN);
				TP->add_prop(SLOT, 1);
				return 1;
			 
			}
			else
			{
				notify_fail("Did you mean to insert the token into the slot?\n");
				return 0;
			}
		 }
	 }
	 notify_fail("You need a token to spin the wheel.\n");
	 return 0;
 }
 
 //spin the wheel
 int
 do_spin(string str)
 {
	 string obj = ONE_OF_LIST(OBJ); //we can add novel items in the #define section
	 if(!TP->query_prop(SLOT))
	 {
		 notify_fail("You need to insert a token into the slot first.\n");
		 return 0;
	 }
	 if(str == "the " + name | str == name | str == adj1 + " " + name | str == adj2 + " " + name | str == adj1 + " " + adj2 + " " + name)
	 {
		 write("You spin the wheel!\n");
		 say(QCTNAME(TP) + " spins the wheel!\n");
		object novelty;
		novelty = clone_object(obj);
		novelty->move(TP);
        say("The wheel lands on a " + novelty->query_short() + " and " 
            + QCTNAME(TP) + " picks it up!\n");
		write("The wheel stops on a " + novelty->query_short() + "! You pick it up.\n");
		TP->remove_prop(SLOT);
		return 1;
	 }
	 else
		 notify_fail("Spin what? The wheel?\n");
	 return 0;
 }