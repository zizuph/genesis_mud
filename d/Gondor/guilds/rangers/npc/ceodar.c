/*
 * /d/Gondor/common/guild/ithilien/npc/ceodar.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * The cook for the Ithilien guild
 *
 * Modification log:
 *    Alto, Feb 2002. Move and modify to new rangers theme.
 *    Tigerlily, Oct 2003: fixed gender
 */
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "npc_ranger.c";


/* prototypes */
public void     create_ranger();
public void     introduce(object pl);
public int      query_knight_prestige();
public string   def_answer();
public string   whiskey_ask();


/*
 * Function name: create_ranger
 * Description  : set up the cook
 */
public void
create_ranger() 
{
    set_gender(G_MALE);
    set_name("ceodar");
    add_name("cook");
    set_race_name("human");
    set_adj("cheerful");
    add_adj("grey-haired");
    set_title("the Head Cook of the Rangers of the Ithilien");
    set_long("This grey-haired man seems to be in a " +
        "good humor. He leans against the crates, dispensing " +
        "food and drink with an air of easy competence.\n");

    /* values taken from the northern innkeeper */
    default_config_npc(42);
    set_base_stat(SS_INT,   55);
    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE,   30);
    set_skill(SS_TRADING,   55);
    set_alignment(200 + random(200));

    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("You look thirsty.");
    add_chat("My ale is excellent -- would you like to try it?");
    add_chat("The dried beef takes up little space, and keeps well.");

    add_cchat("Depart, you traitorous cur!");
    add_cchat("You will rue this day!");
    add_cchat("Other rangers shall learn of your treachery!");

    set_default_answer(&def_answer());
    add_ask(({ "water", "glass of water" }),
        "say Our cold clean water is most refreshing!", 1);
    add_ask(({ "ale", "golden ale" }),
        "say It's an excellent golden ale.", 1);
    add_ask(({ "wine", "white wine"}),
        "say The wine is a sparkling wine, made from Ithilien grapes.", 1);
    add_ask(({ "stew", "vegetable stew"}),
        "say The stew is a vegetable stew, hot and quite filling.", 1);
    add_ask(({ "beef", "dried beef", }),
        "say The beef is thinly sliced and air-dried. You won't find " +
        "any better, even in Minas Tirith.", 1);
    add_ask(({ "whiskey", "rohan whiskey", "whiskey from rohan", }),
        &whiskey_ask(), 1);
        
    set_company_no(1);
}

public string
def_answer()
{
    
    command("peer " + OB_NAME(TP));
    command("say The pricelist will give you a good idea of what I offer.");
    return "";
}

public string
whiskey_ask()
{
    command("nod .");
    command("say We sometimes get a bottle of whiskey brought in from " +
        "Minas Tirith.");
    command("say It is originally made in Rohan, and of high quality too.");
    command("say It's really just to please those who might like a " +
        "nightcap to be able to relax after a hard day's work.");
    command("say The supply is too small, so people should not be using " +
        "it for travel supplies, really.");
    return "";
}

/*
 * Function name: introduce
 * Description  : respond to introductions
 * Arguments    : object pl -- the person who intro'd
 *                string name -- their name
 */
public void
introduce(object pl)
{
    if (!present(pl, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("say Pleased to meet you!");
    command("introduce me to " + OB_NAME(pl));
}

/* 
 * Function name: query_knight_prestige
 * Description  : Gives negative prestige for Solamnian knights.
 * Returns      : -5 prestige
 */
public int
query_knight_prestige()
{
    return (-5);
}

