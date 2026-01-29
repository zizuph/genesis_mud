/**********************************************************************
 * - tunic.c                                                        - *
 * - Tunic's for                                                    - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Updated by Damaris 6/2003                                      - *
 * - Updated by Zhar 4/2015                                         - *
 **********************************************************************/

#pragma strict_types

#include "guild.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";

public string
query_auto_load()
{
    return MASTER + ":";
}

public string
query_recover()
{
    return 0;
}

public varargs string
long(string str, object for_obj)
{
    string res = ::long(str, for_obj);
    
    if (!objectp(for_obj))
        for_obj = this_player();

    if (str || !IS_MEMBER(for_obj))
        return res;
    
    return res + "Use <clhelp> to guide you in the ways of the Clans.\n";
}

public void
create_object()
{
    set_name( ({"tunic","tunic","shirt","clothing"}) );
    add_name(OBJECT_ID);
    set_layers(1);
    set_looseness(10);
    set_wf(this_object());
    set_slots(A_BODY | A_ARMS);
    add_prop(OBJ_M_NO_DROP, "Oddly enough, you can't seem to do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high for you to "
        + "simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 100);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != GUILD_SUBLOC)
        return this_player()->show_subloc(subloc, on, for_obj);

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == on)
    {
        return "You proudly wear your "
            + short()
            + ", displaying your clan colours.\n";
    }

    return on->query_The_name(for_obj)
        + " is wearing "
        + LANG_ADDART(short())
        + " of the Clans.\n";
}

int
tug_hem(string str)
{
    if(this_player() != query_worn())
        return 0;
        
    if((str == "tunic"))
    {
        notify_fail("Tug tunic perhaps?\n");
    
        return 0;
    }

    write("You discreetely tug on the hem of your tunic.\n");

    say(QCTNAME(TP)
        + " discreetely tugs on the hem of "
        + HIS(TP) 
        + " tunic.\n");

    return 1;
}

int
brush_tunic(string str)
{
    if(this_player() != query_worn())
        return 0;

    if((str != "tunic"))
    {
        notify_fail("Brush tunic perhaps?\n");
    
        return 0;
    }

    write("You brush the dirt from your tunic.\n");

    say(QCTNAME(TP)
        + " brushes the dirt from "
        + HIS(TP)
        + " tunic.\n");

    return 1;
}

int
adjust_tunic(string str)
{
    if(this_player() != query_worn())
        return 0;

    if((str != "tunic"))
    {
        notify_fail("Adjust tunic perhaps?\n");

        return 0;
    }

    write("You adjust your tunic.\n");

    say(QCTNAME(TP)
        + " adjusts "
        + HIS(TP)
        + " tunic.\n");

    return 1;
}

void
init()
{
    mixed tmp;
    ::init();
    add_action(tug_hem, "tug");
    add_action(brush_tunic, "brush");
    add_action(adjust_tunic, "adjust");

    if (!living(environment()))
        return;

    setuid();
    seteuid(getuid());

    tmp = (string)SERVER->query_clan(ENV(TO)->query_real_name());

    if (!strlen(tmp))
    {
        set_adj(tmp = ({ "soft", "brown" }));
        set_short("soft brown tunic");
        set_pshort("soft brown tunics");
    }
    else
    {
        set_adj(tmp = (string)SERVER->query_clan(tmp)[CLAN_CLRS]);
        set_short(implode(tmp, " and ")
            + " tunic");
        set_pshort(implode(tmp, " and ")
            + " tunics");
    }

    add_adj("wool");
    set_long("This woolen tunic is commonly worn by humans from "
        + "Khalakhor. The trim and collar of the tunic is "
        + (tmp[0] == "soft" ? "a soft brown colour" : tmp[0])
        + " with the rest dyed "
        + (tmp[1] == "brown" ? "brown as well" : tmp[1])
        + ".\n");
}
