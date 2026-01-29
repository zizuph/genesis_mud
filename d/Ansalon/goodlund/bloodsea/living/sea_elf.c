#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit "/std/act/action";

inherit AM_FILE

string *gAdj1 = ({"green-eyed","wide-eyed","webbed-fingered",
          "purple-haired","green-haired"});

#define FOBJ "/d/Ansalon/balifor/flotsam/obj/"
#define WEP FOBJ + "weapon/spear"
#define WEP2 BOBJ + "trident"
#define ARM FOBJ + "armour/sskin"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("sea-elf");
    add_name("elf");
    add_name("sea elf");
    set_race_name("sea-elf");
    set_adj("blue-skinned");
    set_adj(ONE_OF(gAdj1));
    set_gender(random(2));
    set_long("This blue-skinned elf with brilliant green eyes " +
      "is a creature of legends and childhood tales, a sea elf! "+
      "Rumour has it that sea-elves are generally very reclusive " +
      "around air breathers.\n");
    set_stats(({86 +random(40),110 +random(40),88 +random(40),90,88, 100+random(40)}));
    set_hp(10000);

    set_alignment(800);
    set_knight_prestige(-1);
    set_all_hitloc_unarmed(20); 

    set_skill(SS_WEP_POLEARM, 75 + random(20));
    set_skill(SS_DEFENCE, 80 + random(20));
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_PARRY, 75 + random(20));
    set_skill(SS_AWARENESS, 85);

    set_act_time(15);
    add_act("emote swims playfully around the sea kelp.");
    add_act("emote bubbles: Be careful of the sunken cathedral, a nasty " +
      "sea hag lives there!");
    add_act("emote bubbles: Another vessel was lost at sea during the " +
      "last storm.");
    add_act("emote bubbles: Rumours speak of the return of the sea dragons.");

    set_default_answer("The sea elf indicates he doesn't know the answer to your question.\n");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    if(random(2))
    {
       clone_object(WEP)->move(this_object(),1);
       clone_object(WEP)->move(this_object(),1);
    }
    else
       clone_object(WEP2)->move(this_object(),1);
    command("wield all");
    clone_object(ARM)->move(this_object(),1);
    command("wear all");
}


