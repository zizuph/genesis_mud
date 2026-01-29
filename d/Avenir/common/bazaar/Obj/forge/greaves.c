// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/
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
    string str;
    if (plating && plating != 0)
        str = "The only embellishment is "+ plating +"-plated "+
              "knotwork of dazzling complexity and elegance.\n";
    else
        str = "The steel has been "+ decor +" in "+ colour +", "+
              "presenting a surface so remarkably smooth and un"+
              "marred it almost seems a pity to wear the greaves "+
              "into combat.\n";

    return  "This "+ short() +", unsurpassed in beauty and function"+
            "ality, can only be the work of sybarite dwarves, whose "+
            "master armourers are rumoured to be women.\n   The "+ 
            astyle +" is composed of "+ query_style_long() +" The "+
            "greaves are lined with "+ colour +" "+ lining +" and "+
            "moulded to provide perfect fit and comfort for "+ 
            LANG_ADDART(query_owner()) +". "+ str;
}

string
short_desc()
{
    if (plating && plating != 0)
        return plating +"-plated pair of "+ astyle +" greaves";
    else    
        return "pair of "+ colour +" "+ decor +" "+ astyle +" greaves";

}

string
pshort_desc()
{
    if (plating && plating != 0)
        return plating +"-plated pairs of "+ astyle +" greaves";
    else    
        return "pairs of "+ colour +" "+ decor +" "+ astyle +" greaves";
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

    set_name("greaves");
    set_at(A_LEGS);
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
       
    set_adj(({ lining, colour, decor }));
    set_name(FORGE_MASTER->query_armour_style(style));

    add_name(({style, "armour", "greaves"}));
    add_name(({"pair of "+ style, colour +" "+ style, decor +" "+ style }));

    set_short(short_desc);
    set_pshort(pshort_desc);
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
