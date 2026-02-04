//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    Lilith Jan 2022: exit direction change
// note: 
// bug(s):
// to-do:

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <stdproperties.h>
#include <macros.h>

create_room()
{
    set_short("avalanche");
    set_long(
        "You are near the top of an avalanche. The mountain has "+
        "spilled inky darkness from its side like a wounded "+
        "animal. The footing on the rock and shale is precarious, "+
        "with small pieces skittering down with every step. "+
        "The air is very thin and a chilling wind carries a fine "+
        "icy mist that obscures visability of all but your "+
        "immediate surroundings. Powdery snow and frost "+
        "covers the ground in a thin layer. Below you, part of the "+
        "mountain has fallen away as an avalanche that nearly buried "+
        "the house far below.\n");


    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "Far below are ancient oak trees.\n");


    add_item(({"path", "zig-zag path"}),
        "Strewn with loose rocks, it winds upwards toward the top "+
        "of the mountain, and down, into oaks trees.\n");

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "In the distance you can see some trees.\n");
    add_item("ground", 
	"The ground is hard with frost and covered in snow.\n");
    add_item(({"ravine", "gash"}),
        "Your eyes cannot penetrate the darkness which leads south "+
        "into the mountain.\n");
    add_item(({"house", "ruins", "mansion", "building"}),
        "These are the remains of a once-great house, long ago "+
        "abandoned and now crumbling to ruins.\n");   
    add_item(({"vineyard", "vines"}),
        "The vines were long ago petrified into the grotesquely "+
        "tortured shapes you see now.\n");
    add_item(({"shale", "loose rocks"}), 
        "The shale has formed from pieces of the mountain that have "+
        "fallen off and down its side, deteriorating. It makes your "+
        "footing very difficult, and creates concerns about "+
        "causing a new avalanche.\n");
    add_item("avalanche", "Its composed of lose shale that crumbled "+
        "to bits when the mountainside fell away.\n");    
    add_item(({"crack"}), "It is big enough for you to enter.\n");
    add_prop(ROOM_I_INSIDE, 0);
    add_exit("avalanche1", "southeast");
    add_exit("avalanche3", "northwest");

}


