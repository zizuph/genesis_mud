
/*
 * skiamorphi_obj.c
 *
 * This is the spell object for the skiamorfi (Elemental Form) spell for 
 * the Elemental Clerics of Calia and based on the standand spell object
 * maintained in the Genesis Magic System. It keeps track of the darkvision
 * and the other spell objects for this spell. This spell grants a player
 * LIVE_I_SEE_INVIS, 10 and if they are a member of the racial guild it 
 * also gives them LIVE_I_SEE_DARK, 5.
 *
 * Jaacar, February 2017
 */

#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "darkvision_obj";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "defs.h"

// Global Variables
int darkness_sight = 5;
int g_invis_amount = 10;
object s_shadow;
object s_aitheras_obj;
object s_unteristi_obj;
object s_evade_obj;
int st_timer = 0;
int revert_timer = 0;
int duration = 0;
int success_level = 0;

string *fire_tier1_adjs = ({"glowing", "gleaming", "incandescent"});
string *fire_tier2_adjs = ({"blistering", "burning", "scorching"});
string *fire_tier3_adjs = ({"blazing","raging","blazing"});

string *air_tier1_adjs = ({"gusty", "gaseous", "hazy"});
string *air_tier2_adjs = ({"crisp", "brisk", "boreal"});
string *air_tier3_adjs = ({"turbulent", "intense","tempestuous"});

string *water_tier1_adjs = ({"lymphatic", "languid", "impassive"});
string *water_tier2_adjs = ({"insipid", "fluidic", "flowing"});
string *water_tier3_adjs = ({"aqueous", "drizzling","surging"});

string *earth_tier1_adjs = ({"firm", "solid", "rough"});
string *earth_tier2_adjs = ({"rockbound", "rock-ribbed", "flinty"});
string *earth_tier3_adjs = ({"rough", "craggy","jagged"});

string *spirit_tier1_adjs = ({"indistinct", "translucent", "gossamer"});
string *spirit_tier2_adjs = ({"unearthly", "otherworldly", "ethereal"});
string *spirit_tier3_adjs = ({"immaculate", "transcendent","divine"});

string elems = "shadows";


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_skiamorfi_object_");
    set_short("skiamorfi spell object");    
    set_long("This is the standard skiamorfi spell's object. It causes "
        + "one to become their elemental form.\n");
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is the spell object for the Elemental "+
        "Clerics Elemental Form spell. Players also gain the "+
        "ability to see invisible creatures and possibly in the dark.\n");
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

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
   
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
	object target = query_effect_target();
    
    if (!objectp(target))
    {
        return;
    }
    target->catch_tell("You feel your elemental form weakening.\n");
    //revert_timer = set_alarm(30.0, 0.0, &do_revert());
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you lose control of "
            + "the elemental powers sustaining the Skiamorfi gift.\n");
    }    
}

