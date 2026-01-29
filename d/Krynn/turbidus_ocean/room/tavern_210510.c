#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

inherit SAIL_ROOM_BASE;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define TAVNAME "Crown o' Thorns"

#define TAVNPCDIR "/d/Krynn/turbidus_ocean/living/"
#define TAVOBJDIR "/d/Krynn/turbidus_ocean/obj/"
#define TAVOBJPAT "tavern_rareobj*"
#define TAVBSTICK "/d/Krynn/turbidus_ocean/obj/stick.c"

#define PATRON_I_HAS_FOUND_TIMBERS "_patron_i_has_found_timbers"

#define RARE_OBJECT_CHANCE_PCT 25
#define KICKOUT_CHANCE_PCT 25

#define NUM sizeof(MONEY_TYPES)

object tavernkeeper;      /* green skinned human barkeep */
object tavern_seadog;     /* a lone patron */

int test; /* to indicate that a test is going on, no money given. */


/*
* Prototypes
*/
int move_item(mixed arg);

/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_sea_room()
{
    if (!tavernkeeper)
    {
        tavernkeeper = clone_object(TAVNPCDIR + "tavernkeeper");
        tavernkeeper->move(TO);
    }

    if (!tavern_seadog)
    {
        tavern_seadog = clone_object(TAVNPCDIR + "tavern_seadog");
        tavern_seadog->move(TO);
    }
}


string
rareobject()
{
    int i, n, ns;
    string pathstr, *selectf;

    string *files = filter(get_dir(TAVOBJDIR), &wildmatch(TAVOBJPAT));

    if ( !sizeof(files) ) return TAVBSTICK;

    selectf = ({});
    foreach ( string file : files )
    {
        pathstr = sprintf("%s%s",TAVOBJDIR,file);
        n = find_object(pathstr)->query_prevalence();
        if ( !n ) n = 1;
        for ( i=0;i<n;i++ )
            selectf += ({pathstr});
    }

    ns = sizeof(selectf);
    if ( !ns ) return TAVBSTICK;
    return selectf[random(ns)];
}


string
find_in_timbers()
{
    object obj;
    string str;

    if( TP->query_prop(PATRON_I_HAS_FOUND_TIMBERS) )
    {
        return "Your search turns up nothing much of interest.";
    }

    if (!tavernkeeper)
    {
        TP->add_prop(PATRON_I_HAS_FOUND_TIMBERS,1);

        seteuid(getuid(this_object()));

        if ( random(100) < RARE_OBJECT_CHANCE_PCT )
            obj = clone_object(rareobject());
        else
            obj = clone_object(TAVBSTICK);
        obj->move(TP, 1);

        str = obj->short() + " , seemingly from an ancient wreck.";
        return "Free to search about the timbers and canvas of the ramshackle walls, "+
          "you come away with " + str;
    }
    else
    {
        return "Your search is interrupted by the chill feeling of the eyes of the "+
          "the tavern keeper boring into your back; that, and the tap on your shoulder "+
          "of a drunken seadog warning you that 'e don' allow lubbers to fossick'.";
        tell_room(TO,QCTNAME(TP) + " breaks off his search.\n",TP);
    }
}


int
query_standard_water_room()
{
    return 0; 
}

public void
sink(object ob)
{
    return;
}

