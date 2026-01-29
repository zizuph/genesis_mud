/*
 * /d/Gondor/minas/obj/tomb_token.c
 *
 * The Token of the Tombs
 *
 * Alto 20 May 2001
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/lib/spectre_riddles.c"



void
create_object()
{
    set_name("token");
    set_adj("shiny");
    add_adj("metal");
    set_short("shiny metal token");
    set_pshort("shiny metal tokens");
    set_pname("tokens");
    add_name("_token_of_tombs_");
    set_long("This is a shiny metal token. There is an inscription "
        + "carved into its face.\n");
    add_item(({"inscription", "face"}), "The inscription reads:\n\n"
        + "\t\tThis is the Token of the Tombs. Should any question\n"
        + "\t\tyour right to enter the tombs, you may 'answer' with\n"
        + "\t\tconfidence.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 150);
    seteuid(getuid(TO));
}


