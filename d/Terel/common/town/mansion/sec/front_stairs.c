/*
The mansion stairs. Mortricia 920906.

Second floor and fall down added by Napture  181092.
*/

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

/* This defines damage as 20% of maximum hits */
#define DAMAGE          ((this_player()->query_max_hp() * 20 ) / 100)

#define NO_GO_STAIR     50 /* DIS required to automatically use stairs */
#define TOO_DUMB        75 /* INT required to know the stairs aren't safe */

#define BS(message)    break_string(message, 70)
#define TP             this_player()

#define DOWN_STRS  MANSION + "stairs"
#define BOTTOM     MANSION + "basement/hall5"

void
create_room()
{
    set_short("Top of the Main Stairs");
    set_long(BS(
        "You stand on a grand landing.  The landing is governed " +
        "by a large balustrade staircase leading to the floor below.  " +
        "This room is truly impressive - what you can see of it under " +
        "all the dust and grime.  To the northeast, there seems to be " +
	"a long and big room.\n"));
   
    add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(MANSION + "second/hall1", "west", 0);
   add_exit(MANSION + "second/gallery_w", "northeast", 0);
    add_exit(DOWN_STRS, "down", "@@creak");

    add_item(({"stairs", "staircase", "balustrade stairs"}),
        "A gothic set of oak balustrade stairs leading down.\n");
        
    add_item(({"dust", "grime"}), "It is beginning to take over " +
                                  "the whole room.\n");

    add_prop(OBJ_S_WIZINFO, BS("Due to the way checks are made " +
                "against a player's DIS and INT, most wizzes might " +
                "have difficulty going down here - so it's been set " +
                "to allow wizzes straight down without checking.  " +
                "Also, ghosts don't stand on things, so can go " +
                "up and down freely.\n"));
}

creak()
{
    string gender;
    gender = this_player()->query_pronoun();
    
    write("The stairs look very unsafe!\n");

    if ((TP->query_wiz_level()) || (TP->query_ghost())) { return 0; }
    
/* Not brave enough to try the stairs */  
    if((TP->query_stat(SS_DIS)) < random(NO_GO_STAIR))  {
        write("You decide not to continue down them.\n");
        say(QCTNAME(TP) + " starts to go down the stairs.\n" +
              "But " + gender + " quickly scampers back up.\n");
        tell_room(DOWN_STRS, "You see movement at the top of the stairs.\n"); 
        return 1;
        }
        
/* Brave - but check to see if they are dumb enough! */    
    write("You are so brave you continue anyhow.\n" +
          "The stairs are obviously in a worse state than you expected.\n");
    if ((TP->query_stat(SS_INT)) > random(TOO_DUMB)) {

/* Too clever to go down, but random check so they might go down anyway */
        if (random(1)) {
            write("You realise that the stairs wont take your " +
                  "weight and return to the landing.\n");
            say(QCTNAME(TP) + " starts to go down the stairs.\nBut " +
                  gender + " wisely decides to return to the landing.\n");
            tell_room(DOWN_STRS, "You see movement at the top of " +
                                 "the stairs.\n");
            return 1;
            }
        }

/* Brave and foolhardy enough to go down the stairs..... */
    write("You loose your footing halfway and tumble all the way down.\n");
    TP->reduce_hit_point(DAMAGE);
    say(QCTNAME(TP) + " bravely falls head-first down the stairs.\n");
    tell_room(DOWN_STRS, "Suddenly, " + QCTNAME(TP) +
                         " goes tumbling past you down the stairs!\n");
    tell_room(BOTTOM, "Suddenly, " + QCTNAME(TP) +
                      " comes tumbling down the stairs.\n");
    this_player()->move(BOTTOM);
    return 1;
}

