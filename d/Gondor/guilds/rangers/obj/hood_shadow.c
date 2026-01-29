/*
 * The shadow for the cloak hood
 *
 * 960117 by Rastlin
 *   Modification Log:
 *     Elessar, 1998.
 *     Alto, February 2002. Modified for ranger recode.
 *     Toby, 29 Nov, 2006  : Removed query_prop so that players are always known. 
 *                           (Need to check that this holds true and nothing more
 *                            needs fixing.)
 *                           Change needed on orders from the Admin. No player
 *                           may no longer use LIVE_I_NEVERKNOWN.
 */

#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit "/std/shadow";

#define EYES_SUBLOC         "eyes"
#define HAIR_SUBLOC         "hairstyle"
#define RANGERS_AS_KNOWN     "_rangers_as_known"
#define RANGERS_HOOD_CLOSED "_rangers_hood_closed"
#define RANGERS_I_INCOGNITO "_rangers_incognito"

static string *gAdjs;

public void
set_colour(string colour)
{
    if (!strlen(colour))
        gAdjs = ({ "cloaked", "hooded" });
    else
        gAdjs = ({ colour + "-cloaked", "hooded" });
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

    if(caller[0..8]== "/d/Avenir")
        return 0;
    return 1;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc == EYES_SUBLOC || subloc == HAIR_SUBLOC)
        return "";
    else return shadow_who->show_subloc(subloc, me, for_obj);
}

public string
show_scar(mixed for_obj)
{
    return "";
}
/*
public mixed
query_prop(string prop)
{
    // A different prop is desired. Give it. 
    if (prop != LIVE_I_NEVERKNOWN)
        return shadow_who->query_prop(prop);

    // Our hood isn't closed, don't bother with anymore checks. 
    if (!shadow_who->query_prop(RANGERS_HOOD_CLOSED))
        return shadow_who->query_prop(LIVE_I_NEVERKNOWN);

    // Wizards can see us always
    if (previous_object()->query_wiz_level())
        return 0;

    // This person knows me. 
    if (member_array(shadow_who->query_real_name(), 
      previous_object()->query_prop(RANGERS_AS_KNOWN)) != -1)
        return 0;

    return 1;
}
*/