void
create_sea_room()
{
    config_default_trade();

    set_short("The " + TAVNAME + " Tavern");
    set_long("@@long_descr");

    add_prop(ROOM_I_NO_CLEANUP, 1);

//VW
    add_item(({"jetsam","flotsam"}),"A fug of smoke, salt and sweat hangs heavy in the "
                 + TAVNAME + "Tavern \n");
//VW can find torches and clubs among the timbers

//VW TIMBERS are wet

//VW
    add_item(({"walls","ceiling"}),"The walls and ceiling of "+
               "the tavern consist of a jumble of shipwreck timbers, "+
               "canvas and cordage. This eccentric construction " +
               "offers the opportunity to fossick for firewood "+
               "for the braziers when out of sight of the barkeep. "+
               "Who knows what treasures may be mixed in with the dross?\n");

//VW brazier on the bar ... next to Nax
//VW rocky coral.... broken timbers atop it... worn smooth through use
    add_item(({"bar","centre"}),"A long " +
      "bar positioned defensively in " +
      "the corner of the tavern. A portly barman stands behind " +
      "it, pouring drinks for the rowdy clientele. A menu is tacked " +
      "on the wall behind the bar. \n");

    add_item(({"Tavern","tavern"}),"You stand " +
      "within the " + TAVNAME + " Tavern, the rowdy ramshackle joint at "+
      "the heart of the notorious pirate port that is Reefcutter's Jetty.\n");

    add_item(({"brazier","braziers","glowing brazier","glowing braziers"}), 
    "Dotted about, glowing braziers are stoked by patrons with driftwood "+
    "from the tavern's ramshackle walls -- serving to keep the sea's "+
    "damp chill from seeping inside. Smoke from the braziers wafts upwards "+
    "and passes through gaps between timbers and canvas in the jury-rigged "+
    "ceiling.\n");

//VW *** need variation in descriptions depending on whether Nax is present or not

    add_item(({"patrons","pirates"}),"Relying on pirates, corsairs, " +
      "and brigands for patrons, it is no wonder that this place is nothing " +
      "short of lively.\n");

    add_item(({"hole","holes","door","doors"}), "Any of the many holes, "+
             "big and small, between the timbers, canvas and cordage of the "+
             "walls offer a quick exit out to the jetty.\n");

    add_item("menu","A menu with words. Read it and don't make trouble.\n");

    add_cmd_item("menu", "read", "@@read");

    add_exit(ROOM + "jetty", "out");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

//VW
    add_search(({ "timbers", "walls", "ceiling" }), 5, "find_in_timbers",1);


/*VW
    set_tell_time(120+random(15));
    add_tell("All of a sudden there is a loud crash in the kitchen, " +
        "followed by a louder splashing noise.\n");
    add_tell("Suddenly you hear someone in the kitchen yell: \"Oh for " +
        "Paladin's sakes! Not again!\"\n");
    add_tell("Lovely aromas come to you from inside the kitchen. " +
        "Unfortunately - or fortunately for some - they all smell like potatoes.\n");
*/

    reset_sea_room();
}

//VW
public void
hook_smelled(string str)
{
    write("The magic of fermentation fills the air with anticipation.\n");
}


string
long_descr()
{
    return "You stand in the only tavern to be found in long "+
    "leagues of open water -- known as the " + TAVNAME + ". From the "+
    "outside it appears like nothing so much as sprawling jam of " +
    "ships timbers and jetsom that was granted life to crawl "+
    "starfish-like onto the shore and lie stranded and damp above "+
    "the high tide line.\n"+
    "At its heart lies a maelstrom of booze and bad "+
    "behaviour -- its denizens fight and curse and shout bawdies "+
    "in a never-ending revel. The weary slink away to the dark " +
    "corners of its innards to pass time passed out, before "+
    "returning to the fray.\n" +
    "Hot glowing braziers are dotted all about the place. "+
    "Any one of the many holes in the haphazard arrangement of "+
    "timbers and canvas that make up the tavern, will serve as a "+
    "way out. An imposing bar of rock and coral is at the centre "+
    "of all things.\n";
}

int
out_bar()
{
    write("You duck out a hole from the " + TAVNAME + "...\n");
    return 0;
}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init();

    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
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
      " \n" +
      "   Bladderwrack Gin          144 cc\n" +
      "   Sailors Rum               220 cc\n" +
      "\n" +
      "   Booty:  ID Export Brew     24 cc\n" +
      "      ("+ BREWCRAFT_MENU +") \n"+
      "\n" +
      "Take note that the barman does not like \n" +
      "strangers. He will not let you buy more \n" +
      "than ten things at once. He likes your \n" +
      "coins crossing his palm well enough.\n");
    return 1;
}

/*
* Function name: order
* Description:   The buyer orders a drink
* Arguments:     str - name of drink an possibly description on how to pay and
*                      get the change
*/
int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("buy what?\n");
    if (!str)
	return 0;

    /* Has the player defined how payment will be done and what change to get back? */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
	/* Well, maybe player has defined how payment will be done at least? */
	str3 = "";
	if (sscanf(str, "%s with %s", str1, str2) != 2)
	{
	    str2 = "";
	    str1 = str;
	}
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
	num = 1;

    switch(str1)
    {
    case "brew":
    case "brews":
    case "booty":
        name = "brewcraft_beermug";
	price = num * 24;
	break;
    case "gin":
    case "gins":
    case "bladderwrack":
    case "bladderwrack gin":
	name = "tavern_gin";
	price = num * 144;
	break;
    case "rum":
    case "rums":
    case "sailors":
    case "sailors rum":
	name = "tavern_rum";
	price = num * 220;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }
    if (num > 10)
    {
	NF("The barkeeper says: I aint carrying more than 10 things!\n");
	return 0;
    }
    if (num < 1)
        cheater_log(this_player(), this_object(), "buy 0 units");

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
	write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The barkeeper gets to work.\n");

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
        if (name != "brewcraft_beermug")
            file = TAVOBJDIR + name;
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

