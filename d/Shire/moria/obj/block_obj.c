/* 
 *Psuedo stun...keeps players from reentering Burzum's room for a short time
 *Altrus, August 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define IS_BLOCK "_is_shaken_up"
#define DID_ATTACK "_attacked_burzum"

void
create_object()
{
    set_name("_room_block");
    add_name("_invis_item");
    set_short("You shouldn't be able to see this.\n");
    set_long("If you can see this, 'bug _invis_item' so I know I totally goofed up on it.\n");
    
    //No peaky ;)
    set_no_show();

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);

}

void
reset_block(object target)
{
	target->catch_msg("You settle down a bit after that brutal attack.\n");
	target->remove_prop(IS_BLOCK);
	if (target->query_prop(DID_ATTACK))
		target->remove_prop(DID_ATTACK);
	TO->remove_object();
}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    to->add_prop(IS_BLOCK, 1);
    set_alarm(25.0, 0.0, &reset_block(to));
}
