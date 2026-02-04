/*
 * cell_1.c
 *
 * A dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "/dungeon/cell";

#include <stdproperties.h>
#include <macros.h>

#define DUNG_DIR (LOD_DIR + "dungeon/")
#define ROPE     (LOD_DIR + "obj/rope")
#define SKELETON (LOD_DIR + "obj/skeleton")

object rope, skeleton;

public void
reset_room()
{
    ::reset_room();
    
    seteuid(getuid());
    
    if (!rope || !present(rope)) {
        rope = clone_object(ROPE);
        rope->move(TO);
    }
    
    if (!skeleton || !present(skeleton)) {
        skeleton = clone_object(SKELETON);
        skeleton->move(TO);
    }

    if (skeleton->tie_object(rope, "neck"))
    {
        rope->set_tied_to(skeleton);
        rope->set_tied_to_text(skeleton->short());
        rope->add_prop(OBJ_M_NO_GET, "It is tied too hard.\n");
        rope->add_prop(OBJ_M_NO_DROP, "It is tied too hard.\n");
    }
}

public void
create_room()
{
    ::create_room();
    
    reset_room();
}
