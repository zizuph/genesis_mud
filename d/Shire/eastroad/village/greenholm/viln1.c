inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#include "../local.h"

#define EXIT1 ER_DIR + "er7n","south",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/inn","north",0,1
#define EXIT3 ER_BASE_DIR + "village/greenholm/viln2","northeast",0,1


int do_enter(string str);
void add_stuff();
void reset_room();

void
create_room()
{
    int i;
    string *herbs;
   

    areaname = "Greenholm";
    land = "the Shire";
    areatype = 2;
    areadesc = "path";
 
    extraline = "The geographic center of the village Greenholm is "+
        "not much for the eye to take in.  A few holes have "+
        "been dug out of the larger hills around, and an actual "+
        "building is to the north, with a large red sign hanging "+
         "from above the door.";

    add_item(({"actual building","building","pub","north building"}),
        "This relatively large building is made of stone and wood.  The "+
        "wood has been weathered to a grey-black, nearly matching "+
        "the dark stone.\n");

    add_item(({"sign","red sign","large red sign"}),
        "The sign depicts an apparent caricature of a gruff, ruddy-faced "+
        "hobbit.  There is writing above it.\n");

    add_item("writing",
        "It is quite legible.\n");
 
    add_cmd_item("sign","read",
        "The sign reads: The Bounder.\n");
    add_cmd_item("writing","read",
        "The sign reads: The Bounder.\n");

    add_item(({"village","greenholm"}),
        "This village, named Greenholm is quite small indeed. It consists " +
        "of only a few burrows and the Bounder, the local pub.\n");

    add_item(({"hobbit holes","holes","hobbit-holes","smials","burrows"}),
        "The burrows are cut into the western hillside, all except one "+
        "guarded by a big round door.  The nearest burrow's door is open, "+
        "you could probably enter the burrow.\n");

    add_item(({"rolling hills","dales","hills","scene"}),
        "The rolling hills to the south are covered with grass, and look "+
        "very comfortable for relaxing.  The pastoral scene of hill and dale "+
        "makes you sleepy, in fact.\n");

    add_item(({"door","big round door","round door"}),
        "All of the holes in this area seem to be closed off by large "+
        "round doors, designed in the hobbit fashion.  One reason they "+
        "might be so big is for the hobbits to get their bellies through "+
        "the door.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);

    herbs = ({HERBS[random(sizeof(HERBS))],
        HERBS[random(sizeof(HERBS))],
        HERBS[random(sizeof(HERBS))]});
   
    for(i = 0; i < sizeof(herbs); i++)
        add_herb_file(herbs[i]);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,8);
   
    set_search_places(({"bushes","bush","tree","trees","ground","grass"}));
   
    make_the_room();
    reset_room();
}

void
add_stuff()
{
    object worm, girl;

    if(!present("worm"))
    {
        worm = clone_object(ER_BASE_DIR + "npc/worm");
        worm->move(TO);
    }

    if(!present("brunhilda"))
    {
        girl = clone_object(ER_BASE_DIR + "npc/girl");
        girl->move(TO);
    }        
}

void
reset_room()
{
    set_searched(0);
    add_stuff();
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
        return 0;
 
    if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
    {
        write("You enter the open burrow.\n");
        say(QCTNAME(TP)+ " leaves into the open burrow.\n");
        TP->move_living("M",ER_BASE_DIR + "village/greenholm/1",1);
        say(QCTNAME(TP)+" arrives.\n");
        return 1;
    }

    write("Enter what ? A "+str+" ? You must be kidding!\n");
    return 0;
}
