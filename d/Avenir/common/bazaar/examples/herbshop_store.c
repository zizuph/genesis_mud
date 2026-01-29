/*
 *   The storage room of the Hobbiton drugstore
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "defs.h"
#include "/sys/stdproperties.h"

#define MAX_REFRESH 10
#define MAX_TOBS 10
#define KNOWN_HERBS ({	HERB_DIR + "huckleberry", \
			HERB_DIR + "parsley", \
			HERB_DIR + "treemushroom", \
			HERB_DIR + "pawnrose" })

#define KNOWN_TOBS ({	OBJ_DIR + "tob_bree", \
			OBJ_DIR + "tob_home_brew", \
			OBJ_DIR + "tob_northeast", \
			OBJ_DIR + "tob_south", \
			OBJ_DIR + "tob_west", \
			OBJ_DIR + "tob_old_brandy" })

/* Prototypes */
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
   set_short("Herbshop storage room");
   set_long(break_string(
      "You have entered the dusty storage room of the herbshop. "
    + "This is where the owner of the shop stores all his items that "
    + "are for sale. "
    + "You better leave the stuff here alone, or else the owner of "
    + "the shop will be upset with you.\n",70));

   add_exit(HINROOM_DIR + "herbshop","east");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   reset_room();
}

void
reset_room()
{
   object *obs;
   int total, new_clones, i, s, tobnum;

   total = 0;
   tobnum = 0;
   obs = all_inventory(this_object());

   for (i=0; i<sizeof(obs); i++)
   {
      s = obs[i]->num_heap();
      total += s;
      if (s == 0)
         tobnum++;
   }
   new_clones = MAX_REFRESH - total;  

   s = sizeof(KNOWN_HERBS);
   for (i=0; i<new_clones; i++)
      clone_object(KNOWN_HERBS[random(s)])->move(this_object());

   new_clones = MAX_TOBS - tobnum;
   s = sizeof(KNOWN_TOBS);
   for (i=0; i<new_clones; i++)
      clone_object(KNOWN_TOBS[random(s)])->move(this_object());
}
