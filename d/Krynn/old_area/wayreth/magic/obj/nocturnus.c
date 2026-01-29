/* 
 * Nocturnus object, Darkness globe.
 */
inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>



void
create_object()
{
    add_name("mag_dark_globe");
    set_name("globe");
    set_adj("dark");
    set_long("The dark globe looks like it is made of dark glass. A nightshade "+
	"is enclosed in its center.\n");	
    add_prop(OBJ_S_WIZINFO, "A magical darkness globe. Will eventually fade out.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "abjured" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
        "The magic globe offers an aura of darkness.\n", 0}) );

    add_prop(OBJ_I_LIGHT,-2);
}



public void
notify_dispel_magic(object ob)
{
    
	object env=environment();

	if (env->query_prop(ROOM_I_IS))
	{
	   tell_room(env, "The room suddenly gets a little brighter.\n");	 
	}
	if (living(env))
    {
  
	env->catch_msg("Suddenly the globe of darkness starts to feel brittle, and then it " +
			"disappears.\n");
	tell_room(E(env), "The darkness flickers a bit, and it becomes a little lighter.\n",env);
    }
    
    remove_object();
}

