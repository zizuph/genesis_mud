/*
 * Who          : Corth de-Orilg, a smelly confident male minotaur
 * Located      : Sailing the Bloodsea on a minotaur warship.
 *                /d/Ansalon/goodlund/bloodsea/living
 * Description  : The minotaur captain of the Orilg tribe. Hold clues
 *              : and items for the Toron_missing_standard quest.
 * Base file    : Made to inherit "minotaur_base" in the same DIR.
 * Made by      : Cherek, Feb 2007
 */

#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit T_MINOTAUR;

#define MAP BOBJ + "mithas_map.c"
#define CASE BOBJ + "wooden_case.c"
#define PLATEMAIL BOBJ + "platemail.c"
#define CUTLASS BOBJ + "cutlass.c"
#define CLOAK BOBJ + "red_cloak.c"
#define CORTH_STORY_01 (BNPC + "corth_story_01.txt")
#define CORTH_STORY_02 (BNPC + "corth_story_02.txt")
#define CORTH_STORY_03 (BNPC + "corth_story_03.txt")

int talking = 0;

/* Global variable for telling stories. */
string *lines = ({ });

string start_story_standard();
string start_story_war();
string continue_story_war(object player, object me);
void add_ask_act();
void arm_me(object me);

void
create_minotaur()
{
    set_type("CAPTAIN");  /* Set the type of minotaur, basically defines 
                             how powerful  his special is in the base 
                             file. */

    set_name("corth");
    set_living_name("corth");	    
    set_title("de-Orilg, Captain of the Windrider");
    add_name("_orilg_standard_mino");
    set_adj("smelly");   
    set_adj("confident");

    set_stats(({ 180+random(40), 220+random(40), 
                 180+random(40), 80+random(40), 
                 80+random(40), 80+random(40) }));

    set_gender(G_MALE);

    set_long("Before you stands a large creature. He is half human " +
             "and half bull leading you to believe this must be a " +
             "minotaur. His skin is thick and covered with a deep " +
             "brown fur but his most noticable feature are the two " +
             "long and very sharp horns growing on his head. He " +
             "proudly bears the traditional marks of a minotaur " +
             "from the Orilg tribe.\nHe is tall and fat for a " +
             "minotaur. \n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_ask_act();

    set_alarm(0.1, 0.0, &arm_me(TO));

    setuid();
    seteuid(getuid()); 

}

int query_max_hp() 
{
    return 5000; /* Extra HP. */ 
}

void arm_me(object me) /* NOTE: Function called using an alarm. */ 
{
    clone_object(CASE)->move(me, 1);
    clone_object(CLOAK)->move(me, 1);
    clone_object(PLATEMAIL)->move(me, 1);
    clone_object(CUTLASS)->move(me, 1);
    me->command("wear all");
    me->command("wield all");
}

void
add_ask_act()
{

    add_ask(({"quest", "help", "task"}),
              "say Yeah? Do I look like I care?" ,1);

    add_ask("toron", 
            "say From what I hear they do not exist enymore.", 1);

    add_ask("windrider",
            "say You're standing on her deck.", 1); 

    add_ask("ship", 
            "say You mean the Windrider? You're standing on her deck.", 1);

    add_ask(({"case", "wooden case"}), 
              "say What about it? Its mine.", 1);

    add_ask(({"standard", "battle standard"}), start_story_standard);

    add_ask(({"war", "wars"}), start_story_war);  
    
    set_default_answer("emote ignores you.",1);

    set_act_time(50+random(50));

    add_act("emote growls: What are you doing on my ship?");
    add_act("say Maybe you can help us fish? As bait!");
    add_act("emote laughs at you.");
    add_act("say This ship is the fastest on the Bloodsea.");
    add_act("emote looks at you.");
    add_act("emote grumbles unhappily");
    add_act("say The pathetic Torons will soon be extinct. ");
    
    seq_addfirst("_mon_ran_act", 1*random(10));
}

/*
 * Function name: give_map
 * Description  : Gives the player the map to finding the battle 
 *                standard in the toron_standard_quest.
 */ 
 
void
give_map(object player, object me)
{
    string player_name = player->query_real_name();

    if(present(player, environment(me)))
    {
        clone_object(MAP)->move(player, 1);

        tell_room(environment(me), QTNAME(me) + " gives a " + 
                  "newly drawn map to " + QTNAME(player) + ".\n", player);
        
        player->catch_msg(QCTNAME(me) + " gives you a newly drawn map. \n");
        
        player->add_prop("_toron_map", 1);

    }
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
    set_default_answer("say Be quiet and listen!",1);
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
story_line(int index, int story, object player, object me)
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
        
        if(story == 2)
        {
            if(player->query_prop("_toron_map")) 
            {
                me->command("say Wait a minute. I've told you this " +
                            "already. Why are you still here?"); 

                add_ask_act();
                talking = 0;
            }
            
            else
            {
                continue_story_war(player, me);
            }         
        }
         
        if (story == 3)
        {
             give_map(player, me);
        }
             
        add_ask_act();
        talking = 0;
        
        return;
    }

    delay = atoi(lines[index]);
    if (delay > 0)
    {           
        set_alarm(itof(delay), 0.0, &story_line(index + 1, story, player, me));
        return;
    }

    me->command(lines[index]);
    story_line(index + 1, story, player, me);
}

