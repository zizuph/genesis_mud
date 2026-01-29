/* Ashlar, 17 Jul 97
   A dark cleric that sells his services as a spellcaster
   for money.
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit "/lib/trade";

#define ARM1 NOBJ + "npcmedallion"

#define NERAKA_LIVE_AM_GIVEN_TO_DCLERIC     "_neraka_live_am_given_to_dcleric"

#define DEBUG(x)    (find_player("ashlar")->catch_msg("DCLERIC: " + x + "\n"))

void arm_me();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    config_default_trade();

    set_name("belaen");
    add_name("cleric");
    //set_living_name("kordhek");
    set_title("the Dark Cleric");
    set_introduce(1);
    
    set_race_name("half-elf");
    set_adj("dark-haired");
    add_adj("slender");
    set_long("This guy needs a long desc!\n");

    add_prop(CONT_I_HEIGHT, 170);
    add_prop(CONT_I_WEIGHT, 55000);

    set_stats(({95,115,100,125,125,110}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB, 55);
    set_skill(SS_DEFENCE, 45);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_ELEMENT_LIFE, 65);
    set_skill(SS_FORM_DIVINATION, 65);
    set_skill(SS_FORM_ENCHANTMENT, 60);
    set_skill(SS_FORM_ABJURATION, 60);

    set_all_hitloc_unarmed(3);

    set_alignment(-950);
    set_knight_prestige(950);

    add_ask("identify","say I can identify an item for you.. " +
        "The price is 4 platinum.. Place the object on the ground, " +
        "bring me a pearl for my magic workings and pay me to identify " +
        "the item.",1);
    set_default_answer(QCTNAME(TO) + " shakes his head, obviously " +
        "not understanding your question.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}


string
strip_article(string s)
{
	if (extract(s,0,3)=="the ")
		s = extract(s,4);
	if (extract(s,0,1)=="a ")
		s = extract(s,2);
	return s;
}

int
do_pay(string str)
{
    string *l;
    object *cl, *ob;
    int int_str, value, *money_arr;
    string pay_type, get_type, coin_pay_text, coin_get_text;

    value = 1728 * 4;   // 4 platinum

    if(!stringp(str))
        str = "";
    l = explode(str, " to identify ");
    if (sizeof(l) != 2)
    {
        NF("Pay what? Pay the cleric to identify an object perhaps?\n");
        return 0;
    }

	l[0] = strip_article(l[0]);
	l[1] = strip_article(l[1]);

    cl = FIND_STR_IN_OBJECT(l[0],E(TO));
    if ((sizeof(cl) != 1) || (cl[0] != TO))
    {
        NF("Pay whom? Pay the cleric perhaps?\n");
        return 0;
    }

    ob = FIND_STR_IN_OBJECT(l[1],E(TO));
    if (sizeof(cl) == 0)
    {
        NF("Pay the cleric to identify what? Remember to put the object on the floor.\n");
        return 0;
    }

    if (!P("pearl",TO))
    {
        command("say You must give me a pearl before I can help you.");
        return 1;
    }

    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1)
    {
        command("say You do not have enough money to pay me!");
        return 1;
    }
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
        sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    TP->catch_msg("You pay " + QTNAME(TO) + " " + coin_pay_text + ".\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " in return.\n");
    tell_room(E(TO),QCTNAME(TP) + " pays " + QTNAME(TO) + " some coins.\n", TP);

    DEBUG("Issuing command: pidentify " + l[1]);
    command("pidentify " + l[1]);
    return 1;
}

void
init_living()
{
    ::init_living();

    add_action(do_pay,"pay");
}


void
arm_me()
{
    setuid();
    seteuid(getuid(this_object()));

/*
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
*/
    clone_object(ARM1)->move(this_object(),1);
    command("wear all");
}

/*
 * Function name: identify_success
 * Description:   This gets called if the identify was a success
 * Arguments:     string str - The information gleaned about the object
 *                object obj - The object itself
 */

void
identify_success(string str,object obj)
{
    string *l = explode(str,"\n");
    int i;

    command("emote takes a deep breath.");
    command("say This is what I know of this item:");
    for (i=0; i<sizeof(l); i++)
    {
        command("say " + l[i]);
    }
}

/*
 * Function name: identify_failed
 * Description:   This gets called if the identify failed
 * Arguments:     object obj - The target of the identify
 */

void
identify_failed(object obj)
{
    command("sigh softly");
    command("say I could not discern anything about that item.");
}
    

/*
 * Function name: spell_failed
 * Description:   This gets called if the spell failed
 */
void
spell_failed()
{
	command("emote mutters: This is beyond me...");
}
