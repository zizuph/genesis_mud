// file name:        /d/Avenir/common/holm/shorep
// creator(s):       Lilith, Jan 1997
// revision history: Lilith, 28 March 1997
// purpose:          for placing objects on the holm/shore

#include <macros.h>

#include "holm.h"
#include "/d/Avenir/smis/smis.h"

inherit SMIS_MODULE_PLACER;

void create_placer()
{
    set_module_id("shorep");
    set_module_description("The Holm's shoreline");

    set_location_npc(SHORE + "sh1",     HOLM_MON + "phrynos");
    set_location_npcs(SHORE + "sh6",  ({ HOLM_MON + "seabird",
                                        HOLM_MON + "noble"}));
    set_location_npc(SHORE + "sh8",     HOLM_MON + "trolgen");
    set_location_npc(SHORE + "sh14",    HOLM_MON + "adept");
    set_location_npc(SHORE + "sh16",    HOLM_MON + "seamonster");
    set_location_npc(SHORE + "sh19",    HOLM_MON + "trolgen");    
    set_location_npcs(SHORE + "sh20", ({ HOLM_MON + "seabird",
                                         HOLM_MON + "phrynos"}));
    set_location_npc(SHORE + "sh22",    HOLM_MON + "noble");
    set_location_npcs(SHORE + "sh25", ({ HOLM_MON + "hunted_l",
                                        HOLM_MON + "hunted",  
                                        HOLM_MON + "hunted" }));
    set_location_npc(SHORE + "sh26",    HOLM_MON + "selkie");

    set_location_object(SHORE + "sh7",  HOLM_OBJ + "conch"); 
    set_location_object(SHORE + "sh11",  HOLM_OBJ + "small_hole"); 
    set_location_object(SHORE + "sh15", DARK + "obj/skull"); 
    set_location_object(SHORE + "sh16", HOLM_OBJ + "hiz_altar");
    set_location_object(SHORE + "sh27", HOLM + "/wolf/imprint");
    set_location_object(SHORE + "sh15", HOLM + "wolf/pelvic");
}
