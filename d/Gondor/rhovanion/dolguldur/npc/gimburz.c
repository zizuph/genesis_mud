/*
 * MM Guru Quest NPC - /d/Gondor/rhovanion/dolguldur/npc/gimburz.c
 *
 * Varian - November 2020
 * Questlogic - Nerull 2021
 */

#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

#define TIMER_OBJECT           "/d/Gondor/rhovanion/dolguldur/obj/timer_obj.c"
#define INSTANCE_OBJECT        "/d/Gondor/rhovanion/dolguldur/obj/instance_obj.c"
#define MM_GURUQUEST           "_on_mm_quest"
#define NO_AVAILABLE_TASK      "_no_available_mm_task"
#define MM_GURU_QUEST_WARNING  "_mm_quest_warning"

int quest_info_stage = 0;

//void arm_me();

void
reset_task()
{
    this_object()->remove_prop(NO_AVAILABLE_TASK);
    quest_info_stage = 0;
    
    return;
}


void quest_info()
{
    switch (quest_info_stage)
    {
        case 0:
        this_object()->command("say The Dark Lord requires your service. " +
            "When the cowardly scum ambushed Dol Guldur many years ago, " +
            "certain works, important writings, were lost. The Dark " +
            "Lord requires them to be found and returned.");
        break;
        
        case 1:
        this_object()->command("say Hidden somewhere in the rubble of " +
            "Dol Guldur is a mighty tome, a spellbook which focuses " +
            "upon the most wonderful art of Necromancy. You must find " +
            "it, and find it quickly. Events in this world are moving " +
            "quickly and there is no time to waste.");
        break;
        
        case 2:
        this_object()->command("say Others have gone before you and " +
            "failed. They have suffered the ultimate price of " +
            "failure, as shall you if you cannot complete this task " +
            "swifly enough. Now go, find what the Dark Lord seeks and " +
            "give the spellbook to me when you return.");
        break;
    }
    
    quest_info_stage = quest_info_stage + 1;
    
    if (quest_info_stage <= 2)
    {
        set_alarm(3.0, 0.0, &quest_info());
    }
    
    return;
}
    
    

string
add_ask1()
{
    object timer_object_start;
    int quest_nr = 0;
    
    /*if (this_player()->test_bit("Gondor", 2, 1))
    {
        command("say You have done this quest before!");
        return "";
    }*/
    
    if (objectp(timer_object_start = present("_mm_timerobject1_", 
        this_player())))
    {
        command("say I have given you the task, do not bother me until you " +
            "have completed it! Now hurry, or face the consequences, the " +
            "Dark Lord is displeased with your lax manner!");
        return "";
    }
    
    if (this_object()->query_prop(NO_AVAILABLE_TASK) == 1)
    {
        command("say Come back and see me again soon. I have already " +
            "assigned this task to another, but they are too slow and " +
            "the Dark Lord is growing impatient.");
        return "";
    }
      
    if (!this_player()->query_prop(MM_GURU_QUEST_WARNING))
    {
        command("say I have a task for you, but if you fail, the Dark Lord " +
            "will have your hide! There will be no tolerance for the slow " +
            "or inept. If you are sure about this, then ask me again.");
        
        this_player()->add_prop(MM_GURU_QUEST_WARNING, 1);
        return "";
    }
    
    clone_object(TIMER_OBJECT)->move(this_player(), 1);
    clone_object(INSTANCE_OBJECT)->move(environment(this_object()), 1);
    
    // From 1 -> 7.
    //quest_nr = random(7) + 1;
	quest_nr = 7;
    
    // The value of this property defines _where_ the book can be
    // found.
    this_player()->add_prop(MM_GURUQUEST, quest_nr);
    
    this_object()->add_prop(NO_AVAILABLE_TASK, 1);
    
    set_alarm(240.0, 0.0, &reset_task());
    
    command("cackle");
    command("say Yes, a task!");
    
    set_alarm(3.0, 0.0, &quest_info());
    
    return "";
}


/*
 * Function name: reward_task()
 * Description  : Determines the reward for various tasks
 */
int
give_spellbook(string str)
{
    object spellbook;
    object timer_obj_end;
    
    if (str == "spellbook to gimburz" 
    || str == "spellbook to servant"
    || str == "spellbook to figure")
    {
        if (objectp(spellbook = present("_mm_spellbook_", 
        this_player())))
        {
            // If the player has done this quest.
            if(this_player()->test_bit("Gondor", 2, 1))
            {
                write("You give the spellbook to the figure.\n");
   
                command("emote takes the spellbook and stores it away " +
                    "safely.\n");
                command("say You already found a copy of this for the Dark " +
                    "Lord. Do not expect any reward or thanks from me.\n");
                                    
                if (objectp(timer_obj_end = present("_mm_timerobject1_", 
                this_player())))
                {
                    timer_obj_end->remove_object();
                }
                
                spellbook->remove_object();
                
                return 1;
            }
            
            write("You give the spellbook to the figure.\n");
                
            command("say Splendid, you found it!\n");
                
            this_player()->catch_msg("\nYou feel little more experienced for " +
                "completing this task! You feel ready to further master your " +
                "skills in the dark arts now.\n");
            
            spellbook->remove_object();
            
            if (objectp(timer_obj_end = present("_mm_timerobject1_", 
            this_player())))
            {
                timer_obj_end->remove_object();
            }
            
           // this_player()->set_bit(2, 1);
           
           // Guru quest for MM - no xp rewarded.
           //this_player()->add_exp_quest(0);
            
            return 1;
        }
         
        return 0;
    } 
    
    return 0;
}


void
create_monster()
{
   seteuid(getuid());
   
   set_name("gimburz");
   add_name("servant");
   add_adj( ({"menacing", "looming"}) );
   set_title("the Mordu, Hand of the Dark Lord");
   set_long("You are unable to determine the race of this menacing " +
      "figure looms over you, gazing at you with what appears to be " +
      "disdain.\n");
   set_race_name("figure");
   set_gender(0);
   
   add_act("say Are you willing to prove yourself worthy to the " +
      "Dark Lord?");
      
   
   add_ask( ({ "quest", "task", "help" }), add_ask1);

   set_act_time(10);

   set_stats(({ 200, 200, 200, 110, 110, 200}), 10);
   
   set_alignment(-1150);
   
   equip( ({"../wep/gim_sword.c", "../arm/gim_armour.c", 
      "../arm/gim_cloak.c"}) );

}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

void
init_living()
{
    ::init_living();
    add_action(give_spellbook, "give");
}