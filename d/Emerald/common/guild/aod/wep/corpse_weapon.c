/*
 *  /d/Emerald/common/guild/aod/wep/corpse_weapon.c
 *
 *  Ogres can pick up corpses and use them as clubs. Wheeee!!!!
 *
 *  Created April 2007, by Cooper Sherry (Gorboth)
 *
 *  Suggested by Khonnis, Elvarg, and Guk
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/weapon";

#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>


/* Global Variables */
public string      Gender      = "";
public string      Race        = "";
public string      NonMet_Name = "";
public string      Met_Name    = "";
public int         Wep_Weight;
public int         Wep_Volume;
public int         Wep_Max_Weight;
public int         Wep_Max_Volume;
public string     *Wep_As_Killer;
public string      Wep_Living_File;
public string      State_Desc  = "corpse of ";
public string      Pstate_Desc = "corpses of ";


/* Prototypes */
public void    create_weapon();
public string  short_func();
public string  pshort_func();
public string  long_func();

public void        set_wep_nonmet(string s)          { NonMet_Name = s; }
public void        set_wep_met(string s)                { Met_Name = s; }
public void        set_wep_weight(int i)              { Wep_Weight = i; }
public void        set_wep_volume(int i)              { Wep_Volume = i; }
public void        set_wep_max_weight(int i)      { Wep_Max_Weight = i; }
public void        set_wep_max_volume(int i)      { Wep_Max_Volume = i; }
public void        set_wep_as_killer(string *s)    { Wep_As_Killer = s; }
public void        set_wep_living_file(string s) { Wep_Living_File = s; }


/*
 * Function name:        set_wep_gender
 * Description  :        assign the gender to the wep
 */
public void
set_wep_gender(string s)
{
    Gender = s;
    add_adj(s);
} /* set_wep_gender */


/*
 * Function name:        set_wep_race
 * Description  :        assign the race to the wep
 */
public void
set_wep_race(string s)
{
    Race = s;
    add_adj(s);
    add_name(s);
} /* set_wep_race */


/*
 * Function name: set_name
 * Description  : Called upon construction of this weapon to set the name
 *                of the diseased. It follows up with some additional names
 *                such as 'remains', etc.
 *                Do NOT call this routine more than once!
 *                Use add_name() for additional names.
 * Arguments    : string name - the name of the person who died.
 */
public void
set_name(string name)
{
    ::set_name("corpse");
    add_name("corpse of " + Met_Name);
    add_name("remains");
    add_name("remains of " + Met_Name);
    if (NonMet_Name)
    {
        add_name("corpse of " + NonMet_Name);
        add_name("remains of " + NonMet_Name);
    }
} /* set_name */


/*
 * Function name:        update_things
 * Description  :        set up the properties of the weapon
 */
public void
update_things()
{
    add_prop(OBJ_I_WEIGHT, Wep_Weight);
    add_prop(OBJ_I_VOLUME, Wep_Volume);
    
} /* update_things */


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    int   rnd = random(10),
          wval = 15;

    add_name( ({ "weapon", "aod_corpse_weapon", "corpse", }) );
    set_short(short_func);
    set_pshort(pshort_func);
    set_long(long_func);
 
    set_default_weapon(10 + random(5),
                       10 + random(5), W_CLUB, W_BLUDGEON, W_BOTH, 0);

    setuid();
    seteuid(getuid());
} /* create_weapon */


/*
 * Function name: short_func
 * Description  : Returns the short description of this object, based on
 *                recognition of the head.
 * Returns      : string - the short description.
 */
public string
short_func()
{
    object pob;

    pob = vbfc_caller();
    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = previous_object(-1);
    if (!pob || !query_interactive(pob))
        pob = this_player();
    if (pob && pob->query_real_name() == lower_case(Met_Name))
        return State_Desc + "yourself";
    else if (pob && pob->query_met(Met_Name))
        return State_Desc + capitalize(Met_Name);
    else
        return State_Desc + LANG_ADDART(NonMet_Name);
} /* short_func */


/*
 * Function name: pshort_func
 * Description  : Returns the plural short description of this object, based on
 *                recognition of the head.
 * Returns      : string - the plural short description.
 */
public string
pshort_func()
{
    object pob;

    pob = vbfc_caller();
    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = previous_object(-1);
    if (!pob || !query_interactive(pob))
        pob = this_player();
    if (pob && pob->query_real_name() == lower_case(Met_Name))
        return Pstate_Desc + "yourself";
    else if (pob && pob->query_met(Met_Name))
        return Pstate_Desc + capitalize(Met_Name);
    else
        return Pstate_Desc + LANG_PWORD(NonMet_Name);
} /* pshort_func */


/*
 * Function name: long_func
 * Description  : Returns the long description of this object, based on
 *                recognition of the head.
 * Returns      : string - the long description.
 */
public string
long_func()
{
    object  pob;
    string  extra = "\n";

    pob = vbfc_caller();

    if (!pob || !query_interactive(pob) || pob == this_object())
    {
        pob = this_player();
    }

    if (pob->query_guild_name_occ() == GUILD_NAME)
    {
        extra = " Looks like you've decided it would make a good"
              + " weapon. Ahh ... to be an Ogre.\n";
    }   

    if (pob->query_real_name() == lower_case(Met_Name))
    {
        return "This is your own corpse!" + extra;
    }

    if (pob->query_met(Met_Name))
    {
        return "This is the corpse of " 
             + capitalize(Met_Name) + "." + extra;
    }

    return "This is the corpse of " + NonMet_Name + "." + extra;
} /* long_func */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * We mask this function so that when the corpse weapon leaves the
 * environment of the ogre's inventory, we change it back into a normal
 * corpse. The exception is when the new environment is also in the
 * inventory of the ogre (pack, etc).
 */
public void
enter_env(object dest, object old)
{
    object  corpse;

    ::enter_env(dest, old);

    if (!IS_OGRE(dest))
    {
        corpse = clone_object("/std/corpse");
        corpse->set_name(this_object()->query_name());
        corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
        corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
        corpse->add_prop(CORPSE_S_RACE, Race);
        corpse->add_prop(CONT_I_TRANSP, 1);
        corpse->change_prop(CONT_I_MAX_WEIGHT, Wep_Max_Weight);
        corpse->change_prop(CONT_I_MAX_VOLUME, Wep_Max_Volume);
        corpse->add_prop(CORPSE_AS_KILLER, Wep_As_Killer);
        corpse->add_prop(CORPSE_S_LIVING_FILE, Wep_Living_File);
        corpse->move(dest, 1);

        remove_object();
    }
} /* enter_env */