/* mainhall.c: Hallway guarded by Brutus. Serpine, 4-24-95
 * Added no magic attack and no magic props to room Damaris 010/04
 * Revised by Shanoga, 2021 Apr 21:
 *   Removed blockage of arena after fixing Kitiara's sword
 *   which was removing the shadow that prevents death.
 */
#pragma save_binary

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";

#include "defs.h"
#include "/d/Cirath/common/mobber.h"
#include <composite.h>
#include <stdproperties.h>


#define CHESTROOM (GLAD_ROOM + "gldchest")
#define STANDS ("/d/Cirath/guilds/glads/arena/stands")
#define BOARD ("/d/Cirath/guilds/glads/arena/board")
#define STAGING ("/d/Cirath/guilds/glads/arena/staging")
private int alarm_id;

public int
wep_or_arm(object ob)
{
   return (ob->check_armour() || ob->check_weapon());
}

public void
brutus_sweep()
{
   object chest, croom, brutus, *objs;
   int sz;

   alarm_id = 0;

   brutus = present("brutus", this_object());

   if(!brutus)
      return;

   objs = filter(all_inventory(this_object()), wep_or_arm);
   sz = sizeof(objs);

   brutus->command(
      "emote grabs " + COMPOSITE_ALL_DEAD(objs) + " and tosses " +
      (sz > 1 ? "them" : "it") + " to the west."
   );

   croom = find_object(CHESTROOM);

   if(!croom)
      return;

   chest = present("_gladiator_chest", croom);

   if(chest)
   {
      objs->move(chest, 1);
      tell_room(croom, capitalize(COMPOSITE_ALL_DEAD(objs)) +
         (sz > 1 ? " fly" : " flies") + " in from the west and " +
         (sz > 1 ? "land" : "lands") + " in the chest, producing a " +
         "large thunk.\n");
   } else {
      objs->move(croom, 1);
      tell_room(croom, capitalize(COMPOSITE_ALL_DEAD(objs)) +
         (sz > 1 ? " fly" : " flies") + " in from the west and " +
         (sz > 1 ? "land" : "lands") + " on the floor.\n");
   }
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(alarm_id || !present("brutus", this_object()) || !wep_or_arm(ob))
      return;

   alarm_id = set_alarm(30.0, 0.0, &brutus_sweep());
}

void
reset_room()
{
    bring_room_mob("brutus", GLAD_NPC+"brutus", 1, 1);
}

void
create_room()
{
    set_short("barren hallway");
    set_long("This hallway is cold and bare, with nothing to break the "+
      "monotony of angular stone. Unless of course you count the "+
      "dried blood of those who have dared face the Guardian of "+
      "the Gladiators. The sounds of combat echo through this "+
      "hallway from the west to the south, and the screams of "+
      "the arena audience echo from a tunnel running under the "+
      "stands to the north.\n");

    add_item(({"blood", "dried blood"}), "Unremarkable save in amount.\n");
    add_item(({"guard"}),
    "A guard is lurking within some shadows but you cannot reach him.\n");
    
    INSIDE

    add_exit(GLAD_ROOM+"stairwy1.c", "west", "@@west_block@@", 1);
    add_exit(GLAD_ROOM+"entrance.c", "south", 0, 1);
//    add_exit(STANDS, "northeast", "@@stadium_block@@", 1);
//    add_exit(BOARD, "east", "@@stadium_block@@", 1);
    add_exit("/d/Cirath/guilds/glads/arena/gcage.c", "north", "@@stadium_block@@", 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC, 1); 
    reset_room();
}

int
west_block()
{
//    object guard = present ("brutus", TO);
//    if(objectp(guard))
//    {
	if((!IS_MEMBER(TP))&&(!IS_WIZ(TP)))
	{
	    TP->catch_msg("A guard shoves you back shouting: Get lost!\n");
	    return 1;
	}    
	TP->catch_msg("A guard salutes with his axe as you pass.\n");
//    }
    return 0;
}

int
stadium_block()
{  
    /*
    if (present("poison",TP))
    {
	TP->catch_msg("A voice inside your head screams 'No poison "+
	    "may pass this way. Begone!' You feel compelled to obey.\n");
	return 1;
    }
    */

    if (present("_no_stadium_",TP))
    {
	TP->catch_msg("A voice inside your head screams 'You carry a "+
	  "forbidden item. Begone!' You feel compelled to obey.\n");
	return 1;
    }
    /*
     * Remove comments to block entrance to the arena.
     *
    if (!IS_WIZ(TP))
    {
        TP->catch_msg("A guard shoves you back and says: The arena is" +
        " closed. Come back later.\n");
        return 1;
    }
    */
    return 0;
}
