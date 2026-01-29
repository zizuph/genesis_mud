/* 
 * Outer road of Telberin
 * By Finwe, January 1997
 */
 
#include "default.h"
 
inherit AVENUE;
 
 
void
create_avenue()
{
    add_my_desc("\n" +
        "A statue has been erected here.\n\n");
 
    add_item( ({"statue"}),
        "Here stands a statue of an elven hero, proud " +
        "and sure of himself. It has been carved from white " +
        "marble and has features that look lifelike. It has " +
        "piercing blue eyes that seem to bore into your very soul.\n");

/*
    add_item(({"sign", "street sign"}),
        "Maybe you should read the sign.\n");
    add_cmd_item( ({"sign", "street sign"}), "read", "@@read_sign@@");
*/

    add_exit(AVENUE_DIR + "ave05", "east");
    add_exit(AVENUE_DIR + "ave03", "southwest");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}

/*
string
read_sign()
{
     return "\n\n" +
        "       ---------------------------     \n" +
        "       |                         |     \n" +
        "       |      East - Willow Way  |     \n" +
        "       | Southwest - Lilac Way   |     \n" +
        "       |                         |     \n" +
        "       ---------------------------     \n" +                               
        "                  |    |               \n" +
        "                  |    |               \n" +
        "                  |    |               \n" +
        "                  |    |               \n" +
        "                  |    |               \n" +
        "                  |    |               \n" +
        "           ^^^^^^^|^^^^|^^^^^^^        \n\n"; 
}
*/
