/*  this is a room of the town Gelan

    coder(s):   Merlin 
 
    History:    date        who  what      
                14. 9. 94   pb   created 

    purpose:    hospital of the town, here you can get healing, removing
                of poisons, scars, plastic surgery and more
                this is the lobby of the hospital

    exits:      north to the road, south to the corridor with the doors

    objects:    none
    npcs:       a receptionisc

    quests:     none
    special:   

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE


#define DOC_QUAL   5000                
/* the quality of the doc
   
   0           all fails
   1000        all serious fails, chance per factor of injury
   n * 1000    chance for failure with serious disease, 1/n
*/


/*
 * Function name: reset_room
 * Description:   resets the room, installs the npcs
 * Arguments:     none
 * Returns:       none
 */

reset_room()
/* resets the room */
{
    seteuid(getuid());

} /* reset_room */

/*
 * Function name: create_room
 * Description:   creates the room
 * Arguments:     none
 * Returns:       none
 */

create_room()
/* creates the room */
{
    /* descriptions */

    set_short("Healing");
    set_long("This is a test healing room, to test the commands\n\n");

    /* properties */

    add_prop(ROOM_I_INSIDE, 1);		/* this room is inside */

    /* exits */

    // add_exit("", "west", "@@pass_guards", 3);

    /* items in the room */

    // add_item(({"note", "notice"}), 
    //        "                    Berti Chees Hospital (BCH)\n\n"
    //      + "The BCH welcomes you. Don't heistate to ask anything at "
    //      + "the lobby.\n\n");
    //add_item("desk", "This is a huge, white desk, very clean.\n");

    reset_room();
} /* create_room */

/*
 * Function name: heal_me
 * Description:   the player wants to be healed
 * Arguments:     none
 * Returns:       none
 */

int
heal_me()
{
  int hpAdj;                       /* the adjustment to the hp */
  object player;                   /* the player starting this command */
  int hp;                          /* the hp of the player */
  int maxHp;                       /* the max hp of the player */
  int maxHeal;                     /* the maximum number of hps to heal */
  int fail;                        /* the chance to fail */
 
  player = this_player();

  hp = player->query_hp();
  maxHp = player->query_max_hp();
  maxHeal = maxHp - hp;

  /* first we determine the chance of failure in 1/1000*/
  fail = 1000 - hp * 1000 / maxHp;

  /* now we check if the doctor can handle that task */

  if(random(DOC_QUAL) >= fail)
    /* ok, we succeeded */
    hpAdj = random(maxHeal);
  else
    /* too bad, we fail :-) */
    hpAdj = -random(hp);

  player->heal_hp(hpAdj);
  write("I healed " + hpAdj + "\n");

  // now we determine how much hp the player can gain (or lose... :-)

   

  return 1;
}

/*
 * Function name: cure_me
 * Description:   the player wants to be cured from poison
 * Arguments:     none
 * Returns:       none
 */

int
cure_me()
{
  

  return 1;
}

/*
 * Function name: init
 * Description:   add the commands to the player
 * Arguments:     none
 * Returns:       none
 */

void
init()
{
  add_action("heal_me","heal");
  add_action("cure_me","cure");
  ::init();

}

