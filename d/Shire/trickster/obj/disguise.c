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
#include "/d/Shire/skills.h"
#include <ss_types.h>
#include <language.h>


#define SW   shadow_who
#define DISGUISE_TASK(o)  SW->resolve_task(TASK_ROUTINE, \
            ({SKILL_AVG, TS_INT, TS_WIS, SKILL_END, SS_DISGUISE}), \
            o, ({SKILL_AVG, TS_INT, TS_WIS, SKILL_END, SS_AWARENESS}))
#define DISGUISE_SUBLOC  "_trickster_disguise_subloc"
#define CAP(s)   capitalize(s)
#define HE_SHE(o)  o->query_pronoun()
#define HIM_HER(o)  o->query_objective()


//    Prototypes
int query_is_fooled(object player);
public int my_neverknown();
void remove_disguise();
private mixed query_list(mixed list, int arg);


//   Global Vars
private mapping Players = ([]);
int Block_prop = 0;
string Adj1, Adj2;

/*
 * Function name :  query_disguise_shadow
 * Description   :  A quick easy way to see if someone has this shadow
 */
int query_disguise_shadow() {return 666;}

int query_disguised() {return 1;}

void
query_player_mapping() {dump_mapping(Players);}

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
    SW->remove_prop(OBJ_S_SEARCH_FUN);
    SW->remove_prop(OBJ_I_SEARCH_TIME);
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
    Players[SW->query_real_name()] = "Passed";

    Adj1 = vars[0];
    Adj2 = vars[1];
    SW->add_subloc(DISGUISE_SUBLOC,this_object());
    SW->add_prop(LIVE_I_NEVERKNOWN, my_neverknown);
    SW->add_prop(OBJ_I_SEARCH_TIME, 3); // 3 second search time
    SW->add_prop(OBJ_S_SEARCH_FUN, "attempt_reveal_disguise");
    Block_prop = 1;
}

public int my_neverknown() {return query_is_fooled(previous_object(-1));}

/* 
 * Function name :  add_prop_*
 * Description   :  To prevent people from altering the props.
 */
mixed add_prop_live_i_neveknown()  {return Block_prop;}
mixed add_prop_obj_i_search_time() {return Block_prop;}
mixed add_prop_obj_s_search_fun() {return Block_prop;}

/*
 * Function name :  add_prop_*     
 * Description   :  Switches the Block prop so the props this shadow adds
 *                  Can not be altered.
 */

/*
 * Function name :  query_is_fooled
 * Arguments     :  object player,  The player we want to test
 * Description   :  Basically a filter which figures out who is fooled
 *                  by this disguise and who is not.
 * Returns       :  1 if fooled
 *               :  0 if not fooled
 */
int
query_is_fooled(object player)
{
    string name;

    if (!objectp(player) || !living(player))
	return 0;
    if (player->query_npc())  //  Npcs always get fooled
	return 1;
    if (player->query_wiz_level())  //  Can't fool wizards
	return 0;

    name = player->query_real_name();
    if (Players[name] == "Passed")
	return 0;
    if (Players[name] == "Failed")
	return 1;
    if (DISGUISE_TASK(player) <= 0)
    {
	Players[name] = "Passed";
	return 0;
    }
    else
    {
	Players[name] = "Failed";
	return 1;
    }
}

/*
 * Function name :  add_not_fooled_by_disguise
 * Arguments     :  object player  the player object we want to have
 *                  know that the shadowed person is disguised
 * Description   :  moves a player from the fooled array to the not_fooled
 *                  array. In other words lets them know that the shadowed 
 *                  person is disguised.
 */
void
add_not_fooled_by_disguise(object player)
{
    if (!player || !player->query_login_from())
	return;
    Players[player->query_real_name()] = "Passed";
}

/*
 * Function name : attempt_reveal_disguise
 * Arguments     : object player,  The player who tried to reveal the disguise
 * Description   : This function determines if a player can reveal a disguise
 *                 or not.
 */
string
attempt_reveal_disguise(object player, string str)
{
    if (!present(player,environment(SW)))
	return 0;
    if (query_is_fooled(player))
    {
	if (DISGUISE_TASK(player) >= 20)
	{
	    /*  
	     *  Poor sap is really fooled by the disguise so he won't
	     *  be able to reveal it 
	     */  
	    return 0;
	}  
    }
    set_alarm(0.1,0.0,remove_shadow);
    SW->catch_msg(QCTNAME(player)+" removes your disguise!\n");
    tell_room(environment(SW), QCTNAME(player)+" reveals that "+QTNAME(SW)+
      " was disguised!\n",({SW,player}));
    return "You reveal "+
    LANG_POSS(SW->query_the_name(player))+" disguise.\n";
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
    return ({Adj1}) + ({Adj2}) + ({ SW->query_gender_string() });
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


public varargs string
short(object who)
{
    int success;
    string desc, extra;

    if (!objectp(who))
	who = this_player();

    if (query_is_fooled(who))
    {
	desc = SW->query_nonmet_name();
    }
    else
    {
	if (SW->notmet_me(who))
	    desc = SW->query_nonmet_name() + " wearing a disguise";
	else
	    desc = SW->query_met_name() + " wearing a disguise";
    }

    if (strlen(extra = SW->query_prop(LIVE_S_EXTRA_SHORT)))
    {
	return (desc + " and " + extra);
    }
    return desc;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != DISGUISE_SUBLOC)
    {
	return SW->show_subloc(subloc,on,for_obj);
    }
    if (for_obj == on)
    {
	return "You have disguised yourself as "+
	LANG_ADDART(SW->query_nonmet_name()) +".\n";
    }
    if (!query_is_fooled(for_obj))
    {
	return CAP(HE_SHE(SW)) + " is attempting to disguise "+
	HIM_HER(SW)+"self as "+LANG_ADDART(SW->query_nonmet_name())+".\n";
    }
    return "";
}

//   If attacked it's quite impossible to keep the disguise on
public void
attacked_by(object attacker)
{
    set_alarm(1.0,0.0,remove_disguise);
    SW->attacked_by(attacker);
}

//    We can't keep our disguise on while killing someone!
public void
attack_object(object ob)
{
    set_alarm(1.0,0.0,remove_disguise);
    SW->attack_object(ob);
}

//  Tell the player and the Room the fact that a disguise has fallen off
void
remove_disguise()
{
    if (environment(SW))
	tell_room(environment(SW), QCTNAME(SW)+"'s disguise falls off!!\n",
	  SW);
    SW->catch_msg("Your disguise falls off, revealing your true identity!!\n");
    remove_shadow();
}



