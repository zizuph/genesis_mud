#pragma strict_types
#pragma save_binary

#include "../../morgulmage.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <language.h>
#include <living_desc.h>
#include <composite.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "shadow_base_sh";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"

#define NOHIDE_FUNCTIONS ({ "target_fartell_spell", "last" })

int is_moving;
int in_notmet;

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    shadow_who->steed_is_updated();
}

public void
remove_nifarist_shadow()
{
    m_spell_object->dispel_effect(shadow_who);
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Withdrawing into the remote depths of"
          + " your robe, you feel your identity fading into the"
          + " impenetrable aspects of a wraith of Mordor.\n");
        tell_room(environment(target), QCTNAME(target) + " withdraws"
          + " into the remote depths of " 
          + target->query_possessive() + " robe, fading from"
          + " any recognizable form into that of a wraith.\n", 
            ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("As your countenance emerges from its"
          + " impenetrable barrier of protection, you sense that you"
          + " are again recognizable to the world of mortals.\n");
        tell_room(environment(target), QCTNAME(target) + " emerges"
          + " from the fathomless shadows of "
          + target->query_possessive() + " wraith-like form, and"
          + " is suddenly recognizable.\n", ({ target }));
    }
}


/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the shadows that hold your"
          + " guise as that of a wraith begin to weaken.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Your mind lapses, and the shadows which"
          + " shield you from view disperse!\n");
    }    
}

public int is_bypass_function()
{
    int idx = 0;
    string function_name;
    for (; function_name = calling_function(idx); idx--)
    {
        if (member_array(function_name, NOHIDE_FUNCTIONS) != -1)
            return 1;
    }
    return 0;
}

/*
 * Function name:   notmet_me
 * Description:     Finds out if obj is considered to have met me. Players
 *                  must have been introduced to me. All others don't have to
 *                  be introduced to know me.
 * Arguments:       obj: Object in question, has it met me?
 * Returns:         True if object has not met me.
 */
public int
notmet_me(object obj)
{
    string * known_prop;
    string name = shadow_who->query_real_name();

    if (!objectp(obj))
        return 1;
    if (!interactive(obj))
    {
        return 1;
    }
    
    if (obj->query_real_name() == name)
    {
        // We always know ourself.
        return 0;
    }

    if (obj->query_wiz_level())
        return 0;
    
    
    in_notmet = 1;

    int shadow_value = shadow_who->notmet_me(obj);

    in_notmet = 0;

    int my_level = shadow_who->query_morgul_level();
    int their_level = obj->query_morgul_level();

    if (their_level > my_level) 
    {
        return shadow_value;
    }

    if (environment(obj) != environment(shadow_who))
    {
        return shadow_value;
    }

    int visibility = shadow_who->query_mage_option(OPTION_NIFARIST);

    if (IS_MEMBER(obj)) 
    {
        if (IS_APPRENTICE(obj)) return visibility & NIFARIST_APPRENTICES ? 0 : 1;
        return visibility & NIFARIST_FULL_MAGES ? shadow_value : 1;
    }

    if (member_array(obj, shadow_who->query_team_others()) != -1) {
        return visibility & NIFARIST_TEAM ? shadow_value : 1;
    }

    return 1;
}

public object
find_previous_living()
{
    string func = 0;
    int count = 0;
    while(stringp(func = calling_function(count))) {
        if (func == "catch_vbfc") {
            return previous_object(-1);
        }

        count--;
    }

    if (living(previous_object(-1))) return previous_object(-1);
    if (living(previous_object())) return previous_object();

    int current = -2;
    object previous = 0;
    object last_living = 0;
    while(objectp(previous = previous_object(current))) {
        current--;
        if (living(previous)) last_living = previous;
    }

    return objectp(last_living) ? last_living : this_player();
}

public string
query_pronoun()
{    
    object pobj = find_previous_living();

    if (objectp(pobj) && notmet_me(pobj) )
        return "it";
        
    return (shadow_who->query_pronoun());
}

public string 
query_objective()
{
    object pobj = find_previous_living();

    if (objectp(pobj) && notmet_me(pobj) )
        return "it";

    return (shadow_who->query_objective());
}