/*
 * Function name: start_story_"xxx" / continue_story_"xxx"
 * Description  : These functions reads a text-file containing all the 
 *                commands for the NPC to tell a story. Each story has
 *                its own text file.
 */
 
string
start_story_standard()
{
   
    TP->add_prop("_toron_standard_quest_02", 1);

    if(talking)
    {    
        return "";
    }
    
    talking = 1;
    
    setuid();
    seteuid(getuid());
    
    lines = explode(read_file(CORTH_STORY_01), "\n");
    story_line(0, 1, TP, TO);
    
    TP->add_prop("_toron_standard_quest_02", 1);
    
    return "";
}

string
start_story_war()
{

    TP->add_prop("_toron_standard_quest_02", 1);
    
    if(talking)
    {    
        return "";
    }
    
    talking = 1;
    
    setuid();
    seteuid(getuid());

    lines = explode(read_file(CORTH_STORY_02), "\n");
    story_line(0, 2, TP, TO);

    return "";
}

string
continue_story_war(object player, object me)
{    
    talking = 1;
    
    setuid();
    seteuid(getuid());

    lines = explode(read_file(CORTH_STORY_03), "\n");
    story_line(0, 3, player, me);
}

void
enter_inv(object ob, object from)
{ 

    string the_object = ob->short();
        
    ::enter_inv(ob, from);
    
    if (!interactive(from))
    {
	return;
    }
    
    if(ob->id("_deep_green_battle_standard"))
    {
        if(from->query_prop("_toron_standard_quest_02", 1)) 
        {   
            command("put standard in case");
            command("close case");
            command("say Ah, that's the one. Excellent! This is the final " +
                    "symbol of our victory over the puny Torons. History " +
                    "will know that I the great Captain Corth de-Orilg " +
                    "found it myself. No need to reward you when I have it " +
                    "now is there? Now get off my ship! ");
            command("cackle");
        }
        else
        {
            command("Hey! It's the standard of the pathetic Torons. " + 
                    "Sweet. Thanks for giving it to me. Now get off " +
                    "my ship.");
        }
    }
    else
    {        
        command("say Huh? I don't want this."); 
        
        tell_room(environment(TO), QTNAME(TO) + " gives the " +
                  the_object + " back to " + QTNAME(from) + ".\n", from);
                  
        from->catch_msg(QCTNAME(TO) + " gives the " + the_object + " back " +
                        "to you.\n");
            
        ob->move(from);
    }
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

/*
 * Function name: attacked_by
 * Description  : If the player is doing the toron_missing_standard
 *                quest, a prop is added that the player has attacked
 *                Corth. Failure to participate in combat with him
 *                means slightly less XP reward from quest.
 */

void
attacked_by(object ob)
{
    if(ob->query_prop("_toron_standard_quest_01"))
    {
        ob->add_prop("_toron_standard_quest_03", 1);
    }
    command("emote laughs: Finally! Some entertainment!");
}
