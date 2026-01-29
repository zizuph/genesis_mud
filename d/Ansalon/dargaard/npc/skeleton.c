/*************************************************
 * Name     : skeleton warrior                   *
 * Location : Dargaard keep                      *
 * Made by  : Elmore                             *
 * Date     : April, 2001                        *
 *************************************************/

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
    set_race_name("human"); 
    set_name(({"skeleton", "warrior"}));
    add_prop(LIVE_I_UNDEAD, 100);
    switch(random(3))
    {
        case 0:
            set_adj("lesser");
            set_short("lesser skeleton warrior");
            set_long("The skeleton is covered with shards of "+
                     "decaying flesh, and some of his original "+
                     "armour still covers his now yellow "+
                     "bones. This skeleton looks "+
                     "rather weak and brittle.\n");

            set_stats(({50,60,50,40,30,80}));

            set_skill(SS_WEP_SWORD, 50);
            set_skill(SS_WEP_CLUB, 50);
            set_skill(SS_WEP_AXE, 50);
            set_skill(SS_WEP_POLEARM, 50);
            set_skill(SS_PARRY, 50);
            set_skill(SS_DEFENCE, 50);
            set_skill(SS_UNARM_COMBAT, 50);
            set_skill(SS_BLIND_COMBAT, 100);
            set_skill(SS_AWARENESS, 80);

            MONEY_MAKE(random(10) + 10,"silver")->move(TO,1);

            clone_object(DARM + "chainmail.c")->move(TO,1);
            clone_object(DARM + "cloak.c")->move(TO,1);
            clone_object(DARM + "hood.c")->move(TO,1);
            clone_object(DWEP + "weapon.c")->move(TO,1);

            break;
        case 1:
            set_short("skeleton warrior");
            set_long("The skeleton is covered with shards of "+
                     "decaying flesh, and some of his original "+
                     "armour still covers his now yellow "+
                     "bones. This skeleton looks like a "+
                     "capable fighter.\n");

            set_stats(({80,80,90,50,60,120}));

            set_skill(SS_WEP_SWORD, 75);
            set_skill(SS_WEP_CLUB, 75);
            set_skill(SS_WEP_AXE, 75);
            set_skill(SS_WEP_POLEARM, 75);
            set_skill(SS_PARRY, 75);
            set_skill(SS_DEFENCE, 75);
            set_skill(SS_UNARM_COMBAT, 75);
            set_skill(SS_BLIND_COMBAT, 100);
            set_skill(SS_AWARENESS, 80);

            MONEY_MAKE(random(5),"gold")->move(TO,1);  

            clone_object(DARM + "scalemail.c")->move(TO,1);
            clone_object(DARM + "cloak.c")->move(TO,1);
            clone_object(DARM + "helm.c")->move(TO,1);
            clone_object(DWEP + "weapon.c")->move(TO,1);

            break;

        case 2:
            set_adj("greater");
            set_short("greater skeleton warrior");
            set_long("The skeleton is covered with shards of "+
                     "decaying flesh, and his original "+
                     "armour still covers his now yellow "+
                     "bones. This skeleton must be one "+
                     "of the veteran fighter before being summoned " +
                     "from the grave.\n");

            set_stats(({160,160,130,80,90,180}));

            set_skill(SS_WEP_SWORD, 100);
            set_skill(SS_WEP_CLUB, 100);
            set_skill(SS_WEP_AXE, 100);
            set_skill(SS_WEP_POLEARM, 100);
            set_skill(SS_PARRY, 100);
            set_skill(SS_DEFENCE, 100);
            set_skill(SS_UNARM_COMBAT, 100);
            set_skill(SS_BLIND_COMBAT, 100);
            set_skill(SS_AWARENESS, 80);

            MONEY_MAKE(random(2),"platinum")->move(TO,1);  

            clone_object(DARM + "platemail.c")->move(TO,1);
            clone_object(DARM + "cloak.c")->move(TO,1);
            clone_object(DARM + "fhelm.c")->move(TO,1);
            clone_object(DWEP + "weapon.c")->move(TO,1);

            break;
    }

    set_alignment(-1100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 35000);
    set_aggressive(VBFC_ME("check_aggressive"));

    set_act_time(random(25));
    add_act("emote turns his empty eye sockets towards you.");
    add_act("emote howls: Death to all mortals!");
    add_act("emote inspects his weapon carefully.");
    add_act("scream");
    add_act("cackle");
    add_act("grin");
    add_act("grin");

    set_cact_time(0);
    add_cact("assist");

    command("wield all");
    command("wear all");
}

int
query_option(int opt)
{
    if (opt == OPT_UNARMED_OFF)
    {
        return 1;
    }
    else
    {
        return ::query_option(opt);
    }
}

