// file name:        rothe_skin.c
// creator(s):       Nikklaus, Aug'97
// revision history:
// purpose:          Another trading commodity of Undraeth, for delivery.
//                   Perhaps will use it as a leftover for rothe corpses.
// note:
// bug(s):
// to-do:

# pragma strict_types
# include <stdproperties.h>

inherit "/std/object";

public void
create_object()
{
    set_name("rothe hide");
    add_name("hide");
    add_name("skin");
    set_adj("rothe");
    add_name("leather");
    set_short("unworked rothe hide");
    set_long("This is a long sheet of cured rothe hide, ready for "+
      "for finishing and tailoring.\n");
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 900);
}
