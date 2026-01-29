/*
 * Revision Feb 2000 Stern: adapted to genesis gem system
 */

inherit "/std/container";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

void    reset_container();

void
create_container()
{
    set_short("wooden shelf");
    set_name("shelf");
    set_adj("wooden");
    set_long(BSN("A large wooden shelf to store items. Since it is standing "
      + "here in the treasury, it was probably intended to hold the "
      + "heirlooms of the House of Hurin."));

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(OBJ_I_VOLUME,   5000);
    add_prop(OBJ_I_WEIGHT,  20000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

    enable_reset(200);

    reset_container();
}

void
reset_container()
{
    object  diamond;

    FIX_EUID
    if (!present("scabbard", TO))
        clone_object(ITH_DIR + "emyn-arnen/obj/scabbard")->move(TO, 1);
    if (!present("horn", TO))
        clone_object(ITH_DIR + "emyn-arnen/obj/arawhorn")->move(TO, 1);
    if (!present("helm", TO))
        clone_object(ARM_DIR + "vishelm")->move(TO, 1);
    if (!present("gem", TO))
    {
        diamond = clone_object(GEM_DIR + "sapphire");
        diamond->set_heap_size(3 + random(3));
        diamond->move(TO, 1);
        diamond = clone_object(GEM_DIR + "opal");
        diamond->set_heap_size(4 + random(3));
        diamond->move(TO, 1);
        diamond = clone_object(GEM_DIR + "garnet");
        diamond->set_heap_size(2 + random(3));
        diamond->move(TO, 1);
        diamond = clone_object(GEM_DIR + "diamond");
        diamond->set_heap_size(2 + random(3));
        diamond->move(TO, 1);
    }
}

void
clone_scabbard()
{
    FIX_EUID
    if (!present("scabbard", TO))
        clone_object(ITH_DIR + "emyn-arnen/obj/scabbard")->move(TO, 1);
}

