inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";

#include "/d/Emerald/defs.h";
#include <wa_types.h>;

void create_creature() {
    set_name("rabbit");
    set_race_name("rabbit"); 
    set_adj("white");
    add_adj("baby");
    set_long("It is a really CUTE white rabbit.\n");
    set_stats(({ 5,   4,   3,   2,   3,   4}));
    set_hp(10);
    set_gender(random(2));
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(CONT_I_HEIGHT, 300);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(CONT_I_IN, 0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_attack_unarmed(0,  6,  7, W_IMPALE, 80, "teeth");
    set_attack_unarmed(1, 12, 12, W_SLASH,  10, "left paw");
    set_attack_unarmed(2, 12, 12, W_SLASH,  10, "right paw");
    set_hitloc_unarmed(0, ({ 5, 7, 3, 2 }), 20, "head");
    set_hitloc_unarmed(1, ({ 5, 4, 8, 0 }), 80, "body");
}
