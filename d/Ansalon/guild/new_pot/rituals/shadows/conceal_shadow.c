/*
 * The shadow for the cloak hood
 *
 * 960117 by Rastlin
 *   Modification Log:
 *     Elessar, 1998.
 *     Alto, February 2002. Modified for ranger recode.
 *     Tigerlily, Dec. 2004, modified to conceal more sublocs.
 *                Jan. 2005, fixed to allow 'last' command on
 *                           rangers when masked
 *     Toby, 29 Nov, 2006  : Removed query_prop so that players are always known. 
 *                           (Need to check that this holds true and nothing more
 *                            needs fixing.)
 *                           Change needed on orders from the Admin. No player
 *                           may no longer use LIVE_I_NEVERKNOWN.
 */

#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <living_desc.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include <composite.h>

inherit "/std/shadow";

#define EYES_SUBLOC             "eyes"
#define HAIR_SUBLOC             "hairstyle"
#define MISC_EXTRA              "_subloc_misc_extra"
#define SOUL_EXTRA              "_soul_cmd_extra"

                     
static string  *gAdjs,
                gColour,
                gRobed;
static int      gAdjsNum = 0,
                hood_worn = 0;

public void
set_hood_worn(int worn)
{
    hood_worn = worn;
}

public int
query_hood_worn()
{
    return hood_worn;
}

public string
set_conceal_colour(string colour)
{
    if (gColour != colour)
        gColour = colour;
    else
        gColour = "iridescent";
    
    return gColour;
}

public string
query_conceal_colour()
{
    return gColour;
}

public string
new_conceal_feature()
{
    gAdjsNum++;
    
    if (sizeof(gAdjs) <= gAdjsNum)
        gAdjsNum = 0;
    
    return gAdjs[gAdjsNum];
}

public void
init_priest_robe()
{
    gAdjs   = shadow_who->query_adjs();
    gColour = "iridescent";
    gRobed  = "velvet-robed";
    
}

/*
 * Function name: query_adj
 * Description  : Gives the adjective(s) of the object.
 * Arguments    : int arg - if true, all adjectives are returns, else only
 *                          the first adjective is returned.
 * Returns      : mixed   - int 0    - if there are no adjectives.
 *                          string   - one adjective if 'arg' is false.
 *                          string * - an array with all adjectives if
 *                                     'arg' is true.
 */
varargs public mixed
query_adj(int arg) 
{ 
    if (arg)
        return gAdjs;
    else
        return gAdjs[0]; 
}

/*
 * Function name: query_adjs
 * Description  : This function returns an array of all adjectives of
 *                this object.
 * Returns      : An array of all adjectives of this object
 *                or false if there are no adjectives.
 */
public string *
query_adjs() 
{ 
    return gAdjs;
}

/*
 * Function name: parse_command_adjectiv_id_list
 * Description  : This function is used by the efun parse_command()
 */
public string *
parse_command_adjectiv_id_list() 
{
    return gAdjs;
}

/*
 * Function name: adjectiv_id
 * Description  : This function can be used to see whether a certain
 *                adjective is used by this object.
 * Arguments    : string str - the adjective you want to test.
 * Returns      : int 1/0 - true if the adjective is indeed used.
 */
public int
adjectiv_id(string str)
{
    return (member_array(str, gAdjs) >= 0);
}

public void
remove_robe_hood_shadow()
{
    if (objectp(shadow_who))
        shadow_who->catch_msg("You emerge from within the " +
        "illusion shrouding you.\n");
    
    remove_shadow();
}

public int
query_hooded()
{
    object po = previous_object();
    mixed caller;
    
    if (!objectp(po))
        return 0;

    caller = file_name(po);

    if (caller[0..8]== "/d/Avenir")
        return 0;

    return 1;
}

public string
show_scar(mixed for_obj)
{
    return "";
}

public string
query_nonmet_name()
{
    string  short_desc;
    
    if (gAdjsNum > sizeof(gAdjs))
        gAdjsNum = 0;
    
    if (query_hood_worn())
    {
        if (gColour == "hooded")
            short_desc = gRobed + " " + gColour;
        else
            short_desc = gColour + " " + gRobed;
    }
    else
    {
        short_desc = gRobed + " " + gAdjs[gAdjsNum];
    }
    
    short_desc +=   " " + shadow_who->query_gender_string() +
                    " " + shadow_who->query_race_name();
                    
    return short_desc;
}

varargs public mixed 
show_cont_subloc(string sloc, object for_obj)
{
    string  pron,
           *armours = filter(shadow_who->query_armour(-1), &operator(!=)(1) @
                      &->query_takhisis_guild_item());
              
    if (sloc == EYES_SUBLOC || sloc == HAIR_SUBLOC)
    {
        if (!query_hood_worn())
            return shadow_who->show_cont_subloc(sloc, for_obj);
            
        return "";
    }
    if (sloc == MISC_EXTRA)
        return "";
    if (sloc == SOUL_EXTRA)
        return "";
    if (sloc == SUBLOC_WIELD)
        return shadow_who->show_cont_subloc(sloc, for_obj);
    if (sloc == SUBLOC_HELD)
        return shadow_who->show_cont_subloc(sloc, for_obj);
    if (sloc == SUBLOC_WORNA)
    {
        if (shadow_who->notmet_me(for_obj))
            pron = " is ";
        else
            pron = capitalize(shadow_who->query_pronoun()) + " is ";
        if (for_obj == shadow_who)
            pron = "You are ";
            
        pron += "enshrouded in a long robe made of rich velvet " +
                "fabric. It has an iridescent black colour which " +
                "shifts in green, blue and deep purple like that of " +
                "beetle wings, making it look alive. An intricate " +
                "embroidery of a five-headed multi-coloured dragon " +
                "adorns the back. The large hood and wide sleeves are " +
                "lined with a two-inch wide band of fine deep " +
                "blue-coloured velvet and on the left side of the " +
                "robe is a crescent of deepest black.";
        
        if (for_obj == shadow_who)
            pron += " Around your neck ";
        else
            pron += " Around the neck ";
        
        pron += "hangs a medallion, a plain disc of metal, blackened, and " +
                "inscribed with a life-like carving of a five-headed dragon.";
        
        if (for_obj == shadow_who)
            return "You are wearing " + COMPOSITE_DEAD(armours) +
            ".\n" + pron + "\n"; 
        
        if (sizeof(armours))
            pron += " The robe effectively conceals the " +
            (query_hood_worn() ? "head and " : "") + "body, but as if " +
            "its fabric was faintly translucent you catch glimpses of " +
            COMPOSITE_DEAD(armours) + ".";
        
        return pron + "\n";
    }

    return "";
}

