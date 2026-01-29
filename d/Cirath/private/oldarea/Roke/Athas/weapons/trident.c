inherit "/std/weapon";

#include <filter_funs.h>
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
        set_name("trident");
        set_short("gigantic trident");
        set_long("This is the largest weapon you have EVER seen in"+
        " your life. You could easily skewer a horse with it. The"+
        " three sharp prongs on the end are crafted out of the"+
        " finest platinum and are glowing white hot.\n");
        set_adj("gigantic");
        set_hit(40);
        set_pen(40);
        set_wt(W_POLEARM);
        set_dt(W_IMPALE);
        set_hands(W_BOTH);
        set_wf(TO);

        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,54) + 2000);
        add_prop(OBJ_I_WEIGHT, 28000);
        add_prop(OBJ_I_VOLUME, 8000);
        add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
        add_prop(MAGIC_AM_MAGIC,({46, "enchantment"}));
        add_prop(MAGIC_AM_ID_INFO,({"It is enchanted to only allow "+
           "a certain quality of person to wield it.",10,
          "The user must have great strength and skill to wield it. "+
       "It allows only those of a certain alignment to wield it. "+
            "It is also especially effective against a certain type "+
            "of foe.",25,
          "The user must have the strength of a titanic hero, "+
          "an alignment between blessed and malevolent, and the "+
            "skill of a master journeyman to wield this "+
            "magnificent weapon of human slaying.",50}));
        add_prop(OBJ_S_WIZINFO,({"The user must have a 120 str and a 50"+
            " polearm to wield. It does 2 times damage to humans. "+
     "The wielder also needs alignment between 750 and -750. "+
            "It is found on the monster: /d/Roke/Athas/npc/gladiator.c"}));
}
