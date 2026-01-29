/*
 * /d/Gondor/common/guild/ithilien/npc/ceodar.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * The cook for the Ithilien guild
 */

#pragma strict_types

inherit	"/d/Gondor/common/npc/npc_ranger";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"


/* prototypes */
public void	create_ranger()	;
public string	default_answer();
public string	ask_ale();
public string	ask_wine();
public string	ask_water();
public string	ask_stew();
public string	ask_beef();
public void     add_introduced(string who);
public void     do_introduce(object pl, string name);
public int	query_knight_prestige();


/*
 * Function name:	create_ranger
 * Description	:	set up the cook
 */
public void
create_ranger() 
{
    set_name("ceodar");
    add_name("cook");
    set_race_name("human");
    set_adj("cheerful");
    add_adj("grey-haired");

    set_long(BSN(
	"This grey-haired man seems to be in a good humour. "+
	"He leans against the crates, dispensing food and drink "+
	"with an air of easy competence."));
    set_company("Ithilien");

    /* values taken from the northern innkeeper */
    default_config_npc(42);
    set_base_stat(SS_INT, 55);
    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_TRADING, 55);
    set_alignment(100+random(200));

    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("You look thirsty.");
    add_chat("My ale is excellent -- would you like to try it?");
    add_chat("The dried beef takes up little space, and keeps well.");

    add_cchat("Depart, you traitorous cur!");
    add_cchat("You will rue this day!");
    add_cchat("Other rangers shall learn of your treachery!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({ "water", "glass of water" }), VBFC_ME("ask_water"));
    add_ask(({ "ale", "golden ale" }), VBFC_ME("ask_ale"));
    add_ask(({ "wine", "white wine"}), VBFC_ME("ask_wine"));
    add_ask(({ "stew", "vegetable stew"}), VBFC_ME("ask_stew"));
    add_ask(({ "beef", "dried beef", }), VBFC_ME("ask_beef"));
    add_ask(({ "whiskey", "rohan whiskey", "whiskey from rohan", }),
        VBFC_ME("ask_whiskey"));

#if 0
don't do this now. changing npc_ranger.c's inheritance to gondor std monster
may be what broke the knife (tho i don't see how), so i backed out that
change, which means there is no set_equipment() available.   gnad 15 oct 98
    set_equipment(WEP_DIR + "knife");
#endif
} /* create_ranger */


/*
 * Function name:	default_answer
 * Description	:	respond to unrecognized questions
 * Returns	:	string "" -- response is written here.
 */
public string
default_answer()
{ 
    command("peer "+TP->query_real_name());
    command("say The pricelist will give you a good idea of what I offer.");
    return "";
} /* default_answer */

/*
 * Function name:	ask_ale
 * Description	:	respond to questions about ale
 * Returns	:	string "" -- response is written here.
 */
public string
ask_ale()
{
    command("say It's an excellent golden ale.");
    return "";
} /* ask_ale */

/*
 * Function name:	ask_wine
 * Description	:	respond to questions about wine
 * Returns	:	string "" -- response is written here.
 */
public string
ask_wine()
{
    command("say The wine is a sparkling wine, made from Ithilien grapes.");
    return "";
} /* ask_wine */

/*
 * Function name:	ask_water
 * Description	:	respond to questions about water
 * Returns	:	string "" -- response is written here.
 */
public string
ask_water()
{
    command("say Our cold clean water is most refreshing!");
    return "";
} /* ask_water */

public string
ask_whiskey()
{
    command("nod .");
    command("say We sometimes get a bottle of whiskey brought in from "
      + "Minas Tirith.");
    command("say It is originally made in Rohan, and of high quality too.");
    command("say It's really just to please those who might like a nightcap "
      + "to be able to relax after a hard day's work.");
    command("say The supply is too small, so people should not be using it for "
      + "travel supplies, really.");
    return "";
}

/*
 * Function name:	ask_stew
 * Description	:	respond to questions about stew
 * Returns	:	string "" -- response is written here.
 */
public string
ask_stew()
{
    command("say The stew is a vegetable stew, hot and quite filling.");
    return "";
} /* ask_stew */

/*
 * Function name:	ask_beef
 * Description	:	respond to questions about beef
 * Returns	:	string "" -- response is written here.
 */
public string
ask_beef()
{
    command("say The beef is thinly sliced and air-dried.");
    command("say You won't find better, even in Minas Tirith.");
    return "";
} /* ask_beef */


/*
 * Function name:       add_introduced
 * Description  :       after a short delay, respond to introductions
 * Arguments    :       string who -- name of person who intro'd
 */
public void
add_introduced(string who)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(TP) &&
        CAN_SEE_IN_ROOM(TO) &&
        CAN_SEE(TO, TP) &&
        (!TP->query_met(query_name()) ||
         TP->query_wiz_level()))
    {
        set_alarm(5.0, 0.0, &do_introduce(TP, who));
    }
} /* add_introduced */


/*
 * Function name:       do_introduce
 * Description  :       respond to introductions
 * Arguments    :       object pl -- the person who intro'd
 *                      string name -- their name
 */
public void
do_introduce(object pl, string name)
{
    if (!present(pl, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("say Pleased to meet you, "+CAP(name)+".");
    command("introduce me to "+name);
} /* do_introduce */

/* solamnian prestige */
public int	query_knight_prestige()	{ return (-5); }

