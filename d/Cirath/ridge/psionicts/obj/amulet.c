/*
* Created by: Luther
* Date: Oct 2001
*
* File: /d/Cirath/rige/psionicts/obj/amulet.c
* Comments: Guild item, copied from glad cuirasse
*/
    
#pragma save_binary

inherit "/std/armour";

#include "defs.h"
#include <wa_types.h>

void create_armour()
{

    set_name(({ "amulet", AMUL_ID }));
    set_pname("amulets");
    set_short("iron amulet");
    set_pshort("iron amulets");
    add_adj("iron");
    set_long("Made of iron, and thus a rarity in Athas, the amulet "+
             "worn by Kalak's servants marks you as both his "+
             "slave and as a master of the mind.\nUse <help "+
             "psion> to list your abilities.\n");
    set_default_armour(0, A_HEAD);
   
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
