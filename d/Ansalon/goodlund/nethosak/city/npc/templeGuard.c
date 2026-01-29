#include <options.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

inherit "/d/Krynn/common/monster/minotaur_base";
#include "/d/Ansalon/common/defs.h";

void
create_minotaur()
{ 
    set_race_name("minotaur"); 
    set_name(({"minotaur", "guard"}));
    set_adj("powerful");
    add_adj("robed"); 
    set_short("powerful robed minotaur");
    set_long("This is one of the minotaurs on the Island of Mithas. "+
             "It's extremely tall almost seven feet in height, short "+
             "fur covers his massive body and a thin fuzz hides their "+
             "faces and covers their forearms. It's bullish face is "+
             "brutish and ugly, with a broad snout and wide-set eyes. "+
             "It has long, wide hands with thick fingers ending in short "+
             "claws. This minotaur is especially muscular, he is dressed "+
             "in a black robed and is wielding a huge weapon and wearing "+
             "excellent armour.\n"+
             "He is a temple guard.\n");
    
    set_stats(({190,160,170,120,90,120}));
    set_alignment(random(50)-25);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000);
    
    set_act_time(5);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
 
    // Set skills.
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80); 
    set_skill(SS_2H_COMBAT, 120);

    MONEY_MAKE(random(20) + 10,"silver")->move(this_object(),1);
    MONEY_MAKE(random(20) + 10,"gold")->move(this_object(),1);
    clone_object(MWEP + "runedAxe.c")->move(this_object(),1); 
    clone_object(MWEP + "runedAxe.c")->move(this_object(),1);
    clone_object(MARM + "bandedmail.c")->move(this_object(),1);
    clone_object(MARM + "silverrobe.c")->move(this_object(),1);
    command("wield all");
    command("wear all");

}

