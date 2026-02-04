/*
The mansion stairs. Mortricia 920906.

Second floor and fall down added by Napture  181092.
                                        English dates  ;-)  ;-)
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define DAMAGE          (this_player()->query_max_hp() * 10 / 100)
/* The above defines damage at 10% of max */
#define NO_GO_STAIR     25  /* DIS required to automatically go down */
#define LIKELY_TO_FALL  50  /* DEX required not to fall ever */

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define GENDER         this_player()->query_pronoun()

#define SAYNAME(x1,x2)  say(                                             \
     ({ break_string(capitalize(x1+this_player()->query_name()+x2), 70), \
        break_string(capitalize(x1+"the " + this_player()                \
                                   ->query_nonmet_name()+x2),       70), \
        break_string(capitalize(x1+"someone"+x2),                   70)  \
     }), this_player())  

#define DOWN_STRS   MANSION + "rooms/bstairs_mid"

void
create_room()
{
    set_short("Top of the Old Stairs");
    set_long(BS(
        "You stand in a tiny little room.  Other than some rickety old " +
        "stairs leading into the darkness below, there is nothing in " +
        "this room at all; apart from the even larger quantity of " +
        "dust that has accumulated here. A tiny passage twists off " +
        "to the south from here.\n"));
   
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
   
    add_exit(MANSION + "second/passage2", "south", 0);
    add_exit(DOWN_STRS, "down", "@@creak");
   add_exit(MANSION + "second/antechamber", "north", 0);

    add_item(({"stairs", "staircase", "rickety stairs"}),
          "A very old set of stairs - more like some old " +
          "planks forming stairs.\n");

    add_item(({"planks", "old planks"}), BS("They must be very tasty as " +
            "the holes in some of them measure upto 2 centi-metres in " +
            "diameter.\n"));
      
    add_item(({"dust", "thick dust"}), "@@dusty_floor"); 
    add_item("cobwebs", "Read the description!  Who mentioned cobwebs?\n");
    add_item(({"footprint", "footprints"}), "@@footprint");

    add_cmd_item(({"planks", "old planks"}), ({"get", "eat"}),
                 ({"Although very old, they are securely fastened down!\n",
                   "Yeuck!  Shame you're not a woodworm!\n"}));
}

dusty_floor()
{
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
              + (TP->query_skill(SS_LOC_SENSE)) > (random(250)+50) ) {
        return "The dust is very thick here.  You can just about make " +
                "out some footprints.\n";
        }
    else { return "The dust is very thick here.  You can feel your feet "+
                  "sinking into the thickness.\n"; }
}

footprint()
{
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
             + (TP->query_skill(SS_LOC_SENSE)) > (random(250)+50) ) {
        return "The footprints lead towards the old stairs.\n";
        }
    else {
        return "You recognise the footprints as your own.\n";
        }
}
    
creak()
{
    if ((this_player()->query_stat(SS_DIS)) < random(NO_GO_STAIR)) {
        write("The stairs look so unsafe that you dare not go down them!\n");
        return 1;
        }
    write("You feel uneasy using these old stairs, but you continue " +
          "down anyway.\n");
    if ((this_player()->query_stat(SS_DEX)) > random(LIKELY_TO_FALL)) {
        write("CRACK!!\n");
        write("CREAK!!\n");
        return 0;
        }
    write("On your way down, you stand on a loose plank!\n" +
            "Ouch!  You unceremoniously land in a painful heap.\n");
    SAYNAME("", " vanishes down the stairs quicker than " +
                      GENDER + " should!\n");
    tell_room(MANSION + "back_stairs", "All of a sudden, " +
            QCTNAME(TP) + " comes tumbling down the stairs!\n");
/*  DAMAGE is defined at start for percentage or actual loss */
    this_player()->reduce_hit_point(DAMAGE);
    return 0;
}
