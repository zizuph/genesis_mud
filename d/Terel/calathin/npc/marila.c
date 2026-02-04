/*
 * marila.c Gem shop keeper.
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
#define KILLS_CAL "_kills_cal"

public string
reply_goblin()
{
    command("say Calathin is safe most of the time, but the tribes do "+
                   "sometimes come down and attack.");
    command("say Goblins are a people we just can't trust though, so "+
                   "we'll let them pass through, but we don't do any business "+
                   "with them.");
    return "";
}

public string
reply_maskyr()
{
    command("say Maskyr Keep is a bad bad city.");
    command("say They want to rule everything.");
    command("say Their Army is powerful! I don't know what will stop them.");
    return "";
}
public string
reply_calathin()
{
     command("say This town has become a sort of center of the land.");
     command("say We're situated as a sort of crossroads between the "+
                    "north and south, as well as the east and west.");
     return "";
}

public string
reply_silver()
{
     command("say The Silver forest is directly to the north of the town.");
     command("say The forest is filled with a variety of animals, a "+
                    "number of dangerous ones too.");
     command("say Nearly everthing from dragons to squirrels.");
     return "";
}

public string
reply_enchanted()
{
    command("say The Enchanted forest is the one south of the town.");
    command("say It's filled with a number of things, as well as some "+
                   "very special creatures, like the Unicorn.");
    return "";
}

public string
reply_last()
{
    command("say Last is the northern most port town on the eastern "+
                   "coast.");
    command("say It's just a small village, last stop before the untamed "+
                   "north you might say.");
    return "";
}

public string
reply_dabaay()
{
    command("say Ahh, Dabaay!");
    command("say I met a nice boy their once.");
    command("sigh wist");
    command("say That town is southeast of here, on the eastern coast.");
    command("say It's just a small fishing village.");
    return "";
}

public string
reply_dragon()
{
    command("say Dragons, dragons, dragons....");
    command("say I've only heard of two so far.");
    command("say A great white that lives on the mountain north of Last.");
    command("say Then there's the red that lives somewhere in the Silver "+
                   "forest.");
    command("say But I'm sure there are more.");
    return "";
}

public string
reply_legion()
{
    command("say The Legion.");
    command("say The Legion is the Army of Maskyr Keep.");
    command("say That foul place.");
    command("frown");
    return "";
}

public string
reply_horse()
{
    command("say Hah! Horses! You'd never see my furry feet leaving "+
                   "the ground.");
    command("say Only place to get horses around here is at Jonas' "+
                   "stable.");
    command("say It's on the north side of town as you head to the north "+
                   "gate.");
    return "";
}

public string
reply_inn()
{
    command("say You need a place to stay?");
    command("say The Silver Tree Inn is your best bet.");
    command("say It's in the southeast corner of the town square");
    return "";
}

public string
reply_pub()
{
    command("say You know thats really bad for you, no matter "+
                   "how much faster you heal.");
    command("say There are a few pubs in Calathin.");
    command("say The Dragon Claw is right next door.");
    command("say The Big Rock is on the south side of the town square.");
    command("say Then there is the <NEED TO NAME> which is <PLACE>.");
    return "";
}

public string
reply_smith()
{
    command("say We have a blacksmith, but no armour or weapon "+
                   "smith.");
    command("say He's on the east side of the town square.");
    return "";
}

public string
reply_ribos()
{
    command("say Ribos is the town to the far west.");
    command("say To be honest, I know very little of it.");
    return "";
}

public string
reply_bags()
{
    command("say That kind of stuff you can get from Talok.");
    command("say His shop is on the north side of the square.");
    command("say You can't miss it! It's in a tree!");
    command("giggle");
    return "";
}

public string
reply_sea()
{
    command("say The Sea of Terel is beautiful!");
    command("say It's a deep deep blue.");
    command("say It runs the length of the eastern coast.");
    return "";
}

public string
reply_mansion()
{
    command("say Oh that place is abandoned.");
    command("say All kinds of ghost stories about that place.");
    command("say No one has seen an of the Avenchir's for years.");
    return "";
}

public string
reply_gypsy()
{
    command("say The gypsies are wonderful people!");
    command("say Always putting on shows, and always lots of "+
                    "games to play!");
    command("say They say there is always a job to be had with "+
                   "the gypsies!");
    return "";
}



public void
create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
                         return;

    set_name("marila");
    set_living_name("marila");
    set_race_name("halfling");
    set_title("Jarvin, Master Appraiser");
    set_adj("small");
    set_adj("brown-haired");
    set_gender(FEMALE);
    set_long("A petite young female halfling. She owns and runs the shop "+
                   "by herself. Long brown hair braided down the center of her "+
                   "back is glittered with various types of gems.\n");

     /* Average stat: 60
     */
     default_config_npc(60);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_AWARENESS, 80);

    set_hp(5500);

    set_all_hitloc_unarmed(50);

    set_chat_time(15);
    add_chat("Hello, welcome to my shop.");
    add_chat("I have a variety of gems to choose from.");
    add_chat("Rubies are my personal favorite.");
    add_chat("The mountains must be rich with all kinds of stones.");
    set_act_time(1);
    add_act("emote dusts off her counters.");

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
    add_ask(({"inn", "Inn", "Silver Tree Inn", "silver tree inn"}), reply_inn,1);
    add_ask(({"pubs","pub"}), reply_pub, 1);
    add_ask(({"smith","smiths"}), reply_smith, 1);
    add_ask(({"Ribos", "ribos"}), reply_ribos, 1);
    add_ask(({"bags","pouch","pouches", "bag", "sack", "sacks", "backpacks",
                    "backpack"}), reply_bags, 1);
    add_ask(({"sea","Sea","sea of terel","Sea of Terel", "sea of Terel"}), 
                    reply_sea, 1);
    add_ask(({"mansion","Mansion","Avenchir","avenchir"}), reply_mansion, 1);
    add_ask(({"gypsy","gypsies","gypsy camp","camp"}), reply_gypsy, 1);



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
