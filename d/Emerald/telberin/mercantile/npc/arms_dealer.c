/*
 *  /d/Emerald/telberin/mercantile/npc/arms_dealer.c
 *
 *  This is the shopkeeper for the Arms Shop in Telberin.
 *  He is also part of a quest to return an ancient sword
 *  which can be found in Del Rimmon.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Emerald/blackwall/delrimmon/antique_dealer";
inherit "/d/Genesis/lib/intro";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* 
 * Function name:        create_telberin_elf
 * Description  :        set up the npc
 */
public void
create_telberin_elf() 
{
    set_living_name("annu");
    set_name("annu");
    add_name( ({ "owner", "shopkeeper", "shopowner",
                 "arms dealer", "dealer" }) );
    add_name("_telberin_antique_sword_dealer");
    set_adj( ({ "muscular", "keen-eyed" }) );

    set_title("Vashenti, Arms Dealer of the Telberin Merchants"
     + " Guild");

    set_short("muscular, keen-eyed elf");
    set_long("This elf looks strong and savvy about his business."
      + " He moves about the shop with confidence and purpose,"
      + " examining his wares and restocking his shelves. He is"
      + " always glad to see customers, but keeps a close eye on"
      + " those he does not recognize.\n");

    config_elf(130); /* This guy is a former member of the KoT */

    set_skill(SS_WEP_SWORD, random(10)+80);
    set_skill(SS_DEFENCE,   random(10)+60);
    set_skill(SS_PARRY,     random(10)+50);
    set_skill(SS_AWARENESS, random(10)+50);
    set_skill(SS_TRADING,   90);

    set_alignment(50 + random(100));

    set_default_answer(VBFC_ME("default_answer"));
    add_ask( ({ "sword", "antique sword", "antique", "antiques",
                "old sword", "rusty sword", "rusty old sword",
                "old rusty sword", "hilt" }),
                antique_ask);

    set_act_time(20);
    add_act("emote strolls around the shop, carefully inspecting his"
      + " wares.");
    add_act("emote picks up a sword from one of the display cases"
      + " and holds it at eye length, examining the line of the"
      + " metal as it extends from the hilt.");
    add_act("emote polishes a bit of tarnish from a suit of armour.");
    add_act("emote stares contentedly around the room.");
    add_act("emote applies a fine oil coat to the blade of a"
      + " particularly expensive-looking sword.");

    set_cact_time(10);
    add_cact("emote tries desparately to avoid your attacks.");
    add_cact("emote peers at you in surprise and outrage.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote shrieks: You shall not come by my wares by blood,"
      + " scoundrel!"); 

    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_job_response("My living is based on dealing fine armours"
      + " and weapons. Perhaps I can interest you in such things?");
}

varargs void
do_bow(object tp = TP)
{
    if (objectp(tp))
        command("salute " + TP->query_real_name());
    command("say Hello, good adventurer!");
    command("say Can I offer you any of my excellent wares?");
}


public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!interactive(actor))
	return;

    switch(emote)
    {
    case "bow":
	set_alarm(2.0, 0.0, &do_bow(TP));
	break;
    case "wellmet":
	set_alarm(2.0, 0.0, &command("wellmet"));
	break;
    case "smile":
	set_alarm(2.0, 0.0, &command("smile at " + actor->query_real_name()));
	break;
    case "sigh":
	set_alarm(2.0, 0.0, &command("comfort " + actor->query_real_name()));
	break;
    case "wave":
	if (!strlen(adverb) || (adverb == "happily"))
	    adverb = "goodbye";
	set_alarm(2.0, 0.0, &command("wave "+adverb+" to " + actor->query_real_name()));
	break;
    }
}
	

string
default_answer()
{
    command("peer "+TP->query_real_name());
    command("say I'm sorry, but I don't know what you're talking about.");

    return "";
}


void
return_object(object obj, object to)
{
    string  name = to->query_real_name(),
            obname = OB_NAME(obj);

    if (react_to_antique(obj, to))
    {
        command("give " +obname+ " to " + name);
        return;
    }

    if (obj->id("coin"))
    {
        command("say Well now ...");
        command("say Awfully kind of you to tip!");
        command("beam");
        return;
    }

    command("say Thanks, but I don't think I need that.");
    command("give " + obname + " to " + OB_NAME(to));
    if (ENV(obj) == TO)
    {
       command("drop " + obname);
    }
}



/*
 * function name:        init_living
 * description:          a patch for the automatic attack if this
 *                       mobile can do that. in this case, we use it
 *                       to check whether Merdol notices any antiques
 *                       that the player might be carrying.
 */
public void
init_living()
{
    ::init_living();

    set_alarm(1.0, 0.0, &check_for_antique(this_player()));
} /* init_living */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */


void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) || !objectp(obj) || !living(from))
        return;

    set_alarm(0.5, 0.0, &return_object(obj, from));
}
