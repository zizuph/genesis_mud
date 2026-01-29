/*
 * /d/Gondor/mordor/obj/flour_sack.c
 *
 * This is the sack that can be found in the tower at Cirith Ungol. It looks
 * a bit like the sack you can find in the Haradrim camp, but who cares about
 * that. It will self-descruct a little time after creation.
 *
 * /Mercade, 11 October 1993
 */

inherit "/std/receptacle.c";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <filter_funs.h>

#define CONTAINER_DESTRUCT_TIME 100.0 /* float */
#define FLOUR_FILE              MORDOR_DIR + "obj/flour"
#define FLOUR_ID                "_unique_orc_flour_"

/*
 * Prototype
 */
void add_handful();
void destruct_container();

/*
 * Create the sack
 */
void
create_container()
{
    set_name("sack");
    set_adj("flour");

    set_short("sack of flour");
    set_pshort("sacks of flour");
    set_long(BSN("This is a large sack. It is used to stock flour. Most of " +
        "the flour is clotted and curdled and you don't think you have any " +
        "use for those clots. However, there is some grey flour that might " +
        "become in handy."));

    add_prop(OBJ_M_NO_GET, "This sack is either too heavy or too big.\n");
    add_prop(CONT_I_VOLUME,      50000);
    add_prop(CONT_I_MAX_VOLUME,  75000);
    add_prop(CONT_I_WEIGHT,     100000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(OBJ_I_VALUE,           50);
    add_prop(OBJ_S_WIZINFO,
        BSN("This sack contains flour. The flour cannot be eaten, but if " +
        "you throw this flour in someones fact, he will stop fighting for a " +
        "moment. This sack will self-descruct in several seconds (but not " +
        "before you leave the room)."));

    add_handful();
    add_handful();

    set_alarm(CONTAINER_DESTRUCT_TIME, 0.0, destruct_container);
}

/*
 * This adds a 'handful' of flour to the sack.
 */
void
add_handful()
{
    seteuid(getuid(this_object()));
    clone_object(FLOUR_FILE)->move(TO);
}

/*
 * If you remove a 'handful' a new one will be added. Do not fear that people
 * will therefor be able to get themselves a 'heap' of 'hands ful' of flour
 * for the flour is coded in a way that you cannot have more than 5 instances
 * of flour in your inventory.
 */
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->id(FLOUR_ID))
    {
        set_alarm(1.0, 0.0, add_handful);
    }
}

/*
 * This container will self-destruct after several seconds. This is to make
 * sure that you will have to search for the sack if you enter the room.
 */
void
destruct_container()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(this_object()))))    
    {
        set_alarm(CONTAINER_DESTRUCT_TIME, 0.0, destruct_container);
        return;
    }

    remove_object();
}
