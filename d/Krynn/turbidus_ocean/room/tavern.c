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
#define TAVBSTICK "/d/Krynn/turbidus_ocean/obj/stick.c"

// where objects from sunken ships are catalogued:
#define TREASUREMAP "tavern_treasuremap"
#define NULLPLYNAME "null_player_name"

#define NUM_HIDDEN_WEAPONS 3
#define NUM_HIDDEN_DRINKS 9

#define NUM sizeof(MONEY_TYPES)

object tavernkeeper;      /* green skinned human barkeep */
object tavern_seadog;     /* a lone patron */

// sunken treasure map
mapping sunk_t_map;

int test; /* to indicate that a test is going on, no money given. */

static int gNumHiddenWeapons;
static int gNumHiddenDrinks;

/*
* Prototypes
*/
int move_item(mixed arg);


void
getchk_treasuremap()
{
   int n, i;
   string str, fname;
   mixed ind, val;

   setuid();
   seteuid(getuid());
   sunk_t_map = restore_map( TAVOBJDIR + TREASUREMAP );

   ind = m_indices(sunk_t_map);
   val = m_values(sunk_t_map);
   n = sizeof(ind);

   for ( i=0;i<n;i++ )
   {
       // all new-format entries should be two element arrays
       // old-format was a single variable
       // this converts old to new

       if ( !pointerp(val[i]) )
           sunk_t_map[ind[i]] = ({val[i],NULLPLYNAME});

       // delete any entries which no longer refer to extant objects

       fname = sprintf("%s.c",sunk_t_map[ind[i]][0]);
       if ( file_size(fname) == -1 )
           sunk_t_map = m_delete(sunk_t_map,ind[i]);
   }

   return;
}


void
put_treasuremap()
{
   save_map( sunk_t_map, TAVOBJDIR + TREASUREMAP );
   return;
}


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
        tell_room(TO,
        "The damp greenish tavern-keeper surveys the dismal state of " +
        "the " + TAVNAME + "; his unmoving fishy eyes appraise the " +
        "burnt-out braziers all about. Shivering with cold, he makes " +
        "his way to the timbers which make up the walls of the tavern. " +
        "He slips items from a rucksack into the walls while extracting "+
        "wood in return. One by one he stocks the braziers with the wood "+
        "and lights them -- blowing upon them and huddling close for warmth.\n");
        gNumHiddenWeapons = NUM_HIDDEN_WEAPONS;
        gNumHiddenDrinks = NUM_HIDDEN_DRINKS;
    }

    if (!tavern_seadog)
    {
        tavern_seadog = clone_object(TAVNPCDIR + "tavern_seadog");
        tavern_seadog->move(TO);
    }

    getchk_treasuremap();
    put_treasuremap();
}


string
find_behind_bar()
{
    object obj;
    string str;
    int nind;
    mixed ind;

    if ( !tavernkeeper )
    {
        if ( !gNumHiddenDrinks )
            return "Your search turns up nothing much of interest.";

        switch ( random(3) )
        {
            case 1:
                move_item(({"tavern_gin", 1, TP}));
                break;
            case 2:
                move_item(({"tavern_rum", 1, TP}));
                break;
            default:
                move_item(({"brewcraft_beermug", 1, TP}));
                break;
        }

        gNumHiddenDrinks--;

        return "Sly rummaging behind the bar yields you a drink!";
    }
    else
    {
        tell_room(this_object(),QCTNAME(TP) + 
              " breaks off a sly search behind the bar.\n",TP);
        return "Your sly search behind the bar is interrupted by the chill "+
           "eyes of the tavern keeper boring into you. "+
           "You retreat sheepishly from his gaze.";
    }
}


