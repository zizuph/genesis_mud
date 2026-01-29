/*  Seashells for the beach at gont. The blue version of 
 *  this one is used in the witch seashell quest. Players
 *  can find these when they search the debris on the beach
 * in /d/Earthsea/gont/beach/ 
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

private int is_blue = 0;

public void
create_object()
{
    string size = ({ "small", "medium", "large" })[random(3)],
        color = ({ "blue", "pink", "grey", "white", "lavendar",
        "mother-of-pearl" })[random(6)], type = ({ "conch",
        "oyster", "clam", "abalone", "spiral" })[random(5)];

    if(color == "blue")
    {
        is_blue = 1;
    }

    set_short(size + " " + color + " " + type + " seashell");
    set_pshort(size + " " + color + " " + type + " seashells");
    set_long("This is a " + size + " " + color + " " + type +
        " seashell. It may have some value, just for " +
        "its beauty.\n");
    set_name("seashell");
    add_name("shell");
    set_adj("sea");
    add_adj(size);
    add_adj(color);
    add_adj(type);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 20 + random(40));
}

public int
query_color()
{
    return is_blue;
}
