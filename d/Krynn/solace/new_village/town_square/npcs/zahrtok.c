/*
*  Zahrtok, the Solace Slavemaster
*  Created by Leia
*  June 10, 2005
*/

/*
** Updated By:
** Leia
** July 1, 2005
*/

/**
 *  Navarre Jan 17th 2007:
 *  Shortened line width
 *  Fixed typos with double space with the npcs special attacks
 */ 

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>

inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/lib/unique";

inherit M_FILE

string height;
string where;
int how_hard;

int arm_me()
{ 
    clone_object(Z_MAIL)->move(this_object());
    clone_object(Z_HELM)->move(this_object());
    clone_object(Z_BRACERS)->move(this_object());
    clone_object(Z_GREAVES)->move(this_object());
    clone_object(Z_SHIELD)->move(this_object());
    clone_object(Z_BOOTS)->move(this_object());
    clone_unique(WHIP, 5, SIMPLE_WHIP)->move(this_object());
    command("wield weapons");
    command("wear armours");
}

void 
create_krynn_monster()
{
	set_name("zahrtok");
	set_gender(G_MALE);
	add_name("slavemaster");
	add_name("master");
	set_living_name("zahrtok");
	set_adj(({"foul", "menacing"}));
	set_title("the Slave Driver");
	set_race_name("goblin");
	set_short("foul menacing male goblin");
	set_long("This goblin smells as though he has messed " +
                 "himself. His demeanor and manners let you " +
                 "know that he is a wicked being, capable of " +
                 "inflicting harsh pain upon those who test " +
                 "him. He looks as though he is brooding about " +
                 "something.\n");
	set_introduce(1);
	
        set_stats(({270, 290, 270, 215, 220, 240}));
	set_alignment(-100);

	add_prop(CONT_I_HEIGHT, 150);
	add_prop(CONT_I_WEIGHT, 100000);
	add_prop("_ranger_i_not_disarm", 1);
	add_prop(CONT_I_VOLUME, 60000);
        add_prop(NPC_I_NO_LOOKS, 1);

	set_skill(SS_WEP_CLUB, 100);
	set_skill(SS_DEFENCE, 80);
	set_skill(SS_PARRY, 80);
	set_skill(SS_AWARENESS, 100);

	arm_me();
    
        set_act_time(6);
        add_act("emote grumbles and smacks his whip upon his palm.");
        add_act("emote stares at his cages and grumbles unhappily.");
        add_act("emote peers around, catches your eye, and reaches for his whip.");
        add_act("emote snaps his whip in the air, giving you a start.");
        add_act("say Need bath. Swim fountain soon.");
        add_act("say Wonder where Toede. He be here by now should.");
        add_act("say Hear stupid shaman here. Verminaard like him would.");
        add_act("say Kender find hand my pockets again, I whip him.");
        add_act("say Maybe you help me.");
        
        add_ask(({"quest", "task", "help", "job"}), "@@quest_func@@");
        add_ask("items", "@@qitems@@");
        add_ask("dung", "@@qdung@@");
        add_ask("mix", "@@qmix@@");
        add_ask("herbs", "@@qherbs@@");
}

string
qitems()
{
    TO->command("say Need these items: Animal dung, some herbs, beer from Solace.");
    return "";
}

string
qdung()
{
    TO->command("say I dunno. Maybe some dog poop on tree in town.");
    return "";
}

string
qmix()
{
    TO->command("say Mix dump in water you. Make water good bathe in again.");
    return "";
}

string
qherbs()
{
    TO->command("say Need poison ivy, crocus, black currant.");
    return "";
}
      
string
quest_func()
{
    if(TP->test_bit("krynn", GROUP, G_BIT))
    {
        TO->command("say You help shaman! Stupid! Git away from me!");
        return "";
    }
	    
    if(TP->test_bit("krynn", GROUP, E_BIT))
    {
        TO->command("say You done help! You goody two shoe? Git " +
                    "before me whip you.");
        return "";
    }
    TO->command("say Stupid shaman mess with fountain. Me no " +
                "bathe there, too clean.");
    TO->command("say Need you make water dirty. Need you bring " +
                "me items and offer me them.");
    TO->command("say I then mix dirty stuff. You dump in fountain.");
    TO->command("say Soon smell like old-self, I.");
    find_object(ROOM2)->set_fountain_dirty(0);        
    return "";
}

