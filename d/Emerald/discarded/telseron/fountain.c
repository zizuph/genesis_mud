#pragma save_binary
 
inherit "/std/room.c";

inherit "/d/Emerald/lib/room_tell";
 
#include "/d/Emerald/defs.h"
#include <macros.h>
 
object places;
 
create_room()
{
    set_short("At a large fountain");
    set_long("   You are standing on top of a small knoll in the " + 
        "center of the park. The atmosphere here is quiet and " +
        "restful. Many residents come here to listen to the " +
        "soothing music of the large fountain here. Encircling " +
        "the fountain are marble benches which offer comfort for " +
        "those who come up here. Sprinkled across the knoll are " +
        "stands of various trees, creating the effect of being in " +
        "the center of a forest.\n\n");
 
    add_item(({"knoll", "hill"}),
        "The knoll is a grass covered small hill, situated in the " +
        "center of the town. It is dotted with small white flowers " +
        "and a few stands of trees.\n");
    add_item("stands",
        "The stand of trees are made up birches, maples, and oak\n");
    add_item("benches",
        "Elegantly carved of white marble, these benches encircle " +
        "the fountain.\n");
    add_item("fountain",
        "This fountain is quite large and impressive. It sits atop " +
        "a natural spring and is believed by the citizens to have " +
        "healing properties. The fountain has three tiers from " +
        "which water cascades down to the lower bowls of water.\n");
    add_item("grass",
        "The grass is a rich velvet carpet of green, extending over " +
        "and beyond the knoll.\n");
    add_item(({"lower tier", "first tier"}),
        "This tier is the bottom of the fountain. It is quite " +
        "deep in portions. In the center of it, full size statues " +
        "of graceful elves support the upper tiers as water flows " +
        "down before them, forming a crystal curtain. The bowl " +
        "measure about 30 feet across.\n");
    add_item(({"middle tier", "second tier"}),
        "This tier is bowl shaped. Measuring 20 feet across, its " +
        "edge is fluted, allowing water to flow over the edge to " +
        "create a crystal curtain below. Large marble dolphins " +
        "and fish decorate the tier as they spout water into " +
        "the air. The upper tier is supported by full size " +
        "elven warriors.\n");
    add_item(({"upepr tier", "third tier"}),
        "From this distance, it's hard to tell very much about " +
        "the upper tier. You can tell it's bowl with fluted " +
        "edges. Water streams from to the second tier. Water " +
        "spouts up and over a statue that stands in the center of " +
        "the pool of water. It appears that the bowl is about 10 " +
        "feet across.\n");

    add_prop(OBJ_I_CONTAIN_WATER,1);

    set_tell_time(20);
    add_tell("Some elves roll down the knoll.\n");
    add_tell("A breeze caresses your cheek.\n");
    add_tell("An elf splashes you with water.\n");
    add_tell("The fountain sprinkles you with water.\n");
    add_tell("Some elves quietly talk in the distance.\n");
    add_tell("A small group of elves stand up and walk down the " +
        "knoll.\n");
    add_tell("An elf arrives and walks around the fountain.\n");
    add_tell("An elf joins a friend and sits on a bench.\n");
    add_item("The leaves of the trees rustle as a breeze " +
        "floats by.\n");
    add_tell("A gentle floral frangrance fills the air.\n");


    add_exit( TOWNSHIP_DIR + "pk02", "north");
    add_exit( TOWNSHIP_DIR + "pk07", "south");
    add_exit( TOWNSHIP_DIR + "pk05", "east");
    add_exit( TOWNSHIP_DIR + "pk04", "west");
    add_exit( TOWNSHIP_DIR + "pk01", "northwest");
    add_exit( TOWNSHIP_DIR + "pk03", "northeast");
    add_exit( TOWNSHIP_DIR + "pk06", "southwest");
    add_exit( TOWNSHIP_DIR + "pk08", "southeast");

}
 
init()
{
   ::init();
   
    add_action("drink_it",    "drink");
/*
    add_action("down_knoll",  "roll");
    add_action("throw_h20",   "splash");
    add_action("throw_h20",   "throw");
    add_action("swim_types",  "bellyflop");
    add_action("push_player", "push");
 */  
}
drink_it(string s)
{
   if(s=="water" || s=="water from fountain")
       {
           TP->catch_msg("You take a big drink of water. " +
                "You feel refreshed.\n");
           say(QCTNAME(TP)+" drinks some water from the fountain.\n");
           TP->drink_soft(130);
            return 1;
        }
    else
            NF("Drink what?\n");
}
 
 
/*
down_knoll(string str)
{
    if (str=="down knoll" || "down hill")
    { 
        switch(random(3))
        {     
            case 0 :
                TP->catch_msg("You roll down the northern side " +
                    "of the knoll.\n");
                move_living("north", "pk02", 0, 
                    " arrives rolling down the knoll.\n");
                say(QCTNAME(TP) + " rolled down the northern side " +
                    "of the knoll.\n");
                break;
            case 1 :
                TP->catch_msg("You roll down the southern side " +
                    "of the knoll.\n");
                move_living("south", "pk07", 0, 
                    " arrives rolling down the knoll.\n");
                say(QCTNAME(TP) + " rolled down the southern side " +
                    "of the knoll.\n");
                break;
            case 2 :
                TP->catch_msg("You roll down the eastern side " +
                    "of the knoll.\n");
                move_living("east", "pk05", 0, 
                    " arrives rolling down the knoll.\n");
                say(QCTNAME(TP) + " rolled down the eastern side " +
                    "of the knoll.\n");
                break;
            case 3 :
                TP->catch_msg("You roll down the western side " +
                    "of the knoll.\n");
                move_living("west", "pk04", 0, 
                    " arrives rolling down the knoll.\n");
                say(QCTNAME(TP) + " rolled down the western side " +
                    "of the knoll.\n");
                break;
            default :
                TP->catch_msg("Talk to a Emerald wizard. Something " +
                    "isn't working right.\n");
 
        }
    } 
}
*/
reset_room()
{
}

void
enter_inv(object ob, object from)
{
   start_room_tells();
   ::enter_inv(ob, from);
}
