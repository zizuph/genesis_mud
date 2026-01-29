/*
   /d/Kalad/domain_link.c
   
   Preloads Kalad's important objects.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/domain_link";

#include "/d/Kalad/sys/time.h"
#include "/d/Kalad/sys/outlaw.h"

void
preload_link()
{
   // Kalad's clock
   preload(CLOCK);

   // Preload the outlaw file
   preload(OUTLAW_FILE);
   preload("/d/Kalad/common/guilds/red_fang/obj/master");

   // Preloads rooms
   preload("/d/Kalad/common/port/s81"); /* Shire-shipline */
   preload("/d/Kalad/common/port/shipline/pier");
   preload("/d/Kalad/common/port/s1");
   preload("/d/Kalad/common/port/lift");
   preload("/d/Kalad/common/port/s104");
   preload("/d/Kalad/common/port/s8");
   preload("/d/Kalad/common/central/lift_room");
   preload("/d/Kalad/steed/steed_sh");
}

mapping
query_potion_map()
{

    return 
    ([ 
        "misery": ({ 0, 0, ({ "/d/Kalad/common/herbs/glowshroom",
                              "/d/Gondor/common/herbs/hemlock" }),
                     ({}), ({"elven blood vial"}),
                     "/d/Kalad/common/guilds/khiraa/lp/obj/misery" }),
        "skaltakur": ({ 0, 0, ({ "/d/Kalad/common/herbs/nightshade",
                                 "/d/Gondor/common/herbs/attanar",
                                 "/d/Kalad/common/herbs/mandrake" }),
                     ({}),({"human blood vial"}), 
                     "/d/Kalad/common/guilds/khiraa/lp/obj/skaltakur" }),
        "celerity": ({ 0, 0, ({ "/d/Kalad/common/herbs/drudgeworth",
                                "/d/Kalad/common/herbs/lore",
                                "/d/Kalad/common/herbs/vinerot" }),
                    ({}),({"human blood vial"}),
                    "/d/Kalad/common/guilds/khiraa/lp/obj/celerity" }),
        "rot": ({ 0, 0, ({ "/d/Kalad/common/herbs/vinerot",
                           "/d/Kalad/common/herbs/drudgeworth",
                           "/d/Kalad/common/herbs/dajla" }),
               ({}),({"child blood vial"}),
               "/d/Kalad/common/guilds/khiraa/lp/obj/rot" })
    ]);
}

