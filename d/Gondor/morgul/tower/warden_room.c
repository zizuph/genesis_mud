/*
 * /d/Gondor/morgul/tower/warden_room.c
 * The room for the Warden of the Tower
 *
 * Olorin, 25-jul-1994
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

#define LIVE_I_MORGUL_WARDEN	"_live_i_morgul_warden"
#define HIM(x)	(x)->query_objective()

public  int     warden_block();
public  void    reset_room();

static  object  Warden;

public void
create_morgul_tower_room()
{
    set_level(1);
    set_room_type("dark, gloomy chamber");
    set_extra_long("This is the chamber of the Warden of the Tower. " +
        "The Warden of the Tower is one of the more powerful servants " +
        "of the King of Morgul. If you ask him, he might be willing " +
        "to help you. To the west, a dark passage is leading out.");

    add_walls();
    add_roof();
    add_floor();

    add_exit(TOWER_DIR  + "tower_1c",      "west",  0,            1);
    add_exit(TOWER_DIR  + "warden_office", "north", warden_block, 1);

    add_prop(ROOM_I_LIGHT, 1);
    reset_room();
}

public void
reset_room()
{
    if (!objectp(Warden))
    {
        Warden = clone_object(MAGES_DIR + "newnpc/tower_warden");
        Warden->move_living("down", TO);
        Warden->arm_me();
    }
}

public int
warden_block()
{
    if (!objectp(Warden) || !present(Warden))
        return 0;

    if (!CAN_SEE_IN_ROOM(Warden) || !CAN_SEE(Warden, TP))
        return 0;

    if (IS_MORGUL_MAGE(TP))
        return 0;

    write("The "+Warden->query_nonmet_name()+" stops you.\n");
    say(QCTNAME(TP)+" tries to go north, but the "
      + Warden->query_nonmet_name()+" stops "+HIM(TP)+".\n");

    if (TP->query_prop(LIVE_I_MORGUL_WARDEN))
    {
        Warden->do_attack(TP);
    }
    else
    {
        Warden->command("mhiss Where do you think you are going?");
        Warden->command("mglare " + TP->query_real_name());
    }
    
    TP->add_prop(LIVE_I_MORGUL_WARDEN, TP->query_prop(LIVE_I_MORGUL_WARDEN) + 1);

    return 1;

}

public object
query_warden()
{
    return Warden;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || living(ob) || !living(from))
        return;

    if (!objectp(Warden) || !present(Warden, TO))
        return;

    set_alarm(2.0 + rnd() * 5.0, 0.0, &Warden->command("get all"));
}
