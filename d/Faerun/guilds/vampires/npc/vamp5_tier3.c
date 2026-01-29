/*
 * Nerull, 2022
 */

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>

inherit "std/monster.c";
inherit "/std/combat/unarmed";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

string taskob;

int taskobnr;

int task1_int;

string wantobject;

void
update_states()
{
    if (!this_object()->query_prop(OBJ_I_HIDE))
    {
        this_object()->add_prop(OBJ_I_HIDE, 10);
    }
    
    return;
}


int
do_task()
{   
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
    {
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
        {
            if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_5_AGENT_NR)
            {   
                if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 100)
                {
                    return 0;
                }  
                
                if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 1)
                {
                    switch(taskobnr)
                    {
                        // /d/Terel/mountains/ghastly_keep/obj/g_stone.c
                        case 0:
                        wantobject = "A ghastly green stone";
                        break;
                        
                        // /d/Terel/dabaay/obj/eyepatch_n.c
                        case 1:
                        wantobject = "A black leather eyepatch";
                        break;
                        
                        // /d/Faerun/mere/wep/magic_swingblade.c
                        case 2:
                        wantobject = "A gleaming meteorite swingblade";
                        break;
                        
                        // Nonexisting item atm
                        case 3:
                        wantobject = "A large alchemy set";
                        break;
                        
                        // /d/Ansalon/goodlund/bloodsea/obj/storm_amulet
                        case 4:
                        wantobject = "A dark amulet of the storm";
                        break;

                        // /d/Raumdor/magical_weapons/2h_undull_beast_cleaver
                        case 5:
                        wantobject = "A warped rust-red heavy cleaver";
                        break;

                        // /d/Krynn/tharkadan/obj/polymorph_figurine.c
                        case 6:
                        wantobject = "A curious figurine carved of white quartz";
                        break;
                        
                        // d/Avenir/common/dark/obj/war_helm.c
                        case 7:
                        wantobject = "A black war-helm";
                        break;
                        
                        // /d/Ansalon/silvanesti/new_kurinost/weapon/soulsplitter.c
                        case 8:
                        wantobject = "A flawless double-bladed axe";
                        break;
                        
                        // /d/Earthsea/gont/tenalders/arm/spike_boots.c
                        case 9:
                        wantobject = "A pair of spiked boots";
                        break;
                        
                        // /d/Avenir/common/city/obj/worn/stocking.c
                        case 10:
                        wantobject = "A webcloth body-stocking";
                        break;
                        
                        // /d/Krynn/tharkadan/armour/umberhulk_bracers.c
                        case 11:                        
                        wantobject = "The bracers of the umber hulk";
                        break;
                                               
                        // /d/Raumdor/common/beach/bountiful/chest_rewards/magic_scythe.c
                        case 12:
                        wantobject = "An adamantine bone scythe";
                        break;
                        
                        // /d/Terel/mountains/ghastly_keep/obj/g_spyglass.c
                        case 13:
                        wantobject = "A ghostly spyglass";
                        break;
                        
                        // /d/Gondor/ithilien/forest/harad_earring.c
                        case 14:
                        wantobject = "A pair of earrings";
                        break;
                        
                        // /d/Terel/mountains/ghastly_keep/obj/g_wart.c
                        case 15:
                        wantobject = "A witch wart";
                        break;
                        
                        // /d/Avenir/common/dead/obj/kesoit_mask.c
                        case 16:
                        wantobject = "A wooden death mask";
                        break;
                    }
                    
                    if (present("path1_cooldown_obj", this_player()))
                    {
                        this_object()->command("emote says: We don't need "
                        +"any further assistance from "
                        +"you at this time. You will hear from us later.\n");
                        
                        return 1;
                    }
                                      
                    this_object()->command("emote says: The Vampire Nation wants you "
                    +"to collect the following item: "+wantobject+". When you have the "
                    +"item in inventory, you can <complete task>.\n");
                
                    return 1;
                }
                         
                this_object()->command("emote says: Other prominent vampires has started noticing "
                +"you. Your continued efforts of eliminating our enemies has not "
                +"gone entirely unnoticed, so if you wish to continue on the path of Vampire "
                +"prosperity, knowledge and to aid the Vampire Nation further, I will "
                +"require a token of commitment from you. Only then will I reveal "
                +"further objectives of interest that will further our common cause.\n");
                    
                return 1;
            }
        }
    }
    
    return 0;
}


