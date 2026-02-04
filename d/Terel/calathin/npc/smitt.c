/*  This is an NPC named "talok" Smitt. He is called by shop.c as a
 *  shopkeeper.  If he is killed, the shop will not function.  
 *
 *  Coded by Vader on 6/25/92
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/d/Terel/include/log_asks";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#define HUNTING_TREVIN "_i_hunting_trevin"
#define KILLS_CAL "_kills_cal"
dress_me();

public string
default_answer()
{
    command("hmm");
    command("say I don't know about that.");
    return "";
}
public string
reply_warlock()
{
    command("say Another of the evils that come from Maskyr.");
    command("say Warlocks taught in the dark arts, doing the bidding of "+
                   "the rulers of Maskyr Keep."); 
    command("say If there are magical artifacts to be found, they will seek it.");
    return "";
}

public string
reply_cult()
{
    command("say The Cult fanatically do the bidding of the Beast.");
    command("say The Beast is a vile being, who enjoys destruction and death.");
    command("say The Beast wants all of Terel, and the Cult will attempt do "+
                   "give it to him.");
    return "";
}

public string
reply_kobold()
{
    command("say Kobolds are idiot cousins of goblins.");
    command("say Smaller, stupider, and uglier.");
    command("say There are some northwest of Last.");
    return "";
}
public string
reply_trolls()
{
    command("say Large creatures, trolls.");
    command("say There seem to be lots of them in the Dragon Mountains.");
    command("say Avoid them, they can rip a man limb from limb in seconds.");
    return "";
}

public string
reply_explorers()
{
    command("say Explorers?");
    command("say They reside in Calathin, other then that I will not say more.");
    return "";
}

public string
reply_protectors()
{
    command("say The Order of the White are warriors, protectors.");
    command("say They follow in the path of the Mystics and the Ancients.");
    return "";
}

public string
reply_elnoven()
{
    command("say Ahh, a town of elves in the Valley of the Ancients.");
    command("say Only been there once, but you can almost feel the "+
                   "presence of something greater then yourself. ");
    command("say There is a stronghold there believed to be the dwelling "+
                    "of the Order of the White.");
    return "";
}

public string
reply_dragon_mountains()
{
    command("say If you seek death, seek the Dragon Mountains.");
    command("say The mountains are home to goblins, dragons, trolls, "+
                    "kobolds, and any number of things I'm sure you can't even "+
                    "imagine.");
    return "";
}

public string
reply_frost_giants()
{
    command("say I've only seen a frost giant twice.");
    command("say I was in Last on business, and the frost giants came "+
                   "down from the north and attacked.");
    command("say Needless to say, when you see something that can hold your "+
                    "whole body in one fist, you run.");
    return "";
}

public string
reply_gypsy()
{
    command("say Entertainers, they run the camp south of Calathin.");
    command("say Lots of games to play and shows to see.");
    command("say They might even need a hand, you might ask for a job.");
    return "";
}

public string
reply_mansion()
{
    command("say The Avenchir mansion holds many secrets.");
    command("say If you seek adventure, thats a good place to start.");
    command("say The mansion is in the southeast part of town.");
    return "";
}

public string
reply_sea()
{
    command("say The Sea of Terel runs up the eastern coast of the continent.");
    command("say People talk of pirates raiding on the sea, but more likely "+
                   "the pirates are agents of Maskyr Keep.");
    return "";
}

public string
reply_ribos()
{
    command("say Thats a city west of Calathin.");
    command("say Place has been very quiet lately.");
    command("say Don't know anything about whats been going on there.");
    return "";
}

public string
reply_legion()
{
    command("say The Army of Maskyr Keep.");
    command("say Mostly renegedes from the darker places of the world.");
    return "";
}

public string
reply_dabaay()
{
    command("say Dabaay, the town of Halflings southeast of Calathin.");
    command("say It's small happy port town, the little folk try to keep "+
                    "life light and merry.");

    return "";
}

public string
reply_last()
{
    command("say Last, is a town to the northeast on the coast of the "+
                   "Sea of Terel.");
    command("say Some ships port there and travel to other lands.");

    return "";
}

public string
reply_maskyr()
{
    command("say Maskyr Keep?");
    command("say Probably the root of all evil in Terel.");
    command("say The place is a vile city run by demon worshippers.");
    command("say The power of the place is undeniable though.");
    command("say They have the Legion, their army, the Cult of the Beast, "+
                   "as well as the Warlocks of Maskyr.");
    return "";
}

public string
reply_enchanted()
{
    command("say Oh the enchanted forest is south of Calathin.");
    command("say A beautiful Unicorn dwells in the forest, never seen "+
                   "it myself.");
    command("say Rumours say there is also a green dragon that lives there. ");
    return "";
}

public string
reply_silver()
{
    command("say The Silver forest lies to the north.");
    command("say The forest is filled with lots of wildlife, but also some "+
                   "very dangerous creatures.");
    command("say A red dragon makes it's home there for example.");
    return "";
}

public string
reply_calathin()
{
    command("say Ahh this wonderful city.");
    command("say Many things to do, many things to see.");
    command("smile");
    command("say Our problem is everyone wants to take over.");
    command("say Goblins coming down from the north, Maskyr Keep "+
                   "from the east, and on top of that we have to deal with Dragons!");
    return "";
}


public string
reply_goblin()
{
    command("say Scavenging rats.");
    command("say Several tribes live in the Dragon Mountains they breed "+
                   "like rabbits.");
    command("say They grow in numbers and have decided they want to "+
                    "move out of the mountains.");
    return "";
}


public string
reply_dragon()
{
    command("say You should be wary of what you ask about.");
    command("say Dragons are not something to take lightly.");
    command("say So far we are aware of four dragons in the area, but "+
                   "the dragon mountains are sure to be full of them.");
    command("say Siralan the White lives in the mountain named for him "+
                    "north of Last.");
    command("say The Red lives in a mountain within the Silver Forest.");
    command("say A green is said to live within the Enchanted Forest.");
    command("say The great black lives in the Dragon Mountains to the northwest.");
    return "";

}

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
        command("say Yes, I saw him.");
        command("say He headed towards the southern port.");
        command("say Not a very friendly fellow that one.");
        return "";
    }
    return "";
}


void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("talok");
    add_name("shopkeeper");
    add_name("smitt");
    set_race_name("human");
    set_long("Mr Smitt is the owner of the Trading Post.  If you "
      + "kill him, you\nwon't be able to trade!  Plus, you'll get "
      + "the locals MAD at you.\n");

    /* Average stat: 72
     */
    default_config_npc(72);

    /* But we want it to have more hitpoints
     */
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_UNARM_COMBAT, 80);
    set_hp(9999);

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 40);

    set_chat_time(15);
    add_chat("Boy, how I love my job.  The clean air!  The snow!");
    add_chat("You're not from around here, are you?");


    add_chat("It's all diet.");
    add_chat("Ahhh.... Whatever.");
    add_chat("What is all this fuss about the one ring?");
    add_chat("I hear the ranks of the Solamnian Knights are thinning out.");
    add_chat("There is much mystery in the valley.");
    add_chat("How come nobody protects ME?");
    add_chat("My friend Sodar can sharpen weapons.");
    add_chat("I heard there are herbs growing in the forest."); 
    add_chat("I heard the Legion was moving in the east.");
    add_chat("I offer many more bargains than the dealers of Last or the gypsies!");
    set_act_time(1);
    add_act("close door");

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 80);
    add_ask("tall wiry male human", reply_assassin, 1);
    add_ask(({"dragon","dragons"}), reply_dragon, 1);
    add_ask(({"goblins","goblin"}),reply_goblin, 1);
    add_ask(({"calathin","Calathin"}), reply_calathin, 1);
    add_ask(({"silver forest","Silver forest","Silver Forest"}), reply_silver,1);
    add_ask(({"enchanted forest","Enchanted forest","Enchanted Forest"}),
                    reply_enchanted, 1);
    add_ask(({"maskyr keep", "Maskyr keep", "Maskyr Keep"}), reply_maskyr, 1);
    add_ask(({"last","Last"}), reply_last, 1);
    add_ask(({"dabaay","Dabaay"}), reply_dabaay, 1);
    add_ask(({"legion","Legion"}), reply_legion, 1);
    add_ask(({"Ribos", "ribos"}), reply_ribos, 1);
    add_ask(({"sea","Sea","sea of terel","Sea of Terel", "sea of Terel"}), 
                    reply_sea, 1);
    add_ask(({"mansion","Mansion","Avenchir","avenchir"}), reply_mansion, 1);
    add_ask(({"gypsy","gypsies","gypsy camp","camp"}), reply_gypsy, 1);
    add_ask(({"frost giants","giants","frost giant","giant"}), reply_frost_giants, 1);
    add_ask(({"dragon mountains","Dragon mountains","Dragon Mountains",
                    "dragon Mountains"}), reply_dragon_mountains, 1);
    add_ask(({"elnoven","Elnoven"}), reply_elnoven, 1);
    add_ask(({"order of the white","Order of the white","Order of the White",
                    "order of the White"}), reply_protectors, 1);
    add_ask(({"Protectors","protectors"}), reply_protectors, 1);
    add_ask(({"explorers","explorers of the arcanum",
                    "explorers of the arcane"}), reply_explorers, 1);
    add_ask(({"trolls","troll"}), reply_trolls, 1);
    add_ask(({"kobolds","kobold"}), reply_kobold, 1);
    add_ask(({"cult of the beast","Cult of the Beast","Cult of the beast",
                    "cult of the Beast"}), reply_cult, 1);
    add_ask(({"Warlocks of Maskyr","Warlock of Maskyr","warlock of maskyr",
                    "warlocks of maskyr"}), reply_warlock, 1);
    set_default_answer("@@default_answer");
    dress_me();
}

void
dress_me()
{
    FIX_EUID;
    
    clone_object(CALATHIN_DIR + "armour/b_boots")->move(TO);
    clone_object(CALATHIN_DIR + "armour/gr_breeches")->move(TO);
    clone_object(CALATHIN_DIR + "armour/w_tunic")->move(TO);
    command("wear all");
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


