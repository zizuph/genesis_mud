/*
 * Who          : A randomadj randomadj male minotaur
 * Located      : The Hestos tribe minotaur camp in southern Mithas.
 *                /d/Ansalon/goodlund/nethosak/forest/npc
 * Description  : Standard minotaurs. Will only appear if "Helamin" or
 *                "Galdan" is attacked. (minotaurs in the same camp).
 * Base file    : Made to inherit "minotaur_base".
 * Made by      : Cherek, Feb 2007
 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit T_MINOTAUR;

#define AXE MWEP + "long_axe.c"
#define CHAINMAIL MARM + "light_chainmail.c"

string *adjlist = ({ "savage", "brutal", "mean", "violent",
                     "ugly", "wild", "fragile", "large", 
                     "massive", "hairy", "muscular"});

string *adjlist2 = ({ "young", "old",  "ancient",
                      "adult" });

void arming_me(object me);

void
create_minotaur()
{

    set_type("HESTOS"); 
    
    set_name("minotaur");
    set_race_name("minotaur"); 

    add_name("_hestos_mino");

    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_adj(adjlist2[(random(sizeof(adjlist2)))]);
    
    set_stats(({ 150, 150, 150, 100, 100, 100 }));    
    
    set_gender(G_MALE);

    set_long("Before you stands a large creature. He is half human and " +
             "half bull leading you to believe this must be a minotaur. " +
             "His skin is thick and covered with a deep brown fur but " + 
             "his most noticable feature are the two long and very " +
             "sharp horns growing on his head. He proudly bears the " +
             "traditional marks of a minotaur from the Hestos tribe.\n" +
             "He is tall and lean for a minotaur. \n");
                        
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
attacked_by(object ob)
{
 
    object *minotaurs = all_inventory(environment(TO));

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
    string player = ob->query_real_name();

    command("kill " + player);
    command("kill " + player);    
}   