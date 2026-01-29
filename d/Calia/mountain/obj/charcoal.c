/* An icicle, for use in the polymorph quest.
   Gets placed in the inventory of people who fight the polymorph beast
   and become victim of its ice attack.

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
    set_name("charcoal");
    add_name("fragment");
    add_name(CHARCOAL_NAME);
    set_short("fragment of charcoal");
    set_pshort("fragments of charcoal");
    set_long("A little fragment of charcoal produced when some of your " +
          "clothing burned in the demon's fire. It looks rather unusual, " +
          "perhaps magical.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GIVE, "This is not something that you can " +
                            "really give to anyone.\n");
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(MAGIC_AM_MAGIC, ({10, "enchantment"}));
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

