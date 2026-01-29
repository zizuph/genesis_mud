/*
 * /d/Krynn/sancrist/nevermind/guild/obj/ichor.c
 * 
 * Creator: Shadowlynx
 * Date   : Feb 10/99
 * Updated: 
 * By Whom:
 *
 * To be generated from the DragonIchor module on the gizmo
 */

inherit "/std/drink";
#include "/sys/stdproperties.h"

void
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(10);
    set_name("ichor");
    set_pname("ichors");
    add_name("cup");
    add_pname("cups");
    add_name("dragon ichor");
    add_pname("dragon ichors");
    set_short("cup of "
      + ({"red","scarlet","crimson","black","blue","green","white",
	"maroon","brown","silver","gold","bronze","rainbow"})[random(13)]
      + " dragon ichor");
    set_pshort("cups of "
      + ({"red","scarlet","crimson","black","blue","green","white",
	"maroon","brown","silver","gold","bronze","rainbow"})[random(13)]
      + " dragon ichor");
    set_long("A cup oozing with " 
      + ({"a divinely, putrid fragrance", "a heavenly, ethereal fluid",
	"a luscious, pungent tasting liquid",
	"an ethereal, acrid smelling essence",
	"a scrumptuous, creamy mixture"})[random(5)] 
      + " from the entrails of a dragon.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

void
special_effect(int amnt)
{
    write("The wicked eye-watering substance slides smoothly" +
      " down your throat with a gut-wrenching sensation.\n" +
      "You shiver with delight savouring the taste.\n");
}

