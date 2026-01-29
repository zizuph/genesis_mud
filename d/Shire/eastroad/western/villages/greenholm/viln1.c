/* 2004/11/07 Last update
 * 2017/7/25 - Reformatted text
 */

#include "../local.h"

inherit VILLAGE;

int do_enter(string str);
object worm, girl;

void
create_village_room()
{
    areaname = "Greenholm";
    land = "the Shire";
    areatype = 2;
    areadesc = "path";
 
    extraline = "The geographic center of the village Greenholm is not " +
        "much for the eye to take in. A few holes have been dug out of " +
        "the larger hills around, and an actual building is to the north, " +
        "with a large red sign hanging from above the door.";

    add_item(({"actual building","building","pub","north building"}),
        "This relatively large building is made of stone and wood. The "+
        "wood has been weathered to a grey-black, nearly matching "+
        "the dark stone.\n");

    add_item(({"sign","red sign","large red sign"}),
        "The sign depicts an apparent caricature of a gruff, ruddy-faced " +
        "hobbit. There is writing above it.\n");

    add_item("writing","It is quite legible.\n");
 
    add_cmd_item("sign","read","The sign reads: The Bounder.\n");
    add_cmd_item("writing","read","The sign reads: The Bounder.\n");

    add_item(({"village","greenholm"}),
        "This village, named Greenholm is quite small indeed. It consists " +
        "of only a few burrows and the Bounder, the local pub.\n");

    add_item(({"hobbit holes","holes","hobbit-holes","smials","burrows"}),
        "The burrows are cut into the western hillside, all except one " +
        "guarded by a big round door. The nearest burrow's door is " +
        "open, you could probably enter the burrow.\n");

    add_item(({"rolling hills","dales","hills","scene"}),
        "The rolling hills to the south are covered with grass, and look " +
        "very comfortable for relaxing. The pastoral scene of hill and dale "+
        "makes you sleepy, in fact.\n");

    add_item(({"door","big round door","round door"}),
        "All of the holes in this area seem to be closed off by large "+
        "round doors, designed in the hobbit fashion. One reason they "+
        "might be so big is for the hobbits to get their bellies through "+
        "the door.\n");

    add_exit(EAST_R_DIR + "er7n","south");
    add_exit(GREENHOLM_DIR + "inn","north");
    add_exit(GREENHOLM_DIR + "viln2","northeast");
    reset_shire_room();
}

void
reset_shire_room()
{
    object worm;
//    object girl;

    setuid();
    seteuid(getuid());

// We dont want a worm everytime the room resets, just occasionally
// added by Finwe, August 2017
   if(random(10) > 5)
   {
        if(!present("worm") || !objectp("worm"))
        {
            worm = clone_object(EAST_R_NPC+ "worm");
            worm->move(TO);
        }
    }
/*  
  if(!present("brunhilda"))
    {
      girl = clone_object(EAST_R_NPC + "girl");
      girl->move(TO);
    }
*/

    if(!objectp(girl))
    {
        girl = clone_object(EAST_R_NPC + "girl");
        girl->move(TO);
    }
}

void
init()
{
    ::init();
    add_action("do_enter","enter");
}

int
do_enter(string str)
{

    if (!str)
    {
        return 0;
    }
 
    if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
    {
        write("You enter the open burrow.\n");
        say(QCTNAME(TP)+ " leaves into the open burrow.\n");
        TP->move_living("M",GREENHOLM_DIR + "1",1);
        say(QCTNAME(TP)+" arrives.\n");
        return 1;
    }

    write("Enter what ? A "+str+" ? You must be kidding!\n");
    return 0;
}
