/*
 * The Blacksmith of the orc camp
 * Finwe, October 2007
 */

inherit "/std/monster";
inherit "/d/Faerun/smithy/base_blacksmith";

#include "defs.h"
#include <const.h>   // for G_MALE
#include <macros.h>  // for OB_NAME

void
create_monster()
{
    seteuid(getuid());

    set_name("orc");
    add_name(ORC_BLACKSMITH);
    add_name("blacksmith");
    set_race_name("orc");
    set_adj("muscular");
    set_adj("large");
    set_long("This is the master blacksmith of the orcs. His dark skin is covered by a leather apron. The dog-like face is splotched from heat and its long arms are muscular and free of hair. Its disheveled hair is is black and tied back out of its face.\n");
    set_gender(G_MALE);
    set_stats(({ 100, 100, 100, 100, 100, 100 }));
    
    config_default_trade();

    set_act_time(5);
    add_act("emote hammers a piece of metal repeatedly, forging it into a deadly weapon.");
    add_act("emote wipes the sweat from his brow.");
    add_act("emote looks up from his work and watches you.");
    add_act("emote hammers a piece of metal repeatedly, turning it into a piece of armour.");
    add_act("emote stops hammering and pumps the bellows, making the fire flare hotter.");
    add_act("emote stokes the fire.");

}
void
init_living()
{
    ::init_living();
    init_smithy();

}

attacked_by(object ob)
{
    ::attacked_by(ob);
    call_out("react", 1, ob);
}

void
react(object ob)
{

    if (!present(ob, environment(this_object())))
	return;

    /*
     * Stop the fighting
     */
    ob->stop_fight(this_object());
    this_object()->stop_fight(ob);

    tell_room(environment(), QCTNAME(this_object()) + " jumps up from the forge, growls, and tosses " + QTNAME(ob) + " out of the forge!\n", ob);

    ob->catch_msg(QCTNAME(this_object()) + " jumps up from the forge, growls, and tosses you out of the forge!\n");

    ob->move_living("M", OC_DIR + "camp18", 1);
}

