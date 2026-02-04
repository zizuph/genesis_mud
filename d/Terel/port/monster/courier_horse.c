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
    set_adj("grey");
    set_short("grey horse");
    set_horse_long("It is a grey horse. It looks strong and swift.");
    set_stats(({ 59, 59, 59, 49, 49, 59 }));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_hp(9999);
    set_mana(9999);
    set_attack_unarmed(A_BITE, 24, 24, W_IMPALE,   20, "teeth");
    set_attack_unarmed(A_HOOF, 35, 35, W_BLUDGEON, 80, "hoofs");
    set_hitloc_unarmed(H_HEAD, ({ 19, 19, 19, 19 }),  5, "head");
    set_hitloc_unarmed(H_BODY, ({ 42, 42, 42, 42 }), 75, "torso");
    set_hitloc_unarmed(H_LEGS, ({ 34, 34, 34, 34 }), 20, "legs");
}
