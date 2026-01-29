/* The Grunts collar. This is the symbol of the Grunts guild, and is   */
/* proudly worn by many Goblins.                                       */
/* Originally coded 31/3/1993, by Tulix I.                             */
/* Based on the nose-ring made by Quis.                                */
/* Totally recoded 10/08/95 by Tulix III.                              */
/* Notches (kills) are now counted in public, function added 05/11/95. */
/* Recoded 28/12/95 to improve fault-tolerance and add pragmas.        */
/* Spike description added 25/09/98.                                   */
/* Spike description improved 03/10/98 (well, nobody is perfect)       */
/* Recruitment logging added 28/01/2000 by Tulix V.                    */

inherit "/std/armour";

/* These two lines are put in to keep Mercade happy */
#pragma strict_types
#pragma save_binary  

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>

#include "../guild.h"

/* Define the default warcry given to the grunts */
#define DEFAULT_WARCRY   "GrUntz rOol!!!"

/* Global variables to be saved */
public string *recruits; /* A list of all Grunts recruited by this Grunt */
public string *heritage; /* The order in which grunts were recruited */
public string warcry;    /* Warcry to shout at your enemies */

/* Prototype functions */
public int change_warcry(string str);
public string do_show_notches();
public string notch_desc();
public void reset_armour();
public string spike_desc();

/*
 * Function name:   create_armour
 * Description:     define all the basics of the object
 */
public void
create_armour()
{
    
    set_name("collar");
    add_name("grunts_collar");
    set_adj("spiked");
    add_adj("leather");
    
    set_short("leather collar with " + "@@spike_desc");
    set_long("The collar is the symbol of the Grunts guild. "
         + "It has written on it:\n'For more information about the Grunts "
         + "guild try <help grunts>'.\n"
         + "The collar fits nicely around your neck."
         + "@@notch_desc");  /* This vbfc puts notches in the long desc */
    
    add_item("notches", "@@do_show_notches");  /* Add notches as an item */
    add_item("spikes", "The spikes are made from a material that "
         + "reflects the number of notches on \nyour collar. You have "
         + "now earned " + "@@spike_desc@@" + ".\n");

    set_ac(0);            /* Not much use as armour, to be honest */
    set_at(A_NECK);       /* This collar is worn around the neck  */
    
    setuid();
    seteuid(getuid());    /* Needed for cmdsoul manipulation      */
    
    add_prop(OBJ_I_WEIGHT, 100);  /* Weight 100g */
    add_prop(OBJ_I_VOLUME, 50);   /* Volume 50ml */
    add_prop(OBJ_I_VALUE, 0);     /* Genuinely priceless */
    add_prop(OBJ_M_NO_DROP, "You cannot bear to part with your collar.\n");
}

/*
 * Function name:   init
 * Description:     add commands to owner, add Grunts soul and custom warcry
 */
public void
init()
{
    ::init();
    add_action(change_warcry, "change");       /* Customise players warcry */
    
    if ( this_player() == environment(this_object()) )
    {    
        /* Check to see if this grunt has any previous convictions */
        if (file_size(GRUNTS_WARCRY_DIR+this_player()->query_real_name()+".o")>=6)
        {
            /* Restore the custom warcry from the file it is saved in */
            /* Note that all the global variables are restored */
            restore_object( GRUNTS_WARCRY_DIR + this_player()->query_real_name() );
            if (warcry)
            {
                write ("\nYou remember your warcry:\n'" + warcry + "'\n");
            }
            else
            {
                /* Otherwise, set the warcry to the default warcry */
                warcry = DEFAULT_WARCRY;
            }
        }
        this_player() -> add_prop(LIVE_S_GRUNTS_WARCRY, warcry);
    }

    return;
}

/*
 * Function name:   change_warcry
 * Description:     customise the players 'warcry' to a new string
 * Arguments:       str: the string containing the new warcry
 * Returns:         1 if successfully changed, 0 otherwise.
 */