int
do_commitment_ask()
{
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
    {
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
        {
            if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_5_AGENT_NR)
            {
                if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 100)
                {
                    return 0;
                }
                
                if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) > 0)
                {
                    this_object()->command("emote says: You are aready committed to the cause. You may "
                    +"ask me for tasks now.\n");
                    
                    return 1;
                }
                              
                this_object()->command("emote says: From you, I will siphon two parts of your Immortality if "
                +"you wish to <commit to the cause>. Else, be on your way. Feel free to 'commit to the cause' "
                +"if you wish to aid the Vampire Nation in furthering its goals by completing "
                +"various tasks.\n");
                
                return 1;
            }           
        }
    }
    
    return 0;
}


int
set_taskobjective(int i)
{
    taskobnr = i;

    return 1;
}


int
query_taskobjective()
{
    return taskobnr;
}


int
update_objective()
{
    set_taskobjective(random(17));
    
    return 1;
}


/*
 * Function name: create_monster()
 * Description  : Constructor. Edit this to change monster.
 */
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    add_name("vampire");
    add_name("anchilla vampire");

    add_adj("crimson-cloaked");
    add_adj("hooded");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_ATTACK, "No. You think that would be unwise.\n");
    add_prop(OBJ_I_HIDE, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
  
    set_short("crimson-cloaked hooded male human");

    set_long("This man is almost entirely covered by a "
    +"large crimson cloak, concealing almost all "
    +"features. You spot a pair of blue eyes and a "
    +"pair of white fangs in the shadows of the hood.\n");
        
    add_ask( ({ "task", "quest", "help", "aid"}), do_task, 1);
    add_ask( ({ "nation", "vampire nation", "token", "commitment"}), do_commitment_ask, 1);

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    set_stats(({ 200, 200, 200, 200, 200, 200 }));

    set_hitloc_unarmed(A_HEAD, 35, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 35, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 35, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 35, 45, "body");
    set_hitloc_unarmed(A_LEGS, 35, 20, "legs");

    set_attack_unarmed(W_BOTH,  40, 40, W_IMPALE,
    20, "sharp fangs");

    set_attack_unarmed(W_RIGHT,  40, 40, W_SLASH,
    40, "left sharp claw");

    set_attack_unarmed(W_LEFT,  40, 40, W_SLASH,
    40, "right sharp claw");

    set_attack_unarmed(W_FOOTL,  40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTR,  40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,90);

    set_alarm(60.0, 60.0, &update_states());
    set_alarm(1.0, 10800.0, &update_objective());
}


/*
 * Function name: reward_task()
 * Description  : Determines the reward for various tasks
 */
