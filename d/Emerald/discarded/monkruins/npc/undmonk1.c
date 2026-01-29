/* Undead Monk Initiate - Karath...Opening Day */
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";

#include "/d/Emerald/defs.h"
#include "wa_types.h"

mixed my_equip();

int palm(object enemy);

void
create_emerald_monster()
{
    string *adjs, adj1;

    adjs = ({ "small", "short", "clumsy", "slow", "shuffling" });

    adj1 = adjs[random(sizeof(adjs))];
    set_race_name("monk");
    add_adj(adj1);
    set_gender(2);
    set_short(adj1 + " undead monk");
    set_long("This unfortunate soul seems to be what is left of what was a "+
	"monk initiate in life. Some strange, perhaps evil, power has left "+
	"it caught between life and death. Strips of flesh are falling off "+
	"its limbs, and it gives off a horrid stench.\n");

    set_stats( ({70 + random(20), 70 + random(20), 70 + random(20),
	      10 + random(20), 30 + random(20), 80}) );

    set_skill(SS_UNARM_COMBAT, 50 + random(20));
    set_skill(SS_DEFENCE, 50 + random(20));
    set_skill(SS_BLIND_COMBAT, 50 + random(20));
    set_skill(SS_AWARENESS, 20 + random(20));

    set_alignment(-150 + (random(100)));
    add_prop(LIVE_I_UNDEAD, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_random_move(8);
    set_restrain_path( ({ MONKRUIN_DIR }) );

    set_act_time(6);
    add_act("emote mumbles something that could have resembled speech "+
	"if it had come from a body with lips and a throat.");
    add_act("emote lifts its head to the air as if trying to feel where "+
	"the warmth of life is coming from.");
    add_act("moan strange");
    set_cact_time(3);
    add_cact("moan violent");
    add_cact("emote stares at you with soulless eyes.");
		
    add_equipment(my_equip());
    set_special_attack_percent(15);
    add_special_attack(palm, 100, "palm");
}

mixed
my_equip()
{
    if(random(2))
      return ({ MONKRUIN_DIR + "arm/initrobes", MONKRUIN_DIR +
		 "arm/sandals" });
    return MONKRUIN_DIR + "arm/initrobes";
}

int
palm(object enemy)
{
    mixed* hitresult;
    string how;
    int phurt, mypow;

    mypow = TO->query_skill(SS_UNARM_COMBAT) + TO->query_stat(SS_STR);

    if(2*(random(mypow)/2) < random((enemy->query_skill(SS_DEFENCE)+enemy->query_skill(SS_ACROBAT))))
       {
	TO->catch_msg("You strike out with your palm at your enemy's "+
		"face, but somehow your enemy dodges!\n");
	enemy->catch_msg(QCTNAME(TO) + " suddenly strikes out at " +
		"you with his palm flying towards your face! You "+
		"instinctively dodge, and its fist flies right "+
		"where your chin used to be!\n");
	tell_watcher(QCTNAME(TO) + " suddenly strikes out with " +
		"its palm at "+QTNAME(enemy)+"'s face! "+HE_SHE(enemy)+
		" instinctly dodges "+HIS_HER(enemy)+" head, and "+
		QTNAME(TO)+"'s palm flies just past where "+HIS_HER(enemy)+
		"'s chin used to be!\n", enemy);
	return 1;
    }

    hitresult = enemy->hit_me(mypow, W_BLUDGEON, TO, -1, A_HEAD);

    switch(hitresult[0])
    {
    case 0:
      {
	how = "harmless blow to the cheek";
	break;
      }
    case 1..5:
      {
	how = "glancing blow off the cheekbone";
	break;
      }
    case 6..10:
      {
	how = "solid blow to the brow";
	break;
      }
    case 11..20:
      {
	how = "sharp blow to chin";
	break;
      }
    case 21..40:
      {
	how = "crunching blow to the chin";
	break;
      }
    case 41..80:
      {
	how = "devastating smash on the nose";
	break;
      }
    default:
      {
	how = "deadly impact on the temple";
	break;
      }
    }

   TO->catch_msg("You suddenly strike out with your palm at your enemy's "+
	"head! Your blow scores a " + how + ".\n");
    enemy->catch_msg(QCTNAME(TO) + " suddenly strikes out with its "+
	"palm at your head! Its sudden blow scores a "+how+".\n");
    tell_watcher(QCTNAME(TO) + " suddenly strikes out with its palm "+
	"at "+QTNAME(enemy)+"'s head! Its sudden blow scores a "+
	how+".\n", enemy);

    if (enemy->query_hp() <= 0)
	enemy->do_die(TO);

    return 1; 
}
