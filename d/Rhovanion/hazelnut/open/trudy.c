inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/act/chat";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    set_name("trudy"); 
    add_name("furface");
    set_race_name("cat");
    set_short("white tiger");
    set_adj(({"white", "cuddly" }));
    set_short("Trudy Furface");
    set_long("A nice little cat! She looks rather cuddly!\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 90, 30, 80, 20, 5, 75}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");

    add_act("purr");
    add_act("snuggle mecien");

    add_chat("Meow!");
}

