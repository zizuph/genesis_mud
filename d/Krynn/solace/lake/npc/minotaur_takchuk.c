/*
 * Who          : Takchuk de-Toron, an old wrinkled male minotaur
 * Located      : The Toron minotaur village near Crystalmir Lake outside
 *                Solace.
 *                /d/Krynn/solace/lake/npc
 * Description  : The Sage for the tribe. Gives out and rewards players 
                  for solving the Toron_missing_standard quest.
 * Base file    : Made to inherit "minotaur_base".
 * Made by      : Cherek, Feb 2007
 */

#include "../local.h"
#include <ss_types.h>
#define ARMOUR OBJ + "breastplate.c"
#define TAKCHUK_STORY_01 (NPC + "takchuk_story_01.txt")
#define TAKCHUK_STORY_02 (NPC + "takchuk_story_02.txt")



inherit "/lib/unique";
inherit MINOTAUR;



/* Global variable for telling stories. */
string *lines = ({ });

int talking = 0;

void add_ask_act();
void start_story_quest();
void start_story_standard();
void arm_me(object me);

void
create_minotaur()
{

    set_type("SAGE");  
    
    set_adj("wrinkled");   
    set_adj("old");
    
    set_name("takchuk");
    set_living_name("_takchuk");	    
    set_title("de-Toron, Sage of the Toron tribe minotaurs");       
    set_gender(G_MALE);            
    set_long("Before you stands a large creature. He is half human and " +
	     "half bull leading you to believe this must be a minotaur. " +
	     "His skin is thick and covered with a deep brown fur but his " +
	     "most noticable feature are the two long and very sharp " +
	     "horns growing on his head. This is the sage of the Toron " +
	     "tribe minotaurs. Even so, he looks like he can take care " +
	     "of himself in a battle.\nHe is short and lean for " +
	     "a minotaur. \n");
    
    set_gender(G_MALE);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    
    add_ask_act();
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 35);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS, 60);

    set_alarm(0.1, 0.0, &arm_me(TO));
    
    setuid();
    seteuid(getuid());   
    
}

void arm_me(object me) /* NOTE: Function called using an alarm. */ 
{
    clone_object(ARMOUR)->move(me, 1);
    clone_unique(OBJ+"dwarf_bane", 3,
          "/d/Krynn/icewall/plains/obj/taxe")->move(TO, 1);
    me->command("wear all");
    me->command("wield all");
}

void
add_ask_act()
{
    set_default_answer("emote shrugs helplessly.",1);
    
    add_ask(({"task", "quest", "help"}), start_story_quest); 
        
    add_ask(({"standard", "battle standard"}), start_story_standard);

    set_act_time(10+random(5));
    
    add_act("say If the standard was returned, everything might " +
            "not be lost. ");
    add_act("say This is not a public library you know. ");
    add_act("say The gods have not abandoned us. Why would they " +
            "abandon their greatest creation?");
    add_act("say You do not look like much, but maybe you can help us? ");
            
    seq_addfirst("_mon_ran_act", 1*random(2));    
}

/*
 * Function name: remove_ask_act
 * Description  : Removes the possibility to ask the NPC questions,
 *                also removes the NPCs actions. Used when he is
 *                telling a story.
 */ 
 
void remove_ask_act()
{
    seq_clear("_mon_ran_act");
    remove_asks();
    set_default_answer("say Hey, I am talking.",1);
}

/*
 * Function name: story_line
 * Description  : This function prints a text-file containing all the 
 *                commands for the NPC to tell a story. Each story has
 *                its own text file. The function prints one line at a
 *                time until the end of the file.
 *                NOTE: Called using an alarm, and calls itself with
 *                an alarm.
 */ 
 
void
story_line(int index, object player, object me)
{
    int delay;
  
    if(index == 0)
    {
        remove_ask_act();
    }    
    
    if(!present(player, environment(me)))
    {
        add_ask_act();
        talking = 0;
        return;
    }
      
    if (index >= sizeof(lines))
    {     
        lines = ({ });           
        add_ask_act(); 
        talking = 0;
        return;
    }

    delay = atoi(lines[index]);
    if (delay > 0)
    {           
        set_alarm(itof(delay), 0.0, &story_line(index + 1, player, me));
        return;
    }

    me->command(lines[index]);
    
    story_line(index + 1, player, me);   
    
}

/*
 * Function name: start_story_"xxx"
 * Description  : These functions reads a text-file containing all the 
 *                commands for the NPC to tell a story. Each story has
 *                its own text file.
 */
 
string
start_story_quest()
{

    if(talking)
    {    
        return "";
    }
    
    talking = 1;

    setuid();
    seteuid(getuid());
    
    if(TP->test_bit("Krynn",3,18))
    {
        command("say There is nothing more you can do for us.");
        
        talking = 0;
        return "";
    }

    TP->add_prop("_toron_standard_quest_01", 1);     
    lines = explode(read_file(TAKCHUK_STORY_01), "\n");
    story_line(0, TP, TO);   

    
    return "";
}

