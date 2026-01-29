
/*
 * entry_path2.c
 *
 * Entry path leading between the road from Argos and
 * the Temple for the Spirit Circle of Psuchae.
 *
 * Copyright (C): Jaacar (Mike Phipps), August 2nd, 2003
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
 
void 
create_room() 
{
    set_short("A path through a dark forest");
    set_long("You are walking along a path through a dark forest. "+
        "Towering black pines populate the woods, their long needles look "+
        "sharp enough to draw blood. The branches of the pines grow so "+
        "thickly all around that the only way out seems to be along the path "+
        "to the northeast or the southwest.\n");
 
    add_item(({"forest","trees","woods"}),"Towering pine trees, their bark "+
        "as black as night and their black needles sharp enough to cut.\n");
    add_item("branches","They grow thickly from the crowded trees, their "+
        "spiny needles warning of any contact.\n");
 
    add_item("sounds","You don't see anything moving...you wonder what is "+
        "making them.\n");
    add_item("sun","You can't see it, though you can tell it is daytime.\n");
    add_item(({"cones","pine cones"}),"You see some hanging high from "+
        "the branches of the black pines.\n");
    add_item("path","It looks rather old, and leads from the northeast "+
        "to the southwest.\n");
 
    add_exit(SPIRIT_TEMPLE+"entry_path1","northeast",0,1);
    add_exit(SPIRIT_TEMPLE+"entry_path3","southwest",0,1);
}
 
