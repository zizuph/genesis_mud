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
    set_adj(({"old", "shabby"}));
    set_short("old shabby mare");
    set_horse_long("It is an old shabby looking mare. "+
                   "It's probably too old to do  anything but limp around.\n");
    add_name("mare");
    set_gender(1);
    set_stats(({ 15, 14, 12, 10, 9, 13 }));
    set_skill(SS_DEFENCE, 10);
    set_skill(SS_AWARENESS, 10);
    set_hp(9999);
    set_mana(9999);
    set_attack_unarmed(A_BITE, 4, 4, W_IMPALE,   20, "teeth");
    set_attack_unarmed(A_HOOF, 15, 15, W_BLUDGEON, 80, "hoofs");
    set_hitloc_unarmed(H_HEAD, ({ 4, 4, 4, 4 }),  5, "head");
    set_hitloc_unarmed(H_BODY, ({ 13, 13, 13, 13 }), 75, "torso");
    set_hitloc_unarmed(H_LEGS, ({ 11, 11, 11, 11 }), 20, "legs");
}