int
give_taskobjective(string str)
{
    object taskobjective;
    object path1coold_object;
    
    if (taskobnr == 0)
    {
        taskob = "_ghastly_keep_stone";
    }
    
    if (taskobnr == 1)
    {
        taskob = "eyepatch";
    }
    
    if (taskobnr == 2)
    {
        taskob = "swingblade";
    }
    
    if (taskobnr == 3)
    {
        taskob = "large_alchemy_set";
    }
    
    if (taskobnr == 4)
    {
        taskob = "amulet of the storm";
    }  
    
    if (taskobnr == 5)
    {
        taskob = "rust_red_undull_heavy_cleaver";
    }
    
    if (taskobnr == 6)
    {
        taskob = "_thark_polymorph_figurine";
    }
    
    if (taskobnr == 7)
    {
        taskob = "war-helm";
    }
    
    if (taskobnr == 8)
    {
        taskob = "soulsplitter";
    }
    
    if (taskobnr == 9)
    {
        taskob = "pair of spiked boots";
    }
    
    if (taskobnr == 10)
    {
        taskob = "body-stocking";
    }
    
    if (taskobnr == 11)
    {
        taskob = "_umber_hulk_bracers";
    }
    
    if (taskobnr == 12)
    {
        taskob = "_tomb_scythe";
    }
    
    if (taskobnr == 13)
    {
        taskob = "_ghastly_spyglass";
    }
    
    if (taskobnr == 14)
    {
        taskob = "earrings";
    }
    
    if (taskobnr == 15)
    {
        taskob = "_ghastly_keep_wart";
    }
    
    if (taskobnr == 16)
    {
        taskob = "_Avenir_magic_death_mask";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
    {
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
        {
            if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_5_AGENT_NR)
            {
                if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 100)
                {
                    return 0;
                }  
                               
                if (str == "objective" || str == "task" || str == "quest")
                {
                    if (objectp(taskobjective = present(taskob, 
                    this_player())))
                    {
                        if (present("path1_cooldown_obj", this_player()))
                        {
                            command("emote says: We don't need any further assistance from "
                            +"you at this time. Report back later though.\n");
                            
                            return 1;
                        }
                                              
                        write("You give the "+taskobjective->short()+" to the "
                            +short()+".\n");
                            
                        if (taskobjective->query_prop(OBJ_I_BROKEN))
                        {
                            command("emote says: Hmm, it's broken, and isn't very useful for us. I will "
                            +"discard it though for you.\n");
                            
                            taskobjective->remove_object();
                            
                            return 1;
                        }
                            
                        command("emote says: Excellent, and thank you for the "
                        +"assistance. Return to me later for further assignments.\n");
                        
                        int pathprog;
                        
                        pathprog = VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name());
                        
                        pathprog = pathprog + 1;
                        
                        if (pathprog >= 100)
                        {
                            pathprog = 100;
                        }
                        
                        VAMPIRES_MAPPINGS->set_vamp_pathprogression(this_player()->query_name(), pathprog);
                        
                        write("Your standing with the Vampire Nation increases slightly.\n");
                        
                        if (pathprog == 100)
                        {
                            command("emote says: On the behalf of the Vampire Nation, you have done "
                            +"enough for now. Farewell Vampire, my assignment with you is done, and "
                            +"we shall not meet again. Keep an eye for vampires of higher stature as "
                            +"they may contact you in the future.\n");
                           
                            taskobjective->remove_object();
                      
                            return 1;
                        }
      
                        taskobjective->remove_object();
                        
                        //command("emote says: Let me know if you want to pursue a new objective.\n");                       
                        //set_taskobjective(random(4));
                        
                        if (!present("path1_cooldown_obj", this_player()))
                        {
                            path1coold_object = clone_object(VAMPIRES_GUILD_DIR +"obj/path1_cooldown");
                            path1coold_object->move(this_player(), 1);
                            path1coold_object->start_me();
                        }
                      
                        return 1; 
                    }
                    
                    write("You are missing the relevant object.\n");
                    
                    return 1;
                }

                write("Try to 'complete objective' if you possess the desired item.\n");

                return 1;                
            }
        }
    }

    return 0;
}


int do_commit(string str)
{
    if (str == "to the cause")
    {
        if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
        {
            if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
            {
                if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_5_AGENT_NR)
                {
                    if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) == 0)
                    {
                        int current_resilience_rank = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name()); 
                        int new_resilience_rank = current_resilience_rank - 2;
                            
                        if (current_resilience_rank < 2)
                        {
                            write("This action requires two points of immortality, which "
                            +"you don't currently have.\n");
                            
                            return 1;
                        }
                            
                        VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), new_resilience_rank);
                    
                        write("You commit to the cause of the Vampire "
                        +"Nation!\nYou pay two points of immortality.\n");
                        
                        VAMPIRES_MAPPINGS->set_vamp_pathprogression(this_player()->query_name(), 1);
                        
                        return 1;
                    }

                    write("You are already committed to the cause.\n");

                    return 1;
                }
            }
        }                    
    }
    
    return 0;
}


public int 
check_seen(object for_obj)
{
    // Wizards can always see us.
    if (for_obj->query_wiz_level())
    {
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
    {
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
        {
            if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_5_AGENT_NR)
            {
                if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 100)
                {
                    return 0;
                }  
                
                return 1;
            }           
        }       
    }
               
    return 0;
}


void
do_vamp_notify()
{
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
    {
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
        {
            if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_5_AGENT_NR)
            {
                if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 100)
                {
                    return;
                }  
                
                this_player()->catch_tell("\nYou sense the presence of a "
                +"Vampire here.\n");
                
                return;       
            }           
        }
    }        
 
    return; 
}


void
init_living()
{
    ::init_living();
     
    set_alarm(0.1, 0.0, &do_vamp_notify());
    add_action(give_taskobjective, "complete");
    add_action(do_commit, "commit");
}