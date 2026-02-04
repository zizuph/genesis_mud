/* A carriage. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define NO_OF_BEERS     5

int broken;
object jester;

void
reset_room()
{
    int i;
    object hat, beer;

    if (!jester) {
        jester = clone_object(CAMP_DIR + "jester");
        jester -> move(TO);

	hat = clone_object(CAMP_DIR + "hat");
	hat -> add_prop("blood_stained", 1);
	hat -> move(jester);

        for (i=0; i<NO_OF_BEERS; i++) {
            beer = clone_object("/std/drink");
            beer -> set_name("beer");
            beer -> set_short("silver beer");
            beer -> set_long("A silver beer.\n");
            beer -> set_adj("silver");
            beer -> set_soft_amount(100);
            beer -> set_alco_amount(4);
            beer -> add_prop(OBJ_I_WEIGHT, 100);
            beer -> add_prop(OBJ_I_VOLUME, 100);
            beer -> move(jester);
        }
	jester -> command("wear hat");
    } else {
        hat = present("hat", jester);
        if (!hat) {
	    hat = clone_object(CAMP_DIR + "hat");
	    hat -> add_prop("blood_stained", 1);
	    hat -> move(jester);
	    jester -> command("wear hat");
        }
    }
}

void
create_room()
{
    set_short("Dirty carriage");
    set_long(BSN(
	"You are inside a dirty carriage. The owner of this carriage " +
	"must be a sloppy person, since you notice that litter " +
	"and bottles are spread all over the floor. However, you " +
	"pay attention to some details: A funny looking costume, " +
	"a pair of weird shoes, and a mirror have been " +
	"thrown on the floor." 
    ));
    add_item(({"bottles"}), BSN(
        "Unfortunately, all bottles are empty."
    ));
    add_item(({"litter", "dirt"}), BSN(
        "Well, as said before, the owner of this carriage must " +
	"have lost his interest of cleaning long ago."
    ));
    add_item(({"costume", "funny costume"}), BSN(
        "This costume must belong to a jester."
    ));
    add_item(({"shoes", "weird shoes"}), BSN(
        "They look very stupid, with bells attached to them."
    ));
    add_item(({"mirror"}), "@@exa_mirror");
    add_cmd_item(({"mirror"}), "hit", "@@hit_mirror");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CAMP_DIR + "camp_02", "north", 0);

    reset_room();
}

exa_mirror()
{
    string str;

    if (!broken) {
        str = "You see your own face, and realise that the mirror " +
	      "image of it doesn't look any better than the normal " +
	      "would.";
    } else {
	str = "It's broken.";
    }
    return BSN(str);
}

hit_mirror()
{
    string str;

    if (!broken) {
	str = "You hit the mirror and pieces of glass whirl all " +
	      "over the room.";
	say(QCTNAME(TP) + " hits the mirror.\n");
	broken = 1;
    } else {
	str = "You hit the broken mirror and cut yourself.";
	TP -> reduce_hit_point(1);
	TP -> do_die(TP);
	say(QCTNAME(TP) + " hits the mirror and get hurt.\n");
    }
    return BSN(str);
}
