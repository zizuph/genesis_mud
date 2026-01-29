/* towncastle/npc/alligator.c is cloned by towncastle/moat.c */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/attack";
 
#include <ss_types.h>
#include <wa_types.h>
#include "../default.h"
 
#define A_BITE  0
#define A_TAIL  1
 
#define H_HEAD  0
#define H_BODY  1
#define H_TAIL  2
 
void
create_creature()
{
    set_name("alligator");
    set_race_name("alligator");
    add_adj("huge");
    add_adj("vicious");
    set_long("It looks like it eats adventurers for breakfast!\n");
 
    set_stats( ({ 100, 65, 75, 5, 5, 150 }) );
 
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_SWIM, 100);

    add_prop(CONT_I_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 150000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_attack_unarmed(A_BITE, 60, 30, W_IMPALE, 55, "jaws");
    set_attack_unarmed(A_TAIL, 50, 20, W_SLASH,  45, "tail");
 
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 20, 30, 60, 30 }), 60, "body");
    set_hitloc_unarmed(H_TAIL, ({ 15, 25, 20, 20 }), 20, "tail");
 
    heal_hp(query_max_hp());
    
    set_aggressive(1);
    set_attack_chance(40);
 
    set_random_move(20);
    set_restrain_path(TCASTLE_DIR + "moat");
    set_monster_home(TCASTLE_DIR + "moat6");
 
    trig_new("%w 'pats' 'you' %s", "react_pat");
}
 
int
react_pat(string who, string what)
{
    if (who) {
        who = lower_case(who);
        set_alarm(1.0,0.0,"return_pat",who);
        return 1;
    }
    return 0;
}
 
void
return_pat(string who)
{
    object obj;
 
    if (obj = present(who, environment()))
        command("snarl " + who);
}
