/*
 * The code for the forsaken inn is basically the same as for the prancing 
 * pony in Bree, /d/Shire/common/bree/inn.c
 * The code for The Foaming Mug inn is taken from both of the above.
 *
 *  Recoded for Waymeet
 *  --Raymundo, March 2020
 */

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Gondor/open/room_chairs/room_chairs";


#include "/d/Shire/sys/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include "/d/Shire/eastroad/western/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"



#define PRICELIST_ID ({"pricelist", "list", "menu", "prices"})
#define SUPL_DIR "/d/Shire/eastroad/western/supplies/"
#define SOFA_NAME "barstool"
#define JUNIPER "_i_picked_juniper_berries"
#define NO_SERVE "_waymeet_no_serve_alcohol"

public void	init();
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);	/* VBFC for chairs */

static object barman;

int window_open = 0;
int is_chandelier = 1;

int
block_people()
{
	if(TP->query_wiz_level())
	{
		barman->command("say Welcome, Oh great one! Please head upstairs!");
		return 0;
	}
	if(TP->query_prop(NO_SERVE))
	{
		write("You don't feel welcomed to go upstairs after puking all "
            + "over the floor!\n");
		return 1;
	}
	if(TP->query_prop(JUNIPER)| CHECK_QUEST(TP, "fix_still"))
	{
		write("The bartender winks at you and you know you are allowed to "
			+ "go upstairs.\n");
		say("The bartender winks at " + QCTNAME(TP) + ", letting " 
			+ HIM_HER(TP) + " know it's OK to go upstairs.\n");
		return 0;
	}
	
	else
	{
		write("You don't feel welcome to go upstairs.\n");
		return 1;
	}
}


