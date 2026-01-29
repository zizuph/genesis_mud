/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "climb.h"

/*
 * Prototypes
 */
void reset_room();

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    set_short("small cave");
    set_long(BS("This is a small dim cave. Fortunately there is some light "+
                "comming inside through the small hole above your head so you "+
                "are able to see somehow.\n"));

    add_item("hole", "You have entered this room through it. So maybe you "+
                     "should use it again.\n");

    add_exit(MISTY_DIR+"r3", "down", "@@block_exit:" + 
               file_name(this_object()) + "|"+MISTY_DIR+"r3@@");

    reset_room();
}

int
block_exit(string room)
{
  if(present("_misty_goblin_", TO) &&
     TP->check_seen(present("_misty_goblin_", TO)) &&
     (TP->query_prop(LIVE_O_LAST_ROOM) != find_object(room)))
   {
     write("The goblin guard stops you from passing.\n");
     say(QCTNAME(TP)+" was stopped from passing from the goblin guard.\n");
     return 1;
   }
  return 0;
}

void
reset_room(){
  object goblin1, goblin2, /* there are several goblins here    */
         armour, weapon, *treasure;
  int i, is_in_treasure;

  seteuid(getuid());

  if(!find_object(MISTY_DIR+"r3")) clone_object(MISTY_DIR+"r3");

  if(!present("_misty_goblin_"))
  {
    if((sizeof(FILTER_LIVE(all_inventory(TO)))) &&
       (sizeof(FILTER_LIVE(all_inventory(find_object(MISTY_DIR+"r3"))))))
    {
      call_out("reset_room",200);
      return;
    }
    goblin1 = clone_object(NPC_DIR+"goblins/goblin_high");
    goblin1->add_prop(LIVE_I_SEE_DARK, 1);
    goblin1->arm_me();
    goblin1->move_living("xxx", this_object());
    goblin2 = clone_object(NPC_DIR+"goblins/goblin_med");
    goblin2->add_prop(LIVE_I_SEE_DARK, 1);
    goblin2->arm_me();
    goblin2->move_living("xxx", this_object());
    goblin1->team_join(goblin2); /* goblin1 will be the leader */

    armour = clone_object("/d/Rhovanion/common/armours/prisoner_cloak");
    weapon = clone_object("/d/Rhovanion/common/weapons/prisoner_sword");

    treasure = all_inventory(find_object(MISTY_DIR+"r3"));
    is_in_treasure = 0;
    for(i=0; i<sizeof(treasure); i += 1)
      if(MASTER_OB(treasure[i]) == MASTER_OB(armour))
        is_in_treasure = 1;
    if(!is_in_treasure) armour->move(MISTY_DIR+"r3");
    is_in_treasure = 0;
    for(i=0; i<sizeof(treasure); i += 1)
      if(MASTER_OB(treasure[i]) == MASTER_OB(weapon))
        is_in_treasure = 1;
    if(!is_in_treasure) weapon->move(MISTY_DIR+"r3");
  }
}

init()
{
    ::init();
    add_action("enter_hole", "enter");
}

int enter_hole(string hole){
  if(hole=="hole")
   if(!block_exit(MISTY_DIR+"r1"))
   {
     TP->catch_msg("You squeeze up through the hole.\n");
     say(QCTNAME(TP)+" squeezes up through the hole.\n");
     tell_room(MISTY_DIR+"r1",QCTNAME(TP)+" enters crawling from behind the tree.\n");
     TP->move_living("M",MISTY_DIR+"r1");
     return 1;
   } 
  NF("Enter what?\n");
  return 0;
}
