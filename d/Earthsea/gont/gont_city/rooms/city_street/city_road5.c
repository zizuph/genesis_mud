#pragma strict_types
#pragma no_clone

#include <stdproperties.h>

inherit "/std/room";

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Road crossings");
    set_long("The street becomes a bit brighter here,"+
        " as the distance between the houses gets wider. Here most"+
        " buildings are larger and with small gardens surrounded by"+
        " iron fences or low stone walls. A smaller road"+
        " joins from the south and looking that way you can see"+
        " many wooden structures built closely together. To the"+
        " west the cobbled street continues towards two"+
        " high towers. To the east you see a small wooden house"+
        " with a yard full of flowers. It is very crowded here, with people"+
        " constantly passing by on all sides.\n");
    add_item("street","The cobbled street leads between the"+
        " northeast and west, among larger stone buildings.\n");
    add_item("road","A smaller road meets this one here,"+
        " leading southwards towards many wooden houses.\n");
    add_item("houses","The houses are larger here, built"+
        " by the same cut black stone as the city wall. Most"+
        " of the houses are at least two storys high and"+
        " surrounded by small gardens inside iron fences or"+
        " low walls.\n");
    add_item("gardens","Peeking over the fences you see"+
        " small beautiful gardens inside, with grass lawns,"+
        " bushes and several different trees.\n");
    add_item(({"walls","fences"}),"Behind iron fences or"+
        " low stone walls you can see beautiful gardens"+
        " surrounding the larger houses.\n");
    add_item("people","There are more people dressed like"+
        " rich merchants here, most with the characteristic dark"+
        " skin of one born on the island of Gont.\n");
    add_exit("../yard", "east");
    add_exit("city_road4", "northeast");
    add_exit("city_road6", "west");
    add_exit("city_road11", "south");
}
