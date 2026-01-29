/* Navarre June 24th 2006, added add_item("lock"). */

inherit "/std/receptacle";

#include <stdproperties.h>

#define MITHAS_FOREST_CHEST "_mithas_forest_key"

public void
create_receptacle()
{
    set_name("chest");
    set_adj("heavy");
    add_adj("wooden");
    set_short("heavy wooden chest");

    set_long("This is a heavy chest made of wooden planks held "+
      "together with rusty iron bands. A small copper lock "+
      "keeps the chest locked.\n");

    add_prop(CONT_I_WEIGHT, 2500000);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_I_VALUE, 120);
    add_prop(CONT_I_LOCK, 1);
    set_no_pick();
    set_cf(this_object());
    add_item("lock", "It is a lock, if it is locked it keeps the chest "+
             "from being opened.\n");
    set_key(MITHAS_FOREST_CHEST);
}