//adds a day or night descriptor
string
day_night()
{
	if(CLOCK->query_night())
	{
		return("moon");
	}
	else
	{
		return("sun");
	}
}


 
void
create_shire_room()
{
   configure_shire_inn();
   set_short("The Foaming Mug");
   set_long(
      "This is The Foaming Mug inn, a large and cheerful inn in "
      + "the village of Waymeet. Many of the locals from Waymeet "
	  + "stop here for a cold beer. Occasionally weary travelers "
	  + "from the Great East Road indulge in a pint or seven "
	  + "here as well. A large "
	  + "@@window_open_closed@@" + " window lets in some " 
	  + "@@day_night@@" + "light. And if it's too dark, a chandelier "
      + "hangs from the ceiling to help brighten up the place. "
      + "There is a long bar to lean against "
	  + "as well as "
	  + "some stools to sit on.\n");
	add_item("bar", "This is a long wooden bar, long enough that several "
		+ "people could sit at it. You notice that it's an old bar, and "
		+ "there are scuff marks on the wood where people's boots have "
		+ "knocked into it over the years, but the top is covered with "
		+ "leather. It seems that someone has put some money into "
		+ "refurbishing this establishment lately.\nThere is a menu "
		+ "on top of the bar.\n");
	add_item( ({"leather", "top", "leather top"}), "The leather on top "
		+ "of the bar is soft. It has been stiched into a diamond pattern "
		+ "and covers the entire bar. It looks nice. Someone spent a lot "
		+ "of platinum coins redoing it!\n");
	add_item( ({"scuff marks", "marks"}), "The front of the bar is made "
		+ "of wood. It has been scuffed by people's boots when they "
		+ "bump into the bar getting into or out of their bar stools.\n");
		
	add_item( ({"floor", "ground"}), "The floor is made of river stones. "
		+ "It is slightly bumpy, like a cobble stone road, but also looks "
		+ "as if it will last a long time, rocks being rocks.\n");
	add_item( ({"wall", "walls"}), "The walls are wooden, but the boards "
		+ "are tight enough to keep out the howling wind. There is a "
		+ "painting on the west wall.\n");
	add_item( ({"west wall"}), "The west wall is also made of wooden "
		+ "boards. There is a painting on it.\n");
	add_item( ({"painting", "frame"}), "@@exa_painting@@");
	
	
	add_item( "ceiling", "The ceiling is made of shiplapped wood, not uncommon "
		+ "for a two-storey construction in the shire. You can see some "
		+ "exposed beams holding it all up. " + "@@exa_chandelier@@");
	add_item( ({"chandelier", "candle", "candles"}), "@@chandelier@@");
	add_item( ({"wood", "shiplap", "shiplapped wood"}), "This is basically "
		+ "one board overlapping slightly another and another and another "
		+ "all across the ceiling. It looks like a nice hard wood floor, "
		+ "but over your head.\n");
	add_item( ({"beam", "beams"}), "This thick and heavey timber must have "
		+ "come from an old tree. Don't tell the ents!\n");
	add_item( ({"bolt", "bolts"}), "@@chandelier_bolts@@");
	add_item( ({"cone", "copper cone", "chandelier cone"}), "@@exa_cone@@");
    add_item( ({"chain", "long chain"}), "The chain looks thick enough to "
        + "restrain a mean dog. It holds the chandelier in place from the "
        + "ceiling. Lucky for you, a chain this thick probably won't break.\n");
    add_item( ({"ball", "metal ball"}), "The metal ball is spherical in "
        + "shape. The chain seems to attach to the top of it, but you really "
        + "can't see that from here. Several metal poles extend outward from "
        + "the ball, like spokes on a wheel.\n");
    add_item( ({"pole", "metal pole", "poles", "metal poles"}), 
        "The metal poles extend a couple of "
        + "hands from the ball. Each one has a candle on the end of it, "
        + "lighting the inn.\n");
    add_item( ({"candle", "candles"}), "The candles are attached to the "
        + "metal poles. They light the room nicely.\n");
		
	add_item( ({"beer", "cold beer"}), "Why not order one and see for "
		+ "yourself!\n");
	add_cmd_item( "against bar", "lean", "You lean against the bar, "
		+ "taking a load off your feet. Now it's time for another drink!\n");
	
	add_item( ({"stair", "stairs", "upstairs"}), "A wide sturdy-looking "
		+ "flight of stairs leads to the second storey.\n");
	add_item( ({"storey", "second storey"}), "You can't see much from here. "
		+ "There's an open door, a flickering light, and that's about it. "
		+ "You'd have to go up there to see anything else.\n");

    add_item( ({"window", "windows", "large window", "large windows"}), 
        "@@exa_window@@");
	
	add_item(PRICELIST_ID, "@@pricelist_desc");
   	add_item( ({ "stool", "bar stool", "stools", "bar stools"}), 
		&look_at(SOFA_NAME) );
	add_chair(SOFA_NAME, "[down] [on] / [in] [one] [of] [the] [bar] 'stool' / 'stools' / 'barstool' ", 6);
	
	add_prop(ROOM_I_INSIDE, 1);
	reset_shire_room();
	set_room_tell_time(400);
   
	add_room_tell("@@clean_puke@@");
	add_room_tell("You hear birds chirping outside.\n");
	add_room_tell("The ceiling creaks. Someone must be walking upstairs.");
	add_room_tell("You smell pipe smoke.");
	add_room_tell("Lights flicker upstairs.");
	
	
   add_exit(WAYM_STREET_DIR + "street_9", "out");
   add_exit(WAYM_STREET_DIR + "street_9", "west", 0,0,1);
   add_exit(EAST_R_DIR + "foam_mug_up", "up", block_people);
}

