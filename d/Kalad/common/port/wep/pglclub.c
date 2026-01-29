inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("club");
    set_adj("ebony-hued");
    add_adj("spiked");
    set_long("A midnight-black club of great proportions. Its extremely "+
      "unyielding surface leads you to believe it is fashioned from some "+
      "type of obsidian. Amazingly enough there is not one chip in the "+
      "club's shiny surface.\n");
    set_hit(25);
    set_pen(21);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_IMPALE);
    add_prop(OBJ_I_VALUE,480);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,4000);
}
