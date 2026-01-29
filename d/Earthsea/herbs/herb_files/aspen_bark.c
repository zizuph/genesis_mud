inherit "/std/herb";

/*
 *   coded by Amelia  4/17/97
 *  aspen bark, when chewed, alleviates headache,
 *  hangover, and has a slight healing effect
 */
#include <herb.h>
#include <macros.h>
#include "defs.h"
#include "/sys/stdproperties.h"

int CC, EFFECT;

void
create_herb()
{
    set_name(({"bark"}));
    add_pname("herbs");
    set_adj(({"aspen", "poplar", "white"}));
    set_herb_name("aspen bark");
    set_pname("pieces of white bark");
    set_short("piece of white bark");
    set_pshort("pieces of white bark");
    add_pname("pieces of aspen bark");
    set_unid_long("A piece of white bark. "+
      "It has the texture of leather or paper, "+
      "peeled from a tree.\n"); 
    set_id_long("A piece of bark from the Populus "+
	"tremuloides, or quaking aspen, a relative of "+
	"the poplar tree. It has the texture of leather or "+
	"paper. It has medicinal properties that relieve "+
	"headaches and hangovers. It appears too rough "+
	"to eat, but you might try chewing it.\n");
    set_id_diff(20);
    set_find_diff(1);

    EFFECT = 40;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    set_ingest_verb("chew");
    set_herb_value(CC);
    set_decay_time(10000);
    set_effect(HERB_SPECIAL, "", EFFECT);
}


void
special_effect()
{
    object tp = this_player();
    object to = this_object();

    tp->catch_msg("You chew the rough bark slowly.\n");
    tell_room(environment(tp), QCTNAME(tp) + " chews a "+ "piece of white bark.\n", ({ tp }));
    tp->heal_hp(EFFECT);

    add_effect_message("You feel better.\n");
}

public mixed
command_eat()
{
    if (query_verb() != "chew") 
    {
        write("You try to swallow the bark but it is too rough, " + 
            "and you have to spit it out. Next time just try chewing it.\n");
        this_player()->command("$spit");
        return 0;
    }

    return ::command_eat();
}

