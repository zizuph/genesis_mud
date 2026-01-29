/*
 * The terrace path along the river in Imladris
 * By Finwe, December 1997
 */

#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit VALLEY_BASE;
inherit "/d/Gondor/common/lib/drink_water.c";

#define MIN_AWARE 10

string do_search(object searcher, string str);

object reeds;
int reeds_found = 0;
void
create_valley_room()
{

    add_my_desc("The path twists and turns past some rocks " +
        "jutting up from the riverbank's edge. The river " +
        "rushes over the rocks, splashing into some pools " +
        "below. Some fruit trees shade the path while the ground " +
        "slopes towards the river.\n");

    add_item(({"road","ground","path","stony path", "down"}),
        "The path is made from flat stones that closely fit " +
        "together.\n");
    add_item(({"last homely house", "house"}),
        "The house is constructed of stone with ornately carved " +
        "dark beams. The beams form criss-cross and diamond " +
        "patterns across the face of the house. Gables extend from " +
        "the roof. The roof is covered with cedar shingles.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are weather worn but still " +
        "in good condition.\n");
    add_item("roof",
        "The roof is steeply pitched, allowing snow and " +
        "rain to roll off the house quickly and easily.\n");
    add_item("gables",
        "The extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item("garden",
        "The garden surrounds the house. Many fruit trees, " +
        "vegetables, and edible plants can be seen growing " +
        "there. A split-rail fence surrounds the garden.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes west over " +
        "polished rocks. The water is clear. Its gentle music " +
        "fills the air.\n");
    add_item(({"reeds", "rushes"}),
        "The reeds grow alongside the river. They are tall and " +
        "wave gently in the breeze.\n");
    set_fence("They are secured to posts that have " +
        "been sunk into the ground.\n");

    add_prop("_obj_s_search_fun","do_search");

    reset_shire_room();

    add_path_herbs();

    set_drink_from(({"river", "river bruinen", "bruinen"}));

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN,"do_search");

    add_exit(VALLEY_DIR + "t_path08",  "east");
    add_exit(VALLEY_DIR + "t_path06",  "west");
    reset_room();
}

void
reset_room()
{
    set_searched(0);
    reeds_found = 0;
}

void
init()
{
    ::init();
    init_drink();
}

string short_desc()
{
    return ("The terrace path along the Bruinen");
}

/*
string
do_search(object searcher, string str)
{
   int awareness;

   awareness = searcher->query_skill(SS_AWARENESS);

   if(awareness < MIN_AWARE + random (MIN_AWARE))
        return 0;

   if(!str || (str!= "reeds"))
        return 0;

   if(reeds = 0)
        return 0;

   seteuid(getuid(TO));
   reeds = clone_object(ROBJ_DIR + "rushes");
   reeds->move(searcher,1);
   say(QCTNAME(searcher)+ " finds something in the grasses.\n");
   return "You find some dried reeds alongside the river.\n";
}
*/

mixed
do_search(object searcher, string str)
{
    int awareness;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < 13)
    {
        return 0;
    }

    if(str=="reeds" || str == "river" || str == "grass")
    {
        if(reeds_found == 3)
        {
            return "You found nothing in the grasses.\n";
        }
        else
        {
            seteuid(getuid(TO));
            reeds = clone_object(ROBJ_DIR + "rushes");
            reeds->move(searcher,1);
            say(QCTNAME(searcher)+ " finds something in the grasses.\n");
            reeds_found++;
            return "You find some dried reeds alongside the river.\n";
        }

        return "You found nothing alongside the river.\n";
    }
    else
    {
        return ;
    }
}