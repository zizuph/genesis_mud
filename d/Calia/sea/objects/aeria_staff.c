/*******************************************************
*
* /d/Calia/sea/objects/aeria_staff.c
*
* Creator:    Quintas    03/10/2002
* Updated:    Jaacar      5/08/2003 - modified slightly
                                      moved to sea dir.
              Petros      5/13/2008 - fixed bug where quitting while
                                      wielded left the room dark.
              ?           2009/4/5    Previous update?
              Lavellan    2010/9/2    Typos
*
* A magical staff that gives light and darkness.
*
* (c) Dwayne Wilson, March 2002  
*
*  Changelog: 
*   Baldacin, 04-02-28: Added a command to permanently remove
*                       the staff.
* 
********************************************************/

#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";

#include <formulas.h>
#include <macros.h> 
#include <ss_types.h>
#include <language.h>
#include <tasks.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "defs.h"

#define  LIGHT_STRENGTH 2
#define  BREAK_LOG      "aeria_staff_break_log"

static string gConfirm = "";
static private int Alarm_Id;

void
create_object()
{
    /*
     * Set names, adjectives, descriptions. 
     */

    set_name("staff of Aeria");
    add_name("staff");
    add_name("aeria staff");
    set_pname("staves"); 
    set_short("staff of Aeria");
    set_pshort("staves of Aeria");
    set_long("This is a long, runed staff with a large gem set in "+
        "the top of it. It appears that a golden claw of some sort "+
        "is holding a diamond in place. Spidery runes trace up and down " +
        "the shaft of the staff. It looks very fragile. It is possible "+
		"to 'permanently remove' the staff, if you wish to.\n");
    set_adj(({"long","runed"}));

    /* Add_item for Runes, claw, diamond, shaft */ 

    add_item(({"runes"}), "@@runes_desc");
    add_item(({"claw","golden claw"}), "This claw has small scales and "+
        "long talons which form a perfect cradle for the diamond to nestle "+
        "into. It obviously came from a lizard of some type, or maybe even "+
        "a gold dragon.\n");
    add_item(({"gem","diamond","large gem"}), "This diamond is of very pure "+
        "quality. Its clarity and brilliance momentarily blind you as you "+
        "look at it.\n");
    add_item(({"shaft"}), "The shaft of the staff is made of rare ironwood. "+ 
        "You see runes carved into it.\n"); 

    set_slots(W_ANYH);
    
    add_prop(OBJ_I_NO_SELL,1);   // Can't sell it
    add_prop(OBJ_I_NO_DROP,1);   // Can't drop it
    add_prop(OBJ_I_NO_GIVE,1);   // Can't give it away
    add_prop(OBJ_M_NO_STEAL,1);  // Nobody can steal it
    
    /*
     * Set weapon standard properties. Ie. weight, size, value, etc
     */
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20, 20));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(20, W_CLUB));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_WEAPON(20, W_CLUB) / 5);
  
    /*
    * Make the weapon magical.
    */

    /* Designate this as a magic weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    /* The 'form' of the magic and the degree of its expression. */
    add_prop(MAGIC_AM_MAGIC, (({ 60, "enchantment" })));

    /* Allow for identification of the magical properties */

    add_prop(MAGIC_AM_ID_INFO, (({"The staff appears to be magical.\n", 10,
        "Commanded properly, it may shed some light.\n", 15})));

    /* Wizard information */

    add_prop(OBJ_S_WIZINFO, "This staff is enchanted. It is a light "+
        "source. Grants "+LANG_NUM2WORD(LIGHT_STRENGTH)+" levels of light.\n");
}

/*
 * Function:     runes_desc
 * Description:  A function used in VBFC to give the description
 *               of the staff, depending on skill and stat checks.
 * Returns:      The runes' description.
 */

string
runes_desc(string str)
{
    str = "The runes are a flowing cursive script made up "+ 
           "of curlicues and dots. "; 
    
    /* Does the holder have enough INT and SS_LANG to read the runes? */
    
    /* The holder cannot read any of the command words */
    
    if ((TP->query_skill(SS_LANGUAGE) < 25) ||
       (TP->query_stat(SS_INT) < 15))
       str = (str + "They seem to shift and squiggle before your eyes. "+ 
           "You cannot make any understanding out of them.\n");
      

    if ((TP->query_skill(SS_LANGUAGE) >= 40) && 
             (TP->query_stat(SS_INT) >= 50))
    {
        // The holder can read both words
        str = (str + "You find that you can understand both the command "
            + "words from the runes.  They are 'Lignium' and 'Nosterim'.\n");
    }
    else if ((TP->query_skill(SS_LANGUAGE) >= 25) &&
             (TP->query_stat(SS_INT) >= 15))
    {
        /* The holder can read the first command word */
        str = (str + "You find that you can understand the first command "
            + "word from the runes. It is called 'Lignium'.\n");
    }

    return str;
}

