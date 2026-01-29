/*
* Quiet street of Gont City
*
* Coded by Porta 971017.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("A silent street");
    set_long("This is a quiet"+
        " street of the Port of Gont,"+
        " with old stone houses surrounded by beautiful"+
        " lush gardens. Vines and ivy climb the black stone"+
        " walls almost completely embedding the buildings"+
        " in green vegetation. The leaves of the old oak trees"+
        " shadowing the wide grass lawns are rustling in the"+
        " breeze, but except for that everything is silent. To"+
        " the north is another large garden, and an even"+
        " larger building, while to the south a low wall"+
        " blocks the entrance to a park of some kind.\n");
    add_item("houses","These houses look very old and"+
        " are not as large as the other stone buildings"+
        " you have seen. Vines and ivy climb the dark"+
        " stone walls, embedding them in green vegetation.\n");
    add_item(({"vines","ivy"}),"Vines and ivy climb"+
        " the dark stone walls of the houses, embedding"+
        " them in lush vegetation.\n");
    add_item("vegetation","This part of the Port of Gont,"+
        " is very green with old oak trees and grass lawns"+
        " growing around the houses.\n");
    add_item("lawns","The grass lawns are well-tended and"+
        " very wide around each house.\n");
    add_item("wall","A low stone wall secludes the road"+
        " from what appears to be a park. You can see a"+
        " gravel path inside, winding through groves of oak"+
        " and birch trees.\n");
    add_item("larger buildin","This large building looks"+
        " almost like a palace, and must be the home for a"+
        " successful merchant or a Lord of Gont.\n");
    add_item(({"oaks","trees"}),"The oak trees are old"+
        " and shadows the grass lawn with their wide crowns."+
        " The only sound heard is created by the breeze"+
        " making the leaves rustle.\n");
    add_exit("city_road13", "southeast");
    add_exit("city_road8", "northeast");
}
