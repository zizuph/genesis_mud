/*
 *   The storage room of the Thornlin shop
 *   Original author uncertain (based on MT Gen'l Shop Storeroom)
 *   Modified for Thornlin use by Auberon, Dec. 31 2000
 */

/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */

#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
inherit "/lib/store_support";

#include <stdproperties.h>

/* prototype */
void reset_room();

object *oil;
int nr;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room() 
{
    set_short("The store room of Thornlin General Store");
    set_long("This is the store room for the Thornlin General Store.\n");

    add_exit(THORN_DIR + "shop", "south",0);

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    nr = 3 + random(6);
    oil = allocate(nr);
    reset_room();
}

void
reset_room()
{
    int i;

    if (!present("torch"))
	clone_object(OBJ_DIR + "torch")->move(TO);
    for(i = 0; i < nr; i++)
    {
	if(!oil[i] || !present(oil[i],TO))
	{
	    oil[i] = clone_object(OBJ_DIR + "oilflask");
	    oil[i]->move(TO);
	}
    }

    if (!present("lamp"))
	for(i = 0; i < 2; i++)
	    clone_object(OBJ_DIR + "oil_lamp")->move(TO);
    if (!present("spear"))
	for(i = 0; i < 5; i++)
	    clone_object(THORN_DIR + "obj/spear")->move(TO);
    if (!present("cloak"))
	for(i = 0; i < 8; i++)
	    clone_object(THORN_DIR + "obj/cloak")->move(TO);
    if (!present("gauntlets"))
	for(i = 0; i < 4; i++)
	    clone_object(THORN_DIR + "obj/gauntlets")->move(TO);
    if (!present("shield"))
	for(i = 0; i < 6; i++)
	    clone_object(THORN_DIR + "obj/shield")->move(TO);
    if (!present("hauberk"))
	for(i = 0; i < 4; i++)
	    clone_object(THORN_DIR + "obj/hauberk")->move(TO);
    if (!present ("boots"))
	for(i = 0; i < 2; i++)
	    clone_object(THORN_DIR + "obj/boots")->move(TO);
    if (!present ("pike"))
	for(i = 0; i < 3; i++)
	    clone_object(THORN_DIR + "obj/pike")->move(TO);
}