string
clean_puke()
{
	object puke;
	  if(objectp(puke = present("_drunk_person_vomit")))
	  {
		  puke->remove_object();
		  return("The bartender grabs a rag and a bucket from behind the bar. "
			+ "He comes around the bar and bends down, cleaning up the puddle "
			+ "of vomit.\nHe says: "
			+ "So help me this jerk isn't getting another drop to "
			+ "drink tonight!");
	  }
	  else
	  {
		  return("The bartender says: I'm so glad none of you has gotten "
			+ "drunk enough to puke all over my floor.");
	  }
}
//for the bolts add_item
string
chandelier_bolts()
{
	if(is_chandelier == 1)
	{
		return("These bolts look to be about as thick as your small finger. "
			+ "There are three of them, and they simply stick through the chain "
			+ "and the copper cone to keep everything held up. If you wanted "
			+ "to 'borrow' the cone, you could remove or unbolt the bolts.\n");
	}
	else
	{
		return("There are three bolts hung through the chain. Their thick "
			+ "heads keep them from falling to the floor, but otherwise "
			+ "they don't seem to be doing much. They probably used to hold "
			+ "the chandelier's cover in place, back before someone got "
			+ "drunk and stole it.\n");
	}
}

//for the chandelier add_item
string
chandelier()
{
	if(is_chandelier == 1)
	{
		return("A long chain hangs down from the ceiling. It supports a metal "
			+ "ball, out of which come several metal poles. Each pole holds "
			+ "a candle on the end of it. The chandelier is covered with a "
			+ "copper cone. The cone is about the width of a large pipe on "
			+ "top, and as wide as a big pot on the bottom. It has been "
			+ "polished and reflects the candle light down into the "
			+ "inn. The cone seems to be held on by a couple of bolts.\n");
	}
	else
	{
		return("A long chain hangs down from the ceiling. It supports a metal "
			+ "ball, out of which come several metal poles. Each pole holds "
			+ "a candle on the end of it.\n");
	}
}

string
exa_cone()
{
    if(is_chandelier == 1)
    {
        return("The cone on the chandelier is about as wide as a drain pipe "
            + "on top and as wide as a large pot on the bottom. It's curvy "
            + "but still makes a recognizable cone shape. It's being held "
            + "onto the chandelier with some bolts, which could probably "
            + "be removed or unbolted.\n");
    }
    else
    {
        return(chandelier_bolts());
    }
}

//for the ceiling add_item
string
exa_chandelier()
{
	if(is_chandelier == 1)
	{
		return("A large chandelier hangs down from the ceiling. There are "
			+ "several lit candles inside of a metal cone.\n");
	}
	else
	{
		return("A long chain hangs from the ceiling. On the end is a "
			+ "metal ball with several small poles sticking out of it. "
			+ "Each pole holds a candle on the end of it.\n");
	}
}


//Bars should have advertisements on the wall.
string
exa_painting()
{
	int the_painting = (random(3));
	switch(the_painting)
	{
		case 0:
		return("The painting depicts a long-bearded dwarf, muscles rippling, "
			+ "holding aloft a foaming glass of ale. On the picture frame is "
			+ "written: THE FOAMING MUG, WHAT DWARVES CRAVE!\n");
			
		case 1:
		return("The painting depicts a blonde-haired thick-armed "
		+ "male human. He's smiling with a wolfish grin, holding up a "
		+ "tankard of foamy ale. On the frame is written: THE FOAMING "
		+ "MUG!\n");
		
		case 2:
		return("The painting depicts a well-dressed hobbit, sitting at the bar "
			+ "amongst other well-dressed hobbits, all engaged in a lively "
			+ "conversation. On the frame is written: THE FOAMING MUG TOASTS "
			+ "FRIENDSHIP!\n");
	}
}



string
pricelist_desc()
{
return("\n"
   + "+================================================+\n"
   + "|                THE FOAMING MUG                 |\n"
   + "|             Under New Management               |\n"
   + "+------------------------------------------------+\n"
   + "| 1.  Ale                                 25 cc  |\n"
   + "| 2.  House Wine                          55 cc  |\n"
   + "| 3.  Whiskey                            100 cc  |\n"
   + "| 4.  Elven Wine                         150 cc  |\n"
   + "|                                                |\n"
   + "| ** Please don't hesitate to ask our well-      |\n"
   + "|    trained staff about our specials and        |\n"
   + "|    occasional food offerings. **               |\n"
   + "|                                                |\n"
   + "+================================================+\n\n");
}

