
#include <ss_types.h>
 
inherit "/d/Shire/common/lib/effect";
#include <stdproperties.h>
 
create_effect()
{
    set_name("_bundle_stun_effect_");

    set_time(2);
}


void
do_start_effect(object who)
{
    who->add_prop("_unwrapping_bundle_", 1);

}
 
void
do_stop_effect(object who)
{
    who->add_prop("_unwrapping_bundle_", 0);
}
