/* 
 * /d/Gondor/guilds/militia/obj/neq_rack.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * non-Saving Equipment Rack
 * Auberon and Gwyneth, April 2001
 */
inherit "/std/container";
#include <stdproperties.h>

void
create_container()
{
    set_name("rack");
    add_name("non_glowing_rack");
    set_adj("spruce");
    add_adj("wood");
    set_short("spruce wood rack");
    set_long("This is a rack where members can place their equipment for " + 
        "use by other members. The word 'Sort' has been blackened into the " + 
        "side.\nThis rack looks a bit more beat up than the other rack.\n");

    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The spruce wood rack is impossible to carry.\n");
}

