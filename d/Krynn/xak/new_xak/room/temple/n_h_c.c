/* 
 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;
inherit CHAPEL;

public void
create_xak_room()
{    
    set_short("In the North Holy Circle");
    set_long("You are standing in an large circular chamber that stretches " +
	     "some forty feet in diameter. The chamber walls are made of " +
             "smooth white stone that soars up sixty feet to a domed " +
	     "ceiling. The chamber is given an extra appearance of size " +
	     "by its emptiness. Wonderous frescoes line the walls showing " +
	     "acts of miraculous healing filling you with awe. An exit " +
	     "leads south back into the main chamber.\n");

    add_item(({"frescoe", "frescoes", "fresco"}), "The frescoes show sight " +
	     "of miraculous healing. The lame walking, the blind seeing, " +
	     "the deaf hearing. In each case the afflicted is surrounded " +
	     "in a glowing blue nimbus which seems to heal the person. " +
	     "You realise that that is the power this goddesses priests " +
	     "and priestesses must have once possessed. How sad that so " +
	     "many have turned their eyes away from worshipping her.\n");

    add_exit(TEMPLE + "chamber1", "south");
}

public void
init()
{
    init_chapel();
    ::init();
}