void
reset_shire_room()
{
   if (!barman)
      barman = clone_object(ER_NPC + "tarlas_test");
   if (!present(barman))
      barman->move(TO);
	window_open = 0;
	is_chandelier = 1;

}

void
init()
{
   ::init();
   add_action("do_read", "read", 0);
   init_shire_inn();
   add_action("open_window", "open");
   add_action("close_window", "close");
   init_room_chairs();
   add_action("remove_bolts", "remove");
   add_action("remove_bolts", "unbolt");
   
   add_action("do_puke", "puke");
   add_action("do_puke", "vomit");
   add_action("do_puke", "throw");
}

//You're drunk. Really Drunk. So drunk you puke.
int
do_puke(string str)
{
	if(TP->query_intoxicated() < ( (TP->intoxicated_max() /2)))
	{
		return 0;
	}
	if(TP->query_prop(NO_SERVE))
	{
		notify_fail("\nNo. You already puked all over the floor once! It's "
			+ "time for you to go!\n");
		say("The bartender grabs " + QCTNAME(TP) + " by " + HIS_HER(TP) 
			+ " ear and drags " + HIM_HER(TP) + " to the door. He says: "
			+ "Don't puke on my floor! And then throws " + QCTNAME(TP)
			+ " out of the inn!\n");
		tell_room(WAYM_STREET_DIR + "street_9", 
			QCTNAME(TP) + " tumbling out of the "
			+ "inn and lands flat on " + HIS_HER(TP) + " rear. You hear "
			+ "the bartender shouting about puking on the floor.\n");
		TP->move_living("M", WAYM_STREET_DIR + "street_9");
		return 0;
	}
	if(!strlen(str) | str == "up")
	{
		write("You're so drunk you puke all over the place! "
			+ "The bartender looks annoyed.\n");
		say(QCTNAME(TP) + " pukes all over the floor! Uh "
			+ "oh, the bartender looks annoyed.\n");
		TP->add_prop(NO_SERVE, 1);
		object puke;
		puke = clone_object("/d/Shire/eastroad/western/supplies/vomit");
		puke->move(environment(TP));
		return 1;
	}
	else
	{
		notify_fail("If you're feeling too drunk, maybe you should "
			+ "just puke already!\n");
		return 0;
	}
}

//removes the bolts so you can have the chandelier cover. Quest related.
int
remove_bolts(string str)
{ 
	if(str == "bolt" | str == "bolts")
	{
		if(is_chandelier == 0)
		{
			write("There's no reason to remove the bolts. They're just "
				+ "hanging from the chain, doing nothing.\n");
			return 1;
		}
		if(TP->query_intoxicated() > (TP->intoxicated_max()/2) || TP->query_skill(SS_AWARENESS) > 75)
		{
			write("You reach up, pull the bolts off, and remove the "
			+ "copper cone. It was a bit tricky getting everything "
			+ "through the hole, but you managed all right.\n");
			say(QCTNAME(TP) + " pulls the bolts off and removes the "
				+ "copper cone. It was tricky, but " + HE_SHE(TP)
				+ " managed to remove it somehow.\n");
			object cone;
			cone = clone_object(WAYM_OBJ_DIR + "chandelier_cone");
			cone->move(TP);
			is_chandelier = 0;
			return 1;
		}
        else
        {
            
			notify_fail("You're either way too sober to do something this "
				+ "dumb, or way too unobservant of your surroundings to do "
                + "it without getting caught!\n");
			return 0;
		}
		
	}
	else
	{
		notify_fail("Remove what? The bolts?\n");
		return 0;
	}
}
public string
look_at(string arg)
{
    /* ok, the descs are a little lame, but you get the idea ... */
    switch ( arg )
    {
    case SOFA_NAME:
	return "The barstools are high enough that when hobbits sit on the "
		+ "stools, they can comfortably rest their elbows on the bar. They "
		+ "are, perhaps, a little short for big people, but still, they "
		+ "look comfortable enough.\n"+
	    sitting_on_chair(SOFA_NAME, this_player(), 0);
    }
}

