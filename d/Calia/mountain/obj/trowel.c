// OBJECT:  trowel

    /* Calia Domain

    HISTORY

    [96-02-16] Created by Uhclem from [C:\CALIA\MOUNTAIN\OBJ\TROWEL.DOC].

    PURPOSE

    This trowel is a quest item found which may be purchased in the Calia
    palace hardware shop.  It is necessary to have a trowel in order to plant a
    seed in the garden.  Acquiring this trowel is not a difficult task, so no
    provision is made for recovery.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

// OBJECT DEFINITION

void
create_object()
{

    /*  DESCRIPTION  */

    int i = random(4);
    set_name("trowel");
    set_short("small trowel");
    set_adj("small");

    switch (i)

        {

        case 0:

            set_long("This small trowel is one of a series of " +
                "gardening tools decorated with scenes from old " +
                "Calian fairy-tales.  The illustration depicts " +
                "the bedroom of a young princess who cannot " +
                "sleep because there is a trowel under her mattress.\n");

            break;

        case 1:

            set_long("This small trowel is one of a series of " +
                "gardening tools decorated with scenes from old " +
                "Calian fairy-tales.  The illustration depicts " +
                "a little girl holding a red trowel skipping though " +
                "the forest on the way to her grandmother's house.\n");

            break;

        case 2:

            set_long("This small trowel is one of a series of " +
                "gardening tools decorated with scenes from old " +
                "Calian fairy-tales.  The illustration depicts " +
                "a little blonde-haired girl trying to decide " +
                "between a trowel that is much too big for her, " +
                "one that's too small, and one that looks just right.\n");

            break;

        case 3:

            set_long("This small trowel is one of a series of " +
                "gardening tools decorated with scenes from old " +
                "Calian fairy-tales.  The illustration depicts " +
                "a young woman hurrying out of a royal palace " +
                "just at the stroke of midnight, " +
                "leaving behind her a solitary glass trowel.\n");

            break;

        }

    /*  ITEMS  */

    add_item(("illustration"),
        "You discern the unmistakable chaotic brushstrokes of an " +
        "inebriated Calian wizard.\n");

    /*  PROPERTIES  */

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 12);

    }
