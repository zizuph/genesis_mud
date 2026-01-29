/* 	this is a map for Gelan

    coder(s):   Deinonychus

    history:
            28.1.2000   added read command            Maniac
                21.09.94        removed position of player
		11.09.94	made it a heap-object		Deinonychus
		22.02.93	created				Deinonychus

    purpose:    orientation for players

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/heap";
#include "object.h"
#include <stdproperties.h>

void
create_heap()
{
    /* descriptions */

    set_name("map");
    set_short("map of Gelan");
    set_pshort("maps of Gelan");
    set_long(
    "This is a map of Gelan:     Legend:\n\n"
  + "         |-|  |---|\n"
  + "   \\     |#|  |  %|   / /   Roads:                 Official Buildings:\n"
  + "  \\ \\    |-|  |-| |  / /     1) Palace Road         @) Stable of Gelan\n"
  + "   \\ \\/\\ |c|  |C|-/\\/ /      2) Calia Street        #) Guards Armoury\n"
  + "    \\ \\D\\|-| 5|-|/!/ /       3) Maple Street        %) Guards Headquarters\n"
  + "    /\\6\\/        \\/4/\\       4) Parliament Street   !) Jail\n"
  + "    \\d\\            / /       5) Castle Road\n"
  + "     \\/     $$     \\/        6) High Street\n"
  + "   ---              ---      7) Surgery Street\n"
  + "   |e|              |B|\n"
  + "------              -----   Commerce:              Special Points:\n"
  + "    7               3        a) McCroissant bakery  $) Pillory of Gelan\n"
  + "------              -----    b) Angora Hairdresser  +) Fountain of Gelan\n"
  + "   |E|      ++      |b|      c) Brandybug Inn       &) Gate of Gelan\n"
  + "   ---     ++++     ---      d) Goldiloon Alchemy\n"
  + "     /\\     ++     /\\        e) Miser Shop\n"
  + "    /f/            \\A\\       f) Hammerhead Smithy\n"
  + "    \\/ /\\        /\\2\\/       g) Tomati Empire\n"
  + "    / /g/|-| 1|-|\\a\\ \\ \n"
  + "   / /\\/ |@|  |@| \\/\\ \\     Public Buildings:\n"
  + "  / /    |-|  |-|    \\ \\     A) public lavatory\n"
  + " / /     |#|  |#|     \\ \\    B) Public School of Gelan\n"
  + "  /      |-|  |-|      \\     C) Tourist Office\n"
  + "           |  |              D) Post Office of Gelan\n"
  + "           |&|-              E) Bank of Calia, Gelan branch \n"
  + "           | |\n\n");

  add_prop(HEAP_S_UNIQUE_ID, "gelanmap");
  add_prop(HEAP_I_UNIT_VALUE, 0);
  add_prop(HEAP_I_UNIT_VOLUME, 10);
  add_prop(HEAP_I_UNIT_WEIGHT, 9);

  set_heap_size(1); 
} /* create_heap */


/*
 * Function name: command_read
 * Description  : Define this in an object that can be read.
 * Arguments    : int more - if true, the command should read using more.
 * Returns      : string - an error message upon failure.
 *                int 1  - when successfully read.
 */                                                                           
mixed
command_read(int mor)
{
    if (mor)
        this_player()->more(query_long()); 
    else
        tell_object(this_player(), query_long()); 

    return 1; 
}


/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
