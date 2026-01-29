/* created by Aridor 06/19/93 */


#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"

inherit M_FILE

void
create_krynn_monster()
{
    int i;

    set_name("hobgob");
    set_race_name("hobgoblin");
    set_adj("dirty");
    add_adj("large");

    set_short("dirty large hobgoblin");
    set_long("The hobgoblin is very dirty but he is large and looks threatening.\n");

    set_act_time(1);
    add_act("say I just hope Fluuk will bring some loot today.");
    add_act("say What do YOU want here? This is our place!");
    add_act(({"say Tomorrow it's your turn Kruuk.",
		"say And you better bring home somethin decent!"}));
    add_act("say Everyone should be afraid to take the road through the " +
	    "mountains. But not too much so that there's still victims " +
	    "left for us.");
    add_act("grin");
    add_act("say Hey, ya know tomorrow we get another payment. But only " +
	    "if we do as ordered. You know what that means gang!");
    add_act("say Darn, cut out that playing will ya!");
    set_cact_time(2);
    add_cact("say Get out of here!");
    add_cact("say I'm going to have to kill you slowly.");
    add_ask(({"about thieves","thieves","thief","about thief"}),
	    "say Hey, I don't know whatcha talking about. I ain't never seen " +
	    "no thief around here.",1);
    add_ask(({"about palanthas","palanthas"}),
	    "say Blasted city. We wanna get our share of the riches, too.",1);

    for(i=0; i<6; i++)
        set_base_stat(i, 50 + random(20));
    set_skill(SS_DEFENCE, 40 + random(10));
    set_skill(SS_WEP_SWORD, 30 + random(40));

    set_alignment(-150);
    set_knight_prestige(200);

    NEVERKNOWN;

    set_all_attack_unarmed(30, 40);
    set_all_hitloc_unarmed(30);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(OBJ + "orc_sword")->move(TO);
    MONEY_MAKE_CC(random(600) + 10)->move(TO);
    command("wield all");
}
