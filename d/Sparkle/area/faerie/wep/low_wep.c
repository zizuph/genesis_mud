/*
 * Sword for graveyard. Based on the Sparkle orc sword.
 * Finwe, April 2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 10,
    pen = 13;


public void
create_weapon()
{
    string *adjectives, *wep_type, adj, adj1, wep;

    adjectives = ({"ancient", "chipped", "corroded", "dull", "heavy", 
        "lethal", "long", "old", "rusty", "vicious"});
    wep_type = ({"sword", "axe", "knife", "dagger"});

    wep = wep_type[random(sizeof(wep_type))];
    adj = adjectives[random(sizeof(adjectives))];
    adj1 = adjectives[random(sizeof(adjectives))];
    while (adj1 == adj)
    {
        adj1 = adjectives[random(sizeof(adjectives))];
    }

    set_hit(hit);
    set_pen(pen);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen));
    set_adj(adj);
    set_adj(adj1);

    switch(wep)
    {
        case "sword": 
        {
            set_name("sword");
            add_name ("longsword");
            set_short(adj + " " + adj1 + " longsword");

            set_wt(W_SWORD);
            set_dt(W_IMPALE | W_SLASH);
            set_hands(W_NONE);
            set_long("The " + short() + " looks like it once belonged " +
                "to someone important. Nontheless, it still looks deadly.\n");
            break;
        }
        case "axe": 
        {
            set_name("axe");
            set_short(adj + " " + adj1 + " axe");

            set_wt(W_AXE);
            set_dt(W_BLUDGEON | W_SLASH);
            set_hands(W_NONE);
            set_long("The " + short() + " is ancient yet dangerous looking. " +
                "The axe looks like it is still deadly, even though " +
                "the blade is rusted and the handle is rotted.\n");
            break;
        }

        case "knife":
        {
            set_name("knife");
            set_short(adj + " " + adj1 + " knife");

            set_wt(W_KNIFE);
            set_dt(W_IMPALE | W_SLASH);
            set_hands(W_NONE);
            set_long("The " + short() + " looks like it was made many " +
                "ages ago. It appears to have been fashioned by elves.\n");
            break;
        }

        case "dagger": 
        {
            set_name("dagger");
            set_short(adj + " " + adj1 + " dagger");

            set_wt(W_KNIFE);
            set_dt(W_IMPALE | W_SLASH);
            set_hands(W_NONE);
            set_long("The " + short() + " looks old and rusty. It seems " +
                "dull but probably able to do some damage in the proper " +
                "hand.\n");
            break;
        }
    }

}
