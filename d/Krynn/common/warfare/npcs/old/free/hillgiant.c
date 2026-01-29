/* Ashlar, 3 Jul 97 - A Hill Giant */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit AC_FILE

string *gAdj1 = ({ "towering", "huge", "immense", "powerful",
            "hulking", "muscular" }),
       *gAdj2 = ({ "beastly", "cruel", "daunting", "fearsome",
            "evil", "frightening" });
    

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif


void
create_creature()
{
    if(!IS_CLONE)
	return;

    set_name("giant");
    
    set_race_name("giant");

    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));

    set_short(implode(query_adjs()," ") + " hill giant");
    add_adj("hill");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("A huge humanoid creature, a hill giant is not very bright " +
        "but what it lacks in thought it makes up for in brute force. " +
        "This formidable killing machine is no-one you want to mess with!\n");

    add_prop(CONT_I_HEIGHT, 600);
    add_prop(CONT_I_WEIGHT, 550000);
    add_prop(CONT_I_VOLUME, 450000);

    set_stats(({300,85,220,45,60,165}));
    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY, 30);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 40);

    set_hitloc_unarmed(1, 25, 17, "left thigh");
    set_hitloc_unarmed(2, 25, 17, "right thigh");
    set_hitloc_unarmed(3, 35, 20, "left shin");
    set_hitloc_unarmed(4, 35, 20, "right shin");
    set_hitloc_unarmed(5, 25,  6, "abdomen");
    set_hitloc_unarmed(6, 35, 15, "left foot");
    set_hitloc_unarmed(7, 35, 15, "right foot");

    set_attack_unarmed(1, 45, 50, W_BLUDGEON, 20, "left foot");
    set_attack_unarmed(2, 45, 50, W_BLUDGEON, 30, "right foot");
    set_attack_unarmed(3, 75, 35, W_BLUDGEON, 20, "left fist");
    set_attack_unarmed(4, 75, 35, W_BLUDGEON, 30, "right fist");

    set_alignment(-600);
    set_knight_prestige(600);

    ::create_creature();
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen;

    mixed hitres;

    string *how;

    attacktype = random(5);

    if (attacktype == 0)
    {
	    hitres = enemy->hit_me(500, W_BLUDGEON, TO, -1);

        how = ({ QCTNAME(TO) + " tries to step on you, but you jump " +
            "aside.",
            QCTNAME(TO) + " tries to step on " + QTNAME(enemy) +
            ", but " + HE(enemy) + " jumps aside."});
	            
	    if(hitres[0] > 0)
	        how = ({ QCTNAME(TO) + " treads on you, lightly.",
	            QCTNAME(TO) + " treads on " + QTNAME(enemy) + ", lightly." });
                
	    if(hitres[0] > 7)
	        how = ({ QCTNAME(TO) + " steps down on you, hard.",
	            QCTNAME(TO) + " steps down on " + QTNAME(enemy) +
	            ", hard." });

	    if(hitres[0] > 18)
            how = ({ QCTNAME(TO) + " crushes you against the ground " +
                "with his foot.",
                QCTNAME(TO) + " crushes " + QTNAME(enemy) + " against the " +
                "ground with his foot." });
	    
	    if (hitres[0] > 37)
	        how = ({ QCTNAME(TO) + " crushes you with his foot, grinding " +
	            "body into the ground.",
	            QCTNAME(TO) + " crushes " + QTNAME(enemy) + " with his foot, " +
	            "grinding the latter into the ground." });

        if (hitres[0] > 99)
            how = ({ "Putting all his weight behind it, " + QTNAME(TO) +
                "puts his immense foot over you, crushing you against " +
                "the ground. The last thing you feel is your bones " +
                "snapping under the pressure...",
                "Putting all his weight behind it, " + QTNAME(TO) +
                "puts his foot over " + QTNAME(enemy) + ", and with " +
                "a bonecrushing sound drives " + HIM(enemy) + " into " +
                "the ground." });

        enemy->catch_msg(how[0] + "\n");
        tell_room(E(TO), how[1] + "\n", enemy);

	    if (enemy->query_hp() <= 0)
	    {
	        enemy->do_die(TO);
	    }

	    return 1;
    }

    return 0;
}