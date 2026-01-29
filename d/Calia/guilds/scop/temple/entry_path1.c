
/*
 * entry_path1.c
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
 
#define CONNECTING_ROOM "/d/Calia/argos/swterr/rooms/r33"

void 
create_room() 
{
    set_short("A path through a dark forest");
    set_long("You are at the end of a path through a dark forest. "+
        "Towering black pines populate the woods, their long needles look "+
        "sharp enough to draw blood. The branches of the pines grow so "+
        "thickly all around that the only way out seems to be along the path "+
        "to the southwest.\n");
 
    add_item(({"forest","trees","woods"}),"Towering pine trees, their bark "+
        "as black as night and their black needles sharp enough to cut.\n");
    add_item("branches","They grow thickly from the crowded trees, their "+
        "spiny needles warning of any contact. Some branches seem to have "+
        "been broken through to the northeast, as if some creatures have "+
        "crawled through them several times.\n");
 
    add_item("sounds","You don't see anything moving...you wonder what is "+
        "making them.\n");
    add_item("sun","You can't see it, though you can tell it is daytime.\n");
    add_item(({"cones","pine cones"}),"You see some hanging high from "+
        "the branches of the black pines.\n");
    add_item("path","It looks rather old, and leads to the southwest.\n");
 
    add_exit(SPIRIT_TEMPLE+"entry_path2","southwest",0,1);
}
 
int 
do_crawl(string str) 
{
    if (!str)
        return 0;
    if (!parse_command(str, ({}), "[through] [the] 'branches'"))
    { 
        notify_fail("Crawl where? Through the branches? <crawl through "+
            "branches>\n"); 
        return 0; 
    }

    write("You crawl through the branches, sharp needles scratching your "+
        "hands and face painfully.\n");
    set_dircmd("through branches");
    TP->move_living("into the branches",CONNECTING_ROOM);
    return 1;
}
 
void 
init() 
{
   ::init();
   add_action(do_crawl,"crawl");
}
