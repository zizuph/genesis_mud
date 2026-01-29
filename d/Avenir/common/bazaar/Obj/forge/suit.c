// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/forge/suit.c
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

int times;
void forge_it();
void final_update();

string
long_desc()
{
    string str, str2;
    if (plating && plating != 0)
        str = "The entire suit is embellished with "+ plating +
              "-plated knotwork of dazzling complexity and elegance.\n";
    else
        str = "The entire suit has been "+ decor +" in "+ colour +".\n";

    return  "This custom-made "+ short() +", unsurpassed in beauty and "+
            "function"+
            "ality, can only be the work of sybarite dwarves, whose "+
            "master armourers are rumoured to be women.\n   This suit "+ 
            "of armour has been made with "+ query_style_long() +
            " It will provide excellent coverage from head to toe, "+
            "however, once any section of it is damaged beyond repair, "+
            "the entire suit will be rendered useless. "+ str +
            "   It has been padded with "+ colour +" "+ lining +
            " that is moulded to fit the frame of "+ 
            LANG_ADDART(query_owner()) +" perfectly. ";
}

string
short_desc()
{
    if (plating && plating != 0)
        return plating +"-plated suit of "+ astyle;
    else    
        return colour +" "+ decor +" suit of "+ astyle;

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

    set_name("suit");
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
            owner = environment(this_object())->query_race();
        else
            owner = "person your size";
    }
  
    if (plating)
    {
        set_plating(plating);
        add_adj(plating); 
        add_knotwork();
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
    add_name(({"suit", style, "armour", "suit of armour", astyle}));

    set_short(short_desc);
    set_long(long_desc);

    set_at(A_TORSO | A_HEAD | A_NECK | A_WAIST | A_LEGS | A_ARMS | A_HANDS | A_FEET);
    set_ac(FORGE_MASTER->query_armour_ac(style));
    set_am(FORGE_MASTER->query_armour_am(style));
  
    /* Lets be sure to get the legal values */
    this_object()->update_prop_settings();
    this_object()->final_update();   

    add_item(({"lining", lining}), 
        FORGE_MASTER->query_lining_long(lining));    
}

void
final_update()
{
    /* Expensive, custom-made armours. 
     * Modify the values.
     * In this case, you have to pay thru the nose.
     */
    add_prop(OBJ_I_VALUE,  (query_value() * 15));

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

