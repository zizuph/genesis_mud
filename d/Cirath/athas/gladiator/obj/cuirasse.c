#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "defs.h"
#include <wa_types.h>

void
create_object()
{
    set_name(({ "cuirasse", CUIR_ID }));
    set_pname("cuirasses");

    set_slots(A_NECK);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, "Ouch! It's too painful to drop.\n");
    add_prop(OBJ_I_WEIGHT, 670);
    add_prop(OBJ_I_VOLUME, 20); 
}

int
query_recover()
{
    return 0;
}

void
configure_cuirasse(object who)
{
    int position = (who ? POSITION(who) : POS_NONE);

    remove_adj(query_adj());

    switch(position)
    {
        case POS_WIZ:
        case POS_HIGH:
            set_short("gold cuirasse");
            set_pshort("gold cuirasses");
            set_adj("gold");
            set_long("Made of gold, a metal so rare on Athas that only Sorceror " +
                "Kings and the heads of dynastic merchant houses can have " +
                "much, the cuirasse marks you as the High Overseer of " +
                "the Gladiators of Athas.\nYou may use 'help gladiator' " +
                "or 'help overseer' for more information.\n");
        break;
        case POS_NONE:
            set_short("iron cuirasse");
            set_pshort("iron cuirasses");
            add_adj("iron");
            set_long("Made of iron, and thus a rarity in Athas, the cuirasse " +
                "worn by Kalak's champions marks you as both his " +
                "slave and as the deadliest of warriors.\nUse <help " +
                "gladiator> to list your abilities.\n");
        break;
        default:
            set_short("silver cuirasse");
            set_pshort("silver cuirasses");
            set_adj("silver");
            set_long("Made of silver, a rare and expensive metal in Athas, the " +
               "cuirasse shows you to be a Lesser Overseer of the " +
               "Gladiators of Athas.\nYou may use 'help gladiator' " +
               "or 'help overseer' for more information.\n");
        break;
    }
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if(!IS_MEMBER(env) && !IS_WIZ(env))
        remove_object();

    configure_cuirasse(env);
    set_alarm(4.5, 0.0, wear_me);
}

public void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
