/*
 * /d/Gondor/minas/obj/palantir.c
 *
 * The Palantir of the White Tower of Ecthelion
 *
 * Alto 5 June 2001
 *  Modification log:
 *    Fixed lower case bug in return, Alto, 08 November 2001
 * Serif, Aprli 21, 2002: added logging.
 *
 * Added checks vs ROOM_M_NO_SCRY/ROOM_I_NO_SCRY, Nerull 2016.
 * Added checks vs LIVE_O_NO_SCRY, Zizuph 2021
 */

inherit "/std/object";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Gondor/defs.h"


object actor, target, *items;
string room, targetname, actorname, surroundings;

void
create_object()
{
    set_name("globe");
    add_name("_palantir_stone");
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
    add_prop(OBJ_M_NO_GET, "The small crystal globe seems magically fused to "
        + "the pedestal.\n");

    seteuid(getuid(TO));
    set_no_show_composite(1);
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
    actorname = TP->query_name();

    if ((actor->query_mana()) <= ((actor->query_max_mana())/7))
    {
    actor->catch_tell("You are too mentally exhausted to master "
        + "the palantir stone.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gazes into the small "
        + "crystal globe and looks visibly shaken.\n",
        ({actor}));
    log_file("palantir",
        ctime(time())+ " " + actorname + " tried to scry " + targetname
        + " but was too mentally drained.\n");
    return 1;
    }

    if ((actor->query_stat(3)) <= 100)
    {
    actor->catch_tell("You do not have the strength of will to "
        + "master the palantir stone.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gazes into the small "
        + "crystal globe and looks visibly shaken.\n",
        ({actor}));
    log_file("palantir",
        ctime(time())+ " " + actorname + " tried to scry " + targetname
        + " but was not able to use the stone.\n");
    return 1;
    }

    if (target->query_wiz_level() && !actor->query_wiz_level())
    {
    actor->catch_tell("You don't dare spy on " + targetname + ".\n");
    log_file("palantir",
        ctime(time())+ " " + actorname + " tried to scry " + targetname
        + " but failed, because wizards cannot be scried.\n");
    return 1;
    }

    if (!objectp(target) || target->query_invis() ||
        target->query_prop(LIVE_I_NO_SCRY))
    {
    actor->catch_tell("You do not sense "+ LANG_POSS(targetname) +
      " presence in the realms.\n");
    log_file("palantir",
        ctime(time())+ " " + actorname + " tried to scry " + targetname
        + " but " + targetname + " was not to be found.\n");
    return 1;
    }

    if ((ENV(target)->query_prop(ROOM_M_NO_MAGIC)) ||
        (!objectp(environment(target))))
    {
    actor->catch_tell("The palantir stone cannot see there.\n");
    log_file("palantir",
        ctime(time())+ " " + actorname + " tried to scry " + targetname
        + " but " + targetname + " was in a protected room.\n");
    return 1;
    }

	if ((ENV(target)->query_prop(ROOM_M_NO_SCRY)) ||
		(!objectp(environment(target))))
	{
		actor->catch_tell("The palantir stone cannot see there.\n");
		log_file("palantir",
			ctime(time()) + " " + actorname + " tried to scry " + targetname
			+ " but " + targetname + " was in a protected room.\n");
		return 1;
	}

	if ((ENV(target)->query_prop(ROOM_I_NO_SCRY)) ||
		(!objectp(environment(target))))
	{
		actor->catch_tell("The palantir stone cannot see there.\n");
		log_file("palantir",
			ctime(time()) + " " + actorname + " tried to scry " + targetname
			+ " but " + targetname + " was in a protected room.\n");
		return 1;
	}

    if (environment(target)->query_prop(OBJ_I_LIGHT) < 1)
    {
    actor->catch_tell("The palantir stone shows you nothing "
        + "but a dark room.\n");
    log_file("palantir",
        ctime(time())+ " " + actorname + " tried to scry " + targetname
        + " but " + targetname + " was in a dark room.\n");
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
    target->catch_tell("You feel as if someone is looking at you from afar.\n");

    log_file("palantir",
        ctime(time())+ " " + actorname + " scried " + targetname + ".\n");
    return 1;
}

