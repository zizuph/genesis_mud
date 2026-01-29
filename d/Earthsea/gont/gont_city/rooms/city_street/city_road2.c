#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Dark street");
    set_long("The street is narrow and quite dark"+
        " here, continuing between tall stone buildings towering"+
        " up on both sides. This area seems to be mostly living"+
        " quarters, and you can see lines with hanging laundry"+
        " stretched between the upper floors of the houses."+
        " Behind a lower house to the north the high city wall"+
        " is visible. To the northeast the street leads to"+
        " the city gates, and to the west it continues between"+
        " the buildings. It is very crowded here, with people"+
        " passing by laughing and talking.\n");
    add_item(({"buildings","houses"}),"Tall stone buildings"+
        " line the narrow street on both sides, probably living"+
        " quarters judging by the many windows and lines of"+
        " laundry hanging between the upper floors of the houses.\n");
    add_item(({"lines","laundry"}),"Lines full of drying"+
        " laundry hang"+
        " across the street, between the upper storys of the"+
        " large stone houses.\n");
    add_item(({"wall","city wall"}),"Behind a house to the"+
        " north, you can see the city wall surrounding the great"+
        " Port of Gont.\n");
    add_item(({"street","road"}),"The street is narrow and"+
        " gloomy, shadowed by the tall buildings on both sides.\n");
    add_item("people","Travelers and citizens pass by in"+
        " a constant stream, moving in both directions. You hear"+
        " laughter and talk everywhere.\n");
    add_exit("city_road1", "northeast");
    add_exit("city_road4", "west");
}
