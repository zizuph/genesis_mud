// Bazaar Armourer (/d/Avenir/common/bazaar/NPCS/armourer.c)
// creator(s):     Lilith, Mar 98
// last update:  
// purpose:        cloned to /bazaar/intr/armr_shop.c
// note:           sells custom armours abandoned by players
// bug(s):
// to-do:        
#pragma strict_types

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";
inherit "/d/Avenir/inherit/shop_list";

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"

#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

#define ARM_PATH "/d/Avenir/common/bazaar/Obj/forge/"
#define MAXLIST  10


public void 
create_monster(void)
{
    if (!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());

    set_name("phinia");
    set_living_name("phinia");
    set_title("icu Ormad, Sharz Master Armourer");
    set_race_name("dwarf");
    set_adj("capable");

    set_long("@@my_long@@");

    set_gender(G_FEMALE);
    set_alignment(0);
    set_appearance_offset(-10);

    default_config_npc(random(20) + 110);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_UNARM_COMBAT, 80);
    set_act_time(25);
    add_act("sigh softly");
    add_act("peer at hobbit");
    add_act("smile respect elf");

    MAKE_SYBARITE; 

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);

    /* Set up the shop */
    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    set_store_room(file_name(TO));
    set_blank_lines(0);
}

void 
equip_me(void)
{
    object ob;

    ob = clone_object(ARM_PATH +"boots");
    ob->forge_it();    
    ob->move(TO);

    ob = clone_object(ARM_PATH +"bracers");
    ob->forge_it();    
    ob->move(TO);

    ob = clone_object(ARM_PATH +"breast");
    ob->forge_it();    
    ob->move(TO);

    ob = clone_object(ARM_PATH +"gauntlets");
    ob->forge_it();    
    ob->move(TO);

    ob = clone_object(ARM_PATH +"greaves");
    ob->forge_it();    
    ob->move(TO);

    ob = clone_object(ARM_PATH +"helm");
    ob->forge_it();    
    ob->move(TO);

    ob = clone_object(ARM_PATH +"shield");
    ob->forge_it();    
    ob->move(TO);
}

public string 
query_exp_title(void)
{
    return "sybarite";
}

public string
my_long(void)
{
    string str = "She is a kindly female dwarf.\n";

    if (TP->query_met(query_real_name()))
    {
	str = query_name() +" is a kindly dwarf, presenting "+
	"herself as:\n"+ query_name();
	if (strlen(query_title()))
	    str += " "+ query_title() +",";
	str += " "+ query_exp_title() +", female dwarf.\n";
    }

    str += "She is a slender, paler version of a surface dwarf.\n"+
    "She has smooth and creamy nut-brown skin.\n"+	 
    "Her chestnut brown hair is cropped short and falls\n"+
    "in ringlets about her face and neck.\n"+
    "Her whiskers are short, thin and silky-soft.\n"+
    "Her shoulders and arms are muscular, and her square,\n"+
    "short-nailed hands have callouses.\n"+
    "She has wise, dark eyes that regard you with tolerance.\n";
    return str;
}

/* Shop function redefinitions */

/* Only sell what I am supposed to */
public int 
shop_hook_allow_buy(object ob)
{
    if (ob->id("_Avenir_specialty_armour"))
	return 1;

    return 0;
}

public void 
shop_hook_list_empty_store(string str)
{
    command("say I have nothing available at this time.");
    NF("");
}

public int 
do_buy(string str)
{
    if (query_attack())
    {
	write(CAP(query_pronoun()) + " seems too busy right now.\n");
	return 1;
    }

    return ::do_buy(str);
}

public void 
init_living(void)
{
    ::init_living();

    /* Shop stuff. */
    add_action(do_buy,  "buy");
    add_action(do_list, "list");
    add_action(do_show, "show");
}
