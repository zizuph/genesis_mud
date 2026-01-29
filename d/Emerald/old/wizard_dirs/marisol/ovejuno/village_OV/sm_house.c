/* The smith's house in the village of Re Albi
 * Coded by Marisol (05/26/98)
 * Modified by Marisol (08/04/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

inherit "/d/Emerald/std/room";
#include "/d/Emerald/sys/macros.h";
#include <stdproperties.h>
#include "defs.h"
#define SMDOOR DOORS + "sm_out"

object smdoor;


void
create_emerald_room()
{

    set_short("The smith's house");
    set_long("The house is empty right now. Possibly the smith's wife "+
        "is not too far away doing some errand. The walls of the "+
        "house are quite sturdy, made of a golden-hue oakwood. "+
        "A nice-looking stone fireplace is set at the left wall. "+
        "Comfortable chairs and a sofa face to the wide front windows. "+
        "Farther back in the house there is a kitchen with a "+
        "small stove and sink. To the right, a door open to another "+
        "room. The house is well-kept and clean as befit a craftman "+
        "and his wife.\n");

    add_item("fireplace",
        "Is made of square stones. Right now is not burning. "+
        "A stack of wooden logs lay ready to be set on fire. "+
        "Metal tongs and other paraphernalia to build a fire hangs "+
        "in the walls. A metal rod with three hanging metal hooks hold "+
        "some cooking pots.\n");

    add_item("walls",
        "The walls are made with a golden-hue oakwood that made the "+
        "inside of the house looks cheerful.\n");

    add_item(({"kitchen", "sink", "stove"}),
        "This is a nice kitchen, with a wooden counter to "+
        "cut vegetables and meat, a sink to soak dirty "+
        "dishes and a small stove to compliment the fireplace "+
        "cooking.\n");

    add_item(({"chairs", "sofa"}),
        "The chairs and sofa seem to be custom-made for the smith. "+
        "Comfortable down feather padding cover the chairs and sofa, "+
        "making it a pleasure to rest in it. From the chairs and sofa "+
        "you can see through the windows the village's road to the "+
        "smith shop.\n");

    add_item("windows",
        "Two wide glass windows face the village's path.\n");

    add_item("floor",
        "The floor is made with the same wood than the walls.\n");

    smdoor= clone_object(SMDOOR);
    smdoor->move(TO);

    add_exit("sm_annex.c", "in");

}                                                                   
