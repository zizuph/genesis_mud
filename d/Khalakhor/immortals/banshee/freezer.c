#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
#include <ss_types.h>
#define FREEZER_NAME   "_banshee_freezer"
#define WARMUP_TIME    120

inherit "/std/shadow";

string type;
object victim;
int break,
    orig_break;

public varargs int
shadow_me(mixed to_shadow)
{
    if (!::shadow_me(to_shadow))
        return 0;

    if (shadow_who->check_armour())
    {
        type = "armour";
        victim = shadow_who->query_worn();
    }
    else
    {
        type = "weapon";
        victim = shadow_who->query_wielded();
    }
    break = 0;
    orig_break = shadow_who->query_likely_break();
} 

public void
change_message(string how)
{
    if (!victim)
        return;

    if (type == "armour")
    {
        if (!shadow_who->query_worn())
        {
            victim = 0;
            return;
        }
        else if (shadow_who->query_worn() != victim)
        {
            victim = shadow_who->query_worn();
        }
    }
    else
    {
        if (!shadow_who->query_wielded())
        {
            victim = 0;
            return;
        }
        else if (shadow_who->query_wielded() != victim)
        {
            victim = shadow_who->query_worn();
        }
    }

    if (how == "colder")
        victim->catch_msg("Your " + shadow_who->short() + 
            " becomes even colder!\n");
    else
        victim->catch_msg("Your " + shadow_who->short() +
            " seems to warm up a bit.\n");
}
      
public void
increase_break()
{
    if (break)
        change_message("colder");
    break = (break >= 100 ? 100 : break + 25);
    shadow_who->set_likely_break(break + orig_break);
}

public void
decrease_break()
{
    if (!break)
        return;
    break = (break <= 0 ? 0 : break - 25);
    shadow_who->set_likely_break(break + orig_break);
    change_message("warmer");
}
