/* 
 * The cellar of a modest estate in the southeast of
 * the Court d'Plaisiri in the Nobles quarter.  Gui,
 * the noble who lives there, collects and sells wines.
 *
 * Mortis 12.2005
 *
 * Sewer secret entrance in shadows in the corner?
 * If so, adjust exa's as well as smells which should
 * reveal drafts to perceptive races.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <cmdparse.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <money.h>

inherit NOBLE_ROOMBASE;
inherit "/lib/trade";

#define VIEWNW			(NOBLE + "nplaza")
#define NUM	sizeof(MONEY_TYPES)

int move_item(mixed arg); 
int test;

object vintner;

string
query_to_jail()
{
  return "northwest";
}


void
reset_palan_room()
{
	if (!vintner)
	{
	vintner = clone_object(NOBLE + "living/gui");
	vintner->move(TO);
	}
}

void
create_palan_room()
{
    config_default_trade();

    SHORT("A wine cellar");
    LONG("This is the cellar of a modest, two-story noble estate off the "
	+ "Court d'Plaisiri in the Plaisir district.  Its red and tan brick "
	+ "walls are cool to the touch, and the air is moist and cool.  Three "
	+ "marble steps lead up to an old door of dark oak in the northwest "
	+ "wall.  The walls are lined with casks and wine racks full of wine "
	+ "bottles that stretch from floor to ceiling.  Hanging on a thin, "
	+ "dark chain from the ceiling is an iron oil-lamp, and a dusty "
	+ "staircase leads up to an ornate door with gold-foil trim.\n");

	ITEM(({"plaza", "court"}), "The court is busy at all hours providing "
	+ "pleasurable services in the nobles quarter.  You can view it from "
	+ "the windows northwest.\n");
	ITEM("door", "Which door do you want to examine?  The old door of "
	+ "dark oak on the northwest wall, or the ornate door with gold-foil "
	+ "trim at the top of the dusty staircase?\n");
	ITEM(({"old door", "dark door", "oak door", "dark oak door"}), "Up "
	+ "three marble steps in the northwest wall is an old door of dark "
	+ "oak opening onto the alley behind the estate that leads to the "
	+ "Court d'Plaisiri.\n");
	ITEM(({"ornate door", "gold-foil door", "door with gold-foil trim",
		"door with gold-foil", "gold door"}), "At the top of a dusty "
	+ "staircase is an door with ornately carved woodwork trimmed with "
	+ "gold foil.\n");
	ITEM(({"staircase", "dusty staircase", "stairs"}), "A dusty staircase "
	+ "leads up to an ornate door with gold-foil trim.\n");
	ITEM(({"steps", "step", "three steps", "marble steps",
		"three marble steps"}), "Three marble steps of brown-tinged, "
	+ "translucent white lead up to an old door of dark oak in the "
	+ "northwest wall.\n");
	ITEM("floor", "The floor is brown-tinged, translucent white marble.\n");
	ITEM(({"wall", "walls"}), "The walls are made of dark red and tan "
	+ "bricks and are cool to the touch.  You can't see much of the walls "
	+ "as casks and wine racks line them from floor to ceiling in most "
	+ "places.\n");
	ITEM("ceiling", "The ceiling is brown-tinged, translucent white marble.  "
	+ "Hanging from its center is an iron oil-lamp.\n");
	ITEM(({"thin dark chain", "dark chain", "thin chain", "chain", "lamp",
		"oil lamp", "iron lamp", "iron oil lamp", "oil-lamp",
		"iron oil-lamp"}), "In the center of the marble ceiling hangs an "
	+ "iron oil-lamp on a thin, dark chain that splits into three to suspend "
	+ "the lamp in a level manner.  It sheds a wavering yellow glow about "
	+ "the wine cellar creating shadows in the corners.\n");
	ITEM(({"shadow", "shadows", "corner", "corners"}), "Wavering yellow "
	+ "light from the iron oil-lamp hanging from the ceiling forms shadows "
	+ "in the corners.\n"); // Sewer secret entrance?
	ITEM(({"cask", "casks", "rack", "racks", "wine rack", "wine rack",
		"shelf", "shelves"}),
	  "Casks of wine sit on shelves, and racks of wine line the walls in "
	+ "most places from ceiling to floor.  Judging by the labels and "
	+ "stamps, the casks look fairly new.  You may <peruse casks> if you "
	+ "wish to have a better look at them.  Some of the bottles of wine "
	+ "range from fairly recent to very old.\n");
	ITEM(({"wine", "wines", "bottle", "bottles"}), "The walls are stacked "
	+ "floor to ceiling with racks of wines some of which are quite old.  "
	+ "The store room area has several newer casks of wine stacked up for "
	+ "sale.  You may <peruse casks> if you wish.\n");
	ITEM(({"window", "windows"}), "Small windows sit high on along the "
	+ "northwest wall affording a good view of the Court d'Plaisir outside.  "
	+ "You may <view court> to have a look.\n");

	add_smell("vampire", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of wines, smells "
	+ "you might have enjoyed long ago.  You detect little fresh blood.");
	add_smell("morgul", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("human", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("elf", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("goblin", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the smells of red and white "
	+ "booze, not the good stuff, but pretty stiff.");
	add_smell("dwarf", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("hobbit", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("gnome", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("minotaur", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the smells of red and white "
	+ "booze, not the good stuff, but pretty stiff.");
	add_smell("halfhuman", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("halfelf", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("orc", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the smells of red and white "
	+ "booze, not the good stuff, but pretty stiff.");
	add_smell("hobgoblin", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the smells of red and white "
	+ "booze, not the good stuff, but pretty stiff.");
	add_smell("kender", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines.");
	add_smell("drow", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of old and "
	+ "exquisite red and white wines.  Being below ground again is a "
	+ "pleasant respit from the hectic city streets above.");
	add_smell("noldor", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of almost old but "
	+ "still fairly exquisite red and white wines.");
	add_smell("presence", "The air is cool, damp, and most, but this isn't "
	+ "the best form for experiencing it.");
	add_smell("unknown", "The air is cool, damp, and moist.  The smells of "
	+ "aging wood and dust mingle here with the bouquets of very old and "
	+ "exquisite red and white wines, but what the heck race are you?  Why "
	+ "not mail Krynn for fun?");

	EXIT(NOBLE + "nplaza", "northwest", 0, 0);
	EXIT(NOBLE + "vintner2", "stairs", "@@up_stairs", 0);

	CMD(({"plaza", "the plaza", "court", "the court"}), "view",
		  "@@view_plaza");

	reset_palan_room();
}

int
up_stairs() 
{ 
  write("The ornate door at the top of the stairs is barred shut from "
  + "the other side.\n"); 
  return 1; 
}

view_plaza()
{
	/* This function returns an equivalent of 'look' from nplaza
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWNW->long());
	target = find_object(VIEWNW);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Through the small windows high on the northwest wall, you can "
	+ "make out " + desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the small windows high on the northwest "
	+ "wall.\n");
 
	return 1;
}

void 
init()
{    
    ::init();
	ADA("peruse");
    ADD("order", "buy");
}

int
peruse(string str)
{
	if (!str)
	{
		write("What would you like to peruse?  The casks of wine?\n");
		return 1;
	}

	if (parse_command(str, ({}), "'cask' / 'casks' [of] [wine]"))
	{
		write("There are at present three varieties of casks in the "
		+ "store room area:  East Solace Chardonnay (5pc), Gea Calathin "
		+ "Pinot Noir (6pc), and Goodlund Honeywine(7pc).\n");
		return 1;
	}
	write("What would you like to peruse?  The casks of wine?\n");
	return 1;
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink and possibly description on
 * how to pay and get the change
 */

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;
    
    NF("The vintner is not here to fix your order.\n");
    if (!vintner || !P(vintner, TO))
      return 0;
    
    NF("Buy what?\n");
    if (!str)
      return 0;

    /* Has the player defined how payment will be done and what change
	 *to get back? */  
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

	if (parse_command(str1, ({}), "[east] [solace] 'chardonnay' "))
	{
		name = "cask_chardonnay";
		price = num * 8640;
	}

	else if (parse_command(str1, ({}), "[gea] [calathin] [pinot] 'noir'"))
	{
		name = "cask_pinotnoir";
		price = num * 10368;
	}

	else if (parse_command(str1, ({}), "[goodlund] 'honeywine' "))
	{
		name = "cask_honeywine";
		price = num * 12096;
	}

	else
	{
		write("Smiling in a friendly manner the vintner says:  All I have "
		+ "for sale is what you can peruse in the store room area.\n");
		return 1;
	}

	if (TP->query_prop("_has_helped_gui") != 1)
	{
		vintner->needs_help();
		return 1;
	}
    
	if (num > 2)
      {
	  NF("It's dangerous to handle more than two casks at a time.\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The vintner allows you to take your purchase from the shelf.\n");
    
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
	  file = NOBLE + "obj/" + name;
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
			    say(QCTNAME(ob) + " buys " + drink->short() + ".\n", ob);
			}
		  }
	    }
	  else 
	    {
		say(QCTNAME(ob) + " seems to be estimating something.\n", ob);
		return 1;
	    }
	  if (num < 1)
	    break;
      }
    
    if (num > 0)
      set_alarm(1.0, 0.0, &move_item(({name, num, ob})));
    return 1;
}
