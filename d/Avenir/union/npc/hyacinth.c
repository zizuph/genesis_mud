/*
 * Equipment saleswoman for the Union.
 *   Cirion, aug 5th, 1996
 *
 * Revisions:
 *	Lilith, Fed ????: Allow buying of items
 *	Lilith, Jun 2004: Removed cloning/selling of scarves
 *	Lilith, Jun 2004: Removed selling of items to non-members.
 *	Lucius, Jul 2017: Re-Code.
 *
 */
#pragma strict_types
#include "../defs.h"

inherit (NPC + "npc");
inherit "/d/Avenir/inherit/shop_list";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


public void
create_monster(void)
{
    if (!IS_CLONE)
	return;

    set_name("hyacinth");
    set_living_name("hyacinth");
    set_race_name("human");
    set_adj("serene");

    set_long("She looks about her with an air of calm and "
      + "confidence, as if she has passed by some dark and "
      + "terrible secret.\n");

    set_gender(G_FEMALE);
    set_base_stat(SS_OCCUP, 45);
    set_stats(({ 48, 106, 47, 85, 71, 84 }));

    set_union_npc();
    TO->set_union_sphere(SPH_HISTORY);

    set_skill(SS_LANGUAGE,      99);
    set_skill(SS_WEP_KNIFE,     49);
    set_skill(SS_PARRY,         15);
    set_skill(SS_WEP_MISSILE,   18);
    set_skill(SS_ACROBAT,       20);
    set_skill(SS_AWARENESS,    125);
    set_skill(SS_DEFENCE,       80);
    set_skill(SS_UNARM_COMBAT,  44);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_LOC_SENSE,     54);
    set_skill(SS_SWAY,          40);

    set_alignment(0);

    set_act_time(25);
    add_act("sigh softly");
    add_act("peer search");
    add_act("rub sphere");

    set_cact_time(3);
    add_cact("wield all");
    add_cact("fling");
    add_cact("sway");

    add_ask(({ "hizarbin" }), "say His is the domain of Water.", 1);
    add_ask(({ "darkness" }), "say It surrounds everything, "
      + "waiting to get in though the cracks that form in "
      + "our dreams, like the sands of an ever-encroaching desert.", 1);
    add_ask(({ "door" }), "say Only the Elders may pass through there.", 1);
    add_ask(({ "flame" }), "say It keeps us close to the "
      + "shadows, brings upon us the glories of the Sway.", 1);
    add_ask(({ "follow me" }), "say I most certainly will not.", 1);
    add_ask(({ "gate" }), "say The Gate was made long ago "
      + "from unknown metals, nothing can destroy it.", 1);
    add_ask(({ "guild" }), "say Ours is a Union, not a guild.", 1);
    add_ask(({ "hello" }), "say Greetings.", 1);
    add_ask(({ "help" }), "say I can offer you no help.", 1);
    add_ask(({ "hizbarin" }), "say His is a watery domain.", 1);
    add_ask(({ "improve" }), "say Nothing may I teach you.", 1);
    add_ask(({ "introduce" }), "introduce myself", 1);
    add_ask(({ "job" }), "say I have none to give you.", 1);
    add_ask(({ "join" }), "say You will need to seek elsewhere in "
      + "order to join the Union.", 1);
    add_ask(({ "joining" }), "say Joining the Union is difficult, "
      + "only the worthy may enter, and then only with the "
      + "permission of the Elders.", 1);
    add_ask(({ "key" }), "say I do not have the key.", 1);
    add_ask(({ "open" }), "say I cannot open this door.", 1);
    add_ask(({ "open door" }), "say No.", 1);
    add_ask(({ "pendent" }), "smile vague", 1);
    add_ask(({ "pine door" }), "say Only the Elders and "
      + "the Elect may pass through it.", 1);
    add_ask(({ "purchase" }), "say I can sell items to "
      + "those of the Union and our allies.", 1);
    add_ask(({ "quest" }), "say You will need to seek elsewhere "
      + "for one.", 1);
    add_ask(({ "scarf" }), "say They veil us in a dark shroud, "
      + "unrecognized may we walk this world of Infidels.", 1);
    add_ask(({ "secret" }), "emote narrows her eyes.", 1);
    add_ask(({ "secrets" }), "say I have learned many in my life, "
      + "dark and terrible they are.", 1);
    add_ask(({ "seek" }), "say What do you seek?", 1);
    add_ask(({ "service" }), "say I serve none but the Union and "
      + "its friends.", 1);
    add_ask(({ "shadow" }), "emote stares into space, "
      + "her face shrouded by whisps of shadows that "
      + "seem to pass along her like clouds.", 1);
    add_ask(({ "shadows" }), "say They are everywhere...", 1);
    add_ask(({ "shard" }), "say It was once very precious to "
      + "someone...", 1);
    add_ask(({ "sphere" }), "say It is our physical link "
      + "to the Jazur Flame.", 1);
    add_ask(({ "sway" }), "say Through the Sway we will "
      + "truly become one with the Flame.", 1);
    add_ask(({ "task" }), "say I have none to give you.", 1);
    add_ask(({ "union" }), "say The Union is one of Shadows.", 1);
    add_ask(({ "unlock" }), "say I can not.", 1);
    add_ask(({ "unlock door" }), "say No.", 1);

    add_prop(CONT_I_HEIGHT, 200);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    set_store_room(file_name(TO));

    set_maxlist(30);
    set_show_price(1);
    set_blank_lines(0);

    give(50, TO);
    enable_reset();

    equip(({OBJ+"robe", OBJ+"sandals"}));
}

