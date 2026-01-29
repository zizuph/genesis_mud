/*
 * Looting abilities for backpacks.
 * Copied from the Moria loot sack and adapted for all Shire backpacks
 * -- Finwe, October 2004
 */
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <composite.h>

inherit "/d/Shire/common/obj/backpack";
//inherit "/std/receptacle";
inherit "/d/Shire/common/lib/parse";
inherit "/d/Faerun/lib/pack_sort";

#define SHIRE_BACKPACK  "_shire_backpack"
#define ETO environment()
#define INV(x) all_inventory(x)
#define IM_PARSE_FILE   "/d/Shire/common/lib/parse"


init()
{
    ::init();
    add_action("do_loot", "packloot");
    add_action("do_loot", "pl");
}


int is_corpse(object what)

{
    return !living(what) && what->query_prop(CONT_I_IN);
}

int
is_backpack(object what)
{
    return what->id(SHIRE_BACKPACK);
}

int
do_loot(string arg)
{
    mixed  *obs;
    object *loot;
    string rest;
    object pack;
    string pack_name = "backpack";

    FIXEUID;

    notify_fail("Usage: " + query_verb() +" <corpse> [with <" + pack_name + ">]\n");
/*
    if (ETO != TP)
    return notify_fail("You must wear the " + pack_name + " to loot corpses.\n");
*/
    if (!strlen(arg))
    arg = "corpse";

    if (parse_command(arg, INV(ENV(TP)),
               "%i 'in' / 'into' / 'with' / 'using' [the] %s",
              obs, rest))
    {
        loot = VISIBLE_ACCESS(obs, "is_corpse", TO);
        if (!parse_command(rest, INV(TP), "[the] %i", obs))
        return notify_fail("Loot it into which " + pack_name + "?\n");
        obs = VISIBLE_ACCESS(obs, SHIRE_BACKPACK, TO);
        if (!sizeof(obs))
        return notify_fail("Which " + pack_name + " are you referring to?\n");
        if (sizeof(obs) > 1)
        return notify_fail("You may only use one " + pack_name + " at a time\n");
        pack = obs[0];
        return pack->do_loot_one(loot, rest);
    }
    else {
    loot = IM_PARSE_FILE->parse_environment_items(arg, "");
    if (!sizeof(loot))
        return 0;
    loot = filter(loot, "is_corpse", TO);
    if (!sizeof(loot))
        return 0;
    return TO->do_loot_one(loot, "loot pack");
    }
}

int move_to(object what)
{
    if (!objectp(what))
      return 0;
    if( what->move(TO) != 0 )
      return 0;

    return 1;
}

int
do_loot_one(object *loot, string name)
{
    int i, j;
    object *thing;
    object *got;

    if (query_prop(CONT_I_CLOSED))
    return notify_fail("Perhaps open the " + name + " first?\n");

    i=sizeof(loot);

    if (!i)
    return 0;

    write("You loot " + COMPOSITE_DEAD(loot) + " using your "+name+".\n");
    say(QCTNAME(TP) + " starts looting " + QCOMPDEAD + ".\n");

    while (i--) {
    if (!objectp(loot[i]))
        continue;

    thing = all_inventory(loot[i]);
    j = sizeof(thing);

    if (!j) {
        write("The " + loot[i]->short() + " is empty.\n");
        continue;
    }

    got = filter(thing, "move_to", TO);

    if (!sizeof(got))
        write("You couldn't loot anything from the " + loot[i]->short() + ".\n");
    else {
        write("You loot " + COMPOSITE_DEAD(got) + " from the " +
          loot[i]->short() + " into " + name + ".\n");
        say(QCTNAME(TP) + " loots " + QCOMPDEAD + " from the " +
        loot[i]->short() + ".\n");
    }
    }
    return 1;
}
