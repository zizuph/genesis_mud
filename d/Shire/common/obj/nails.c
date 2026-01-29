/*
 * Nails used to fix wagon wheel in quest.
 * -- Finwe January 2005
 */

#pragma save_binary
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

int nails_status = 0; // 0 not bent, 1 bent/useless

create_object()
{
    set_name(({"nails","_shire_nails"}));
    set_adj(({"small", "iron"}));
    set_short("set of small iron nails");
    set_pshort("sets of small iron nails");
    set_long("@@long_descr@@");

   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_I_VOLUME, 10);
}

string
long_descr()
{
    string long_desc = "This is a set of small iron nails. There are four " +
        "of them and they are about a finger's length. " ;
        
    if(nails_status == 0)
    {
        long_desc += "Each nail has a flat top where they are hammered to " +
        "fasten things together.\n";
    }
    else
    {
        long_desc += "The nails are bent and unusable.\n";
    }

    return long_desc;
}