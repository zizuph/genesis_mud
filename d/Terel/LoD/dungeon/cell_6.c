/*
 * cell_6.c
 *
 * A dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "/dungeon/cell";

#include <stdproperties.h>
#include <macros.h>

#define DUNG_DIR (LOD_DIR + "dungeon/")
#define CHAIN    (LOD_DIR + "obj/chain")
#define PRISONER (LOD_DIR + "monster/prisoner")

object chain, prisoner;

public void
reset_room()
{
    ::reset_room();
    
    seteuid(getuid());
    
    if (!chain || !present(chain)) {
        chain = clone_object(CHAIN);
        chain->move(TO);
    }
    
    if (!prisoner || !present(prisoner)) {
        prisoner = clone_object(PRISONER);
        prisoner->move_living("M", TO);
    }

    if (prisoner->tie_object(chain, "prisoner"))
    {
        chain->set_tied_to(prisoner);
        chain->set_tied_to_text(QSHORT(prisoner));
        chain->add_prop(OBJ_M_NO_GET, "It is locked too hard.\n");
        chain->add_prop(OBJ_M_NO_DROP, "It is locked too hard.\n");
    }
}

public void
create_room()
{
    ::create_room();
    
    reset_room();
}
