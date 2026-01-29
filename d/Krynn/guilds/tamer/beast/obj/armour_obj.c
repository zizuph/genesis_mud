#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

inherit "/std/armour";

// Global Variables
static mapping  gArmourVars = ([]);

/* 
 * Function name:   query_tamer_pet_armour
 * Description:     Proves the legitimacy of the armour
 * Arguments:       None
 * Returns:         (status) always true
 */
public status
query_tamer_pet_armour()
{
    return 1;
} /* query_tamer_pet_armour */

/* 
 * Function name:   query_ac
 * Description:     Give the ac for a specific hitlocation that is protected
 * Arguments:       (int) hid: Hitlocation id
 * Returns:         (int) The armour ac
 */
varargs int
query_ac(int hid)
{
    int     a_class,
            mat_mod;
    
    if (!m_sizeof(gArmourVars))
        return ::query_ac(hid);
    
    switch(gArmourVars["craft"])
    {
        case "poorly crafted":
        a_class = 1;
            break;
        case "roughly crafted":
        a_class = 2;
            break;
        case "savagely crafted":
        a_class = 3;
            break;
        case "well crafted":
        a_class = 4;
            break;
        case "expertly crafted":
        a_class = 5;
            break;
        default:
            return ::query_ac(hid);
    }
    
    switch(gArmourVars["material"])
    {
        case "metal":
        mat_mod = 5;
            break;
        case "leather":
        mat_mod = 3;
            break;
        default:
        mat_mod = 1;
            break;
    }
   
    return a_class * mat_mod;
} /* query_ac */

/*
 * Function name:   set_pet_armour_vars
 * Description:     This function sets the variables of the armour.
 * Arguments:       (mapping) vars - The variables for the armour.
 * Returns:         Nothing
 */
public void
set_pet_armour_vars(mapping vars)
{
    gArmourVars = vars;
} /* set_pet_armour_vars */

/*
 * Function name:   pet_armour_short
 * Description:     This returns the short description of the pet armour.
 * Arguments:       None
 * Returns:         (string) The short description of the armour
 */
public string
pet_armour_short()
{
    return "companion armour";
} /* pet_armour_short */

/*
 * Function name:   pet_desc_long
 * Description:     This returns the long description for the pet while wearing
 *                  armour.
 * Arguments:       None
 * Returns:         (string) The long description of the pet
 */
public string
pet_desc_long()
{
    if (!m_sizeof(gArmourVars))
        return "";
    
    return "The " + gArmourVars["race"] + " is clad in a "
    + gArmourVars["pet_desc"];
} /* pet_desc_long */

/*
 * Function name:   pet_armour_long
 * Description:     This returns the long description of the pet armour.
 * Arguments:       None
 * Returns:         (string) The long description of the armour
 */
public string
pet_armour_long()
{
    if (!m_sizeof(gArmourVars))
        return "";
    
    return "This is a " + gArmourVars["pet_desc"] + "\n";
} /* pet_armour_long */

/*
 * Function name:   match_pet_size
 * Description:     Checks if the one wearing the armour has an appropriate size
 *                  and genus to wear it.
 * Arguments:       (object) pet - The pet trying to wear the armour
 * Returns:         (status) 1 - armour fits the pet
 */
public status
match_pet_size(object pet)
{
    string  race;
    int     size;

    if (!m_sizeof(gArmourVars))
        return 0;
    
    if (!stringp(race = gArmourVars["genus"]) || pet->query_genus() != race)
        return 0;

    if (!intp(size = gArmourVars["height"]) ||
        pet->query_prop(CONT_I_HEIGHT) != size)
        return 0;

    return 1;
} /* match_pet_size */

/*
 * Function name:   pet_armour_weight
 * Description:     Determines the armour weight.
 * Arguments:       None
 * Returns:         (int) The armour weight
 */
public int
pet_armour_weight()
{
    int weight = 1000;
    
    if (!m_sizeof(gArmourVars))
        return weight;
    
    weight *= gArmourVars["height"];
    
    switch(gArmourVars["material"])
    {
        case "leather":
        weight = (weight * 3) / 100;
            break;
        case "metal":
        weight = (weight * 8) / 100;
            break;
    }
    
    return weight;
} /* pet_armour_weight */

/*
 * Function name:   pet_armour_volume
 * Description:     Determines the armour volume.
 * Arguments:       None
 * Returns:         (int) The armour volume
 */
public int
pet_armour_volume()
{
    int vol;
    
    if (!m_sizeof(gArmourVars))
        return 300;
    
    vol = gArmourVars["height"];
    vol *= vol * 2;
    vol /= 100;
    
    return vol;
} /* pet_armour_volume */

/*
 * Function name:   create_armour
 * Description:     The basic armour construct
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_armour()
{
    set_short("@@pet_armour_short@@");
    set_long("@@pet_armour_long@@");
    
    set_at(A_HEAD | A_BODY | A_ARMS | A_LEGS);
    set_wf(this_object());
    set_keep(1);
    set_ac(1);
    
    add_prop(OBJ_M_NO_SELL, "No shop would be able to place a price on a "
    + "customized companion armour.\n");
    add_prop(OBJ_M_NO_BUY, 1);
    
    add_prop(OBJ_I_WEIGHT, &pet_armour_weight());
    add_prop(OBJ_I_VOLUME, &pet_armour_volume());
} /* create_armour */

/*
 * Function name:   wear
 * Description:     This function might be called when someone tries to wear
 *                  this armour. To have it called, use set_wf().
 * Arguments:       (object) obj - The armour we want to wear.
 * Returns:         (int)   0 - The armour can be worn normally.
 *                          1 - The armour can be worn, but print no messages.
 *                         -1 - The armour can't be worn, use default messages.
 *                  (string) - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    if (match_pet_size(this_player()))
        return 1;

    return "This is a customized pet armour, it would not fit your body "
    + "type.\n";
} /* wear */

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object obj)
{
    return 1;
} /* remove */

/*
 * Function name:   query_recover
 * Description:     Called to make this armour recoverable, and to make sure the
 *                  variables are correct.
 * Arguments:       None
 * Returns:         (string) The recovery string
 */
string
query_recover()
{
    if (!m_sizeof(gArmourVars))
        return ::query_recover();
    
    return MASTER + ":TamerPetArmour#" + gArmourVars["color"] + "#"
    + gArmourVars["color_adj"] + "#" + gArmourVars["condition"] + "#"
    + gArmourVars["craft"] + "#" + gArmourVars["genus"] + "#"
    + gArmourVars["height"] + "#" + gArmourVars["material"] + "#"
    + gArmourVars["race"] + "#" + gArmourVars["style"] + "#";
} /* query_recover */

/*
 * Function name:   init_recover
 * Description:     Initiates the recovery of the pet armour variables.
 * Arguments:       (string) arg - The recovery string
 * Returns:         Nothing
 */
void
init_recover(string arg)
{
    string  head, tail, color, color_adj,
            condition, craft, genus,
            material, race, pet_desc, style;
    int     height;
    
    sscanf(arg, "%sTamerPetArmour#%s#%s#%s#%s#%s#%d#%s#%s#%s#%s#%s", head,
    color, color_adj, condition, craft, genus, height, material, race, style,
    pet_desc, tail);
    
    gArmourVars = ([
        "color" : color, "color_adj" : color_adj, "condition" : condition,
        "craft" : craft, "genus" : genus, "height" : height,
        "material" : material, "race" : race, "style" : style,
        "pet_desc" : pet_desc,
    ]);
} /* init_recover */
