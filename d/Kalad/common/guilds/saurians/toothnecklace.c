/*
 * Guild item for the Saurians of Kalad
 * Mirandus - Feb, 2018
 */
#pragma save_binary
#pragma strict_types
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";
inherit "/lib/help";
#include "lizards.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

#define SAURIAN_SUBLOC "saurian_subloc"

/*
 * Function name: query_auto_load()
 * Description  : Checks if this object should be loaded at login
 * Arguments    : None
 */
string
query_auto_load()
{
  return MASTER;
}

/*
 * Function name: create_object()
 * Description  : Creates the object.
 * Arguments    : None
 */
void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_help_dir(GUILD_HELP);
    set_help_category(({"saurian", "lizard", "saurians"}));
    set_help_default("all");
    set_name("necklace");
    set_adj(({"jagged tooth", "jagged", "tooth"}));
    add_name(MEDALLION_NAME);
    set_short("jagged tooth necklace");
    set_long("This is a " + query_short() + " made from teeth of fallen " +
        "Saurians. It represents your bond with the Saurians and your " +
        "recognition of the ancestry that came before you. These teeth " +
        "represent those of your line who have passed. One day your tooth " +
        "shall be added to the string and it will be passed down. Type " +
        "<help saurian> to learn more about the guild.\n");
    set_wf(this_object());
    set_slots(A_NECK);
    add_prop(OBJ_I_NO_DROP,"This is too valuable of an object to lose.\n");
    add_prop(OBJ_S_WIZINFO, "Saurian Racial Guild Item.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
      "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 10);
}

/*
 * Function name: show_subloc
 * Description  : Shows the subloc for the player when wearing their
 *                necklace.
 * Arguments    : string subloc - The subloc shown for the player
 *                object on     - The player wearing the object
 *                object for_obj - This object.
 */
public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    string ssurname;
    
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    
    if (SURNAME_MANAGER->query_saurian_surname(on) == 0)
    {
        ssurname = "that ancient race";
    }
    
    else 
       ssurname = SURNAME_MANAGER->query_saurian_surname(on);
    
    if (for_obj == on)
        return  "You are a Saurian, a descendant of "+ ssurname +".\n";
        
    else
        ssurname = SURNAME_MANAGER->query_saurian_surname(on);
        if (SURNAME_MANAGER->query_saurian_surname(on) == 0)
        {
            ssurname = "that ancient race";
        }
        return (capitalize(on->query_pronoun())) + " is a Saurian, "
        + "a descendant of "+ ssurname +".\n";
}

/*
 * Function name: wear
 * Description  : Does stuff when we wear this object
 * Arguments    : Object wep - The object
 *                Object wearer - The player wearing the object.
 */
public mixed
wear(object wep)
{
    object wearer = TP;
    say(QCTNAME(wearer) +" proudly wears "+ HIS(this_player())+" " 
    + this_object()->query_short() +".\n");
    
    wearer->add_subloc(SAURIAN_SUBLOC, TO);
    
    write("You proudly wear your " + this_object()->query_short() + 
    " around your neck.\n");
    return 1;
}

/*
 * Function name: wear
 * Description  : Does stuff when we remove this object
 * Arguments    : Object wep - The object
 *                Object wearer - The player wearing the object.
 */
public mixed
remove(object wep)
{
    object wearer = TP;
    say(QCTNAME(wearer) + " removes "+HIS(this_player())+" "+
    this_object()->query_short() +".\n");
    
    wearer->remove_subloc(SAURIAN_SUBLOC);
    
    write("You remove your "+ this_object()->query_short() + " from around "
    +"your neck.\n");
    return 1;
}    

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 */   
public void
enter_env(object dest,object old)
{
    remove_name(MEDALLION_NAME);
    if(present(MEDALLION_NAME,E(TO)))
    {
        tell_room(E(TO),"You throw the duplicate necklace away.\n");
        remove_object();
        return;
    }
    add_name(MEDALLION_NAME);

}

void
init()
{
    ::init();
}