public string
query_possessive()
{
    object pobj = find_previous_living();

    if (notmet_me(pobj))
        return "its";

    return (shadow_who->query_possessive());
}

/*
 * Function name: query_nonmet_name
 * Description  : Returns our description, it changes depending on our
 *              : state.
 * Returns      : a string
 */
string 
query_nonmet_name(object pobj)
{
    if (!objectp(pobj)) pobj = find_previous_living();
    
    if (notmet_me(pobj))
        return "black-robed hooded wraith";

    return (shadow_who->query_nonmet_name());
}

public varargs string
short(object for_obj)
{
    if (!objectp(for_obj))
        for_obj = find_previous_living();

    if (objectp(for_obj) && notmet_me(for_obj) )
        return query_nonmet_name(for_obj);

    return query_shadow_who()->short(for_obj);
}


/*
 * Function name: query_race_name
 * Description  : Fake our race name
 * Returns      : a string
 */
string 
query_race_name()
{
    if(calling_function() == "query_presentation") return query_shadow_who()->query_race_name();
    return "wraith";
}

varargs public mixed 
show_cont_subloc(string sloc, object for_obj)
{
    if (query_shadow_who()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) 
    {
        return query_shadow_who()->show_cont_subloc(sloc, for_obj);
    }

    if ((for_obj != query_shadow_who()) && notmet_me(for_obj)) {
        mixed *allowed_sublocs = ({ "_stoneskin_subloc" });
        if (member_array(sloc, allowed_sublocs) == -1) return "";
    }

    return shadow_who->show_cont_subloc(sloc, for_obj);
}

private string 
remove_str(string needle, string haystack) 
{
    if (!stringp(haystack)) return "";
    if (!stringp(needle)) return haystack;

    return implode(explode(haystack, needle), "");
}

string 
describe_hands(object ob, object for_ob) 
{
    if (!objectp(ob)) return "hands";
    string s = for_ob->check_call(ob->short());    
    return remove_str("pair of ", s);
}

string
describe_item(object ob, object for_obj) 
{
    return LANG_ADDART(for_obj->check_call(ob->short()));
}

string long(object for_obj)
{
    if (!objectp(for_obj)) for_obj = find_previous_living();
    
    if ((for_obj == query_shadow_who()) || !notmet_me(for_obj)) {
        return query_shadow_who()->long(for_obj);
    }

    string description = "Before you is a dark figure, bent slightly beneath "
        + "its long and tattered black cloak. Whatever features of this "
        + "being would be revealed in its face are lost beneath the shadows "
        + "of its deep hood, "
        + (query_shadow_who()->query_nazgul() == 2 ? "except for a large "
            + "crown of steel." : "which seems empty and haunted.");

    object *items = query_shadow_who()->query_weapon(-1) +
        filter(query_shadow_who()->query_armour(-1),
            &operator(==)(A_SHIELD) @ &->query_at());

    object hands = query_shadow_who()->query_armour(A_HANDS);
    string hand_description = describe_hands(hands, for_obj);

    string *item_descriptions = map(items, &describe_item(, for_obj));
    if (sizeof(item_descriptions)) {
        description += " Gripped in its " + hand_description 
            + (sizeof(item_descriptions) > 1 ? " are " : " is ")
            + COMPOSITE_WORDS(item_descriptions) + ".";
    }

    return description + "\n" + query_shadow_who()->show_sublocs(for_obj);
}

string query_art_name(object pobj)
{
    string pre, aft;

    if (!objectp(pobj)) pobj = find_previous_living();

    pre = ""; aft = "";

    if (!CAN_SEE(pobj, shadow_who) || 
        !CAN_SEE_IN_ROOM(pobj))
        return LD_SOMEONE;

    if (shadow_who->query_prop(OBJ_I_INVIS) > 0)
    {
        pre = "(";
        aft = ")";
    }
    else if (shadow_who->query_prop(OBJ_I_HIDE) > 0)
    {
        pre = "[";
        aft = "]";
    }
    if (notmet_me(pobj))
        return pre +  LANG_ADDART(query_nonmet_name(pobj)) + aft;

    return (shadow_who->query_art_name(pobj));
}

