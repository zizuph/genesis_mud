/*
 * /d/Sparkle/area/city/bank/obj/bank_manual.c
 * 
 * Bank manual for bank employees
 * 
 * Feb 2009, Aeg
 */

/* Inheritance */
inherit "/std/object";

/* Includes */
#include <stdproperties.h>
#include <macros.h>
 
/* Prototypes */
public int      skim(string arg);

/* Function name:       create_object
 * Description  :       creates our object!
 * Arguements   :       None
 * Returns      :       None
 */ 
public void
create_object()
{
    set_name("manual");
    set_pname("manuals");
    set_adj("mundane");
    set_adj("gray");
    set_long("This is the manual for employees of the Gnomes of Genesis. "
           + "You could skim some pages, if you'd like.\n"); 
    add_prop(OBJ_I_VALUE, 2);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 40);
    
    seteuid(getuid());
    
      
} /* create_object() */

/* Function name:       init
 * Description  :       adds the action
 * Arguements   :       None
 * Returns      :       None
 */
public void
init()
{
    ::init();
    add_action("skim", "skim");
} /* init */

/* 
 * Function name:       skim
 * Description  :       allows players to skim the manual
 * Arguments    :       string arg - what was typed after the verb
 * Returns      :       int 1 - success, 0 - failure
 */
public int
skim(string arg)
{
    if (arg == "pages")
    {
        write("You skim the manual. Holy hell this is boring!\n");
        say(capitalize(QCTNAME(this_player()))
            + " skims " + this_player()->query_possessive()
            + " manual. " + capitalize(this_player()->query_pronoun()) 
            + " appears to be drowsy.\n");
        return 1;
    }
    
    notify_fail("Skim pages?\n");
    return 0;
} /* skim */
