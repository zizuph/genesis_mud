inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "defs.h"
 
#define A_CLAWS 0
#define A_TEETH 1
 
#define H_HEAD 0
#define H_BODY 1
 
void
create_creature()
{
    set_name(({"the small wolf","small wolf","timberwolf","wolf"}));
    set_short("small timberwolf");
    set_pshort("small timberwolves");
    set_race_name("timberwolf");
    set_adj(({"small","dark"}));
    set_long(BS(
        "A small timberwolf common in these woods.  He is very small, " +
        "but his teeth look very sharp.  He stares at you with evil "   +
        "yellow eyes.\n"));
 
    set_stats(({ 10, 10, 10, 10, 10, 10}));
 
    set_hp(3000);
 
    set_skill(SS_DEFENCE, 10);
 
    set_attack_unarmed(A_CLAWS, 10, 10, W_SLASH, 10, "claws");
    set_attack_unarmed(A_TEETH, 10, 10, W_SLASH, 10, "sharp teeth");
 
    set_hitloc_unarmed(H_HEAD, ({10, 10, 10, 10 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10, 10, 10, 10 }), 80, "body");
 
    set_alignment(-300);
    set_act_time(10);
    add_act("emote looks you over hungrily.");
    add_act("emote glares at you with his evil yellow eyes.");
    add_act("emote howls into the forest.");
    add_act("emote growls lowly.");
    add_act("emote hunches near the ground, ready to attack.");
    add_act("east");
    add_act("west");
 
}
