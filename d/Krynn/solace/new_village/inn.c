/* Inn in solace, coded by Nick */

/*
* Last Updated By:
* Leia
* June 05, 2005
*
* Navarre Updated June 11th 2006
* Added linebreak to long description.
*
* Navarre August 19th 2007
* Fixed so when leaving the room you standup before you actually get to leave.
* Before it told people outside the bar that you were getting up.
*/

#include "/d/Ansalon/common/brewcraft/brewcraft.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/local.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"
#include "/d/Krynn/gnome/schorsch/schorsch.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit  SOLINROOM;
inherit "/lib/trade";

#define NUM          sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define MINSTREL     "/d/Terel/guilds/minstrels/living/travelling_repairer2"
#define START_ROOM   "/d/Krynn/solace/new_village/inn_room"
#define IS_OOTS(x)   ((x)->query_guild_name_lay() == "Holy Order of the Stars")
#define BREWSEEKER   "/d/Ansalon/estwilde/living/dwarf_brewseeker.c"

object minstrel;
object brewseeker;
int test;          /* to indicate that a test is going on, no money given. */
object tika ;      /* Tika, the girl that serves in the inn. */
object schorsch;   /* Gives out a tour quest. */
object jakey;     

/*
 * Prototypes
 */
int move_item(mixed arg);
int check_stand_up();
int schorsch_alarm = 0;

/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_solace_room()
{
  if (!tika)
  {
      tika = clone_object(NPC + "tika");
      tika->move_living("xxx", TO);
  }

  if(!schorsch)
  {
      schorsch_alarm = set_alarm(30.0, -1.0, "schorsch_comes");
  }
  
  if ( !jakey )
  {
     jakey = clone_object("/d/Krynn/qualinesti/npc/hunter");
     jakey->move(TO, 1);
     jakey->command("sit at bar");
  }

    if(!objectp(minstrel))
    {
        minstrel = clone_object(MINSTREL);
        minstrel->move(TO, 1);
    }
  
    if(!objectp(brewseeker))
    {
        brewseeker = clone_object(BREWSEEKER);
        brewseeker->move(TO, 1);
    }
  
}

