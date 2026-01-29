// file name: amulet.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:

/*  A small gem */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
        set_name("amulet");
        set_adj("water");
        set_long("This is the amulet of water. It is"
                +" finely carved from shimmering blue sapphire, and"
                +" depicts an ocean wave cresting. It shines with"
                +" the reflections of the light around it, and also with"
                +" the soft blue light of an inner power.\n");
        add_prop(OBJ_I_VALUE, 800);
}

