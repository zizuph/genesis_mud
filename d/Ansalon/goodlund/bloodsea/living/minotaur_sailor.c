/*
 * Who          : Standard sailor minotaurs, a random male minotaur.
 * Located      : Sailing the Bloodsea on a minotaur warship.
 *                /d/Ansalon/goodlund/bloodsea/living
 * Description  : Standard minotaurs for the warship.
 * Base file    : Made to inherit "minotaur_base".
 * Made by      : Cherek, Feb 2007
 */
 
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

#define CUTLASS BOBJ + "lesser_cutlass.c"

inherit T_MINOTAUR;

string *adjlist = ({ "proud", "salty", "rugged", "weathered",
                     "experienced", "furry"});
      
string *adjlist2 = ({ "tall", "sturdy",  "strong",
                      "muscular" });

void arm_me(object me);

void
create_minotaur()
{

    set_type("STANDARD");

    add_name("_orilg_standard_mino");

    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_adj(adjlist2[(random(sizeof(adjlist2)))]);

    set_gender(G_MALE); 

    set_long("Before you stands a large creature. He is half human " +
             "and half bull leading you to believe this must be a " +
             "minotaur. His skin is thick and covered with a deep " +
             "brown fur but his most noticable feature are the two " +
             "long and very sharp horns growing on his head. He " +
             "proudly bears the traditional marks of a minotaur " +
             "from the Orilg tribe.\nHe is tall and lean for " +
             "a minotaur. \n");

    set_act_time(60);
    add_act("emote snorts violently.");
    add_act("emote laughs silently.");
    add_act("emote grumbles unhappily.");
    add_act("emote carefully inspects the hull of the ship.");
    add_act("say Let's throw this one back into the sea?");
    add_act("say What are you doing here?");
    add_act("say You better jump overboard before someone gets hurt!");
    
    set_default_answer("say Stop bothering me. Ask the captain.",1);

    set_alarm(0.1, 0.0, &arm_me(TO));
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    setuid();
    seteuid(getuid());   
}
  
/*
 * Function name: arm_me
 *                NOTE: Called using an alarm. 
 */   

void arm_me(object me) 
{

    clone_object(CUTLASS)->move(me, 1);
    me->command("wield all");   

}

void
attacked_by(object ob)
{

    object *minotaurs = all_inventory(environment(TO));
    
    switch (random(3))
    {
        case 0:
            command("shout Orilg! Orilg!");
            break;
         
        case 1:
            command("emote growls angrily.");
            break;
         
        default:
            command("say I hope you can swim!"); 
    }

    for(int i = 0; i < sizeof(minotaurs); i++)
    {
        if(minotaurs[i]->id("_orilg_standard_mino"))
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
                command("emote cackles with glee.");
                break;

            case 1:
                command("emote laughs madly..");
                break;
         
            default:
                command("emote snarls threatingly.");
        }  
    }

    command("kill " + player);
    command("kill " + player);   
}   

