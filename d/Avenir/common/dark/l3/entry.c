// file name: ~Avenir/common/dark/l3/entry.c
// creator(s):
// revision history:
//			Jan 96: Cleaned up A Lot Of Junk(TM)
//				Added reset-ability to the impquest.
//					-=Denis
// purpose:
//    this file also contains routine for pieces of source placing in whole
//    Utterdark. It sdould have been placed in l3/altar.c, but it is heavy
//    without it. So i placed the routine here, in the closest location to
//    l3/altar.c
// note:
//    FOR MORE INFO ON IMPQUEST SEE FILE ~Avenir/QUESTS/impquest.doc
//
//    THIS FILE WORKS AS MAIN DAEMON FOR THE IMPQUEST.
//
// bug(s):
// to-do:

# include "l3_defs.h"
# include "../dark.h"
inherit "/std/room";

int sources_placed;
int *sources;

/* ImpQuest reset information.
 */
static string *source_rooms = ({
        "/d/Avenir/common/dark/l3/sc1",
        "/d/Avenir/common/dark/l3/nc2",
        "/d/Avenir/common/dark/l4/n21",
	"/d/Avenir/common/dark/l3/n8",
        });

static string *imp_rooms = ({
        "/d/Avenir/common/dark/l3/e1",
        "/d/Avenir/common/dark/l3/n1",
        "/d/Avenir/common/dark/l3/n2",
        "/d/Avenir/common/dark/l3/n3",
        "/d/Avenir/common/dark/l3/n4",
        "/d/Avenir/common/dark/l3/n5",
        "/d/Avenir/common/dark/l3/n6",
        "/d/Avenir/common/dark/l3/nc1",
        "/d/Avenir/common/dark/l3/sc1",
        "/d/Avenir/common/dark/l3/wc1",
        });
/*
 * Function name: create_room
 * Descrition: standard room creation routine (well, almost at least).
 */
create_room()
{
    set_short("Entry foyer");
    set_long(
"This room is a large foyer to what appears to be some sort of temple "+
"to the north. The archway on the north end of the room rises up in "+
"a fearful majesty, through which an intensely hot, dry wind is blowing. "+
"Tall obsidian pillars flank the blood-red curves of the arch, looming "+
"over you and creating a sense of dread. The "+
"room tapers to the south, where it enters a narrow, dark hallway.\n");

    add_exit("/d/Avenir/common/dark/l3/n6","south",0);
    add_exit("/d/Avenir/common/dark/l3/altar","north",0);

    IN

    add_item("pillars",
"These tall obsidian pillars are glossy smooth with dark-red, spidery "+
"veins coursing through them. The veins almost seem to give off a "+
"pulsing glow of their own.\n");

    add_item(({"arch","archway"}),
"The terrible arch rises above you, almost seeming to dare you to "+
"enter. It is made from an unknown, blood red stone, and across the "+
"top spidery symbols are carved in thin, blue lines.\n");

    add_item(({"symbol","symbols"}),
"The symbols are too high up for you to make out clearly, so you "+
"cannot ascertain what they might mean.\n");

    add_item("temple",
"You can only dimly make out the temple to the north from the dim "+
"light of this room. The archway seems to obscure your view in "+
"some way, but you can clearly see that there is some large, "+
"strangly shaped altar in the center of the temple.\n");

    sources_placed = 0;
    sources=({ });
}

/****************************************************************************
 * The impquest daemon itself starts here.				    *
 ****************************************************************************/

/*
 * Function name: reset_room
 * Description:   Handles the impquest reset.
 */
reset_room()
{
    source_rooms->reset_source();
    sources = ({ });
    sources_placed = 0;
    if(!ALTAR->ghost_is_here())
    {
        imp_rooms->reset_statues();
        ALTAR->reset_ghost();
    }
}

/*
 * Function name: place_sources
 * Description:   Distributes the limited amount of pieces of source - parts
 *                of impquest (in amount of SEL_SOURCES) among the places
 *                that might contain a piece (in amount of ALL_SOURCES)
 */
place_sources()
{
    int source;

    sources_placed = 1;
    while(sizeof(sources) < SEL_SOURCES)
    {
        source = random(ALL_SOURCES);
        if(member_array(source, sources) < 0)
            sources += ({ source });
    }
}

/*
 * Function name: query_has_sources
 * Description:   Checking if a location can contain piece of source.
 * Arguments:     where - unique number of location. (see 
 *                QUESTS/impquest.doc) and source_rooms variable.
 * Returns:       True if location can contain source.
 */
int query_has_source(int where)
{
    if(!sources_placed)
    {
        place_sources();
    }
    return member_array(where, sources) + 1;
}

/*
 * Function name: clean_up
 * Description:   Preventing the room from unloading from memory and thus
 *                destroying the sources alyout.
 */
public int clean_up()
{
}

