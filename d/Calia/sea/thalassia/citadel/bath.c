
/*  In the Bath Chamber

    coder(s):   Jaacar

    history:    21. 7.03    room coded                      Jaacar

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
    set_short("In the bath chamber");
    set_long("You are floating in one of the bathing chambers "+
        "in the Royal Palace of Thalassia. It is good to get "+
        "air into your lungs once again. The water you are "+
        "floating in is certainly warmer than any of the water "+
        "you were swimming through to reach this place. Right "+
        "beside you there is a dish floating in the water that "+
        "contains soap. Here you may <bathe> if you wish, or "+
        "you can simply leave back <out> into the bathing chamber.\n");

    add_item(({"soap","dish"}),"There is soap sitting in a dish "+
        "that is floating beside you. If you were to bathe yourself, "+
        "you could use this soap.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);

    add_exit(THALC+"palace_2_8","out", 0, 1);
}

int
do_bathe(string str)
{
    if (str && str != "myself")
    {
        NF("You cannot bathe anyone but yourself. <bathe myself>\n");
        return 0;
    }

    write("You remove all of your clothing and belongings and place "+
        "them on a small plastic rack that is floating conveniently "+
        "right beside you. You reach for the soap and lather "+
        "your naked body with the sweet smelling soap. You lie back "+
        "and float on your back in the water. It feels nice to relax "+
        "for a change. You are so relaxed that you almost drift off "+
        "to sleep. After a while you casually rinse the soap from your "+
        "body, gather up your clothing, get dressed once again and "+
        "finally take all of your belongings from the rack.\n");
    say(QCTNAME(TP)+" removes all of "+HIS(TP)+" clothing and belongings "+
        "and places them on a small plastic rack that is conveniently "+
        "floating next to "+HIM(TP)+". "+capitalize(HE(TP))+" reaches for the "+
        "soap and lathers up "+HIS(TP)+" naked body with the sweet smelling "+
        "soap. "+capitalize(HE(TP))+" lies back and floats on "+HIS(TP)+" back "+
        "in the water, almost drifting off to sleep by the looks of "+
        "things. After a while, "+HE(TP)+" casually rinses off all of the "+
        "soap from "+HIS(TP)+" body, gathers up "+HIS(TP)+" clothing, gets "+
        "dressed once again, and finally removes all of "+HIS(TP)+
        " belongings from the rack.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("do_bathe","bathe");
}

