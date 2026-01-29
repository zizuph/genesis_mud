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
inherit "/lib/unique"; 

#define A_CLAW  0
#define A_BITE 1

#define H_BODY 0
#define H_WING 1
#define H_HEAD 2

int amulet_used = 1;

create_krynn_monster() 
{

    if (!IS_CLONE)
	return;
    set_name("nyctimene");
    set_living_name("nyctimene");
    set_title("of the Furies, Queen of the Harpies");
    add_name("queen");
    set_race_name("harpy");
    set_short("harpy queen");
    set_long("Hovering before you is a monster that is often the nightmare tale " +
      "of sailors of the Bloodsea, the harpy! With the head and torso of a beautiful " +
      "woman, the rest of its body is that of a giant vulture. Rumour has it these " +
      "creatures have a poisonous bite, and this particular one looks larger and more " +
      "regal than stories would have you believe!\n");

    set_gender(G_FEMALE);
    set_stats(({ 130,200,170,145,145,147 }));
    /* str, dex, con, int, wis, dis */

    set_skill(SS_DEFENCE, 100);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 700000);
    add_prop(OBJ_I_VOLUME, 450000);
    add_prop(OBJ_I_NO_INS, 1);
    set_aggressive(1);
    set_exp_factor(110); 
    set_alignment(-800);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE, 20, 25, W_SLASH, 10, "poisonous bite");
    set_attack_unarmed(A_CLAW, 55, 50, W_IMPALE, 90, "talons");

    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_BODY, ({ 50, 45, 45 }), 60, "body");
    set_hitloc_unarmed(H_WING, ({ 30, 40, 20 }), 30, "wings");
    set_hitloc_unarmed(H_HEAD, ({ 10, 10, 20 }), 10, "head");

    set_act_time(10);
    add_act("emote shrieks shrilly.");
    add_act("emote flies up into the air, and then shrieks as she dives at you!");
    add_act("emote circles around the edge of the tower, and then swoops at you, " +
            "talons gleaming dangerously!");
    add_act("say I will feast on your flesh, mannling!");
    add_act("emote beats the air with her wings in agitation.");

    seteuid(getuid());
    clone_unique(BOBJ + "storm_amulet", 10)->move(TO);
    clone_object("/d/Krynn/common/scrolls/reflect_damage_scroll")->move(TO);
    command("wear all");


}

void
return_intro()
{
    command("introduce myself");
}
 
void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
        set_alarm(1.0, 0.0, return_intro);
    }
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;

    if(aid==A_BITE) 
    {
	tell_watcher("The queen of the harpies bites " + QTNAME(enemy) + " deeply " + 
	  "with her poisonous fangs.\n", enemy);
	tell_object(enemy, "The queen of the harpies bites you deeply with " +
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

int
special_attack(object ob)
{

 
    if((random(5) == 1) && (TO->query_hp() < 500) && amulet_used)
    {
        command("grasp amulet");
        amulet_used = 0;
        return 1;
    }
    return 0;
}
