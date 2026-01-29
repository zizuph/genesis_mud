/*
 * Back Porch of the Last Homely House
 * By Finwe, February 1998
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
    object board;
    set_extraline("This porch, known as the back or east porch, " +
        "stretches the width of the house. It offers shelter " +
        "from the elements and provides a cool place to sit and " +
        "relax. North and south of the porch is the garden.");
 
    add_item(({"flat stones", "stones"}),
        "The stones are smooth and interconnecting. They make up " +
        "the paths which run throughout the valley.\n");
    add_item(({"ground","down", "floor"}),
        "The floor is made from diagonal slats of cedar. The slats " +
        "are smooth and a reddish color\n");
    add_item(({"slats", "floor slats", "diagonal slats", "cedar slats"}),
        "The slats are made from smooth cedar plans. They are " +
        "smooth and a redish color.\n");
    add_item(({"last homely house", "house"}),
        "The house is large and constructed of stone with " +
        "ornately carved dark beams. The beams form a criss-cross " + 
        "and diamond patterns across the face of the house. " +
        "Gables extend from the roof. The roof is covered with " +
        "cedar shingles. Large windows cover the front of the house.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are weather worn but still " +
        "in good condition.\n");
    add_item("roof",
        "The roof is steeply pitched, allowing snow and " +
        "rain to roll off the house quickly and easily.\n");
    add_item("gables",
        "The extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item("garden",
        "The garden stretches north and south of here. " +
        "Some fruit trees, vegetables, and edible " +
        "plants can be seen growing there. A split-rail fence " +
        "surrounds the garden.\n"); 
    add_item(({"fence", "wooden fence", "split-rail fence"}),
        "The fence is constructed of timbers that have been " +
        "split in two. They are secured to posts that have been " +
        "sunk into the ground.\n");
    add_item(({"river", "river bruinen", "bruinen", "water"}),
        "This finger of the river Bruinen rushes west. The " +
        "water foams as it heads west out of the valley. " +
        "Its gentle sound fills the air with a quiet music.\n"); 
    add_item(({"porch"}),
        "The porch is runs the length of width of the house. It " +
        "is covered which makes the porch cool and airy here. " +
        "From here, you can see the valley pretty well " +
        "including the path that leads into the valley.\n");
     
    add_exit(VALLEY_DIR + "garden03", "north");
    add_exit(VALLEY_DIR + "garden04", "south");
    add_exit(VALLEY_DIR + "v_path11", "east");
    add_exit(VALLEY_DIR + "d_cor06",  "west");
}
 
 
string short_desc()
{
    return ("The back porch");
}
