/*
   dog.c
   This is rather a tough beast. One must be quite skilled to handle it.
   
   Blizzard, 01/2003

*/

inherit "/std/creature";
inherit "/std/combat/unarmed";   
inherit "/std/act/attack.c";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

string  *adj_list1 = ({"wild", "big", "large", "deadly-looking", "dangerous",
                       "vicious" }); 
string  *adj_list2 = ({"green", "brown", "dark-green", "dark-brown"});
string  adj1, adj2;

create_creature()
{
    adj1 = adj_list1[random(sizeof(adj_list1))];
    adj2 = adj_list2[random(sizeof(adj_list2))];
    
    set_name("cooshee"); 
    set_race_name("dog");
    set_short(adj1 + " " + adj2 + " dog");
    set_adj(({ adj1, adj2 }));
    set_long("This large, vicious creature is as large as a wolf, and " +
        "appears to be a cross of two or more of the most dangerous " +
        "breeds of hounds. It is known as the elven hound, cooshee. " +
        "Its dirty " + adj2 + " pelt is covered in many patches, and it " +
        "snaps wildly at you with bloodlust in its eyes.\n");

    set_stats(({ 70, 60 + random(15), 70 + random(10), 30, 5, 85}));

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 70);
    
    if ( adj2 == "green" || adj2 == "dark-green" )
        add_leftover(ARM + "dog_pelt_g", "pelt", 1, "", 0, 1);
    else if ( adj2 == "brown" || adj2 == "dark-brown" )
        add_leftover(ARM + "dog_pelt_b", "pelt", 1, "", 0, 1);

    CUTLEFTOVER("skull");
    CUTLEFTOVER("rib");
            
    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30,}), 45, "body");
    set_hitloc_unarmed(H_LEGS, ({ 15, 15, 25,}), 35, "legs");
        
    set_aggressive(1);
    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 32000);
    add_prop(LIVE_I_QUICKNESS, 100);

    set_act_time(2);
    add_act("emote snaps wildly at you.");
    add_act("emote bares its fangs.");
    add_act("emote growls menacingly.");

}

int
special_attack(object enemy)
{
    object me = TO;
    mixed  hitresult;
    string how;
    int stun_duration = 5 + random(5);

    if ( !enemy )
        return 0;
        
    if (random(7))
	return 0;  

    hitresult = enemy->hit_me(170, W_IMPALE, me, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "unharmed";
            break;
        case 1..10:
            how = "barely wounded";
            break;
        case 11..20:
            how = "wounded";
            break;
        default:
            how = "seriously wounded";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " leaps at you, trying to " +
        "knock you down! Then it attempts to bite your throat. " +
        "You are " + how + " by the attack.\n");
    tell_watcher(QCTNAME(me) + " leaps at " + QTNAME(enemy) + ", trying " +
        "to knock " + OBJECTIVE(enemy) + " down!\n", enemy);

    if ( (hitresult[0] > 0) && random(2) )
        enemy->add_attack_delay(stun_duration, 1);
        
    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1; 
}

