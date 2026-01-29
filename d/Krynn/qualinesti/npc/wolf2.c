/*
   wolf2.c
   
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

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

void    attack_animal();

create_creature()
{
    set_name("wolf"); 
    set_race_name("wolf");
    set_short("huge dark-brown wolf");
    set_adj(({"wild", "grey", "vicious" }));
    set_long("The animal in front of you is superior in size to a regular " +
        "wolf. This impressive specimen has a dark brown pelt, under " +
        "which you can see huge, powerfull muscles, which allows it " +
        "to survive in such desolate areas.\n");

    set_stats(({ 80, 60 + random(20), 85, 30, 10, 85}));

    set_skill(SS_DEFENCE, 35);
    set_skill(SS_UNARM_COMBAT, 60);
    
    set_attack_unarmed(A_BITE,  30, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 35, 25, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 35, 25, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 20, 25, 30,}), 45, "body");
    set_hitloc_unarmed(H_LEGS, ({ 10, 15, 20,}), 35, "legs");

    set_aggressive(1);
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 47000);
    add_prop(LIVE_I_QUICKNESS, 100);
        
    LEFTOVER("tail");
    CUTLEFTOVER("skull");
    CUTLEFTOVER("rib");
    
    set_act_time(2);
    add_act("@@attack_animal");
    add_act("emote bares its fangs.");
    add_act("emote rumbles a low, deep growl.");
    add_act("emote growls menacingly.");
    add_act("emote watches the area hungrily.");

}

int
special_attack(object enemy)
{
    object me = TO;
    mixed  hitresult;
    string how;

    if ( !enemy )
        return 0;
        
    if (random(7))
    {
	return 0;
    }

    hitresult = enemy->hit_me(150, W_IMPALE, me, -1);
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

    enemy->catch_tell(query_The_name(enemy) + " paces slowly around and then " +
        "suddenly tears into your throat! You are " + how + " by the " +
        "attack.\n");
    tell_watcher(QCTNAME(me) + " paces slowly around, watching " + 
        QCTNAME(enemy) + ". Then suddenly, the wolf tears into " + 
        enemy->query_possessive() + " throat!\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1; 
}

int 
kill_it()
{
    object victim;  
    
    if ( !present("animal", E(TO)) )
        return 0;
    
    if ( (victim = present("hare", E(TO))) )
    {
        if ( random(3) )
        {
            command("emote suddenly attacks the " + victim->short() +
                ". After a short hunting the wolf clenches its fangs " +
                "at the rabbit's neck.");
            victim->heal_hp(-1000);
            victim->do_die(TO);
        }
        else
            command("emote suddenly attacks the " + victim->short() +
                ", but it is too quick for him.\nThe wolf " +
                "gives up as the rabbit scampers away.");
        
        return 1;
    }
}  

void
attack_animal()
{
    command("emote paces slowly, searching for a victim.");

    if ( present("animal", E(TO)) )
        set_alarm(3.0, 0.0, &kill_it());

}        

