// file name:        snake.c
// creator(s):       Lilith, Dec'96
// revision history: 
// purpose:          snake for the holm.
// note:             
// bug(s):           
// to-do:            

#pragma strict_types

#include "/d/Avenir/include/deities.h"
#include "../holm.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/d/Avenir/inherit/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#define S_BITE  TS_HEAD
#define S_BODY  TS_TORSO
#define S_TAIL  (TS_RFOOT | TS_LFOOT)

#define H_HEAD  TS_HEAD
#define H_BODY  TS_TORSO
#define H_TAIL  (TS_RFOOT | TS_LFOOT)

void
create_creature()
{
    string size = ({ "tiny", "small", "large", "average", "huge" })[random(5)],
	   tnt = ({ "brown", "black", "red", "yellow", "gray",
		    "mottled", "white" })[random(7)];

    set_name("snake");
    set_pname("snakes");
    add_name("serpent");
    set_race_name("snake");
    set_gender(G_NEUTER);
    set_adj(size);
    add_adj(tnt);
    set_short(""+ size + " " + tnt + " snake");
    set_long("This snake has " + tnt + "-coloured, scales. "+
             "It is " + size + " in size. You are unsure as "+
             "to whether or not it is poisonous.\n");

    default_config_creature(5 + random(3));

    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_AWARENESS, 40);

//                   'weapon', hit, pen, damage type, %use, desc
    set_attack_unarmed(S_BITE,  10, 40, W_IMPALE,   20, "fangs");
    set_attack_unarmed(S_BODY,  10, 1,  W_BLUDGEON, 20, "body coil");
    set_attack_unarmed(S_TAIL,  10, 15, W_BLUDGEON, 60, "tail");
    set_hitloc_unarmed(H_HEAD, ({ 10 }), 15, "head");
    set_hitloc_unarmed(H_BODY, ({ 10 }), 65, "body");
    set_hitloc_unarmed(H_TAIL,  ({ 10 }), 20, "tail");

    set_alignment(0);

    add_prop(LIVE_I_SEE_DARK, 40);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(ACLOLTHAYR_OFFERING, 1);

    remove_prop(OBJ_M_NO_GET);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_WEIGHT, 1000);
 

    set_cact_time(2);
        add_cact("emote tries to wrap its coils around you.");

    set_act_time(10);
        add_act("emote flicks its forked tongue.");
        add_act("emote stares unblinkingly at you.");
        add_act("emote adjusts its coils.");
}

void
react_meet(object tp)
{
    if (present(tp, environment(TO)) && random(10))
        TO->move(tp);
}

void
init_living()
{
    ::init_living();

    if (interactive(TP))
	set_alarm(2.0, 0.0, &react_meet(TP));
}  

public int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if (aid == S_BITE)
       tell_object(enemy, "The snake sinks its fangs into you!");

   return 0;
}
