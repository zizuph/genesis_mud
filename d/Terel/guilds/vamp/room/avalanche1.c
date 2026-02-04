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

void
create_room()
{
    set_short("avalanche");
    set_long("You are in the middle of an avalanche. It looks like a gigantic "+
        "claw raked the mountainside, causing it to spill shale like "+
        "a gutted animal. "+
        "The air is thin and a chilling wind carries a fine "+
        "icy mist that obscures visability. Powdery snow and frost "+
        "covers the ground in a thin layer. The path you are picking "+
        "though the loose shale of the avalanche is treacherous at best.\n");

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
    add_item(({"shale", "loose rocks", "avalanche", "mountainside"}), 
        "The shale has formed from pieces of the mountain that have "+
        "fallen off and down its side, deteriorating. It makes your "+
        "footing very difficult, and creates concerns about "+
        "causing a new avalanche.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
    add_exit("outside", "down");
    add_exit("avalanche2", "northwest");


}


