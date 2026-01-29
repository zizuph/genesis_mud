#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#define A_CLAW  0
#define A_BITE 1

#define H_BODY 0
#define H_WING 1
#define H_HEAD 2

string *gAdj1 = ({"malevolent","vicious","sly","aggressive",
  "curious","beautiful","fanged","fair","savage","cruel","sadistic"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

create_krynn_monster() 
{

    if (!IS_CLONE)
	return;
    set_name("harpy");
    set_adj(ONE_OF(gAdj1));
    set_race_name("harpy");
    set_short(implode(query_adjs()," ") + " harpy"); 
    set_long("Hovering before you is a monster that is often the nightmare tale " +
      "of sailors of the Bloodsea, the harpy! With the head and torso of a beautiful " +
      "woman, the rest of its body is that of a giant vulture. Rumour has it these " +
      "creatures have a poisonous bite.\n");

    set_gender(G_FEMALE);
    set_stats(({ 80,150,120,100,100,100 }));
    /* str, dex, con, int, wis, dis */

    set_skill(SS_DEFENCE, 70);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 700000);
    add_prop(OBJ_I_VOLUME, 450000);
    add_prop(OBJ_I_NO_INS, 1);
    set_aggressive(1);
    set_exp_factor(105); 
    set_alignment(-600);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE, 15, 25, W_SLASH, 10, "poisonous bite");
    set_attack_unarmed(A_CLAW, 45, 40, W_IMPALE, 90, "talons");

    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_BODY, ({ 40, 35, 35 }), 60, "body");
    set_hitloc_unarmed(H_WING, ({ 20, 30, 20 }), 30, "wings");
    set_hitloc_unarmed(H_HEAD, ({ 5, 5, 10 }), 10, "head");

    set_act_time(10);
    add_act("emote shrieks shrilly.");
    add_act("emote flies up into the air, and then shrieks as she dives at you!");
    add_act("emote circles around the edge of the tower, and then swoops at you, " +
            "talons gleaming dangerously!");
    add_act("say I will feast on your flesh, mannling!");
    add_act("emote beats the air with her wings in agitation.");

}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;

    if(aid==A_BITE) 
    {
	tell_watcher("The harpy bites " + QTNAME(enemy) + " deeply " + 
	  "with her poisonous fangs.\n",enemy);
	tell_object(enemy, "The harpy bites you deeply with " +
           "her poisonous fangs.\n");

        poison = clone_object("/std/poison_effect");
	if(poison) 
        {
	poison->move(enemy);
	poison->set_time(200);
	poison->set_short("harpy poison");
	poison->set_interval(40);
	poison->set_strength(40);
	poison->set_damage(({POISON_HP, 100}));
  	poison->start_poison();
	}
    }
    return 0;
}