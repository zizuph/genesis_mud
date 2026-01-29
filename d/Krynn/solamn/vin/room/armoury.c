/*  Passage,   Vingaard Keep     */
/*  Coded by Grace, 04/06/94     */

#include "../knight/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

#define ALLOW_RACK 1

object nglow_rack;

void
create_vin_room()
{
    set_short("Passage to armoury");
    set_long("A wide room forming a passage between the Hall and "+
      "the High Armoury. It is used chiefly as a repository of " +
      "excess armours and weapons, and as a place for Knights to " +
      "prepare for combat without crowding the Armoury. A sign " +
      "hangs from one wall.\n");
    AI(({"ceiling","floor","wall"}),"Grey granite composes this.\n");
    AI("walls","Grey granite compose these.\n");
    AI(({"grey granite","granite"}),"It is a volcanic rock.\n");
    AI("hall","The hall to the south opens into other rooms, and " +
      "continues onwards.\n");
    AI("sign","The sign is black with gold-painted words.\n");
    ACI("sign","read","The sign reads:\n\nThe intent of this room " +
      "is a repository for those items which are of short term use " +
      "only. Those items which may survive longer should be placed " +
      "north of here.\n\n");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    AE(VROOM + "high_armoury", "north", 0);
    AE(VROOM + "north_hallway", "south", 0);
    (VROOM + "high_armoury")->load_me();
    (VROOM + "high_armoury_rack")->load_me();
   reset_room();
}

void
reset_vin_room()
{
#ifdef  ALLOW_RACK
    if (!nglow_rack)
    {
        nglow_rack = clone_object(VOBJ + "nglow_rack");
        nglow_rack->move(TO);
    }
#endif
}
