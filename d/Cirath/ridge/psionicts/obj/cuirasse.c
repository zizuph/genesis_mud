/* cuirasse.c: The gladiator guild item: Mylos, 18-8-93.
 *             Useless code (most of file) removed: Shiva, 1/15/95.
 *             Modified to be unremovable: Serpine: 4/25/95.
 *             Added callup of Overseer cuirasse: Serpine, 4/29/95.
 *             Removed old guru code: Decius, Sept 1, 1999.
 */

#pragma save_binary

inherit "/std/armour";

#include "defs.h"
#include <wa_types.h>

void create_armour()
{

    set_name(({ "cuirasse", CUIR_ID }));
    set_pname("cuirasses");
    set_short("iron cuirasse");
    set_pshort("iron cuirasses");
    add_adj("iron");
    set_long("Made of iron, and thus a rarity in Athas, the cuirasse "+
             "worn by Kalak's champions marks you as both his "+
             "slave and as the deadliest of warriors.\nUse <help "+
             "gladiator> to list your abilities.\n");
    set_default_armour(0, A_NECK);
   
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

void enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (!IS_MEMBER(env) && !IS_WIZ(env))
        remove_object();
    set_alarm(4.5, 0.0, "auto_wear");
}

void
auto_wear()
{
    wear_me();
}

/* report_kill is a legacy stub, to be removed when we know
   things won't explode.                                     */
void report_kill(int which) {}
