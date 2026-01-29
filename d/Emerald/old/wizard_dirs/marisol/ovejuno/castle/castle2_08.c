/* Castle rooms second floor-The Sewing's room
 * Coded by Marisol (10/05/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_OV2;

void
create_castle_room()
{

    set_short("Sewing room");
    set_long("This is a sewing room. This room is simple in "+
        "design, very away from elven tastes. There are "+
        "not pictures or tapestries decorating the walls. The walls "+
        "are plain and painted white. A soft rug is spread in "+
        "the floor adding an elven touch to this place. Several "+
        "tables with sewing tools are scattered in the room. A small "+
        "fireplace is burning cheerfully in the wall opposite to "+
        "the entrance door. A high window, facing east, shares the same "+
        "wall as the fireplace. Torches are set strategically to "+
        "provide a nice, mellow light to all the room.\n");              


    add_item("room",
        "A very simple room. There is no one using it right now.\n");


    add_item("tables", 
        "Three wooden tables with their corresponding chairs are "+
        "placed under the light of the torches. Near the fireplace "+
        "there is a spinning wheel table. Different sewing tools are "+
        "available in each table.\n");


    add_item("tools",
        "All tables have these tools: scissors, measurring ribbons, "+
        "thimbles and needles. The spinning wheel has a distaff where "+
        "flax or wood is wound before being spuned.\n");


    add_item("spinning wheel",
        "This is a big wooden wheel that is used together with a "+
        "smaller wheel to spun thread from wool or flax. Right now, "+
        "wool is in the wheel to be worked as thread later.\n");


    add_item("distaff",
        "A distaff is a litte staff on which fibers like flax or wool "+
        "are wound before being spun into thread. Right now, wool "+
        "is wound in the distaff waiting to be spun into thread.\n");


    add_item("scissors",
        "They all are made of silver.\n");


    add_item("thimbles",
        "Small caps made of gold used to cover thumbs when sewing "+
        "clothes.\n");


    add_item("measuring ribbons",
        "These are long sturdy ribbons tied at intervals with knots "+
        "to measure pieces of fabric before they are cut among other "+
        "things.\n");


    add_item("rug",
        "A soft elven rug. The only elvish touch in this room. "+
        "The rug is a light beige very soothing for the tired eyes.\n");


    add_item("fireplace",
        "The stone fireplace is burning cheerily aromatic applewood "+
        "logs. The fireplace exudes a nice warm heat through out the "+
        "room, and the pleasing aroma of the applewood fills the air.\n");

    add_item("window",
        "This is a tall, ordinary window. The interior of the window "+
        "is clean but the outside is dirty. You can see leaves and "+
        "old grime covering the outside of the window, inhibiting the "+
        "entrance of light.\n");

    add_exit("castle2_04.c", "west");

    reset_room();

}                                             
