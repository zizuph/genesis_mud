// Saor - simple manach used by a wizard to possess and direct
//
//   Coder         Date                Action
// -------------- -------- ----------------------------------------------
// Zima           7/11/98   Created
//
#include "defs.h"
inherit  SR_NPC+"monkbase";
inherit  SR_NPC+"monk_specatck";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
 
#define  VEST (({"robe","cincture","tonsure","chasuble"}))
 
void equip_me()
{
   vest_me(VEST);
   (clone_object(SR_WEAPON+"crozier"))->move(TO);
   command("wield all");
}
 
void create_khalakhor_human()
{
    set_name("saor");
    add_name(({"monk","manach","presbytair"}));
    set_title("the Manach of Sean-Rhian and Presbytair of Seanchan "+
              "Tor Abbey");
    add_adj(({"blue-eyed","gray-haired"}));
    set_race_name("elf");
    set_long(
        "He is a blue-eyed gray-haired elf, his habit identifying him as "+
        "an elder member of the Manachs of Sean-Rhian.\n");
 
    set_manach_stats(110);
 
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   set_skill(SS_LANGUAGE,100);
}
 
public int is_saggart()   { return 1; }
public int query_sr_level() { return SRLVL_PRESB; }
