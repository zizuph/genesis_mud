/* 
 *Attack object, for use with burzum
 *Altrus, August 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define DID_ATTACK "_attacked_burzum"

void
create_object()
{
    set_name("_burzum_attack");
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
remove_attack_prop(object target)
{
	target->remove_prop(DID_ATTACK);
	TO->remove_object();
}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    set_alarm(300.0, 0.0, &remove_attack_prop(to));
}
