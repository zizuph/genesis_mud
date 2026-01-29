
/*
 * entry_path4.c
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
    set_short("Outside of some ruins");
    set_long("You are at the end of a path through a dark forest. "+
        "Towering black pines populate the woods, their long needles look "+
        "sharp enough to draw blood. The branches of the pines grow so "+
        "thickly all around that the only way out seems to be along the path "+
        "to the northeast. Standing before you are the ruins of a what used "+
        "to be a large temple. Destroyed stairs lead up to the "+
        "blocked entryway to the north.\n"); 
 
     add_item(({"ruins","ruin","temple","large temple"}),"It is the ruins "+
         "of a large temple made of grey stones. The now blocked entryway "+
         "lies to the north.\n");
     add_item(({"stone","stones","grey stone","grey stones"}),"The grey "+
         "stones make up the outer wall of the large temple.\n");
     add_item(({"entryway","blocked entryway"}),"The entryway to the temple "+
         "lies up some destroyed stairs to the north and is now blocked.\n");
     add_item(({"stairs","destroyed stairs"}),"They are destroyed grey stone "+
         "stairs leading up to the blocked entryway of the ruined temple.\n");
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
        "to the here.\n");
 
    add_exit(SPIRIT_TEMPLE+"entry_path3","northeast",0,1);
}
 