/*
 * Function name: parse_command_id_list
 * Description  : Mask of player_command_id_list() in /std/object.c to make sure
 *                that players cannot use the name of an NPC or player when that
 *                person hasn't been introduced to them.
 * Returns      : string * - the original parse_command_id_list() without the
 *                    lower case name of the person. "Figure" added to list
 *                    of names
 */
public string *
parse_command_id_list()      
{
    string *ids = shadow_who->parse_command_id_list();
    object pobj = previous_object();

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    if (!shadow_who->notmet_me(pobj))
        return ids;

    ids += ({ shadow_who->query_race_name() });
    
    return ids;
}

/*
 * Description: This function is used buy the efun parse_command()
 */
public string *
parse_command_plural_id_list() 
{ 
    string *plural_ids = shadow_who->parse_command_plural_id_list();
    object pobj = previous_object();

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    // else if masked
    if (!shadow_who->notmet_me(pobj))
        return plural_ids;
    
    plural_ids += ({ LANG_PWORD(shadow_who->query_race_name()) });

    return plural_ids;
}
/*
public string
race_sound()
{
    if (shadow_who->query_prop(RANGERS_MASK_CLOSED))
        return "speaks with a calm demeanor"; 

    return (shadow_who->race_sound());
}

public string
actor_race_sound()
{
    if (shadow_who->query_prop(RANGERS_MASK_CLOSED))
        return "speak with a calm demeanor";

    return (shadow_who->actor_race_sound());
}
*/


/*
 * CWD: /std/living/description.c
 *  /sys/living_desc.h
 * description.c
 * Function name:   query_the_name
 * Description:     Gives the name preceded by "the" when the object
 *                  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty",
 *                        when unmet: "the big fat gnome wizard".
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with "the".
 */
public varargs string
query_the_name(object pobj)
{
    string pre = "", aft = "";

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    if (!CAN_SEE(pobj, shadow_who) || 
        !CAN_SEE_IN_ROOM(pobj))
        return LD_SOMEONE;

    if (shadow_who->query_prop(OBJ_I_HIDE) > 0)
    {
        pre = "[";
        aft = "]";
    }

    if (shadow_who->query_prop(OBJ_I_INVIS) > 0)
    {
        pre = "(";
        aft = ")";
    }

    if (objectp(pobj) && shadow_who->notmet_me(pobj))
        return pre + LD_THE + " " + query_nonmet_name() + aft;

    return shadow_who->query_the_name(pobj);
}

/*
 * Function name:   query_The_name
 * Description:     Gives the name preceded by "The" when the calling object
 *                  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty",
 *                        when unmet: "The big fat gnome wizard".
 * Argument:        pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with "The".
 */
public varargs string
query_The_name(object pobj)
{
    string desc;

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    desc = query_the_name(pobj);
    /* Capitalize the right character if the description starts with ( or [. */
    if (wildmatch("[\\[(]*", desc))
        return desc[..0] + capitalize(desc[1..]);

    return capitalize(desc);
}

/*
 * Function name:   query_art_name
 * Description:     Gives the name with a prefix article when the object
 *                  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty",
 *                        when unmet: "a big fat gnome wizard".
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with article.
 */
public varargs string
query_art_name(object pobj)
{
    string pre, aft;

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    pre = ""; aft = "";

    if (!CAN_SEE(pobj, shadow_who) || 
        !CAN_SEE_IN_ROOM(pobj))
        return LD_SOMEONE;

    if (shadow_who->query_prop(OBJ_I_INVIS) > 0)
    {
        pre = "(";
        aft = ")";
    }
    else if (shadow_who->query_prop(OBJ_I_HIDE) > 0)
    {
        pre = "[";
        aft = "]";
    }
    
    if (shadow_who->notmet_me(pobj))
        return pre +  LANG_ADDART(query_nonmet_name()) + aft;

    return (shadow_who->query_art_name(pobj));
}

/*
 * Function name:   query_Art_name
 * Description:     Gives the name with a capitalized prefix article when the
 *                  calling object has not met this living.
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with capitalized article.
 */
public varargs string
query_Art_name(object pobj)
{
    string desc;

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    desc = query_art_name(pobj);

    /* Capitalize the right character if the description starts with ( or [. */
    if (wildmatch("[\\[(]*", desc))
        return desc[..0] + capitalize(desc[1..]);

    return capitalize(desc);
}


/*
 * Function name:   query_the_possessive_name
 * Description:     Gives the possessive form of the name preceded by "the"
 *                  when the calling object  has not met this living.
 * Argument:        pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Possessive name prefixed with "the".
 */
public varargs string
query_the_possessive_name(object pobj)
{
    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }
    
    return LANG_POSS(query_the_name(pobj));
}