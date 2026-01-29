/*
   Diamond. Store Room for supplies

   store1.c
   -------

   Coded ........: May 1997
   By ...........: Kentari

   Latest update : October 1997
   By ...........: Kentari

   Code based on store room in wayreth tower.

*/

#include "../local.h"
#include <stdproperties.h>
inherit IN_BASE;
inherit "/lib/store_support";

object gFlask, gBottle, gHat, gGoggles;

public void
create_dim_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the supply shop in Diamond " +
             "City.\n");
    add_exit(DIROOM + "shop","up");

    setuid();
    seteuid(getuid());

    gFlask = clone_object(FLASK);
    gBottle = clone_object(BOTTLE);
    gHat = clone_object(HAT);
    gGoggles = clone_object(GOGGLES);
    gFlask->move(TO);
    gBottle->move(TO);
    gHat->move(TO);
    gGoggles->move(TO);
}

public void
check_inv()
{
    if (!present(gFlask, TO))
    {
         gFlask = clone_object(FLASK);
         gFlask->move(TO);
    }
    else if (!present(gJar, TO))
    {
         gJar = clone_object(JAR);
         gJar->move(TO);
    }
    else if (!present(gVial, TO))
    {
         gVial = clone_object(VIAL);
         gVial->move(TO);
    }
    else if (!present(gGloves, TO))
    {
        gGloves = clone_object(GLOVES);
        gGloves->move(TO);
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if ((ob == gJar) || (ob == gVial) || (ob == gMortar) || (ob == gGloves)) 
        set_alarm(0.0, 0.0, check_inv);
}
