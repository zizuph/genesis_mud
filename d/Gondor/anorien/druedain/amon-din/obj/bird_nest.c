/*
 * /d/Gondor/anorien/druedain/amon-din/obj/bird_nest.c
 *
 * This is the nest of a bird somewhere in Amon Din. It contains a key.
 *
 * /Gorboth, July 1995
 * special thanks to Mercade for help on this file
 *
 * Revisions: 8 feb. 2000 Stern: adapted to use Genesis gem system
 *            6 oct, 2004 Gorboth: adapted to function properly for longer
 *                                 uptimes
 */

inherit "/std/container";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define GEM_DIR "/d/Genesis/gems/obj/"
void reset_container();

void
create_container()
{
    set_name("nest");
    add_name("bird_nest_at_amon_din");
    set_adj( ({ "birds", "bird's", }) );
    set_short("bird's nest");
    set_long(BSN(
       "This nest sits alone up in these high branches. It seems"
     + " quite unremarkable, being nothing more than a"
     + " bowl shaped assortment of twigs and moss."));
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 900);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "You have nothing against this bird, why"
			 + " would you care to steal its home?\n");

    setuid();
    seteuid(getuid());

    enable_reset();
    reset_container();
}

void
reset_container()
{
    object  gem;
    if (!objectp(present("amon_din_storage_key")))
    {
	     clone_object(AMON_DIR + "obj/storage_key")->move(TO);
    }

    if (!objectp(present("gem")))
    {
        gem = clone_object(GEM_DIR + "beryl");
        gem->move(TO);
    }
}