void
schorsch_comes()
{
  if (!objectp(schorsch))
  {
      schorsch = clone_object("/d/Krynn/gnome/schorsch/schorsch");
  }

  if (!present(schorsch, this_object()))
  {
      schorsch->move_living("comes in with slowly", TO);
      schorsch->command("sit at bar");
  }
  schorsch_alarm = 0;
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */    
void 
init()
{    
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
    add_action("rent", "rent");
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting by a table! How do you expect to sit in two places at once?\n");
                return 1;
        }
           
        if(TP->query_prop(FSIT))
        {
                write("But you are already sitting by the fire! How do you expect to sit in two places at once?\n");
                return 1;
        }
           
        if(TP->query_prop(BSIT))
        {
                write("But you are already sitting by the bar! How do you expect to sit in two places at once?");
                return 1;
        }
           
        if(str == "around table" | str == "around a table" | str == "at table" | str == "at a table" | str == "by table" | str == "by a table" | str == "table" | str == "chair around table" | str == "in chair around table" | str == "in a chair around a table" | str == "chair at table" | str == "in chair at table" | str == "in a chair at a table" | str == "chair by table" | str == "in chair by table" | str == "in a chair by a table") 
        {
                TP->catch_msg("You sit down in one of the comfortable chairs near a table.\n");
                say(QCTNAME(TP) + " sits down in one of the comfortable looking chairs near a table.\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near a table");
                return 1;
        }
        
        if(str == "around fireplace" | str == "around the fireplace" | str == "by fireplace" | str == "by the fireplace" | str == "fireplace" | str == "chair around fireplace" | str == "in chair around fireplace" | str == "in a chair around the fireplace" | str == "chair by fireplace" | str == "in chair by fireplace" | str == "in a chair by the fireplace") 
        {
                TP->catch_msg("You sit down in one of the comfortable chairs near the fireplace.\n");
                say(QCTNAME(TP) + " sits down in one of the comfortable looking chairs near the fireplace.\n");
                TP->add_prop(FSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near the fireplace");
                return 1;
        }
	
	        if(str == "at bar" | str == "at the bar" | str == "by bar" | str == "by the bar" | str == "bar" | str == "chair at bar" | str == "in chair at bar" | str == "in a chair at the bar" | str == "chair by bar" | str == "in chair by bar" | str == "in a chair by the bar")
        {
                TP->catch_msg("You sit down in one of the comfortable chairs near the bar.\n");
                say(QCTNAME(TP) + " sits down in a comfortable looking chair near the bar.\n");
                TP->add_prop(BSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near the bar");
                return 1;
        }
	
        else
        {
                TP->catch_msg("Where would you like to sit? By the fireplace, the bar, or around a table?\n");
                return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up")
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up and leave the table.\n");
                        say(QCTNAME(TP)+" stands up from the table.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
                
                if(TP->query_prop(FSIT))
                {
                        TP->catch_msg("You stand up and move away from the fireplace.\n");
                        say(QCTNAME(TP)+" stands up and moves away from the fireplace.\n");
                        TP->remove_prop(FSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
                
                if(TP->query_prop(BSIT))
                {
                        TP->catch_msg("You stand up and leave the bar.\n");
                        say(QCTNAME(TP)+" stands up from the bar.\n");
                        TP->remove_prop(BSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
        }
        
        else
        {
                TP->catch_msg("Stand? Stand up?\n");
                return 1;
        }
        
        return 1;
}

int 
check_stand_up()
{
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the table before leaving.\n");
                say(QCTNAME(TP) + " stands up from the table as "+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }
          
        if(TP->query_prop(FSIT))
        {
                TP->catch_msg("You stand up from your spot near the fireplace before leaving..\n");
                say(QCTNAME(TP) + " stands up from " + HIS(TP) + "spot at the fireplace as " + HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);            
                TP->remove_prop(FSIT);
        }
        
        if(TP->query_prop(BSIT))
        {
                TP->catch_msg("You stand up from the bar before leaving.\n");        
                say(QCTNAME(TP) + " stands up from the bar as " + HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(BSIT);
        }
	return 0; // always allow him to go out.
}

// Checks if they can enter the upstairs temporary start location.

int 
check_can_enter()
{
        if(TP->query_temp_start_location() != START_ROOM &&
           TP->query_default_start_location() != START_ROOM)
        {
            TP->catch_msg("You have not rented a room, so cannot enter the " +
                "sleeping area of the Inn.\n");
            return 1;
        }

        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the table before climbing the stairs " +
                    "to the sleeping rooms.\n");
                say(QCTNAME(TP) + " stands up from the table as "+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }
          
        if(TP->query_prop(FSIT))
        {
                TP->catch_msg("You stand up from your spot near the fireplace before " +
                    "climbing the stairs to the sleeping rooms.\n");
                say(QCTNAME(TP) + " stands up from " + HIS(TP) + "spot at the fireplace as " + HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);            
                TP->remove_prop(FSIT);
        }
        
        if(TP->query_prop(BSIT))
        {
                TP->catch_msg("You stand up from the bar before climbing " +
                    "the stairs to the sleeping rooms.\n");        
                say(QCTNAME(TP) + " stands up from the bar as " + HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(BSIT);
        }

	return 0; // allow him to go up.
}

void enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        if(!(TP->test_bit("Krynn", SCHORSCH_GROUP, SCHORSCH_BIT)))
        {
	    if (!schorsch_alarm && !present(schorsch, this_object()))
            {
                schorsch_alarm = set_alarm(30.0, 0.0, "schorsch_comes");
            }
        }
    }
}


void leave_inv(object ob, object to)
{
        
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
                return;
                
    check_stand_up();
}

void
create_solace_room()
{
    config_default_trade();
    set_short("The Inn of The Last Home");
    set_long("You are in the Inn of The Last Home. There is a menu on the bar. "+
             "You find this place rather cozy, with a lot of tables and chairs "+
             "and a warm fireplace. The living tree in which the inn is built "+
             "wraps its ancient branches around it lovingly. The walls and the "+
             "fixtures are crafted around the boughs of the tree with such care "+
             "as to make it impossible to tell where nature's work leaves off and "+
             "man's begins. The bar seems to ebb and flow like a polished wave "+
             "around the living wood that supports it.\n");

    add_item("bar", "A nice looking wooden bar with a menu on it.\n");
    add_item("menu", "It's a menu. Perhaps you should try reading it?\n");
    add_item(({"walls", "wall", "fixture", "fixtures"}), 
        "They are made out of oak wood, as is the rest of the place.\n"); 
    add_item(({"chairs", "chair"}), 
        "They are comfortable looking wooden chairs. Each chair has been " +
        "finely crafted from a single piece of wood.\n");
    add_item("tables", "They are made of oak wood, and their surfaces are " +
        "darkened by spilled beer. One of them has been pushed back against " +
        "the trunk of the tree and is surrounded by chairs.\n");
    add_item(({"stairs", "staircase"}), "A small staircase is almost invisible " +
        "in one of the shadowy corners of the Inn. They lead up to sleeping " +
        "rooms. If you have rented a room you can go up them.\n");
    add_item(({"sleeping rooms" }), "A small staircase leads up to the sleeping " +
        "rooms of the Inn.\n");

    add_cmd_item("menu", "read", "@@read");

    add_item(({"branches", "branch"}), "The branches are huge, thick as many " +
        "tree-trunks, and part of the single, ancient vallenwood tree which " +
        "support the floor and ceiling of this structure.\n");
    add_item(({"window", "stained glass", "panes"}), "Vibrant in colour, " +
        "the window allows sunlight to penetrate and illuminate, but it is " +
        "too opaque to see through.\n");
    add_item(({"tree", "vallenwood"}), "This tree seems particularly fond " +
        "of this inn, as it seems to hold the structure in loving arms. " +
        "It is huge, and quite old. Perhaps it pre-dates the Cataclysm.\n");
    add_item(({"kegs", "keg"}), "Otik brews the beer himself, since trade " +
        "has been disrupted by so much war. He would not be pleased if you " +
        "tried to abscond with any of his kegs, but would be happy to sell " +
        "you some, instead.\n");
    add_item(({"warm fireplace", "fireplace"}), "The fireplace is set " +
        "three-quarters of the way back in the room to prevent fire from " +
        "spreading to the room and the tree itself. It is the only stonework " +
        "in the entire Inn and is obviously of dwarven make. It has been crafted " +
        "to look as though it were a part of the tree itself. Next to the fireplace " +
        "is a bin of cordwood.\n");
    add_item(({"wood", "cordwood", "bin"}), "This cordwood is oak, not " +
        "vallenwood. The citizens think too highly of their vallenwood trees " +
        "to ever use them for firewood.\n");

    set_tell_time(120+random(15));
    add_tell("All of a sudden there is a loud crash in the kitchen, " +
        "followed by a louder splashing noise.\n");
    add_tell("Suddenly you hear someone in the kitchen yell: \"Oh for " +
        "Paladin's sakes! Not again!\"\n");
    add_tell("Lovely aromas come to you from inside the kitchen. " +
        "Unfortunately - or fortunately for some - they all smell like potatoes.\n");

    add_tell("The chef yells from inside the kitchen: \"Order up!\"\n");
    add_exit(TDIR + "platform2", "out", check_stand_up, 0);
    add_exit(TDIR + "inn_room", "up", check_can_enter, 0, 1);
    add_exit(KITCHEN, "south", 0);
    reset_solace_room();
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
int
read(string str)
{
    write("" +
	  "   Spring Water              10 cc\n" +
	  "   Small Beer                 12 cc\n" +
          "   Iron Delving Export Brew   24 cc\n"+
          "      (" + BREWCRAFT_MENU +") \n"+
	  "   Some Really Sweet Wine     72 cc\n" +
	  "   An Apple                   25 cc\n" +
	  "   Potato Soup                80 cc\n" +
	  "   Plate of Spiced Potatoes  210 cc\n\n" +
          "   Rent a room for the night   1 gc\n\n" +
	  "Try 'buy beer with gold' if you wanna specify what to\n" +
	  "pay with, or 'test buy beer' to see what would happen\n" +
	  "if you typed 'buy beer'. 'buy 10 beer' would get you\n" +
	  "ten beers from the bar, but it takes a little while to\n" +
	  "give them all to you. You can only order a maximum\n" + 
	  "of 10 items at a time since Tika isn't strong enough \n" +
	  "to carry more.\n");
    return 1;
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink and possibly description on how to pay and
 *                      get the change
 */
int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;
    
    NF("Tika isn't here to answer your call.\n");
    if (!tika || !P(tika, TO))
      return 0;
    
    NF("buy what?\n");
    if (!str)
      return 0;
    
    /* Has the player defined how payment will be done and what change to get back? */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
      {
	  /* Well, maybe player has defined how payment will be done atleast? */
	  str3 = "";
	  if (sscanf(str, "%s with %s", str1, str2) != 2)
	    {
		str2 = "";
		str1 = str;
	    }
      }
    
    if (sscanf(str1, "%d %s", num, str1) != 2)
      num = 1;

    if (num == 0)
      num = 1;
    
    switch(lower_case(str1))
      {
	case "water":
	case "waters":
	case "spring":
	case "spring water":
	case "spring waters":
	  name = "spring_water";
	  price = num * 10;
	  break;
	case "beer":
	case "beers":
	case "small":
	case "small beer":
	  name = "beer";
	  price = num * 12;
	  break;
	case "brew":
	case "brews":
	case "export brew":
	case "export brews":
	case "iron delving export brew":
	case "iron delving export brews":
	  name = "brewcraft_beermug";
	  price = num * 24;
	  break;
	case "wine":
	case "wines":
	case "sweet":
	case "sweet wine":
	  name = "wine";
	  price = num * 72;
	  break;
	case "apple":
	case "apples":
	  name = "iapple";
	  price = num * 25;
	  break;
	case "potato":
	case "potato soup":
	case "soup":
	case "soups":
	  name = "isoup";
	  price = num * 80;
	  break;
	case "potatoes":
	case "spiced":
	case "plate of spiced potatoes":
	case "plate":
	case "plates":
	  name = "potatoes";
	  price = num * 210;	
	  break;
	default:
	  NF("I don't understand what you want to buy.\n");
	  return 0;
      }
    if (num > 10)
      {
	  NF("Tika can only carry a maximum of 10 items at a time!\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("Tika gets to work.\n");
    
    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;
    
    name = arg[0];
    num = arg[1];
    ob = arg[2];
    
    for (i = 0; i < 10; i++)
      {
	  num--;

	  if ( name != "brewcraft_beermug")
   	      file = OBJ + name;
          else
   	      file = "/d/Ansalon/estwilde/obj/" + name;

	  drink = clone_object(file);
	  
	  if (!test && (drink->move(ob)))
	    {
		ob->catch_msg("You drop the " + drink->short() +
			      " on the floor.\n");
		say(QCTNAME(ob) + " drops a " + drink->short() +
		    " on the floor.\n", ob);
		drink->move(TO);
	    } 
	  else if (!test) 
	    {
		if (num == 0)
		  {
		      if (arg[1] > 1)
			{
			    ob->catch_msg("You get some " + drink->plural_short() +
					  ".\n");
			    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
				".\n", ob);
			}
		      else 
			{
			    ob->catch_msg("You get " + drink->short() + ".\n");
			    say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
				ob);
			}
		  }
	    }
	  else 
	    {
		say(QCTNAME(ob) + " seems to be estimating something.\n",
		    ob);
		return 1;
	    }
	  if (num < 1)
	    break;
      }
    
    if (num > 0)
      set_alarm(1.0, 0.0, &move_item(({name, num, ob})));
    return 1;
}

/*
 * Function name: test
 * Description:   To allow the buyer to see what would happen with change and
 *                payment depending on how the buyer chooses to pay.
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
test(string str)
{
    int i;
    string str1;
    
    NF("Test what?\n");
    if (!str || !stringp(str))
      return 0;
    
    if (sscanf(str, "buy %s", str1)) 
      {
	  test = 1;
	  write("This would be the result of a buy:\n");
	  i = order(str1);
	  test = 0;
	  return i;
      }
}

int
rent(string str)
{
    NF("Rent what?\n");


    NF("Rent what? A room?\n");
    if (str != "room")
        return 0;    

    NF("Tika isn't here to answer your call.\n");
    if (!tika || !P(tika, TO))
        return 0;

    if (str == "room")
    {
        if (IS_OOTS(TP))
        {
            write("Tika notices your medallion of faith and " +
                "whispers to you 'You can board here as long as " +
                "you like! Just don't let the High Theocrat see you!'\n\n" +
                "You will now start in the Inn's sleeping rooms as " +
                "a permanent boarder!\n");
            this_player()->set_default_start_location(START_ROOM);
            return 1;
        }

        if (!present("gold coin",TP))
        {
            write("Tika says: I only take gold for my rooms.\n");
            return 1;
        }

        if (!MONEY_MOVE(1,"gold",TP,0))
        {
            write("You pay 1 gold coin for a sleeping room. When you " +
                "next enter the realms you will do so from the rooms " +
                "above the Inn.\n");
            this_player()->set_temp_start_location(START_ROOM);
            return 1;
        }
        return 0;
    } 
    return 0;
}

