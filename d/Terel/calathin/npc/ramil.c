/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ramil.c
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
    command("say Goblins are no good, and have no place here.");
    command("say It's high time we headed north and finished off "+
                    "those foul pigs and stopped their breedin.");
    return "";
}

public string
reply_maskyr()
{
    command("say Maskyr Keep is full of dogs.");
    command("say Bastards run every type of evil activity you can "+
                   "think of.");
    command("say I escaped from their slave pens nearly 10 years ago.");
    return "";
}
public string
reply_calathin()
{
     command("say Calathin is great, except for the lack of mountains.");
     command("say No Maskyr dogs either!");
     command("say This town is always busy with travellers passing "+
                     "through, either north to south or east to west, or the "+
                     "other way around.");
     return "";
}

public string
reply_silver()
{
     command("say The Silver forest, has many kinds of beasts.");
     command("say Beasts you can hunt, or beasts that can hunt you. ");
     command("say You bring me back them meats, I'll give you a good "+
                     "deal.");
     return "";
}

public string
reply_enchanted()
{
    command("say The Enchanted gives me chicken skin.");
    command("say Damn things has a Unicorn living in it.");
    return "";
}

public string
reply_last()
{
    command("say Heh, Northern most port of Terel.");
    command("say If you make your way there, tell Lanc he "+
                   "owes me a pint.");
    return "";
}

public string
reply_dabaay()
{
    command("say I made my way there after I escaped Maskyr Keep.");
    command("say Small town, friendly people, a good place to live.");
    command("say It was just too damn close to the water for me.");
    return "";
}

public string
reply_dragon()
{
    command("say Dragons, forget about em. ");
    command("say These aren't Dragonarmy pets.");
    command("say They're full grown and pack a punch.");
    command("say Dragons are not something to be toyed with. ");
    return "";
}

public string
reply_legion()
{
    command("say Pigs and Dogs.");
    command("say Thats all they are.");
    command("say Army of pigs and dogs.");
    return "";
}

public string
reply_horse()
{
    command("say What would I know about a damn horse?");
    command("say Go see Jonas at the stables in the north "+
                   "part of town.");
    return "";
}

public string
reply_inn()
{
    command("say That skirt Delsanora runs the Silver Tree Inn.");
    command("say Place seems like a good place to stay a night "+
                   "or two.");
    return "";
}

public string
reply_pub()
{
    command("say Pubs, now your talking!");
    command("say The Dragon Claw is off the road to the east gate.");
    command("say The Big Rock is on the south side of the town square.");
    command("say Then there is the Black Cat which is just off the road "+
                   "to the north gate, near the stable.");
    return "";
}

public string
reply_smith()
{
    command("say Sodar runs the forge in the east of town.");
    command("say He's alright at it, for a human.");
    return "";
}

public string
reply_ribos()
{
    command("say Ribos is far to the west.");
    command("say I've never been there myself.");
    return "";
}

public string
reply_bags()
{
    command("say Talok the tree man, he's got bags for sale.");
    command("say His tree is on the north side of the square.");
    return "";
}

public string
reply_sea()
{
    command("say Nearly died in that damn thing.");
    command("say The Sea of Terel runs the eastern coastline.");

    command("say When I slipped out of the slave pens I ended "+
                    "up floating south till I could drag myself out of "+
                    "the water.");
    return "";
}

public string
reply_mansion()
{
    command("say I've been in there a few times.");
    command("say Lots of things to explore and look at.");
    command("say But I didn't find a damn thing of worth there.");
    return "";
}

public string
reply_gypsy()
{
    command("say The gypsies live in a camp south of town.");
    command("say They keep to themselves so not many people "+
                   "bother them.");
    command("say They put on some good shows.");
    return "";
}




public void
create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
					return;

    set_name("ramil");
    set_living_name("ramil");
    set_race_name("dwarf");
    set_title("Doran, Owner of the Calathin Butcher Shop");
    set_adj("short-bearded");
    set_adj("stout");
    set_long("An older dwarf hard to tell how old. He has long greying hair and "+
                   "brown-eyes. He has broad shoulders and short muscular legs. "+
                   "His beard is short and well-kept.\n");

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
    add_chat("Welcome!");
    add_chat("I buy and sell meats of all kinds.");
    add_chat("The more you bring the more you make.");
    add_chat("Certain meats just don't taste good smoked.");
    set_act_time(3);
    add_act("nod .");

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
    clone_object(CALATHIN_DIR + "armour/gr_breeches")->move(TO);
    clone_object(CALATHIN_DIR + "armour/b_tunic")->move(TO);
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


