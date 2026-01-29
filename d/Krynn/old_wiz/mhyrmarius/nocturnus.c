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

}



public void
notify_dispel_magic(object ob)
{
    remove_object();
}