/* This returns who is in the chair to the long or short description.
 * IF you add + "@@is_in_chair@@" somewhere in your long description.
 */
 
string
is_in_chair()
{
	return("\n" + sitting_on_chair(SOFA_NAME, this_player(), 0));
}
int
do_read(string str)
{
   if (!str)
      return 0;
   if (member_array(str, PRICELIST_ID) == -1)
      return 0;
   write(pricelist_desc());
   return 1;
}

int
do_order(string str)
{
	if(TP->query_prop(NO_SERVE))
	{
		notify_fail("After you got drunk and threw up on the floor, "
			+ "you want MORE to drink! No. The bartender is not "
			+ "cleaning up your mess again!\n");
		return 0;
	}
   if (!barman || !present(barman))
      {
      NF("There is no-one here to sell you anything.\n"+
         "The innkeeper must be out.\n");
      return 0;
   }
   return ::do_order(str);
}


mixed *
get_order(string str)
{
   object order;
   int    price;

   switch(str)
   {
      case "ale":
      case "some ale":
      case "pint of ale":
      case "1":
      order = clone_object(SUPL_DIR + "ale");
      price = 25;
      break;
      
      case "wine":
      case "house wine":
      case "glass of wine":
      case "glass of house wine":
      case "2":
      order = clone_object(SUPL_DIR + "wine");
      price = 55;
      break;
      
      case "whiskey":
      case "whisky":
      case "3":
      order = clone_object(SUPL_DIR + "whiskey");
      price = 100;
      break;
      
      case "elven wine":
      case "glass of elven wine":
      case "4":
      order = clone_object(SUPL_DIR + "ewine");
      price = 150;
      break;
      
      case "house special":
	  case "special":
	  
      case "5":
      order = clone_object(SUPL_DIR + "special");
      price = 180;
      break;
      
   }
   return (({order}) + ({price}));
}

//Allows you to open the window
int
open_window(string str)
{
	if(str == "window")
	{
		if(window_open == 0)
		{
			write("You open the window, letting in more "
				+ "light.\n");
			say(QCTNAME(TP) + " opens the window, letting in more "
				+ "light.\n");
			window_open = 1;
			return 1;
		}
		else
		{
			write("The window is already open!\n");
			say(QCTNAME(TP) + " tries to open the already open window. "
				+ "How silly!\n");
			return 1;
		}
	}
	else
	{
		notify_fail("Open what? The window?\n");
		return 0;
	}
}

// Closes the window.
int
close_window(string str)
{
	if(str == "window")
	{
		if(window_open == 1)
		{
			write("You close the window.\n");
			say(QCTNAME(TP) + " closes the window.\n");
			window_open = 0;
			return 1;
		}
		else
		{
			write("The window is already closed!\n");
			say(QCTNAME(TP) + " triest to close the window, but it's "
				+ "already closed!\n");
			return 1;
		}
	}
	else
	{
		notify_fail("Close what? The window?\n");
		return 0;
	}
}
// For the add_items and long description, etc.
string
window_open_closed()
{
	if(window_open == 0)
		return("closed");
	else
		return("open");
}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} 

//Add_item for windows.
string
exa_window()
{
    string desc = "The window is a nice size, big enough to see through but "
            + "not so big as to let people climb through it. ";
    if(window_open == 1)
    {
        return(desc + "It's open now, letting in a cool breeze.\n");
    }
    return(desc + "The window is closed currently, but it could be opened.\n");
}
           
	