// sair_blessing     /d/Avenir/common/port/obj/sair_blessing
// creator(s):    Lilith 2021
// last update:
// purpose:      Blessing object for Sair Altar
// note:         Lasts for 30-45 mins, does not stack,  
//               and does not last through logouts.
// bug(s):
// to-do:

inherit "/std/object";

#include "../port.h"
#include "/d/Avenir/include/deities.h"
#include "/d/Avenir/include/basic.h"
#include <macros.h>
#include <stdproperties.h>

private int bonus = 5;

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"_Avenir_Sair_Blessing"}));

    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This is a blessing that temporarily "
	    +"blesses the bearer with some of Sair's STR (5) and Earth "
		+"Element skills (5).\n");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GET, 1);
}

public void
remove_object(void)
{
	if (!IS_CLONE)
		return;
	
	object blessed;
    blessed = environment(this_object());
	
    if (interactive(blessed))
    {
	    ALTER_STAT(blessed, SS_STR, -bonus);
		ALTER_SKILL(blessed, SS_ELEMENT_EARTH, -bonus);
	    blessed->catch_tell("You feel the essence of the Goddess Sair's "
		    +"Power and Strength leaving you.\n");
    }
    ::remove_object();
}

public void
enter_env(object dest, object prev)
{
    float time = itof(1800 + random(900)); // 30-45 mins.

    ::enter_env(dest, prev);
	
	if (!interactive(dest))
	    return;
	
	ALTER_STAT(dest, SS_STR, bonus);
	ALTER_SKILL(dest, SS_ELEMENT_EARTH, bonus);
    dest->catch_tell("You feel Sair's blessing rest upon your head "
	    +"and shoulders.\nYou feel both physically stronger and more "
		+"skilled in earth magicks.\n");
	    
    set_alarm(time, 0.0 , &remove_object());
}
