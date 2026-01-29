/*
   Wayreth.

   store.c
   -------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/06/02
   By ...........: Jeremiah

   Code based on store room in vingaard keep.

*/

#include "/d/Krynn/wayreth/local.h"
#include "/sys/stdproperties.h"
inherit TOWERROOM;
inherit "/lib/store_support";

object gMortar, gJar, gVial, gGloves;

public void
create_tower_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop in the Tower of " +
             "Wayreth.\n");

    setuid();
    seteuid(getuid());

    gMortar = clone_object(MORTAR);
    gJar = clone_object(JAR);
    gVial = clone_object(VIAL);
    gGloves = clone_object(GLOVES);
    gMortar->move(TO);
    gJar->move(TO);
    gVial->move(TO);
    gGloves->move(TO);
}

public void
check_inv()
{
    if (!present(gMortar, TO))
    {
         gMortar = clone_object(MORTAR);
         gMortar->move(TO);
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
