// -*-C++-*-
// file name:        /d/Avenir/common/dark/obj/sclub.c
// creator(s):       Casca, 11/28/99
// revisions:        
// purpose:          stone club for albus
// note:             
// bug(s):           
// to-do:            

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon ()
{
    set_name ("club");
    set_short ("stone club");
    add_adj("stone");
    set_long ("This is a primitive club, little more then a rock lashed "+
        "to a piece of wood.\n");
    set_wt (W_CLUB);
    set_dt (W_BLUDGEON);
    set_hit (10);
    set_pen (15);
    set_hands (W_ANYH);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 3000);
}