/* 
 * Function name : do_extinguish 
 * Description: Turns the light property of the staff off. 
 *
 */

public varargs mixed
do_extinguish(int i)
{
    int dim_light;
     
    /* Lets check to see if the staff is giving light. */

    if (!Alarm_Id)
    {
        NF("The staff is not lit.\n");
        return 0;
    }

    else if (Alarm_Id) 
    {
        /* Remove the alarm to go out */
    
        remove_alarm(Alarm_Id);
        Alarm_Id = 0;

        /* First remove any light that the staff is generating itself. */        

        dim_light = ((TO->query_prop(OBJ_I_LIGHT)) - LIGHT_STRENGTH);
        TO->change_prop(OBJ_I_LIGHT, dim_light);
        environment(TP)->update_light(1);
    
        /* Change the descriptions of the staff back to the original. */

        set_long("This is a long, runed staff with a large gem set in the "+
            "top of it. It appears that a golden claw of some sort is "+
            "holding a diamond in place. Spidery runes trace up and down " +
            "the shaft of the staff.\n");   
  
        
        /* Now lets go about saying what happened. */

        switch (i)
        {
        case 1:
            // Extinguished by releasing the staff
            say(QCTPNAME(TP) + " " + short() + " flares one last time as " +
                TP->query_pronoun() + " releases it.\n");
            write("Your " + short() + " flares one last time as you release "+
                "it.\n");
            break;
         
        case 2:
            // Extinguished by issuing the command word
            say("You hear " + QCTNAME(TP) + " mumble a word. The gem at the "
                + "top of the staff flares out and the staff's brilliance "
                + "dims until it emits no more light.\n");           
            write("You enunciate the command word, and the brilliant light that "
                + "filled the gem at the top of the staff emits one final flare "
                + "before going completely dim.\n");                
            break;

        case 0:
        default:
            // Extinguished by expiration of alarm            
            say(QCTPNAME(TP) + " " + short() + " gives off one last flare "
                + "before dimming completely.\n");
            write("Your " + short() + " gives off one last flare "
                + "before dimming completely.\n");
            break;

        }
    }

    return 1;
}

/*
 * Function name: do_light
 * Description: Turns the staff into a level 3 light source
 *              when the proper command word is given. 
 * 
 */

public int
do_light()
{
    int t;
   
    /* first we make sure that the command giver wields the staff */

    if (TO->query_prop(OBJ_I_BROKEN))
    {
        NF("The staff is broken and no longer works.\n");
        return 0;
    }

    if (query_holder() != TP) 
    {
        NF("You must hold the " + short() + " to be able to " +
            "use its abilities.\n");    
        return 0;
    }

    /* Is the staff already lit? */

    if (Alarm_Id)
    {
        NF("The staff is already lit.\n");
        return 0;
    }


    /* Does the holder have enough mana to use this ability? */

    if (query_holder()->query_mana() < 50) 
    { 
        NF("You do not have the mental strength to use this ability.\n");
        return 0;
    }

    /* Calculate the duration of the light: 
     * Formula  duration=int/25 * 60 - (random(150)) 
     * Basically, for every 25 int a player has, they get 1 minute of light 
     * minus a random of minutes based once again on thier int.  Yes it is
     * totally possible that they may only get 1 minute out of the charge. 
     */
 
    t = ((((TP->query_stat(SS_INT)) * 60) /25) - 
        (random(150)));
    t = MAX(60,t);

    /* Set the alarm for duration */

    Alarm_Id = set_alarm((itof(t)), 0.0, &do_extinguish(0));
    
    /* Make the staff a light source. */
    TO->add_prop(OBJ_I_LIGHT, LIGHT_STRENGTH);
    environment(TP)->update_light(1);

    /* Subtract the mana. Basically it'll cost 25 mana for every minute of 
      light */
    TP->add_mana(-(t * 25 / 60));
  
    /* Tell the room. */
    say("You hear " + QCTNAME(TP) + " mumble a word. Blue and white arcs "+
        "of power start dancing along the runes on the shaft of "+
        TP->query_possessive() + " staff, feeding themselves into a "+
        "coalescing river of light that flows toward the gem at the top. "+
        "Suddenly, as the power reaches the gem, " + TP->query_possessive()+
        " staff bursts into brilliance and begins shining almost as bright "+
        "as the sun.\n");
    
    /* Tell the holder. */
    write("You enunciate the command word, and blue and white arcs of power "+
        "start dancing along the runes on the shaft of your staff, feeding "+
        "themselves into a coalescing river of light that flows toward the "+
        "gem at the top. Suddenly, as the power reaches the gem, your staff "+
        "bursts into brilliance and begins shining almost as bright as the "+
        "sun.\n");
    
    /* Add the new descriptions for the lighted staff. */

    set_long("This is a long, runed staff with a large gem set in the "+
        "top of it. It appears that a golden claw of some sort is holding " +
	    "a diamond in place. Spidery runes trace up and down the shaft of "+
        "the staff.\nThe runes are full of white energy that flows in "+
        "pulsing rings from the foot of the staff, upwards toward the gem, "+
        "which is blazing with a pure light that rivals the brightness of "+
        "the sun.\n");  

    return 1;

}

