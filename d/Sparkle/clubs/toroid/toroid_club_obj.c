/* created by Arman March 2021
 * 
 * This is the guild object for the anglers club.
 *
 */
inherit "/std/receptacle";
inherit "/lib/keep";
inherit "/lib/wearable_item";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <cmdparse.h>
#include <state_desc.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"
#include "fishing.h"

/*prototypes*/
void soul(object ob);
public int valid_owner();
object wearer;

string 
query_auto_load() 
{
    return MASTER_OB(TO);
}

void
check_if_owner_still_member()
{
    if (!environment() || !living(environment()))
	return;
    
    if (!IS_ANGLER(TP))
    {
	remove_object();
    }
}

/*
 * Function name: valid_owner
 * Description  : Checks whether the owner has the rights to this object
 */
public int 
valid_owner()
{
    object user = this_player();
    if (!IS_ANGLER(user)) 
    {
        return 0;
    }

    return 1;
}

public void
create_receptacle()
{
    set_keep();
    set_name("satchel");
    set_name("_angler_club_object_");
    set_pname("_angler_club_object_s");

    set_adj("bait");

    set_short("bait satchel");
    set_pshort("bait satchels");
    set_long("A large wicker satchel made from thick flexible reeds, " +
        "it is used by members of the anglers club for storing " +
        "fishing bait of all types. For more information about " +
        "fishing check <help angler club>.\n");

    set_slots(A_ANY_HIP);
    set_looseness(20);
    set_layers(1);
    set_wf(TO);

    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_CLOSED, 0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_LIGHT, 0);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1); 

    setuid();
    seteuid(getuid());
}

public mixed 
remove(object ob)
{
    wearer->remove_subloc("the_angler_club");
    wearer = 0;    

    return 0;
}

public mixed 
wear(object ob)
{
    if (ob != this_object())
    {
        return -1;
    }

    wearer = TP;
    TP->add_subloc("the_angler_club", TO);

    return 0;
}

public string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
}

public int
prevent_enter(object ob)
{
    if(!ob->id("_fishing_bait"))
    {
        write("The satchel is for fishing bait only.\n");
        return 1;
    }
    return 0;
}

void
remove_guild_object()
{
    remove_object();
}

public void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);
    mixed oblist;

    if (ob)
    {
	oblist = FIND_STR_IN_OBJECT("all _angler_club_object_s", ob);
	oblist -= ({ 0, TO });
	if(oblist && sizeof(oblist) > 0)
	    set_alarm(2.0, 0.0, &remove_guild_object());
    }

    if (!interactive(ob) || from)
	return;

    if(!valid_owner())
    {
        set_alarm(0.1, 0.0, &remove_guild_object());
        return;
    }

    set_alarm(1.0, 0.0, &soul(ob));
    
    setuid();
    seteuid(getuid());
}

/*
 * Function name: soul
 * Description:   Add the cmdsoul to the member
 */
void
soul(object ob)
{
    int i;
    string *souls;
    
    setuid();
    seteuid(getuid(TO));

    souls = ob->query_cmdsoul_list();

    for (i = 0; i < sizeof(souls); i++)
	ob->remove_cmdsoul(souls[i]);

    for (i = 0; i < sizeof(souls); i++)
	if (souls[i] != CLUB_SOUL)
	    ob->add_cmdsoul(souls[i]);

    ob->add_cmdsoul(CLUB_SOUL);
    ob->update_hooks();
}

string
query_fishing_title(object angler)
{
    int club_stat = FISHING_CLUB_STAT(angler);
    string title = SD_LANG_FILE->get_num_level_desc(club_stat, 
        FISHING_AV_LEVELS, FISHING_AV_TITLES);

    return title;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    string title = query_fishing_title(me);

    if (!IS_ANGLER(me))
	return "";

    if (for_obj == me)
        return  "You are " +LANG_ADDART(title)+ " fishing hobbyist.\n";
    else
        return capitalize(me->query_pronoun()) + " is " +LANG_ADDART(title)+ 
            " fishing hobbyist.\n";    
}

public string
query_bait_quality_description(object ob)
{
    string str;
    int val = ob->query_bait_value();

    switch(val)
    {
        case 0:
            str = "very poor";
        break;
        case 1..5:
            str = "basic";
        break;
        case 6..10:
            str = "good";
        break;
        case 11..19:
            str = "excellent";
        case 20:
            str = "fantastic";
        break;
        default:
            str = "unknown";
        break;
    }

    return str;
}

void 
describe_contents(object fo, object *obarr)
{
    if (sizeof(obarr) == 0)
    {
        fo->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
        return;
    }

    if (sizeof(obarr) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "                    Bait                                    Quality       Qty  \n" +
            "+-----------------------------------------------------+-----------------+-----+\n");
        foreach(object bait : obarr) 
        {
            int quantity = 0;
            string quality = query_bait_quality_description(bait);
            quantity += bait->num_heap() || 1;
            string bait_name = bait->query_short();
            fo->catch_tell(sprintf("| %-:51s | %-:15s | %3d |\n",
                bait_name, quality, quantity));
        }
        fo->catch_tell(
            "+-----------------------------------------------------+-----------------+-----+\n");
    }
}
