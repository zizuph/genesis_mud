/* Ashlar, 1 Oct 97
   a priest npc, this lad is the gardener
   he also acts as a herb shop, and will identify herbs for you if you
   give them to him
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <filter_funs.h>
#include <files.h>
#include <language.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/taman_busuk/neraka/guild/guild.h"

inherit AM_FILE
inherit "/lib/trade";

#undef DEBUG
#define DEBUG(x)    (find_player("ashlar")->catch_msg("PRIEST: " + x + "\n"))

object jar;

void arm_me();
void herb_enter_inv(object obj, object from);
void init_herb_store();

string
query_guild_title_race()
{
    return "Wyllows of Flotsam";
}

int
query_guild_family_name()
{
    return 1;
}


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("alister");
    set_title("Master of the Gardens");
    add_name("priest");
    add_name("gardener");
    add_name("master");

    set_introduce(1);

    set_race_name("half-elf");
    set_adj("tall");
    add_adj("bald-headed");
    set_long("This is the Master of the Gardens, the overseer of the " +
    "plants in these caverns. His long coat is discoloured by plant " +
    "stains and his hands are also stained.\n");

    add_prop(CONT_I_HEIGHT, 185);
    add_prop(CONT_I_WEIGHT, 75000);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_stats(({ 114, 135, 110, 150, 140, 110 }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          70);
    set_skill(SS_DEFENCE,           55);
    set_skill(SS_PARRY,             50);
    set_skill(SS_AWARENESS,         65);
    set_skill(SS_SPELLCRAFT,        65);
    set_skill(SS_ELEMENT_LIFE,      65);
    set_skill(SS_ELEMENT_AIR,       65);
    set_skill(SS_FORM_DIVINATION,   65);
    set_skill(SS_FORM_ENCHANTMENT,  60);
    set_skill(SS_FORM_ABJURATION,   60);
    set_skill(SS_HERBALISM,         70);
    set_skill(SS_ALCHEMY,           70);

    set_skill(PS_GUILD_LEVEL, 45);
    set_skill(PS_SPELLS, -1);

    set_all_hitloc_unarmed(10);

    set_alignment(-900);
    set_knight_prestige(900);

    set_act_time(7);
    add_act("say I know what is worth to know about the plants that " +
    "we grow down here.");
    add_act(VBFC_ME("pick_flower"));
    add_act(VBFC_ME("smell_flower"));
    add_act("emote roots some weeds from the garden.");
    add_act("smile .");

    set_cact_time(5);
    add_cact("say I curse you!");
    add_cact("sneer");
    add_cact("say The hatred of the Dark Queen will follow you to your grave!");

    set_default_answer(QCTNAME(TO) + " mutters: I can not help you with " +
    "that.\n");

    add_ask(" [for] 'help' ", "say I might be able to help you, " +
        "if you have come to seek training in the art of the herbs.", 1);
    add_ask(" [about] [the] [art] [of] [the] 'art' / 'herbs' ",
        "say I may be able to train you in herbalism.", 1);
    add_ask(" [about] 'herbalism' ",
        "say O, mickle is the powerful grace, that lies in herbs, plants, " +
        "stones, and their true qualities.", 1);

    config_default_trade();
}

void
init_living()
{
    ::init_living();
    //init_herb_store();
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    clone_object(NERAKA + "guild/obj/occ_shadow")->add_occ_shadow(TO);

    TO->init_occ_shadow();

}

varargs string
pick_flower(int round)
{
    switch(round)
    {
    	case 0:
    	command("emote picks a small flower and studies it intently.");
    	break;

    	case 1:
    	command("say Within the infant rind of this small flower");
    	break;

    	case 2:
    	command("say Poison has residence, and medicine power");
    	break;
    }

    if (round < 2)
        set_alarm(5.0,0.0,&pick_flower(round+1));
}

varargs string
smell_flower(int round)
{
    switch(round)
    {
    	case 0:
    	command("emote deeply inhales the scent of a purple flower.");
    	break;

    	case 1:
    	command("emote sneezes violently.");
    	break;

    }

    if (round < 1)
        set_alarm(4.0,0.0,&smell_flower(round+1));
}

void
give_back(object obj, object from)
{
    command("say That does not interest me.");
    command("drop " + obj->query_name());
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (living(from))
        if(function_exists("create_object",obj) == "/std/herb")
            set_alarm(0.0+(itof(random(10))/5.0),0.0,&herb_enter_inv(obj,from));
        else if(!obj->query_no_show())
            set_alarm(1.0,0.0,&give_back(obj,from));
            
}

int
second_life(object killer)
{
    setuid();
    seteuid(getuid());
    A_KILL_LOG("pot/npckills","Alister",killer);
    return 0;
}

/**************************
 herbshop support functions
 **************************/

void
herb_enter_inv(object obj, object from)
{
    string str;
    
    /* Sanity check, to see if the giver or the herb has mysteriously
       disappeared
     */

    if (!objectp(obj) || E(obj) != TO || !objectp(from) || E(from) != E(TO))
    {
    	command("scratch head");
    	command("put herb in jar");
        return;
    }

    if (!obj->do_id_check(TO))
    {
    	command("say Nope, I haven't a clue what it is.");
    }
    else
    {
        str = obj->query_id_long();
        str = implode(explode(str,"\n")," ");
        command("say That is " + LANG_ADDART(obj->query_herb_name()) + ".");
        command("say " + str);
    }
    command("give " + obj->query_name() + " to " + from->query_real_name());
}

int
list_herbs(string arg)
{
    object *hl;
    int i,sz;

    if (arg && arg != "herbs")
    {
    	NF("List what?\n");
    	return 0;
    }

    hl = all_inventory(jar);
    sz = sizeof(hl);

    for (i=0; i<sz; i++)
    {
    	string str;
    	int price;

    	str = sprintf("%-30s",hl[i]->short());
    	price = hl[i]->query_herb_value();

    	write(str + text(split_values(price)) + ".\n");
    }
    return 1;
}

int
sell_herb(string arg)
{
    object herb;

    herb = FIND_STR_IN_OBJECT(arg,TP)[0];
    if (!objectp(herb) || function_exists("create_object",herb) != "/std/herb")
    {
    	NF("Sell what? You may only sell herbs, and only one at a time, here.\n");
    	return 0;
    }

    give(herb->query_herb_value(), TO, TP);
    herb->move(jar);
	
    return 0;
}

int
buy_herb(string arg)
{
    return 0;
}

void
init_herb_store()
{
    add_action(list_herbs,"list");
    add_action(sell_herb,"sell");
    add_action(buy_herb,"buy");
}
