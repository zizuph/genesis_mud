/*  Magic crystal for helping with Tyr mounts.
*   Temporarily gives the mount swim skill of 30 for 10 seconds.
*   Nov 2020, Meton.
*   Thanks to Mirandus for the merging code from the Thanar cathedral.


Problemet med write er at den defaulter til den spiller der har manipuleret den, og derfor kommer den i lplog hvis der ikke er nogen.

*/
inherit "/std/object";
inherit "/lib/keep";

#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

string mount,recover;
int swim;

create_object()
{
    add_prop(OBJ_I_WEIGHT,3);
    add_prop(OBJ_I_VOLUME,6);
    set_name(({"crystal","small"}));
    set_short("crystal");
    set_long("A deep focus crystal. This piece was carved and enhanced "
        + "by powerful psionics that had travelled the donut, and found "
        + "too much water on their journeys. Not wanting to walk, they "
        + "thought up the idea of this mental focus.\n");

    add_prop(OBJ_I_VALUE,3456);
    add_prop(OBJ_I_NO_GET,0);
    add_prop(OBJ_M_NO_SELL, "You feel connected to this crystal, it would "
        + " be a shame to have this random shopkeeper defile it!\n");

    set_keep();
}

init()
{
    ::init();
    add_action("attune","focus");
}

/*
*   Function name: attune
*   Description  : If mounted, gives mount +30 swim for 10 seconds.
*   Arguments    : 
*   Returns      : 
*/
int
attune(string s)
{
    mount = TP->query_prop(LIVE_O_STEED);
    swim = TP->query_skill(SS_SWIM);

    NF("Focus on what? The Crystal?\n");
    if(!s || s != "crystal")
    {
        return 0;
    }

    if (!mount)
    {
        write("This crystal only aids you in levitating mounts.\n");
        return 1;
    }

    if (TP->query_mana() < 10)
    {
        write("You try to focus, but lack the mental stamina for "
            + "the task.\n");
        return 1;
    }
   
    write("You focus on crystal and use your mental strength to "
        + "best levitate your mount, giving it the ability to cross "
        + "water or silt.\n");
    say(QCTNAME(TP)+" focuses on "+TP->query_possessive()+" small "
        + "crystal.\nYou think "+TP->query_possessive()+" mount seems to "
        + "hover slightly over the ground.\n");
    TP->add_mana(-10);
    mount->set_skill_extra(SS_SWIM, 30);

    set_alarm(10.0, 0.0, &mount->set_skill_extra(SS_SWIM, (-30)));
    set_alarm(10.1, 0.0, &write("Your mental focus slip, and your "
        + "concentration is lost.\n"));
    set_alarm(10.1, 0.0, &say(QCTPNAME(TP)+" mount seems to be firmly "
        + "grounded again.\n"));

    return 1;
}

/*
*   Function name: remove_shards + dedup_shards
*   Description  : Merges multiple into one item.
*   Arguments    : 
*   Returns      : 
*   Thanks to Mirandus for the code.
*   Original from Thanar Cathedral.
*/
public void
remove_shards(object *shards)
{
    if (sizeof(shards))
        shards->remove_object();
}

public void
dedup_shards(object *shards)
{
    shards -= ({ this_object() });
    
    if (sizeof(shards))
    {
        set_alarm(0.2, 0.0, &remove_shards(shards));
        set_alarm(0.2, 0.0, &tell_room(environment(), "testcrystal merge\n"));
    } 
}

public status
filter_master(object ob)
{
    return ( MASTER_OB(ob) == MASTER );
}

public object *
find_duplicates(object target)
{
    return filter(deep_inventory(target), &filter_master());
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
    ::enter_env(dest, old);
    dedup_shards(find_duplicates(dest));
    
}

string
query_recover()
{
return MASTER + ":" + query_keep_recover();
}