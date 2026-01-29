/*
 * Effect for glimmer herb
 * Palmer - April 1, 2004
 */

#include <ss_types.h>
 
inherit "/d/Shire/common/lib/effect";
#include <stdproperties.h>
 
create_effect()
{
    set_name("_glimmer_effect_");
    set_time((1200 + ( ( random(3) ) * 60 ) ));
}

int
query_vision()
{
    return this_player()->query_prop("_live_i_see_invis");
}
 
void
do_start_effect(object who)
{
    int c;
    
    c = query_vision();
    // Make sure this is less than 100 or you can see wizzes ;)
    if (c <= 99)
        c += 5;
    
    who->catch_msg("Your eyes burn a little bit.\n");
    /*
    if (c <= 99)
         who->add_prop("_live_i_see_invis", c);
     */
}
 
void
do_stop_effect(object who)
{
    int c;

    c = who->query_prop("_live_i_see_invis");
    c -= 5;
    if (c < 0)
        c = 0;
    
    who->add_prop("_live_i_see_invis", c);
    if (c == 0)
    	who->catch_msg("The burning in your eyes subsides.\n");
    else
    	who->catch_msg("The burning in your eyes subsides a bit.\n");
}
