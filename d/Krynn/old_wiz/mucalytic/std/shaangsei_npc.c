/* Standard npc for Sha'ang'sei. ~mucalytic/std/shaangsei_npc */

inherit "/std/monster";

#include "../sys/npc_defs.h"
#include "/sys/stdproperties.h"

void create_shaangsei_monster() { }

void set_weight(int kilos)
{
    add_prop(CONT_I_WEIGHT, kilos * KILOS);
}

void set_height(int feet, int inch)
{
    add_prop(CONT_I_HEIGHT, ftoi((itof(feet) * FEET) + (itof(inch) * INCHES)));
}

void create_monster()
{
    set_name("monster");
    set_long("An unconfigured Sha'ang'sei monster.\n");

    set_weight(65);		/* 65 kilogrammes.  */
    set_height(5, 9);		/* 5 feet 9 inches. */

    create_shaangsei_monster();
}
