/*
 *   The storage room of the Solamnian shop, made by Nick
 *   modified for the thieves fence by Aridor
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "guild.h"
#include <stdproperties.h>

#define TORCH 	"thief_shop_torch"
#define BAG	"thief_shop_bag"
#define SCARF   "thief_shop_scarf"
#define SHIRT   "thief_shop_shirt"
#define KNIFE   "thief_shop_knife"

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
    set_short("The fence's store room");
    set_long("This is the store room of the fence.\n");

    add_exit(GUILDR + "shop", "up");

    INSIDE
    reset_room();
}

void
reset_room()
{
    object ob;

    if (!P(TORCH, TO))
    {
	seteuid(getuid(TO));
	ob = clone_object(OBJ + "torch");
	ob->add_name(TORCH);
	ob->move(TO);
	ob = clone_object(OBJ + "torch");
	ob->add_name(TORCH);
	ob->move(TO);
	ob = clone_object(OBJ + "torch");
	ob->add_name(TORCH);
	ob->move(TO);
    }
    if (!P(BAG, TO))
    {
	seteuid(getuid(TO));
	ob = clone_object(OBJ + "lbag");
	ob->add_name(BAG);
	ob->move(TO);
	ob = clone_object(OBJ + "bag");
	ob->add_name(BAG);
	ob->move(TO);
    }
    if (!P(CHALK, TO))
    {
	seteuid(getuid(TO));
	/*
		ob = clone_object(OBJ + "chalk");
		ob->add_name(CHALK);
		ob->move(TO);
		ob = clone_object(OBJ + "chalk");
		ob->add_name(CHALK);
		ob->move(TO);
	*/
	ob = clone_object(OBJ + "chalk");
	ob->add_name(CHALK);
	ob->move(TO);
    }
    if (!P(SHIRT, TO))
    {
	seteuid(getuid(TO));
	ob = clone_object(POBJ + "sweater");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "pullover");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "cshirt");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "lshirt");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "wshirt");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "cblouse");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "dress");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "pants");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "skirt");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "sskirt");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "leggings");
	ob->add_name(SHIRT);
	ob->move(TO);
	ob = clone_object(POBJ + "trousers");
	ob->add_name(SHIRT);
	ob->move(TO);
    }
    /*
	if (!P(SCARF, TO))
	{
	    seteuid(getuid(TO));
	    ob = clone_object(OBJ + "scarf");
	    ob->add_name(SCARF);
	    ob->move(TO);
	    ob = clone_object(OBJ + "scarf2");
	    ob->add_name(SCARF);
	    ob->move(TO);
	    ob = clone_object(OBJ + "scarf3");
	    ob->add_name(SCARF);
	    ob->move(TO);
	    ob = clone_object(OBJ + "scarf4");
	    ob->add_name(SCARF);
	    ob->move(TO);
	    ob = clone_object("/d/Terel/orc_cave/armour/collar");
	    ob->add_name(SCARF);
	    ob->move(TO);
	    ob = clone_object("/d/Terel/orc_cave/armour/collar");
	    ob->add_name(SCARF);
	    ob->move(TO);
	}
    */
    if (!P(KNIFE, TO))
    {
	seteuid(getuid(TO));
	ob = clone_object(OBJ + "dudgeon");
	ob->add_name(KNIFE);
	ob->move(TO);
	ob = clone_object(OBJ + "dudgeon");
	ob->add_name(KNIFE);
	ob->move(TO);
	ob = clone_object(OBJ + "knife");
	ob->add_name(KNIFE);
	ob->move(TO);
	ob = clone_object(OBJ + "knife");
	ob->add_name(KNIFE);
	ob->move(TO);
    }
}

void
remove_items()
{
    int i;

    for (i=0 ; i<sizeof(remove_list) ; i++)
	if (remove_list[i] && present(remove_list[i]) &&
	  !remove_list[i]->id(KNIFE) &&
	  !remove_list[i]->id(SCARF) &&
	  !remove_list[i]->id(SHIRT) &&
	  !remove_list[i]->id(TORCH) &&
	  !remove_list[i]->id(BAG))
	    remove_list[i]->remove_object();
    remove_list = ({ });
}

