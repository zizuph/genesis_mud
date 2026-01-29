inherit "/std/monster";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>

object club;
void arm_me();

create_monster() {
    set_name("rocky");
    set_short("Strange looking rock-troll");
    set_race_name("troll");
    set_long(
	"This is an evil looking troll, not as large as those in Hollin but about 9 feet tall (3 meters) "+
	"He is awesome in power with a tough, scaly hide. He is very primitive "+
	"with only his club as weapon, and no armour. He is big and slow.\n");
    add_prop(CONT_I_WEIGHT, 677*1000);
    add_prop(CONT_I_HEIGHT, 300);
    set_stats( ({ 300, 300, 10, 10, 10, 200 }) );
    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_WEP_SWORD,    60);
    set_skill(SS_WEP_AXE,      30);
    set_skill(SS_WEP_CLUB,     50);
    set_skill(SS_DEFENCE,      25);
    set_skill(SS_PARRY,        10);
    set_pick_up(20);
    set_attack_chance(30);
    set_title("the stuff nosed, first boxer of the Trollshaws");
    set_alignment(-280-random(200));
    set_act_time(1);
    add_act("shout Pig iv dun fjaert","fart");
    add_act("shout Ig huta sola");
    add_act("spit");
    add_act("fart");
    add_act("emote examins your nostrels with great care.");
    add_act("emote headbutts your nose, it seems rather shaken by the experience!");
    add_act(({"scream", "laugh"}));
    add_act("say Argh! Wanna see some action!??");
    add_act("emote slaps you HARD!!!");

    set_cact_time(2);
    add_cact("emote jumps around you swinging his arms.");
    add_cact("shout You loose buba!");
    add_cact("say I am gonna rip your heart out and shit down your throat!!!");
    add_cact("shout Dinner coming in a FEW swings!!");
    add_cact("shout I am so scared i might wimp, NOT!!!");
    add_cact("laugh");
   set_alarm(2.0,0.0, &arm_me());
}

arm_me()
{
    if(!club || !present(club, this_object()))
    {
	club = clone_object(STAND_WEAPON+"stoneclub");
	club ->move(this_object());
	command("wield club");
    }

    command("shout HAHAHAHA! I'll suck your brains out looser!!");
    command("duh");
    command("scream");

/*reset_monster()*/

}
