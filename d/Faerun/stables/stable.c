/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "/d/Faerun/thornhold/defs.h"
//#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include <filter_funs.h>

#define STABLES_DIR		    "/d/Faerun/thornhold/"
#define D_STABLES_DIR		"/d/Faerun/stables/" /* domain dir where main code sits */
#define STABLES_ROOM_DIR	"/d/Faerun/thornhold/rooms/"
#define STABLES_OBJ_DIR	    STABLES_DIR + "obj/"
#define STABLES_NPC_DIR	    STABLES_DIR + "npcs/"
#define STABLES_STEED_DIR	D_STABLES_DIR + "steeds/"
#define STABLES_LOG_DIR	    D_STABLES_DIR + "log/"
#define RIDER_OBJECT        D_STABLES_DIR + "rider_object"
#define STABLE_MASTER	    "/d/Faerun/thornhold/npcs/stablemaster.c"

inherit "/d/Gondor/common/lib/drink_water.c";
inherit BASE_KEEP;

#define FILTER_PONY(x) \
        filter((x), &operator(==)("Pony") @ &->query_name())

#define FILTER_HORSE(x) \
        filter((x), &operator(==)("Horse") @ &->query_name())

/* Globals */
static object Stable_master;

/* Function prototypes */
public string corral_desc();
int yard_security();

void
create_house()
{
	add_prop(ROOM_I_ALLOW_STEED, 1); // It's a stable so make an exception

    set_short("The Thornhold Stables");
    set_long("You are in the Thornhold stables. Dappled light spills in " +
             "from the courtyard, through spaces in the wooden planks that " +
             "were used to construct the stable entrance. In contrast, " +
             "the ceiling and exterior walls are constructed of the same " +
             "sturdy gray stone of the rest of the hold. A thick layer of " +
             "hay blankets the floor here, and several box stalls with " +
             "feeding and watering troughs for horses, ponies, and mules " +
             "currently in the care of the dwarves of Thornhold. You " +
             "can enter a farrier's workshop to the north, or return " +
             "west to the courtyard.\n");

	add_item("hay",
        "Hay blankets the floor here in a thick layer. It's clean, " +
        "and clearly the stable is well-tended.\n");

    add_item("corral",
        "@@corral_desc@@");

    add_cmd_item("poster", ({"read", "exa", "examine"}), "@@read_poster@@");
    add_cmd_item("sign", ({"read", "exa", "examine"}), "@@read_sign@@");

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({ "trough", "water"}) );
	
    add_exit(ROOM_DIR + "courtyard_south",  "west");
    add_exit(ROOM_DIR + "farrier",  "north");
    add_exit(ROOM_DIR + "corral", "east", yard_security, 0,1);

    reset_room();
}

void
reset_room()
{
    ::reset_room();
    if (!Stable_master)
        Stable_master = clone_object(STABLE_MASTER);

    if (!present(Stable_master, this_object()))
        Stable_master->move(this_object());
}

public void
init()
{
    ::init();
// This initializes the drink function.
    init_drink();
}

