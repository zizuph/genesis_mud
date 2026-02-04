/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave_room.c
 *
 * The red dragon lair global inherit cave file. All rooms in the red dragon
 * lair will inherit this file.
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo or two
 *
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define  REDLAIR_HERBS        ({ (KRY_HERB  + "fireweed"),\
                                 (AVE_HERB  + "mittikna"),\
                              })

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    add_action("do_touch",  "touch",  0);
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells faintly like sulfur.\n";
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "air" || str == "scent" || str == "strange scent") {
        write(smell_desc());
        return 1;
    }
    return 0;
}


/*
 * Function name: touch_desc
 * Description:   Is the wall warm or cold?
 * Returns:       The description of the temp. of the walls
 */ 
public string
touch_desc()
{
    return "The walls here feel warm to the touch.\n";
}

/*
 * Function name: do_touch
 * Description:   Handle the touch action
 * Returns:       1/0
 */ 
public int
do_touch(string str)
{
    NF("Touch what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "wall" || str == "walls" || str == "the walls") {
        write(touch_desc());
        return 1;
    }
    return 0;
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Cave");
    set_long("You are standing in a large cavernous tunnel. The ground is littered " +
       "with various sized rocks and debris. The walls have been scorched black " +
       "and heavily marred, yet look smooth to the touch. The ceiling of the cave " +
       "is about twice as high as the cave is wide. The ceiling appears to be " +
       "cleared of any stalactites and looks smooth to the touch just like the " +
       "walls. The air in here is dry and stale.\n");

    add_item(({"stalagmites", "stalagmite"}),
             "They vary in size and are a bit lighter in colour than the " +
             "ground from which they come.\n");

    add_item(({"stalactites", "stalactite"}),
             "Hanging down from the ceiling, they have a rough texture. " +
             "Some of them drip water onto the cavern floor.\n");

    add_item(({"wall", "walls","ceiling","floor","ground"}),
         "The walls and ceiling appear to be burned by intense heat. Deep grooves " +
       "scar the walls and ground. The texture of the ceiling and ground is smooth " +
       "to the touch as if something rubbed back and forth grinding down the " +
       "rough edges.\n");

    add_item(({"grooves","scarring","grove","scar"}),
       "The grooves do not appear to be formed naturally. The grooves look " +
       "as if someone used a hammer and chisel or some type of large sharp " +
       "object when carving them into solid bedrock.\n");

    add_item(({"debris","rocks"}),
       "Various pieces of debris consisting of rocks, burned twigs, branches " +
       "and what appear to be bones.\n");

    add_item(({"bones"}),"Bones varying in size, litter the ground of the cave. " +
       "Most are smashed, broken and burned beyond recognition.\n"); 
  
     set_up_herbs( ({ONE_OF_LIST(REDLAIR_HERBS),
                     ONE_OF_LIST(REDLAIR_HERBS),
                     ONE_OF_LIST(SUBT_HERBS),
                  }),
                  ({"ground","debris","grooves"}), 
                   3 );
    INSIDE;
}

