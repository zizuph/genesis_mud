/*
 *   The storage room of the Solamnian shop, made by Nick
 *   modified for the dwarves by Aridor
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "../guild/guild.h"
#include "/sys/stdproperties.h"

#define OIL 	"dwarf_shop_oil"
#define OIL_F   "/d/Gondor/common/obj/oilflask"
#define LAMP	"dwarf_shop_lamp"
#define LAMP_F  "/d/Gondor/common/obj/oil_lamp"

/*Prototype*/
void reset_room();


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the accessory shop.\n");

    add_exit(THEIWAR + "r22", "west");

    seteuid(getuid(TO));

    INSIDE;
    reset_room();
}

void
reset_room()
{
    object ob;

    if (!P(OIL, TO))
    {
    	ob = clone_object(LAMP_F);
   	ob->add_name(LAMP);
    	ob->move(TO);
	ob = clone_object(LAMP_F);
   	ob->add_name(LAMP);
    	ob->move(TO);
    }
    if (!P(OIL, TO))
    {
    	ob = clone_object(OIL_F);
   	ob->add_name(OIL);
    	ob->move(TO);
	ob = clone_object(OIL_F);
   	ob->add_name(OIL);
    	ob->move(TO);
	ob = clone_object(OIL_F);
   	ob->add_name(OIL);
    	ob->move(TO);
	ob = clone_object(OIL_F);
   	ob->add_name(OIL);
    	ob->move(TO);
    }
    if (!P(CHALK, TO))
    {
    	ob = clone_object(OBJ + "chalk");
   	ob->add_name(CHALK);
    	ob->move(TO);
	ob = clone_object(OBJ + "chalk");
   	ob->add_name(CHALK);
    	ob->move(TO);
	ob = clone_object(OBJ + "chalk");
   	ob->add_name(CHALK);
    	ob->move(TO);
    }
}
