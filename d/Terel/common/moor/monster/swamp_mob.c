/* redhawk 920717 
 * swamp mob 
 * 
 * 2021-03-08 - Cotillion
 * - Fixed hitloc %
 */


inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_creature()
{
    if (!IS_CLONE) return;

    int alig = random(300)-100;


    set_name("animal");
    set_adj("strange");
    set_short("strange animal");
    set_long("It's a strange looking animal that seems to belong in a swamp.\n");
    set_adj(({"strange"}));
    set_race_name("badger");
    set_alignment(alig);
    set_stats(({30,20,30,10,10,20}));
    set_random_move(30);
    set_aggressive(0);
    set_gender(0);
    set_skill(SS_CLIMB,random(25));
    set_skill(SS_DEFENCE,random(5)+20);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    set_whimpy(0);
    set_act_time(21);
    add_act(({"growl","snarl","sniff","glare"}));
    seq_new("do_stuff");
    set_hp(4000);
}

#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(20,20,W_SLASH, 25,A_BITE);
    add_attack(15,15,W_BLUDGEON, 20,A_RPAW);
    add_attack(15,15,W_BLUDGEON, 20,A_LPAW);

    add_hitloc( ({ 4, 5, 5 }), 15, "head", H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 50, "body",H_BODY);
    add_hitloc( ({ 9, 9, 9 }), 35, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_RPAW:return "right front paw";
    case A_LPAW:return "left front paw";
    }
}

