// file name:        /d/Kalad/common/wild/pass/drow/obj/gem_dark.c
// creator(s):       Antharanos
// purpose:          
// note:             
// bug(s):           
// to-do:            

# pragma strict_types
# include <stdproperties.h>
inherit "/std/object";
inherit "/lib/keep";

void
create_object()
{
    set_name("gem");
    set_adj("darkness");
    set_short("gem of darkness");
    set_long("A cloudy, smoky black gem whose center seems to absorb all "+
	     "light within the vicinity.\n");
    add_prop(OBJ_I_VALUE, 1728);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_LIGHT, -1);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
    add_prop(OBJ_M_NO_SELL, 1);
}
