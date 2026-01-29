/* Kender skeleton for Kender Quest, Gwyneth, August 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("skeleton");
    add_name("_kender_quest_skeleton_");
    set_adj("kender");
    set_short("kender skeleton");
    set_long("These are the last remains of a long deceased kender.\n"); 
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1200);
}

