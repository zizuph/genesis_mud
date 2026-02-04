/*
 * Gate Keeper who can absolve enemies of Calathin, once.
 * Coded by Shinto 111599
 *
 * Too long a memory. Some people have been here for a dozen years.
 * Allowing for multiple absolutions.
 *   -Lilith Feb 2009
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include "guard.h"
#include "/d/Terel/include/quest_bits.h"
#define ARM_DIR CALATHIN_DIR + "armour/"
#define WEP_DIR CALATHIN_DIR + "weapon/"
public string absolve();

void dress_me();


public string
absolve()
{
    setuid();
    seteuid(getuid());
    GUARD_MANAGER->absolve(this_player());
    TP->stop_fight();

    return "";
}



public string
reply_enemy()
{
    command("say Enemies of Calathin tend to have done something "+
                   "against the people of Calathin.");
    command("say Killed someone important, or killed several people.");
    command("say Enemies aren't welcome within the walls of the city "+
                   "and will be attacked by the town guards if they find a "+
                   "way to enter.");
    command("say I can absolve enemies who wish to repent, "+
                   "but only once.");
    return "";
}


public string
reply_repent()
{
    object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");

    if(TP->test_bit("Terel",  QUEST_CAL_GROUP, QUEST_ENE_BIT) &&
        kill_logger->query_killer(TP->query_name()))
    {
        kill_logger->remove_killer(TP->query_name());
        command("say I've seen your face before.  You'd better not make a habit of this.");
        write_file(CALATHIN_DIR + "log/absolved",TP->query_name() + " was absolved. " + 
            ctime(time()) + "\n");
        absolve();      
        return "";

    }

    if(TP->test_bit("Terel", QUEST_CAL_GROUP, QUEST_ENE_BIT))
    {
        command("say You've been absolved already, I suggest you walk "+
                       "lightly within the walls of Calathin.");
        return "";
    }
   
    if(kill_logger->query_killer(TP->query_name()))
    {
        command("say This will be your one and only chance.");
        command("say You are hereby removed as an enemy of Calathin.");
        kill_logger->remove_killer(TP->query_name());
        TP->set_bit(QUEST_CAL_GROUP, QUEST_ENE_BIT);
        command("say From this day forth, if you become an enemy of "+
                       "Calathin again, you will never be absolved of your "+
                       "crimes.");
        write_file(CALATHIN_DIR + "log/absolved",TP->query_name() + " was absolved. " + ctime(time()) + "\n");

    absolve();     

   
        return "";
    }
    
    command("say You are no enemy of Calathin, you need not be absolved "+
                   "of any crimes.");
    command("say As a certain dwarf use to say to me, Walk in Glory.");
    return "";
}

             
public void
create_monster()
{
    set_name("garreth");
    set_living_name("garreth");
    set_title("Blackmane, Sergeant of the Guard");
    set_adj("tall");
    set_adj("muscular");
    MALE;
    set_race_name("human");
    set_long("In his late thirties, this man looks to be someone of "+
                  "authority. He has long brown haired braided down his "+
                  "back. His face has sharp features and his eyes bare "+
                  "down on you intently.\n");
    add_prop(OBJ_M_HAS_MONEY, random(200));
    set_stats(({125, 125, 125, 125, 125, 125 }));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_chat_time(5);
    add_chat("The goblins will come again from the north.");
    add_chat("Enemies seem to be coming out of the woodwork.");
    add_chat("Few come to change their ways these days.");



    add_ask(({"absolve","repent","forgive"}), reply_repent, 1);
    add_ask(({"enemy","enemies"}), reply_enemy, 1);
    dress_me();

}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}


void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(ARM_DIR + "stud_armour")->move(TO);
    clone_object(ARM_DIR + "stud_greaves")->move(TO);
    clone_object(ARM_DIR + "stud_bracers")->move(TO);
    clone_object(ARM_DIR + "stud_cap")->move(TO);      
    switch(random(3)) {
        case 0 :  clone_object(WEP_DIR + "longsword")->move(TO);
                      clone_object(WEP_DIR + "shortsword")->move(TO);   
                      break;
        case 1 :  clone_object(WEP_DIR + "longsword")->move(TO);
                      break;
        case 2 :  clone_object(WEP_DIR + "battleaxe")->move(TO);
                      break;
    }
    command("wield weapons");
    command("wear armours");
}




#define KILLS_CAL "_kills_cal"


void
do_die(object killer)
{
    int i;
    object *enemies;

    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    for (i=0; i<sizeof(enemies); i++)
    {
        if(enemies[i]->query_prop(KILLS_CAL) > 6)
        {
            object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
            kill_logger->add_killer(enemies[i]->query_name());
        }
        enemies[i]->add_prop(KILLS_CAL,
                           enemies[i]->query_prop(KILLS_CAL) + 3);
    }
    if(killer->query_prop(KILLS_CAL) > 6)
    {
        object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
        kill_logger->add_killer(killer->query_name());
    }
    killer->add_prop(KILLS_CAL,
                       killer->query_prop(KILLS_CAL) + 3);
    ::do_die(killer);
}


