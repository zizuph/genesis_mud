#include <ss_types.h>
 
inherit "/d/Shire/common/lib/effect";
#include <stdproperties.h>
 
create_effect()
{
    set_name("_hen_blind_effect_");
    set_time((200+random(200)));
}
 
void
do_start_effect(object who)
{
    who->catch_msg("You see nothing but dark, blurry shapes!\n");
    who->add_prop(LIVE_I_SEE_INVIS,-1);
}
 
void
do_stop_effect(object who)
{
    who->add_prop(LIVE_I_SEE_INVIS,0);
    who->catch_msg("You are able to see again.\n");
}
