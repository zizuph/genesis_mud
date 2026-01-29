/* 
 *Stun, for bouncers
 *Altrus, August 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define IS_STUN "_stunned_by_burzum"

void
create_object()
{
    set_name("_burzum_stun");
    add_name("_invis_item");
    set_short("You shouldn't be able to see this.\n");
    set_long("If you can see this, 'bug _invis_item' so I know I totally goofed up on it.\n");
    
    //No peaky ;)
    set_no_show();

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME,  0);

}

void
un_stun(object target)
{
	target->catch_msg("You seem to have recovered your senses.\n");
	target->remove_prop(IS_STUN);
	target->remove_stun();
	TO->remove_object();
}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    to->add_prop(IS_STUN,1);
    to->add_stun();
    set_alarm(55.0, 0.0, &un_stun(to));
}
