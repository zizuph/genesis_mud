
/*   Coded by Amelia andJaacar */
/*   Minor alterations by Maniac 22/8/96 */ 
/*   Moved/modified room description 19/2/96   Jaacar */
/*   corrected alarm message to player, 16/12/95 */

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include KR_HERBSEARCH

#define MERMAIDD "A beautiful maiden, swimming in the sea.\n"

int seen;
object to = this_object();

void
reset_herb_room()
{
    set_searched(random(3));
}

void
reset_room()
{
    seen = 0;
    reset_herb_room();
}

void
create_room()
{
    set_short("A white, sandy beach");
    set_long("You are walking on a white, sandy beach. To the west "+
	"the blue-green sea extends all the way to where "+
	"it converges with the blue horizon. Waves crash on the "+
	"shore. "+
	"To the east are sand dunes, and the beach stretches "+
        "north and south from here. Far to the south you "+
        "notice a few huts. As you look out over "+
        "the sea, the sun on the waves dazzles your eyes...\n");


    add_item((({"sea", "blue-green sea"})),
		VBFC_ME("mermaid"));

    add_item("water",
             "The water is a clear blue-green and looks warm "+
             "and refreshing.\n");

    add_item("view",
           "There is a beautiful view of the sea, with sun "+
           "sparkling on the waves. To the south is more beach, "+
           "while to the north is a small stretch of beach then " +
           "some rocks. To the east are sand dunes.\n"); 

    add_item(({"huts", "rocks"}), 
            "Why don't you walk over and have a look?\n"); 

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
    add_exit(BEACH+"beach1","north");
    add_exit(SECTOR_PATH(0, 5, 0)+"wr_0_5_0", "west");
    add_exit(BEACH+"beach3","south");

    seteuid(getuid(this_object()));
    set_search_places(({"sand"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERBS+"poison_ivy");
    add_herb_file(HERBS+"salt_wort");
    add_herb_file(HERBS+"bch_plum");
    add_herb_file(HERBS+"cord_grass");
}


void
swim_away(object tp)
{
   if (present(tp, to))
   {
	tp->catch_msg("The maiden waves to you and calls "+
		"out in a language you can't recognize over "+
		"the sound of the waves.\n");

	tp->catch_msg("She seems to gesture to you to join "+
		"her.\n");

	tp->catch_msg("She turns and dives "+
		"into the waves, disappearing from view.\n");

	tp->catch_msg("But just as she disappears with a "+
		"splash, you see what appears to be a large fish tail, "+
		"slap the surface of the water, and disappear.\n");

	tell_room(environment(tp),"You hear a big splash!\n",({tp}));
	tp->catch_msg("You rub your eyes in disbelief!\n");
	tell_room(environment(tp),  QCTNAME(tp)+ " rubs "+
		tp->query_possessive()+" eyes and seems surprised.\n", ({tp}));
   }

   remove_my_desc(MERMAIDD);
   remove_item("maiden");
   remove_item("golden-haired maiden");
}


string
mermaid()
{
   int id;
   object tp = this_player();

   if (!seen) {
       tp->catch_msg("As you look out over the sea, "+
             "rather far from shore you see a beautiful, golden-haired "+
             "maiden swimming in the waves.\n");
       add_item((({"maiden", "golden-haired maiden"})),
            ("She is gorgeous and seems to be smiling at "+
             "you, even from this distance. Her hair is very long, "+
             "and trails around her in the sea.\n"));
       add_my_desc(MERMAIDD);
       id = set_alarm(60.0, 0.0, &swim_away(tp));
       seen = 1;
       return "";
   }
   return ("The sea is blue-green and clear. Waves "+
          "splash on the shore from time to time.\n");
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
