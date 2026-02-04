/*
The mansion stairs. Mortricia 920906.

Second floor and fall down added by Napture  181092.
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

/* this defines percentage damage of max hit points - currently 10% */
#define DAMAGE          (this_player()->query_max_hp() * 10 / 100)
#define NO_GO_STAIR     25 /* DIS required to automatically use stairs */
#define LIKELY_TO_FALL  50 /* DEX required not to fall ever */

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define GENDER	    this_player()->query_pronoun()	

#define SAYNAME(x1,x2)  say(                                             \
     ({ break_string(capitalize(x1+this_player()->query_name()+x2), 70), \
        break_string(capitalize(x1+"the " + this_player()                \
                                   ->query_nonmet_name()+x2),       70), \
        break_string(capitalize(x1+"someone"+x2),                   70)  \
     }), this_player())  

#define UP_STAIRS  MANSION + "rooms/bstairs_top.c"
#define DOWN_STRS  MANSION + "rooms/bstairs_bot.c"

void
create_room()
{
    set_short("The Old Stairs");
    set_long(BS(
   	"You stand in a very small room.  A very old, rickety set of " +
   	"stairs leads both up and down here.  Other than these stairs, " +
   	"there is no sign that life has ever existed here.  Even the " +
   	"cobwebs so common with the rest of the house seem to have " +
        "avoided this room.\n"));
   
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);	
   
    add_exit(UP_STAIRS, "up", "@@creak1");
    add_exit(DOWN_STRS, "down", "@@creak0");

    add_item(({"stairs", "staircase", "rickety stairs", "old stairs"}), BS(
        "The stairs are made of some makeshift planks that seem to " +
        "have been put up in a hurry.\n"));
    add_item(({"planks", "makeshift planks"}), "They look very fragile.\n");
    add_item("cobwebs", "The lack of cobwebs makes you feel very uneasy.\n");
    add_item("dust", "There is no dust to be seen anywhere.\n");
}

creak0()
{
    if((TP->query_stat(SS_DIS)) < random(NO_GO_STAIR))  {
        write("The stairs look too unsafe for you to continue!\n");
        SAYNAME("", " looks nervously at the stairs.\n");
        return 1;
        }
    write("You feel uneasy using these old stairs, but you continue " +
          "down anyhow.\n");
    if((TP->query_stat(SS_DEX)) > random(LIKELY_TO_FALL))  {
        write("CRACK!!\nCREAK!!!\n");
        return 0;
        }
    write("On your way down, you stand on a loose plank!\n" +
          "Ouch!  You unceremoniously fall down in a painful heap.\n");
    TP->reduce_hit_point(DAMAGE);
    SAYNAME("", " disappears quicker down the stairs than " +
                GENDER + " should have!\n");
    tell_room(DOWN_STRS, "Suddenly, " + QCTNAME(TP) +
                         " comes tumbling down the stairs!\n");
    return 0;
}

creak1()
{
   if((TP->query_stat(SS_DIS)) < random(NO_GO_STAIR)){
        write("The stairs look too unsafe for you to continue!\n");
        say(QCTNAME(TP) + " looks nervously at the stairs.\n");
        return 1;
        }
    write("You feel uneasy using these old stairs, but you continue " +
          "up anyhow.\n");
    if((TP->query_stat(SS_DEX)) > random(LIKELY_TO_FALL)){
        write("CRACK!!\nCREAK!!!\n");
        return 0;
        }
    write("On your way up, you stand on a loose plank!\n" +
          "Ouch!  You unceremoniously fall back down in a painful heap.\n");
    TP->reduce_hit_point(DAMAGE);
    tell_room(UP_STAIRS, QCTNAME(TP) + " appears on the stairs, then " +
                         "suddenly disappears!\n");
    SAYNAME("", " doesn't get very far before tumbling back down!\n");
    return 1;
}
