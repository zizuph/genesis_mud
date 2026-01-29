
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
int st_timer, p_mod, d_mod, c_mod;
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
do_check_mana()
{
    object ob;

    ob = environment(TO);
    if (ob->query_mana() < 25)
    {
        write("You do not have enough mental power to retain your shadow "+
        "form.\n");
        seteuid(getuid());
        TO->do_revert();
        return 1;
    }
    ob->add_mana(-25);
    return 1;
}

int
do_revert()
{
    object ob;
    ob = environment(TO);
    dispel_spell_effect(ob);
    return 1;
}

int
do_help(string str)
{
    if (!str || str != "skiamorfi emotes")
        return 0;
    write("You may do the following in shadow form:\n"+
        "\n"+
        "    sfradiate   - Radiate darkness.\n"+
        "    sfglow      - Radiate light.\n"+
        "    revert      - Revert back to normal form.\n"+
        "\n"+
        "NOTE: You will continue to use mana as you stay in shadow form.\n");
    return 1;
}

void
brighten()
{
    spell_caster->catch_tell("The darkness you are radiating diminishes.\n");
    TO->add_prop(OBJ_I_LIGHT, TO->query_prop(OBJ_I_LIGHT) + 1);
}

//Radiate darkness: Costs us 30 mana.
int
do_radiate()
{
    if (success_level < 2)
    {
        notify_fail("You are not strong enough to radiate darkness.\n");
        return 0;
    }
    
    if (TO->query_prop(OBJ_I_LIGHT) <= -5)
    {
        notify_fail("You are unable to grow any darker.\n");
        return 0;
    }
    
    if (spell_caster->query_mana() < 30)
    {
        notify_fail("You do not have the mental strength to radiate" +
            " darkness.\n");
        return 0;
    }

    spell_caster->add_mana(-30);
    set_alarm(300.0, 0.0, &brighten());
    spell_caster->catch_msg("Your form grows darker, sucking light from your" +
        " surroundings.\n");
    tell_room(environment(spell_caster), QCTNAME(spell_caster) + " grows" +
        " darker, sucking light from the surroundings.\n", ({spell_caster}));
    TO->add_prop(OBJ_I_LIGHT, TO->query_prop(OBJ_I_LIGHT) - 1);
    
    return 1;
}


void
darken()
{
    spell_caster->catch_tell("The light you are radiating diminishes.\n");
    TO->add_prop(OBJ_I_LIGHT, TO->query_prop(OBJ_I_LIGHT) - 1);
}


//Radiate light: Costs us 30 mana.
int
do_glow()
{
    if (success_level < 2)
    {
        notify_fail("You are not strong enough to radiate light.\n");
        return 0;
    }
    
    if (TO->query_prop(OBJ_I_LIGHT) >= 5)
    {
        notify_fail("You are unable to grow any brighter.\n");
        return 0;
    }
    
    if (spell_caster->query_mana() < 30)
    {
        notify_fail("You do not have the mental strength to radiate" +
            " light.\n");
        return 0;
    }
    
    spell_caster->add_mana(-30);
    set_alarm(300.0, 0.0, &darken());
    spell_caster->catch_msg("Your form grows brighter, casting light on your" +
        " surroundings.\n");
    tell_room(environment(spell_caster), QCTNAME(spell_caster) + " grows" +
        " brighter, casting light on the surroundings.\n", ({spell_caster}));
    TO->add_prop(OBJ_I_LIGHT, TO->query_prop(OBJ_I_LIGHT) + 1);
    
    return 1;
}

void
init()
{
    ::init();
    add_action(do_revert,"revert");
    add_action(do_glow, "sfglow");
    add_action(do_radiate,"sfradiate");
    add_action(do_intro,"introduce");
    add_action(do_intro,"present");
    add_action(do_help,"help");
}

public int
start()
{
    int p_skill, d_skill, c_skill, success_number;
    string extra_desc = "";
    
    set_spell_effect_desc("shadow form");
   
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    success_number = spell_caster->query_stat(SS_WIS) +
        spell_caster->query_stat(SS_OCCUP) + 
        spell_caster->query_casting_bonus();
    success_level = 1;

    setuid(); 
    seteuid(getuid());
    s_shadow=clone_object(SPIRIT_SPELLS+"skiamorfi_shadow");
    s_shadow->shadow_me(spell_target);
    spell_target->set_disguise(({tier1_adjs[random(sizeof(tier1_adjs))],
        "shadowy"}));

    if (success_number > 250 || spell_caster->query_wiz_level())
    {
        spell_caster->shield_active(25);
        success_level = 2;        
        extra_desc = "You feel more protected.";
        spell_target->set_disguise(({tier2_adjs[random(sizeof(tier2_adjs))],
            "shadowy"}));        
    }
    
    if (success_number > 400 || spell_caster->query_wiz_level())
    {
        spell_caster->shield_active(33);    
        magic_resist = 25;
        success_level = 3;        
        spell_target->set_disguise(({tier3_adjs[random(sizeof(tier3_adjs))],
            "shadowy"}));           
        extra_desc = "You feel more protected and resistant.";
    }
    
    write("You are now in shadow form. " + extra_desc + 
        " Use 'help skiamorfi emotes' "+
        "to see your commands.\n");
    tell_room(environment(spell_target),"Out of the shadows steps "
        + QNAME(spell_target) + ".\n",({spell_target})); 
    spell_target->set_skiamorfi_level(success_level);
   
    p_skill = spell_caster->query_skill(SS_PARRY);
    d_skill = spell_caster->query_skill(SS_DEFENCE);
    c_skill = spell_caster->query_skill(SS_WEP_CLUB);
    
    p_mod = MIN(25, 100 - p_skill);
    d_mod = MIN(25, 100 - p_skill);    
    c_mod = MIN(25, c_skill);
       
    spell_caster->set_skill_extra(SS_WEP_CLUB, 
        spell_caster->query_skill_extra(SS_WEP_CLUB) - c_mod);
    spell_caster->set_skill_extra(SS_PARRY, 
        spell_caster->query_skill_extra(SS_PARRY) + p_mod);
    spell_caster->set_skill_extra(SS_DEFENCE, 
        spell_caster->query_skill_extra(SS_DEFENCE) + d_mod);  
   
    st_timer = set_alarm(180.0, 180.0, &do_check_mana());

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
       return ({ magic_resist, 1}); 
    else
       return ::query_magic_protection(prop, protectee);
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

    spell_caster->set_skill_extra(SS_WEP_CLUB, 
        spell_caster->query_skill_extra(SS_WEP_CLUB) + c_mod);
    spell_caster->set_skill_extra(SS_PARRY, 
        spell_caster->query_skill_extra(SS_PARRY) - p_mod);
    spell_caster->set_skill_extra(SS_DEFENCE, 
        spell_caster->query_skill_extra(SS_DEFENCE) - d_mod);       
    
    TO->remove_prop(OBJ_I_LIGHT);
    
    remove_spell_effect_object();
    return 1;

}


