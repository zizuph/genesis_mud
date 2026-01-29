/* Minotaur for Nethosak in Mithas
 * Elmore, 28/4/00 
 * made to inherit the minotaur_base by Aridor, 10/94
 */ 
#include <options.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

inherit "/d/Krynn/common/monster/minotaur_base";
#include "/d/Ansalon/common/defs.h";
string face();

void
create_minotaur()
{
    set_race_name("minotaur"); 
    set_name(({"minotaur", "guard", }));
    set_adj(face()); 
    add_adj("hairy"); 
    set_short(face() + " hairy minotaur");
    set_long("This is one of the minotaurs on the Island of Mithas. "+
             "It's extremely tall almost seven feet in height, short "+
             "fur covers his massive body and a thin fuzz hides their "+
             "faces and covers their forearms. It's bullish face is "+
             "brutish and ugly, with a broad snout and wide-set eyes. "+
             "It has long, wide hands with thick fingers ending in short "+
             "claws. This minotaur is especially muscular, perhaps it's "+
             "one of the guards that protect the village.\n");
    
    set_stats(({150,90,100,80,50,120}));
    set_alignment(random(50)-25);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000);
    
    set_act_time(5);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("assist");

    set_cact_time(1);
    add_act("assist");
 
    // Set skills.
    set_skill(SS_WEP_AXE, 80); 
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 60);
    MONEY_MAKE(random(20) + 10,"silver")->move(this_object(),1); 

   switch (random(3))
   {
      case 0:
      clone_object("/d/Ansalon/kalaman/obj/weapon/w_tessto.c")->
      move(this_object(),1);
      break;

      case 1:
      clone_object(MWEP + "minotaurAxe.c")->move(this_object(),1);
      break;

      case 2:
      clone_object(MWEP + "flamberge1.c")->move(this_object(),1);
      break;
    }
    clone_object(MARM + "harness.c")->move(this_object(),1);
    clone_object(MARM + "skirt.c")->move(this_object(),1);
    clone_object(MARM + "tabard.c")->move(this_object(),1);
    clone_object(MARM + "belt.c")->move(this_object(),1);
    command("wield all");
    command("wear all");
    clone_object(MWEP + "side_dagger.c")->move(this_object(),1); 
}

string
face()
{
    // Set description.
    string *faces;
    faces = ({"titanic", "big", "huge", "muscular", "brutal"});
    return faces[random(sizeof(faces))];
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


