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
    set_adj(({"nervous", "black"}));
    set_short("nervous black stallion");
    add_name("stallion");
    set_horse_long("This black stallion looks rather nervous.\n");
    set_gender(0);
    set_stats(({ 42, 50, 63, 40, 40, 23 }));
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_AWARENESS, 40);
    set_hp(9999);
    set_mana(9999);
    set_attack_unarmed(A_BITE, 24, 24, W_IMPALE,   20, "teeth");
    set_attack_unarmed(A_HOOF, 35, 30, W_BLUDGEON, 80, "hoofs");
    set_hitloc_unarmed(H_HEAD, ({ 15, 15, 15, 15 }),  5, "head");
    set_hitloc_unarmed(H_BODY, ({ 30, 30, 30, 30 }), 75, "torso");
    set_hitloc_unarmed(H_LEGS, ({ 25, 25, 25, 25 }), 20, "legs");
}
