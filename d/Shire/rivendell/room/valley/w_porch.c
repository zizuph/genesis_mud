/*
 * Front Porch of the Last Homely House
 * By Finwe, January 1998
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
    object board;
    set_extraline("It is said this house is one of the last " +
        "strengths and the easternmost true house of the Eldar in " +
        "Middle-earth. Elrond Half-elven, Master of the house " +
        "and surrounding valley, lives here protecting and " +
        "assisting travellers. The porch is long, covered, and " +
        "stretches the width of the house. It offers shelter " +
        "from the elements and provides a cool place to " +
        "relax.");

    board = clone_object("/d/Shire/std/board");
    board->set_board_name(VALLEY_DIR + "board");
    board->set_num_notes(30);         /* Number of notes         */
    board->set_silent(0);             /* Make noise when reading */
    board->set_show_lvl(0);           /* Full wizards or higher  */
    board->set_remove_str("You somehow failed.");
    board->set_use_gedit(0);          /* Don't use that marvellous editor */
    board->move(this_object());

    add_item(({"flat stones", "stones"}),
        "The stones are smooth and interconnecting. They make up " +
        "the paths which run throughout the valley.\n");
    add_item(({"elrond", "elrond half-elven", "Elrond Half-elven"}),
        "You don't see him anywhere near.\n");
    add_item(({"ground","down", "floor"}),
        "The floor is made from diagonal slats of cedar. The slats " +
        "are smooth and a reddish color\n");
    add_item(({"slats", "floor slats", "diagonal slats", "cedar slats"}),
        "The slats are made from smooth cedar planks. They are " +
        "smooth and a reddish color.\n");
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
        "They extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item("garden",
        "You see the edges of the garden on the south side of " +
        "the house. Some fruit trees, vegetables, and edible " +
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
    add_item(({"windows", "window"}),
        "Large windows cover the front of the wall.\n");
     
    add_exit(VALLEY_DIR + "d_cor03",  "east");
    add_exit(VALLEY_DIR + "v_path01", "west");
}
 
 
string short_desc()
{
    return ("The front porch of the Last Homely House");
}
