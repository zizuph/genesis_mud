#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include <ss_types.h> /* Contains skills */
#include <const.h> /* For G_FEMALE */

void
create_earthsea_monster()
{
    set_name("mermaid");
    set_short("beautiful mermaid");
    set_adj("beautiful");
    set_race_name("merfolk");
    set_long("This lovely creature swims about the waters " +
        "with grace.  Girded in seashells, the mermaid " +
        "floats in and out of the buildings, conversing " +
        "with the other merfolk.\n");

    set_alignment(200);

    set_gender(G_FEMALE);

    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_SWIM, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 50);

              /* str, dex, con, int, wis, dis */
    set_stats(({  50,  70,  60,  60,  60,  60 }));

    /* This will take care of cloning equipment and wielding/wearing */
    add_equipment( ({
                      "/d/Earthsea/replace/this/with/a/path/to/your/equipment",
                      "/d/Earthsea/replace/this/with/a/path/to/your/equipment",
                    }) );
}
