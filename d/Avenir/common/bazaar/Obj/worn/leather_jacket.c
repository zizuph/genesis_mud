// -*-C++-*-
// file name:	leather_jacket.c
// creator(s):  	Sirra
// last update:	Feb 98
// purpose:       Boost a man's ego ;)
// revisions:   Lilith, Jul 1998 : converted to /lib/wearable_item
// 		Lucius, Mar 2018 : converted to /lib/commands

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/commands";
inherit "/lib/keep";

#include <wa_types.h>		//Weapon types
#include <stdproperties.h>	//the properties
#include <macros.h>		
#include <filter_funs.h>	//FILTER_GENDER()
#include <adverbs.h>		//NO_ADVERB_WITH_SPACE

int strut(string str);
int dance(string str);

void
create_object()
{
    set_keep(1);

    set_name("jacket");
    set_adj("black");
    add_adj("leather");
    add_pname(({"clothes", "clothing"}));

    set_long("A black leather jacket, slightly "
      + "worn, and oozing coolness. "
      + "Only rebels wear this.\n");

    set_short("black leather jacket");

    config_wearable_item(A_TORSO, 1, 15, this_object());

    add_prop(OBJ_I_VALUE, 288);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1600);
	
	if (IS_CLONE)
      set_item_expiration();  	  

}

int
init()
{
    ::init();
    add_action(strut, "strut");
    add_action(dance, "dance");
}

//Code format modeled after ~Avenir/bazaar/Obj/worn/gloves.c 
//Filters players in this_players() environment and prints 
//different messages to different sexes when this_player
//wears the jacket.
//Called by set_af()
mixed
wear(object ob)
{
    if (worn)
    {
	tell_object(this_player(), "You already wear a black leather "
	  + "jacket!\n");

	return 0;
    }

    worn = 1;

    if (this_player()->query_gender() == G_MALE)
    {
	tell_object(this_player(),"You wear the leather "
	  + "jacket over your shoulders and slick your hair back. "
	  + "You feel quite the ladies man.\n"
	  + "You're the one they want...\n"
	  + "You're the one they've always wanted...\n");

	this_player()->add_prop(LIVE_S_SOULEXTRA, "ultra cool");

	FILTER_GENDER(all_inventory(environment(this_player())),
	  G_FEMALE) -> catch_msg(QCTNAME(this_player())
	  + " wears a black leather jacket over "
	  + "his shoulders and slicks back "
	  + "his hair. He looks irresistable.\n"
	  + "He's the one you want...\n"
	  + "He's the one you've always wanted...\n");

	FILTER_GENDER(all_inventory(environment(this_player()))
	  - ({this_player()}), G_MALE) 
	-> catch_msg(QCTNAME(this_player())
	  + " wears a black leather jacket over "
	  + "his shoulders and slicks back "
	  + "his hair. The women will be here soon.\n");

	return 1;
    }

    else
    {
	tell_object(this_player(),"You wear the leather "
	  + "jacket over your shoulders and toss your head "
	  + "back. You feel quite saucy.\n");

	this_player()->add_prop(LIVE_S_SOULEXTRA, "ultra cool");

	tell_room(environment(this_player()), QCTNAME(this_player())
	  + " wears a black leather jacket over "
	  + "her shoulders and tosses her head back, saucily."
	  + "\n", this_player());

	return 1;
    }

}

mixed
remove(object ob)
{
    object tp = query_worn();

    worn=0;

    tell_object(tp, "You remove your black "
      + "leather jacket, returning to the world of "
      + "the ordinary.\n");

    tp->remove_prop(LIVE_S_SOULEXTRA, "ultra cool");

    tell_room(environment(tp), QCTNAME(tp) + " removes " +
	tp->query_possessive() + " black leather jacket, looking " +
	"decidedly less cool.\n", tp);

    return 1;
}

//Mask the strut emote with mine.
int
strut(string str)
{
    str = check_adverb_with_space(str, "cooly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Strut how?\n");
	return 0;
    }

    write("You strut your stuff," + str +
	" in your leather jacket!\n");
    all(" struts" + str + " in " +
	this_player()->query_possessive() +
	" leather jacket.", str);
    return 1;
}

int
dance(string str)
{
    object *oblist;

    if (!query_worn())
	return 0;

    if (!stringp(str))
    {
	write("For once doing the disco duck doesn't feel silly.\n");
	all(" does the disco duck and somehow still looks cool.");
	return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Dance with whom?\n");
	return 0;
    }

    actor("You sweep", oblist, " across the dance floor.");
    all2act(" sweeps", oblist, " across the dance floor.");
    target(" sweeps you across the dance floor.", oblist);
    return 1;
}

/*
 * Function name: leave_env
 * Description:   The clothing is moved from the inventory.
 * Arguments:     from - Where from  to - Destination.
 */
void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}
