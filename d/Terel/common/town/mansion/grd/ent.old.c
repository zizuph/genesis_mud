/* cellar.c */
/* janus 921029 */

inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include </sys/money.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int NOOFTOOLS;
int RND;
reset_room()
{
}
create_room()
{
    set_short("garden entrance");
    set_long(BS("You are standing in a small portal. By going to the north "+
       "you will enter the garden of Despair, where an evil witch was "+
       "burned at the stake. The north wing of the mansion can be reached "+
       " by going south.\n"));
    add_exit(MANSION + "grd/ogrd1", "north",0,0);
    add_exit(MANSION + "wing_n2","south",0,0);
/*
 add_item(({"plaque"}), 
BS("\n"+
"Garden of Despair\n"+
"=================\n"+
"In the year xxxx the witch Ulla was found gilty of practicing witchcraft. She "+
"was sentenced to be burned at the stake and decapitation. "+
"The sentence was carried out, "+
"but as the witch was placed at the stake, she uttered a curse over "+
"the garden, saying that this place no longer should bring happiness "+
"and joy but instead despair and sorrow. "+
"The people at the execution laughed at the old witch and "+
"rejoiced when she burned. After the fire the head was struck of from "+
"the body and the executiomer started to bury the corpse, "+
 "when suddenly the plants in the garden came alive and attacked the people "+
"and the people fled in panic. "+
"Not until after several days some brave guards managed to get to the place of "+
"execution but they could not find any trace of the witch's corpse. "+
"Someone else must have taken and hidden the corpse elsewere. \n"));
*/
    reset_room();    
  }


