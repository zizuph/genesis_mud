
/* 
    ~Calia[/something]/palace/weapons/weapon_of_opposites.c 

    This is an generalisation of the "sword of light/darkness" 
    to allow different types of weapon that have "opposites", 
    and for which the magical effects can run out ("fading"), 
    a more recent feature. By default it should be just like 
    a sword of light was before this generalisation. 
    Generalised by Maniac, 6/1/2000. 

    coder(s):   Glykron and Maniac 
    history: 
                weapon of opposites 
                25/8/02     updates weapon value on fading    Maniac
                15/7/02     fixed "unwielded" adjective bug   Maniac
                6/1/2000    generalised - weapon of opposites Maniac

                sword of light 
                23/2/99     light fades, and makes new weapon Maniac 
                 6/6/96     made keepable                     Maniac 
                 6/4/96     properties added                  Maniac 
                18/8/95     made wieldable in any hand        Maniac 
                24. 2.93    recovery added                    Glykron 
                 9. 2.93    header added                      Glykron 
*/ 

#pragma save_binary 
#pragma strict_types 

inherit "/std/weapon"; 
inherit "/lib/keep"; 

#include <const.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

/* Prototypes */ 
void effect_fade(int inform); 
void set_fade_text(string ftext); 
string query_fade_text(); 
void effect_transformation(mixed qualifier); 
void set_transformation_text(string ttext); 
void config_transformation(int new_state); 
void config_transformation_desc(int new_state); 
void config_transformation_stats(int new_state); 
void config_transformation_props(int new_state); 
string query_transformation_text(); 
void fade_woo_desc(int current_state); 
void fade_woo_stats(int current_state); 
void fade_woo_props(int current_state); 
void write_fade_message(); 
void write_transformation_message(); 
void set_woo_name(string wname); 
void set_plural_woo_name(string pwname); 
void set_time_i_fade(int t); 
void set_transformation_state(int new_state, int inform, int timer); 

/* Global variables */ 
string fade_text, trans_text, woo_name, plural_woo_name; 
int already_faded, time_i_fade, fade_alarm, trans_state = -1; 

#define WOO_STATE_LIGHT 1 
#define WOO_STATE_DARK 0 
#define AVG_FADE_SECONDS 25200 


void 
create_weapon() 
{ 
    set_woo_name("sword"); 
    set_plural_woo_name("swords"); 
    set_transformation_state(WOO_STATE_LIGHT, 0, 0); 
} 


/* 
 * Function:     set_woo_name 
 * Description:  Sets the name of the weapon, e.g. scimitar, sabre, 
 *               partisan, halbert or whatever. This allows the name 
 *               to be randomised to several possible weapons in one 
 *               file. 
 * 
 */ 
void 
set_woo_name(string wname) 
{ 
    woo_name = wname; 
} 


void 
set_plural_woo_name(string pwname) 
{ 
    plural_woo_name = pwname; 
} 


/* 
 * Function:     query_woo_name 
 * Description:  Returns the name of the weapon, e.g. scimitar, sabre, 
 *               partisan, halbert or whatever, that was set using 
 *               set_woo_name. 
 * 
 */ 
string
query_woo_name() 
{
    return woo_name; 
}


string 
query_plural_woo_name() 
{ 
    return plural_woo_name; 
} 


/* 
 * Function:     is_calia_weapon_of_opposites 
 * Description:  Returns 1. 
 * 
 */ 
nomask int 
is_calia_weapon_of_opposites() 
{ 
    return 1; 
} 


/* 
 * Function:     query_transformation_state 
 * Description:  Returns the current transformation state of 
 *               this weapon. 
 */ 
int 
query_transformation_state() 
{ 
    return trans_state; 
} 


/* 
 * Function:    set_transformation_text 
 * Description: Sets the text for when the weapon transforms, 
 *              e.g. " suddenly fades and then starts emitting 
 *              darkness!\n". Remember to include a final newline 
 *              and initial space! 
 */ 
void 
set_transformation_text(string ttext) 
{ 
    trans_text = ttext; 
} 


/* 
 * Function:     query_fade_text 
 * Description:  Returns the text for when the weapon fades. 
 * 
 */ 
string 
query_transformation_text() 
{ 
    return trans_text; 
} 


/* 
 * Function:     write_fade_message 
 * Description:  Gives the message when the weapon fades 
 *               to the wielder and environment. 
 * 
 */ 
void 
write_transformation_message() 
{ 
    object env; 
    string str; 

    env = environment(); 
    str = short(); 
    if (living(env)) { 
        tell_object(env, "Your " + str + trans_text); 
        tell_room(environment(env), 
                  "The " + str + " held by " + QTNAME(env) + 
                  trans_text, ({ env })); 
    } 
    else 
        tell_room(env, "The " + str + trans_text, ({ })); 
} 


