/*
 *  /d/Gondor/guilds/rangers/obj/ranger_emblem.c
 *
 *  The emblem carried by the Rangers of the Westlands.
 *  A brooch for RoN, an amulet for RoI, and a ring for apprentices.
 *
 *  Original ranger tokens coded by Elessar.
 *
 *  Alto, February 2002.
 *
 *  Modification log:
 *  Gwyneth, 2 April 2002: Cleaned up
 *  Gwyneth, 12, July 2004: Re-Added ranger subloc code
 *  Gwyneth, 20 July 2004: Modified ranger sublocs to spread out descs more
 *
 */
inherit "/std/object";
inherit "/lib/wearable_item";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

int     Inited;
string  EmblemType, RangerName; 

int
query_value()
{
    return 0;
}

public void 
create_emblem()
{
    set_name("emblem");
    set_slots(A_ANY_FINGER);
}

public string 
set_emblem_short(object pl)
{
    return EmblemType + " emblem";
}  

public string 
set_emblem_long(object pl)
{
    return "It is a plain " + EmblemType + " emblem. You see nothing " +
        "special about it.\n";
}

public void
preserve_options()
{
}

nomask void 
create_object()
{
    add_name(({"ranger_guild_object", "emblem", "_rangers_emblem_id", 
        "ranger emblem"}));
    set_adj("ranger");
    set_short(set_emblem_short);
    set_long(set_emblem_long);

    set_wf(TO);
    add_prop(OBJ_I_VALUE,    0);
    add_prop(OBJ_I_WEIGHT,   20);
    add_prop(OBJ_I_VOLUME,   10);
    add_prop(OBJ_I_NO_DROP,  1);
    add_prop(OBJ_I_NO_STEAL, 1);
    set_looseness(5);
    set_layers(1);
    seteuid(getuid(TO));
    create_emblem();
}

public string
query_recover()
{
    return 0;
}

public int
query_ranger_emblem()
{
    return 1;
}

public void
enter_env(object env, object from)
{
    object *doubles;

    doubles = all_inventory(env) - ({ this_object() });
    doubles = filter(doubles, &->query_ranger_emblem());
    if (sizeof(doubles))
        doubles->remove_object();

    ::enter_env(env, from);
}


public mixed 
wear(object ob)
{
    if (RANGERS_MEMBER(TP)) 
    {
        write("You wear the " + EmblemType + " ring on your finger.\n" +
            "It feels good to be back with the Rangers of the Westlands.\n");
        say(QCTNAME(TP) + " wears the " + 
            (stringp(EmblemType) ? EmblemType : "") + " ring on " + 
            POSSESSIVE(TP) + " finger.\n", TP);
        this_player()->add_subloc(RANGER_S_SUBLOC, TO);
        return 1;
    }

    return "You try to wear the ring, but it just doesn't fit!\n";
}

public mixed
remove(object ob)
{
    this_player()->remove_subloc(RANGER_S_SUBLOC, TO);
    return 0;
}

public string 
describe_emblem(object pl)
{
    int lvl;
    lvl = pl->query_stat(SS_OCCUP);  

    switch (lvl)
    {
    case   0..9: return "brass";    break;
    case 10..19: return "copper";   break;
    case 20..29: return "iron";     break;
    case 30..39: return "bronze";   break;
    case 40..49: return "steel";    break;
    case 50..59: return "silver";   break;
    case 60..69: return "gold";     break;
    case 70..79: return "platinum"; break;
    case 80..89: return "emerald";  break;
    case 90..99: return "mithril";  break;
    default:     return "diamond";  break;
    }
}

public void 
initiate(object pl)
{
    Inited = 1;
    RangerName = pl->query_name();
    EmblemType = describe_emblem(pl);
    set_adj(EmblemType);
    return;
}

public void 
init()
{
    ::init();
    if (!Inited && ENV() == TP)
        set_alarm(0.0, 0.0, &initiate(TP));
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

string
show_subloc(string subloc, object me, object for_obj)
{
    int occ_stat, div;
    string str;
    object who = environment();

    if (subloc != RANGER_S_SUBLOC)
        return who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (me->query_prop("_player_i_bath"))
        return "";

    FIX_EUID;

    occ_stat = who->query_ranger_rank();
    occ_stat /= 15;

/*
    occ_stat = who->query_stat(SS_OCCUP) / 2;
    occ_stat += who->query_legend_skills() / 2;
    div = 100 / sizeof(RANGER_LOOKS);
    occ_stat /= div;
*/

    occ_stat = min(occ_stat, sizeof(RANGER_LOOKS) - 1);

    if (for_obj == me)
        str = "You are ";
    else
        str = CAP(me->query_pronoun()) + " is ";

    str += "looking " + RANGER_LOOKS[occ_stat] + ".\n";
    return str;
}

