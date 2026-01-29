inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"

#define KALAD_SHADOW_INGR "_kalad_shadow_ingr"

/* by Antharanos */
void
create_object()
{
    ::create_object();
    set_name("glass jar filled with tar");
    add_name("glass jar");
    add_name("jar");
    add_name("tar");
    set_short("glass jar filled with tar");
    set_pshort("glass jars filled with tar");
    set_long("A small, fist-sized glass jar that is filled to the brim "+
      "with sticky black tar.\n");
    add_prop(OBJ_I_VALUE,35);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(KALAD_SHADOW_INGR,35);
}
void
init()
{
    ::init();
    add_action("drink","drink");
}
int
drink(string s)
{
    if(!s || s != "tar")
    {
	notify_fail("Drink what?\n");
	return 0;
    }
    write("You almost drink some of the toxic tar before you realize "+
      "that it could kill you!\n");
    say(QCTNAME(TP) + " almost drinks some of the toxic tar before " + TP->query_pronoun() + " realizes that it is fatal!\n");
    set_alarm(3.0,0.0,"fear");
    return 1;
}
fear()
{
    write("You tremble in fear at almost dying.\n");
    say(QCTNAME(TP) + " trembles in fear at almost dying.\n");
    return;
}
