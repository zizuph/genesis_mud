inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/waymeet/defs.h"

mixed do_effect();
int x = 0;

nomask void
create_object()
{
    ::create_object();

    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);

	do_effect();
  
}

mixed
do_effect()
{
	switch(x)
	{
		case 0..5:
		{
			write("The beans make you fart.\n");
			say (QCTNAME(TP) + " lets off a foul fart.\n");
			set_alarm(60.0, 0.0, do_effect);
			x++;
			break;
			return;
		}
		case 6:
		{
			write("You feel less gassy.\n");
			say(QCTNAME(TP) + " looks less gassy.\n");
			remove_object();
		}
	}
}