/*
 * eagle feathers for Bilbo Quest
 * Finwe, 2/99
 */

inherit "/std/object";
#include <stdproperties.h>      /* Properties */

create_object()
{
    int y,z;
    string *color, *type;

    color = ({"brown", "grey", "splotched", "white"});
    type  = ({"spotted", "calico", "plain", "ruffled"});

    y = random(sizeof(color));
    z = random(sizeof(type));

    set_name("feather");
    add_name("_imladris_feather_");
    add_adj(color[y]);
    add_adj(type[z]);
    set_short("large feather");
    set_long("This " + color[y] + " " + type[z] + " feather is " +
        "from a large bird. What the bird may have been can't " +
        "be told by the feather, but surely it was a stately bird.\n");
    add_item("quill",
        "The quill of the feather is about half a finger's " +
		"length. It is a translusent white and has a hollow tip.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_VOLUME, 5);
}

