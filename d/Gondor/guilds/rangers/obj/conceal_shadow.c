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

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

inherit "/std/shadow";

#define EYES_SUBLOC         "eyes"
#define HAIR_SUBLOC         "hairstyle"
#define WIELDED             "wielded"
#define WORN_SUBLOC         "worn_a"
#define MISC_EXTRA          "_subloc_misc_extra"
#define SOUL_EXTRA          "_soul_cmd_extra"
#define RANGERS_AS_KNOWN     "_rangers_as_known"
#define RANGERS_MASK_CLOSED "_rangers_mask_closed"
#define RANGERS_I_INCOGNITO "_rangers_incognito"
#define RANGER_I_PINNED_CLOAK  "_ranger_i_pinned_cloak"
#define EXTREMITIES ({TS_LEGS, TS_LHAND, TS_RHAND, \
                     TS_RFINGER, TS_LFINGER, TS_RFOOT, TS_LFOOT,})

static string *gAdjs;
static string gColour;
static string gHeight;

public void
set_colour(string colour)
{
    switch (shadow_who->query_race_name())
    {
    case "hobbit":
    case "gnome" :
    case "dwarf":
        gHeight = "short";
        break;
    case "human":
    case "elf":
        gHeight = "tall";
        break;
    default:
        gHeight = "medium-sized";
        break;
    }

    if (!strlen(colour))
    {
        gAdjs = ({ "cloaked", "hooded", gHeight });
        gColour = "mottled";
    }
    else
    {
        gAdjs = ({ colour + "-cloaked", "hooded", gHeight });
        gColour = colour;
    }
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
remove_shadow()
{
    shadow_who->remove_cmd_item("face");
    shadow_who->remove_prop(RANGERS_I_INCOGNITO);
    shadow_who->remove_prop(RANGER_I_PINNED_CLOAK);
    shadow_who->remove_prop(RANGERS_MASK_CLOSED);
    shadow_who->remove_name(shadow_who->query_ranger_name());
    shadow_who->update_actions();
    ::remove_shadow();
}

public void
remove_robe_hood_shadow()
{
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

/*
 * Function name:   notmet_me
 * Description:     Finds out if obj is considered to have met me. Players
 *                  must have been introduced to me. All others don't have to
 *                  be introduced to know me.
 * Arguments:       obj: Object in question, has it met me?
 * Returns:         True if object has not met me.
 */
public int
notmet_me(object obj)
{
    string * known_prop;
    string name = shadow_who->query_real_name();

    if (!objectp(obj))
        return 1;
    if (!interactive(obj))
    {
        return 1;
    }
    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->notmet_me(obj));

    if (obj->query_wiz_level())
        return 0;

    //check if revealed 
    known_prop = obj->query_prop(RANGERS_AS_KNOWN);
    if (sizeof(known_prop))
    {
        if (member_array(name, known_prop) == -1)
            return 1;
        else
            return 0;
    }
    else 
        if (interactive(obj))
            return 1;

    return (shadow_who->notmet_me(obj));
}


public string
show_scar(mixed for_obj)
{
    return "";
}

public string
query_nonmet_name()
{
    string short_desc;

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->query_nonmet_name());

    if (sizeof(gAdjs))
        short_desc = gHeight + " " + gAdjs[0] + " figure";
    else
        short_desc = gHeight + " cloaked figure";

    return short_desc;
}

