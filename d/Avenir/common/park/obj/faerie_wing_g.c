// file name: faerie_wing.c
// creator(s): Ilyian
// last update:
// purpose: Wings of faerie.c, used as a leftover
// note:
// bug(s):
// to-do:

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
        set_name("wing");
        set_adj("golden");
        add_adj("tiny");
        set_long("This tiny wing is very much like an insect's, "
                +"except that it appears to be made of gold so "
                +"incrediably thin that it is translucent, and criss-"
                +"crossed with silvery veins.\n");

       add_prop (OBJ_I_WEIGHT, 2);
       add_prop (OBJ_I_VOLUME, 1);
       add_prop (OBJ_I_VALUE,  650);
}