int
set_stuff()
{
    switch(random(9))
    {
        case 0: where = "face";
                height = "high";
                break;
        case 1: where = "shoulder";
                height = "high";
                break;
        case 2: where = "chest";
                height = "high";
                break;
        case 3: where = "arm";
                height = "body-level";
                break;            
        case 4: where = "stomach";
                height = "body-level";
                break;
        case 5: where = "groin";
                height = "low";
                break;
        case 6: where = "thigh";
                height = "low";
                break;
        case 7: where = "knee";
                height = "low";
                break;
        case 8: where = "shin";
                height = "low";
                break;
    }

    return 1;
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    object ob, poison;
    string how_str;
    string how_str2;
    string what_special; 

    if (random(4)) 
    {
        /*
        tell_room(E(TO),"**Zahrtok failed random so no special**\n");
        */
        return 0;
    }

    if (!(ob = TO->query_attack())) 
    {
        /*
        tell_room(E(TO),"**Zahrtok has no enemy so no special**\n");
        */
        return 0;
    }
    
    switch(random(10))
    {
        case 0..4: 
            what_special = "kick";
            break;        

        case 5..9:
            what_special = "herb";
            break;    
    }
    
    if(what_special == "kick")
    {
        set_stuff();
        
        if(where == "chest" | where == "stomach" | where == "face" | where == "groin")
            how_hard = 400;
        if(where == "knee" | where == "shin" | where == "shoulder")
            how_hard = 350;
        if(where == "thigh" | where == "arm")
            how_hard = 300;
        
        hitresult = ob->hit_me(how_hard, W_BLUDGEON, TO, -1);
        
        switch(hitresult[0])
        {
            case 0:
                how_str =  " but misses completely, spinning around " +
                           "in the attempt.\n" + QCTNAME(TO) +
                           " growls and throws himself back into the fight.\n";

                how_str2 = " but misses completely, spinning around in the " +
                           "attempt.\n" + QCTNAME(TO) + " growls and throws " +
                           "himself back into the fight.\n";
                break;

            case 1..10:
                how_str =  ", just barely slapping your " + where +
                           " with his foot.\n" + QCTNAME(TO) + 
                           " yells: Stand still stupid! Me no can hit you!\n";

                how_str2 = ", just barely slapping " + HIS(ob) + " " + where +
                           " with his foot.\n" + QCTNAME(TO) + " yells: " +
                           "Stand still stupid! Me no can hit you!\n";
                break;

            case 11..20:
                how_str =  ", bruising your " + where + " with his foot.\n" +
                           QCTNAME(TO) + " yells: Hah! Feel good, dummy?!\n";

                how_str2 = ", bruising " + HIS(ob) + " " + where +
                           " with his foot.\n" + QCTNAME(TO) + " yells: Hah! " +
                           "Feel good dummy?!\n";
                break;

            case 21..40:
                how_str =  ", striking your " + where + " hard with his foot.\n" +
                           QCTNAME(TO) + " yells: Hit you good! Next time be better!\n";

                how_str2 = ", striking " + HIS(ob) + " " + where + 
                           " hard with his foot.\n" + QCTNAME(TO) +
                           " yells: Hit you good! Next time be better!\n";
                break;

            case 41..60:
                how_str =  ", battering your " + where + " with his foot.\n" +
                           QCTNAME(TO) + " yells: This fight? You no match for me!\n";

                how_str2 = ", battering " + HIS(ob) + " " + where + " with his " +
                           "foot.\n" + QCTNAME(TO) + " yells: This fight? You no " +
                           "match for me!\n";
                break;

            default:
                how_str =  ", demolishing your " + where + " with his foot.\n" +
                           QCTNAME(TO) + " yells: This too easy!\n";

                how_str2 = ", demolishing " + HIS(ob) + " " + where + " with " +
                           "his foot.\n" + QCTNAME(TO) + " yells: This too easy!\n";
        }
            
        ob->catch_msg(QCTNAME(TO) + " aims a " + height + " kick at you" + how_str);
        tell_watcher(QCTNAME(TO) + " aims a " + height + " kick at " + 
                     QCTNAME(ob) + how_str2, ob);

        if(ob->query_hp() <= 0)
        {
            ob->do_die(TO);
            write(QCTNAME(TO) + " laughs maniacally.\n");
        }
    
        return 1;
    
    }
   
    else
    {
        // what_special == "herb"
        tell_watcher(QCTNAME(TO) + " pulls a small blue berry from his pants and " +
                     "eats it.\n" + QCTNAME(TO) + " says: Ah! Better much!\n");
        TO->heal_hp(400);
        return 1;
    }
}
