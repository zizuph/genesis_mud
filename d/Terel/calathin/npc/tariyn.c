/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tariyn.c
 *
 *   
 *  
 * Shinto of Terel 8/99
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
    command("say Goblins are evil, plain and simple.");
    command("say I don't even think they should be allowed "+
                   "within the walls.");
    return "";
}

public string
reply_maskyr()
{
    command("say Maskyr Keep is on the east coast.");
    command("say Not some place you really wish to visit. ");
    command("say Unless you wouldn't mind being captured, beaten, "+
                   "and forced into slavery.");
    return "";
}

public string
reply_calathin()
{
     command("say I've lived in Calathin my whole life.");
     command("say Calathin is filled with good people.");
     command("say A great place to live for an adventurer."); 
     command("say Surrounded by forests with lots of creatures, "+
                    "mountains to the north, and the sea to the east.");
     return "";
}

public string
reply_silver()
{
     command("say The Silver forest is a rangers heaven.");
     command("say Wildlife in abundance, all manner of plants and herbs.");
     command("say I've heard rumours of groves in the forest.");
     return "";
}

public string
reply_enchanted()
{
    command("say The Enchanted forest is where I saw the spirit.");
    command("say Few people see the spirit in their life.");
    return "";
}

public string
reply_last()
{
    command("say The port town of Last is plagued by attacks.");
    command("say They get attacked by goblins, frost giants, even a "+
                   "great white dragon.");
    return "";
}

public string
reply_dabaay()
{
    command("say Debaay is a peaceful port down southeast of here.");
    command("say A small town, but it has a lot of character.");
    return "";
}

public string
reply_dragon()
{
    command("say I've only seen the red. ");
    command("say Something must have upset him because "+
                   "he came roaring out of his lair.");
    command("say I was out in the forest hunting.");
    command("say I've never seen anything living that was that "+
                    "enormous. ");
    return "";
}

public string
reply_legion()
{
    command("say I've fought a few Legion patrols.");
    command("say I was out hunting east of Calathin.");
    command("say Luckily, I knew the forest better then they did.");
    return "";
}

public string
reply_horse()
{
    command("say Jonas has great horses.");
    command("say I stable my stallion there, he's fair with prices. "); 
    command("say He's got all types of horses.");
    return "";
}

public string
reply_inn()
{
    command("say The Silver Tree Inn is the best Inn we've got.");
    command("say It's also run by the most beautiful woman I've "+
                   "ever known, Delsanora.");
    command("smile wist");
    return "";
}

public string
reply_pub()
{
    command("say We have three pubs in Calathin.");
    command("say The Big Rock is on the south side of the town square.");
    command("say Then there is the Black Cat which is just off the road "+
                   "to the north gate, near the stable.");
    command("say The Dragon Claw is off the road to the east gate.");
    return "";
}

public string
reply_smith()
{
    command("say Sodar can repair weapons, he's not up to armours yet.");
    command("say He's on the east side of the town square.");
    return "";
}

public string
reply_ribos()
{
    command("say Ribos is the city far to the west.");
    command("say I don't know a lot about it, not a lot of people "+
                   "seem to spend much time there.");
    return "";
}

public string
reply_bags()
{
    command("say Ahh, you can get bags and that stuff from Talok.");
    command("say His shop is actually in a tree, it's right next to "+
                   "the guard house.");
    return "";
}

public string
reply_sea()
{
    command("say The Sea of Terel is wonderous!");
    command("say Someday I wish to take a voyage across it.");
    command("say The Sea runs the length of the eastern coast.");
    return "";
}

public string
reply_mansion()
{
    command("say I avoid the place, it's got so many stories about it.");
    command("say Mysterious deaths, haunting ghosts, and giant vines.");
    command("say And after all the adventurers who have gone in there "+
                    "there can't be anything of worth anymore.");
    return "";
}

public string
reply_gypsy()
{
    command("say I've spent some time with the gypsies.");
    command("say They just want to perform and be left alone.");
    command("say I even did a few shows with them.");
    command("smile");
    return "";
}




public void
create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
					return;

    set_name("tariyn");
    set_living_name("tariyn");
    set_race_name("half-elf");
    set_title("Wight, Owner of the Sturdy Shield Armour Shop");
    set_adj("black-haired");
    set_adj("thick");
    set_long("A young half-elf in his late twenties. He has black-hair "+
                   "braided in a pony tail. He stands about 6 feet tall and "+
                   "weighs around 200 pounds.\n");

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
    add_chat("Hello.");
    add_chat("I only deal in armours. ");
    add_chat("A good sturdy piece of armour can be the difference "+
                   "between life and death.");
    add_chat("Weapons, you'll have to see Amaylin about.");
    set_act_time(3);
    add_act("emote polishes a piece of armour.");

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


