#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

#define WEP1 WEP + "ogre_club"
#define ARM ARMOUR + "ogre_fur"

string *gAdj1 = ({"warty","ugly","grey-skinned",
  "huge","giant","fat","bony"});
string *gAdj2 = ({"cruel","evil","brutal","depraved",
  "harsh","rugged","hungry"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("ogre");
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_race_name("ogre");
    set_long("Standing over nine feet tall, this ugly, " +
      "gray and warty skinned ogre wanders the plains " +
      "looking for easy prey. If you ever needed a definition " +
      "for brutality, depravity or cunning cruelty, one look " +
      "at an ogre would satisfy that need.\n");

    CUTLEFTOVER("hide");

    set_stats(({200,80,190,60,60,100}));
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-450);
    set_knight_prestige(50);

    set_skill(SS_WEP_CLUB, 60);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 30);
    set_skill(SS_AWARENESS, 10);

    set_act_time(10);
    add_act("emote stares across the plains hungrily.");
    add_act("emote growls: Ooomans taste nice, uhnlike " +
      "dem dwarfies! Der too tough on da chops!");
    add_act("scream");
    add_act("emote smells his smelly furs.");

    set_cact_time(0);
    add_cact("assist");
    add_cact("roar");

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    command("wield all");
    clone_object(ARM)->move(TO,1);
    command("wear all");

}
