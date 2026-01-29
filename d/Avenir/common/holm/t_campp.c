// camp placer for the troloby camp on the Holm , Rangorn Feb 97

#include <macros.h>
#include "/d/Avenir/smis/smis.h"
#include "holm.h"

inherit SMIS_MODULE_PLACER;

void create_placer()
{
    disable_notifications_autoset();
    /* Prevents computation of the list of rooms this module operates
       on: keeps rooms from cluttering the decision tables. */
    set_module_id("t_campp");
    set_module_description("Troloby camp on the Holm.");

    set_location_object(T_CAMP +"c2", DARK +"obj/bones");
    set_location_object(T_CAMP +"t1", DARK +"obj/bones");
    set_location_object(T_CAMP +"c8", DARK +"obj/skull");
    set_location_object(T_CAMP +"c12", DARK +"obj/skull");

    set_location_npc(T_CAMP + "c1" , HOLM_MON + "trolgen");
    set_location_npc(T_CAMP + "c3" , HOLM_MON + "trolgen");
    set_location_npc(T_CAMP + "c5" , HOLM_MON + "trolgen");
    set_location_npc(T_CAMP + "c7" , HOLM_MON + "drunk_troloby");
    set_location_npc(T_CAMP + "c10", HOLM_MON + "trolgen");
    set_location_npc(T_CAMP + "c12", HOLM_MON + "trolgen");
    set_location_npc(T_CAMP + "t2" , HOLM_MON + "noble_troloby");

    set_location_npcs(T_CAMP + "c2", ({ HOLM_MON + "trolgen",
                                        HOLM_MON + "trolgen"}));
    set_location_npcs(T_CAMP + "c6", ({ HOLM_MON + "trolgen",
                                        HOLM_MON + "trolgen"}));
    set_location_npcs(T_CAMP + "c9", ({ HOLM_MON + "trolgen",
                                        HOLM_MON + "trolgen",
                                        HOLM_MON + "trolgen"}));
    set_location_npcs(T_CAMP + "c10", ({ HOLM_MON + "trolgen",
                                        HOLM_MON + "trolgen"}));
    set_location_npcs(T_CAMP + "c11", ({ HOLM_MON + "trolgen",
                                        HOLM_MON + "trolgen",
                                        HOLM_MON + "trolgen"}));
    set_location_npcs(T_CAMP + "w1", ({ HOLM_MON + "wizard",
                                        HOLM_MON + "nasty_troloby"}));
    set_location_npcs(T_CAMP + "cage1", 
                               ({"/d/Avenir/common/park/mon/bicornv",
                                 "/d/Avenir/common/park/mon/bicornv"}));
}
