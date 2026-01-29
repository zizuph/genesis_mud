/* Undead Monk Initiate - Karath...Opening Day */
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";

#include "/d/Emerald/defs.h"
#include "wa_types.h"

mixed my_equip();

int palm(object enemy);
int sidekick(object enemy);

void
create_emerald_monster()
{
    string *adjs, adj1;

    adjs = ({ "strong", "growling", "repulsive", "lumbering" });

    adj1 = adjs[random(sizeof(adjs))];
    set_race_name("monk");
    add_adj(adj1);
    set_gender(2);
    set_short(adj1 + " undead monk");
    set_long("This unfortunate soul seems to be what is left of what was a "+
	"monk of the abbey in life. Some strange, perhaps evil, power has "+
	"left it caught between life and death. Strips of flesh are falling "+
	"off its limbs, revealing a strangely intact muscle structure "+
	"underneath, and it gives off a horrid stench.\n");

    set_stats( ({90 + random(20), 90 + random(20), 90 + random(20),
	      10 + random(20), 30 + random(20), 100}) );

    set_skill(SS_UNARM_COMBAT, 70 + random(20));
    set_skill(SS_DEFENCE, 70 + random(20));
    set_skill(SS_BLIND_COMBAT, 70 + random(20));
    set_skill(SS_AWARENESS, 30 + random(20));

    set_alignment(-150 + (random(100)));
    add_prop(LIVE_I_UNDEAD, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_random_move(8);
    set_restrain_path( ({ MONKRUIN_DIR }) );

    set_act_time(6);
    add_act("emote mumbles something that could have resembled speech "+
	"if it had come from a body with lips and a throat.");
    add_act("emote lifts its head to the air as if trying to feel "+
	"where the warmth of life is coming from.");
    add_act("moan strange");
    set_cact_time(3);
    add_cact("moan violent");
    add_cact("emote stares at you with soulless eyes.");
		
    add_equipment(my_equip());
    set_special_attack_percent(20);
    add_special_attack(palm, 50, "palm");
    add_special_attack(sidekick, 50, "sidekick");
}

mixed
my_equip()
{
    if(random(2))
      return ({ MONKRUIN_DIR + "arm/monkrobes", MONKRUIN_DIR +
		 "arm/sandals", MONKRUIN_DIR + "arm/fistwrap" });
    return ({ MONKRUIN_DIR + "arm/initrobes", MONKRUIN_DIR + "arm/fistwrap" });
}

int sidekick(object enemy)
{
    string how;

    int delay;

    int success = ((3 * (random(query_stat(SS_STR) + query_skill(SS_UNARM_COMBAT))/3)) - (random(enemy->query_skill(SS_DEFENCE) + enemy->query_skill(SS_ACROBAT))));

    if (success < 1) 
    {
	this_object()->catch_msg("You unleash a snapkick at your "+
		"opponent's leg, but the enemy steps back!\n");
	enemy->catch_msg(QCTNAME(TO) + " unleashes a powerful snapkick "+
		"at your leg, but you step back a bit and its foot "+
		"swings harmlessly in front of you!\n");
	tell_watcher(QCTNAME(TO) + " unleashes a powerful snapkick "+
		"at "+QTNAME(enemy)+"'s leg, but "+HE_SHE(enemy)+
		"steps back, and "+QTNAME(TO)+"'s foot swings harmlessly "+
		"in front of "+HIM_HER(enemy)+"!\n", enemy);
	return 1;
    }

    switch (success)
      {
    case 1..19:
	how = "slight thump on the outside thigh";
	delay = 2;
	break;
    case 20..39:
	how = "glancing blow on the inner thigh";
	delay = 4;
	break;
    case 40..59:
	how = "solid blow on the upper thigh";
	delay = 6;
	break;
    case 60..79:
	how = "pounding blow on the front thigh";
	delay = 8;
	break;
    default: 
	how = "resounding pummel on the outside knee";
	delay = 12;
	break;
      }
	TO->catch_msg("You unleash a snapkick at your "+
		"opponent's leg, landing your foot with " + how +
		" of "+QTNAME(enemy)+", causing "+HIM_HER(enemy)+
		" to step back wincing, holding back attacks for "+
		"a while.\n");
	enemy->catch_msg(QCTNAME(TO) + " unleashes a powerful snapkick "+
		"at your leg, landing its foot with a "+how+"."+
		" You step back, wincing and holding back attacks "+
		"for a moment while the pain subsides.\n");
	tell_watcher(QCTNAME(TO) + " unleashes a powerful snapkick "+
		"at "+QTNAME(enemy)+"'s leg, landing its foot with a "+
		how+". "+CAP(HE_SHE(enemy))+" steps back, wincing and "+
		"holding back attacks for a moment while the pain subsides"+
		".\n", enemy);

    enemy->add_attack_delay(delay, 1);

    return 1;
}

int
palm(object enemy)
{
    mixed* hitresult;
    string how;
    int mypow;

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
