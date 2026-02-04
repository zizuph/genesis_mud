/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * rseed.c
 *
 * A plantable seed. Mortricia 930820
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

#include <ss_types.h>
#include <cmdparse.h>

// #define BUSH_FILE    ENCHANT_DIR + "obj/berrybush"
#define BUSH_FILE    ENCHANT_DIR + "obj/redbush"


static int planted = 0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    
    set_name("seed");
    set_adj("small");
    add_adj("red");
    set_short("small red seed");
    set_long("It is a small seed. Maybe you can plant it somewhere?\n");
    add_prop(OBJ_I_VALUE,  50 + random(5));
    add_prop(OBJ_I_WEIGHT, 7);
    add_prop(OBJ_I_VOLUME, 6);
}

/*
 * Function name: grow_herb
 * Description:   grow the berry bush.
 * Arguments:     who - the player who planted the seed.
 */
public void
grow_herb(object who)
{
    int tmp = 1 + random(3);
    object bush;

    FIX_EUID;
    bush = clone_object(BUSH_FILE);
    if (who) {
        tmp += who->query_stat(SS_WIS)/40;
        tmp += who->query_skill(SS_HERBALISM)/20;
    }
    bush->set_berries(tmp);
    bush->move(ETO);
    
    remove_object();
}

/*
 * Function name: do_plant
 * Description:   Handle the polish action
 * Returns:       1/0
 */
public int
do_plant(string str)
{
    object *obs;

    if (planted) return 0;

    NF("Plant what?\n");
    if (!str) return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (sizeof(obs) == 0) return 0;
    if (obs[0] != TO) return 0;

    if (ETP->query_prop(ROOM_I_INSIDE) != 0) {
        write("You cannot plant the " + short() + " here.\n");
        return 1;
    }

    write("You plant the " + short() + ".\n");
    say(QCTNAME(TP) + " plants a seed here.\n");

    move(ETP);
    planted = 1;
    set_no_show();
    add_prop(OBJ_M_NO_GET, 1);

    set_alarm(itof(50 + random(20)), -1.0, &grow_herb(TP));

    return 1;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init()
{
    ::init();
    add_action(do_plant, "plant");
}
