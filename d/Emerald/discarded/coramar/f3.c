#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


    add_fexit(CORAMAR+"f4", "northwest", 0);
    add_fexit(CORAMAR+"f5", "northeast", 0);
    set_long("   The path here branches into three directions. Two "+
             "paths lead north of here, one to the northwest and the other "+
             "to the northeast. It is nearly impossible to see anything other "+
             "than the dull gray outlines of the trees along the path from "+
             "here. The mist provides a concealing blanket of gray moisture "+
             "which softens the edges of the trees and hides various gray "+
             "insects which enjoy the camouflage in the trees. A gentle "+
             "breeze blows calmly across the path from east to west. One "+
             "thing that appears very strange is that the thick fog is "+
             "slowly drifting from west to east, despite the cool wind. Other "+
             "than the sound of the wind whistling through the woods, it is "+
             "eerily quiet here.\n\n");

    add_fexit(CORAMAR+"f2", "south", 0);
}
