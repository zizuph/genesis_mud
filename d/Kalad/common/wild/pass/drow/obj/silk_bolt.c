// file name:        silk_bolt.c
// creator(s):       Nikklaus, Aug'97
// revision history:
// purpose:          Just a content for delivery packages. Undraeth's #1 
//                   mercantile resource.
// note:
// bug(s):
// to-do:

# pragma strict_types
# include <stdproperties.h>

inherit "/std/object";

public void
create_object()
{
    set_name("bolt of silk");
    add_name("silk");
    add_name("bolt");
    set_long("This is a roll of silk fabric, wrapped around a light "+
      "bamboo-like rod.\n");
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 1755);
}
