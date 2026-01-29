/* Street in Gont Port. Coded by Porta 971014. */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

private object merchant;

public void
reset_room()
{
    if(!objectp(merchant))
    {
        merchant = clone_object("/d/Earthsea/gont/gont_city/liv/merchant");
        merchant->move(this_object());
        merchant->command("emote comes strolling in.");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Street between large stone buildings");
    set_long("The narrow street continues toward two"+
        " high towers, rising up above the rest of the"+
        " buildings just a short distance to the southwest."+
        " This seems to be a very rich neighborhood with"+
        " large stone buildings surrounded by beautiful"+
        " well-tended gardens. Two birch trees are planted"+
        " at the side of the street, shadowing the area"+
        " with their long, leafed branches, rustling in"+
        " the breeze. It is not as crowded here, and most of"+
        " the people you meet are dressed like rich merchants"+
        " or noblemen.\n");
    add_item("street","The cobbled street is much cleaner"+
        " and brighter here where the space between the buildings"+
        " around is wider. It continues towards the towers to"+
        " the southwest, and eastwards to a small crossing of"+
        " roads.\n");
    add_item("towers","Looking southwest you can clearly"+
        " see two tall black towers, rising up above the rest"+
        " of the buildings. Following the road would probably"+
        " take you to them.\n");
    add_item("trees","There are two birch trees planted"+
        " on the street here, adding a pleasant athmosphere to"+
        " the otherwise fairly sterile stone structures.\n");
    add_item("people","The people you meet are mostly dressed"+
        " like rich merchants or noblemen, followed by guards and"+
        " servants. Most are dark-skinned originating from this"+
        " island, but many others are foreigners in exotic clothes"+
        " here to strike deals.\n");
    add_item("buildings","The buildings are very large here,"+
        " probably home to merchants and mostly imbedded in"+
        " green foliage climbing up the walls. Almost all houses"+
        " have either an iron fence or a low wall secluding their"+
        " gardens from neighbors and the street.\n");
    add_item("gardens","The gardens look very green and"+
        " well-tended, with all kinds of trees and bushes growing"+
        " between wide grassy lawns.\n");
    add_exit("city_road5", "east");
    add_exit("city_road7", "southwest");
    reset_room();
}
