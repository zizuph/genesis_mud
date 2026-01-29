/* A magical sword. ~mucalytic/hills/weapons/blue_sword */

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_weapon()
{
    set_name("short-sword");
    add_name("sword");
    set_pname("short swords");
    add_pname("swords");
    set_adj("glowing");
    add_adj("blue");
    set_long("This sword looks like any other short sword but for the fact "+
        "that blue flame plays along its blade. This sword is obviously "+
        "magical and is a very lucky find indeed.\n");

    set_hit(20 + random(11));
    set_pen(30 + random(6));

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2500); // 2.5 kilos.
}
