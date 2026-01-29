/*
 * Anyone sneaking in window can start here, but with dire potential
 * outcomes.
 */


#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <money.h>

inherit NOBLE_ROOMBASE;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int move_item(mixed arg);
string hearth_state();
string hearth_exa();
string wood_state();
string stock_stand();
string stack_hearth();
string set_fire();

string
query_to_jail()
{
  return "out";
}

int hearth = 2;
int wood = 1;
int test;        /* Test has been removed. */
object innkeep;  /* The innkeeper Havecius who serves customers. */
object inndoor;

void
reset_palan_room()
{
  if (!objectp(innkeep))
    {
      innkeep = clone_object(NOBLE + "living/havecius");
	  innkeep->arm_me();
      innkeep->move(TO);
    }
}

void 
init()
{    
    ::init();
    add_action("action_sit", "sit");
	add_action("action_stand", "stand");
    add_action("order", "buy");
    add_action("order", "order");
}

int 
action_sit(string str)
{
	if (strlen(str) == 0)
	{
		
	if(TP->query_prop(TSIT))
    {
		write("But you are already sitting at a table! How do you expect "
		+ "to sit in two places at once?\n");
		return 1;
	}
           
	if(TP->query_prop(FSIT))
    {
        write("But you are already sitting by the window! How do you expect "
		+ "to sit in two places at once?\n");
        return 1;
	}
           
	if(TP->query_prop(BSIT))
	{
		write("But you are already sitting at the counter! How do you expect "
		+ "to sit in two places at once?");
        return 1;
	}

	TP->catch_msg("Where would you like to sit?  In a high-backed chair "
		+ "at a roundtable?  A plush leather seat by the hearth?  Or at the "
		+ "counter?\n");
		return 1;
	}
           
	if (parse_command(str, ({}),
		"[in] [at] [on] [around] [by] [a] [the] [high] [backed] [high-backed] [leather] 'chair' / 'table' / 'roundtable' [at] [by] [around] [a] [the] [table] [roundtable]"))
		{
		TP->catch_msg("You sit down in one of the high-backed leather chairs "
		+ "at a roundtable.\n");
		say(QCTNAME(TP) + " sits down in one of the high-backed leather "
		+ "chairs at a roundtable.\n");
		TP->add_prop(TSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a high-backed "
		+ "chair at a roundtable");
		return 1;
	}
        
	if (parse_command(str, ({}),
		"[in] [at] [on] [around] [by] [a] [the] [plush] [leather] 'seat' / 'hearth' / 'fire' / 'fireplace' [at] [by] [around] [a] [the] [hearth] [fire] [fireplace]"))
	{
		TP->catch_msg("You sit down in one of the plush leather seats "
		+ "by the hearth and prop your feet up upon one of the leather "
		+ "footrests.\n");
		say(QCTNAME(TP) + " sits down in one of the plush leather "
		+ "seats by the hearth and props " + HIS(TP) + " feet up upon "
		+ "one of the leather footrests.\n");
		TP->add_prop(FSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a plush leather "
		+ "seat by the hearth with " + HIS(TP) + " feet propped up on a "
		+ "leather footrest");
		return 1;
	}
	
	if (parse_command(str, ({}),
		"[in] [at] [on] [around] [by] [a] [the] [wood] [wooden] 'stool' / 'counter' [at] [by] [around] [a] [the] [counter]"))
	{
		TP->catch_msg("You sit down on one of the stools at the counter.\n");
		say(QCTNAME(TP) + " sits down on a stool at the counter.\n");
		TP->add_prop(BSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting atop a stool at the "
		+ "counter");
		return 1;
	}
	
	else
	{
		TP->catch_msg("Where would you like to sit?  In a high-backed chair "
		+ "at a roundtable?  A plush leather seat by the hearth?  Or at the "
		+ "counter?\n");
		return 1;
	}
}

