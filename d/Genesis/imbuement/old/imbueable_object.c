/*
 *  /d/Genesis/imbuement/imbueable_object.c
 *
 *  Items that are meant to be able to be imbued or receive random 
 *  modification shadows via the imbuement_generator.c should inherit
 *  this file. Intended only for weapons and wearable objects.
 *
 *  Created November 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include "imbuement.h"
#include <macros.h>


/* Global Variables */
public int         Imbue_Check = 0;
public string      Mod1_Type = NULL_IMBUE;
public string      Mod2_Type = NULL_IMBUE;
public string      Mod3_Type = NULL_IMBUE;
public int         Mod1_Lvl = 0;
public int         Mod2_Lvl = 0;
public int         Mod3_Lvl = 0;


/* Prototypes */
nomask void        create_object();
public void        create_imbueable_object();
public void        initialize_imbuement();
public void        perform_mod();
public void        enter_env(object dest, object old);
public string      query_recover();
public void        init_recover(string str);

public void        set_mod1_type(string s) { Mod1_Type = s; }
public void        set_mod2_type(string s) { Mod2_Type = s; }
public void        set_mod3_type(string s) { Mod3_Type = s; }
public void        set_mod1_lvl(int i)     { Mod1_Lvl = i;  }
public void        set_mod2_lvl(int i)     { Mod2_Lvl = i;  }
public void        set_mod3_lvl(int i)     { Mod3_Lvl = i;  }



/*
 * Function name:        create_object 
 * Description  :        the constructor for the object
 */
nomask void
create_object()
{
    setuid();
    seteuid(getuid());

    create_imbueable_object();
} /* create_object */


/*
 * Function name:        create_imbueable_object
 * Description  :        A dummy constructor to be redifined in
 *                       inheriting code.
 */
public void
create_imbueable_object()
{
} /* create_imbueable_object */


/*
 * Function name:        initialize_imbuement
 * Description  :        At creation, we want this object, following
 *                       a brief delay, to try to roll for mods.
 */
public void
initialize_imbuement()
{
    /* If the item is already modded, we do not re-roll! */
    if (this_object()->query_prop(IMBUE_TRY))  
    {
        return;
    }

    set_alarm(1.0, 0.0, &perform_mod());
} /* initialize_imbuement */


/*
 * Function name:        perform_mod
 * Descripton   :        Check to see where this item is. If it is
 *                       in the possession of an npc, we roll for
 *                       mods.
 */
public void
perform_mod()
{
    object    loc = environment(this_object());
    int       chance = 1;

    /* Lets check this here, just to be safe. */
    /* If the item is already modded, we do not re-roll! */
    if (this_object()->query_prop(IMBUE_TRY))  
    {
        return;
    }

    if (living(loc) && !interactive(loc))
    {
        /* We'll eventually implement this, perhaps
        if (loc->query_prop(LIVE_I_IMBUE_CHANCE))
        {
            chance = loc->query_prop(LIVE_I_IMBUE_CHANCE);
        }
        */

        IMBUE_MASTER->imbue_item(this_object(), chance);
    }

    return;
} /* perform_mod */


/*
 * Function name:        enter_env
 * Description  :        when the weapon enters a new environment,
 *                       if the environment is an npc and this is the
 *                       first locaton we've entered, we try to mod
 *                       the item.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (this_object()->query_prop(IMBUE_TRY) || Imbue_Check)
    {
        return;
    }

    if (dest->query_npc())
    {
        initialize_imbuement();
    }

    /* This tells us not to try to imbue this item again from the
     * enter_env function. It might be possible to imbue it some other
     * way, still, so we do not add the IMBUE_TRY prop.
     */
    Imbue_Check = 1;
} /* enter_env */


/*
 * Function name: query_recover
 * Description  : When the object recovers, we keep track of the 
 *                imbuements and their power levels.
 */
public string
query_recover()
{
    string file = MASTER;

    return file + ":#imbue_begin#"
                + Mod1_Type + "#"
                + Mod2_Type + "#"
                + Mod3_Type + "#"
                + Mod1_Lvl  + "#"
                + Mod2_Lvl  + "#"
                + Mod3_Lvl  + "#"
                + "imbue_end#";
} /* query_recover */


/*
 * Function name: init_recover
 * Description  : This function is called when the imbued object
 *                recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_recover(string str)
{
    string  mod1_type,
            mod2_type,
            mod3_type,
            foobar;
    int     mod1_lvl,
            mod2_lvl,
            mod3_lvl;

    if (sscanf(str, "#imbue_begin#%s#%s#%s#%s#%s#%s#imbue_end#", 
               mod1_type,
               mod2_type,
               mod3_type,
               mod1_lvl,
               mod2_lvl,
               mod3_lvl,
               foobar) == 7)
    {
        TELL_G("trying to call imbuement master!");
        IMBUE_MASTER->recover_imbuements(this_object(),
                                         mod1_type,
                                         mod2_type,
                                         mod3_type,
                                         mod1_lvl,
                                         mod2_lvl,
                                         mod3_lvl);
    }
} /* init_recover */


/*
 * Function name:        query_imbuements
 * Description  :        Allow an external query as to the imbuements
 *                       this object currently possesses.
 * Returns      :        string - the information
 */
public string
query_imbuements()
{
    TELL_G("Testing tell_g!");

    return "Current Imbuements on this object:\n"
         + "----------------------------------\n"
         + "  Mod 1: " + Mod1_Type + " (lvl " + Mod1_Lvl + ")\n"
         + "  Mod 2: " + Mod2_Type + " (lvl " + Mod2_Lvl + ")\n"
         + "  Mod 3: " + Mod3_Type + " (lvl " + Mod3_Lvl + ")\n"
         + "----------------------------------\n";
} /* query_imbuements */

