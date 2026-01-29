/*
 * /d/Faerun/guilds/vampires/shadows/vampires_thirst.c
 *
 * Vampires thirstobject.
 *
 * Nerull 2020
 *
 */
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <language.h>
#include <formulas.h>
#include <options.h>
#include "/std/combat/combat.h"
#include "../guild.h"

object Last_env;


int
do_vampthirst_announce()
{   
    if (!interactive(query_shadow_who()))
    {
        return 1;
    }

    int age = VAMPIRES_MAPPINGS->query_vampires_gauge(query_shadow_who()->query_name());    
    int current_bloodpool = VAMPIRES_MAPPINGS->query_thirst_gauge(query_shadow_who()->query_name());
    
    int vamppoints2 = VAMPIRES_MAPPINGS->query_vampires_resilience(query_shadow_who()->query_name());
    
    int vamp_age2 = VAMPIRES_MAPPINGS->query_vampires_gauge(query_shadow_who()->query_name());
    
    float max_bloodpool;
    
    // Imm point corrections.
    switch(age)
    {
        case 1451..3000:
        if (vamppoints2 >= 2)
        {
            vamppoints2 = 2;
        }   
        break;
        
        case 3001..7000:
        if (vamppoints2 >= 3)
        {
            vamppoints2 = 3;
        }   
        break;
        
        case 7001..11000:
        if (vamppoints2 >= 5)
        {
            vamppoints2 = 5;
        }   
        break;
        
        case 11001..15000:
        if (vamppoints2 >= 7)
        {
            vamppoints2 = 7;
        }   
        break;
        
        case 15001..50000:
        if (vamppoints2 >= 9)
        {
            vamppoints2 = 9;
        }   
        break;
    }
    
    VAMPIRES_MAPPINGS->set_vampires_resilience(query_shadow_who()->query_name(), vamppoints2);
    
    switch(age)
    {
        //////////// VAMPIRE SPAWNS ///////////           
        case 0..24:
        max_bloodpool = 24.0;
        break;
        
        
        case 25..48:
        max_bloodpool = 48.0;
        break;
        
        
        case 49..72:
        max_bloodpool = 72.0;
        break;
        
        
        case 73..100:
        max_bloodpool = 100.0;
        break;
        
       
        case 101..250:
        max_bloodpool = 150.0;
        break;
        
        
        case 251..500:
        max_bloodpool = 200.0;
        break;
        
       
        case 501..1000:
        max_bloodpool = 250.0;
        break;
        
        
        case 1001..1440:
        max_bloodpool = 300.0;
        break;

        
        case 1441..1450:
        max_bloodpool = 350.0;
        break;



        //////////// FULL VAMPIRES ///////////
        case 1451..2000:
        max_bloodpool = 400.0;
        break;
        
       
        case 2001..3000:
        max_bloodpool = 450.0;
        break;
        
       
        case 3001..5000:
        max_bloodpool = 500.0;
        break;
        
       
        case 5001..7000:
        max_bloodpool = 550.0;
        break;
        
       
        case 7001..9000:
        max_bloodpool = 600.0;
        break;
        
        
        case 9001..11000:
        max_bloodpool = 700.0;
        break;
        
        
        case 11001..13000:
        max_bloodpool = 800.0;
        break;
        
       
        case 13001..15000:
        max_bloodpool = 900.0;
        break;
        
        
        case 15001..17000:
        max_bloodpool = 1000.0;
        break;
        
        
        case 17001..23000:
        max_bloodpool = 1200.0;
        break;
    }

    //float max_bloodpoolfloat = itof(max_bloodpool);
    float current_bloodpoolfloat = itof(current_bloodpool);


    float pool_90 = (max_bloodpool / 100.0) * 90.0;
    float pool_80 = (max_bloodpool / 100.0) * 80.0;
    float pool_70 = (max_bloodpool / 100.0) * 70.0;
    float pool_60 = (max_bloodpool / 100.0) * 60.0;
    float pool_50 = (max_bloodpool / 100.0) * 50.0;
    float pool_40 = (max_bloodpool / 100.0) * 40.0;
    float pool_30 = (max_bloodpool / 100.0) * 30.0;
    float pool_20 = (max_bloodpool / 100.0) * 20.0;
    float pool_10 = (max_bloodpool / 100.0) * 10.0;
    float pool_05 = (max_bloodpool / 100.0) * 5.0;
    float pool_02 = (max_bloodpool / 100.0) * 2.0;
    
    object token;
    
    query_shadow_who()->set_alignment((query_shadow_who()->query_alignment() - 2));
    
    if (vamp_age2 == 1450)
    {
        query_shadow_who()->catch_msg("You feel you have aged enough to evolve into a full "
        +"vampire.\n");
    }
    
    if (pool_90 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("Your primal urges "
        +"are sated.\n");
        
        if (objectp(token = present("_slowme_vampire_obj", query_shadow_who())))
        {   
            query_shadow_who()->remove_slow_shadow();
            token->remove_object();
        }
         
        return 1;
    }

    if (pool_80 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("Your hunger is "
        +"slaked, a feeling of satisfaction permeates.\n");
        
        return 1;
    }
    
    if (pool_70 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("A dull ache "
        +"persists from behind your eyes, distracting you mildly.\n");
        
        return 1;
    }
    
    if (pool_60 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("You stagger subtly "
        +"from a brief sensation of dizziness and disorientation.\n");
        
        return 1;
    }
    
    if (pool_50 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("A sharp pain shoots "
        +"up and down your back, leaving you feeling physically diminished.\n");
        
        return 1;
    }
    
    if (pool_40 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("An overall lust for "
        +"blood envelops your senses resulting in a not so subtle "
        +"bewilderment.\n");
        
        return 1;
    }
    
    if (pool_30 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("Involuntary "
        +"convulsions begin to wreak havok throughout your body.\n");
        
        return 1;
    }
    
    if (pool_20 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("Confidence is "
        +"supplanted by indecision as your thoughts become "
        +"obscure and imprecise.\n");
        
        return 1;
    }
    
    if (pool_10 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("A distracting tingling "
        +"sensation is beginning to numb your extremeties and "
        +"is causing waves of fatigue.\n");
        
        return 1;
    }
    
    if (pool_05 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("Your limbs are becoming "
        +"unresponsive and tremble with weakness. Even your vision "
        +"is beginning to phase in and out.\n");
               
        if (!query_shadow_who()->query_prop(VAMPIRE_IS_ETHEREAL) 
            || !query_shadow_who()->query_prop(VAMPIRE_IS_INVIS))
        {
            query_shadow_who()->tell_watcher(QTNAME(query_shadow_who())
            +" looks pale and weak.\n");
        }
        
        return 1;
    }
    
    if (pool_02 < current_bloodpoolfloat)
    {
        query_shadow_who()->catch_msg("You can barely see through the "
        +"dimness of your vision while the thirst thunders in your mind.\n");
        
        if (!query_shadow_who()->query_prop(VAMPIRE_IS_ETHEREAL) 
            || !query_shadow_who()->query_prop(VAMPIRE_IS_INVIS))
        {
            query_shadow_who()->tell_watcher(QTNAME(query_shadow_who())
            +" looks pale and very weak.\n");
        }
        
        return 1;
    }
    
    query_shadow_who()->catch_msg("The overwhelming thirst has "
    +"rendered you utterly vulnerable through an almost "
    +"complete paralysis.\n");
    
    if (!query_shadow_who()->query_prop(VAMPIRE_IS_ETHEREAL) 
            || !query_shadow_who()->query_prop(VAMPIRE_IS_INVIS))
    {
        query_shadow_who()->tell_watcher(QTNAME(query_shadow_who())
        +" looks pale and extremely weak.\n");
    }
    
    return 1;
}




















