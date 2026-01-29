/*
 * Who          : Galdan Es-Hestos, a furry green-eyed male minotaur
 * Located      : The Hestos tribe minotaur camp in southern Mithas.
 *                /d/Ansalon/goodlund/nethosak/forest/npc
 * Description  : Will call guards if attacked.
 * Base file    : Made to inherit "minotaur_base".
 * Made by      : Cherek, Feb 2007
 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit T_MINOTAUR;

#define AXE MWEP + "long_axe.c"
#define CHAINMAIL MARM + "light_chainmail.c"
void arming_me(object me);

/* Global variable to define his friend.  */
object my_friend;

/* Global variable that keeps track on if guards have been
   called. 0=call guards. 1=dont call more guards.  */
int guard_check = 0;

void
create_minotaur()
{

    set_type("HESTOS");  

    set_name("galdan");
    set_living_name("_galdan");
    add_name("_hestos_mino");

    set_title("Es-Hestos of Mithas");

    set_adj("furry");   
    set_adj("green-eyed");

    set_stats(({ 150, 150, 150, 100, 100, 100 }));    

    set_gender(G_MALE);

    set_long("Before you stands a large creature. He is half human and " +
             "half bull leading you to believe this must be a minotaur. " +
             "His skin is thick and covered with a deep brown fur but his " +
             "most noticable feature are the two long and very sharp horns " +
             "growing on his head. He proudly bears the traditional marks " +
             "of a minotaur from the Hestos tribe.\n" +
             "He is tall and lean for a minotaur. \n");
             
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_default_answer("say It actually speaks. Just nonsense though.",1);
       
    add_ask(({"standard", "battle standard"}), 
              "say A standard? Funny you should ask. We might have " +
              "found one, depends on who's asking. Anyway, you should " +
              "talk to Halamin. He found it. I mean he might " +
              "have found it." , 1); 
     
    set_alarm(0.1, 0.0, &arming_me(TO));

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
    
    command("say Excellent! Practice!");

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

        /* Tells "Halamin" not to call guards if Galdan has already
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

