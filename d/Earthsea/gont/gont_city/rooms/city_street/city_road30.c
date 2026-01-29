#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Outside a high tower");
    set_long("The cobbled street leads on to the north"+
        " and southeast just below a high wall on the east"+
        " side. Looking over the"+
        " wall you can spot crowns of trees swaying back and"+
        " forth in the breeze and a large house with a roof"+
        " of green eroded copper. On the opposite side are"+
        " large two-story stone buildings, together with"+
        " a high tower elaborately decorated with masonry."+
        " To the southeast the stone buildings give"+
        " way for two-story wooden buildings packed closely"+
        " together as the road enters another part of the"+
        " city.\n");
    add_cmd_item("wall", "climb", "The wall is too high.\n");
    add_item(({"copper","roof"}),"Behind the wall you can"+
        " spot a large house to the east, with a green roof"+
        " of eroded copper.\n");
    add_item("street","The cobbled street leads north"+
        " and southeast between a high stone wall on the"+
        " east side and large stone buildings and a tower"+
        " on the other side.\n");
    add_item("tower","The tower rises up high above"+
        " the street to the west, elaborately decorated"+
        " with cut stone resembling dragons and ships."+
        " A narrow archway leads inside it. This must be"+
        " the home of a powerful organization.\n");
    add_item("archway","An archway of stone, formed in"+
        " the shape of a giant serpent curled together"+
        " leads inside the high tower.\n");
    add_item("masonry","Elaborately worked masonry"+
        " decorate the high tower, resembling dragons and"+
        " ships.\n");
    add_item("wall","The street follows a high wall on"+
        " the east side, which seems to be impossible to"+
        " climb since the stones it is built of are fitted"+
        " very closely together.\n");
    add_item("house","Behind the wall you can see the"+
        " upper storys of a large stone building with a"+
        " green eroded copper roof.\n");
    add_item(({"crowns","trees"}),"Crowns of trees are"+
        " visible behind the high wall, swaying back and"+
        " forth in a fresh breeze that you can't feel down"+
        " on the street. You hear the sound of leaves"+
        " rustling.\n");
    add_item("wooden buildings","To the southeast the"+
        " stone buildings give way for two-story wooden"+
        " buildings packed closely together. You have a"+
        " feeling that you will leave the richer parts of"+
        " Gont Port if you continue in that direction.\n");
    add_exit("city_road31", "north");
    add_exit("city_road29", "southeast");
}
