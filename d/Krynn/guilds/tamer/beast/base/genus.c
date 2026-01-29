#include "defs.h"

// Global Variables
static string   gGenus, gTamerName, gChild, gFamily, gFur;
static mapping  gBiomeList;
static object   gTamerObj;
static int      gTamerLev, gPetAge;


/*
 * Function name:   set_tamer_name
 * Description:     Sets the name of the tamer to whom the mount belongs.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
set_tamer_name(string tamer)
{
    if (!objectp(gTamerObj) || gTamerObj->query_real_name() != tamer)
        gTamerObj = find_player(tamer);
    
    gTamerName = tamer;
} /* set_tamer_name */

/*
 * Function name:   query_tamer_name
 * Description:     Returns the name of the tamer to whom the mount belongs.
 * Arguments:       None
 * Returns:         Nothing
 */
public string
query_tamer_name()
{
    return gTamerName;
} /* query_tamer_name */

/*
 * Function name:   set_tamer
 * Description:     Sets the name of the tamer to whom the mount belongs.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
set_tamer(mixed tamer)
{
    if (stringp(tamer))
        return set_tamer_name(tamer);
    
    if (!objectp(tamer))
        return;
    
    if (tamer->query_real_name() != gTamerName)
        gTamerName = tamer->query_real_name();
    
    gTamerObj = tamer;
} /* set_tamer */

/*
 * Function name:   query_tamer
 * Description:     Returns the tamer object to whom the mount belongs.
 * Arguments:       None
 * Returns:         Nothing
 */
public object
query_tamer()
{
    return gTamerObj;
} /* query_tamer */

/*
 * Function name:   set_genus
 * Description:     Sets the genus name of the mount.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
set_genus(string str)
{
    gGenus = str;
} /* set_genus */

/*
 * Function name:   query_genus
 * Description:     Returns the genus name of the mount.
 * Arguments:       None
 * Returns:         Nothing
 */
public string
query_genus()
{
    return gGenus;
} /* query_genus */

/*
 * Function name:   set_biome_list
 * Description:     Sets the ecological origin of the mount races.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
set_biome_list(mapping biome)
{
    gBiomeList = biome;
} /* set_biome_list */

/*
 * Function name:   query_biome_list
 * Description:     Returns the ecological origin of the mount races.
 * Arguments:       None
 * Returns:         Nothing
 */
public mapping
query_biome_list()
{
    return gBiomeList;
} /* query_biome_list */

/*
 * Function name:   set_family
 * Description:     Sets the family name of the beast.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
set_family(string str)
{
    gFamily = str;
}

/*
 * Function name:   query_family
 * Description:     Returns the family name of the beast.
 * Arguments:       None
 * Returns:         Nothing
 */
public string
query_family()
{
    return gFamily;
} /* query_family */

/* 
 * Function name:   set_child
 * Description:     Sets the racial name of the beast as a cub.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
set_child(string str)
{
    gChild = str;
} /* set_child */

/*
 * Function name:   query_child
 * Description:     Returns the racial name of the beast as a cub.
 * Arguments:       None
 * Returns:         Nothing
 */
public string
query_child()
{
    return gChild;
} /* query_child */

/*
 * Function name:   set_fur
 * Description:     Sets the fur/chitin of the beast.
 * Arguments:       (string)
 * Returns:         Nothing
 */
public void
set_fur(string str)
{
    gFur = str;
} /* set_fur */

/*
 * Function name:   query_fur
 * Description:     Returns the fur/chitin of the beast.
 * Arguments:       None
 * Returns:         Nothing
 */
public string
query_fur()
{
    return gFur;
} /* query_fur */

/*
 * Function name:   query_maturity
 * Description:     Returns the age of the pet.
 * Arguments:       None
 * Returns:         Nothing
 */
public varargs int
query_maturity(mixed tamer)
{
    int age, mature, lev;
    
    if (tamer)
    {
        if (stringp(tamer) && tamer != gTamerName)
            set_tamer_name(tamer);
        
        if (objectp(tamer) && tamer != gTamerObj)
            set_tamer(tamer);
    }
    
    if (objectp(gTamerObj))
    {
        gTamerLev = gTamerObj->query_guild_level_lay();
        gPetAge = MANAGER->query_pet_age(gTamerName);
    }
    /* Calculate pet age in days */
    mature = min(gPetAge, (gTamerLev + min(10, max(1,  gPetAge / 86400))) / 2);
    
    //Test return
    if (BETA_TEST)
        mature = 8;
    
    if (gTamerName && mature > 6)
    {
        if (GENUS->query_genus_rideable(this_object()))
            MANAGER->add_achievement(gTamerName, CAN_MOUNT);
        else
            MANAGER->add_achievement(gTamerName, TSCOUT);
    }
    
    return mature;
} /* query_maturity */

public string
query_maturity_desc()
{
    return (query_maturity() < 4 ? "young" : (query_maturity() > 6 ?
            "adult" : "adolescent"));
}

public string
query_maturity_race()
{
    string r_name, tamer, r_pet;
    
    tamer = query_tamer_name();
    r_pet = MANAGER->query_pet_race(tamer);
    
    if (strlen(tamer) && query_maturity() < 6)
    {
        r_name = GENUS->query_cub(r_pet);
        
        if (stringp(r_name))
            return r_name;
        
        return GENUS->query_cub(query_genus());
    }
    
    return r_pet;
}