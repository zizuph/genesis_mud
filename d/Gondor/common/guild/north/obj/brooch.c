#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../lib/ranger_defs.h"

string  ranger_name;

void
create_object()
{
    set_name("brooch");
    add_name("star");
    add_name(({"ranger_brooch", "North_Ranger_Brooch"}));
    add_name("ranger_guild_object");
    set_adj("silver");
    add_adj("many-pointed");
    add_adj("star-shaped");
    set_short("@@my_short@@");
    set_long("@@my_long@@");
    set_slots(A_L_SHOULDER);
    set_layers(0);
    set_looseness(10);
    set_wf(TO);
    add_prop(OBJ_M_NO_DROP, 1);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

string my_short()
{
    if (TP == environment(TO)) 
        return "silver brooch shaped like a many-pointed star";
    return "silver star-shaped brooch";
}  

string my_long()
{
    if (TP == environment(TO)) 
    {
        if (IS_NRANGER(TP))
        {
            return BSN("This is a brooch of silver shaped like a rayed star. "+
                   "It is the proof of your membership in the Rangers of the North. "+
                   "On the backside is enscribed: "+ranger_name+", Ranger of the North.");
        }
        return BSN("This is a brooch of silver shaped like a rayed star. "+
               "On the backside is enscribed: " + ranger_name + ", Ranger of the North.");
    }
    if (IS_NRANGER(TP))
        return BSN("It is an brooch of silver shaped like a rayed star, the "+
               "symbol of the Rangers of the North, which someone must have dropped.");
    return BSN("It is an brooch of silver shaped like a rayed star.");
}

mixed
wear(object ob)
{
    if (IS_NRANGER(TP) || TP->query_wiz_level())
    {
        write("You wear the silver star-shaped brooch upon your left shoulder"
          + (TP->query_armour(A_ROBE)->id("_RoN_cloak_") ?
             ", fastening it to your grey cloak" : "") + ".\n");
        say(QCTNAME(TP)+" wears a silver brooch shaped like a many-pointed "
          + "star upon " + POSSESSIVE(TP) + " left shoulder"
          + (TP->query_armour(A_ROBE)->id("_RoN_cloak_") ?
            ", clasping it to " + POSSESSIVE(TP) + " grey cloak" : "")
          + ".\n", TP);
        wearer = TP;
        return 1;
    }
    return "You try to wear the brooch, but it just drops off!\n";
}

mixed
remove(object ob)
{
    wearer->catch_msg("You take the silver star-shaped brooch off your "
      + (wearer->query_armour(A_ROBE)->id("_RoN_cloak_") ?
         "grey cloak" : "left shoulder") + ".\n");
    say(QCTNAME(wearer) + " removes the silver star-shaped brooch from "
      + POSSESSIVE(wearer) + " left shoulder.\n", wearer);
    return 1;
}

void
init_brooch(object pl)
{
    FIX_EUID
    ranger_name = NORTH_MASTER->query_ranger_name(pl->query_real_name());
    if (!strlen(ranger_name))
        ranger_name = pl->query_name();
    pl->add_cmdsoul(NRANGER_SOUL);
    pl->update_hooks();
}

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);
    if (IS_NRANGER(TP) && !strlen(ranger_name))
        set_alarm(0.0, 0.0, &init_brooch(TP));
}

string query_auto_load()
{
    return MASTER + ":";
}

int query_recover()
{
    return 0;
}

