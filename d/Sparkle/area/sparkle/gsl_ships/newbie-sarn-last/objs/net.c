/* File:          /d/Khalakhor/ship/macdunn/calia/net.c
 * Creator:       Teth
 * Date:          April 20, 1997
 * Modifications:
 * Purpose:       This is a net in the deck of the ship.
 *                It contains sea urchins.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/calia/
 *                /d/Khalakhor/ship/macdunn/calia/urchin.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include <stdproperties.h>
#include "../ship.h"

object food;

public void
reset_receptacle()
{
    seteuid(getuid());

    if (!food || !present(food))
    {
        food = clone_object(URCHIN);
        food->set_heap_size(1 + (random(6)));
        food->move(this_object(), 1);
    }

    this_object()->add_prop(CONT_I_CLOSED, 1);
}

public void
create_receptacle()
{
    set_name("net");
    add_name("receptacle");
    set_pname("nets");
    set_adj("fishing");
    add_adj("seaweed");
    set_short("fishing net");
    set_pshort("fishing nets");
    set_long("This fishing net is fastened to the hull of the boat. " +
        "It is made of a strange green material, and has a slimy " +
        "texture where wet. It is obviously used for catching " +
        "fish.\n");
    add_item(({"strange material","green material","material",
        "strange green material"}),"The green material seems to " +
        "be seaweed.\n");
    add_item(({"seaweed","weed"}),"The seaweed is knotted and " +
        "twisted to make an effective net.\n");
    add_item(({"texture","slimy texture"}),"It looks quite slimy.\n");
    add_cmd_item(({"texture","slimy texture","net","the net",
        "fishing net","the fishing net","the texture"}),({"touch",
        "feel"}),"Where the net is wet, it is very slimy. " +
        "Where dry, it is rough.\n");
    add_item(({"hook","forged hook"}),"The forged hook is screwed " +
        "deeply into the hull of the boat.\n");
    add_cmd_item(({"hook","forged hook"}),"unscrew","Try as you " +
        "might, you find yourself unable to turn the hook.\n");
    add_cmd_item(({"hook","forged hook"}),"screw","The hook " +
        "is already screwed into the hull!\n");

    add_prop(CONT_I_WEIGHT, 2230);
    add_prop(CONT_I_MAX_WEIGHT, 10453);
    add_prop(CONT_I_VOLUME, 5320);
    add_prop(CONT_I_MAX_VOLUME, 50555);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this net to a " +
        "store, please report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The net is firmly fastened to the side " +
        "of the boat by a forged hook, so that the fisherman doesn't " +
        "lose the net when trawling.\n");
    add_prop(OBJ_I_VALUE, 320);

    enable_reset(150);
    reset_receptacle();
}
