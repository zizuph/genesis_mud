/*
 *  Herb shop of Imladris
 *  Finwe, July 1998
 *  
 */
 
inherit "/d/Shire/std/room.c";
#include "local.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

void reset_shire_room();
 
static object maeryon;  /* herbalist */
 
public void
create_shire_room()
{
    set_short("Herb Shop of Imladris");
    set_long("This is the herb shop of Imladris. An pungent, " +
        "earthy, smell fills the room. The shop has a high " +
        "ceiling and a counter running the width of the room. " +
        "Behind the counters are many shelves filled with jars " +
        "and compartments. A sign is posted on the wall behind " +
        "the counter.\n");
 
    add_item("ceiling",
        "Large carved beams hold up the roof high above you. " +
        "Attached to the beams are hooks with some drying herbs.\n");
    add_item(({"down", "floor", "ground"}),
        "The floor is made of stone, swept clean by the herbalist.\n");
    add_item(({"walls", "wall"}),
        "The walls are strong and durable, made of planed wood. " +
        "Some shelves are attached to the walls.\n");
    add_item("shelves",
        "They are behind the counter, full of jars and drawers.\n");
    add_item(({"jars", "jar"}),
        "The jars sit behind the counter on the shelves. They " +
        "are full of herbs.\n");
    add_item(({"drawers"}),
        "The drawers sit on the shelves behind the counters. " +
        "They are closed.\n");
    add_item("hooks",
        "The hooks are shiny and attached to the ceiling. Some " +
        "are full of hanging herbs that are drying.\n");
    add_item("drying herbs",
        "They are different species of plants being dryed for " +
        "their many properties. They hang upside down from " +
        "hooks in the ceiling.\n");
    add_cmd_item("sign", "read", "@@read_sign@@"); 
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great Elven-power prevents you from teleporting there.\n");
 
    reset_shire_room();
 
    add_exit(VALLEY_DIR + "n_path01", "west");
}
 
 
void
reset_shire_room()
{
 
    if (!maeryon)
        maeryon = clone_object(RNPC_DIR + "herbalist");
    if (!present(maeryon,this_object()))
        maeryon->move(this_object());

}

string
read_sign()
{
    return 
        "\n" +
        "Welcome to the herb shop of Imladris. If you have\n" +
        "any herbs you can't identify, give them to the\n" +
        "herbalist and she can tell you what they are.\n\n" +
        "You can also <buy herbs> or <list herbs> to see what\n"+
        "she currently has in stock.\n\n"+
        "Since space is so valuable and used for storing\n" +
        "herbs, the shopkeeper has agreed to sell pouches.\n\n\n";
}
