/*
 * /d/Raumdor/common/npc/imp.c
 *
 * Imp, summoned by the priest in the Khiraa temple.
 *
 * Nerull   - 16/5-09.
 */

inherit "/d/Raumdor/std/monster";
#include "/d/Raumdor/defs.h"

string
adj_ran()
{
    int i;
    i = random(4);
    switch (i)
    {
        case 0:
        return "nasty";
        break;
        case 1:
        return "horned";
        break;
        case 2:
        return "fierce";
        break;
        default:
        return "teasing";
        break;
    }
}

void
do_despawn()
{
    tell_room(E(TO),"The "+TO->query_short()+" disappears in a puff of smoke.\n");
    remove_object();
}

void
create_monster()
{
	  string ran;
    ::create_monster();
    ran = adj_ran();
    set_name("imp");
    set_race_name("imp");
    set_adj(ran);
    add_adj("red");
    set_short(ran + " red imp");
    
    set_long("This is a tiny red creature, apparently not native to this"
    +    " world. It is a demon of some sort, thin and lean, wrapped in a"
    +    " deep red skin. Long pointy ears, a narrow long nose and a wicked"
    +    " grin with yellow teeth is the most prominent features, with"
    +    " the exception of two wicked and yellow eyes that stares right"
    +    " back at you with a jolly zest.\n");
    
    set_stats(STAT_ARRAY(90));
    set_skill(SS_DEFENCE,70);
    set_skill(SS_PARRY,70);
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,8800);
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_gender(G_NEUTER);
    set_alignment(-400);
    set_act_time(5);
    add_act("emote laughs manically.");
    add_act("emote jumps around you.");
    add_act("emote wiggles with its sharp claws.");
    add_act("emote pokes its nose.");
    add_act("emote paces around impatiently.");
    set_cact_time(3);
    add_cact("emote rumbles: You cannot defeat me, mortal.");
    add_cact("emote rumbles: Die fool!");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_hitloc_unarmed(0,50,15,"head");
    set_hitloc_unarmed(1,50,10,"left arm");
    set_hitloc_unarmed(2,50,10,"right arm");
    set_hitloc_unarmed(3,60,45,"body");
    set_hitloc_unarmed(4,50,20,"legs");  
    set_alarm(120.0, 0.0, &do_despawn()); 
}

int
special_attack(object enemy)
{
    int i, pen, pen2;
    if(random(6) != 0)
        return 0;
                
    i = random(6);
    if(i < 2)
    {
        
        pen2 = (TO->query_stat(0) + 50);
        
        enemy->hit_me(pen2, W_SLASH, TO, -1);
        
        enemy->catch_msg(QCTNAME(TO) + " tears through your flesh " +
                "with its razor-sharp claws!\n");
        
        tell_room(E(TO),QCTNAME(TO)+" tears through " + QTNAME(enemy) 
        +    "'s flesh with its razor-sharp claws!\n",enemy);
        
        if(enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
            return 1;
        }
        
     }
     else
         {
             enemy->catch_msg(QCTNAME(TO)+" gestures with its claws, and"
             +    " cast a small ball of fire at you!\n");
             tell_room(E(TO),QCTNAME(TO)+" gestures with its claws, and"
             +    " cast a small ball of fire"
             +    " at " + QTNAME(enemy) + "!\n",enemy);
             
             if(TP->query_prop(MAGIC_I_RES_FIRE) > 30)
             {
                           
                 pen = 50;
                 
                 enemy->hit_me(pen, MAGIC_DT, TO, -1);
                    
                 enemy->catch_msg("You are barely burnt by the small fireball.\n");
                 tell_room(E(TO),HE(enemy)+" is barely burnt by the small fireball.\n",enemy);
                 if(enemy->query_hp() <= 0)
                     enemy->do_die(TO);
                 return 1;
             }
             else
             {
          
                 
                 pen = 200 + random(50);
                 
                 enemy->hit_me(pen, MAGIC_DT, TO, -1);
                 
                 enemy->catch_msg("You are burnt badly by the small fireball.\n");
                 tell_room(E(TO),HE(enemy)+" is burnt badly by the small fireball.\n",enemy);
                 if(enemy->query_hp() <= 0)
                     enemy->do_die(TO);
                 return 1;
             }
          }
}
