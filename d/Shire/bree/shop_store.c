/*
 *   The storage room of the Bree shop
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "defs.h"
#include "/sys/stdproperties.h"

#define MAX_PACKS 3
static object *packs = allocate(MAX_PACKS);

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room() {
    set_short("Bree storage room");
    set_long("You have entered the dusty storage room of the " +
        "Tools and Supplies shop. This is where the shopkeeper " +
        "keeps all his items that are for sale in the store. " +
        "You better leave the stuff here alone, or else the " +
        "shopkeeper will be upset with you.\n");

    add_exit(BREEE_DIR + "shop","down");

    add_prop(ROOM_I_NO_CLEANUP, 1); // We don't want this room to be unloaded
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_room();
}

reset_room() 
{
int index;
/*
    if (!present("shoptorch"))
	clone_object(STAND_OBJ + "shoptorch")->move(this_object());
    if (!present("shopsword"))
	clone_object(STAND_WEAPON + "shopsword")->move(this_object());
    if (!present("sack"))
	clone_object(STAND_OBJ + "sack")->move(this_object());
    if (!present("_ink_"))
	clone_object(STAND_OBJ + "ink")->move(this_object());
    if (!present("_quill_"))
	clone_object(STAND_OBJ + "quill")->move(this_object());
    if (!present("_piece_of_paper_"))
	clone_object(STAND_OBJ + "paper")->move(this_object());
    if (!present("backpack"))
	clone_object(STAND_OBJ + "backpack")->move(this_object());
*/

/*  Commented out until Moria shaft is fixed  */
/*
    if (!present("rope"))
   clone_object("/d/Shire/moria/obj/rope")->move(this_object());
*/
/*
    for(index = 0; index < MAX_PACKS; index++)
    {
        if (!objectp(packs[index]))
        {
            packs[index] = clone_object(STAND_OBJ + "backpack")->move(this_object());
        }
    }
*/
}