string
start_story_standard()
{

    if(talking)
    {    
        return "";
    }
    
    talking = 1;
    
    setuid();
    seteuid(getuid());
    
    if(TP->test_bit("Krynn",3,18))
    {
        command("say You have helped us enough.");
        
        talking = 0;
        return "";
    }
    else
    {
        TP->add_prop("_toron_standard_quest_01", 1); 
        lines = explode(read_file(TAKCHUK_STORY_02), "\n");
        story_line(0, TP, TO);        
    }
    
    return "";
}

/*
 * Function name: calculate_Experience
 * Description  : Add the appropriate amount of experience to the
 *                player for solving the quest.
 */
 
void
calculate_experience(object player, int penalty)
{

    int xp_base = 12000; 
    int final_xp = 0;

    if(player->test_bit("Krynn", 3, 18))
    {
	command("say Hold on. You have done this before have you not?  "+
	        "I will not reward you for helping us this time. ");	
	return;
    }

    player->catch_msg("You feel more experienced!\n");

    final_xp = xp_base - penalty;
    
    if(player->query_wiz_level())
    {
	player->catch_msg("XP: " + final_xp + "\n");
    }
    
    player->add_exp_quest(final_xp, 0);
    player->set_bit(3, 18);

    K_QUEST_LOG("quest","Toron tribe quest", player, final_xp);

    return;

}

/*
 * Function name: reward_standard
 * Description  : Rewards the player for finding the missing
 *                battle standard.
 */
 
void
reward_standard(object ob, object from, object me)
{
    object wooden_case = present("_ornate_wooden_case", from);
   
    if(wooden_case)
    {
        wooden_case->remove_object();
    
        command("say Ah! There it is! And you have brought " +
                "the case as well! ");
                
	from->catch_msg(QCTNAME(me) + " eagerly takes an ornate " +
	                "wooden case from you. \n");
	    
        tell_room(environment(me), QCTNAME(me)+ 
                  " eagerly takes an ornate wooden case from " + 
                  QTNAME(from) + ".\n", from);  
            
        command("say This will surely raise the morale " +
                "in the camp. I will bring the good news right away, " +
                "and don't worry, I'll tell them I found it. Since you " +
                "are not from the tribe and... well you know. "); 
        command("say I shall honour our agreement and reward you though.");

        /* 
         * Maximum reward is given if the player has successfully
         * cleared all "checkpoints". That is, has recieved the map,
         * traded for the standard, and participated in killing the
         * captain on the Bloodsea. See quest info for toron_standard_quest
         * for additional information.
         */
                
        if(from->query_prop("_toron_standard_quest_02", 1) && 
           from->query_prop("_toron_standard_quest_03", 1) && 
           from->query_prop("_toron_standard_quest_04", 1))
        {    
            calculate_experience(from,0);
        }
        
        /* 
         * Slightly less experience if player has NOT participated
         * in killing the captain on the Bloodsea. Assisting is enough,
         * killing blow is not needed.
         */        
        
         else if(from->query_prop("_toron_standard_quest_02", 1) && 
                from->query_prop("_toron_standard_quest_04", 1))
         {    
             calculate_experience(from,2000);
         }           

        /* 
         * Very little XP if player has asked for the quest and then
         * been given / found everything lying around.
         */ 
         
         else 
         {
             calculate_experience(from,8000);
         }
                
         tell_room(environment(me), QCTNAME(me) +
                  " leaves east.\n");
        
         me->remove_object();
    }

    /* 
     * Less experience if player has only found the standard without
     * the case. No chance of returning with the case later since the
     * questmaster clearly told the player a bonus will be given for
     * finding the case.
     */ 
     
    else
    {
        command("say Ah! There it is!");
        command("say It is a shame you didn't find the case as well.");
        command("say Nontheless, this will surely raise the morale " + 
                "in the camp. I will bring the good news right away, " +
                "and don't worry, I'll tell them I found it. Since " +
                "you are not from the tribe and... well you know. "); 
        command("say I shall honour our agreement and reward you though.");

        if(from->query_prop("_toron_standard_quest_02", 1) && 
           from->query_prop("_toron_standard_quest_03", 1) && 
           from->query_prop("_toron_standard_quest_04", 1))
        {    
            calculate_experience(from,5000);
        }
        
              
        else if(from->query_prop("_toron_standard_quest_02", 1) && 
               from->query_prop("_toron_standard_quest_04", 1))
        {    
            calculate_experience(from,7000);
        }           

        else 
        {
            calculate_experience(from,8000);
        }        
        
        
        tell_room(environment(me), QCTNAME(me) + " leaves east.\n");

        me->remove_object();        
    }
}

/*
 * Function name: reward_case
 * Description  : Rewards the player for finding the missing
 *                case to the battle standard. No reward if 
 *                the case is found without finding the 
 *                standard.
 */
 
