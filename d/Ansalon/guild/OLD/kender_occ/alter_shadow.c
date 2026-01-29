#pragma strict_types
#pragma save_binary

inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <language.h>

#include "guild.h"

static mapping hoopak = ([]);
static mapping weapon = ([]);

int
inside(string map)
{
    if (member_array(map, m_indexes(hoopak)) > -1)
        return 1;
    
    return 0;
}

public int
alter_reverse(object player)
{
    string hoopak_short = shadow_who->short();
    
    foreach(string map, mixed value: hoopak)
    {
        switch(map)
        {
            case "names":
            shadow_who->remove_name(hoopak[map]);
            shadow_who->add_name(weapon[map]);
                break;
            case "adjs":
            shadow_who->remove_adj(hoopak[map]);
            shadow_who->set_adj(weapon[map]);
            
            if (objectp(shadow_who->query_wielded()))
                shadow_who->set_adj("wielded");
            else
                shadow_who->set_adj("unwielded");
            
                break;
            case "short":
            shadow_who->set_short(weapon[map]);
                break;
            case "p_short":
            shadow_who->set_pshort(weapon[map]);
                break;
            case "long":
            shadow_who->set_long(weapon[map]);
                break;
            default:
                break;
        }
    }
    
    player->catch_msg("As you finish peeling of the ornaments from the " +
    hoopak_short + ", you are left with its original and less exciting " +
    "state. The " + shadow_who->short() + " has been restored.\n");
    
    tell_room(environment(player), QCTNAME(player) + " peels away " +
    "the ornaments from the " + hoopak_short + ", revealing " +
    LANG_ADDART(shadow_who->short()) +  "\n", player);
    
    remove_shadow();
}

public int
set_hoopak(string map, mixed value)
{
    hoopak[map] = value;
    
    if (inside(map))
        return 1;
    
    return 0;
}

public object
query_wf()
{
    return this_object();
}

void
kender_wield()
{
    if (shadow_who->query_wielded())
    {
        shadow_who->query_wielded()->catch_tell("You feel at ease with the " +
        "hoopak as you grip your fingers around it. You give it a little " +
        "swing to test it out.\n");
        shadow_who->query_wielded()->command("$swing hoopak");
    }
}

void
default_wield()
{
    if (shadow_who->query_wielded())
        shadow_who->query_wielded()->catch_tell("You feel somewhat foolish " +
        "wielding a weapon designed for kender.\n");
}

mixed
wield(object what)
{    
    if (this_player()->query_race_name() == "kender")
        set_alarm(1.0, 0.0, &kender_wield());
    else
        set_alarm(1.0, 0.0, &default_wield());
    
    return 0;
}

int
query_std_hoopak()
{
    return 1;
}

void
init_hoopak_shadow(object player)
{
    object sling;

    foreach(string map, mixed value: hoopak)
    {
        switch(map)
        {
            case "names":
            weapon[map] = shadow_who->query_names();
            shadow_who->remove_name(weapon[map]);
            shadow_who->add_name(hoopak[map]);
                break;
            case "adjs":
            if (objectp(shadow_who->query_wielded()))
                shadow_who->remove_adj("wielded");
            else
                shadow_who->remove_adj("unwielded");
            
            weapon[map] = shadow_who->query_adjs();
            shadow_who->remove_adj(weapon[map]);
            shadow_who->set_adj(hoopak[map]);
            
            if (objectp(shadow_who->query_wielded()))
                shadow_who->set_adj("wielded");
            else
                shadow_who->set_adj("unwielded");
                break;
            case "short":
            weapon[map] = shadow_who->query_short();
            shadow_who->set_short(hoopak[map]);
                break;
            case "p_short":
            weapon[map] = shadow_who->query_plural_short();
            shadow_who->set_pshort(hoopak[map]);
                break;
            case "long":
            weapon[map] = shadow_who->query_long();
            shadow_who->set_long(hoopak[map]);
                break;
            default:
                break;
        }
    }
    
    if (living(player))
    {
        setuid();
        seteuid(getuid());
        
        sling  = clone_object(HOOPAK_SLING);
        sling->move(player);
        sling->set_sling(shadow_who, player);
    }
}

void
enter_env(object to, object from)
{
    object *slings = ({});

    slings = filter(all_inventory(from), &operator(>)(,0)
                    @ &->query_hoopak_sling());
    
    if (sizeof(slings))
        slings[0]->check_parameters();
    
    slings = filter(all_inventory(to), &operator(>)(,0)
                    @ &->query_hoopak_sling());
    
    if (sizeof(slings))
        return;
    
    init_hoopak_shadow(to);
}