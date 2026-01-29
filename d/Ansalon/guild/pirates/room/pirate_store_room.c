/*
* The store for the Pirates guild, code used from the Palanthas shop.
* Adapted by Elmore.
* 
* June 15th 2006: Navarre, The shop only reset the monkeys, parrots and
* other objects when the first hook has been bought.
* I have fixed this strange requirement of the items resetting.
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"

// Doubling the number of items on this list, yields
// the number listed here divded by 2, for whatever
// reason.
#define NUM_HOOKS      3
#define NUM_MONKEYS    8
#define NUM_PATCHES    4
#define NUM_PARROTS    2
#define NUM_BEARDS     3
#define NUM_MAPS       4
#define NUM_PEGLEGS    4
#define NUM_SPYGLASSES 2
#define NUM_FLAGS      3


mixed pirate_items = ({"/d/Ansalon/guild/pirates/obj/hook", NUM_HOOKS,
                       "/d/Ansalon/guild/pirates/obj/monkey", NUM_MONKEYS,
                       "/d/Ansalon/guild/pirates/obj/patch", NUM_PATCHES,
                       "/d/Ansalon/guild/pirates/obj/parrot", NUM_PARROTS,
                       "/d/Ansalon/guild/pirates/obj/beard", NUM_BEARDS,
                       "/d/Ansalon/guild/pirates/obj/map", NUM_MAPS,
                       "/d/Ansalon/guild/pirates/obj/pegleg", NUM_PEGLEGS,
                       "/d/Ansalon/guild/pirates/obj/pirate_flag1", NUM_FLAGS,
                       "/d/Ansalon/guild/pirates/obj/pirate_flag2", NUM_FLAGS,
                       "/d/Ansalon/goodlund/bloodsea/obj/spyglass", NUM_SPYGLASSES});

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}

create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");
   
   add_exit("pirate_shop","west");

   INSIDE;  /* This is an inside room */
   set_default_stock(pirate_items);
   reset_room();
}

int get_number_of_items(string item)
{ 
   object* items = filter(all_inventory(this_object()), &->id(item));
   return sizeof(items);
}

reset_room()
{
   seteuid(getuid(TO));
   reset_store();
}
