/* Ashlar, 13 Jul 97 - this is a collar that a slave is wearing.
   clone it to the same room as the slave. */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit "/std/receptacle";

void
create_receptacle()
{
    set_name("collar");
    set_adj("iron");

    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET, "The collar is fastened to the wall by a chain, " +
    "it is beyond you to pull it out.\n");
    
    set_long("The iron collar is made of a thick band of iron, " +
        "fastened to a chain. A lock keeps the collar in place.\n");

    set_key(SLAVE_KEY);
    /* It is unpickable because making it easily pickable would
       cheat thieves out of lots of quest xp */
    set_no_pick();

    set_cf(TO);

}

int
handle()
{
    object k;
    k = P("kordhek",E(TO));
    if (k && CAN_SEE(k,TP) && CAN_SEE_IN_ROOM(k))
    {
        TP->catch_msg(QCTNAME(k) + " stops you from reaching the collar.\n");
        return 3;
    }
    else
        return 0;
}

int
handleunlock()
{
    object k;
    k = P("kordhek",E(TO));
    if (k && CAN_SEE(k,TP) && CAN_SEE_IN_ROOM(k))
    {
        TP->catch_msg(QCTNAME(k) + " stops you from reaching the collar.\n");
        return 3;
    }
    k = P("_neraka_slave_key_",TP);
    if (!objectp(k))
    {
        TP->catch_msg("The key does not seem to fit.\n");
        return 3;
    }
    TP->catch_msg("As you turn the key, it breaks in the lock! Luckily you " +
    "managed to unlock the collar first.\n");
    k->remove_object();
    return 0;
}

int
handleopen()
{
    object k;
    k = P("kordhek",E(TO));
    if (k && CAN_SEE(k,TP) && CAN_SEE_IN_ROOM(k))
    {
        TP->catch_msg(QCTNAME(k) + " stops you from reaching the collar.\n");
        return 3;
    }
    k = P("neraka_slave",E(TO));
    if (objectp(k))
        k->freed_by(TP);
    return 0;
}

varargs int open(object ob)
{
    return handleopen();
}

varargs int close(object ob)
{
    return handle();
}

varargs int lock(object ob)
{
    return handle();
}

varargs int unlock(object ob)
{
    return handleunlock();
}

varargs int pick(object ob)
{
    return handle();
}
