/**********************************************************************
 * - no_scry_room.c                                                 - *
 * - This file is to be #included into the room that is not to be   - *
 * - scry-ied using the special entities of Solamnia Knights.       - *
 * - Then in the room you must add the prop:                        - *
 * -      add_prop(ROOM_M_NO_SCRY, query_no_scry);                  - *	
 * - Created by Damaris@Genesis 03/2005                             - *
 **********************************************************************/

#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

private string query_no_scry(); 
private string query_entity();

private string
query_no_scry()
{
  string *messages = ({
        " protective blessing prevents this action.",
        " blessing thwarts this action.",
        " protective light neutralizes this action.",
        " defensive blessing prevents this action.",
        " blessed sanction thwarts this action.",
        " shielding light prevents this action.",
        " protective blessing prevents this attempt.",
        " protective light neutralizes this attempt.",
                      });

  return query_entity() + one_of_list(messages);

}   

private string
query_entity()
{
  string *entity = ({
        "Paladine's",
        "Kiri-Jolith’s",
        "Habbakuk’s",
        "An ancient",
                     });

  return entity[random(sizeof(entity))];
}