string
find_in_dross()
{
    object obj;
    string str;
    mixed ind;

    if (!tavernkeeper)
    {
        if ( !gNumHiddenWeapons )
            return "Your search turns up nothing much of interest.";

        seteuid(getuid(this_object()));

        getchk_treasuremap();
        ind = m_indices(sunk_t_map);

        int i = random(sizeof(ind));

        string objfile = sunk_t_map[ind[i]][0];

        // NB: remaining sunk_t_map array values are names of all players
        // who were aboard the ship that sunk when the object
        // was catalogued ... this is to prevent players shipwrecking
        // on purpose to cloning old items for new ones findable in dross 

        if ( i < 0 || 
              member_array(TP->query_real_name(),sunk_t_map[ind[i]]) != -1 )
                  objfile = TAVBSTICK;

        obj = find_object(objfile);

        if ( !objectp(obj) )
            return "Your search turns up nothing much of interest.";
        else
            if ( pointerp(obj->query_prop(MAGIC_AM_MAGIC)) )
                sunk_t_map = m_delete(sunk_t_map,ind[i]);

        // NB: if object is magical (above) then cloning allowed this one
        // time but delete object from sunk_t_map to prevent repeats

        obj = clone_object(objfile);
        obj->move(TP, 1);

        gNumHiddenWeapons--;

        put_treasuremap();

        str = obj->short() + ", seemingly from an old wreck.";

        return "Free to search about the timbers and canvas dross of "+
          "the ramshackle walls, you come away with " + str;
    }
    else
    {
        return "Your search is interrupted by the chill feeling of the eyes of "+
        "the tavern keeper boring into your back; that, and the tap on your "+
        "shoulder of a drunken seadog warning you that 'e don' allow lubbers "+
        "to fossick'.\n";

        tell_room(this_object(),QCTNAME(TP) + " breaks off a search of the "+
        "dross that makes up the structure of the tavern.\n",TP);
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


public string
descr_braziers()
{
    if ( !tavernkeeper )
    {
        return "Dotted about, braziers have burned through their wood "+
        "-- now gone cold and wafting smoke in the chill gusts from outside.\n"; 
    }
    else
    {
        return "Dotted about, glowing braziers are stoked with wood "+
        "from the tavern's ramshackle walls -- serving to keep the sea's "+
        "damp chill from seeping inside. Smoke from the braziers wafts upwards "+
        "and passes through gaps between timbers and canvas in the jury-rigged "+
        "ceiling.\n";
    }
}


public string
descr_patrons()
{
    if ( !tavernkeeper )
    {
        return "Ordinarily patronised by pirates, corsairs, " +
        "and brigands, now this place seems haunted by nothing " +
        "more than bad feelings.\n";
    }
    else
    {
        return "Relying on pirates, corsairs, " +
        "and brigands for patrons, it is no wonder that this place is nothing " +
        "short of lively.\n";
    }
}


public string
descr_tavern()
{
    if ( !tavernkeeper )
    {
        return "You stand " +
         "within the " + TAVNAME + " Tavern, the normally rowdy joint at "+
         "the heart of Reefcutter's Jetty -- now cold and empty.\n";
    }
    else
    {
        return "You stand " +
         "within the " + TAVNAME + " Tavern, the rowdy ramshackle joint at "+
         "the heart of the notorious pirate port that is Reefcutter's Jetty.\n";
    }
}


public string
descr_bar()
{
    string str = "A high bar of native rock is positioned as a defensive " +
      "ring at the centre of the tavern. Patrons approach the bar with " +
      "care, navigating the exposed sharp corals and shells which populate "+
      "bar's the rocky face. Atop the bar, old broken ships' timbers "+
      "provide a flatish surface on which to put drinks and pass out. " +
      "A brazier stands upon the bar to keep the tavern-keeper and "+
      "patrons warm.\n A menu is propped-up on the bar beside the brazier.\n";

    if ( !tavernkeeper )
    {
        return str + "There is no sign of the tavern-keeper.\n";
    }
    else
    {
        return str + "The tavern-keeper stands within the ring "+
            "of rock that forms the bar.\n";
    }
}


public string
descr_menu()
{
    if ( !tavernkeeper )
        return "A menu with words... and the life-blood stains of the "+
          "person who would take your order.\n";
    else
        return "A menu with words. Read it and don't make trouble.\n";
}

public string
descr_tell1()
{
    if ( !tavernkeeper )
        return "A knot of cutthroats and brigands slink away in fear "+
               "of the curse.\n";
    else
        return "A noisy patron goes suddenly silent; his body tumbles "+
               "outside to the water.\n";
}

public string
descr_tell2()
{
    if ( !tavernkeeper )
        return "Sea urchins, marooned cabin boys and girls, fossick "+
               "about the place.\n";
    else
        return "A bottle of rum is smashed over the head of someone "+
               "who looked thirsty.\n";
}

public string
descr_tell3()
{
    if ( !tavernkeeper )
        return "A bulge of canvas and cordage makes a melancholy "+
                "sound, caught in the chill wind.\n";
    else
        return "A group of Ergothian mutineers sing of better days, "+
                "deep in their cups.\n";
}


void
create_sea_room()
{
    config_default_trade();

    set_short("The " + TAVNAME + " Tavern");
    set_long("@@long_descr");

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"timbers","canvas","cordage","dross","jumble",
               "collection of dross"}),
               "The timbers, canvas, cordage and other dross "+
               "which make up the walls and ceiling of "+
               "the tavern drip moist with cold sea water. "+
               "This eccentric construction " +
               "offers the opportunity to search for things lost, "+
               "fossicking in the dark and damp. "+
               "Who knows what treasures may be mixed in with the dross?\n");

    add_item(({"walls","ceiling"}),"The walls and ceiling of "+
               "the tavern consist of a jumble of shipwreck timbers, "+
               "canvas and cordage -- a collection of dross which " +
               "acts as a structure, while also tempting scavengers "+
               "and beachcombers.\n");

    add_item(({"hole","holes","door","doors"}), "Any of the many holes, "+
             "big and small, between the timbers, canvas and cordage of the "+
             "walls offer a quick exit out to the jetty.\n");

    add_item(({"tavern"}),"@@descr_tavern");

    add_item(({"bar","centre","coral"}),"@@descr_bar");

    add_item(({"brazier","braziers","glowing brazier","glowing braziers"}), 
                 "@@descr_braziers");

    add_item(({"patrons","denizens"}),"@@descr_patrons");

    add_item("menu","@@descr_menu");

    add_cmd_item("menu", "read", "@@read");

    add_exit(ROOM + "jetty", "out");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

    add_search(({ "timbers", "dross", "lost", "things lost" }), 
            5, "find_in_dross",1);
    add_search(({ "bar", "centre" }), 5, "find_behind_bar",1);

    set_tell_time(120+random(15));
    add_tell("Waves of the cruel sea can be heard crashing on the shore.\n");
    add_tell("Gulls peer intently through the holes and gaps in "+
               "the walls of the tavern.\n");
    add_tell("A crab picks particles of rotted patrons' flesh from " +
               "the coral of the bar.\n");
    add_tell("@@descr_tell1");
    add_tell("@@descr_tell2");
    add_tell("@@descr_tell3");

    reset_sea_room();
}


