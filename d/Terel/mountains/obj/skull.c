/*
   torch.c

   A sample torch

    ... uh, actually it's a skull, but I'm going to assume that
        it was modified from some torch.c that the original
        coder found somewhere. Creation date: unknown. - Bleys

    Modified: 16 Sep 2003, by Bleys
        - Updated to use Terel defs
        - Changed description to make it more uniquely
            identifiable for the Halloween 2003 Scavenger Hunt.
            It also alludes to an older, perhaps extinct race
            now, and hints at some kind of purpose for the skull
            itself.


*/

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

#include <stdproperties.h>

create_object()
{
    set_name("skull");
    set_short("stained skull");
    set_adj(({"elven", "stained", "white"}));
    set_long("It's not immediately clear how long this skull " +
        "has been separated from its once living body. The " +
        "stains on the skull cover it in a mottled " +
        "pattern; they could be bloodstains, but they may " +
        "also be the stains of long existence and use. It is " +
        "about the right size and shape to be a human or " +
        "elven skull, but there is a curious oval depression " +
        "in the center of the skull that appears to be natural.\n"); 
}

