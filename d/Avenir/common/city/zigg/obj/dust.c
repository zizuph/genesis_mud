// Pouch of dust ("dust.c")
// creator(s):   Zielia 2007
// last update:
// purpose:      
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>

private static string color = one_of_list(({

  "red", "dark red", "scarlet", "crimson", "pink", "orange", 
  "yellow", "green", "jade", "light green", "dark green", "blue",
  "light blue", "sapphire", "dark blue", "indigo", "teal", "cerulean",
  "turquoise", "violet", "amethyst", "lavender", "purple", "white",
  "black", "onyx", "obsidian", "ruby", "emerald"

}));

public void
create_object(void)
{
    set_name(({"pouch", "dust", "zigg:gem:dust"}));
    set_short("pouch of glittery "+ color +" dust");
    set_adj(({"small", "glittery", "gem"}));
    add_adj(explode(color, " "));
    set_long("A small white pouch filled with glittery "+ color +
	" dust, the powdered byproduct of cutting gem stones.\n");

    add_prop(OBJ_I_WEIGHT,  40);
    add_prop(OBJ_I_VOLUME,  40);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_SELL,  1);
    set_keep(1);
}
