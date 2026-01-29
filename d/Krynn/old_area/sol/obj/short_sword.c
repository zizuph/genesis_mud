/*
 * Short sword coded by Lord Rastlin
 */

inherit "/std/weapon";

#include "/sys/formulas.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

nomask
create_weapon() 
{
    set_name("sword");
    set_adj("short");
    set_short("short sword");
    set_long("Ordinary short sword. But it stinks.\n");
    set_hit(16);
    set_pen(15);
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(16,15));
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1750);
}
