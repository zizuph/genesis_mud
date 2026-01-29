inherit "/std/monster";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Shire/common/make_money.h"

object club;

create_monster() {
    set_name("smock");
    set_short("nasty looking rock-troll");
    set_race_name("troll");
    set_long(
	"This is an evil looking troll, not as large as those in Hollin but about 9 feet tall (3 meters). "+
	"He is awesome in power with a tough, scaly hide. He is very primitive "+
	"with his only weapon a club, and no armour. He is big and slow. "+
	"His eyes are big and round as plates, shining black as he stares at you. "+
	"His feet looks like they are made for stamping on small creatures, like you!!\n");
    add_prop(CONT_I_WEIGHT, 677*1000);
    add_prop(CONT_I_HEIGHT, 300);
    set_stats( ({ 110, 35, 85, 10, 10, 50 }) );
    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 35);
    set_skill(SS_WEP_SWORD,    60);
    set_skill(SS_WEP_AXE,      30);
    set_skill(SS_WEP_CLUB,     69);
    set_skill(SS_DEFENCE,      65);
    set_skill(SS_PARRY,        10);
    set_pick_up(20);
    set_attack_chance(30);
    set_title("the grim, first killer of the Trollshaws");
    set_alignment(-280-random(200));
    MAKE_MONEY;
    make_gold(2);
    
    add_act("emote looks hungrily at you and licks his lips.");
    add_act("burp");
    add_act("grin");
    add_act("emote crushes a huge tree into several pieces " +
        "with his huge club!");
    add_act("growl");
    add_act("nibble all");
    add_act("emote headbutts some big boulders, they crumble " +
        "to dust!!");
    add_act(({"scream", "laugh"}));
    add_act("say Argh! Wanna see some blood!??");
    add_act("emote swings his club around your head.");
 
    set_cact_time(2);
    add_cact("say If you're gonna fight me, make it challenging!");
    add_cact("emote smashes you in the face.");
    add_cact("say I am gonna rip your heart out!");
    add_cact("shout Dinner coming in a FEW blows!!!");
    add_cact("shout I am so scared I might run soon, HAHAHAHAHA!");
    add_cact("laugh");
    add_cact("emote starts to smell the blood from you!!");
    add_cact("emote picks up a tree and throws it after you.");
    call_out("arm_me", 1);
}

arm_me()
{
    if(!club || !present(club, this_object()))
    {
	club = clone_object(STAND_WEAPON+"woodclub");
	club ->move(this_object());
	command("wield club");
    }
    command("shout YEAHH!! Ready for battle, me crush puny humans, eat them raw!");	 
    command("shout HAHAHAHA! I smash your brains out looser!!");
    command("duh");
    command("scream");

/*reset_monster()*/

}
