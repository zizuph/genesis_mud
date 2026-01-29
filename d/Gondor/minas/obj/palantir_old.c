/*
 * /d/Gondor/minas/obj/palantir.c
 *
 * The Palantir of the White Tower of Ecthelion
 *
 * Alto 5 June 2001
 *  Modification log:
 *    Fixed lower case bug in return, Alto, 08 November 2001
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Gondor/defs.h"


object actor, target, surroundings, *items;
string room, targetname;

void
create_object()
{
    set_name("globe");
    set_adj("small");
    add_adj("crystal");
    add_name("stone");
    add_name("palantir");
    add_name("palantir stone");
    set_short("small crystal globe");
    set_pshort("small crystal globes"); /* there should never be more than one */
    set_pname("globes");
    set_long("This small crystal globe is one of the famed palantiri "
        + "wrought ages ago by the Noldor in Eldamar. A person of strong will "
        + "may learn to control the globe and with it scry whomever he "
        + "wishes.\n");
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP,  1);

    seteuid(getuid(TO));
}

void
init()
{
   ::init();
   add_action("scry_stone", "scry");
}

int
scry_stone(string str)
{
    actor = TP;
    targetname = CAP(str);

    if (!strlen(str))
        NF0("Scry who?\n");

    actor->add_mana(-(actor->query_max_mana())/7);

    target = find_player(str);

    if ((actor->query_mana()) <= ((actor->query_max_mana())/7))
    {
    actor->catch_tell("You are too mentally exhausted to master "
        + "the palantir stone.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gazes into the small "
        + "crystal globe and looks visibly shaken.\n", 
        ({actor}));
    return 1;
    }

    if ((actor->query_stat(3)) <= 100)
    {
    actor->catch_tell("You do not have the strength of will to "
        + "master the palantir stone.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gazes into the small "
        + "crystal globe and looks visibly shaken.\n", 
        ({actor}));
    return 1;
    }

    if (!objectp(target) || target->query_invis())
    {
    actor->catch_tell("You do not sense "+ LANG_POSS(targetname) +
      " presence in the realms.\n");
    return 1;
    }

    if ((ENV(target)->query_prop(ROOM_M_NO_MAGIC)) ||
        (!objectp(environment(target))))
    {
    actor->catch_tell("The palantir stone cannot see there.\n");
    return 1;
    }

    if (environment(target)->query_prop(OBJ_I_LIGHT) < 1)
    {
    actor->catch_tell("The palantir stone shows you nothing "
        + "but a dark room.\n");
    return 1;
    }

    if (target->query_wiz_level() && !actor->query_wiz_level())
    {
    actor->catch_tell("You don't dare spy on " + targetname + ".\n");
    return 1;
    }

    surroundings = environment(target)->long();

    items = FILTER_CAN_SEE(all_inventory(environment(target)), actor);

    if (items) 
    {
        if (sizeof(FILTER_DEAD(items)))
         surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
        if (sizeof(FILTER_LIVE(items)))
         surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
    }


    actor->catch_tell("You gaze into the palantir stone, and suddenly a "
        + "storm of colours and textures assault your mind! With immense "
        + "effort you wrest the will of the stone into submission.\n"
        + "This is what you see:\n\n"
        + surroundings + "\nThe stone goes dark again, leaving you mentally "
        + "exhausted.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gazes into the small "
        + "crystal globe and for a moment seems unable to look away.\n", 
        ({actor}));
    return 1;
}
