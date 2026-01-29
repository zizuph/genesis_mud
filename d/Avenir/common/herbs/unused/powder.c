// file name:    /d/Avenir/common/herbs/powder.c
// creator(s):   Casca 12/18/99
// last update:  
// purpose:      replaces the herbs destroyed by the wither_rot herb
// note:         
// bug(s):
// to-do:        Make it goes away shortly after dropped. 

#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

create_object()
{
    set_name(({"powder", "handful"}));
    set_pname("handfuls");
    set_short("handful of brown powder");
    set_pshort("handfuls of brown powder");
    add_adj(({"fine", "brown"}));
    set_long ("This is a small pile of what looks like decayed plant matter.\n");
    add_prop (OBJ_I_WEIGHT, 5);
    add_prop (OBJ_I_VOLUME, 8);
    add_prop (OBJ_I_VALUE, 0);
}
