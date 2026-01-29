#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE

string *gAdj1 = ({"burly","sullen","warty","rough",
  "mean","grim","toothless","ugly",
  "huge","scarred","nasty","black-eyed","bald","one-legged"});

#define WEP1 "/d/Ansalon/common/wep/sword/sabre"
#define WEP2 "/d/Ansalon/common/wep/sword/cutlass1"
#define WEP3 "/d/Ansalon/kalaman/obj/weapon/w_tessto"
#define FARM "/d/Ansalon/balifor/flotsam/obj/armour/"

#define PEARL "/d/Genesis/gems/obj/pearl"
#define sX random(100)

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("slaver");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " ogre slaver");
    set_race_name("ogre");
    set_long("This mean looking ogre is one of the crew on this slaving ship. " +
       "While he looks adequate in his sailing ability, you are sure that his knowledge " +
       "of keeping his slaves in line is second to none.\n");
    set_stats(({100 +sX,50 + sX,100 + sX,sX,sX,50 + sX}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 50 + (sX / 2));
    set_skill(SS_WEP_SWORD, 50 + (sX / 2));
    set_skill(SS_WEP_AXE, 50 + (sX / 2));
    set_skill(SS_DEFENCE, 30 + (sX / 2));
    set_skill(SS_PARRY, 30 + (sX / 2));

    set_all_hitloc_unarmed(25);
    set_alignment(-600);
    set_all_hitloc_unarmed(20); 


    set_act_time(0);
    add_act("scowl");
    add_act("emote tightens a rope at the commands of his " +
      "captain.");
    add_act("say Can I whip the slaves some more, Captain?");
    add_act("emote looks at the slaves malevolently.");
    add_act("spit");
    add_act("emote stretches his huge body.");
    add_act("twinkle danger");

}

void
arm_me()
{
    int weapon = random(3);
    seteuid(getuid(TO));

    if(weapon == 0)
	clone_object(WEP1)->move(TO,1);
    if(weapon == 1)
	clone_object(WEP2)->move(TO,1);
    if(weapon == 2)
	clone_object(WEP3)->move(TO,1);
    command("wield all");
    clone_object(FARM + "bandana4")->move(TO,1);
    command("wear all");
    if(random(5) == 1)
	clone_object(PEARL)->move(this_object(), 1);
}
