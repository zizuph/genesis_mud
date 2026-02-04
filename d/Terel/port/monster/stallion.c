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
    set_short("silver-white stallion");
    add_name("stallion");
    set_horse_long("This silver-white stallion looks strong and agile.");
    set_gender(0);
    set_stats(({ 69, 69, 60, 50, 50, 60 }));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_hp(9999);
    set_mana(9999);
    set_attack_unarmed(A_BITE, 24, 24, W_IMPALE,   20, "teeth");
    set_attack_unarmed(A_HOOF, 35, 30, W_BLUDGEON, 80, "hoofs");
    set_hitloc_unarmed(H_HEAD, ({ 15, 15, 15, 15 }),  5, "head");
    set_hitloc_unarmed(H_BODY, ({ 40, 40, 40, 40 }), 75, "torso");
    set_hitloc_unarmed(H_LEGS, ({ 30, 30, 30, 30 }), 20, "legs");
}
