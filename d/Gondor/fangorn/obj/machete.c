/*
 * /d/Gondor/fangorn/obj/machete.c
 *
 * A machete decoy for the oat quest
 *
 * Alto 30 April 2001
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"


void
create_object()
{
    set_name("machete");
    set_adj("old");
    add_adj("rusty");
    set_short("old rusty machete");
    set_pshort("old rusty machetes");
    set_pname("machetes");
    add_name("_oat_quest_machete_");
    set_long("This is an old rusty machete. It is so rusty that it would "
        + "be useless as a weapon. You might be able to use it to cut or "
        + "chop vegetation, however. There is some kind of residue on the "
        + "handle\n");
    add_item(({"residue", "residue on handle"}), "The residue has the look "
        + "of old dried blood.\n");
    add_item(({"handle"}), "It is smeared with some kind of residue.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 150);
    seteuid(getuid(TO));
}

