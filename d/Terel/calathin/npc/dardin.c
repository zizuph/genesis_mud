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

#define KILLS_CAL "_kills_cal"

dress_me();

public string
reply_goblin()
{
command("say I'll do business with goblins, so long as they aren't wanted.");
   return "";
}

public string
reply_maskyr()
{
    command("say Maskyr Keep is to the east on the coast.");
    command("say Large port city ruled by Jalior Maxim.");
    command("say Rumours spread of others actually ruling and "+
                    "Jalior just a puppet.");
    return "";
}
public string
reply_calathin()
{
     command("say Calathin has been my home for 30 years.");
     command("say We have everything we need here.");
     command("say Wildlife for food, springs for water, and land for "+
                    "homes and crops.");
     return "";
}

public string
reply_silver()
{
     command("say The Silver forest, has an abundance of wildlife.");
     command("say Great hunting, lots of deer, moose, rabbit, squirrel. ");
     command("say Bring me the skins and I'll give you a good price.");
     return "";
}

public string
reply_enchanted()
{
    command("say The Enchanted forest is south of town.");
    command("say It's called the Enchanted forest because of the "+
                   "presense of the great Unicorn.");
    return "";
}

public string
reply_last()
{
    command("say The last port village to the north.");
    command("say No other actual towns any farther north then that.");
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
    command("say Dragons are very much present in Terel. ");
    command("say So far I know of the Red in the Silver Forest.");
    command("say The Black in the northwest Dragon mountains.");
    command("say The White north of Last on Mount Siralan. ");
    command("say I've heard rumours of a Green to the south.");
    return "";
}

public string
reply_legion()
{
    command("say The  Army of Maskyr Keep.");
    command("say A strong army of brutes and savages.");
    command("say What they lack in personal hygene they make "+
                   "up for in numbers.");
    return "";
}

public string
reply_horse()
{
    command("say Go see Jonas, he's got horses for sale.");
    command("say It's on the north side of town as you head to the north "+
                   "gate.");
    return "";
}

public string
reply_inn()
{
    command("say Only one suitable Inn in Calathin right now.");
    command("say The Silver Tree Inn, it's in the southeast "+
                   "corner of the square.");
    return "";
}

public string
reply_pub()
{
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
    command("say We only have a blacksmith right now.");
    command("say His forge is on the east side "+
                   "of the town square.");
    return "";
}

public string
reply_ribos()
{
    command("say Ribos is far to the west.");
    command("say The town is run by some fat King.");
    command("say I try to avoid that place.");
    return "";
}

public string
reply_bags()
{
    command("say You can get all manner of bags from Talok.");
    command("say His shop is on the north side of the square.");
    return "";
}

public string
reply_sea()
{
    command("say The Sea of Terel runs along the east coast.");
    command("say You can find ships that run the coast or "+
                   "to other lands in the port cities.");
    command("say Last, Dabaay and Maskyr Keep all have ship lines.");
    return "";
}

public string
reply_mansion()
{
    command("say That Mansion is a treasure trove of stories.");
    command("say Lots of things to explore and look at there.");
    command("say Adventurers seem to always come around asking "+
                   "about it.");
    return "";
}

public string
reply_gypsy()
{
    command("say Their camp is south of town.");
    command("say You might find work there.");
    return "";
}




public void
create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
					return;

    set_name("dardin");
    set_living_name("dardin");
    set_race_name("human");
    set_title("Tanvore, Owner of Dardin's Skins and Furs");
    set_adj("brown-haired");
    set_adj("muscular");
    set_long("A muscular man in his late thirties. He has short brown-hair and "+
                   "green-eyes. He has broad shoulders and long muscular legs. "+
                   "His hands are rough from long hours of skinning.\n");

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
    add_chat("Well met!");
    add_chat("If you've got some skins to sell you've come to the right place.");
    add_chat("I deal in most types of skins.");
    add_chat("I pay top price for rare skins.");
    set_act_time(3);
    add_act("smile warm");

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
    
    clone_object(CALATHIN_DIR + "armour/b_boots")->move(TO);
    clone_object(CALATHIN_DIR + "armour/bl_breeches")->move(TO);
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


