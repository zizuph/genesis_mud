/* A horror chamber. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"
#define NO_OF_DEMONS    3

object *demons;

public void
move_here(object ob)
{
    ob->move_living("xx", TO);
}

public void
reset_room()
{
    int i;
    object stone;

    for(i=0; i<NO_OF_DEMONS; i++) {
	if (!demons[i]) {
            demons[i] = clone_object(HAUN_DIR + "demon");
            stone = clone_object(HAUN_DIR + "stone");
            if (i == 0) {
                stone->set_adj("black");
            }
            if (i == 1) {
                stone->set_adj("white");
            }
            if (i == 2) {
                stone->set_adj("glowing");
            }
            stone->move(demons[i]);
            set_alarm(itof(2+2*i*i), -1.0, &move_here(demons[i]));
        }
    }
}

public void
create_room()
{
    set_short("Dirty chamber");
    set_long(
        "You are standing in a small and dirty chamber. " +
        "The chamber has been carved out directly from the " +
        "rock. The walls and the ground are wet and slippery. " +
        "The chamber is lit up by some glowing stones which are " +
        "embedded in the rock.\n"
    );
    
    add_item(({"stones", "glowing stones"}), "They glow with a yellow " +
             "light. They are firmly embedded in the rock and cannot " +
             "be removed.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAUN_DIR + "house_7", "north", "@@leave");

    demons = allocate(NO_OF_DEMONS);

    reset_room();
}

public int
leave()
{
    int i;

    for (i=0; i<NO_OF_DEMONS; i++) {
	if (demons[i]) demons[i]->haunt(TP);
    }
    return 0;
}
