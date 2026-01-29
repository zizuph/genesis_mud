/* File         : /d/Khalakhor/se_speir/rannoch/room/g_06.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "room.h"

inherit HILL_BASEFILE;

int check_stones();
int check_marks();

int
check_stones()
{
 
    int a_skill = TP->query_skill(SS_AWARENESS);

    if (a_skill <= 30)
    {
        say(QCTNAME(this_player())+ " takes a closer look at the heap of "
                                  + "stones around the oak, but it does not "
                                  + "seem as if " + HE + " found out anything.\n");

        write("The stones are quite big, too heavy for you to lift. Most "
            + "of them are covered in moss, but you do not see anything "
            + "interesting about them.\n");

    }
    else if (a_skill <= 50)
    {
        say(QCTNAME(this_player())+ " takes a close look at the stone circle "
                                  + "around the giant oak, and it looks "
                                  + "like " + HE + " found out something "
                                  + "interesting.\n");

        write("The stones are quite big, too heavy for you to lift. Most "
            + "of them are covered in moss, and several looks to be below "
            + "ground. You think you can see some kind of marks on a few "
            + "of them.\n");

    }
    else if (a_skill > 50)
    {
        say(QCTNAME(this_player())+ " makes a thorough search of the stones "
                                  + "lying around the base of the huge oak, "
                                  + "and by the look of " + HIS + " face, you "
                                  + "think indeed that " + HE + " found "
                                  + "something.\n");

        write("The stones are quite big, too heavy for you to lift. Most "
            + "of them are covered in moss, and several looks to be below "
            + "ground, probably quite deep down too. You can see some marks "
            + "on some of the stones, a few less eroded than others.\n");
    }

    return 1;
}

int
check_marks()
{

    int a_skill = TP->query_skill(SS_AWARENESS);
    int l_skill = TP->query_skill(SS_LANGUAGE);

    if (a_skill <= 30)
    {
         write("You find no marks.\n");
    }
    else if (a_skill <= 999 && l_skill <= 30)
    {
        write("The marks are very hard to see, they are mere "
            + "traces of what once might have been runes or "
            + "other inscriptions. No matter how many you look "
            + "at, you can not find a single one that makes any "
            + "sense at all.\n");
    }
    else if (a_skill <= 50 || a_skill && l_skill <= 50)
    {
        write("The marks are hard to see, but you manage to "
            + "find a couple of stones with more easily seen "
            + "marks upon them. It looks like very old runes, "
            + "in a language unknown to you. Some resemble "
            + "simple motifs such as animals and trees.\n");
    }
    else if (a_skill > 50 && l_skill > 50)
    {
        write("The marks are hard to see, but you manage to "
            + "find a couple of stones with more easily seen "
            + "marks upon them. The marks are actually very "
            + "old runes, but even to you they make no sense, since "
            + "the language must be forgotten completely. But "
            + "some of the marks are symbols, depicting either "
            + "animals, people, or plants. You make out a couple "
            + "of boars on one stone, and a really faded rat "
            + "or mouse on another. A few stones show people with "
            + "sticks in their hands and wearing long robes as "
            + "well as ordinary people and warriors, and "
            + "on many stones you see trees, leaves, and vines.\n");
    }

    return 1;
}

void
do_view()
{
     clone_object(OBJ + "view_object")->move(TP);   
}

public void
create_khalakhor_room()
{

    create_loch_room();

    add_item(({"view","surroundings"}),
               "");
    add_item(({"forest","trees","woods","woodland","woodlands"}),
               "No trees grow up here, except the giant oak at the "
             + "very center of the hilltop. The forest surrounding "
             + "this hilltop stretches out in all directions.\n");
    add_item(({"hilltop","hill","summit"}),
               "This is the top of the hill, which is bare of any "
             + "growth except grass and a few small shrubs. The "
             + "view is excellent, since there is nothing here "
             + "to block your view. At the very highest point of "
             + "the hill grows a giant oak amid a circle of stones.\n");           
    add_item(({"oak","tree"}),
               "It is huge, its branches stretching out across "
             + "the whole hilltop, and high into the sky. Around "
             + "the base of its trunk you notice a ruined stone "
             + "structure.\n");
    add_item(({"branch","branches","leaves","leaf","foliage"}),
               "The branches of the oak spreads out across the whole "
             + "hilltop, bearing green-grey leaves and acorns.\n");
    add_item(({"acorn","acorns"}),
               "You don't see many of them, not even on the ground.\n");
    add_item(({"heap","pile","cairn","heap of stones","heap of old stones",
               "stone circle","structure","ancient structure",
               "remains","stone structure","ruined stone structure",
               "ruin","ruins"}),
               "The stone circle around the base of the oak suggests "
             + "that here was once some kind of structure. That must "
             + "truly have been long in the past, since a oak of this "
             + "size must be several hundred years old. The stones "
             + "themselves might be worth having a closer look at.\n"); 

    add_cmd_item(({"cairn","stones"}),
                 ({"inspect","examine","exa"}),
                    check_stones);
    add_cmd_item(({"marks","mark","rune","runes","symbol",
                   "symbols","etching","etchings","motif",
                   "motifs","picture","pictures"}),
                 ({"inspect","examine","exa"}),
                    check_marks);
    add_cmd_item(({"stones","heap","over stones","cairn",
                   "over the stones"}),
                   "climb",
                   "It is not much to climb over, it is all just "
                 + "a low pile of old stones.\n");
    add_cmd_item(({"oak","tree","giant tree","giant oak","the oak",
                   "the tree","up"}),
                   "climb",
                   "You do not seem to able to find anything to hold "
                 + "to, the trunk is too high.\n");
    add_cmd_item(({"view","surroundings"}),
                 ({"exa","examine"}),
                   do_view);

    add_exit(ROOM + "g_05.c","west",0,3,1);
    add_exit(ROOM + "f_05.c","northwest",0,3,1);
    add_exit(ROOM + "f_06.c","north",0,3,1);
    add_exit(ROOM + "f_07.c","northeast",0,3,1);
    add_exit(ROOM + "g_07.c","east",0,3,1);
    add_exit(ROOM + "h_07.c","southeast",0,3,1);
    add_exit(ROOM + "h_06.c","south",0,3,1);
    add_exit(ROOM + "h_05.c","southwest",0,3,1);

    set_short("On a hilltop");
    set_long("You stand on the highest spot available for miles, "
           + "offering an incredible view of your surroundings. "
           + "At the very top of the hill stands an enormous oak, "
           + "its branches covering almost the entire hilltop. "
           + "Except for the oak, not much grows up here, even the "
           + "heather seems reluctant to cover the hilltop.\n");

    create_room_tells();

}

void
create_room_tells()
{

    add_tell(({"A chilling wind sweeps up from the east, whistling "
             + "through the grass, and then dies away.\n",
               "The leaves of the mighty oak rustle in the wind.\n",
               "You notice a lone bird circling high above you.\n",
               "A fierce, cold wind sweeps up from the east, as "
             + "if a higher power wants you off the hilltop.\n",
               "The mighty oak groans slightly in the breeze.\n",}));

    set_tell_time(440);
}


