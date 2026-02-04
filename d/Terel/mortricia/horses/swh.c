inherit "/d/Terel/mortricia/horses/horse";

#include <ss_types.h>
#include <wa_types.h>

#define A_BITE  0
#define A_HOOF  1

#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2

public void
create_horse()
{
    set_adj("silver-white");
    set_short("silver-white horse");
    set_horse_long("It looks very strong and agile.");
    set_stats(({ 99, 99, 99, 20, 20, 99 }));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_hp(9999);
    set_mana(9999);
    set_fatigue(9999);
    set_attack_unarmed(A_BITE, 34, 34, W_IMPALE,   20, "teeth");
    set_attack_unarmed(A_HOOF, 45, 45, W_BLUDGEON, 80, "hoofs");
    set_hitloc_unarmed(H_HEAD, ({ 25, 25, 25, 25 }),  5, "head");
    set_hitloc_unarmed(H_BODY, ({ 50, 50, 50, 50 }), 75, "torso");
    set_hitloc_unarmed(H_LEGS, ({ 40, 40, 40, 40 }), 20, "legs");
}
