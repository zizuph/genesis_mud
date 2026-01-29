/*
 *  /d/Sparkle/area/tutorial/obj/torch.c
 *
 *  This torch is sold at the General Store of Silverdell:
 *      /d/Sparkle/area/tutorial/town/general_store.c
 *
 *  It is modified from /d/Gondor/common/obj/torch.c
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */

inherit "/std/torch";
inherit "/lib/keep";

#include <stdproperties.h>

void
create_torch()
{
    set_name("torch");
    set_long("This torch can be used to light up dark areas."
      + " You can <light> the torch to get it going. However,"
      + " torches burn out if you leave them lit. Don't forget to"
      + " <extinguish> the torch once you are in lit areas again.\n");
    set_adj("wooden");

    set_time(2000);
    set_strength(1);
    set_value(40);
}

nomask varargs string
my_short(object for_obj)
{
    if (!obj_short)
    {
        if (sizeof(obj_adjs) && sizeof(obj_names))
            obj_short = implode(obj_adjs," ") + " " + obj_names[0];
        else if (sizeof(obj_names))
            obj_short = obj_names[0];
        else
            return 0;
    }
    return check_call(obj_short, for_obj);
}

public varargs string
short(object for_obj)
{
    return ((Burn_Alarm != 0) ? "burning " : "") + my_short(for_obj);
}

public varargs string
plural_short(object for_obj)
{
    if (!obj_pshort)
        return 0;
    if (!check_seen((objectp(for_obj) ? for_obj : this_player())))
        return 0;
    return ((Burn_Alarm != 0) ? "burning " : "") +
    check_call(obj_pshort, for_obj);
}