/* 
 * Function:     config_transformation_desc 
 * Description:  Makes the appropriate changes to the weapon 
 *               desc when a transformation occurs. 
 */ 
void 
config_transformation_desc(int new_state) 
{ 
    if (new_state == WOO_STATE_DARK) { 
        remove_name(query_names() - ({"weapon", OB_NAME(this_object()) }) ); 
        remove_adj(((string *) query_adj(-1)) - ({ "unwielded" })); 
        set_name(query_woo_name() + " of darkness"); 
        add_name(({ query_woo_name(), "_calia_weapon_of_darkness" })); 
        set_adj("dark"); 
        set_short(query_woo_name() + " of darkness"); 
        set_pshort(query_plural_woo_name() + " of darkness"); 
        set_long("This " + query_woo_name() + " exudes darkness.\n"); 
        set_fade_text(" flickers and stops exuding darkness.\n"); 
        set_transformation_text(" suddenly starts emitting " + 
            "brilliant white light!\n"); 
    } 
    else if (new_state == WOO_STATE_LIGHT) { 
        remove_name(query_names() - ({"weapon", OB_NAME(this_object()) }) ); 
        remove_adj(((string *) query_adj(-1)) - ({ "unwielded" })); 
        set_name(query_woo_name() + " of light"); 
        add_name(({ query_woo_name(), "_calia_weapon_of_light" })); 
        set_adj("light"); 
        set_short(query_woo_name() + " of light"); 
        set_pshort(query_plural_woo_name() + " of light"); 
        set_long("This " + query_woo_name() + " glows with a brilliant " + 
                 "white aura.\n"); 
        set_fade_text(" flickers and its aura of light fades.\n"); 
        set_transformation_text(" suddenly fades and then starts " + 
            "emitting darkness.\n"); 
    } 
} 


/* 
 * Function:     config_transformation_stats 
 * Description:  Makes the appropriate changes to the weapon 
 *               stats when a transformation occurs. 
 */ 
void 
config_transformation_stats(int new_state) 
{ 
    if (new_state == WOO_STATE_DARK || 
        new_state == WOO_STATE_LIGHT) { 
        set_hit(40); 
        set_pen(40); 
        set_hands(W_ANYH); 
        set_wt(W_SWORD); 
        set_dt(W_IMPALE | W_SLASH); 
    } 
} 


/* 
 * Function:     config_transformation_props 
 * Description:  Makes the appropriate changes to the weapon 
 *               properties when a transformation occurs. 
 */ 
void 
config_transformation_props(int new_state) 
{ 
    if (new_state == WOO_STATE_DARK) { 
        add_prop(OBJ_I_LIGHT, DARKNESS_TEMPORARY); 
        add_prop(OBJ_I_WEIGHT, 10000); 
        add_prop(OBJ_I_VOLUME, 5000); 
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen())); 
        add_prop(OBJ_M_NO_BUY, 1); 
        add_prop(MAGIC_AM_MAGIC, ({ 20, "enchanted" }) ); 
        add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); 
        add_prop(MAGIC_AM_ID_INFO, 
                 ({"A quite powerfully enchanted weapon, " + 
                   "the darkness it exudes appears to be not of this " + 
                   "world, being unusually deep and carrying a " + 
                   "damaging charge.\n", 10})); 
        add_prop(OBJ_S_WIZINFO, 
                   "This object is magical, and is obtainable " + 
                   "by killing the kroug commander in the " + 
                   "foothills of Mount Kyrus, Calia.\n"); 
    } 
    else if (new_state == WOO_STATE_LIGHT) { 
        add_prop(OBJ_I_WEIGHT, 10000); 
        add_prop(OBJ_I_VOLUME, 5000); 
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen())); 
        add_prop(OBJ_M_NO_BUY, 1); 
        add_prop(OBJ_I_LIGHT, 1); 
        add_prop(MAGIC_AM_MAGIC, ({ 20, "enchanted" }) ); 
        add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); 
        add_prop(MAGIC_AM_ID_INFO, 
                 ({"A quite powerfully enchanted weapon, " + 
                   "the light it exudes appears to be not of this " + 
                   "world, being unusually bright and carrying a " + 
                   "damaging charge.\n", 10})); 
        add_prop(OBJ_S_WIZINFO, 
                   "This weapon is magical, and is obtainable " + 
                   "either by killing the white warrior in the " + 
                   "Crystalline Palace of Calia or by walking " + 
                   "into the bright palace room with a " + 
                   "corresponding weapon of darkness " + 
                   "(which may be obtained by killing " + 
                   "the kroug commander on the foothills).\n"); 
    } 
} 


