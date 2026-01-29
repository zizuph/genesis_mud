#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/rituals/shadows/std_enchantment";

#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <language.h>

#define HOOD    "/d/Ansalon/guild/new_pot/rituals/shadows/conceal_shadow.c"
#define EMOTES  "/d/Ansalon/guild/new_pot/rituals/shadows/vestment_emotes.c"

mapping original_robe = ([]);
object  emotes;
string gColour;

/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

/* added to test cosmetic enchantment */
public int query_cosmetic() { return 1; }

string
query_colour(object player)
{
    switch (player->query_priest_level())
    {
        case GUILD_LEVEL_PRIEST:
            gColour = "deep blue";
            break;
        case GUILD_LEVEL_HIGH_PRIEST:
            gColour = "dark purple";
            break;
        case GUILD_LEVEL_INITIATE:
        default:
            gColour = "dark green";
            break;
    }
    
    return gColour;
}

string
wizinfo_extra()
{
    return "Adds basic guild robe descriptions to a new robe.\n";
}

string
query_strength_desc()
{
    switch (query_enchantment_strength())
    {
        case 1..15:
            return "weak";
        case 16..30:
            return "somewhat powerful";
        case 31..50:
            return "powerful";
        case 51..75:
            return "very powerful";
        case 76..90:
            return "extremely powerful";
        case 91..100:
            return "vastly powerful";
    }
}

mixed *
query_identify_info()
{
    return ({
        "An illusory effect has been cast upon the robe to shroud its " +
        "appearance.\n", 10,
        "The enchantment laid upon the robe seems " +
        query_strength_desc() + ".\n", 30,
        });
}

void
warn_effect_dimnishing()
{
    if (objectp(shadow_who->query_worn()))
        shadow_who->query_worn()->catch_msg("The " + shadow_who->short() +
        " flickers, briefly revealing " + LANG_ADDART(original_robe["short"]) +
        ". The enchantment appears to be wearing off.\n");
}

mixed
enchant_object(object obj)
{
    string worn;
    int robe_time;
    
    if (query_enchanted_object_type() != 2 || obj->query_at() != A_ROBE)
        return "This enchantment can only affect robes!";

    original_robe["names"]  = obj->query_names();
    original_robe["adjs"]   = obj->query_adjs();
    original_robe["short"]  = obj->query_short();
    original_robe["long"]   = obj->query_long();
    
    obj->set_name("robe");
    obj->set_adj(({"deep-black", "shimmering"}));
    obj->set_short("deep-black shimmering robe");
    obj->set_pshort("deep-black shimmering robes");
    obj->set_long("This is a long robe made of rich velvet fabric. It has " +
    "an iridescent black colour which shifts in green, blue and deep purple " +
    "like that of beetle wings, making it look alive. An intricate " +
    "embroidery of a five-headed multi-coloured dragon adorns the back. " +
    "The lining is made of fine deep black-coloured velvet. The " +
    "large hood and wide sleeves are lined with a two-inch wide band of the " +
    "same material and on the left side is a crescent of deepest black. You " +
    "notice a small caption on the inside of one of the sleeves that you " +
    "could possibly read.\n");

    robe_time = 10000 + (40 * query_enchantment_strength());
    set_enchantment_duration(robe_time);
    
    set_alarm(itof(robe_time - 1800), 0.0, &warn_effect_dimnishing());
    
    return 0;
}

varargs void
remove_enchantment(int quiet)
{
    object obj = query_enchanted();
    
    if (member_array("robe", original_robe["names"]) < 0)
        obj->remove_name("robe");
    
    if (member_array("deep-black", original_robe["adjs"]) < 0)
        obj->remove_name("deep-black");
    
    if (member_array("shimmering", original_robe["adjs"]) < 0)
        obj->remove_name("shimmering");
    
    obj->set_short(original_robe["short"]);
    obj->set_pshort(LANG_PWORD(original_robe["short"]));
    obj->set_long(original_robe["long"]);
    
    if (objectp(obj->query_worn()))
        obj->query_worn()->remove_robe_hood_shadow();
    
    if (objectp(emotes))
        emotes->remove_object();
    
    
    remove_shadow();
    
}

mixed
wear(object what)
{
    string gColour;
    
    if (!objectp(safely_load_master_file(HOOD)))
        return "The magic in the robe repels your presence.\n";
    
    clone_object(HOOD)->shadow_me(this_player());
    this_player()->init_priest_robe();
    
    if (objectp(safely_load_master_file(EMOTES)))
    {
        gColour = query_colour(this_player());
        emotes  = clone_object(EMOTES);
        emotes->move(environment(shadow_who), 1);
        emotes->set_colour(gColour);
    }
    
    return ::wear(what);
}

int
remove(object ob)
{
    this_player()->remove_robe_hood_shadow();
    emotes->remove_object();
    
    return ::remove(ob);
}

/*
 * Function name: leave_env
 * Description  : Called when the robe leaves its environment.
 */
public void
leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);
    
    if (!living(to) || !to->query_pot_member())
        remove_enchantment();
}

public int
query_takhisis_guild_item()
{
    return 1;
}