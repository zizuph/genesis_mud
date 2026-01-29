/*
 * Creator : Shadowlynx
 * Date    : 29-November-2000
 * Purpose : When chewed will restore partial mana and health.
 * Credits : Modification from original file by Amelia on 
 *           17-April-1997. The original file was designed
 *           to alleviate headaches, hangovers and have a 
 *           slight healing effect when chewed.
 * Updates :
 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

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
    set_id_long(break_string("A piece of bark from the Populus "+
	"tremuloides, or quaking aspen, a relative of "+
	"the poplar tree. It has the texture of leather or "+
	"paper. It has medicinal properties that relieve "+
	"headaches and hangovers. It appears too rough "+
	"to eat, but you might try chewing it.\n", 70));
    set_id_diff(20);
    set_find_diff(1);
    EFFECT = 40;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(10000);
    set_effect(HERB_SPECIAL, "", EFFECT);
}

string
query_recover()
{ 
    return MASTER + ":" + query_herb_recover();
}
void
init_recover(string arg)
{ 
    init_herb_recover(arg); 
}


int
chew_bark(string str)
{
    object tp = this_player();
    object to = this_object();

    notify_fail("Chew what?\n");
    if (!id(str))
	return 0;
    tp->catch_msg("You chew the rough bark slowly.\n");
    tell_room(environment(tp), QCTNAME(tp) + " chews a "+
      "piece of white bark.\n", ({tp}));
    tp->heal_hp(EFFECT);
    tp->catch_msg("You feel better.\n");
    to->remove_object();
    return 1;
}

void
special_effect()
{

    object tp = this_player();

    tp->catch_msg(break_string("You try to swallow the "+
	"bark but it is too rough, and you have to spit it "+
	"out. Next time just try chewing it.\n", 70));
    tp->command("spit");
}

void
init()
{
    add_action(&chew_bark(), "chew");
    ::init();
}
