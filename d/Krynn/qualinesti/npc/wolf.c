/*
   wolf.c
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
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

void    attack_animal();
string  *adj_list = ({ "wild", "big", "massive", "aggressive", "adult",
                       "dangerous", "ferocious" });

string adj;

create_creature()
{
    set_name("wolf"); 
    set_race_name("wolf");
    adj = adj_list[random(sizeof(adj_list))];
    set_short(adj + " grey wolf");
    set_pshort(adj + " grey wolves");
    set_adj(adj); 
    set_adj("grey");
    set_long("This huge wolf stands nearly four feet in height, and " +
        "is covered in a glossy grey pelt. Its red eyes glare at you " +
        "viciously, and it bares its fangs and growls spitefully. " +
        "The wolves like this one may be found sometimes in Qualinesti, " +
        "but usually in packs.\n");

    set_stats(({ 70, 50 + random(15), 75, 30, 10, 75}));

    set_skill(SS_DEFENCE, 35);
    set_skill(SS_UNARM_COMBAT, 60);
    
    set_attack_unarmed(A_BITE,  30, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 25, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 25, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30,}), 45, "body");
    set_hitloc_unarmed(H_LEGS, ({ 10, 10, 15,}), 35, "legs");
        
    set_aggressive(1);
    
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 33000);
    
    CUTLEFTOVER("skull");
    LEFTOVER("rib");
    LEFTOVER("tail");
    
    set_act_time(2);
    add_act("@@attack_animal");
    add_act("emote raises his head and sniffs the air.");
    add_act("emote bares its fangs.");
    add_act("emote rumbles a low, deep growl.");
    add_act("emote growls menacingly.");
    add_act("emote watches the area hungrily.");

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
/*
    if ( (victim = present("squirrel", E(TO))) )
    {
        if ( !random(3) )
        {
            command("emote suddenly attacks the " + victim->short() +
                ". After a short hunting the wolf clenches its fangs " +
                "at the squirrel's neck.");
            victim->heal_hp(-1000);
            victim->do_die(TO);
        }
        else
            command("emote suddenly attacks the " + victim->short() +
                ", but the squirrel avoids the wolf's fangs " +
                "and quickly climbs the nearest tree.");
        
        return 1;
    }
*/
}  

void
attack_animal()
{
    command("emote paces slowly, searching for a victim.");

    if ( present("animal", E(TO)) )
        set_alarm(3.0, 0.0, &kill_it());

}        

