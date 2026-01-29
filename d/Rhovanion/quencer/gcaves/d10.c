/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"


/*
 * Prototypes
 */
void reset_room();

create_room()
{
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_INSIDE, 1);

    set_short("big hall");
    set_long("This big hall is very different from other parts of caves. "+
             "It is surprisingly clean and well lit by many torches. "+
             "Somehow you can guess that not every goblin is allowed "+
             "into this place. Maybe here lives the goblin lord himself. "+
             "To the north is a door that leads back to the tunnels. Maybe "+
             "you should leave immediately if you don't want to be caught "+
             "here.\n");

  add_item(({"torch","torches"}), "There are many torches fastened to "+
                                  "the walls all around.\n");
  add_item("door", "This is the other side of the secret door. The goblins "+
                   "haven't even tried to hide it from this side. So you "+
                   "can simply push it to get through.\n");
  add_item(({"wall","walls"}),BS("These walls seems to be natural. But "+
              "then again you have seen so many strange things in these "+
              "caves that you are not sure with anything you see or feel.\n"));

  add_exit(CAVE_DIR+"d11", "east", "@@block_exit");

  reset_room();
}

int
block_exit(string room)
{
  if(present("_misty_goblin_", TO) &&
     TP->check_seen(present("_misty_goblin_", TO)))
   {
     write("The goblin lord stops you from passing.\n");
     say(QCTNAME(TP)+" was stopped from going east by the goblin lord.\n");
     return 1;
   }
  return 0;
}

void
reset_room()
{
  object goblin1, key, bottle, halberd, *treasure;
  int i, is_in_treasure; 

  seteuid(getuid());

  if(!find_object(CAVE_DIR+"d12")) clone_object(CAVE_DIR+"d12");
  if(!find_object(CAVE_DIR+"d11")) clone_object(CAVE_DIR+"d11");

  if (!present("_misty_goblin_"))
  {
    if((sizeof(FILTER_LIVE(all_inventory(TO)))) ||
       (sizeof(FILTER_LIVE(all_inventory(find_object(CAVE_DIR+"d12"))))) ||
       (sizeof(FILTER_LIVE(all_inventory(find_object(CAVE_DIR+"d11"))))))
    {
      call_out("reset_room",200);
      return;
    }
    goblin1 = clone_object(NPC_DIR+"goblins/gcave_lord");
    goblin1->add_prop(LIVE_I_SEE_DARK, 1);
    goblin1->arm_me();
    goblin1->move_living("xxx", this_object());
    clone_object(OBJ_DIR+"mirror")->move(goblin1);

    treasure = all_inventory(find_object(CAVE_DIR+"d12"));
    is_in_treasure = 0;
    for(i=0; i<sizeof(treasure); i++ )
      if(MASTER_OB(treasure[i]) == WEAPON_DIR+"halberd_sup")
        is_in_treasure = 1;
    if(!is_in_treasure) 
    {
      halberd = clone_object(WEAPON_DIR+"halberd_sup");
      halberd->move(CAVE_DIR + "d12");
    }
    for(i=0; i<sizeof(treasure); i++ )
      if(MASTER_OB(treasure[i]) == OBJ_DIR+"prisoner_key")
        is_in_treasure = 1;
    if(!is_in_treasure) 
    {
      key = clone_object(OBJ_DIR+"prisoner_key");
      key->move(CAVE_DIR + "d12");
    }
    is_in_treasure = 0;
    for(i=0; i<sizeof(treasure); i++ )
      if(MASTER_OB(treasure[i]) == OBJ_DIR+"bottle")
        is_in_treasure = 1;
    if(!is_in_treasure)
    {
      bottle = clone_object(OBJ_DIR+"bottle");
      bottle->set_max(50000);
      bottle->set_soft(20000+random(20000));
      bottle->set_alco(bottle->query_soft() / 2);
      bottle->set_filled_short("best whiskey");
      bottle->set_name("barrel");
      bottle->set_pname("barrels");
      bottle->set_adj("wooden");
      bottle->set_short("wooden barrel");
      bottle->set_pshort("wooden barrels");
      bottle->move(CAVE_DIR + "d12");
    }
  }
}

init()
{
    ::init();
    add_action("push_something", "push");
}

push_something(something)
{
  if(something=="door")
  {
    TP->catch_msg("You open the door. You quickly pass and the wall swings "+
                  "back closing the small opening.\n");
    say(QCTNAME(TP)+" opens the door and disappears inside. The wall swings "+
        "back closing the small opening.\n");
          tell_room(CAVE_DIR+"t25",QCTNAME(TP)+" enters the room through "+
                                           " the secret door.\n");
    TP->move_living("M",CAVE_DIR+"t25");
          return 1;
   }
 return 0;
}
