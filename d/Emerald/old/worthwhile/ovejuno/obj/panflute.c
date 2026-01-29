/* Ckrik June 1998
 * Modified by Marisol (08/28/98) to be used in Ovejuno, Emerald
 */

inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

void
create_object()
{
    set_name("pipe");
    set_pname("pipes");

    set_adj("pan");

    set_short("pan pipe");
    set_pshort("pan pipes");
  
    set_long("A shepherd's pipes, better known as Pan pipes. Is a "+
        "double flute, with two long wooden tubes, attach to each "+
        "other with holes placed in a certain interval. Maybe "+
        "you can play it.\n");

    add_prop(OBJ_I_VALUE, 250 + random(20));
    add_prop(OBJ_I_WEIGHT, 200);
  
    add_prop(OBJ_I_VOLUME, 350);
}

void
init()
{
    ::init();
    add_action("play", "play");
    add_action("play", "blow");
}

int
play(string str)
{
    if (str == "pan pipes" || str == "pipes")
    {
        this_player()->catch_msg("You blow into the pan pipes and " +
			       "melodious music flows out from the " +
			       "pipes.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
		" blows into the pan pipes and melodious music " +
		"flows out from the pipes.\n", this_player());
        return 1;
    }

        return 0;
}
