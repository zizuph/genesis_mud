/* towncastle/npc/piranha.c is cloned by towncastle/moat.c */
inherit "/std/creature";
inherit "/std/combat/unarmed";
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
 
    set_stats( ({ 10, 150, 8, 5, 5, 150 }) );
 
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_SWIM, 100);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_attack_unarmed(A_BITE, 100, 30, W_IMPALE, 15, "jaws");
 
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 100, "body");
    
    heal_hp(query_max_hp());
 
    set_aggressive(1);
}
