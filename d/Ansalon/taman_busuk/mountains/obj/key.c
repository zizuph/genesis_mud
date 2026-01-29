/*
*    Key for treasure chest in quest in Flotsam
*/
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

#include <stdproperties.h>
inherit "/std/key";

void
create_key() 
{
    ::create_key();
    set_name("key");
    set_short("iron key");
    set_adj("elaborate");
    set_long("This is a large iron key. It looks like it is " +
      "suffering from a major case of rust.\n");

    set_key(7111111);
    add_prop("_key_i_no_keyring",1);
    add_prop(OBJ_M_NO_STEAL, "@@prevent_steal@@");
}

mixed
prevent_steal()
{
    object env = environment(this_object());
    string garren_description;

    if (this_player()->query_met(env))
    {
      garren_description = "Garren";
    }
    else
    {
      garren_description = "The frustrated noble male human";
    }

    if (env && living(env))
    {
        return garren_description + " has too strong a grasp on the key for it to be stolen.\n";
    }
    return 0;
}