public void
hook_smelled(string str)
{
    if ( !tavernkeeper )
        write("The chill sweeping in through the walls makes it hard "+
                 "to smell anything.\n");
    else
        write("Warm smoke fills the nostrils, keeping the cold of the "+
                "sea at bay.\n");
}


string
long_descr()
{
    if ( !tavernkeeper ) 
    {
        return "You stand in the only tavern to be found in long "+
        "leagues of open water -- known as the " + TAVNAME + ". From the "+
        "outside it appears like nothing so much as sprawling jam of " +
        "ships timbers and jetsom that was granted life to crawl "+
        "starfish-like onto the shore and lie stranded and damp above "+
        "the high tide line.\n"+
        "It seems deserted by its regular crowd of patrons; boozers and bad "+
        "behavers all. The party is over, and there is only blood and bits on "+
        "the sand floor to show for it.\n"+
        "Braziers are dotted all about the place -- trailing smoke "+
        "in the gusts of cold salt air which penetrate the tavern walls. "+
        "Any one of the many holes in the haphazard arrangement of "+
        "timbers and canvas that make up the tavern, will serve as a "+
        "way out. An imposing bar of rock and coral is at the centre "+
        "of all things. It is untended and splashed with blood.\n"+
        "It looks like someone or something has been searching "+
        "through the dross making up the walls of this place.\n";
    }
    else
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
        "of all things -- whence the tavern-keeper coldly eyes his domain.\n";
    }
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
      "The tavern-keeper will not let you buy more\n" +
      "than ten drinks at once. There is enough\n" +
      "drunken brawling as it is. He will accept\n" +
      "donations of wooden items to keep the\n" +
      "braziers burning.\n");
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

    NF("There is no one alive behind the bar to serve you.\n");
    if (!tavernkeeper)
        return 0;

    NF("buy what?\n");
    if (!str)
	return 0;

    /* Has the player defined how payment will be done and change to get back? */  
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
	NF("The tavern-keeper says: I aint carrying more'n 10 things!\n");
	return 0;
    }
    if (num < 1)
        cheater_log(this_player(), this_object(), "buy 0 units");

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
	write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The tavern-keeper gets to work.\n");

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
                    if ( !tavernkeeper ) 
                    {
                        ob->catch_msg("You steal " + drink->short() + ".\n");
                        say(QCTNAME(ob) + " steals " 
                                   + drink->short() + ".\n", ob);
                    }
                    else
                    {
                        ob->catch_msg("You get " + drink->short() + ".\n");
                        say(QCTNAME(ob) + " buys " + drink->short() + ".\n", ob);
                    }
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


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}
