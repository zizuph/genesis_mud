/*
 *  /d/Gondor/anorien/druedain/amon-din/storage1.c
 *
 *  August 1995, by Gorboth
 *
 *  Modification log:
 *    Alto -> added shelf and search for Denethor pyre quest.
 *
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/binbit.c";


#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"

#define INNER_MINAS "/d/Gondor/minas"

int bundle_is_taken = 0;

public string do_search(object actor, string str);
public int get_bundle(object actor, int i);

object bundle;

void reset_room();

void
create_room()
{
    set_short("in a long narrow storage building");
    set_long("Long shadows run the length of the inside walls of"
      + " this building, adding a very gloomy aspect to the place."
      + " Though it is not directly apparent from this vantage point,"
      + " this seems to be some sort of holding area for woodstores,"
      + " as the floor is littered with debris. The building extends"
      + " further to the north.\n");
    add_item(({"shadow","shadows"}), 
        "Shadows extend deep into this building, making it difficult"
      + " to see much of anything.\n");
    add_item(({"wall","walls"}), 
        "The brick walls of this building are stark and bare. The"
      + " feeling of this place is one of stern functionality. There"
      + " is a shelf on the east wall.\n");
    add_item(({"building","place"}), 
        "The building is long and fairly narrow, extending a ways to"
      + " the north. A lack of any windows makes visibility quite"
      + " poor in here.\n");
    add_item(({"window","windows"}), "If only there were some!\n");
    add_item(({"floor","ground"}), 
        "The floor seems to have remained unswept for quite some time,"
      + " as there are debris and dirt scattered everywhere.\n");
    add_item(({"debris","dirt","wood","bits","bits of wood","bark"}),
        "Dried flakes of bark and bits of wood virtually cover"
      + " the floor surface inside this building. There must be a"
      + " good deal of lumber passing through this place.\n");
    add_item(({"west wall", "western wall"}), "It is stark and bare.\n");
    add_item(({"east wall", "eastern wall"}), "It is stark and bare. A "
      + "shelf extends from the wall several feet above the floor.\n");
    add_item(({"shelf"}), "It is difficult to see if the shelf has anything "
      + "on it. Perhaps you should search it?\n");

    add_exit(AMON_DIR + "storage2.c", "north");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG, "A dark, narrow building.\n");
    add_prop(ROOM_I_LIGHT, 0);

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");


    setuid();
    seteuid(getuid());

    enable_reset();
    reset_room();
}

void
reset_room()
{

        bundle_is_taken = 0;

    if(!objectp(present("amon_din_storage_door_in")))
    {
        clone_object(AMON_DIR + "doors/stdoorin")->move(TO);
    }
}


public string
do_search(object actor, string str)
{
    if(!str)
        NFN("Search what?");

    switch(str)
    {
        case "shelf" :
            WRITE("You carefully examine the shelf on the east wall.\n");
            get_bundle(actor, 1);
            return "\nA little dust gets in your eyes.\n";
    }
     NFN("You don't find any " + str + " to search.");
}


public int
get_bundle(object actor, int i)
{
    if ((actor->test_bit("Gondor",
        MTIRITH_PORTER_GROUP,
        MTIRITH_DENETHOR_BIT)) || bundle_is_taken)
    {
        WRITE("There appears to be nothing on the shelf.");
        return 0;
    }

    if (!actor->query_prop(QUESTING_FOR_BUNDLE))
    {
        WRITE("The shelf appears to be empty.");
        return 0;
    }


    if (actor->query_prop(QUESTING_FOR_BUNDLE))
    {
        WRITE("You find a large bundle of firewood on the shelf!");
        bundle_is_taken = 1;
        actor->add_prop(FOUND_DENETHOR_BUNDLE, 1);

        bundle = clone_object(INNER_MINAS + "/obj/denethor_q_bundle");
        bundle->move(actor, 1);
        return 1;
    }

    else
    {
    WRITE("There is nothing special about the shelf.");
    return 0;
    }
}
