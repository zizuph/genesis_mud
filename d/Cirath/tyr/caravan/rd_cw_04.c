/* rd_cw_04: Caravan Way section 4. */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/teamer.h"


void
reset_room()
{
    if (leader) return;
    bring_room_team(TYR_NPC+"tmpl_mid.c", 1, 2, TYR_NPC+"hgiant.c", 1); 
    leader->set_random_move(20);
    leader->set_restrain_path(({TYR_CARAVAN, TYR_MERCHANT}));
    leader->set_monster_home(TYR_CARAVAN+"rd_cw_04");
}

void create_room()
{
    ::create_room();
    set_short("central caravan way");
    set_long ("A massive swarm of people mill about, some heading "+
              "along Caravan Way, while others enter the "+
              "Message Center to the north. Only a few head "+
              "into the store to the south, these all seeming nervous, "+
              "as if some law was being broken within.\n");
    add_item(({"swarm", "people"}), "Many are merchants, "+
              "eager to send messages to their far flung holdings.\n");
    add_item(({"store"}), "Some bones spelling out the word 'Weaponsmith' "+
              "are nailed to the front.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(GLAD_DIR+"room/postoffc.c", "north", 0, 1);
    add_exit(TYR_CARAVAN+"rd_cw_05.c", "east", 0, 1);
    add_exit(TYR_BONESMITH+"bonesmith.c", "south", 0, 1); 
    add_exit(TYR_CARAVAN+"rd_cw_03.c", "west", 0, 1);

    reset_room();
}
