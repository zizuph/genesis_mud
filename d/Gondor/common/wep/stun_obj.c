/* 
 *Stun object, to work with Haradrim greatbow/barbed arrows
 *Altrus, July 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define IS_STUN "_stunned_from_barbed_arrow"

void
create_object()
{
    set_name("_arrow_stuck");
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
reset_stun(object target)
{
	target->remove_prop(IS_STUN);
	TO->remove_object();
}

void
un_stun(object target)
{
    if (objectp(target))
    {
	target->remove_stun();
	target->remove_subloc("_arrow_stunned");
	target->catch_msg("Gritting your teeth, you rip the arrow out of your shoulder!\n");
	tell_room(ENV(target), QCTNAME(target) + " grits " + HIS_HER(target) + " teeth and rips the arrow out of " + HIS_HER(target) + " shoulder!\n", target, target);
	set_alarm(30.0, 0.0, &reset_stun(target));
	}
}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    to->add_subloc("_arrow_stunned", this_object());
    set_alarm(15.0, 0.0, &un_stun(to));
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if(subloc!="_arrow_stunned")
      return "";

    //What they see in their inventory
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
 
    //What they see when they examine themselves
    if (for_obj == me)
        return "You have a barbed grey-feathered arrow stuck in you!\n";
    
    //What others see when they examine the welt-haver
    else
        return CAP(HE_SHE(me))+" has a barbed grey-feathered arrow stuck in " + HIM_HER(me) + "!\n";
}
