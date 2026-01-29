/* 
 * playhouse.c 
 * metaprat - 920703 
 * Just decoration, to give the feeling that the minstrels have somewhere 
 * to play in the evenings.  Also, a donation box to confuse the players ;) 
 * Updated by Shinto 10-19-98
 *    Lilith May 2022: Added this to the venue list for Minstrels and 
 *                     performers.  Updated desc, etc.
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>

object door;

void
create_room() 
{
    set_short("Calathin Playhouse");
    set_long(
      "You are in the Calathin Playhouse.  The performing arts are taken " +
      "very seriously in this town, and unlike towns of this size elsewhere, "+
      "has its own theatre. Ranks of seats line the floor, providing " +
      "seating for about two hundred people, and face a large pine stage "+
      "to the east. "+	  
      "Dozens of townsfolk fill the seats and dally in the rows, waiting "+
      "the next performance to begin. "+	  
	  "Strangely enough, there is no ticket office, only a " +
      "steel donations box by the door. "+
      "A huge fireplace in the south wall probably provides heating, " +
      "important given the severe climate in this area.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    add_item( ({ "stage" }), "A large wooden stage, made of pine.\n");

    add_item( ({ "seat", "seats" }), "Handcrafted from pine and rushes, " +
            "these provide seating for the audience.\n");

    add_item( ({ "box", "donation box" }), 
         "A box, made of thick, strong steel built into the floor of " +
         "the playhouse.\nYou can't open it, but maybe you can break it.\n");

    add_item( ({ "fireplace" }), 
            "No fire is burning at the moment, but presumably when a " +
            "performance is held,\nit will be lit.\n");

    add_cmd_item( ({ "box", "donation box" }),
              ({ "break" }),
                 "You try to force open the donation box, but its thick " +
                 "steel shell defeats you.\n");

    add_npc(CALATHIN_DIR +"npc/std_citizen", 4);
	add_npc(CALATHIN_DIR +"npc/recplayer", 1);
    door = clone_object(CALATHIN_DIR +"obj/play_door");
    door->move(TO);
}
