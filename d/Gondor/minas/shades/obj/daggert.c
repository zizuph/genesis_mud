/*
 * /d/Gondor/minas/shades/obj/daggert.c
 *
 * A poisoned dagger.
 * Used by Talin (/d/Gondor/minas/shades/talin.c)
 *
 * Modification log:
 * 05-aug-1997, Olorin: Changed inheritance to generic Gondor poisoned dagger.
 */
#pragma strict_types

inherit "/d/Gondor/common/wep/poison_dagger.c";

#include <macros.h>

public void
create_poison_dagger()
{
    configure_dagger("short", "sharp");
    set_doses(3);
}
