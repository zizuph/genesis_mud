
/* Fire Elemental Object

   Conjured by the Stoiecheio spell of the Firewalkers.

   Coded by Jaacar 

*/

#pragma strict_types

inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/object";

#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <filter_funs.h>

object s_shadow;
int    st_timer;
string *adjectives1 = ({"angry","enormous","colossal","gigantic","massive","immense","great"});
string *adjectives2 = ({"roaring","blazing","white-hot","flickering","raging","fiery","flaming","shimmering"});
string adj1, adj2, new_short;

varargs public int dispel_spell_effect(object dispeller);

void 
create_object()
{
    set_name("stoicheio_obj");
    add_name(STOIECHEIO_OBJ);
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
}

int
do_intro(string str)
{
    string intro_to, intro_who;
    int index;
    object *targets, *livings;

    if (!str)
	return 0;

    if (sscanf(str, "%s to %s", intro_who, intro_to) != 2)
    {
	intro_who = str;
    }
    if (intro_who == "me" || intro_who == "myself")
    {
	livings = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
	if (strlen(intro_to))
	{
	    targets = PARSE_THIS(intro_to, "[the] %l") - ({this_player()});
	}
	else
	{
	    targets = FILTER_CAN_SEE(livings, this_player());
	}
	if (!sizeof(targets))
	    return 0;
	index = -1;
	this_player()->catch_msg("You reveal your true identity to all those "+
	  "whom you just introduced to.\n");
	while (++index < sizeof(targets))
	{
	    this_player()->hook_add_player_i_introduced_to(targets[index]->query_real_name());
	    targets[index]->catch_msg(QCTNAME(this_player())+" reveals "+
	      this_player()->query_possessive()+" true identity to you.\n");
	}
    }
    return 0;
}

int
do_check_mana()
{
    object ob;

    ob = environment(this_object());
    if (ob->query_mana() < 25)
    {
        write("You do not have enough mental power to retain your elemental "+
        "form.\n");
        seteuid(getuid());
        this_object()->do_revert();
        return 1;
    }
    ob->add_mana(-25);
    return 1;
}

int
do_revert()
{
    object ob;
    ob = environment(this_object());
    dispel_spell_effect(ob);
    return 1;
}

int
do_help(string str)
{
    if (!str || str != "stoiecheio emotes")
        return 0;
    write("You may do the following in elemental form:\n"+
        "\n"+
        "    flicker    - Make your body flicker\n"+
        "    radiate   - Make your body radiate heat\n"+
        "    revert    - Revert back to normal form\n"+
        "\n"+
        "NOTE: You will continue to use mana as you stay in elemental form.\n");
    return 1;
}

int
do_flicker()
{
    object ob;
    ob = environment(this_object());
    ob->catch_msg("You make your body flicker.\n");
    tell_room(environment(ob),"The "+new_short+" fire elemental "+
        "flickers briefly.\n",({ob}));
    return 1;
}

int
do_radiate()
{
    object ob;
    ob = environment(this_object());
    ob->catch_msg("You radiate heat from your body.\n");
    tell_room(environment(ob),"The "+new_short+" fire elemental "+
        "pulses as waves of heat radiate from "+ob->query_possessive()+
        " body.\nYou are forced to take several steps back to avoid being "+
        "burned by the heat.\n",({ob}));
    return 1;
}

void
init()
{
    ::init();
    add_action("do_revert","revert");
    add_action("do_flicker","flicker");
    add_action("do_radiate","radiate");
    add_action("do_intro","introduce");
    add_action("do_intro","present");
    add_action("do_help","help");
}

varargs public int
dispel_spell_effect(object dispeller)
{
    dispeller->catch_msg("You revert back to normal form.\n");
    tell_room(environment(dispeller),"The "+new_short+" fire elemental "+
        "emits a searing, blinding flash of light.  You are forced to "+
        "avert your eyes.\n",({dispeller}));
    dispeller->remove_disguise_shadow();
    remove_alarm(st_timer);
    tell_room(environment(dispeller),"When you look upon "+dispeller->query_objective()+
        " again, "+dispeller->query_pronoun()+" stands in the shape of a "+
        dispeller->query_nonmet_name()+".\n",({dispeller}));
    remove_spell_effect_object();
    return 1;
}

public int
start()
{
    int j,k;
    object ob;
    
    j = random(sizeof(adjectives1));
    k = random(sizeof(adjectives2));
    adj1 = adjectives1[j];
    adj2 = adjectives2[k];
    new_short = adj1 + " " + adj2;
    ob = spell_target;
   
    set_spell_effect_desc("stoiecheio");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    setuid(); 
    seteuid(getuid());
    s_shadow=clone_object(STOIECHEIO_SH);
    s_shadow->shadow_me(ob);
    ob->set_disguise(({adj1,adj2}));
    write("You are now in elemental form.  Use 'help stoiecheio emotes' "+
        "to see your commands.\n");
    tell_room(environment(ob),"Out of it steps a "+new_short+" fire elemental.\n",({ob}));
    st_timer = set_alarm(100.0, 100.0, &do_check_mana());
}

