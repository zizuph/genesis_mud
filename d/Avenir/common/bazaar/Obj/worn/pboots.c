/* These boots are normal save for one thing:
 * Worn by anything not a troloby (which is HUGE)
 * The wearer will suffer a loss of 20 DEX
 * 
 * Ckrik 1/9/2023
 * Removed the interactive check. If the boots are put into
 * a backpack while worn, the interactive check fails and
 * the DEX is never restored.
 */
inherit "/std/armour";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

int dex_reduction = 0;

void
create_armour ()
{
    set_name("boots");
    set_short("pair of studded black leather boots");
    add_name(({"boots", "armour"}));
    add_adj(({"black", "leather"}));
    set_long("These boots are knee-high on the troloby guards for "+
        "whom they were crafted. They are made of heavy hide stud"+
        "ded with steel, and have a strong musky odor to them.\n");
    set_af(this_object());
    set_ac(25);
    set_at(A_FEET);
}

mixed wear()
{     
    object tp = this_player();
    dex_reduction = 0;

    if (!interactive(environment(this_object())))
        return 0;

    if (tp->query_race() == "troloby" ||
        tp->query_race() == "goblin")
        return 0; 
   
    dex_reduction = 20;
    tp->set_stat_extra(SS_DEX, 
        tp->query_stat_extra(SS_DEX) - dex_reduction);

    write("You feel a bit awkward, wearing such large boots.\n");
    return 1;
}

mixed
remove(object ob)
{
    object tp = query_worn();
    if (tp->query_race() == "troloby" ||
        tp->query_race() == "goblin")
        return 0; 

    tp->set_stat_extra(SS_DEX, 
        tp->query_stat_extra(SS_DEX) + dex_reduction);
    dex_reduction = 0;

    write("You feel considerably less awkward, now that you've "+
        "taken off such large boots.\n");
    return 1;
}