int 
action_stand(string str)
{
	if(str == "up" || str != "up")
	{
		if(TP->query_prop(TSIT))
		{                        
		TP->catch_msg("You stand up from your high-backed leather chair and "
		+ "leave the roundtable.\n");
		say(QCTNAME(TP) + " stands up from " + HIS(TP) + " high-backed "
		+ "leather chair and leaves the roundtable.\n");
		TP->remove_prop(TSIT);
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		return 1;
		}
                
		if(TP->query_prop(FSIT))
		{
		TP->catch_msg("You lift your feet off the leather footrest and "
		+ "stand up from your plush leather seat by the hearth.\n");
		say(QCTNAME(TP) + " lifts " + HIS(TP) + " feet off " + HIS(TP)
		+ " leather footrest and stands up from " + HIS(TP) + " plush "
		+ "leather seat by the hearth.\n");
		TP->remove_prop(FSIT);
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		return 1;
		}

		if(TP->query_prop(BSIT))
		{
		TP->catch_msg("You stand up from your stool at the counter.\n");
		say(QCTNAME(TP)+" stands up from a stool at the counter.\n");
		TP->remove_prop(BSIT);
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		return 1;
		}
	}
        
	else
	{
		TP->catch_msg("Stand?  Stand up?\n");
		return 1;
	}
        
	return 1;
}

