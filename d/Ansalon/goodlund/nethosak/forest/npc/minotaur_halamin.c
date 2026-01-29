/*
 * Who          : Halamin Es-Hestos, a hairy green-eyed male minotaur
 * Located      : The Hestos tribe minotaur camp in southern Mithas.
 *                /d/Ansalon/goodlund/nethosak/forest/npc
 * Description  : Gives out the Battle standard for the 
 *                Toron_missing_standard quest. Will call guards if
 *                attacked.
 * Base file    : Made to inherit "minotaur_base".
 * Made by      : Cherek, Feb 2007
 */

#include "/d/Ansalon/common/defs.h"
#include <language.h>
#include "../local.h"
#include <macros.h>

inherit T_MINOTAUR;

#define STANDARD MOBJ + "toron_standard.c"
#define AXE MWEP + "long_axe.c"
#define CHAINMAIL MARM + "light_chainmail.c"
#define HALAMIN_STORY_01 (MNPC + "halamin_story_01.txt")

int talking = 0;

/* Global variable to define his friend.  */
object my_friend;

/* Global variable for telling stories. */
string *lines = ({ });

/* Global variable, used to make sure he only accepts ONE item
   at a time. */   
int i_recieved_item;

/* Global variable that keeps track on if guards have been
   called. 0=call guards. 1=dont call more guards.  */
int guard_check = 0;

void start_story_deal();
void add_ask_act();
void arming_me(object me);

void
create_minotaur()
{

    set_type("HESTOS");
    
    i_recieved_item = 0;
    
    set_name("halamin");
    set_living_name("_halamin");
    add_name("_hestos_mino");
    
    set_title("Es-Hestos of Mithas");
    
    set_adj("hairy");   
    set_adj("green-eyed");
    
    set_stats(({ 200, 200, 200, 100, 100, 100 }));    
    
    set_gender(G_MALE);

    set_long("Before you stands a large creature. He is half human and " +
             "half bull leading you to believe this must be a minotaur. " +
             "His skin is thick and covered with a deep brown fur but his " +
             "most noticable feature are the two long and very sharp horns " +
             "growing on his head. He proudly bears the traditional marks " +
             "of a minotaur from the Hestos tribe.\n" +
             "He is short and lean for a minotaur. \n");
             
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
       
    add_ask_act(); 

    set_alarm(0.1, 0.0, &arming_me(this_object()));

    setuid();
    seteuid(getuid());
}

void arming_me(object me) /* NOTE: Function called using an alarm. */ 
{
    clone_object(CHAINMAIL)->move(me, 1);     
    clone_object(AXE)->move(me, 1); 
    me->command("wear all");
    me->command("wield all");
}

