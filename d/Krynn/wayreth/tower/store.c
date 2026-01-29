/*
   Wayreth.

   store.c
   -------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : Oct 2016
   By ...........: Arman

   Code based on store room in vingaard keep.

*/

#include "/d/Krynn/wayreth/local.h"
#include "/sys/stdproperties.h"
inherit TOWERROOM;
inherit "/lib/store_support";

#define HERB_POUCH      "/d/Shire/common/obj/pouch"
#define LAMP            "/d/Krynn/solamn/palanthas/aesthetics/obj/mlantern_bullseye"
#define FLASK           "/d/Krynn/solamn/palanthas/aesthetics/obj/moil_flask"

object gJar, gGloves, gPouch, gLamp, gFlask;

public void
create_tower_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop in the Tower of " +
             "Wayreth.\n");

    setuid();
    seteuid(getuid());

    gJar = clone_object(JAR);
    gGloves = clone_object(GLOVES);
    gPouch = clone_object(HERB_POUCH);
    gLamp = clone_object(LAMP);
    gFlask = clone_object(FLASK);
    gJar->move(TO);
    gGloves->move(TO);
    gPouch->move(TO);
    gLamp->move(TO);
    gFlask->move(TO);
}

public void
check_inv()
{

    if (!present(gJar, TO))
    {
         gJar = clone_object(JAR);
         gJar->move(TO);
    }
    else if (!present(gGloves, TO))
    {
        gGloves = clone_object(GLOVES);
        gGloves->move(TO);
    }
    else if (!present(gPouch, TO))
    {
        gPouch = clone_object(HERB_POUCH);
        gPouch->move(TO);
    }
    else if (!present(gLamp, TO))
    {
        gLamp = clone_object(LAMP);
        gLamp->move(TO);
    }
    else if (!present(gFlask, TO))
    {
        gFlask = clone_object(FLASK);
        gFlask->move(TO);
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

    if ((ob == gJar) || (ob == gGloves) || (ob == gPouch) || 
        (ob == gLamp) || (ob == gFlask)) 
        set_alarm(0.0, 0.0, check_inv);
}
