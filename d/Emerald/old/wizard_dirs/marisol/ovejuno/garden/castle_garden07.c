/*Manor's Garden VII
*Coded by Marisol (9/3/97)
*Copyright (c) Marisol Ramos 1997
*/

#include "defs.h"
#include "/d/Emerald/sys/macros.h"
#define SCARABAE CASTLE_GARDEN_NPC + "g_scarabae"
#define SCARABAE2 CASTLE_GARDEN_NPC + "g_scarabae"
inherit CASTLE_GARDEN;


object scarabae;
object scarabae2;


void reset_room()
{
if (!objectp(scarabae))
{
 scarabae= clone_object(SCARABAE);
 scarabae->move(TO);
 scarabae->command("emote crawls in.");
}

if(!objectp(scarabae2))
{
 scarabae2= clone_object(SCARABAE2);
 scarabae2->move(TO);
 scarabae2->command("emote crawls in.");
}

}

create_emerald_garden()
{

    set_long("An old ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendrons surrounds the garden, making it "+
        "impossible to see outside the enclosure. There is an "+
        "intersection here. The west path goes to the center of the "+
        "garden and the north one continues the rest of the enclosure. "+
        "The path is overgrown with weeds and tall grass. On both "+
        "sides of the path, a blanket of blue-red plants with "+
        "pink-white flowers cover the ground, intermingled with "+
        "common weeds and grass. The air is scented "+
        "with a delicate sweet aroma.\n");

    add_item("plants",
        "The ground is covered with many strange plants with "+
        "blue-red leaves and pink-white flowers. Weeds dot with yellow "+
        "grow together with these plants, struggling for "+
        "space in the ground.\n");

    add_item(({"pink-white flowers", "red-blue plants"}),
        "This is a blue-red Begonia from the highest mountains of "+
        "Emerald. They are found in cold climates and wet terrains. "+
        "This plant has prostrate, red stems, which grow up from small "+
        "tubers. It leaves-stalk and back of the leaves are red, while "+
        "the front of the leaves have a bluish tint on them. The flowers "+
        "are pinkish-white and are delicately scented. Some of the "+
        "petals have fallen onto the long and wide leaves. They rot "+
        "slowly, leaving a delicate sweet aroma in the air.\n");

    add_exit("castle_garden10", "west");
    add_exit("castle_garden12", "north");
    add_exit("castle_garden05", "south");

reset_room();
}
