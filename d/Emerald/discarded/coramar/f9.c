#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


    set_long("   The thick cloud of mist hovers low near the ground here. "+
             "The path through the enormous forest is wide and seems to wind in curves moving from one tree "+
             "to the next, slowly making its way in one direction. The "+
             "ground is soft and moist, as are the trunks of the trees "+
             "and everything else in the wood. As the path curves around "+
             "a tree and begins wandering northwest, there is a large "+
             "boulder at the edge of the path covered in moss.\n\n");

    add_item( ({"boulder", "large boulder"}),
             "It is an ordinary boulder, with the exception of the amount "+
             "of moss covering it. You can barely see any of the gray or "+
             "black or white of the rock, it all seems hidden beneath the "+
             "massive tufts of moss.\n");

    add_item("moss",
             "The moss covering the rock is incredibly thick. It definately "+
             "gives you an indication that this mist and moisture must "+
             "remain here year-round, regardless of the seasons.\n");

    add_fexit(CORAMAR+"f13", "northwest", 0);
    add_fexit(CORAMAR+"f6", "east", 0);
}
