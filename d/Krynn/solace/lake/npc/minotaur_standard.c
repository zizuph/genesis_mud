/*
 * Who          : Standard minotaurs, a random random male/female minotaur.
 * Located      : The Toron minotaur village near Crystalmir Lake outside
 *                Solace.
 *                /d/Krynn/solace/lake/npc
 * Description  : Standard minotaurs for the Toron village. Wields axe,
 *                 sword or nothing.
 * Base file    : Made to inherit "minotaur_base".
 * Made by      : Cherek, Feb 2007
 */
 
#include "../local.h"
#include <money.h>

#define ARMOUR OBJ + "breastplate.c"
#define SWORD OBJ + "great_sword.c"
#define AXE OBJ + "great_axe.c"

inherit MINOTAUR;

string *adjlist = ({ "savage", "brutal", "mean", "violent",
                     "ugly", "wild", "fragile", "large", 
                     "massive", "hairy", "muscular"});
      
string *adjlist2 = ({ "young", "old",  "ancient",
                      "adult" });

void arm_me(object me);

void
create_minotaur()
{

    set_type("STANDARD");

    add_name("_toron_standard_mino");

    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_adj(adjlist2[(random(sizeof(adjlist2)))]);

    set_gender(gender); 

    if(gender == 1)
    {
        set_long("Before you stands a large creature. She is half human " +
                 "and half bull leading you to believe this must be a " + 
                 "minotaur. Her skin is thick and covered with a deep " +
                 "brown fur but her most noticable feature are the two " +
                 "long and very sharp horns growing on her head. She " +
                 "proudly bears the traditional marks of a minotaur " +
                 "from the Toron tribe.\nShe is tall and lean for " +
                 "a minotaur. \n");
    }
            
    else
    {
        set_long("Before you stands a large creature. He is half human " +
                 "and half bull leading you to believe this must be a " +
                 "minotaur. His skin is thick and covered with a deep " +
                 "brown fur but his most noticable feature are the two " +
                 "long and very sharp horns growing on his head. He " +
                 "proudly bears the traditional marks of a minotaur " +
                 "from the Toron tribe.\nHe is tall and lean for " +
                 "a minotaur. \n");
    }

    set_act_time(60);
    add_act("emote snorts violently.");
    add_act("emote chuckles silently at you.");
    add_act("say One day we will regain our honour! ");
    add_act("say The Orilg tribe will suffer greatly. We shall take " +
            "back what was stolen from us. ");
    add_act("say Kadez is a strong leader, he will lead us to revenge.");
    add_act("say What is your business with the proud Toron tribe?");
    add_act("say This is our land now and none shall take it from us.");
    add_act("say The Dragonarmies have a camp nearby, surely to spy on us.");
    add_act("say The puny draconians would never dare enter our village.");
    add_act("say You look a little lost. Maybe you should go see the " +
            "sage. He can take a look inside your head!");
            
    add_ask("sage", 
            "say Takchuk de-Toron is our Sage. Why?", 1); 
        
    add_ask(({"dragonarmy", "dragon army", "dragonarmies"}),
              "say They fear us. They all do.", 1);  
        
    add_ask("kadez", 
            "say What about him? He is the chieftain.", 1);
        
    add_ask(({"toron", "toron tribe", "tribe"}), 
              "say That would be us. You on the other hand do " +
              "not belong here.", 1);
  
    add_ask(({"orilg", "orilg tribe"}), 
              "emote eyes are filled with hatred and rage.", 1);

    add_ask(({"land", "lands", "stolen"}), 
              "say They had no right, but they came looking for war, and " +
              "war they will have.", 1);
        
    add_ask("war", 
            "say We are at war with the Orilg tribe, may their " +
            "souls never find rest", 1);
              
    set_default_answer("emote ignores you.",1);

    set_alarm(0.1, 0.0, &arm_me(TO));
       
    setuid();
    seteuid(getuid());   
}
  
/*
 * Function name: arm_me
 * Description  : Arms the minotaur with either a sword an
 *                axe or unarmed. Many minos in the village are
 *                not warriors, so chance of unarmed is slightly
 *                greater.
 *                NOTE: Called using an alarm. 
 */   

void arm_me(object me) 
{
    clone_object(ARMOUR)->move(me, 1); 
    me->command("wear all");

    MONEY_MAKE_GC(1 + random(3))->move(me, 1);   
    
    switch (random(4))
    {
        case 0:
            clone_object(AXE)->move(me, 1);
            me->command("wield all");    
            break;
          
        case 1:
            clone_object(SWORD)->move(me, 1);
            me->command("wield all");   
            break;

    }
}

void
attacked_by(object ob)
{

    object *minotaurs = all_inventory(environment(TO));
    
    switch (random(3))
    {
        case 0:
            command("shout For the tribe!");
            break;
         
        case 1:
            command("emote growls: Die, enemy of the tribe.");
            break;
         
        default:
            command("say You are as good as dead!"); 
    }

    for(int i = 0; i < sizeof(minotaurs); i++)
    {
        if(minotaurs[i]->id("_toron_standard_mino"))
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