int
do_help(string str)
{
    if (!str || str != "skiamorfi")
        return 0;
    write("You may do the following in elemental form:\n"+
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
    add_action(do_intro, "introduce");
    add_action(do_intro, "present");
    add_action(do_help,  "help");
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
	object spell_caster = query_spell_effect_caster();
    object spell_target = query_spell_effect_target();
    
	int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    
    // Set up invis vision
    int current_see_invis = spell_target->query_prop(LIVE_I_SEE_INVIS);   
    if (g_invis_amount + current_see_invis >= 100)
    {
        // don't allow someone to see to 100. That is wizard-style see invis.
        // assume that they're not at 99 already.
        g_invis_amount = max(1, 100 - current_see_invis);
    }    
    spell_target->inc_prop(LIVE_I_SEE_INVIS, g_invis_amount);     
//    spell_target->inc_prop(LIVE_I_SEE_DARK, darkness_sight);
    
    // Set up disguise shadow    
    
    string extra_desc = "";
    string elem_type = "shadowy";
    string diety = "Psuchae";
    string *tier1_adjs = spirit_tier1_adjs;
    string *tier2_adjs = spirit_tier2_adjs;
    string *tier3_adjs = spirit_tier3_adjs;
    string primary_element = GUILD_MANAGER->
    	query_primary_element(spell_caster);
    	
    switch (primary_element)
    {
    	case "fire":
        	tier1_adjs = fire_tier1_adjs;
    		tier2_adjs = fire_tier2_adjs;
    		tier3_adjs = fire_tier3_adjs;
    		elem_type = "fiery";
    		elems = "flames";
    		diety = "Lord Pyros";
        	break;
    
	    case "earth":
	        tier1_adjs = earth_tier1_adjs;
    		tier2_adjs = earth_tier2_adjs;
    		tier3_adjs = earth_tier3_adjs;
    		elem_type = "rocky";
    		elems = "rocks";
    		diety = "Lady Gu";
	        break;
	    
	    case "water":
	        tier1_adjs = water_tier1_adjs;
    		tier2_adjs = water_tier2_adjs;
    		tier3_adjs = water_tier3_adjs;
    		elem_type = "watery";
    		elems = "waters";
    		diety = "Lord Diabrecho";
	        break;
	    
	    case "air":
	        tier1_adjs = air_tier1_adjs;
    		tier2_adjs = air_tier2_adjs;
    		tier3_adjs = air_tier3_adjs;
    		elem_type = "vaporous";
    		elems = "clouds";
    		diety = "Lady Aeria";
	        break;
	        
	    case "life":
	        tier1_adjs = spirit_tier1_adjs;
    		tier2_adjs = spirit_tier2_adjs;
    		tier3_adjs = spirit_tier3_adjs;
    		elem_type = "shadowy";
    		elems = "shadows";
    		diety = "Psuchae";
	        break;
    }   
    
    set_spell_effect_desc("elemental form");

    setuid(); 
    seteuid(getuid());
    s_shadow=clone_object(ELEMENTALIST_SPELL_OBJS+"skiamorfi_shadow");
    s_shadow->shadow_me(spell_target);
    
    // By default they get the first description
    success_level = 1;
    spell_target->set_disguise(({tier1_adjs[random(sizeof(tier1_adjs))],
        elem_type}));
    
    // If they have completed their Guru quest, they get the second
    // description 
    if (spell_target->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
        success_level = 2;        
        extra_desc = "";
        spell_target->set_disguise(({tier2_adjs[random(sizeof(tier2_adjs))],
                                     elem_type}));        
    }
    
    // If they are full master clerics, they get the third
    // description
    if (GUILD_MANAGER->query_is_full_master(spell_target))
    {
        success_level = 3;        
        spell_target->set_disguise(({tier3_adjs[random(sizeof(tier3_adjs))],
                                     elem_type}));           
        extra_desc = "";
    }
    
    object mandala = present("_elemental_guild_mandala", spell_target);
    write("You touch your " + mandala->short() + " to your chest.\n"+
        "You feel the power of " + diety + " coursing through your "+
        "very soul.\n");
    tell_room(environment(spell_target), QCTNAME(spell_target) +
        " touches something to "+spell_target->query_possessive()+
        " chest.\n",({spell_target}));
    
    if (spell_target->is_elemental_racial_cleric())
    {
        write("Every vein in your body begins to pulse with "+
            mandala->query_color2()+" energy. "+
            capitalize(mandala->query_color1() +
            " "+ elems + " flow outward from your mandala, covering your "+
            "entire body.\nYou are now in elemental form. " + extra_desc +
            "\n"));
        tell_room(environment(spell_target),"Every vein in " +
            QPNAME(spell_target)+" body begins to pulse with "+
            mandala->query_color2()+" energy. "+
            capitalize(mandala->query_color1())+
            " " + elems + " flow outward from the centre of "+
            spell_target->query_possessive()+" chest, covering "+
            spell_target->query_possessive()+" entire body.\n",
            ({spell_target}));
    }
    else
    {
        write(capitalize(elems)+" explode all around you, encompassing you "+
            "from head to toe and the surrounding area where you stand.\n"+
            "As you step out of the "+elems+", they disappear from sight.\n"+
            "You are now in elemental form. " + extra_desc +"\n");
        tell_room(environment(spell_target),capitalize(elems)+
            " explode all around "+
            QNAME(spell_target)+", encompassing "+
            spell_target->query_objective()+
            " from head to toe and the surrounding area where "+
            spell_target->query_pronoun()+
            " stands. As "+QNAME(spell_target)+" steps out of the "+
            elems+", they disappear from sight.\n",({spell_target}));
    }
         
    spell_target->set_skiamorfi_level(success_level);       

//    duration = 3600;
    
    // Racial guild members get the duration doubled
//    if (spell_target->is_elemental_racial_cleric())
//        duration += duration;
//    st_timer = set_alarm(itof(duration), 0.0, 
//    	&hook_spell_effect_warn_fading());
    	
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
	object spell_caster = query_spell_effect_caster();
    object spell_target = query_spell_effect_target();
    
	int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    // Remove invis vision 
    if (spell_target)
    	spell_target->dec_prop(LIVE_I_SEE_INVIS, g_invis_amount);

    
    // Remove disguise shadow
    if (spell_target)
    {
	    spell_target->catch_msg("You revert back to normal form.\n");
	    tell_room(environment(spell_target), "The "+elems+" surrounding " + 
	              QTNAME(spell_target) + " slip away.\n", ({spell_caster})); 
	    spell_target->remove_disguise_shadow();
	    remove_alarm(st_timer);
	    tell_room(environment(spell_target),"When you look upon "+
	              spell_target->query_objective()+" again, "+
	              spell_target->query_pronoun()+" stands in the shape of a "+
	              spell_target->query_nonmet_name()+".\n",({spell_target}));
	}
	
    remove_spell_effect_object();
    return 1;
}
