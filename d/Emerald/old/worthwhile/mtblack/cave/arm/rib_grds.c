/* Spiked rib guards - Another classic from Tulix's armoury inc.           */
/* Coded 26/4/1993 */

inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

void
create_armour()
{
    set_name("guards");
    set_short("spiked metal rib guards");
    set_long(break_string(
        "These rib guards were developed to protect the unwary from the " +
        "likes of a certain balding arch-wizard, who mercilessly pokes " +
        "people in the ribs, usually without warning.\n",78));

    add_adj("rib");
    add_adj("spiked");
    add_adj("metal");

    set_ac(1); /* Just good enough to stop those poking fingers */

    set_am(({ 0, -1, 1}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 400);

}

string
query_recover()
{
    return "/d/Emerald/tulix/armour/rib_guards.c" + ":" +
        query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
