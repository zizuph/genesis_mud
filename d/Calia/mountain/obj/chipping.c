/* Chipping from an obelisk, for use in the polymorph quest.

   Coded by Maniac 29/8/95

*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "obj.h"
#include POLYMORPH_QUEST


void
create_object()
{
    set_name("chipping");
    set_adj(({"magical", "stone"}));
    add_name(CHIPPING_NAME);
    set_long("A chipping of stone from one of the magical obelisks " +
             "in Calia.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(MAGIC_AM_MAGIC, ({60, "enchantment"}));
}


void
lose_msg(object tp)
{
    if (interactive(tp)) 
        tp->catch_msg("Oops, looks like you lost sight of the " + 
                       short() + ". Now it's gone!\n"); 
    remove_object();
}


void
leave_env(object old, object dest)
{
    if (!living(dest)) 
        set_alarmv(1.0, 0.0, "lose_msg", ({old}));

    ::leave_env(old, dest);
}

