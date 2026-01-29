/*****************************************************
 * Name: Zombie                                                    
 * By: Elmore
 * Desc: A zombie for Dargaard Keep.
 * Note: -
 *                                                                             
 *****************************************************/
  
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h";

inherit AM_FILE

int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}

void
create_krynn_monster()
{
    set_name("zombie");    
    set_race_name("undead");

    set_adj("decaying");
    
    switch(random(6))
    {
        case 0:
            add_adj("human");
            set_short("decaying human zombie");
        break;

        case 1:
            add_adj("elf");
            set_short("decaying elf zombie");
        break;

        case 2:
            add_adj("dwarf");
            set_short("decaying dwarf zombie");
        break;

        case 3:
            add_adj("kender");
            set_short("decaying kender zombie");
        break;

        case 4:
            add_adj("gnome");
            set_short("decaying gnome zombie");
        break;

        default:
            add_adj("goblin");
            set_short("decaying goblin zombie");
        break;

    }

    add_prop(LIVE_I_UNDEAD, 100);

    set_long("You stand before one of the wraiths in Dargaard Keep. "+
             "This horrible creature is seen as black, vaguely "+
             "man-shaped clouds. This creature has no true "+
             "substance, instead this one has shaped itself "+
             "with two upper limbs, a torso, and a head with two "+
             "glowing red eyes. This shape might be a convenience "+
             "born from the habit of once having a human body.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 50000);
    set_gender(G_NEUTER);
    set_random_move(random(100));
    set_aggressive(1);

    set_stats(({78+random(10),78+random(10),60+random(20),40,50,80}));

    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 55);
    set_skill(SS_PARRY, 50);

    set_alignment(-1000);
    set_knight_prestige(10);
    set_aggressive(VBFC_ME("check_aggresive"));
    set_all_hitloc_unarmed(10);

    clone_object(DARM + "rags.c")->move(TO,1);
    command("wield all");
    command("wear all");
}


