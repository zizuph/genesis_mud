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
    set_short("filthy hobgoblin");
    set_adj("filthy");
    add_adj("killer");

    set_long("The hobgoblin is very filthy and dirty.\n");

    set_act_time(2);
    add_act("say I got a 4. Damn, another copper lost.");
    add_act(({"cheer","say 12! Yes! Gimme that silver!"}));
    add_act("say Cheater! I'll teach you some manners!");
    add_act("poke hobgoblins");
    add_act("say Shhhhh, quiet.");
    add_act("say Yea, what DO you want here?");
    add_act("grin mercilessly");
    add_act("say Well, I just hope the city guards of Palanthas never find " +
	    "this place. We'd be dead meat then.");
    add_act("say Leave while ya still can.");
    set_cact_time(3);
    add_cact("say You don't belong here!");
    add_cact("say Misbegotten orphan of a gully dwarf!");

    add_ask(({"about thieves","thieves","thief","about thief"}),
	    "say Hey, we are no thieves. Everyone has to earn his living, " +
	    "ya know! I don't even know how to spell that word!",1);
    add_ask(({"about palanthas","palanthas"}),
	    "say Hehe, Fluuk is al.... rrarrgrr lemme go!",1);

    for(i=0; i<6; i++)
        set_base_stat(i, 30 + random(20));
    set_skill(SS_DEFENCE, 40 + random(10));
    set_skill(SS_WEP_SWORD, 30 + random(20));
    set_skill(SS_WEP_KNIFE, 30 + random(20));
    set_skill(SS_WEP_CLUB, 30 + random(20));

    set_alignment(-150);
    set_knight_prestige(100);

    NEVERKNOWN;

    set_all_attack_unarmed(10, 20);
    set_all_hitloc_unarmed(10);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    object wep;
    seteuid(getuid(TO));
    if (random(2))
      clone_object(HOBGOBLIN_KNIFE)->move(TO);
    else
      {
	  wep = clone_object(HOBGOBLIN_CLUB);
	  wep->set_long("It's a standard army mace.");
	  wep->move(TO);
      }
    MONEY_MAKE_CC(random(3) + 30)->move(TO);
    command("wield all");
}
