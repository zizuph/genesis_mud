#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
#include "/d/Gondor/elessar/lib/evilkill.h"
#include <wa_types.h>
#include <ss_types.h>
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
    set_name("wolf"); 
    set_race_name("wolf");
    set_short("white wolf");
    set_pshort("white wolves");
    set_adj(({"white", "hungry" }));
    set_aggressive(1);
    set_attack_chance(95);
    set_long("It looks rather hungry! It has thick, white fur and sharp fangs.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 90, 30, 30, 20, 5, 75}));
    set_hp(1000);

    set_skill(SS_DEFENCE, 17);
    set_skill(SS_UNARM_COMBAT,66);
    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30 }), 80, "body");
}


query_combat_file()
{
  return "/std/combat/cplain";
}
