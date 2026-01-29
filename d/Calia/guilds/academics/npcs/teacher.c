/* 
 * Teacher for the Academy of Elemental Arts
 * 
 * Samoht is the Teacher for the Academy of Elemental Arts.
 * He teaches the channeling classes that allow students to
 * gain spells.
 *
 * Created by Petros, December 2009
*/ 

#pragma save_binary

#include "../defs.h" 
#include <wa_types.h> 
#include <macros.h> 
#include <tasks.h> 
#include <options.h> 
#include <files.h> 
#include <cmdparse.h> 
#include <composite.h>

inherit "/d/Calia/gelan/monsters/stdaided";
inherit "/d/Calia/std/remember"; 

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <formulas.h>

public void 
create_monster() 
{
    if (!IS_CLONE) 
        return; 
        
    set_name("samoht"); 
    set_living_name("samoht");
    add_name("teacher"); 
    set_race_name("elf"); 
    set_adj(({"stern", "mindful"})); 
    set_title("the Teacher for the Gelan Academy of Elemental Arts"); 
    set_long("Before you stands a modest elf in simple brown robes. He is in "
        + "charge of teaching the channeling classes at the Academy. He "
        + "seems deeply engaged in his work and you doubt he would have time "
        + "for conversation of any kind.\n"); 

   set_stats(({130, 145, 135, 148, 150, 120 })); 
   set_hp(query_max_hp());
   
   // Add Skills Here
   set_skill(SS_UNARM_COMBAT, 100); 
   set_skill(SS_WEP_CLUB, 100); 
   set_skill(SS_PARRY, 100); 
   set_skill(SS_DEFENCE, 100); 
   set_skill(SS_AWARENESS, 60); 
   set_skill(SS_BLIND_COMBAT, 100); 
   add_prop(NPC_I_NO_RUN_AWAY, 1); 
   add_prop(CONT_I_HEIGHT, 130); 
   add_prop(CONT_I_WEIGHT, 70000); 
   add_prop(NPC_I_NO_UNARMED, 1); // when wielding a weapon, don't use unarmed
   set_alignment(0); 
   set_gender(G_MALE);
   
   set_default_answer("@@default_response", 1);
   
   add_ask( ({ "channel", "channeling", "class", "task", "permission" }),
      "say Don't bother me with that. Find the taskmaster Amjal. He should "
    + "have more time than me for this.", 1);
}

public int
second_life(object killer)
{
    object ghost; 

    ::second_life(killer); 
    log_file("academic", ctime(time()) + ": Samoht killed by " + 
                      killer->query_real_name() + ".\n"); 
    seteuid(getuid()); 
    ghost = clone_object("/d/Calia/gelan/objects/ghost"); 
    ghost->set_ghost_des("stern mindful male elf"); 
    ghost->set_duration(900); 
    ghost->move(killer); 
    ghost->start_haunt(); 

    return 0; 
}

public string
default_response()
{
    object player = this_player();
    string * random_response = ({
        "Shh.. I am busy teaching a class here!",
        "Not now! I am teaching at the moment, can't you see?!?",
        "I do not have time for questions.",
        "What? Hmm??? Not now. Teaching here.",
        "Ask someone else, please.",
        "If you are not here for channeling, I really do not have the "
            + "time for you."
        });
    
    return "say " + random_response[random(sizeof(random_response))];
}
