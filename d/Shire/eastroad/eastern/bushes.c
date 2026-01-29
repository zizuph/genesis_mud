/*
 * Connection between Imladris and
 * Great East Road
 * Finwe, August 1998
 */
#pragma save_binary
#pragma strict_types
 
#include "local.h"
#include <composite.h>
#include <filter_funs.h>
 
inherit EAST_ROAD;

#define TROLLSHAW_DIR   "/d/Shire/common/trollsh/"
#define RIVER_DIR       "/d/Shire/rivendell/room/river/"
#define BUSHES          "/d/Shire/eastroad/eastern/"

 
void
create_er_room()
{
    set_area("at a crossroad on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("foothill");
    set_grass("wet, long");
    set_treetype("oak");
 
    set_extraline("The Great East Road ends here.  It " +
        "connects to a path that winds into the Misty " +
        "Mountains.");

  
    add_item(({"forest","oak forest","trees"}),
      "The shadow of Misty Mountains envelopes the Great East "+
      "Road here. Ancient oaks look ominous and gloomy as they " + 
      "rise up along the road.\n");
    add_item(({"mountains", "misty mountains", "foothills"}),
      "The tops of the Misty Mountains rise up before you. " +
      "They look forbidding and dangerous as they stand in " +
      "the distance.\n");
    add_item(({"path", "paths"}),
        "One path looks well used as it heads into the " +
        "mountains, skirting the river to the east. Another " +
        "less travelled path runs east to the river.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows east out of the mountains and south " +
        "alongside the road.\n");
    add_item(({"bushes", "shrubs"}),
        "The bushes are tall and grow along the road. They are very thick and thorny, and look dangerous.@@bushes_descr@@\n");
 
    add_exit(TROLLSHAW_DIR + "mpath6",    "north", 0, 1);
    add_exit(TROLLSHAW_DIR + "mpath4",    "south", 0, 1);
    add_exit(RIVER_DIR    + "riverbank", "east", 0, 2,1);

/*
    add_exit(RIVER_DIR    + "riverbank", "east", "@@no_way@@",2,1);
*/
}

public void
init()
{
    ::init();
    add_action("enter_bushes", "enter");

}


string
inside_bushes()
{
    object other_room;
    mixed opeople;
 
    if (!LOAD_ERR(BUSHES + "riv_bushes"))
        other_room = find_object(BUSHES + "riv_bushes");
    else
        return "Some sort of magic is plaguing the bushes. Contact " +
            "a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return " No one is visible in the bushes.";
    else
        return " You see "+COMPOSITE_LIVE(opeople)+" hidden in the bushes.";
}

int
no_way()
{
   if (this_player()->query_wiz_level())
        return 0;
    write("You can't go there. It seems the river has flooded " +
        "its banks, making it impossible to go there.\n");
    return 1;
}


string bushes_descr(string str)
{
        if (R_ALLOWED)
            return " Hidden within the bushes is path that leads into " +
            "them so you may go into them. " + inside_bushes() + "\n";
        else
            return "";
}


int enter_bushes(string str)
{

    if (R_ALLOWED)
    {    
        if(!str)
        {
            write("Enter what?\n");
            return 1;
        }

        if(str =="bushes" || str =="shrubs")
        {
            write("You disappear from the road and into the bushes.\n");
            TP->move_living("M",BUSHES + "riv_bushes", 1);
            tell_room("treetop.c", QCTNAME(TP) + 
            " went west into the bushes.\n");
            tell_room(ENV(TP), QCTNAME(TP) + " arrives from the road.\n",TP);
            return 1;
        }
        else 
        {
            write("Enter what?\n");
            return 1;
        }
    }    
}


string ranger_descr()
{
    if (R_ALLOWED)

        return "Bushes grow alongside the road, hiding a path into them.";
    else
        return "";

}


void tree_south()
{
    tell_room("/d/Shire/eastroad/eastern/secret_riv_bushes.c", QCTNAME(TP) +
    " headed south towards the Trollshaws.\n");
}

void tree_north()
{
    tell_room("/d/Shire/eastroad/eastern/secret_riv_bushes.c", QCTNAME(TP) + 
    " went north into the Misty Mountains.\n");
}
void tree_east()
{
    tell_room("/d/Shire/eastroad/eastern/secret_riv_bushes.c", QCTNAME(TP) + 
    " went east towards Imladris.\n");
}