int
yard_security()
{
    // Block all but wizards, the stable master, and horses from entering the corral
    if (TP->query_wiz_level() || 
        TP->query_name() == "Torvil" ||
        TP->query_name() == "Torvil Jassen" ||
        TP->query_race() == "horse")
        return 0;

    write("You can't seem to enter the corral\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    object quest_horse;
    object leader_obj;
    object leader;
    int test;

    ::enter_inv(ob, from);
    if (present("__leader_object", ob))
    {
        leader_obj = present("__leader_object", ob);
    }
}



public string
corral_desc()
{
    object other_room;
    mixed opeople;

    if (!LOAD_ERR("/d/Faerun/thornhold/rooms/corral"))
        other_room = find_object("/d/Faerun/thornhold/rooms/corral");
    else
        return "ERROR: Corral error.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return "Behind the corral fence you see no horses.\n";
    else
        return "Behind the corral fence you see " + COMPOSITE_LIVE(opeople) + ".\n";
}


string read_poster()
{
    return  "\t+----------------------------------------------------------------+\n" +
            "\t|                                                                |\n" +
            "\t| I have the best steeds available for rent. They have been bred |\n" +
            "\t| to be gentle animals and as pack animals for travellers.       |\n" +
            "\t| Before you can use one, you must pay a fee. The fee is used to |\n" +
            "\t| maintain the stables and take care of the animals.             |\n" +
            "\t|                                                                |\n" +
            "\t| I do not rent to goblins, ogres, orcs, or minotaurs. They look |\n" +
            "\t| at my animals as food.                                         |\n" +
            "\t|                                                                |\n" +
            "\t| These are my fees:                                             |\n" +
            "\t|  * Start up fee . . . . . . . 100 pc                           |\n" +
            "\t|  * Rental Fee . . . . . . . .   1 pc                           |\n" +
            "\t|                                                                |\n" +
            "\t| Read the sign to see what animals are available. When you      |\n" +
            "\t| find an animal to rent, do this:                               |\n" +
            "\t|                                                                |\n" +
            "\t| <rent adj1 adj2 horse/pony>                                    |\n" +
            "\t| Example: rent haughty tan horse                                |\n" +
            "\t|                                                                |\n" +
            "\t| Large races like humans and elves, can only rent horses.       |\n" +
            "\t| Small races like hobbits, dwarves, and gnomes, can only rent   |\n" +
            "\t|                                                                |\n" +
            "\t| When you are finished with your animal, be sure to return it   |\n" +
            "\t| here. If you don't, you won't be able to rent a horse for      |\n" +
            "\t| 24 hours. To return your steed, do:                            |\n" +
            "\t|                                                                |\n" +
            "\t| <stable [animal]>                                              |\n" +
            "\t|                                                                |\n" +
            "\t| There may be times when all our horses and ponies are rented.  |\n" +
            "\t| Please be patient, We will get more shortly.                   |\n" +
            "\t|                                                                |\n" +
            "\t| Riding supplies and food for the animals are next door.        |\n" +
            "\t|                                                                |\n" +
            "\t| When you are mounted on your animal, do <hhelp> for commands   |\n" +
            "\t| and emotes.                                                    |\n" +
            "\t|                                                                |\n" +
            "\t|                                   Torvil Jassen, Stablemaster  |\n" +
            "\t|                                                                |\n" +
            "\t+----------------------------------------------------------------+\n";
}

public string
read_sign()
{
    object other_room;
    mixed opeople;
    string sign_ret = "";

    if (!LOAD_ERR(STABLES_ROOM_DIR + "corral"))
        other_room = find_object(STABLES_ROOM_DIR + "corral");
    else
        return "ERROR: We have a problem in the corral view. Please bug " +
            "report this.";

    int i;
    int sz = sizeof(opeople);

    opeople = FILTER_PONY(all_inventory(other_room));
    sz = sizeof(opeople);
    sign_ret += "\t+------------------------------------------------+\n";
    sign_ret += "\t|                                                |\n";
    sign_ret += "\t| These are the ponies and horses that are       |\n";
    sign_ret += "\t| available for rent.                            |\n";
    sign_ret += "\t|                                                |\n";
    sign_ret += "\t| Ponies:                                        |\n";
    for(i = 0; i < sz; i++)
        sign_ret += sprintf("\t| %3d : %-40s |\n", i+1, opeople[i]->short() );
    sign_ret += "\t|                                                |\n";

    opeople = FILTER_HORSE(all_inventory(other_room));
    sz = sizeof(opeople);
    sign_ret += "\t| Horses:                                        |\n";
    for(i = 0; i < sz; i++)
        sign_ret += sprintf("\t| %3d : %-40s |\n", i+1, opeople[i]->short() );
    sign_ret += "\t|                                                |\n";
    sign_ret += "\t|                  Torvil Jassen, Stablemaster   |\n";
    sign_ret += "\t|                                                |\n";
    sign_ret += "\t+------------------------------------------------+\n";
    sign_ret += "\n";
            
    if (!sizeof(opeople))
        return "Inside the corral you see no horses or ponies.\n";
    else
        return sign_ret;
}
