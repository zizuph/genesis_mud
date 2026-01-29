/* 
 * Nocturnus object, Darkness globe.
 */
inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

int oldsight;


void
create_object()
{
    add_name("mag_infravision");
    set_long("The dark globe looks like it is made of dark glass. A nightshade "+
	"is enclosed in its center.\n");	
    add_prop(OBJ_S_WIZINFO, "A magical means to see in darkness, will fade.\n");
    set_no_show();
    add_prop(OBJ_M_NO_DROP,1);

}


public void
enter_env(object dest, object old)
{
    object wearer;
    int newsight;

    wearer=dest;
    oldsight=wearer->query_prop(LIVE_I_SEE_DARK);
    newsight=oldsight+4;
    wearer->add_prop(LIVE_I_SEE_DARK,newsight);
    
}



public void
notify_dispel_magic(object ob)
{
    
	object env=environment();
	
	if (living(env))
    {
  
	env->catch_msg("Your eyes looses their enchantment, you can no longer see " +
			"in darkness.\n");
	
    }
    env->add_prop(LIVE_I_SEE_DARK,oldsight);
    remove_object();
}

