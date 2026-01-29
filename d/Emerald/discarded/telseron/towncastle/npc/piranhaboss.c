/* towncastle/npc/piranhaboss.c is cloned by towncastle/moat.c */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/attack";
 
#include <ss_types.h>
#include <wa_types.h>
#include "../default.h"
 
#define	A_BITE	0
 
#define	H_BODY	0
 
void
create_creature()
{
    set_name("piranha");
    set_race_name("piranha");
    add_adj("hungry");
    set_long("You don't think you've ever seen that sharp teeth before!\n");
 
    set_stats( ({ 10, 150, 8, 5, 10, 150 }) );
 
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_SWIM, 100);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 1200);
    add_prop(CONT_I_VOLUME, 1200);
 
    set_attack_unarmed(A_BITE, 100, 30, W_IMPALE, 15, "jaws");
 
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 100, "body");
 
    set_aggressive(1);
 
    set_random_move(5);
    set_restrain_path(TCASTLE_DIR + "moat");
    set_monster_home(TCASTLE_DIR + "moat6");
}
