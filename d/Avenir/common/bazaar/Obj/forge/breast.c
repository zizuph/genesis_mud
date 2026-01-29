// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/forge/breast.c
// creator(s):	  Lilith 
// last update:	  Lilith 
// purpose:       
// note:          
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/Obj/forge/armour_base";

#include <macros.h>
#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/common/bazaar/Obj/forge/forge.h"

string breast;
int times;

void forge_it();
void final_update();

string
long_desc()
{
    string str, str2;
    if (plating && plating != 0)
        str = "The edges of the "+ breast +" have a "+ plating +
              " -plated knotwork of dazzling complexity and elegance.\n";
    else
        str = "The steel has been "+ decor +" in "+ colour +".\n";

    if (breast == "breastplate")
        str2 = "The breastplate itself has the sculpted look of a "+
               "classical, well-muscled bust. ";
    else
        str2 = "The hauberk will provide good protection from the "+
               "torso down to the upper thighs. ";

    return  "This "+ short() +", unsurpassed in beauty and function"+
            "ality, can only be the work of sybarite dwarves, whose "+
            "master armourers are rumoured to be women.\n   "+ str2 +
            "It is composed of "+ query_style_long() +" It is "+
            "padded with "+ colour +" "+ lining +" that is "+
            "moulded to fit "+ LANG_ADDART(query_owner()) +
            " perfectly. "+ str;
}

string
short_desc()
{
    if (plating && plating != 0)
        return "handsome "+ plating +"-plated "+ breast;
    else    
        return "handsome "+ colour +" "+ decor +" "+ breast;

}

void
create_armour()
{
    ::create_armour();

    /* Expensive custom-made armours. 
     * Guaranteed to recover 3 times. 
     */
    if (times < 4) 
    {
        times++;
        set_may_recover();
    }

    set_af(TO);
}

void
forge_it()
{
    if (!style)
        style = STYLE;
    if (!lining)
        lining = LINING;
    if (!decor)
        decor = DECOR;
    if ((decor == "plated") && (!plating))
    {
        plating = PLATING;    
        colour = "white";
    }
    if (!colour)
        colour = COLOUR;
    if (!owner)
    {
        if (living(environment(this_object())))
            owner = environment(this_object())->query_race_name();
        else
            owner = "person your size ";
    }
    
    if (plating)
    {
        set_plating(plating);
        add_adj(plating); 
        add_knotwork();
    }

    if (style == "plate")
    {
        breast = "breastplate";
        set_at(A_CHEST);
    }
    else
    {
        breast = "hauberk";    
        set_at(A_TORSO | A_WAIST | A_HIPS);
    }
    
    set_lining(lining);
    set_line_long(FORGE_MASTER->query_lining_long(lining));
    set_colour(colour);
    set_decor(decor);
    set_style(style);
    set_style_long(FORGE_MASTER->query_armour_long(style));
    set_arm_style(FORGE_MASTER->query_armour_style(style));
    astyle = query_arm_style(); 

    set_adj(({ lining, colour, decor, astyle }));
    set_name(FORGE_MASTER->query_armour_style(style));
    add_name(({style, "armour", breast, astyle}));

    set_short(short_desc);
    set_long(long_desc);

    set_ac(FORGE_MASTER->query_armour_ac(style));
    set_am(FORGE_MASTER->query_armour_am(style));
 
    /* Lets be sure to get the legal values */
    update_prop_settings();	
    final_update();   

    add_item(({"lining", lining}), 
        FORGE_MASTER->query_lining_long(lining));    
}

void
final_update()
{
    /* Expensive, custom-made armours. 
     * Lets modify the values.
     */
    add_prop(OBJ_I_WEIGHT, (query_prop(OBJ_I_WEIGHT) * 4) / 5);
    add_prop(OBJ_I_VALUE,  (query_value() * 3) / 2);
}




/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    string rec;

    if (plating && plating != 0)
        rec = MASTER + ":#STYLE#" + style + 
                        "#LINING#" + lining +
                        "#COLOUR#" + colour +
                        "#DECOR#"  + decor +
                        "#TIMES#"   + times +
                        "#PLATING#" + plating +
                        "#NONE#";
    else
        rec = MASTER + ":#STYLE#"  + style + 
                        "#LINING#" + lining +
                        "#COLOUR#" + colour +
                        "#DECOR#"  + decor +
                        "#TIMES#"  + times +
                        "#NONE#";

    return rec + query_arm_recover();
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    sscanf(arg, "#STYLE#%s#LINING#%s#COLOUR#%s#DECOR#%s#TIMES#%d#PLATING#%s#NONE#%s", 
           style, lining, colour, decor, times, plating, none);
    init_arm_recover(arg);
    forge_it();   
}



