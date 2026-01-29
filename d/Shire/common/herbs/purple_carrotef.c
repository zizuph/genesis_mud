#include <ss_types.h>
 
inherit "/d/Shire/common/lib/effect";
#include <stdproperties.h>
 
create_effect()
{
    set_name("_grapel_effect_");
    set_time((200+random(200)));
}
 
int
query_vision()
{
    return this_player()->query_prop("_live_i_see_dark");
}

void
do_start_effect(object who)
{  
    int c;
    
    c = query_vision();
    
    if (c <= 100)
        c += 10;
    
    who->catch_msg("Your eyes begin to tingle.\n");
    who->add_prop("_live_i_see_dark", c);
}
 
void
do_stop_effect(object who)
{
    int c;
    
    c = query_vision();
    c -= 10;
    if (c < 0)
        c = 0;
    
    who->add_prop("_live_i_see_dark", c);
    who->catch_msg("You blink your eyes rapidly.\n");
}
