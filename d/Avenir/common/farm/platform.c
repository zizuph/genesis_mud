/* Creator: Ibun
 * Revised by: Lilith, June 2004
 */
#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

inherit "/std/room";

void
create_room()
{
    set_short("The platform");
    set_long("This is the platform, or landing, of the stairway that once "+
        "connected the "+
        "upper floor of the manor with the lower level. It has just a "+
        "remnant of brownish-grey carpet tacked to the dust-laden floor, "+
        "the only sign of the prosperity of its former owners. "+
        "Directly north is the doorway to what appears to be a small room, "+
        "probably a bedroom. A broad corridor extends away from here along "+
        "the length of the house, and below you can see the great hall.\n");
    add_item("platform","@@long");
    add_item(({"corridor", "broad corridor"}),
        "It is a wide corridor. Your imagination gives it gleaming "+
        "hardwood floors, a runner of reddish carpet, and wall sconces, "+
        "but you cannot hold the image and it reverts to what it is: "+ 
        "a dusty, neglected corridor running east and west along the "+
        "length of the house. You measure the corridor to be approximately 18 feet wide.\n");
    add_item(({"doorway", "door", "north", "small room", "bedroom"}),
        "The doorway is framed in warped wood. Beyond it, all you can "+ 
        "see is a room.\n");
    add_item(({"carpet", "remnant"}),
        "You bend down to look at the carpet, but its state of filth "+
        "undermines your desire to conduct a closer inspection.\n");
    add_item(({"hall", "great hall", "below"}),
        "Leaning out from the railing you look down into the hall. " +
        "From up here you have a good view of whats happening down there. " +
        "@@desc_hall@@");
    add_item("railing","You grab the railing and shake it hard. The creaking " +
        "sound from it makes you take a step back.\n");
    add_item(({"stairway", "stairs"}), 
        "There is no stairway, only the memory of "+
        "one provided by the debris piled on the floor below, and "+
        "the scars along the wall where it once stood.\n");
    add_item(({"debris", "scars", "wall"}), 
        "You lean on the railing to try to get a better look, but the "+
        "loud cracking noise has you backing quickly away from there.\n");
    add_exit("bedroom_n","north");
    add_exit("corridor1e","east");
    add_exit("corridor1w","west");
    reset_room();
}

void
reset_room()
{

}

void
init()
{
    ::init();
    add_action("jump_hall", "jump");
}


string
desc_hall()
{
    object *ob, opp;
    object *liv;
    string str;

    if (LOAD_ERR(THIS_DIR + "hall"))
        return "You cant see anything of interest in the hall.\n";

    opp = find_object(THIS_DIR + "hall");

    if (!opp)
        return "You cant see anything of intetrest in the hall.\n";

    if (opp->query_prop(OBJ_I_LIGHT) <= 0)
        return "It is dark down there though, so you can't percieve any details.\n";

    ob = FILTER_CAN_SEE(all_inventory(opp), TP);

    if (!sizeof(ob))
        return "Nothing special down there attracts your eyes though.\n";

    return "Down in the hall you see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
}
 
string
desc(object ob)
{
    if (living(ob))
        return COMPOSITE_LIVE(ob);
    else
        return LANG_ADDART(ob->short());
}


int
jump_hall(string str)
{
    if (strlen(str) && (str == "to hall" || str == "down"))
    {

            write("You take a brave jump down and easily land on your " +
                "feet down in the hall.\n");
            say(QCTNAME(TP) + " takes a brave step out in the air and " +
                "disappears down into the hall.\n");
            tell_room(THIS_DIR + "hall",
                QCTNAME(TP) +
                " arrives from above with a thud on the floor.\n");
            TP->move_living("M", THIS_DIR + "hall", 1);
            return 1;
    }
            return 0;
}


