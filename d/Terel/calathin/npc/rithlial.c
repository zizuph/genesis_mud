/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corman.c
 *
 *   
 *  
 * Shinto of Terel 6/98
 *  
 *  
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <money.h>


public string
reply_giants()
{
    command("say The frost giants live farther north "
                   +"then mount Siralan, so attacks by them are rare.");
    return "";
}

public string
reply_goblin()
{
    command("say Feh! Goblins!! We spend more time dealing "+
       "with their filth then we do anything else. Three different "+
       "tribes from the north and northwest, they head south to raid.");
    return "";
}

public string
reply_dragon()
{
    command("say Siralan, the great white dragon that lives in the "+
       "mountain to the north. A fearsome creature, every so often "+
         "he flies down to harass us.");
    return "";
}

public string
reply_calathin()
{
    command("say Calathin lies southwest from here, "+
        "another small trading town likes ours. Head west till you "+
        "reach the cornerstone, then make your way south through "+
        "the Silver forest.");
    return "";
}



create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
					return;

    set_name("corman");
    set_living_name("corman");
    set_race_name("human");
    set_title("Driven, Owner of the Armour Shop of Last");
    set_adj("barrel-chested");
    set_long("A simple man making a living for himself. He stands a good "+
                   "6 feet tall and proudly wanders through his shop dusting "+
                   "and polishing various sets of armour.\n");

     /* Average stat: 60
     */
     default_config_npc(60);

    /* But we want it to have more hitpoints
     */
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_hp(5500);

    set_all_hitloc_unarmed(50);

    set_chat_time(15);
    add_chat("Welcome to my shop!");
    add_chat("The goblins will likely raid again soon.");
    add_chat("If it's not the goblins, it's the frost giants, if it's not the "+
                   "frost giants it's the White!.");
    add_chat("I only deal in armours, Lanc the dwarf runs the Weapon shop.");
    set_act_time(10);
    add_act("emote dusts several sets of armours behind him.");
    add_act("smile warm");
    add_act("emote takes a peek out the window, observing the falling snow.");
    add_ask(({"siralan","Siralan","white","White","the White","dragon"}), 
                      reply_dragon, 1);
    add_ask(({"giants","giant","frost giants"}), reply_giants, 1);
    add_ask(({"goblins","goblin"}),reply_goblin, 1);
    add_ask(({"calathin","Calathin"}), reply_calathin, 1);



}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}

