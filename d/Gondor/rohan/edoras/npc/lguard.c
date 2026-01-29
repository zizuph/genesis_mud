inherit "/d/Gondor/rohan/edoras/npc/edoras_soldier";
inherit "/d/Gondor/common/lib/logkill";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_guard() 
{
    ::create_guard();
    default_config_npc(80);
    set_base_stat(SS_CON, 90);
    set_base_stat(SS_STR, 90);
    refresh_living();
    set_skill(SS_WEP_SWORD, random(10) + 90);
    set_skill(SS_DEFENCE, random(10) + 70);
    set_skill(SS_PARRY, random(10) + 70);
    set_alignment(650 + random(150));
    set_chat_time(15);
    add_chat("Stay, strangers here unknown!");
    add_chat("It is the will of Theoden King that none should enter "
      + "his gates, save those who are our friends!");
    add_chat("None are welcome here in days of war but our own "
      + "folk, and those that come from Mundburg in the land of "
      + "Gondor.");
    add_chat("Say, are you not some spy from Saruman, or phantoms of his craft?");
    add_cchat("Dirty serfs of Saruman, you will die for this!");
    add_cchat("To arms, Eorlingas! Intruders at Meduseld! To arms!");
    add_cchat("Westu Theoden hal!");
    add_cchat("Death to all the spies of the Dark One!");
}

/* Solamnian prestige */
query_knight_prestige() {return (-6);}
