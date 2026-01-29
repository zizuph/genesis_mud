/*
 * /d/Gondor/minas/npc/drunk.c
 *
 * Modification history:
 *	17 June 1998, Gnadnar:	fix runtime error in response to 
 *		drinks, general cleanup
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster";

#include <const.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_gondor_monster();
public void	arm_me();
public void	enter_inv(object obj, object from);
public void	got_gift(object gift, object player, int was_coin);
public void	give_hint(object player);


static string	*Hints = ({
    "The Gondorian Rangers have their Guildhouse in the Druedain Forest!",
    "The Shades need help! Check with Fredor down in Harlond!",
    "If you're tired of walking, you could travel by horse-wagon to Edoras!",
    "Take it from me: The Gondorian Rangers are the best trackers around!",
    "Be careful with the herbs you find in the wilderness, might be poison!",
    "There are trolls in the White Mountains, so beware!",
    "In Pelargir, visit Carastur, the Lord Councillor.",
    "Ithilien is very dangerous! Don't go there, or you'll die!",
    "I heard the rangers have ferries going over the Anduin in Osgiliath.",
    "The times, they are a-changing. And with the time, "+
	"the world changes, too!",
  });


/*
 * Function name:	create_gondor_monster
 * Description	:	set up the drunk
 */
public void
create_gondor_monster() 
{
    set_name(({"drunkard", "drunk"}));
    set_race_name("human");
    set_adj(({"drunken", "smelly"}));
    set_long(BSN("He is of middle height, out of shape, "+
	"and generally dishevelled. He appears to be somewhat the "+
	"worse for drink."));
    set_gender(G_MALE);
    set_alignment(10);
    GONDOR_MASTER->npcsize(TO, "normal", "plump");
    default_config_npc(28);
    set_base_stat(SS_CON,45);
    set_skill(SS_WEP_KNIFE, (random(10)+20));
    set_skill(SS_DEFENCE, (10+random(10)));
    set_skill(SS_AWARENESS, (10+random(5)));

    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    set_act_time(7);
    add_act("burp");
    add_act("say I think I'll have another drink.");
    add_act("hiccup");
    add_act("say Hey, why don't you buy me an ale, friend?");
    add_act("say It would be nice with an ale now.");
    add_act("say I think life would be worsche without alcohol.");
    add_act("say Perschonally I don't think there'sch ever gonna be a war.");
    add_act("burp");
    add_act("hiccup");
    add_act("say I don't like the thought of a war though.");
    add_act("sigh");
    add_act("say I really wouldn't mind an ale now.");
    add_act("drink ale");
    add_act("say How about buying me an ale, pal?");
    add_act("buy ale");
    add_act("drink ale");
    add_act("say Oh, an ale would be fine now.");

    set_equipment( ({ WEP_DIR+"dagger" }) );
} /* create_gondor_monster */

/*
 * Function name:	arm_me
 * Description	:	mask parent to add money
 */
public void
arm_me()
{
    ::arm_me();
    MONEY_MAKE_CC(120)->move(TO);
} /* arm_me */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to respond to gifts
 * Arguments	:	object obj -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object obj, object from)
{
    /* if the obj is a coin and if drunk already has coins of its type,
     * obj will be null on return from ::enter_inv(), so use was_coin 
     * to remember about it.
     */
    int	was_coin;

    was_coin = obj->id("coin");
    ::enter_inv(obj, from);

    if (objectp(from) &&
	living(from) &&
	(objectp(obj) ||
	 was_coin))
    {
	if (obj->id("ale"))
	{
	    set_alarm(2.0, 0.0, &give_hint(from));
	}
	else
	{
	    set_alarm(2.0, 0.0, &got_gift(obj, from, was_coin));
	}
        return;
    }
} /* enter_inv */

/*
 * Function name:	got_gift
 * Description	:	responds to gifts
 * Arguments	:	object gift -- the thing we got
 *			object player -- who gave it
 *			int was_coin -- true if gift was coins
 */
public void
got_gift(object gift, object player, int was_coin)
{
    if (was_coin ||
	MASTER_OB(gift) == "/std/coins")
    {
	command("smile");
	if (ENV(player) == ENV(TO))
	{
            command("say Why, thank you, my dear "+
		player->query_race_name()+".");
	}
	return;
    }

    if (function_exists("create_heap", gift) == "/std/drink")
    {
	command("drink " + gift->query_name());
        command("thank " + player->query_name());
        return;
    }
    command("say What am I supposed to do with this?");
    command("shrug");
    set_alarm(1.0, 0.0, &command("drop " + OB_NAME(gift)));
} /* got_gift */

/*
 * Function name:	give_hint
 * Description	:	tell the player something
 * Arguments	:	object player -- the person to tell
 */
public void
give_hint(object player)
{
    int		i = random(sizeof(Hints));
    string	name = player->query_real_name(),
		hint = Hints[i];

    seq_new("do_things");
    seq_addfirst("do_things",
	({"whisper "+name+" Thanks, pal! Let me tell you something...",
          "drink ale", "whisper "+name+" "+hint,
	  "hiccup","smile "+name,"burp"}));
} /* give_hint */