private string *snds = ({ "speaks", "says", "whispers", "sings" });

public string
race_sound(void)
{
    return one_of_list(snds);
}

public void
reset_monster(void)
{
    int size = NUM_ITEMS("shirt");
    while(size < 6)
    {
	size++;
	clone_object(OBJ+"shirt")->move(TO);
    }

    size = NUM_ITEMS("pants");
    while(size < 6)
    {
	size++;
	clone_object(OBJ+"pants")->move(TO);
    }

    size = NUM_ITEMS("cape");
    while(size < 6)
    {
	size++;
	clone_object(OBJ+"cape")->move(TO);
    }
}

public void
refresh_living(void)
{
    reset_monster();
    ::refresh_living();
}

public void
init_living(void)
{
    ::init_living();

    add_action(do_list,  "list");
    add_action(do_buy,   "buy");
    add_action(do_show,  "show");
    add_action(do_value, "value");
}

/* Shop function redefinitions */

/* Only sell what I am supposed to */
public int
shop_hook_allow_buy(object ob)
{
    if (ob->query_worn() || ob->query_wielded())
	return 0;

    return (ob->id("cape") || ob->id("shirt") || ob->id("pants"));
}

public void
shop_hook_list_empty_store(string str)
{
    command("say I have nothing left.");
}

public string
shop_hook_list_object(object ob, int amount)
{
    if (!shop_hook_allow_buy(ob))
	return "";
    else
	return ::shop_hook_list_object(ob, amount);
}

public int
do_buy(string str)
{
    if (query_attack())
    {
	write(CAP(query_pronoun()) + " seems too busy right now.\n");
	return 1;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOBUY))
    {
	command("us I have been instructed by the Elders to sell "
	  + "you nothing, " + TP->query_name() + ".");
	return 1;
    }

    if (!IS_MEMBER(TP))
    {
	command("say I am not permitted to sell to you, "
	  + TP->query_race_name() + ".");
	return 1;
    }

    return ::do_buy(str);
}

public string
category(object ob)
{
    if (ob->id("pants"))
	return "Pants";

    if (ob->id("shirt"))
	return "Shirt";

    if (ob->id("cape"))
	return "Cape";
}

public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    force_new_list();
}
