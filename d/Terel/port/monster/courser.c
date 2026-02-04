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
    set_adj(({"spirited", "golden"}));
    set_short("spirited golden courser");
    add_name("courser");
    set_horse_long(break_string(
	"This golden courser seems to be in excellent condition." +
	" It must be a pleasure to ride such a horse.\n"
    , 72));
    set_gender(0);
    set_stats(({ 89, 93, 80, 50, 50, 85 }));
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_AWARENESS, 89);
    set_hp(9999);
    set_mana(9999);
    set_attack_unarmed(A_BITE, 34, 34, W_IMPALE,   20, "teeth");
    set_attack_unarmed(A_HOOF, 45, 40, W_BLUDGEON, 80, "hoofs");
    set_hitloc_unarmed(H_HEAD, ({ 15, 15, 15, 15 }),  5, "head");
    set_hitloc_unarmed(H_BODY, ({ 40, 40, 40, 40 }), 75, "torso");
    set_hitloc_unarmed(H_LEGS, ({ 30, 30, 30, 30 }), 20, "legs");
}