void
leave_inv(object ob, object to)
{
	::leave_inv(ob, to);

	if(!objectp(to) || !objectp(ob))
	return;
                
	if(TP->query_prop(TSIT))
	{
		TP->catch_msg("You stand up from your high-backed leather "
		+ "chair at the roundtable before leaving.\n");
		say(QCTNAME(TP) + " stands up from " + HIS(TP) + " high-backed "
		+ "leather chair at the roundtable before leaving.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(TSIT);
	}

	if(TP->query_prop(FSIT))
	{
		TP->catch_msg("You lift your feet off the leather footrest and "
		+ "stand up from your plush leather seat by the hearth before "
		+ "leaving.\n");
		say(QCTNAME(TP) + " lifts " + HIS(TP) + " feet off " + HIS(TP)
		+ " leather footrest and stands up from " + HIS(TP) + " plush "
		+ "leather seat by the hearth before leaving.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);            
		TP->remove_prop(FSIT);
	}

	if(TP->query_prop(BSIT))
	{
		TP->catch_msg("You stand up from your stool at the counter "
		+ "before leaving.\n");        
		say(QCTNAME(TP) + " stands up from " + HIS(TP) + " stool at the "
		+ "counter before leaving.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(BSIT);
	}
}

nomask public void
create_palan_room()
{
    config_default_trade();

    SHORT("A warm, well-furnished inn");
    LONG("In the hall of the Greystone Inn " + "@@hearth_state@@" + "  The hall "
	+ "is filled with several roundtables, high-backed leather chairs, and "
	+ "plush leather seats with footrests by the hearth.  The innkeep's "
	+ "counter is by the entrance, and beside it a staircase rises to the "
	+ "upper levels and rooms.  A small pair of swinging double doors in the "
	+ "southwest leads to the kitchen.  The walls are adorned with oil "
	+ "paintings, arms and shields, and mounted heads.  Small, iron oil "
	+ "lamps hang low in the corners and rest in the center of the "
	+ "roundtables.\n");

	ITEM("ceiling", "The ceiling is not directly lit.  Flickering shadows "
	+ "from the hall's lights cast shadow on its dark wood.\n");
	ITEM("floor", "The floor is completely done with strips of dark stained "
	+ "mahogany.  Though old, the wood adds a rich tone to the hall keeping "
	+ "it from appearing bright.\n");
	ITEM(({"wall", "walls"}), "The granite walls are covered with old oil "
	+ "paintings, armaments, shields, and the stuffed heads of animals.  "
	+ "Small silver flecks reflect muted sparkles as light from the flames "
	+ "of the hall dances across the grey, stone blocks.\n");
	ITEM(({"granite", "blocks", "granite walls", "stone blocks",
		"grey blocks", "grey stone blocks", "flecks", "silver flecks"}),
	  "Grey blocks of granite imported from the south have been used to "
	+ "build the walls of the Greystone.  The early builders spared no "
	+ "expense in its construction.\n");
	ITEM(({"painting", "paintings", "oil paintings"}), "Oil paintings of "
	+ "the ancestors of the Havecius family line the walls alongside city "
	+ "scapes of early Palanthas, the Tower of High Sorcery rising from "
	+ "the Shoikan Grove, a rampant gold dragon, the High Clerist's Tower, "
	+ "and the Bay of Branchala during a storm with high waves breaking "
	+ "upon the piers.  Among them, hung over the hearth, is a wide "
	+ "tapestry.\n");
	ITEM(({"tapestry", "wide tapestry"}), "Above the hearth, running its "
	+ "whole length, is a very old tapestry depicting a scene in the "
	+ "ancient style of a man in chainmail and princess in white coming "
	+ "from a grey stone vale, through a forest with armoured ogre, along "
	+ "a mountain path watched by a great serpent, to a sheltered bay and "
	+ "small white city where they appear holding hands and smiling at "
	+ "each other.\n");
	ITEM(({"style", "ancient style"}), "The tapestry above the hearth must "
	+ "be of great age for it is done in the ancient style which depicts "
	+ "people and scenes in simplified two dimension.  It is most common "
	+ "in ancient stained glass windows.\n");
	ITEM(({"hearth", "fireplace", "fire"}), "@@hearth_exa@@" + "  A grated"
	+ " iron stand sits beside the hearth for storing wood.  "
	+ "@@wood_state@@" 	+ "\n");
	ITEM(({"stand", "iron stand", "grated iron stand", "grated stand"}),
	  "This stand is used for holding logs of wood to fuel the fire.  It's "
	+ "grated with squared iron bars that extend upward between which the "
	+ "wood may be stacked.  " + "@@wood_state@@" + "\n");
	ITEM(({"wood", "log", "logs", "pile", "stack"}), "Wood for the fire is "
	+ "kept stacked in the grated iron stand by the hearth.  "
	+ "@@wood_state@@" + "\n");
	ITEM(({"stair", "stairs", "staircase"}), "A set of wooden stairs "
	+ "leads up to the rooms.  Its balustrade is well-worn and topped "
	+ "at its base by a polished brass ball.\n");
	ITEM(({"ball", "brass ball", "polished brass ball"}), "Set into the "
	+ "wooden balustrade of the staircase, the ball, though tarnished "
	+ "at its base, bears a small inscription, \"Est Cruces Vercius\".\n");
	ITEM(({"double doors", "swinging doors", "swinging double doors",
		"pair of doors"}), "A pair of doors near the corner in the southwest "
	+ "wall that swing in and out at a push from either side.\n");
	ITEM(({"chair", "chairs", "leather chairs", "high-backed chairs",
		"high-backed leather chairs"}), "Darkening bronze studs hold the "
	+ "stiched and padded leather to the high backs of these elaborate "
	+ "dark wood chairs.  The sturdy, dark brown leather covers the chair "
	+ "back, seat, and arms which fit just under the roundtables around "
	+ "which they are arranged allowing them to be pushed as close as "
	+ "desired to the table.\n");
	ITEM(({"seat", "seats", "plush seats", "plush leather seats"}),
	  "These all leather seats are low, wide, and so plush that it looks as "
	+ "if you'd sink in so comfortably that you'd never want to get up.  "
	+ "Before each one is a matching leather covered footrest.  A few are "
	+ "arranged near the hearth if you wish to enjoy its warmth.\n");
	ITEM(({"footrest", "footrests"}), "Four ornate and outwardly curved, "
	+ "short legs form the base of these sizeable, dark brown leather "
	+ "covered footrests.  They match the plush leather seats and are kept "
	+ "in front of them by the hearth.\n");
	ITEM(({"arms", "armaments", "shields", "arms and shields", "weapons"}),
	  "Ornamental arms of some age adorn the walls.  An old sabre crossed "
	+ "with a horseman's axe, a tarnished longsword behind an iron-rimmed "
	+ "wooden shield painted with a faded yellow slash, and a tarnished "
	+ "ball and chain crossed with an iron-headed warhammer are a few.\n");
	ITEM(({"head", "heads", "mounted head", "mounted heads",
		"stuffed head", "stuffed heads"}), "Mounted on ornately trimmed "
	+ "wooden backings are the heads of a mountain cougar, a large black "
	+ "bear, a buck with fourteen point antlers, a very large and tusked "
	+ "wild boar, and a great green snake head with fangs beared.\n");
	ITEM(({"table", "tables", "roundtable", "roundtables"}), "These old, "
	+ "dark reddish stained oak tables bear the nicks and scratches of a "
	+ "long life of service.  Despite their wear, they are of such quality "
	+ "that they may last another lifetime or two.  The tables are large "
	+ "enough for a party of half a dozen to sit around in the inn's "
	+ "high-backed chairs and high enough for the arms of those chairs to "
	+ "squeeze just below them.  On each roundtable in the middle is a "
	+ "small, iron oil-lamp shedding a soft glow above the table.\n");
	ITEM(({"lamp", "lamps", "oil lamp", "oil lamps"}), "These oil lamps "
	+ "hang low in the corners and sit atop the center of each roundtable, "
	+ "their tarnished, dark iron bodies mere outlines below the glow of "
	+ "their flames.\n");
	ITEM("counter", "Beside the entrance in the northeast of the inn is "
	+ "the innkeep's counter with its 'L' shape and polished marble top "
	+ "extending near the staircase.  Before it are several tall stools.  "
	+ "Behind it the innkeep serves drinks, rent rooms, and stores three "
	+ "large, tapped casks.  High on the wall behind the counter is a "
	+ "menu.\n");
	ITEM(({"stool", "stools"}), "Several tall, wooden stools are before "
	+ "the counter.  Their cushioned seats are atop smooth, round, wooden "
	+ "poles bolted to the floor and can swivel thanks to the ingenius "
	+ "gnomish gizmos below them.  All they are missing are bells and "
	+ "whistles.  You suspect this innkeep has removed them.\n");
	ITEM(({"cask", "casks"}), "Three large, four foot diameter wooden casks "
	+ "rest set into the wall behind the counter.  Each has a tap for "
	+ "serving its contents.\n");
	ITEM(({"sign", "menu", "list", "pricelist", "offering", "offerings"}),
	  "Written in flowing, cursive script in black ink upon a translucent "
	+ "white marble sign is the Greystone Inn's menu.  You may read it.\n");
	ITEM(({"hall", "inn"}), "That's where you are.  Have a look around.\n");
	ITEM("rack", "In the great hearth is a large iron rack for stacking "
	+ "wood upon.\n");

	CMD(({"sign", "menu", "list", "pricelist", "offering", "offerings"}),
	"read", "@@read");
	CMD("blat", "crobb", "@@crobb");
	CMD("hearth", "stack", "@@stack_hearth");
	CMD("stand", "stock", "@@stock_stand");
	CMD("fire", "set", "@@set_fire");
	CMD("fire", "ruin", "@@ruin_fire");

	EXIT(NOBLE + "grey_up2", "stairs", 0, 0);
	add_invis_exit(NOBLE + "n09", "kitchen", "@@enter_kitchen", 0);

	inndoor = clone_object(NOBLE_DOOR + "greystone1.c");
	inndoor->move(TO);

    reset_palan_room();
}

int
enter_kitchen()
{
   write("You push on the double doors.  They swing open, and you enter "
   + "the kitchen.\n\n");
   say(QCTNAME(TP) + " pushes on the double doors.\n");
   return 0;
}

string
hearth_state()
{
	/* Three+ settings for an int.
	 * If 3 its great hearth is empty of wood
	 * If 1 its great hearth is stacked wood...
	 * If 2 a fire burns in its great hearth shedding...
	 */
	if (hearth == 1)
	{	return "its great hearth is stacked full of split logs."; }
	if (hearth == 2)
	{	return "a roaring fire crackles in its great hearth."; }
	if (hearth == 3)
	{	return "dying coals glow in its great hearth."; }
	 return "Meekro!";
}

string
hearth_exa()
{
	/* States of int determine result of examining */
	if (hearth == 1)
	{	return "A great hearth, large enough to roast a boar in, its "
		+ "iron rack for holding wood is stacked with split logs ready "
		+ "for someone to <set fire> to."; }
	if (hearth == 2)
	{	return "A roaring fire crackles in the great hearth, large enough "
		+ "to roast a boar over.  Hopefully, no one wants to <ruin fire>"; }
	if (hearth == 3)
	{	return "A great hearth, large enough to roast a boar in, its "
		+ "iron rack for holding wood contains only ashes and awaits "
		+ "someone to <stack hearth> with wood."; }
	 return "Beedledo!";
}

string
wood_state()
{
	/* Two+ settings for an int.
	 * If 0 it's out of wood
	 * If 1 it has wood
	 */
	if (wood == 0)
	{	return "The iron stand is empty except for a few splinters of "
		+ "to indicate it once held split wooden logs.  It's ready "
		+ "for someone to <stock stand> with wood."; }
	if (wood == 1)
	{	return "The iron stand is neatly stacked with split wooden logs "
		+ "and is ready for someone to <stack hearth> with its wood."; }
	 return "Tito!";
}

stock_stand()
{
	/* remove wood object from player, too */
	object wod;

	if (wood == 1)
	{
		write("Admirable of you to stock the Greystone's hearth stand, "
		+ "but at present it is already full of wood.  Perhaps you can "
		+ "try again once that's been burned through.\n");
		return 1;
	}

	if (wod = present("wood", TP))
	{
		wood = 1;
		write("You neatly stack your wood upon the iron stand by the "
		+ "hearth.  It's now ready for someone to <stack hearth> with "
		+ "its wood.\n");
		return 1;
	}
	write("You're welcome to stock the hearth stand with wood, but "
	+ "this appears as if it will require that you have that wood "
	+ "first.\n");
	return "";
}

stack_hearth()
{
	if (hearth != 3)
	{	write("Admirable of you to stack the Greystone's hearth with "
		+ "wood, but at the moment, it's already fully stocked.  You "
		+ "are welcome to try again when it has burned out.\n"); return 1; }
	if (wood == 1)
	{
		wood = 0;
		hearth = 1;
		write("Taking the neatly piled wood from the iron stand by the "
		+ "hearth, you stack the wood in the great hearth.  Now it is "
		+ "ready for someone to <set fire> to it.\n");
		say(QCTNAME(TP) + " takes the neatly piled wood from the iron stand "
		+ "by the hearth and stacks it carefully inside the hearth's iron "
		+ "rack.\n");
		return 1;
	}
	write("There isn't any wood left in the stand to stack the hearth.\n");
	return 1;
}

set_fire()
{
	if (hearth == 2)
	{	write("There is already a good fire burning in the hearth.  Did "
		+ "you want to <ruin fire> and spoil everyone's fun?\n"); return 1; }
	if (hearth == 3)
	{	write("There are only coals and ashes in the iron rack of the "
		+ "great hearth.  Did you want to <stack hearth> with wood from "
		+ "the iron stand beside it?\n"); return 1; }
	if (hearth == 1)
	{
		hearth = 2;
		write("You light the pile of stacked, split wood logs in the great "
		+ "hearth.  A roaring blaze sheds flickering light and warmth "
		+ "across the hall.\n");
		say(QCTNAME(TP) + " lights a pile of stacked, split wood logs in the "
		+ "great hearth.  A roaring blaze sheds flickering light and warmth "
		+ "across the hall.\n");
		return 1;
	}
}

ruin_fire()
{
	if (hearth != 2)
	{	write("There would need to be a fire burning in order for you "
		+ "to be able to put it out.\n"); return 1; }
	else
	{	hearth = 3;
		write("You ruined the fire!  Why have you done this?!?\n");
		say(QCTNAME(TP) + " pretends no one is looking, pulls down " + HIS(TP)
		+ " pants, and urinates on the fire in the great hearth ruining "
		+ "it!  Why would " + HE(TP) + " do such a thing?!?\n");
		return 1;
	}
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
      "  ._____________________________________________.\n" +
	  "  |             The Greystone Inn              ||\n" +
	  "  |--------------------------------------------||\n" +
	  "  | Todo:  Coffee                   |       sc ||\n" +
	  "  | Todo:  Ale                      |       sc ||\n" +
	  "  | Todo:  Wine                     |       sc ||\n" +
	  "  | Todo:  Water                    |       sc ||\n" +
	  "  |                                 |          ||\n" +
	  "  |--------------------------------------------||\n" +
	  "  |                   Fare                     ||\n" +
	  "  |--------------------------------------------||\n" +
	  "  | Todo:  Pheasant                 |       sc ||\n" +
	  "  | Todo:  Venison                  |       sc ||\n" +
	  "  | Todo:                           |       sc ||\n" +
	  "  | Todo:  Greystone Dinner         |       sc ||\n" +
      "  |_________________________________|__________||\n" +
      "  \\_________________________________\\__________\\|" + "\n");
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
    
    NF("The innkeep is not here to arrange service.\n");
    if (!innkeep || !P(innkeep, TO))
      return 0;
    
    NF("Buy what?\n");
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
    
    switch(str1)
      {
	case "roast":
	case "roasts":
	case "evening roast":
	case "evening roasts":
	case "vanilla roast":
	case "vanilla roasts":
	case "evening vanilla roast":
	case "evening vanilla roasts":
	  name = "evening_vanilla";
	  price = num * 155;
	  break;
	case "coffee":
	case "coffees":
	case "blend":
	case "blends":
	case "special blend":
	case "special blends":
	case "light hart special blend":
	case "light hart special blends":
	  name = "special_blend";
	  price = num * 125;
	  break;
	case "wine":
	case "wines":
	case "red":
	case "reds":
	case "hartvale red":
	case "hartvale reds":
	case "glass of wine":
    case "glasses of wine":
	case "red wine":
	case "red wines":
	  name = "box_apricots";
	  price = num * 95;
	  break;
	case "toast":
	case "toasts":
	case "aniseed toast":
	case "aniseed toasts":
	  name = "bbiscuit";
	  price = num * 80;
	  break;
	case "paninos":
	case "turkey paninos":
	  name = "grape_half";
	  price = num * 190;
	  break;
	case "risotto":
	case "bowl":
	case "bowl of risotto":
	case "bowls":
	case "risottos":
	case "bowls of risotto":
	  name = "lpmuffin";
	  price = num * 170;
	  break;
	default:
	  NF("The innkeep looks confused for a moment and says:  I'm not sure "
	   + "what you want to buy.\n");
	  return 0;
      }
    if (num > 10)
      {
	  NF("The inn staff is good but can only fix a maximum of 10 items at a "
	  + "time.\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("A chef in a white coat brings you your order from the kitchen.\n");
    
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
	  file = OBJ + name;
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

string
crobb()
{
	if (!TP->query_npc())
	return "What?\n";
	TP->move_living("disappears under the counter momentarily",
		NOBLE + "grey_key_stall");
	TP->command("get key");
	TP->move_living("pops back up", NOBLE + "greystone");
	return "As it is.\n";
}