public int
change_warcry(string str)
{
    string verb;
   
    verb = query_verb();
    notify_fail(capitalize(verb) + " what?\n");
    
    if (strlen(str) <= 5)
        return 0;

    if (str == "warcry")  
    {
        write("Your warcry has been set to the standard Grunts warcry.\n");
        warcry = DEFAULT_WARCRY;
        
        this_player() -> add_prop(LIVE_S_GRUNTS_WARCRY, warcry);
        return 1;
    }
    
    if (sscanf(str, "warcry %s", str) == 0)
        return 0;     /* Make sure it is the warcry player wants to change */
    
    sscanf(str, "to %s", str);     /* 'change warcry to <x>' is acceptable */
    
    /* Now that str is ready, lets change the warcry to the new string str */
    /* Need to update variables in case we have just recruited someone     */
    if (file_size(GRUNTS_WARCRY_DIR+this_player()->query_real_name()+".o")>=6)
    {
        restore_object( GRUNTS_WARCRY_DIR + this_player()->query_real_name() );
    }

    warcry = str;
    this_player() -> add_prop(LIVE_S_GRUNTS_WARCRY, warcry);

    /* Save the new custom warcry to the correct file */
    save_object( GRUNTS_WARCRY_DIR + this_player()->query_real_name() );
    write ("Your war-cry will now be:\n'" + capitalize(warcry) + "'\n");

    return 1;
}

/*
 * Function name:   do_show_notches
 * Description:     show the number of notches on the collar.
 * Returns:         a string description of the notches, if present.
 */
public string
do_show_notches()
{
    int kills;
    string str;

    kills = this_player()-> query_skill(GRUNT_KILLS_COUNT);

    if (!kills)
        return "There are no significant notches on the collar.\n";

    if (kills == 1)
        return "There is a single notch on the collar.\n";

    if (kills >= 2)
    {
        /* This function was added because Thunder wants to show off */
        str = "a couple";
        
        if (kills >= 3)
            str = "a few";

        if (kills >= 10)
            str = "the many";

        if (kills >= 36)
            str = "the few dozen";

        if (kills >= 100)
            str = "over a hundred";

        if (kills >= 300)
            str = "a few hundred";
    
        if (kills >= 1000)
            str = "over a thousand";

        if (kills >= 3000)
            str = "a few thousand";
        
        if (kills >= 10000)
            str = "the many thousands of";
        
        tell_room( environment(this_player()), QCTNAME(this_player())
            + " counts " + str + " notches on " +
            this_player()->query_possessive() + " collar.\n", this_player() );

        return "You count " + LANG_WNUM(kills) + " notches on your collar.\n";
    }
}

/*
 * Function name:   notch_desc
 * Description:     show how the collar is notched (for the set_long).
 * Returns:         a string description of the notches, if present.
 */
public string
notch_desc()
{
    int kills;

    kills = this_player()-> query_skill(GRUNT_KILLS_COUNT);

    if (!kills)
        return "\n";

    if (kills == 1)
        return "\nThere is a single notch on the collar.\n";

    if (kills <= 10)
        return "\nThere are a few notches on your collar.\n";

    if (kills <= 36)
        return "\nThere are many notches on your collar.\n";

    if (kills <= 100)
        return "\nThere are a few dozen notches on your collar.\n";

    if (kills <= 300)
        return "\nThere are at least a hundred notches on your collar.\n";

    if (kills <= 1000)
        return "\nThere are at least a few hundred notches on your collar.\n";
    
    if (kills <= 3000)
        return "\nThere are at least a thousand notches on your collar.\n";

    if (kills <= 10000)
        return "\nThere are a few thousand notches on your collar.\n";

    if (kills <= 30000)  
        return "\nThere are several thousand notches on your collar.\n";

    if (kills <= 100000)  
        return "\nThere are tens of thousands of notches on your collar.\n";
    else
        return "\nThere is barely room for another notch on your collar.\n";

}

/*
 * Function name:   reset_armour
 * Description:     allow the player to crap again (redundant fail-safe)
 */
public void
reset_armour()
{
    if (environment(this_object()) -> query_prop(LIVE_I_CRAPPED_NUMBER) >= 1)
        environment(this_object()) -> remove_prop(LIVE_I_CRAPPED_NUMBER);
    return;
}

/*
 * Function name:   spike_desc
 * Description:     set a material for the spikes, based on kill count.
 * Returns:         a string description of the spikes.
 */
public string
spike_desc()
{
    int kills;
    mixed grunt;

    grunt = environment(this_object());

    kills = grunt -> query_skill(GRUNT_KILLS_COUNT);
 
    if (!kills)
        return "wooden spikes";

    if (kills <= 10)
        return "copper spikes";

    if (kills <= 100)
        return "nickel spikes";

    if (kills <= 300)
        return "bronze spikes";

    if (kills <= 1000)
        return "iron spikes";

    if (kills <= 3000)
        return "brass spikes";
    
    if (kills <= 10000)
        return "steel spikes";

    if (kills <= 20000)
        return "silver spikes";

    if (kills <= 50000)  
        return "golden spikes";
    else
        return "platinum spikes";

}

public string
query_recover()
{
    return 0;
}
