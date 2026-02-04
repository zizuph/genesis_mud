/*
 * A tomb dweller
 * based on the LoD guard and the monsters in Mort.'s haunted house
 */

inherit "/d/Terel/sorgum/tomb/dweller_base";
inherit "/lib/unique";
     
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
     set_stats(({120, 100, 100, 100, 100}));
     set_hp(7000);

     set_skill(SS_UNARM_COMBAT, 60 + random(10));
     set_skill(SS_DEFENCE, 60 + random(10));
     set_skill(SS_WEP_SWORD, 80 + random(10));
     add_prop(LIVE_I_QUICKNESS, 60);
     ::go_berzerk();
}
     
create_monster()
{

     ::create_monster();
     set_alignment(0);

     set_stats(({100, 80, 80, 80, 80, 80}));
     set_hp(6000);

     set_skill(SS_UNARM_COMBAT, 50 + random(10));
     set_skill(SS_DEFENCE, 50 + random(10));
     set_skill(SS_WEP_SWORD, 70 + random(10));

     seq_new("do_first");
     seq_addfirst("do_first", "@@dress_me");
     
}

dress_me()
{
     seteuid(getuid(this_object()));
     MONEY_MAKE_SC(random(30)) -> move(TO);     
     clone_object(ARM_DIR + "dw_helmet3")->move(TO);
     clone_unique(ARM_DIR + "dw_shield3", 10, ARM_DIR+"dw_shield2")->move(TO);
     clone_object(ARM_DIR + "dw_chainmail3")->move(TO);
     clone_object(ARM_DIR + "dw_greaves3")->move(TO);     
     clone_object(WEP_DIR + "dw_sword3")->move(TO);
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

    hitresult = random(200);

    switch (hitresult) {
    case 40..59:
	how = "scratched and drained of strength";
	break;
    case 60..79:
	how = "slightly hurt and drained of strength";
	break;
    case 80..99:
	how = "hurt and drained of strength";
	break;
    case 100..139:
	how = "hurt quite badly and drained of strength";
	break;
    case 140..179:
	how = "hurt very badly and drained of strength";
	break;
    case 180..199:
	how = "utterly devastated and drained of strength";
	break;
    default:
	how = "hit hard";
	poisoned = 0;
    }

    enemy->catch_msg("You were " + how + " by the tomb dweller!\n");
    tell_watcher(QCTNAME(enemy) + " is " + how + " by the tomb dweller!\n",
		 enemy);

    /*    enemy->reduce_hit_point(hitresult); */
    enemy->hit_me(hitresult, W_BLUDGEON, TO, -1);
    enemy->do_die(me);
	
    if (poisoned)
	enemy->add_tmp_stat(SS_STR, -4, 9);

    delay = 20 + random(20);
    set_alarmv(itof(delay), -1.0, "set_spell_prop", ({me}));	
    dump_pack();
    return 1;
}
