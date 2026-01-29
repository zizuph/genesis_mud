
/*
 * skiamorphi_obj.c
 *
 * This is the spell object for the skiamorfi (Shadow Form) spell for 
 * the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Modifications by Bishop, April 2004.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

object s_shadow;
int st_timer = 0;
int revert_timer = 0;
int duration = 0;
int magic_resist = 0;
int success_level = 0;
string *tier1_adjs = ({"indistinct", "vaporous", "gossamer"});
string *tier2_adjs = ({"unearthly", "otherworldly", "ethereal"});
string *tier3_adjs = ({"celestial", "empyreal"});


void 
create_object()
{
    set_name("_skiamorfi_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    
    add_prop(OBJ_S_WIZINFO, "This is the spell object for the Spirit Circle" +
        " Shadow Form spell. It gives a bonus to defensive skills, a penalty" +
        " to the club skill, possibly a damage shield and possibly some magic"+
        " resistance. Players may also gain the ability to generate light or" +
        " darkness.\n");
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
	livings = FILTER_OTHER_LIVE(all_inventory(environment(TP)));
	if (strlen(intro_to))
	{
	    targets = PARSE_THIS(intro_to, "[the] %l") - ({TP});
	}
	else
	{
	    targets = FILTER_CAN_SEE(livings, TP);
	}
	if (!sizeof(targets))
	    return 0;
	index = -1;
	TP->catch_msg("You reveal your true identity to all those "+
	  "whom you just introduced to.\n");
	while (++index < sizeof(targets))
	{
	    TP->hook_add_player_i_introduced_to(targets[index]->query_real_name());
	    targets[index]->catch_msg(QCTNAME(TP)+" reveals "+
	    TP->query_possessive()+" true identity to you.\n");
	}

    }
    return 0;
}

int
do_revert()
{
    object ob;
    remove_alarm(st_timer);
    ob = environment(TO);
    dispel_spell_effect(ob);
    return 1;
}


int
warn_expire(object caster)
{
    caster->catch_tell("You feel the shadows of your skiamorfi weakening.\n");
    revert_timer = set_alarm(30.0, 0.0, &do_revert());
    return 1;
}


int
do_help(string str)
{
    if (!str || str != "skiamorfi")
        return 0;
    write("You may do the following in shadow form:\n"+
        "\n"+
        "    revert      - Revert back to normal form.\n"+
        "\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_revert,"revert");
    add_action(do_intro,"introduce");
    add_action(do_intro,"present");
    add_action(do_help,"help");
}

public int
start()
{
    int p_skill, d_skill, c_skill, success_number;
    int wis, gstat;

    string extra_desc = "";
    
    set_spell_effect_desc("shadow form");
   
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    success_number = gstat+wis+random(gstat/2);
             
    success_level = 1;

    setuid(); 
    seteuid(getuid());
    s_shadow=clone_object(SPIRIT_SPELLS+"skiamorfi_shadow");
    s_shadow->shadow_me(spell_target);
    spell_target->set_disguise(({tier1_adjs[random(sizeof(tier1_adjs))],
        "shadowy"}));

    if (success_number > 150 || spell_caster->query_wiz_level())
    {
        success_level = 2;        
        extra_desc = "You feel more protected.";
        spell_target->set_disguise(({tier2_adjs[random(sizeof(tier2_adjs))],
                                     "shadowy"}));        
    }
    
    if (success_number > 300 || spell_caster->query_wiz_level())
    {
        magic_resist = 15+random(spell_caster->query_stat(SS_OCCUP)/10);
        success_level = 3;        
        spell_target->set_disguise(({tier3_adjs[random(sizeof(tier3_adjs))],
                                     "shadowy"}));           
        extra_desc = "You feel more protected and resistant.";
    }
    
    write("You are now in shadow form. " + extra_desc +"\n");
    tell_room(environment(spell_target),"Out of the shadows steps "
        + QNAME(spell_target) + ".\n",({spell_target})); 
    spell_target->set_skiamorfi_level(success_level);
   
    duration = MIN(3000, 900+9*gstat+random(400));
    st_timer = set_alarm(itof(duration), 0.0, &warn_expire(spell_target));

    return 1;
}

/*
 * Function name:  query_magic_protection     (see /std/object.c)
 * Description:    This function should return the amount of 
 *                 protection versus an attack of 'prop' on 'obj'.
 * Arguments:      prop - The element property to defend.
 *                 protectee - Magic protection for who or what?
 */
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (prop == MAGIC_I_RES_MAGIC)
    {
        return ({ magic_resist, 0}); 
    }
    else
       return ::query_magic_protection(prop, protectee);
}

void
reapply_spell_effect()
{
  remove_alarm(st_timer);
  remove_alarm(revert_timer);
  st_timer = set_alarm(itof(duration), 0.0, &warn_expire(spell_target));
}


varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_msg("You revert back to normal form.\n");
    tell_room(environment(spell_target), "The shadows surrounding " + 
              QTNAME(spell_target) + " slip away.\n", ({spell_caster})); 
    spell_target->remove_disguise_shadow();
    remove_alarm(st_timer);
    tell_room(environment(spell_target),"When you look upon "+
              spell_target->query_objective()+" again, "+
              spell_target->query_pronoun()+" stands in the shape of a "+
              spell_target->query_nonmet_name()+".\n",({spell_target}));

    remove_spell_effect_object();
    return 1;
}
