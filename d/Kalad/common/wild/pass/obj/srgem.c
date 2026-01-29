/* by Antharanos */
/* 2017-06-03 Malus: Change multiple set_name into add_adj */
/* 2020-02-03 Arman: Added in a decay for the light benefit.
                     Added in item recovery. */

inherit "/std/object.c";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"

/* Prototypes */ 
void effect_fade(int inform); 
void fade_woo_props(int current_state); 
void write_fade_message(); 
void set_time_i_fade(int t); 
public void start_fade();

/* Global variables */  
int already_faded, time_i_fade, fade_alarm, trans_state = -1; 

#define AVG_FADE_SECONDS 25200

void
create_object()
{
   ::create_object();
   set_name("gem");
   add_adj("sparkling");
   add_adj("red");
   set_short("sparkling red gem");
   set_long("An absolutely gorgeous blood-red gem. Its many-faceted surface "+
      "seems to catch the faintest of lights and intensifies them into a "+
      "brilliance that astounds the eye.\n");
   add_prop(OBJ_I_VALUE,2000);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_LIGHT,1);
   add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
   add_prop(MAGIC_AM_ID_INFO,
       ({"This gem has absorbed some magical energy from the depths of the "+
           "underdark, making it glow like a torch.\n", 10})); 
    add_prop(OBJ_S_WIZINFO, 
        "This is a " + short() + " that provides 1 level of light for " +
        "approximately 7 hours before decaying.\n");
   set_keep(1);
}

/* 
 * Function:     write_fade_message 
 * Description:  Gives the message when the gem fades 
 *               to the holder and environment. 
 * 
 */ 
void 
write_fade_message() 
{ 
    object env; 
    string str; 
    env = environment(); 
    str = short(); 

    if (living(env)) 
    { 
        tell_object(env, "Your " +short()+ " no longer radiates light.\n"); 
        tell_room(environment(env), 
                  "The " + short() + " held by " + QTNAME(env) + 
                  " stops radiating light.\n", ({ env })); 
    } 
    else 
        tell_room(env, "The " + short() + " stops radiating light.\n", ({ })); 
} 

/* 
 * Function:     fade_woo_props 
 * Description:  changes (remove/change/add) the relevant properties 
 *               when the gem fades. 
 */ 
void 
fade_woo_props(int current_state) 
{  
    set_long("An absolutely gorgeous blood-red gem. Its many-faceted surface "+
        "seems to catch the faintest of lights and intensifies them into a "+
        "brilliance that astounds the eye.\n");
    remove_prop(OBJ_I_LIGHT); 
    remove_prop(MAGIC_AM_MAGIC);  
    remove_prop(MAGIC_AM_ID_INFO); 
    add_prop(OBJ_S_WIZINFO, 
        "This is a " + short() + " after its magic has faded.\n"); 
} 

/* 
 * Function:     effect_fade 
 * Description:  Effects the fade of the gem. 
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

    if (fade_alarm) 
    { 
        remove_alarm(fade_alarm); 
        fade_alarm = 0; 
    } 

    fade_woo_props(trans_state); 
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
 * Description:  Used to restore a new copy of the gem between 
 *               logins. 
 */ 
string 
query_recover() 
{ 
    return MASTER + ":" + query_keep_recover() +  
           "#woo_tf#" + time_i_fade + "#"; 
} 

public void
start_fade()
{ 
    int tl;

    if (!time_i_fade) 
    { 
            set_time_i_fade(AVG_FADE_SECONDS + time() + 
                            random(3600) - 1800); 
    } 

    tl = time_i_fade - time();

    if(tl > 0)   
        set_long("An absolutely gorgeous blood-red gem. Its many-faceted surface "+
            "seems to catch the faintest of lights and intensifies them into a "+
            "brilliance that astounds the eye. The light of the gem radiates " +
            "around you.\n"); 
}

/* 
 * Function:     enter_env 
 * Description:  Start the removal alarm of the gem. 
 * 
 */ 
void 
enter_env(object to, object from) 
{ 
    ::enter_env(to, from); 

    start_fade();
} 

void 
init_recover(string arg) 
{ 
    int trs, tf; 

    string str; 
    sscanf(arg, "%s#woo_tf#%d#", str, tf); 
 
    init_keep_recover(str);  
    set_time_i_fade(tf); 
} 
