/*
 * What         : A newly drawn map
 * Used by      : Handed out my minotaur captain Corth sailing the Bloodsea.
 *                A quest item for the Toron_missing_standard quest.
 *                /d/Ansalon/goodlund/bloodsea/obj
 * Description  : A map over southern mithas, X shows the location of the
 *                camp the player is searching for.
 * Made by      : Cherek, Feb 2007
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <composite.h>

string map_desc()
{
    return "                                                   \n" +
           "                                                   \n " +
           "                                                   \n " +
           "                  O                                \n " +
           "                  |                                \n " +
           "                  O                                \n " +
           "                  |                                \n " +
           "                  O                                \n " +
           "                   \\                              \n " +
           "                    O                              \n " +
           "                     \\                            \n " +
           "                  O-O-O          ################  \n " +
           "                                #    ~             \n " +
           "                              #   ~                \n " +
           "       ####         X        #  ~                  \n " +
           "   ~   ~   #     ############  ~   ~               \n " +
           "     ~   ~  #####  ~   ~   ~  ~                    \n " +
           "          ~   ~   ~   ~   ~   ~                    \n " +
           "                                                   \n " +
           "                                                   \n ";
}
                     
void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("map");
    add_name("newly drawn map");
    add_name("new map");
    add_name("newly map");
    add_name("drawn map");
    set_pname("newly drawn maps");
    set_adj( ({"newly", "drawn" }) );
    set_short("newly drawn map");
    set_pshort("newly drawn maps");
    set_long(map_desc);

    add_cmd_item("map","read", map_desc);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 1000);

}
