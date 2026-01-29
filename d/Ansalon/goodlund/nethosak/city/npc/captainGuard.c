#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <options.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

inherit "/d/Ansalon/std/monster";
inherit AUTO_TEAM

void
create_krynn_monster()
{
    set_name("scurn");
    set_adj("towering");
    add_adj("scarred");  
    set_living_name("scurn");
    set_race_name("minotaur");
    set_title("the Captain of the Imperial Guards");
    set_short("towering scarred minotaur");
    add_name("captain");
    set_long("This is one of the minotaurs on the Island of Mithas. "+
             "It's extremely tall almost seven feet in height, short "+
             "fur covers his massive body and a thin fuzz hides their "+
             "faces and covers their forearms. It's bullish face is "+
             "brutish and ugly, with a broad snout and wide-set eyes. "+
             "It has long, wide hands with thick fingers ending in short "+
             "claws. This minotaur is especially muscular, perhaps it's "+
             "one of the guards that protect the village.\n"+
             "He wear the tabard of the Captain of the Imperial Guards.\n");

    set_stats(({180,200,190,89,89,110}));
    set_alignment(-100);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000);
    set_introduce(1);
  
    add_prop("_ranger_m_not_disarm", 1);
    set_act_time(0);
    add_act("assist");
    add_act("close door");
 
    // Set skills.
    set_skill(SS_WEP_AXE, 110);
    set_skill(SS_WEP_SWORD, 110);
    set_skill(SS_WEP_CLUB, 110);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 100);

    MONEY_MAKE(random(15),"platinum")->move(this_object(),1);
    clone_object(MWEP + "crystalAxe.c")->move(this_object(),1);
    clone_object(MWEP + "stunAxe.c")->move(this_object(),1);
    clone_object(MARM + "harness.c")->move(this_object(),1);
    clone_object(MARM + "skirt.c")->move(this_object(),1); 
    clone_object(MARM + "captainsTabard.c")->move(this_object(),1);
    command("wield all");
    command("wear all"); 
    clone_object(MWEP + "side_dagger.c")->move(this_object(),1);

    set_pick_up_team(({"guard"}));
    set_max_team_size_auto_join(6);

}

int
query_option(int opt)
{
    if (opt==OPT_UNARMED_OFF)
    {
        return 1;
    }
    else
    {
        return ::query_option(opt);
    }
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

