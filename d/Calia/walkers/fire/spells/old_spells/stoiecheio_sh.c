/*
 *   Igneous' Disguise Shadow   
 *
 *   This shadow is used to disguise a players met/nonmet description
 *
 *   Copyright (C) Chad Richardson July 1996
 *
 *   Revision history:
 *   Igneous: too many to count *grin* This final version was done Jan 9 1997
 *   Igneous: Made drastic changes and removed a bunch of shadowed functions
 *            which became obsolete.  Feb 21, 1997
 *   Igneous: Changed the disguise so it used a Mapping instead of 2 object
 *            arrays.   June 14th, 1997
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>

#define SW   shadow_who

//    Prototypes
public int my_neverknown();
private mixed query_list(mixed list, int arg);

//   Global Vars
private string *Intro_list = ({});
int Block_prop = 0;
string Adj1 = "large", Adj2 = "blazing";

/*
 * Function name :  remove_disguise_shadow
 * Description   :  remove this shadow from a player.
 */
void remove_disguise_shadow() {remove_shadow();}

/*
 * Function name :  remove_shadow
 * Description   :  Removes all the props we added to the player
 *                  and removes the shadow
 */
void
remove_shadow()
{	
    SW->remove_prop(LIVE_I_NEVERKNOWN);
    destruct();
}

/*
 * Function name :  set_disguise
 * Arguments     :  *string vars,  an array of vars we need to have to make
 *                  this disguise.
 * Description   :  Does what is says... sets up the disguise.
 */
void
set_disguise(string *vars)
{
    //  Can't fool ourselves
    Intro_list = ({SW->query_real_name()});

    Adj1 = vars[0];
    Adj2 = vars[1];
    SW->add_prop(LIVE_I_NEVERKNOWN, my_neverknown);
    Block_prop = 1;
}

public int 
my_neverknown()
{
    object player = previous_object(-1);

    if (player->query_wiz_level())
	return 0;
    if (member_array(player->query_real_name(), Intro_list) == -1)
	return 1;
    else
	return 0;
}

mixed add_prop_live_i_neveknown()  {return Block_prop;}

void
hook_add_player_i_introduced_to(string name)
{
    name = lower_case(name);
    if (!objectp(find_player(name)))
	return;
    if (member_array(name, Intro_list) == -1)
	Intro_list += ({name});
}


/* 
 *  All functions that this shadow masks should be placed 
 *  below this comment header, -Igneous-  
 */


/*
 * Function name :  parse_command_adjectiv_id_list
 * Description   :  Adds the disguised adverbs to the adjective list
 */
string *
parse_command_adjectiv_id_list()
{
    return ({Adj1}) + ({Adj2});
}

string *
parse_command_id_list()
{
    return ({SW->query_real_name(), OB_NAME(SW), 
      "elemental", "fire elemental"});
}

private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
	return 0;
    if (!arg && sizeof(list))
	return list[0];
    else
	return list + ({});
}

varargs public mixed
query_adj(int arg)
{
    return query_list(({Adj1,Adj2}), arg);
}

public string *
query_adjs() 
{ 
    return query_list(({Adj1, Adj2}), 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, ({Adj1, Adj2})) >= 0);
}

string
query_race_name()
{
    return "fire elemental";
}

public varargs string
long(mixed for_obj)
{
    if (!objectp(for_obj))
    for_obj = this_player();

    return (SW == for_obj ? "You are a raging inferno in the vague shape "+
        "of a humanoid.  You pulse and flicker as waves of intense heat "+
        "flow from your body.  Small wisps of smoke trail up from where "+
        "your feet touch the ground." : capitalize(SW->query_pronoun())+
        " is a raging inferno in the vague shape of a humanoid.  "+
        capitalize(SW->query_pronoun()) + " pulses and flickers as "+
        "waves of intense heat flow from " + SW->query_objective() + 
        ".  You dare not look at "+SW->query_objective() + " closely "+
        "as looking directly at "+SW->query_objective() + " burns your "+
        "eyes.  Small wisps of smoke trail up from where " + 
        SW->query_pronoun() + " touches the ground.") + "\n";
} 

public string
race_sound()
{
    return "roars in a hissing, crackling voice";
}

public void
shadow_me_transform(object target)
{
    shadow_me(target);
}