void
reward_case(object ob, object from, object me)
{

    object *my_inventory;
    int standard_check = 0;
    
    command("open case");
    command("get all from case");

    my_inventory = all_inventory(me);
    
    for(int i = 0; i < sizeof(my_inventory); i++)
    {
        if(my_inventory[i]->id("_deep_green_battle_standard"))
        {
            standard_check = 1;    
        }
    }

   /* 
    * Maximum reward is given if the player has successfully
    * cleared all "checkpoints". That is, has recieved the map,
    * traded for the standard, and participated in killing the
    * captain on the Bloodsea. See quest info for toron_standard_quest
    * for additional information.
    */
     
    if(standard_check == 1)
    {
        command("say Ah! There it is! Inside the case and all. " +
                "Perfect.");
        command("say This will surely raise the morale in the " +
                "camp. I will bring the good news right away, " +
                "and don't worry, I'll tell them I found it. Since " +
                "you are not from the tribe and... well you know. "); 
        command("say I shall honour our agreement and reward you though.");
        
        if(from->query_prop("_toron_standard_quest_02", 1) && 
           from->query_prop("_toron_standard_quest_03", 1) && 
           from->query_prop("_toron_standard_quest_04", 1))
        {    
            calculate_experience(from,0);
        }
        
              
        else if(from->query_prop("_toron_standard_quest_02", 1) && 
               from->query_prop("_toron_standard_quest_04", 1))
        {    
            calculate_experience(from,2000);
        }           

        else 
        {
            calculate_experience(from,8000);
        }

        tell_room(environment(me), QCTNAME(me) + 
                  " leaves east.\n");

        me->remove_object();
    }

    else if(standard_check == 0)
    {    
        object battle_standard = 
        present("_deep_green_battle_standard", from);

        if(battle_standard)
        {
            battle_standard->remove_object();
    
            command("say Ah, the case! And you have brought the " +
                    "standard as well! ");

            from->catch_msg(QCTNAME(me) + " eagerly takes a " +
                            "deep green battle standard from you. \n");

            tell_room(environment(me), QCTNAME(me) + 
                      " eagerly takes a deep green battle standard from " +
                      QTNAME(from) + ".\n", from);      

            command("say This will surely raise the morale in " +
                    "the camp. I will bring the good news right " +
                    "away, and don't worry, I'll tell them I found " +
                    "it. Since you are not from the tribe and..." +
                    "well you know. "); 
            command("say I shall honour our agreement and " +
                    "reward you though.");  

        if(from->query_prop("_toron_standard_quest_02", 1) && 
           from->query_prop("_toron_standard_quest_03", 1) && 
           from->query_prop("_toron_standard_quest_04", 1))
        {    
            calculate_experience(from,0);
        }
        
              
        else if(from->query_prop("_toron_standard_quest_02", 1) && 
               from->query_prop("_toron_standard_quest_04", 1))
        {    
            calculate_experience(from,2000);
        }           

        else 
        {
            calculate_experience(from,8000);
        }

            tell_room(environment(me), QCTNAME(me) + 
                      " leaves east.\n");

            me->remove_object();
        }

        /* The case is not accepted without the standard. */
        
        else
        {
            command("say Oh! The case for the standard.");
            command("open case");
            command("say Hmm, it's empty. I have no use for an " +
                    "empty case. You might as well keep it until " +
                    "you find the standard. ");
            
            tell_room(environment(me), QTNAME(me) + " gives the " +
                      "ornate wooden case back to " + QTNAME(from) + 
                      ".\n", from); 
        
            from->catch_msg(QCTNAME(me) + " gives the ornate wooden case " +
                            "back to you.\n"); 
                            
            ob->move(from, 1);                
                            
        }
    }
}

/*
 * Function name: give_items_back
 * Description  : Gives everything that is not the case or the standard
 *                back to the player.
 *                NOTE: Called using an alarm. 
 */ 
 
void
give_items_back(object ob, object from, object me)
{
    string item = LANG_ASHORT(ob); 
    
    me->command("say I don't want this.");
    
    tell_room(environment(me), QTNAME(me) + " gives " +
              item + " back to " + QTNAME(from) + ".\n", from); 
        
    from->catch_msg(QCTNAME(me) + " gives " + item + 
                    " back to you.\n");                            
    
    ob->move(from, 1);    
}

/*
 * Function name: quest_items
 * Description  : Checks if items given are the items
 *                wanted for the quest.
 */

void
quest_items(object ob, object from, object me)
{
    if(ob->id("_deep_green_battle_standard"))
    {
 	    
        reward_standard(ob, from, me);

    }

    else if(ob->id("_ornate_wooden_case"))
    {
   	    
        reward_case(ob, from, me);


    }
    else
    {
        set_alarm(0.1, 0.0, &give_items_back(ob, from, me));
    }

}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
        
    if (!interactive(from))
    {
        return;
    }

    set_alarm(0.1, 0.0, &quest_items(ob, from, TO));;

}

void
return_intro(object me) /* NOTE: Function called using an alarm. */ 
{
    me->command("introduce myself");
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
        set_alarm(1.0, 0.0, &return_intro(TO));
    }
}
    
void
attacked_by(object ob)
{
    command("emote growls: I might be old, but I am not dead like you!");
}

