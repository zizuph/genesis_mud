#include "../../garden.h"

inherit PLANT_BASE;

#include <wa_types.h>
#include <ss_types.h>

void create_plant()
{
  set_name("roper");

  set_stats(({ 80, 90, 100, 20, 20, 90 }));
  
  set_attack_unarmed(1,  80, 40, W_BLUDGEON, "vines");
  set_attack_unarmed(2,  80, 40, W_BLUDGEON, "vines");  
  set_attack_unarmed(4,  80, 40, W_BLUDGEON, "vines");
  set_attack_unarmed(8,  80, 40, W_BLUDGEON, "vines");
  set_attack_unarmed(16, 80, 40, W_BLUDGEON, "vines");

  set_hitloc_unarmed(1, 60, 70, "vines");
  set_hitloc_unarmed(2, 50, 20, "leaves");
  set_hitloc_unarmed(4, 80, 10, "stem");
 
  set_skill(SS_UNARM_COMBAT, 90);
  set_skill(SS_DEFENCE, 90);
}
