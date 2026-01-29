/* innroom: Place to sleep in Golden Inix Inn
 *   Based on Prancing Pont Inn in Bree, which seems to have come
 *   from the Ri Albi hotel room and been modified all sorts.
 *
 *	June 30, 2000, Fylo - removed the .c extension from the temp
 *						  start location string. This seemed to
 *						  prevent the proper setting of the temp
 *                        start location.
 *
 */

inherit "/std/room.c";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void
create_room()
{
    ::create_room();
    set_short("a room in the golden inix inn");
    set_long("This cramped chamber is just large enough to contain a cot, "+
             "a chamberpot, and whoever plans on sleeping here. There is "+
             "of course no room service, unless you count the occasional "+
             "lizard or insect that wanders through (of course they could "+
             "very well be renting the next room). Large elvish travel "+
             "symbols are engraved on the wall.\n");

    add_item(({"insect", "reptile"}), "I was kidding! Really. They aren't "+
             "wandering. Sleeping next door yes, but not wandering.\n");

    add_item("cot", "The pile of stuffed cloth doesn't look especially "+
             "comfortable. But it was cheap.\n");

    add_item("chamberpot", "Ever the intrepid researcher, you feel around "+
             "inside it and find it filled with....\n");

    add_item(({"wall", "symbol", "symbols"}), "Found in almost every inn "+
             "in Athas, the symbol means that it is deemed safe for a "+
             "person to 'start here' in this place.\n");

    INSIDE

    add_exit(TYR_CARAVAN+"innrecpt.c", "down", 0, 1);
}

init()
{
    ::init();
    add_action("start","start");
}

int
start(string s)
{
    object ob;
    if(!(ob=present("_tyr_room_key_",TP)))
    {
        write("How do you propose to do that without a room key?\n");
        return 1;
    }
    NF("Start where?\n");
    if(s!="here") return 0;
    ob->remove_object();
    TP->set_temp_start_location(TYR_CARAVAN + "innroom");
    write("You toss around in the cot for some time, eventually dozing off "+
          "with foolish confidence that you will reawaken alive and in "+
          "the same spot.\n");
    TP->command("quit");
    return 1;
}
