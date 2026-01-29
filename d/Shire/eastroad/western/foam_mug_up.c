/*
 * The code for the forsaken inn is basically the same as for the prancing 
 * pony in Bree, /d/Shire/common/bree/inn.c
 * The code for The Foaming Mug inn is taken from both of the above.
 *
 * This is the upstairs bar in the Foaming Mug. Here you can get
 * stronger and fancier drinks.
 *
 * Raymundo, Jan 2020
 */

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

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
#define QBIT	"_i_have_test_qbit"

static object barman;

void
create_shire_room()
{
   configure_shire_inn();
   set_short("Upstairs at The Foaming Mug");
   set_long(
      "You are standing in quite a posh looking establishment. There is a "
		+ "long, redwood bar that looks as if it were made from a single "
		+ "giant tree, noticably free of scuff marks compared to the bar "
		+ "downstairs. The walls have been stained to a dark brown and, "
		+ "instead of hard wood, the floor is carpeted in a lush red. "
		+ "Lamplight flickers, but you see no lamps. They must be cleverly "
		+ "hidden about the room. You also cannot find a menu anywhere. "
		+ "The only thing that looks out of place is the (admittedly well-"
		+ "polished) pot still behind the bar.\n");
   
   add_item( ({"still", "pot still"}), "@@exa_pot_still@@");
   add_item( "stove", "The stove is just large enough to heat the pot still "
	+ "to a rolling boil.\n");
	add_item( ({"bar", "redwood", "red wood", "redwood bar"}), "This bar "
		+ "was made from a single tree trunk, and it must have been "
		+ "enormous. No redwoods grow in the Shire, so this must have been "
		+ "hauled at great expense from high up the in mountains.\n");
	add_cmd_item( ({"bar", "against bar", "up to the bar"}), 
		({"lean", "belly"}), "You lean against the bar. It's time for a "
		+ "drink!\n");
	add_item( ({"marks", "scuff marks"}), "Unlike the bar downstairs, this "
		+ "bar has no scuff marks on it. They must serve a gentler class of "
		+ "customer here.\n");
	add_item( ({"lamp", "lamps"}), "You see no lamps anywhere! They must "
		+ "be hidden!\n");
	add_item( ({"carpet", "carpeting", "floor"}), "The carpet is red and plush. "
		+ "It's about as deep as a human's index finger is long!\n");
   add_item( ({"wall", "walls"}), "The walls are covered in wood pannels, as "
		+ "is normal in the Shire. These, however, have been stained to a deep"
		+ "dark brown. They look very classy.\n");
	add_item( "ceiling", "Instead of the normal shiplapped wood, the inkeeper "
		+ "decided to do this ceiling in copper tiles. It looks quite nice!\n");
	add_item( ({"tile", "tiles", "copper tile", "copper tiles"}),
		"Each tile is about the size of an ogre's hand, except square. They "
		+ "depict scenes of daily life in the Shire, such as smoking a pipe, or "
		+ "eating. Or more eating. Or still more eating! Also, some of the tiles "
		+ "depict drinking ale.\n");
   //This is a posh establishment. No menu on the wall! The bartender will give you 
   // a paper menu (or vellum) instead.
   add_item(PRICELIST_ID, "Strange. You don't see a menu anywhere. Maybe "
		+ "you should ask the bartender about it.\n");
	remove_item("spittoon");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_M_NO_SCRY, "The face of a bartender appears before you, "
		+ "taking up your whole field of vision. He says: We're sorry, but "
		+ "our clients' privacy is of the utmost importance to us. Thank you "
		+ "for understanding.\n");
	add_prop(ROOM_M_NO_STEAL, 1);
	add_prop(ROOM_M_NO_ATTACK, 1);
	add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
	add_prop(OBJ_S_SEARCH_FUN, "search_here");
   reset_shire_room();
   
   add_exit(EAST_R_DIR + "foam_mug_2020", "down");
}


void
reset_shire_room()
{
   if (!barman)
      barman = clone_object(ER_NPC + "imbert");
   if (!present(barman))
      barman->move(TO);

}

void
init()
{
   ::init();
   init_shire_inn();
   add_action("add_qbit", "add"); //REMOVE BEFORE OPENING
}

