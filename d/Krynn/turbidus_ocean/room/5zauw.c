#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

#define CHEST_OBJECT   "/d/Krynn/turbidus_ocean/obj/barnacled_chest"
#define SCROLLCASE     "/d/Krynn/solamn/palanthas/nobles/obj/bishon_scrollcase"
#define RECIPE         "/d/Krynn/solamn/palanthas/nobles/obj/bishon_potion_scroll"

string *herbs = HERB_MASTER->query_herbs( ({ "seabottom","intertide", }) );

object chest;
object scrollcase;
object scroll;

string
query_sink_path()
{
    return "";
}

/* Objects don't sink here */
public void
sink(object ob)
{
    return;
}

void
reset_sea_room()
{
    set_searched(0);

    if(objectp(chest))
    {
        if(!present(scrollcase, chest))
        {
            scrollcase = clone_object(SCROLLCASE);
            scrollcase->move(chest, 1);
            scroll = clone_object(RECIPE);
            scroll->move(scrollcase, 1);

            chest->add_prop(CONT_I_CLOSED, 1);
            chest->add_prop(CONT_I_LOCK, 1);
        }
        else
        {
            tell_room(TO, "The barnacle-covered chest slowly " +
                "sinks into the sand.\n", 0);
            chest->remove_object();
        }
    }

    return;
}

mixed
search_sand(object searcher, string what)
{

    if (CAN_SEE_IN_ROOM(this_player()))
    {
        if(!objectp(chest))
        {
            setuid();
            seteuid(getuid());
            chest = clone_object(CHEST_OBJECT);
            chest->move(TO, 1);
            scrollcase = clone_object(SCROLLCASE);
            scrollcase->move(chest, 1);
            scroll = clone_object(RECIPE);
            scroll->move(scrollcase, 1);

            say(QCTNAME(this_player())+ " found a barnacle-covered " +
                  "chest buried in the sand!\n");
	    return ("Your search through the sand and find a barnacle-covered " +
                 "chest amongst the ship wreckage.\n");
        }
	else
	  {
	      return "You search through the sand, but do not find anything " +
                  "of interest.\n";
	  }
    }
  return 0;
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"dangerous shoals","shoals","sandbars"}),
        "To your north you can make out through the clear waters shoals and sandbars " +
        "that provide protection from the rough ocean, but also danger to " +
        "any ship wanting to enter the bay.\n"); 
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north beyond the sandbars is the Turbidus Ocean - a massive body " +
        "of water that extends from the Courrain Ocean in the east, across " +
        "northern Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"water"}),
        "The water here is calm and clear, allowing you good visibility of " +
        "the sea bed around you.\n");
    add_item(({"sea bed", "bed", "bay", "sand", "golden sand"}),
        "The sea bed of this bay is a blanket of golden sand, largely undisturbed " +
        "except for pieces of wreckage from a small sailing vessel.\n");
    add_item(({"wreckage", "wreck","hull","parts","remains of a ship's hull",
        "vessel","small sailing vessel"}),
        "It looks like the hull of a sailing vessel was ripped open from the " +
        "shoals to the north, leaving wreckage half-buried in the sand here.\n");
    add_cmd_item(({"water","to surface","up" }),
         ({"dive","swim"}),"If you want to swim up, just head in that direction!\n");

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER); 

    add_exit(ROOM + "5za", "up", "@@swim_up", 1, 1);

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water", "sea bed", "bed"}), 2);

   add_search(({"sand", "golden sand", "wreckage" }), 
       10, "search_sand", 1);

    reset_sea_room();
}

int
swim_up()
{
    write("You swim up to the surface.\n");
    say(QCTNAME(TP)+ " swims up to the surface.\n");
    return 0;
}

string
short_descr()
{
    return "sandy sea bed of a sheltered bay";
}
 
string
long_descr()
{
    return "You are underwater on a sea bed in a sheltered bay " +
        "bordering the Turbidus Ocean. The water here is clear and calm, " +
        "the sea floor a carpet of golden sand broken up only by what looks " +
        "like parts of the wreckage of a small sailing vessel - part of the " +
        "remains of a ship's hull. " +
        "To your north shoals and sandbars provide a natural barrier to the " +
        "ocean, but also making passage in that direction impossible. "+
        "\n";
}


