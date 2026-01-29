/* A sapphire of draining for use in the polymorph quest.
   Sold to players by Coiney, for a great price.

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
    set_name("sapphire");
    set_short("sapphire of draining");
    set_pshort("sapphires of draining");
    add_name(JEWEL_NAME);
    set_long("A large sparkling sapphire, but no ordinary one, " +
             "this is a sapphire of draining. Its use you ought " +
             "to know already.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 10000); /* roughly 6 plat */
    add_prop(OBJ_M_NO_GIVE, "Why give it away? It is so important to your " +
                            "quest!\n");
    add_prop(OBJ_M_NO_SELL, "Why sell it? It is so important to your " +
                            "quest!\n");
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