void
add_ask_act()
{       
    set_default_answer("say I have no interest in those matters. Begone.",1);
    
    add_ask(({"quest", "help", "task"}), 
              "say I'm not interested in your problems." ,1); 
        
    add_ask("toron", 
            "say I could care less about the puny Kothas tribes. " ,1); 
        
    add_ask("orilg", 
            "say We have seen their ships, but they would never dare " + 
            "set their dirty feet on our soil" ,1);
        
    add_ask(({"standard", "battle standard"}), start_story_deal);
    
    add_ask("deal", "say A fair deal if you ask me. " ,1);    

    set_act_time(50+random(50));
    add_act("emote growls: I sincerly hope you are lost.");   
    add_act("say This is no place for someone like you.");     
    add_act("emote looks at your with pity.");    
          
    seq_addfirst("_mon_ran_act", 20*random(30));
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
    set_default_answer("say You shall be silent while I speak.",1);
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
        player->add_prop("_hestos_deal", 1);       
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
start_story_deal()
{

    if(talking)
    {    
        return "";
    }
    
    talking = 1;
   
    setuid();
    seteuid(getuid());
        
    if(TP->query_prop("_toron_standard_quest_04")) 
    {
        command("say Uh, I already gave it to you.");
        talking = 0;
    }
                
    else
    {
        lines = explode(read_file(HALAMIN_STORY_01), "\n");
        story_line(0, TP, TO);        
    }

    return "";
}

/*
 * Function name: give_standard
 * Description  : Gives the player the battle standard quest item.
 *                and adds the final prop for the quest.
 *                NOTE: Called using an alarm. 
 */ 
 
string
give_standard(object player, object me)
{
    string player_name = player->query_real_name();  

    if(present(player, environment(me)))
    {
        me->command("emote enters the tent and quickly returns carrying " +
                    "a deep green battle standard.");
                
        clone_object(STANDARD)->move(player, 1);
    
        tell_room(environment(TO), QTNAME(TO) + " gives a " + 
                  "deep green battle standard to " + QTNAME(player) + 
                  ".\n", player);
        
        player->catch_msg(QCTNAME(TO) + " gives you a deep green battle " +
                          "standard.\n");
            
        me->command("shake " + player_name);
    
        player->add_prop("_toron_standard_quest_04", 1); 
        player->remove_prop("_hestos_deal"); 
        i_recieved_item = 0;
    }
}

/*
 * Function name: deal_closed_02
 * Description  : Nothing special, just a delay for the give_standard
 *                function.
 *                NOTE: Called using an alarm. 
 */ 
 
string
deal_closed_02(string item, object player, object me)
{ 
    if(present(player, environment(me)))
    {   
        me->command("say Yeah why not, I'll take it. Anything is probably " +
                    "worth more than this useless flag. Pleasure doing " +
                    "business with you.");
                
        set_alarm(3.0 ,0.0, &give_standard(player, me)); 
    }
}

string    /* NOTE: Function called using an alarm. */ 
deal_closed_01(object ob, object player, object me) 
{ 

    string item = LANG_ASHORT(ob);

    if(present(player, environment(me)))
    {           
        me->command("say So, " + item + "?");
        set_alarm(3.0 ,0.0, &deal_closed_02(item, player, me));
    }    
}

/*
 * Function name: give_items_back
 * Description  : Accepts the first item, gives the rest back to
 *                the player.
 *                NOTE: Called using an alarm. 
 */ 

void
give_items_back(object ob, object player, object me)
{
    string item = LANG_ASHORT(ob);
    
    me->command("say Don't throw all that junk at me. One item " +
                "at a time is enough!"); 
            
    tell_room(environment(me), QTNAME(me) + " gives the " + item + 
              " back to " + QTNAME(player) + ".\n", player);                                 
    
    player->catch_msg(QCTNAME(me) + " gives " + item + 
                      " back to you.\n");                            
    
    ob->move(player, 1);
}

/*
 * Function name: give_items_back_2
 * Description  : Gives everything back to the player.
 *                NOTE: Called using an alarm. 
 */ 

void
give_items_back_2(object ob, object player, object me)
{
    string item = LANG_ASHORT(ob);
    
    me->command("say Hey, I haven't asked you to give me this.");
    
    tell_room(environment(me), QTNAME(me) + " gives " + item + 
              " back to " + QTNAME(player) + ".\n", player); 

    player->catch_msg(QCTNAME(me) + " gives " + item +
                      " back to you.\n");

    ob->move(player, 1);
}

void drop_items(object ob)
{

    command("drop " + ob->short());

}

/*
 * Function name: enter_inv
 * Description  : Checks if the player has asked about the standard,
 *                quest. If not, just gives everything back.              
 */ 
 
void
enter_inv(object ob, object from)
{
     ::enter_inv(ob, from);
    
    if (!interactive(from))
    {
        return;
    }
    
    if(sizeof(query_enemy(-1)) > 0)
    {
        set_alarm(0.1, 0.0, &drop_items(ob));
        
        return;
    
    }
    
    if(from->query_prop("_hestos_deal", 1))     
    {     
         if (i_recieved_item == 1)
         {
             set_alarm(0.1, 0.0, &give_items_back(ob, from, TO));	
             return;
         }
         else
         {
             i_recieved_item = 1;        
             set_alarm(1.0, 0.0, &deal_closed_01(ob, from, TO)); 
         }
    }    
    else
    {
        set_alarm(0.1, 0.0, &give_items_back_2(ob, from, TO));	
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
 * Function name: set_friend
 * Description  : Called when from the room when it resets, sets
 *                variable my_friend to galdan, his minotaur buddy
 *                in his camp.
 */
 
void set_friend(object friend)
{
    my_friend = friend;
}

void guards_reset()
{
    guard_check = 0;
}

void guards_set()
{
    guard_check = 1;
}
/*
 * Function name: attacked_by
 * Description  : Clones up to 6 guards to assist him against
 *                the player. Will not clone more guards if there
 *                are already 6 guards in the room.
 */
 
void
attacked_by(object ob)
{

    object *minotaurs;
    object *guards = all_inventory(environment(TO));   
    
    int guard_counter = 0;
    
    command("say I don't have time for this. Or wait, I do!");

    if(guard_check != 1)
    {
    
        for(int i = 0; i < sizeof(guards); i++)
        {
            if(guards[i]->id("_hestos_mino"))
            {
                guard_counter = guard_counter + 1;
            }
        }

        for(guard_counter; guard_counter < 8; guard_counter++)
        { 
            clone_object(MNPC + "minotaur_hestos_standard.c")
                         ->move(environment(TO), 1); 

            tell_room(environment(TO), "A minotaur rushes " +
                      "out from one of the surrounding tents! \n");
        
            guard_check = 1;
        }  
 
        /* Tells "Galdan" not to call guards if Halamin has already
           done so. */
        if(objectp(my_friend))
        {
            my_friend->guards_set(); 
        }
    } 
    
    minotaurs = all_inventory(environment(TO));
    
    for(int i = 0; i < sizeof(minotaurs); i++)
    {
        if(minotaurs[i]->id("_hestos_mino"))
        {
            if(minotaurs[i]!=TO)
            {
                minotaurs[i]->assisting(ob);
            }
        }
    }
}

void
assisting(object ob)
{
    object *enemies;
    string player = ob->query_real_name();
    
    enemies = query_enemy(-1);

    if(sizeof(enemies) == 0)
    {
        switch (random(3))
        {
            case 0:
                command("emote snorts violently.");
                break;

            case 1:
                command("emote screams loudly.");
                break;
         
            default:
                command("emote lets out a terrible battlecry.");
        }  
    }

    command("kill " + player);
    command("kill " + player);   
}  