/*
 * Function name: do_permanently_remove
 * Description: Permanently removes the staff, if the player choose
 *              so. 
 */
int
do_permanently_remove(string str)
{
	notify_fail("Permanently remove <what>? The staff?\n");
    if (!strlen(str) || (!parse_command(lower_case(str), ({}),
	  "'remove' [the] 'staff' [of] [aeria]")))
	{
	    return 0;
	}

	if (gConfirm != TP->query_real_name())
    {
	    notify_fail("Are you sure you -permanently- want to remove the staff? Try again if " +
	        "you're sure.\n");
	    gConfirm = TP->query_real_name();
	    return 0;
    }

	write("You focus your mind on removing the "+short()+". Suddenly the "+
		"staff starts pulsing with a bright white light, and it explodes into "+
		"thin air.\nAfter a few moments a voice fills your mind saying: "+
		"'As you wish'.\n");
	say("You see "+QCTNAME(TP)+" focus very hard on something. Suddenly "+
		TP->query_possessive()+" "+short()+" starts pulsing with a "+
		"bright-white light and it explodes in thin air.\n");
	log_file(BREAK_LOG, capitalize(TP->query_name())+" destructed staff"+
		"(by free will). "+ctime(time())+"\n",-1);
	TO->remove_object();
	return 1;        
}

/*
 * Function name: hold
 * Description  : Called when the person wants to hold an item. This function
 *                may allow or disallow the object to be held, and it may
 *                print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be held, print default messages.
 *                 1 - The item can be held, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be held. Print default messages.
 *                string - The item cannot be held. The string contains the
 *                         fail message.
 */
public mixed
hold()
{
    say("A light breeze blows through the area as " + QCTNAME(TP)
        + " holds " + TP->query_possessive() + " " + short() + ".\n");

    write("A light breeze swirls around you as you hold your " + 
        short() + ".\n");

    return 1;
}

/*
 * Function name: release
 * Description  : Called when the person wants to release the item. This
 *                function may allow or disallow the object to be released,
 *                and it may print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be relased, print default messages.
 *                 1 - The item can be relased, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be released. Print default messages.
 *                string - The item cannot be relased. The string contains the
 *                         fail message.
 */
public mixed
release()
{
    if (Alarm_Id)
    {
        do_extinguish(1);
        return 1;
    }

    return 0;
}

string
query_auto_load()
{
    if (!TO->query_prop(OBJ_I_BROKEN))
    {
        return MASTER + ":";
    }
}

public string
query_recover()
{
    return 0;
}

public int
do_nosterim(string str)
{
    return do_extinguish(2);
}

public int
do_lignium(string str)
{
    return do_light();
}

/* Adds the command words of the staff to the holder */

public void
init()
{
    ::init();
    add_action(do_lignium, "Lignium");
    add_action(do_lignium, "lignium");
    add_action(do_nosterim, "Nosterim");
    add_action(do_nosterim, "nosterim");
	add_action(do_permanently_remove, "permanently");
}

// Functions to support holdable item. See comments in /lib/holdable_item

void
leave_env(object from, object to)
{
     ::leave_env(from, to);
     holdable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}