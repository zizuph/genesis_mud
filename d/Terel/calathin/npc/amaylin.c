/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * amaylin.c
 *
 * Weaponshop Keeper of Calathin
 * 
 *
 *  Shinto of Terel, 7-18-98
 *  
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <money.h>
#define KILLS_CAL "_kills_cal"

dress_me();

public string
reply_goblin()
{
    command("say The whole town is wary of goblins, with good reason.");
    command("say Farther north several tribes of goblins raid and attack "+
                   "anyone they come across.");
    command("say They've even been known to come this far south.");
    return "";
}

public string
reply_maskyr()
{
    command("say The biggest power in the area is that keep.");
    command("say They don't seem satisfied with that though, and want more.");
    command("say The Legion, their army, is filled with brutes and savages.");
    return "";
}
public string
reply_calathin()
{
     command("say Calathin is a wonderful place.");
     command("say Likely one of the safest towns in all of Terel.");
     return "";
}

public string
reply_silver()
{
     command("say The Silver forest is most of the forest north of the town.");
     command("say Good hunting, lots of deer, moose, rabbit, squirrel. ");
     command("say Dardin can give you good prices for skins and Ramil "+
                    "will give you some coin for the meats.");
     return "";
}

public string
reply_enchanted()
{
    command("say The Enchanted forest is the forest down south.");
    command("say It's filled with all manner of creatures.");
    return "";
}

public string
reply_last()
{
    command("say Thats the small village to the northeast.");
    command("say Just a small port, last town you'll find along the "+
                   "northern coast.");
    return "";
}

public string
reply_dabaay()
{
    command("say Dabaay is the small port town to the southeast.");
    command("say Fishing town, nice friendly people.");
    return "";
}

public string
reply_dragon()
{
    command("say Dragons use to be as common as trees in Terel. ");
    command("say Slowly though, they've killed each other off or been "+
                   "slain by adventurers.");
    command("say Everyone knows of the red that lives in the Silver forest.");
    command("say I know there's a black in the northwest part of the Dragon "+
                   "mountains.");
    return "";
}

public string
reply_legion()
{
    command("say The Legion is the Army of Maskyr Keep.");
    command("say A strong army of brutes and savages.");
    command("say When they march, they bring a fight the likes you've "+
                   "never seen.");
    return "";
}

public string
reply_horse()
{
    command("say You can find horses at Jonas' stable.");
    command("say It's on the north side of town as you head to the north "+
                   "gate.");
    return "";
}

public string
reply_inn()
{
    command("say The Silver Tree is the most comfortable inn.");
    command("say It's in the southeast corner of the town square");
    return "";
}

public string
reply_pub()
{
    command("say I could use a drink myself pretty soon.");
    command("say There are a few pubs in Calathin.");
    command("say The Dragon Claw is off the road to the east gate.");
    command("say The Big Rock is on the south side of the town square.");
    command("say Then there is the Black Cat which is just off the road "+
                   "to the north gate, near the stable.");
    return "";
}

public string
reply_smith()
{
    command("say Just a blacksmith right now, he's on the east side "+
                   "of the town square.");
    return "";
}

public string
reply_ribos()
{
    command("say Ribos is far to the west.");
    command("say Seems they are having a rough time.");
    command("say Had a few refuges move into town.");
    return "";
}

public string
reply_bags()
{
    command("say Talok is the man to talk to about that.");
    command("say His shop is on the north side of the square.");
    return "";
}

public string
reply_sea()
{
    command("say The Sea of Terel runs straight up and down the coast.");
    command("say I've heard some pirates have been seen lately.");
    command("say Might even be some smugglers out there.");
    return "";
}

public string
reply_mansion()
{
    command("say The Avenchir Mansion has a pretty sorted past.");
    command("say Not even sure who lives in there now.");
    command("say Adventurers seem to always come around asking "+
                   "about it though.");
    return "";
}

public string
reply_gypsy()
{
    command("say Their camp is south of town.");
    command("say I take my kids there every few weeks.");
    command("say I'm sure if your looking for a job they'd have "+
                   "something you could do.");
    return "";
}



public void
create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
                         return;

    set_name("amaylin");
    set_living_name("amaylin");
    set_race_name("human");
    set_title("Selvir, Owner of the Weapon Shop of Calathin");
    set_adj("muscular");
    set_adj("brown-haired");
    set_long("A strong well-built man in his thirties. Brown-hair tied in "+
             "a pony tail. He has light-brown eyes and very angular face.\n");

     /* Average stat: 60     */
     default_config_npc(60);

    /* But we want it to have more hitpoints
     */
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_hp(5500);

    set_all_hitloc_unarmed(15);

    set_chat_time(15);
    add_chat("Hello, what can I do for you?");
    add_chat("I'm just a weapons dealer, armours you'll have to see Tariyn,"+
                   " bags and backpacks you should see Talok.");
    set_act_time(1);

    add_ask(({"dragon","dragons"}), reply_dragon, 1);
    add_ask(({"horse","horses",}), reply_horse, 1);
    add_ask(({"goblins","goblin"}),reply_goblin, 1);
    add_ask(({"calathin","Calathin"}), reply_calathin, 1);
    add_ask(({"silver forest","Silver forest","Silver Forest"}), reply_silver,1);
    add_ask(({"enchanted forest","Enchanted forest","Enchanted Forest"}),
                    reply_enchanted, 1);
    add_ask(({"maskyr keep", "Maskyr keep", "Maskyr Keep"}), reply_maskyr, 1);
    add_ask(({"last","Last"}), reply_last, 1);
    add_ask(({"dabaay","Dabaay"}), reply_dabaay, 1);
    add_ask(({"legion","Legion"}), reply_legion, 1);
    add_ask(({"inn", "Inn", "Silver Tree Inn", "silver tree inn"}),reply_inn,1);
    add_ask(({"pubs","pub"}), reply_pub, 1);
    add_ask(({"smith","smiths"}), reply_smith, 1);
    add_ask(({"Ribos", "ribos"}), reply_ribos, 1);
    add_ask(({"bags","pouch","pouches", "bag", "sack", "sacks", "backpacks",
                    "backpack"}), reply_bags, 1);
    add_ask(({"sea","Sea","sea of terel","Sea of Terel", "sea of Terel"}), 
                    reply_sea, 1);
    add_ask(({"mansion","Mansion","Avenchir","avenchir"}), reply_mansion, 1);
    add_ask(({"gypsy","gypsies","gypsy camp","camp"}), reply_gypsy, 1);
    dress_me();
}

void
dress_me()
{
    FIX_EUID;
    
    clone_object(CALATHIN_DIR + "armour/bro_boots")->move(TO);
    clone_object(CALATHIN_DIR + "armour/t_breeches")->move(TO);
    clone_object(CALATHIN_DIR + "armour/w_tunic")->move(TO);
    command("wear all");
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

