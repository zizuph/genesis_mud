inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    set_adj("small");
    add_adj("halfling");
    set_long("A small sword crafted for use by halflings and their ilk.\n");
    set_hit(20);
    set_pen(20);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_wf(TO);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2000);
}
mixed
wield(object what)
{
    if(TP->query_race_name() == "halfling")
    {
	write("You easily wield the small halfling sword.\n");
	return 0;
    }
    return "You're too big to wield the small halfling sword!\n";
}
mixed
unwield(object what)
{
    return 0;
}
