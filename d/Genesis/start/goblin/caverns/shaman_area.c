
/*
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../goblins.h"

static object guard1, shaman;

void reset_room();

void
create_room()
{
    object door;
    ::create_room();

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    change_prop(ROOM_I_INSIDE,1);
    change_prop(ROOM_I_LIGHT,1);
    set_short("The shaman's office.");
    set_long(break_string(
        "This is the refectory of a goblin shaman. " +
        "You know this is so by the evil symbols painted on the wall, " +
        "the " +
        "" +
        "\n\n",70));

    door = clone_object(GOBLIN_OBJ_DIR + "shaman_door2");
    door->move(this_object());

    add_item(({"floor","ground"}), 
        break_string("You see nothing special.\n",70));

    reset_room();
}

wizinfo()
{
    return(break_string("The shaman will be the focus of some minor " +
       "quests, provide healing for spider poison, and teach minor " +
       "spellcraft skill.  He will also provide a hint on how to find " +
       "the Goblin Shaman's guild, when that is ready.\n",70));
}

void
reset_room()
{
    if (!guard1 || !present(guard1, this_object())) {
        guard1 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard1->move_living("east", this_object());
    }

    if (!shaman) {
        shaman = clone_object(GOBLIN_NPC_DIR + "shaman");
        shaman->move_living("east", this_object());
    }

}

int
read_sign()
{
    write("Bwhere de mity Goblin King! [sic]\n");
    return 1;
}

int
block_attack()
{
  write(BSN("You don't want to break the armed truce with these goblins."));
  return 1;
}