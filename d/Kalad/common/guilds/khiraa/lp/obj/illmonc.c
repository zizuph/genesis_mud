/*
    illmonc.c
    
    Control thingy for lphantasm spell.
            
    Sarr
    Recoded and balanced by Fysix, April 1998
 */
#include "../../default.h"
#include "../../khiraa.h"
#include "../../magic.h"
#include <composite.h>

inherit "/std/object";
inherit SPELL_EFFECT_OBJECT;

object *monsters = ({});
int mana_up_keep = 10;

void dispel();

// Remove all 0 entries from the monsters array
object*
clean_monsters(object *monsters)
{
    return filter(monsters, objectp);
}

void
mana_drain()
{
    // Check if our phantasms still exist
    monsters = clean_monsters(monsters);
    if (!sizeof(monsters))
    {
        remove_object();
        return;
    }

    // mana check    
    if (ENV(TO)->query_mana() < mana_up_keep)
    {
        tell_object(ENV(TO), "You no longer have the mana to keep up " +
            "your phantasms!\n");
        dispel();
        return;
    }

    ENV(TO)->add_mana(-mana_up_keep);
    set_alarm(60.0, 0.0, &mana_drain());
}

int
do_dispel()
{
    write("You release your illusional monsters.\n");
    dispel();

    return 1;
}

int
do_attack(string str)
{
    int res, i;

    monsters = clean_monsters(monsters);

    res = 1;
    for (i = 0; i < sizeof(monsters); i++)
        if (!monsters[i]->command("$kill " + str))
            res = 0;

    return res;
}

void
init()
{
    ::init();
    add_action(do_dispel, "illdispel");
    add_action(do_attack, "illkill");
}

void
create_object()
{
    set_name("_illmonc_");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 0);
    set_no_show();
    set_alarm(60.0, 0.0, &mana_drain());
}

void
add_monster(object monst)
{
    string lm;

    monsters += ({ monst });
    lm = ENV(TO)->query_m_out();
    mana_up_keep += 5;
    monst->trig_new("%s '" + lm + "' %s", "check");
}

void
dispel()
{
    int i;

    monsters = clean_monsters(monsters);
    for (i = 0; i < sizeof(monsters); i++)
    {
        if (objectp(monsters[i]))
        {
            monsters[i]->destruct_shadows();
            tell_room(ENV(monsters[i]), "The " + monsters[i]->short() +
                " explodes in a shower of white sparks!\n");
            monsters[i]->remove_object();
         }
    }
    remove_object();
}

// This spell can be dispelled.
varargs public int
dispel_spell_effect(object dispeler)
{
    monsters = clean_monsters(monsters);
    if (sizeof(monsters))
    {
        // Give some messages
        dispeler->catch_msg("You dispel the " + COMPOSITE_LIVE(monsters) +
            ".\n");
        ENV(TO)->catch_msg("Your " + COMPOSITE_LIVE(monsters) + " " +
            (sizeof(monsters) > 1 ? "are" : "is") + " dispelled by " +
            QCTNAME(dispeler) + ".\n");
        tell_room(ENV(dispeler), QCTNAME(dispeler) + " dispels the " +
            COMPOSITE_LIVE(monsters) + ".\n", ({dispeler, ENV(TO)}));
    }
    else
    {
        dispeler->catch_tell("There were no illusional monsters to " +
            "dispel.\n");
    }

    dispel();
    return 1;
}