/* 
 * Function:      config_transformation 
 * Description:   Makes the appropriate changes to the weapon 
 *                description, stats and props when a 
 *                transformation occurs. 
 */ 
void 
config_transformation(int new_state) 
{ 
    config_transformation_desc(new_state); 
    config_transformation_stats(new_state); 
    config_transformation_props(new_state); 
} 


/* 
 * Function:     set_transformation_state 
 * Description:  Set the state of the weapon regarding its 
 *               transformation. 
 * Arguments:    int new_state - the state to transform to 
 *               int inform - 1 if trans message should be written, 
 *                            0 otherwise. 
 *               int timer  - 1 if fade timer should be started
 *                            0 otherwise. 
 * Note:         By convention, the state 1 is reserved for 
 *               "light", 0 for "darkness". 
 */ 
void 
set_transformation_state(int new_state, int inform, int timer) 
{ 
    object w; 

    if (trans_state == new_state) 
        return; 

    if (inform) 
        write_transformation_message(); 

    config_transformation(new_state); 
    trans_state = new_state; 

    if (timer) { 
        if (time_i_fade != 0) 
            set_time_i_fade(time_i_fade + random(3600)); 
        else 
            set_time_i_fade(AVG_FADE_SECONDS + time() + 
                            random(3600) - 1800); 
    } 

    if (objectp(w = query_wielded()) && (w == environment())) 
        w->update_weapon(this_object()); 
} 


/* 
 * Function:     effect_transformation 
 * Description:  Effects the transformation to the opposite 
 *               weapon, when qualified by the supplied 
 *               information. By default this works only if 
 *               the qualifier is an integer, using that 
 *               as the target transformation state. A weapon 
 *               can only transform if it hasn't faded yet. 
 * Note:         By convention, the state 1 is reserved for 
 *               "light", 0 for "darkness". 
 */ 
int 
effect_transformation(mixed qualifier) 
{ 
    if (!already_faded && intp(qualifier)) 
        set_transformation_state(qualifier, 1, 1); 
} 


/* 
 * Function:    set_fade_text 
 * Description: Sets the text for when the weapon fades, 
 *              e.g. " flickers and its aura of light fades\n". 
 *              Remember to include a final newline and initial 
 *              space! 
 */ 
void 
set_fade_text(string ftext)
{
    fade_text = ftext; 
}


/* 
 * Function:     query_fade_text 
 * Description:  Returns the text for when the weapon fades. 
 * 
 */ 
string 
query_fade_text() 
{ 
    return fade_text; 
} 


/* 
 * Function:     write_fade_message 
 * Description:  Gives the message when the weapon fades 
 *               to the wielder and environment. 
 * 
 */ 
void 
write_fade_message() 
{ 
    object env; 
    string str; 

    env = environment(); 
    str = short(); 
    if (living(env)) { 
        tell_object(env, "Your " + str + fade_text); 
        tell_room(environment(env), 
                  "The " + str + " held by " + QTNAME(env) + 
                  fade_text, ({ env })); 
    } 
    else 
        tell_room(env, "The " + str + fade_text, ({ })); 
} 


/* 
 * Function:  fade_woo_desc 
 * Description:  fades the relevant descs when the weapon fades. 
 */ 
void 
fade_woo_desc(int current_state) 
{ 
    if (current_state == WOO_STATE_LIGHT) { 
        remove_name(query_names() - ({"weapon", OB_NAME(this_object()) }) ); 
        remove_adj(((string *) query_adj(-1)) - ({ "unwielded" })); 
        set_name(query_woo_name()); 
        set_pname(query_plural_woo_name()); 
        set_adj(({"gleaming", "white"})); 
        set_short("gleaming white " + query_woo_name()); 
        set_pshort("gleaming white " + query_plural_woo_name()); 
        set_long("This " + query_woo_name() + " has a white blade " + 
            "that gleams brightly in the slightest flicker of light.\n"); 
    } 
    else if (current_state == WOO_STATE_DARK) { 
        remove_name(query_names() - ({"weapon", OB_NAME(this_object()) }) ); 
        remove_adj(((string *) query_adj(-1)) - ({ "unwielded" })); 
        set_name(query_woo_name()); 
        set_pname(query_plural_woo_name()); 
        set_adj(({"dull", "black"})); 
        set_short("dull black " + query_woo_name()); 
        set_pshort("dull black " + query_plural_woo_name()); 
        set_long("This " + query_woo_name() + 
            " has a black blade that reflects no light.\n"); 
    } 
} 


/* 
 * Function:     fade_woo_stats 
 * Description:  fades the relevant stats when the weapon fades. 
 * 
 */ 
void 
fade_woo_stats(int current_state) 
{ 
    set_hit(34); 
    set_pen(34); 
} 


