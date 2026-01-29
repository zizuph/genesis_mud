
/*
     coder(s):	Amelia  & Jaacar

     Added Halloween code to reset_room(), 13/10/02 Uhclem
         (also added to beach1)
     Minor alterations by Maniac 22/8/96 
     moved/modified description 19/2/96 Jaacar
     updated add_items 29/5/95 Amelia
     history:	coded 5/95  	Amelia
*/

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include KR_HERBSEARCH

void
reset_herb_room()
{
    set_searched(random(2));
}

void
reset_room()
{

    /****  Begin Halloween code  ****/
    object ob;
    string *datetext = explode(ctime(time()), " ");
    if (strlen(datetext[2]) == 1)
    {
        datetext[2] = "0" + datetext[2];
    }

    /*
     *  Halloween items are deployed starting at 23:00:01 the day before
     *  Halloween so that they ready for the beginning of the game-wide
     *  scavenger hunt.  The turtle dispenser is invisible to mortals and
     *  requires no entry message.
     */

    if ((datetext[1] == "Oct" &&
        (datetext[2] == "31" ||
        (datetext[2] == "30" && datetext[3] > "23:00:00")))
        ||
        (datetext[1] == "Nov" && datetext[2] <= "03"))
    {
        if (!present("calia_turtle_dispenser", this_object()))
        {
            ob = clone_object("/d/Calia/weenware/turtle_dispenser");
            ob->move(this_object());
        }
    }
    /****  End Halloween code  ****/

    reset_herb_room();
}

void
create_room()
{
    set_short("A white, sandy beach");
    set_long("You are walking on a white, sandy beach. To the west "+
        "the blue-green sea extends all the way to where "+
        "it converges with the blue horizon. Waves crash rhythmically " +
        "on the shore. As you look out over "+
        "the sea, the sun on the waves dazzles your eyes. " + 
        "To your east are sand dunes, while to the south you see a " +
        "little path that leads to a small village.\n"); 

    add_item(({"path", "little path"}),
               ("The path is very simple, a seaside variation of a dirt " +
                "track, i.e. a sand track.\n"));

    add_item(({"village", "small fishing village", "fishing village",
               "small village"}),
             ("It is a small fishing village. You spot some fishing boats " +
              "hauled up on the sand in front of a row of simple huts.\n"));

    add_item(({"boat", "boats", "fishing boats", "fishing boat"}),
              ("They are small fishing boats, " +
               "about ten feet long. Not exactly the type of thing one " +
               "would go shark fishing with, but good enough for a skilled " +
               "fisherman to land a decent catch in.\n"));

    add_item(({"hut", "huts"}), "They are of the rude wooden variety.\n");

    add_item((({"sea", "blue-green sea"})),
            "The sea is blue-green and clear. Waves "+
            "splash on the shore from time to time.\n");

    add_item("water",
             "The water is a clear blue-green and looks warm "+
             "and refreshing.\n");

    add_item("view",
           "There is a beautiful view of the sea, with sun "+
           "sparkling on the waves. To the south is a path leading " +
           "to a small fishing village, "+
           "while to the north is a stretch of beach then " +
           "some rocks. To the east are sand dunes.\n"); 

    add_item("rocks", "Why not go closer and have a look?\n"); 

    add_item((({"horizon", "blue horizon"})),
           "Where the sea meets the sky, there is a point "+
           "where the two seem to blend together.\n");

    add_item("waves",
           "Waves are regularly beating against "+
           "the shore. They appear very inviting.\n");

    add_item((({"beach", "shore"})),
           ("This is a beautiful white sandy beach "+
            "on the shore of the sea.\n"));

    add_item("sand",
           "The sand is sugary white, but is "+
           "rather hard to walk in.\n");

    add_item((({"dunes", "sand dunes"})),
           "The dunes to the east are too steep to climb. "+
           "They are fairly barren except for occasional "+
           "sea grasses.\n");

    reset_room();
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_tell_time(80);

    add_tell("A large wave crashes on the shore.\n");
    add_tell("Sea foam washes against your feet.\n");
    add_tell("Gulls cry and swoop above you.\n");

    add_exit(BEACH+"beach3", "north");
    add_exit(SECTOR_PATH(0,7,0)+"wr_0_7_0", "west");
    add_exit(BEACH+"v_path","south");

    seteuid(getuid(this_object()));
    set_search_places(({"sand"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERBS+"ss_grass");
    add_herb_file(HERBS+"bch_willow");
    add_herb_file(HERBS+"bch_plum");
    add_herb_file(HERBS+"dandelion");
}

int
do_collect(string str)
{
    object sand;
    int num;
    if (str != "sand")
    {
        NF("What?\n");
        return 0;
    }
    sand=clone_object("/d/Calia/sea/objects/sand");
    sand->move(TP,1);
    write("You collect a handful of sand from the beach.\n");
    say(QCTNAME(TP)+" collects some sand from the beach.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_collect,"collect");
}
