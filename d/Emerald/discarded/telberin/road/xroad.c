/*
 * Lakeside road that goes to the crossroad of Telberin
 * Based on the kroad files
 * By Finwe
 * January 1997
 */
 
#include "../default.h"
 
#include "/d/Emerald/sys/paths.h"
inherit LAKEROAD;
 
 
void
create_road()
{
    add_prop(IS_CARRIAGE_STOP, 1);
    set_short("A lake side road.\nA large sign stands here");
    set_long("   You are walking along the western edge of a " +
        "great lake. Many trees grow along the shore and " +
        "obscure your view of the water. They rise tall into " +
        "the sky creating a shaded canopy across the road here. " +
        "The road is well used by travellers heading north into " +
        "the mountains and south into Emerald. A great field " +
        "spreads out in all directions from the shore.\n"+
        "A large sign stands here.\n\n");

    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

   add_exit(LROAD + "road24",  "north");
   add_exit(LROAD + "road22", "south");
    add_exit(LROAD_DIR + "leroad01", "west");
    add_exit( THIS_DIR   + "bridge1", "east");
   set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}

string
read_sign()
{
    return "       +---------------------------------------------+\n" +
        "       |                                             |\n" +
        "       |               Mountains and                 |\n" +
        "       |                 Foothills                   |\n" +
        "       |                                             |\n" +
        "       |                     ^                       |\n" +
        "       |                     |                       |\n" +
        "       |                     |                       |\n" +
        "       |    Village   < ---- * ---->     The         |\n" +
        "       |    Of Leah          |        Great Lake     |\n" +
        "       |                     |                       |\n" +
        "       |                     v                       |\n" +
        "       |                                             |\n" +
        "       |                 Telan Road                  |\n" +
        "       |                                             |\n" +
        "       +---------------------------------------------+\n" +
        "                           |   |\n" +
        "                           |   |\n" +
        "                           |   |\n" +
        "                           |   |\n" +
        "                           |   |\n" +
        "                           |   |\n" +
        "                           |   |\n" +
        "                           |   |\n" +
        "          ^^^^^^^^^^^^^^^^^|^^^|^^^^^^^^^^^^^^^^^^^\n";
}
