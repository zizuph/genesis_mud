/*
 * A tomb dweller
 * based on the LoD guard and the monsters in Mort.'s haunted house
 */

inherit "/d/Terel/sorgum/tomb/dweller_base";
     
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

#define ARM_DIR  SORGUMDIR + "armour/"
#define WEP_DIR  SORGUMDIR + "weapon/"

int berzerked = 0;
int level = 1;

go_berzerk()
{
     set_stats(({100, 80, 80, 80, 80}));
     SET_MAX_HP;

     set_skill(SS_UNARM_COMBAT, 40 + random(10));
     set_skill(SS_DEFENCE, 40 + random(10));
     set_skill(SS_WEP_SWORD, 70 + random(10));
     add_prop(LIVE_I_QUICKNESS, 50);
     ::go_berzerk();
}
     
create_monster()
{

     ::create_monster();
     set_alignment(0);

     set_stats(({90, 70, 70, 70, 70, 70}));
     SET_MAX_HP;

     set_skill(SS_UNARM_COMBAT, 30 + random(10));
     set_skill(SS_DEFENCE, 30 + random(10));
     set_skill(SS_WEP_SWORD, 50 + random(10));

     seq_new("do_first");
     seq_addfirst("do_first", "@@dress_me");
     
}

dress_me()
{
     seteuid(getuid(this_object()));
     MONEY_MAKE_SC(random(10)) -> move(TO);     
     clone_object(ARM_DIR + "dw_helmet1")->move(TO);
     clone_object(ARM_DIR + "dw_shield1")->move(TO);
     clone_object(ARM_DIR + "dw_chainmail1")->move(TO);
     clone_object(ARM_DIR + "dw_boots1")->move(TO);     
     clone_object(WEP_DIR + "dw_sword1")->move(TO);
     command("wield sword");
     command("wear armours");
     command("frown");     
}


int
spell_attack(object me, object enemy)
{
    int poisoned;
    int hitresult;
    string how;
    int damage;
    int delay;

    poisoned = 1;

    hitresult = random(100);

    switch (hitresult) {
    case 40..49:
	how = "scratched and drained of strength";
	break;
    case 50..59:
	how = "slightly hurt and drained of strength";
	break;
    case 60..69:
	how = "hurt and drained of strength";
	break;
    case 70..79:
	how = "hurt quite badly and drained of strength";
	break;
    case 80..89:
	how = "hurt very badly and drained of strength";
	break;
    case 90..99:
	how = "utterly devastated and drained of strength";
	break;
    default:
	how = "hit hard";
	poisoned = 0;
    }
    
    enemy->catch_msg("You were " + how + " by the tomb dweller!\n");
    tell_watcher(QCTNAME(enemy) + " is " + how + " by the tomb dweller!\n",
		 enemy);

    /*    enemy->reduce_hit_point(hitresult);*/
    enemy->hit_me(hitresult, W_BLUDGEON, TO, -1);
    enemy->do_die(me);
	
    if (poisoned)
	enemy->add_tmp_stat(SS_STR, -3, 3);

    delay = 30 + random(20);
    set_alarmv(itof(delay), -1.0, "set_spell_prop", ({me}));
    return 1;
}




