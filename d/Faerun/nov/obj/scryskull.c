
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../nov.h"

inherit "/std/leftover";

void
do_messages()
{
	tell_room(environment(this_object()), "The floating skull begins to scrutinize " +
	"with its pin-point lights that serve as eyes in its hollow eyesockets.\n");
}

void
do_messages2()
{
	tell_room(environment(this_object()), "The floating skull booms out a hollow " +
	"eerie laughter as it looks at you with a piercing pin-point gaze.\n");
}

void
do_messages3()
{
	tell_room(environment(this_object()), "The floating skull grins morbidly with " +
	"its teeth that seem to be made of fine priceless gems.\n");
}

void
do_rem()
{	
       tell_room(environment(this_object()), "The white pin-point lights in the " +
       "floating skull's eyesockets slowly diminish, and the gems " +
       "in its jaws suddently turn into normal teeth.\n\nThe " +
       "skull levitates down to the ground.\n\nA cold chill runs down your " +
       "spine!\n");
       remove_adj("floating");
       set_short("human skull");
       set_long("This is the torn and bloody remains of a human skull.\n");
       remove_prop(OBJ_I_NO_STEAL);
       remove_prop(OBJ_M_NO_GET);
}


create_leftover()
{
        set_name("skull");
        set_adj("floating");
        set_short("floating skull");
        set_long("This is a floating human skull.\n");
        add_prop(OBJ_I_NO_STEAL, "The floating skull avoids your nimbling fingers.\n");
        add_prop(OBJ_M_NO_GET, "You try to get the floating skull, but it easily " +
        "floats above you, out of reach.\n");
        
      set_alarm(2.0,0.0, &do_messages());
      set_alarm(9.0,0.0, &do_messages2());
      set_alarm(18.0,0.0, &do_messages3());
      set_alarm(22.0,0.0, &do_rem());

}

