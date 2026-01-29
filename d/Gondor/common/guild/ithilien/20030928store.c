/*
 *   The storage room of the Equipment Store in Henneth Annun
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define RANGER_OBJ_DIR  RANGER_DIR + "obj/"
#define OILFLASK (OBJ_DIR + "oilflask")
#define OILLAMP  (OBJ_DIR + "oil_lamp")
#define BACKPACK (RANGER_DIR + "obj/backpack")

public void   reset_room();

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

public void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

  add_exit(RANGER_ITH_DIR+"shop","west",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
  reset_room();
}

public void
reset_room()
{
    int i;
    object quiver, arrows;
    
    seteuid(getuid(TO));
    if (!present("torch",TO)) 
        clone_object(OBJ_DIR+"torch")->move(TO);
    if (!present("lamp-oil",TO)) 
        clone_object(OILFLASK)->move(TO);
    if (!present("oil-lamp",TO)) 
        clone_object(OILLAMP)->move(TO);
    if (!present("pouch",TO))
        clone_object(RANGER_OBJ_DIR+"herbpouch")->move(TO);
    if (!present("spear",TO))
        clone_object(WEP_DIR + "r_spear")->move(TO);
    if (!present("sword",TO))
        clone_object(WEP_DIR + "r_lsword")->move(TO);
    if (!present("armour", TO))
        clone_object(ARM_DIR + "studlarm")->move(TO);
    if (!present("backpack",TO)) 
    {
        clone_object(BACKPACK)->move(TO);
        clone_object(BACKPACK)->move(TO);
    }
    
    if (!present("quiver"))
    {
	arrows = clone_object(RANGER_OBJ_DIR + "arrows");
	quiver = clone_object(RANGER_OBJ_DIR + "quiver");
	arrows->move(quiver, 1);
	quiver->move(TO, 1);
	
	arrows = clone_object(RANGER_OBJ_DIR + "arrows");
	quiver = clone_object(RANGER_OBJ_DIR + "quiver");
	arrows->move(quiver, 1);
	quiver->move(TO, 1);
    }

    if (!present("arrows"))
    {
	arrows = clone_object(RANGER_OBJ_DIR + "arrows");
	arrows->set_heap_size(500);
	arrows->move(TO, 1);
    }

    if (!present("shortbow"))
    {
	clone_object(RANGER_OBJ_DIR + "shortbow")->move(TO, 1);
	clone_object(RANGER_OBJ_DIR + "shortbow")->move(TO, 1);
    }
}









