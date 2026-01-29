/*
 * Effect for bilberry herb
 * Thanks to palmer for doing it.
 * Finwe, March 2003
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>

inherit "/lib/herb_support.c";
inherit "/d/Shire/common/lib/effect";

#define HENSBANE_PROP   "_hensbane_ate_"
int c = 10+random(10);

create_effect()
{
    set_name("_hensbane_effect_");
    set_time((180+random(180)));
}
 
void
do_start_effect(object who)
{
    
    if(who->query_prop(HENSBANE_PROP))
    {
        who->catch_msg("You suddenly bend over in excruciating pain.\n");
        who->add_prop("magic_i_res_poison", 0);
        set_effect(HERB_POISONING, "all", c);
    }
    else
    {   
        who->add_prop(HENSBANE_PROP,1);
        who->catch_msg("Your blood begins to warm and run faster.\n");
        who->add_prop("magic_i_res_poison", c);
    }

}
 
void
do_stop_effect(object who)
{
    who->remove_prop("magic_i_res_poison", c);
    who->catch_msg("Your blood begins to cool down a return to normal.\n");
    who->remove_prop(HENSBANE_PROP);
}
