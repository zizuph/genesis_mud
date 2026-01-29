/*  /d/Faerun/guilds/vampires/npc/nation_target.c
*
*   Target of interest for the Vampire guild.
*
*   Nerull 2021
* 
*/
inherit "/d/Faerun/std/faerun_npc";
inherit "/d/Faerun/lib/assist_friend";

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>
#include "../guild.h"

int nattier;


int set_nattier(int i)
{
    nattier = i;
    
    return 1;
}


int query_nattier()
{   
    return nattier;
}


/*
* Function name: do_die()
* Description  : Sets the items that this monster might drop.
*/
void
do_die(object killer)
{
    MONEY_MAKE_PC(random(4))->move(this_object(), 1);
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(killer->query_name()) > 0)
    {
        int currentrep;
        int newrep;
        
        currentrep = VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name());
        
        newrep = currentrep + 1;
        
        if (newrep > 100)
        {
            newrep = 100;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) <= 10 
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 1)
        {
            VAMPIRES_MAPPINGS->set_vampire_reputation(killer->query_name(), newrep);
        
            killer->catch_tell("Your reputation as a Vampire increases slightly.\n");
            
            REP_INCREASE_LOG("rep_increase_log",
                killer->query_name()+" increased 1 point in reputation.\n");
                
            NATION_TARGET_LOG("nationtarget_log",
            "Nationtarget killed by "+killer->query_name()+".\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) > 10
        && VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) <= 25       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 2)
        {
            VAMPIRES_MAPPINGS->set_vampire_reputation(killer->query_name(), newrep);
        
            killer->catch_tell("Your reputation as a Vampire increases slightly.\n");
            
            REP_INCREASE_LOG("rep_increase_log",
                killer->query_name()+" increased 1 point in reputation.\n");
                
            NATION_TARGET_LOG("nationtarget_log",
            "Nationtarget killed by "+killer->query_name()+".\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) > 25
        && VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) <= 40       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 3)
        {
            VAMPIRES_MAPPINGS->set_vampire_reputation(killer->query_name(), newrep);
        
            killer->catch_tell("Your reputation as a Vampire increases slightly.\n");
            
            REP_INCREASE_LOG("rep_increase_log",
                killer->query_name()+" increased 1 point in reputation.\n");
                
            NATION_TARGET_LOG("nationtarget_log",
            "Nationtarget killed by "+killer->query_name()+".\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) > 40
        && VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) <= 70       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 4)
        {
            VAMPIRES_MAPPINGS->set_vampire_reputation(killer->query_name(), newrep);
        
            killer->catch_tell("Your reputation as a Vampire increases slightly.\n");
            
            REP_INCREASE_LOG("rep_increase_log",
                killer->query_name()+" increased 1 point in reputation.\n");
                
            NATION_TARGET_LOG("nationtarget_log",
            "Nationtarget killed by "+killer->query_name()+".\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) > 70
        && VAMPIRES_MAPPINGS->query_vampire_reputation(killer->query_name()) <= 100       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 5)
        {
            VAMPIRES_MAPPINGS->set_vampire_reputation(killer->query_name(), newrep);
        
            killer->catch_tell("Your reputation as a Vampire increases slightly.\n");
            
            REP_INCREASE_LOG("rep_increase_log",
                killer->query_name()+" increased 1 point in reputation.\n");
                
            NATION_TARGET_LOG("nationtarget_log",
            "Nationtarget killed by "+killer->query_name()+".\n");
        }
        
        VAMPIRES_OBJHANDLER->set_vamptarget_inactive();

        ::do_die(killer);
        
        return;
                
    }
    
    NATION_TARGET_LOG("nationtarget_log",
    "Nationtarget killed by non-applicable player "+killer->query_name()+".\n");
    
    VAMPIRES_OBJHANDLER->set_vamptarget_inactive();

    ::do_die(killer);
}


void
destroy_target()
{
    VAMPIRES_OBJHANDLER->set_vamptarget_inactive();
    
    tell_room(environment(this_object()), "The "+query_short()
    +" travels elsewhere.\n");  
    
    NATION_TARGET_LOG("nationtarget_log",
        "Nationtarget Despawned..\n");
           
    remove_object();
}


void create_monster()
{
    int i;

    seteuid(getuid());
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_race_name("human");
    add_name("man");
    
    int dice1;
    
    dice1 = random(5);
    
    switch(dice1)
    {
        case 0:
        set_short("cloaked well-travelled man");    
        set_long("This figure seems to have spent quite a few "
        +"nights under the open sky, travelling mostly in the "
        +"wilderness. He is wearing a thick worn cloak of "
        +"linen, conceiling most of his features. You get the "
        +"impression that he is running from something.\n");
        
        set_adj("cloaked");
        add_adj("well-travelled");
        break;
        
        case 1:
        set_short("nervous young man");    
        set_long("His eyes darts everywhere, looking for possible "
        +"threats. Sweating profusely, it seems that something has "
        +"triggered a great amount of fear, as he is desperately "
        +"looking over his shoulders and is trying to best of his "
        +"ability to conceal himself from the environment. He is "
        +"definitely running from something.\n");
        
        set_adj("nervous");
        add_adj("young");
        break;
        
        case 2:
        set_short("well-dressed petite man");    
        set_long("Clad in the clothes of a fine noblesman, this "
        +"petite and apparently arrogant man is walking confident "
        +"about, almost ignoring his environment entirely. He "
        +"seems to be more busy cleaning his nails and powdering "
        +"his nose than looking at the path ahead of him. His "
        +"walking-speed slightly indicates that he is walking or "
        +"fleeing away from something.\n");
        
        set_adj("well-dressed");
        add_adj("petite");
        break;
        
        case 3:
        set_short("wounded blue-eyed man");    
        set_long("This blue-eyed man is bleeding from a couple of "
        +"puncture wounds at his neck. Signs of a swordfight is "
        +"also apparent if you judge by the several cuts that "
        +"is decorating his arms and body. He appears unarmed "
        +"though, and on the run from something.\n");
        
        set_adj("wounded");
        add_adj("blue-eyed");
        break;
        
        case 4:
        set_short("barrel-chested filthy man");    
        set_long("This is a filthy but large-framed man, "
        +"wearing only a set of ragged clothes. He has some "
        +"old brutal scars here and there, indicating that "
        +"he once might have served as a gladiator. With open "
        +"drooling mouth, thick unkept filthy hair and a a bushy "
        +"monobrow gives away the impression of a man that "
        +"doesn't take personal hygiene particular seriously, "
        +"paired with a mind that might not fit a scholar. He is "
        +"making grumpy noises and is looking about for threats. You "
        +"think this man is hunted by something or someone.\n");
        
        set_adj("barrel-chested");
        add_adj("filthy");
        break;
    }
            
    set_gender(G_MALE);
    add_prop(CONT_I_WEIGHT,95000);
    add_prop(CONT_I_HEIGHT,190);
    
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 190 + random(25));
    set_base_stat(5, 80);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_ACROBAT,90);
    set_skill(SS_PARRY,90);
    
    set_random_move(8);

    set_alarm(20750.0, 0.0, &destroy_target());    
}