varargs public mixed 
show_cont_subloc(string sloc, object for_obj)
{
    int ext_loc = random(sizeof(EXTREMITIES));
    string pron;

    if (sloc == EYES_SUBLOC || sloc == HAIR_SUBLOC)
        return "";
    if (sloc == MISC_EXTRA && shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return "";
    if (sloc == SOUL_EXTRA && shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return "";
    if (sloc == WIELDED)
        return shadow_who->show_cont_subloc(sloc, for_obj);

    if (sloc == WORN_SUBLOC && shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
    {
        if (notmet_me(for_obj))
            pron = "The figure is ";
        else
            pron = capitalize(shadow_who->query_pronoun()) + " is ";
        if (for_obj == shadow_who)
            pron = "You are ";
        if (objectp(shadow_who->query_armour(EXTREMITIES[ext_loc])))
             return pron + "wearing a " + 
                "cloak that is pinned at the " +
                "left shoulder and hooded, effectively concealing " +
                "the head and body from view, but you catch a glimpse of " +
                LANG_ASHORT(shadow_who->query_armour(EXTREMITIES[ext_loc])) + 
                ".\n";
        else
            return pron + 
                "wearing a cloak that is pinned at the left shoulder " +
                "and hooded, concealing the head and body from view.\n";
    }

    if (shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return "";

    return shadow_who->show_cont_subloc(sloc, for_obj);
}

public string
query_pronoun()
{    
    object pobj = previous_object();

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->query_pronoun());

    //else neuter--can't tell gender
    if (objectp(pobj) && notmet_me(pobj) )
        return "it";
        
    return (shadow_who->query_pronoun());
}

public string 
query_objective()
{
    object pobj = previous_object();

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->query_objective());
    //else neuter--can't tell gender
    if (objectp(pobj) && notmet_me(pobj) )
        return "it";

    return (shadow_who->query_objective());
}

public string
query_possessive()
{
    object pobj = previous_object();

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->query_possessive());

    //else neuter--can't tell gender
    if (notmet_me(pobj))
        return "its";

    return (shadow_who->query_possessive());
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
    string *ids;
    string prace = shadow_who->query_race_name();
    object pobj = previous_object();

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->parse_command_id_list());

    if (!notmet_me(pobj))
        return (shadow_who->parse_command_id_list());

    ids = shadow_who->parse_command_id_list();
    ids += ({ "figure" });
    if (member_array(prace, ids) != -1)
        ids -= ({ prace });
    return ids;
}

/*
 * Description: This function is used buy the efun parse_command()
 */
public string *
parse_command_plural_id_list() 
{ 
    string *plural_ids = shadow_who->parse_command_plural_id_list();
    string prace;
    object pobj = previous_object();

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->parse_command_plural_id_list());

    // else if masked
    if (!notmet_me(pobj))
        return (shadow_who->parse_command_plural_id_list());
    prace = LANG_PWORD(shadow_who->query_race_name()); 
    plural_ids += ({ "figures" });
    if (member_array(prace, plural_ids) != -1)
        plural_ids -= ({ prace });
    return plural_ids;
}


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

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK)) 
        return (shadow_who->query_the_name(pobj));

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

    if (objectp(pobj) && notmet_me(pobj))
        return pre + LD_THE + " " + query_nonmet_name() + aft;

    return shadow_who->query_the_name(pobj);
}

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

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (shadow_who->query_The_name(pobj));

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

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))  
        return (shadow_who->query_art_name(pobj));

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
    if (notmet_me(pobj))
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

public string
race_sound()
{
    if (shadow_who->query_prop(RANGERS_MASK_CLOSED))
        return "speaks in a hushed voice"; 

    return (shadow_who->race_sound());
}

public string
actor_race_sound()
{
    if (shadow_who->query_prop(RANGERS_MASK_CLOSED))
        return "speak in a hushed voice";

    return (shadow_who->actor_race_sound());
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

    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED) &&
        !shadow_who->query_prop(RANGER_I_PINNED_CLOAK))
        return (LANG_POSS(shadow_who->query_the_name(pobj)));

    if (notmet_me(pobj))
        return LANG_POSS(query_the_name(pobj));
     
    return LANG_POSS(shadow_who->query_the_name(pobj));
}

/*
public mixed
query_prop(string prop)
{
    object pobj = previous_object();
    string verb = query_verb();

    // A different prop is desired. Give it. 
    if (prop != LIVE_I_NEVERKNOWN)
        return shadow_who->query_prop(prop);

    if (!objectp(pobj))
    {
        if (objectp(previous_object(-1)))
            pobj = previous_object(-1);
        else
            pobj = this_player();
    }

    // Wizards can see us always 
    if (pobj->query_wiz_level())
        return 0;

    // Our hood isn't closed, don't bother with anymore checks. 
    if (!shadow_who->query_prop(RANGERS_MASK_CLOSED))
        return shadow_who->query_prop(LIVE_I_NEVERKNOWN);

    // let players who remember us see us on last and who lists 
    if (member_array(verb, ({ "last", "who" }) ) > -1)
        return shadow_who->query_prop(prop);

    // This person knows me. 
    if (member_array(shadow_who->query_real_name(), 
        pobj->query_prop(RANGERS_AS_KNOWN)) != -1)
        return 0;

    return 1;
}
*/