/* 
 * Function:     fade_woo_props 
 * Description:  changes (remove/change/add) the relevant properties 
 *               when the weapon fades. 
 */ 
void 
fade_woo_props(int current_state) 
{ 
    if (current_state == WOO_STATE_LIGHT) { 
        remove_prop(OBJ_I_LIGHT); 
        remove_prop(MAGIC_AM_MAGIC); 
        remove_prop(OBJ_I_IS_MAGIC_WEAPON); 
        remove_prop(MAGIC_AM_ID_INFO); 
        add_prop(OBJ_S_WIZINFO, 
             "This is a " + query_woo_name() + " of light " + 
             "after its magic has faded.\n"); 
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen())); 
    } 
    else if (current_state == WOO_STATE_DARK) { 
        remove_prop(OBJ_I_LIGHT); 
        remove_prop(MAGIC_AM_MAGIC); 
        remove_prop(OBJ_I_IS_MAGIC_WEAPON); 
        remove_prop(MAGIC_AM_ID_INFO); 
        add_prop(OBJ_S_WIZINFO, 
             "This is a " + query_woo_name() + " of darkness " + 
             "after its magic has faded.\n"); 
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen())); 
    } 
} 


/* 
 * Function:     effect_fade 
 * Description:  Effects the fade of a weapon from one kind to 
 *               another (usually magical to non-magical). 
 */ 
void 
effect_fade(int inform) 
{ 
    object w; 

    if (already_faded) 
        return; 

    if (inform) 
        write_fade_message(); 

    already_faded = 1; 

    if (fade_alarm) { 
        remove_alarm(fade_alarm); 
        fade_alarm = 0; 
    } 

    fade_woo_stats(trans_state); 
    fade_woo_desc(trans_state); 
    fade_woo_props(trans_state); 

    if (objectp(w = query_wielded()) && (w == environment())) 
        w->update_weapon(this_object()); 
} 


/* 
 * Function:     set_time_i_fade 
 * Description:  Set the time that the weapon should fade 
 *               which uses the same convention as the standard 
 *               time() function. This sets the necessary 
 *               alarm to carry out the fade. 
 * 
 */ 
void 
set_time_i_fade(int t) 
{ 
    int tl; 

    if (already_faded) 
        return; 

    if (fade_alarm) 
        remove_alarm(fade_alarm); 

    tl = (time_i_fade = t) - time(); 

    if (tl < 0) 
        effect_fade(0); 
    else if (tl == 0) 
        fade_alarm = set_alarm(0.0, 0.0, &effect_fade(1)); 
    else 
        fade_alarm = set_alarm(itof(tl), 0.0, &effect_fade(1)); 
} 


/* 
 * Function:     query_time_i_fade 
 * Description:  The time when this weapon should fade, which 
 *               uses the same convention of the time() function. 
 */ 
int 
query_time_i_fade() 
{ 
    return time_i_fade; 
} 


/* 
 * Function:     query_recover 
 * Description:  Used to restore a new copy of the weapon between 
 *               logins, includes the path of the master object 
 *               and the relevant state variables. 
 */ 
string 
query_recover() 
{ 
    return MASTER + ":" + query_wep_recover() + query_keep_recover() + 
           "#woo_sn#" + query_woo_name() + 
           "#woo_pn#" + query_plural_woo_name() + 
           "#woo_oa#" + query_prop(OBJ_S_ORIGIN_ALIGNMENT) + 
           "#woo_ts#" + trans_state + 
           "#woo_tf#" + time_i_fade + "#"; 
} 


/* 
 * Function:     enter_env 
 * Description:  Start the darkness removal alarm if the 
 *               sword is not in the inventory of a kroug. 
 * 
 */ 
void 
enter_env(object to, object from) 
{ 
    ::enter_env(to, from); 

    if (!already_faded && objectp(from) && 
        objectp(to) && !fade_alarm) { 
            set_time_i_fade(AVG_FADE_SECONDS + time() + 
                            random(3600) - 1800); 
    } 
} 


void 
init_recover(string arg) 
{ 
    int trs, tf; 
    string str, origin_alignment; 

    sscanf(arg, "%s#woo_sn#%s#", str, woo_name); 
    sscanf(arg, "%s#woo_pn#%s#", str, plural_woo_name); 
    sscanf(arg, "%s#woo_oa#%s#", str, origin_alignment); 
    sscanf(arg, "%s#woo_ts#%d#", str, trs); 
    sscanf(arg, "%s#woo_tf#%d#", str, tf); 

    init_wep_recover(str); 
    init_keep_recover(str); 
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, origin_alignment); 

    set_transformation_state(trs, 0, 1); 
    set_time_i_fade(tf); 
} 
