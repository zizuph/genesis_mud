/* Oldgarden32.c */
/* janus 920929 */
/*
    Modified: 30 Apr 2003, by Bleys
        - Fixed a typo in one of the add_items (s/varies/vary)

    Modified: 6 May 2003, by Bleys
        - Changed the ITEMS array to use standard
            gems.
        - Changed the ITEMS array to use full paths.
        - Called set_searchable() so that we dodge the
            herbsearch code here in favor of Janus' original
            search code... otherwise the witch's mother
            quest is broken
        - Updated to modern includes & inherit

    Modified: 15 Sep 2003, by Bleys
        - It was inheriting the ogrd_std_room.c copy from my personal
            directory. When I cleaned up my dir, that broke. Duh. Now
            inheriting the proper version.

*/

#include "/d/Terel/include/Terel.h"
inherit MANSION + "grd/ogrd_std_room";

#define ITEM_DIR    MANSION + "grd/"
#define GEM_DIR     "/d/Genesis/gems/obj/"
//#define ITEMS ({"hgem", "hgem", "dagger", 40})
#define ITEMS ({ \
                GEM_DIR + "ruby", \
                GEM_DIR + "ruby", \
                ITEM_DIR + "dagger", \
                40 \
                })

void
reset_room()
{
    NOOFPLANTS = 3;
    NOOFTOOLS = sizeof(setup_search());
    if (skull) skull = 0;
    BIGMAMA = 1;
}


void
create_ogrd_room()
{
    set_short("Hangman's hill");
    set_long("The air here is permeated with evil and a smell of decay. "+
               "You can feel the evil radiate out from a log standing in the "+
               "middle of the small hill. Nothing grows here except the "+
               "ever present thick vines.\n");
    add_exit(MANSION + "grd/ogrd31.c", "south", "@@gogo", 3);
    add_item(({"log","burned log"}), "The log is about two meters high "+
               "and half a meter in diameter. It appears to be scorched as "+
              "if it has been exposed to intense heat. The vegetation except "+
              "for the vines, is burned away in a three meter radius around "+
              "the log. You also see some small burned sticks in a circle "+
              "around the log.\n");
    add_item(({"sticks", "circle", "stick"}),
      "The sticks vary in size but all of them are burned. "+
      "It looks like someone had a big fire here in a distant past.\n");
    SKULL = 1;

    // This room is a quest room, so we want to ditch the herbsearch
    //  stuff in favor of Janus' original search function.
    set_searchable();

}

mixed *
setup_search()
{
    return ITEMS;
}