string query_Art_name(object pobj)
{
    if (!objectp(pobj))
    {
         pobj = find_previous_living();
    }
    string desc = query_art_name(pobj);

    /* Capitalize the right character if the description starts with ( or [. */
    if (wildmatch("[\\[(]*", desc))
        return desc[..0] + capitalize(desc[1..]);

    return capitalize(desc);
}

string query_art_possessive_name(object pobj)
{
    if(!objectp(pobj)) pobj = find_previous_living();
    if(pobj->query_met(query_shadow_who()->query_real_name()))
        return query_shadow_who()->query_name() + "'s";

    return LANG_ADDART(query_nonmet_name(pobj)) + "'s";

}

string query_Art_possessive_name(object pobj)
{
    return capitalize(query_art_possessive_name(pobj));
}

string query_the_name(object pobj)
{
    string pre = "", aft = "";

    if (!objectp(pobj)) pobj = find_previous_living();

    if (!CAN_SEE(pobj, shadow_who) || 
        !CAN_SEE_IN_ROOM(pobj))
        return LD_SOMEONE;

    if (shadow_who->query_prop(OBJ_I_HIDE) > 0)
    {
        pre = "[";
        aft = "]";
    }

    if (shadow_who->query_prop(OBJ_I_INVIS) > 0)
    {
        pre = "(";
        aft = ")";
    }

    if (objectp(pobj) && notmet_me(pobj))
        return pre + LD_THE + " " + query_nonmet_name(pobj) + aft;

    return shadow_who->query_the_name(pobj);
}

string query_The_name(object pobj)
{
    if (!objectp(pobj))
    {
         pobj = find_previous_living();
    }
    string desc = query_the_name(pobj);

    if (wildmatch("[\\[(]*", desc))
        return desc[..0] + capitalize(desc[1..]);

    return capitalize(desc);
}

string query_the_possessive_name(object pobj)
{
    if (!objectp(pobj))
    {
         pobj = find_previous_living();
    }

    if (notmet_me(pobj))
        return LANG_POSS(query_the_name(pobj));
     
    return LANG_POSS(shadow_who->query_the_name(pobj));
}

string query_The_possessive_name(object pobj) 
{ 
    if (!objectp(pobj))
    {
         pobj = find_previous_living();
    }

    if (notmet_me(pobj))
        return LANG_POSS(query_The_name(pobj));
     
    return LANG_POSS(shadow_who->query_The_name(pobj));
}


string *parse_command_adjectiv_id_list()
{
    string* list = ({ "black-robed", "hooded" });
    if (shadow_who->query_gender() == 1)
    {
        list += ({ "female" });
    }
    else
    {
        list += ({ "male" });
    }
    if (shadow_who->query_mm_mounted())
    {
    list += ({ "black" });
    }
    return list;
}

string *parse_command_id_list()
{
    object pobj = find_previous_living();

    if (!notmet_me(pobj))
        return (shadow_who->parse_command_id_list());

    string *ids = shadow_who->parse_command_id_list();
    ids -= ({ shadow_who->query_race_name(), 
        shadow_who->query_real_name() });
    ids += ({ "wraith" });
    if (shadow_who->query_mm_mounted())
    {
        ids += ({ "rider" });
    }
    return ids;
}  

string *parse_command_plural_id_list()
{
    object pobj = find_previous_living();

    if (!notmet_me(pobj))
        return (shadow_who->parse_command_id_list());

    string *ids = shadow_who->parse_command_id_list();
    ids -= ({ LANG_PWORD(shadow_who->query_race_name()), 
        LANG_PWORD(shadow_who->query_real_name()),
        shadow_who->query_race_name(),
        shadow_who->query_real_name() });
    ids += ({ "wraiths" });
    return ids;
}

int has_nifarist_shadow()
{
    return 1;
}

public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);

    if (prop != LIVE_I_NEVERKNOWN)
    {
        return result;
    }
    if (in_notmet)
    {
        return result;
    }
    if (is_bypass_function())
    {
        return result;
    }
    if (notmet_me(find_previous_living()))
    {
        return 1;
    }
    return result;
}