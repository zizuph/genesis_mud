//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    Lilith Jan 2022: reopened avalanche exit and updated
//                   this room to lead a location closer to where this 
//                   area is located.
// note: 
// bug(s):
// to-do:

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    set_short("hanging on the side of a dark mountain");
    set_long(
        "The air is very thin. A harsh wind buffets you against "+
        "the vertical cliff wall.\n\nYour feet rest on a tiny ledge. "+
        "If it crumbles, you will surely die.\n\n"+
        "Below you, part of the mountain has fallen away as an "+
        "avalanche that nearly buried a house in the valley far "+
        "below.\nThere is a crack in the face of the cliff. "+
        "It looks like it may be the only way to safety.\n");

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "Far below are ancient oak trees.\n");
    add_item(({"path", "zig-zag path"}),
        "Strewn with loose rocks, it winds upwards toward the top "+
        "of the mountain, and down, into oaks trees.\n");
    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "In the distance you can see some trees.\n");
    add_item("ground", 
	"The ground is hard with frost and covered in snow.\n");
    add_item(({"house", "ruins", "mansion", "building"}),
        "These are the remains of a once-great house, long ago "+
        "abandoned and now crumbling to ruins.\n");    
    add_item(({"vineyard", "vines"}),
        "The vines were long ago petrified into the grotesquely "+
        "tortured shapes you see now.\n");
    add_item(({"shale", "loose rocks", "path"}), 
        "The shale has formed from pieces of the mountain that have "+
        "fallen off and down its side, deteriorating.\n");
    add_item("avalanche", "Its composed of lose shale that crumbled "+
        "to bits when the mountainside fell away.\n");    
    add_item(({"crack"}), "It is big enough for you to enter.\n");
    add_prop(ROOM_I_INSIDE, 0);

    add_exit("/d/Terel/mountains/goblincave/cave06", "crack");
    add_exit("avalanche4", "down");


}


