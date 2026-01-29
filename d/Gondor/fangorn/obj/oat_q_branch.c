/*
 * /d/Gondor/fangorn/obj/oat_q_branch.c
 *
 * marsh oak branch for the Oat Quest
 *
 * Alto, 15 May 2001
 *
 */


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("branch");
    add_name("_oat_quest_branch_");
    set_adj("dark");
    add_adj("grey");
    set_pname("branches");
    set_short("dark grey branch");
    set_pshort("dark grey branches");
    set_long("This is a medium-sized branch from a rare marsh oak "
        + "tree.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 150);
    seteuid(getuid(TO));
}