//FOR TESTING PURPOSES. TO BE REMOVED.
int
add_qbit(string str)
{
	if(str == "qbit")
	{
		TP->add_prop(QBIT, 1);
		write("ADDED");
		return 1;
	}
	else
		return 0;
}

int
do_order(string str)
{
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
      case "martini":
      case "a martini":
      order = clone_object(SUPL_DIR + "martini");
      price = 1728;
      break;
      
	  //For everything but the martini, include a qbit check.
	  //You can only order the drinks if you've done the quest.
      case "a brandy":
      case "brandy":
      case "glass of brandy":
     
		if(CHECK_QUEST(TP, "fix_still") | TP->query_wiz_level())
		{
      order = clone_object(SUPL_DIR + "p_brandy");
      price = 1728;
		}
		else
		{
			write("The bartender looks at you with feigned ignorance. Hmm...\n");
		}
      break;
            case "a whiskey":
      case "whiskey":
      case "glass of whiskey":
	  case "whisky":
	  case "a whisky":
	  case "glass of whisky":
     
		if(CHECK_QUEST(TP, "fix_still") | TP->query_wiz_level())
		{
      order = clone_object(SUPL_DIR + "p_whisky");
      price = 1728;
		}
		else
		{
			write("The bartender looks at you with feigned ignorance. Hmm...\n");
		}
      break;
	        case "a gin":
      case "gin":
      case "glass of gin":
     
		if(CHECK_QUEST(TP, "fix_still") | TP->query_wiz_level())
		{
      order = clone_object(SUPL_DIR + "p_gin");
      price = 1728;
		}
		else
		{
			write("The bartender looks at you with feigned ignorance. Hmm...\n");
		}
      break;
		case "a lightning":
      case "lightning":
      case "glass of lightning":
	  case "a white lightning":
	  case "white lightning":
	  case "a glass of white lightning":
     
		if(CHECK_QUEST(TP, "fix_still") | TP->query_wiz_level())
		{
      order = clone_object(SUPL_DIR + "p_lightning");
      price = 1728;
		}
		else
		{
			write("The bartender looks at you with feigned ignorance. Hmm...\n");
		}
      break;
		case "a schnapps":
      case "schnapps":
      case "glass of schnapps":
     
		if(CHECK_QUEST(TP, "fix_still") | TP->query_wiz_level())
		{
      order = clone_object(SUPL_DIR + "p_schnapps");
      price = 1728;
		}
		else
		{
			write("The bartender looks at you with feigned ignorance. Hmm...\n");
		}
      break;
	        case "a vodka":
      case "vodka":
      case "glass of vodka":
     
		if(CHECK_QUEST(TP, "fix_still") | TP->query_wiz_level())
		{
      order = clone_object(SUPL_DIR + "p_vodka");
      price = 1728;
		}
		else
		{
			write("The bartender looks at you with feigned ignorance. Hmm...\n");
		}
      break;
    
      
   }
   return (({order}) + ({price}));
}

//why not search for the lamps
string
search_here(object me, string arg)
{
	if(arg == "lamp" | arg == "lamps" | arg == "here for lamp" | arg == "here for lamps")
	{

		say(QCTNAME(TP) + " finds the hidden lamps!\n");
		return("Ahhh, so that's how they did it! You see lamps hidden "
			+ "behind colored glass pannels. They look like the wall, "
			+ "but they give off light. Clever!\n");
		
	}
	else
	{
		return("");
	}
}
	

//Returns the add_item for the still based on whether or not 
//You have done the quest.
string
exa_pot_still()
{

	if(TP->query_prop(QBIT))
	{
		return("There is a pot still behind the bar. It has a round "
			+ "bottom that sits directly over a small wood stove. "
			+ "The bottom, or pot, is covered with a metal cone which "
			+ "leads to a series of pipes. The pipes eventually empty "
			+ "into a large glass jar. The innkeeper uses this still "
			+ "to make liquor like gin!\n");
	}
	else 
		return("There is a pot still behind the bar, or at least "
		+ "part of one. You see a large round-bottomed pot that "
		+ "narrows slightly to an opening on the top. If this were "
		+ "a working still, the hole would be covered with a metal "
		+ "cone and some pipes and whatnot. All of that would lead "
		+ "to the glass jar, which would collect the distilled "
		+ "liquor. Unfortunately, only the bottom of the still and "
		+ "the jar are here. Everything else seems to have gone "
		+ "missing! Oh no!\n");
}