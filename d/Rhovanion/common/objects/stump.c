inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Rhovanion/defs.h"

#define TREE OBJ_DIR+"tree"

create_object()
{
    set_name("stump");
    set_adj("tree");
    set_long("This is the stump of what was once a mighty tree.\n");
    add_prop(OBJ_I_NO_GET, 1);
    set_alarm(200.0, 0.0, "new_tree");
}

new_tree()
{
    object ob;
    ob = clone_object(TREE);
    tell_room(environment(this_object()), "The stump starts to shake, " +
        "and then almost by magic, regenerates itself into a full " +
        "tree.\n");
    ob->move(environment(this_object()));
    remove_object();
}
