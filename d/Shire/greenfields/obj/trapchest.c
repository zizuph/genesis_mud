/*
 * A small chest 940618, belongs to Hzzz, leader of the orc camp

 April 19, 2006 Palmer:
 Removed non-standard gems and upped the number of gold coins

 */

inherit "/d/Genesis/lib/trap";
inherit "/std/receptacle";
inherit "/d/Faerun/lib/gems";
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <poison_types.h>
#include <composite.h>


void reset_chest();

void
create_receptacle()
{
    set_name("chest");
    set_adj("small");
    add_name("trapped_chest");
    add_adj("iron");
    set_pshort("small iron chests");
    set_long("A small iron chest made of a solid piece of "+
      "cast iron with an inset lock to hold the hinged lid in "+
      "place, and keep prying eyes, and fingers, out of the chest.\n@@trap_desc@@");

    set_key("Hzzz_Chest_Key");
    set_cf(this_object());
    set_pick(49);
    set_trap_level(28);

    add_prop(CONT_I_WEIGHT, 4500); 	/* It weights 4500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 14500); 	/* It can hold 14500 grams. */
    add_prop(CONT_I_VOLUME, 1900); 	/* 1.9 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 6000); 	/* 6 litres of volume */
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VALUE, 220); 		/* Worth 220 cc */

}

void
reset_chest()
{

    setuid(); seteuid(getuid());
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    set_trapped(1);
    if (!present("coin"))
        MONEY_MAKE_GC(35)->move(this_object(), 1);
}

void
poison_me(object who)
{
    object poison;

    poison = clone_object("/std/poison_effect");
    poison->set_interval(25);
    poison->set_time(600);
    poison->set_strength(40);
    poison->set_damage(({ POISON_FATIGUE, 120, POISON_HP, 75}));
    poison->move(who, 1);
    poison->start_poison();
}

void
spring_trap(object player)
{
    object *victims;

    if (!query_trapped())
	return;
    ::spring_trap(player);
    setuid(); seteuid(getuid());
    switch(random(5))
    {
    case 0..3:
	player->catch_tell("As you "+query_verb()+" the "+real_short()+
	  " a razor sharp blade slides out of the chest slicing your "+
	  "hand badly!!\n");
	player->command("wince");
	player->heal_hp(-(200 + random(101)));
	if (player->query_hp() < 1)
	    player->do_die(this_object());
	break;
    case 4:
	tell_room(environment(this_object()), "As "+QTNAME(player)+
	  " opens the "+real_short()+" you smell the faint smell of gas "+
	  "filter into the environment.\n", ({player}));
	player->catch_tell("As you "+query_verb()+" the "+real_short()+
	  " a burst of gas shoots forth from the chest!!\n");

	victims = FILTER_LIVE(all_inventory(environment(this_object())));
	map(victims, poison_me);
	break;
    }
}

public mixed
open(object ob)
{
    spring_trap(this_player());
    return 0;
}

public void
pick_fail()
{
    spring_trap(this_player());
}

public void
init()
{
    ::init();
    init_trap();
}
