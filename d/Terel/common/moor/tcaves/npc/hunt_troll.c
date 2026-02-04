/*


*/
#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/act/domove";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>

/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE 0
#define A_R_CLAW 1
#define A_L_CLAW 2

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
   
   set_name("troll"); 
   set_race_name("troll");
   set_adj(adj());
   set_long("A horrible flesh-eating creature. It has thick skin\n"
      +"of putrid gray-green and mottled black. Its mouth lined\n"
      +"with cruel teeth, its hands with dagger-like claws.\n"
      +"Dirty and smelling of rot, its body covered with hides\n"
      +"and tattered clothing, its head draped by thick strands\n"
      +"of gray bestial hair. Its eyes black with yellow slits.\n");
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 200, 140, 200, 135, 125, 125}));
   set_hp(9000);
    set_skill(SS_UNARM_COMBAT, 75);
   
   set_skill(SS_DEFENCE, 50);
   AGGRESSIVE;
   set_alignment(-700);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(LIVE_I_SEE_INVIS,3);
   
   set_attack_unarmed(A_BITE,   30, 45, W_IMPALE, 35, "bite");
   set_attack_unarmed(A_R_CLAW, 35, 30, W_SLASH, 60, "right claw");
   set_attack_unarmed(A_L_CLAW, 30, 30, W_SLASH, 55, "left claw");
    set_skill(SS_AWARENESS, 80);
   set_restrain_path(TROLL_CAVE_DIR);
   
   
   set_hitloc_unarmed(H_HEAD, ({ 40, 40, 25}), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 35, 40, 35}), 80, "body");
}
string adj()
{
    string *adj;
    adj = ({"large","terrifying","green-skinned","disgusting",
            "sickly","grotesque","slimy","brown-skinned"});
    return adj[random(sizeof(adj))];
}
int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, wuss;
    int hurt;


    me = TO;

    if(random(11) > 6) {

        hurt = F_PENMOD(100, 40 + random(40));

        hitresult = enemy->hit_me(hurt, W_SLASH, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " slashes at " + QCTNAME(enemy) + ".\n", enemy);
        enemy->catch_msg(QCTNAME(me) + " slashes at you!\n");
        enemy->catch_msg("You feel " + how + ".\n");
        me->heal_hp(200);
        wuss = query_smallest_enemy();
        if (wuss != query_attack())
            command("kill " + wuss->query_real_name());
        set_follow(enemy->query_real_name());

        return 1;
    }

    return 0;
}
