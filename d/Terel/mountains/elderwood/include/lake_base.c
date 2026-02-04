/* File:          /d/Terel/mountains/elderwood/include/lake_base.c
 * Creator:       Tomas
 * Date:          July 2000
 * Modifications: 
 * Purpose:       This is the base file for Mirror Lake within the Elderwood Forest.
 *                This file should be inherited into the lake files within the 
 *                ~Terel/mountains/elderwood/lake directory.
 *
 * Related Files: 
 * Comments:      The lake is very cold. Mortals not wearing cold resistance
 *                or having less than 30 in swim have an excellent chance of 
 *                Drowning.
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"
#define LAKE_DIR MOUNTAIN_DIR + "elderwood/lake/"

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";
  // inherit "/d/Terel/mountains/elderwood/include/cold_fatigue.c";

public void do_drown(object ob);

int long, short, exits;

int set_long_desc(int i)
{
    long = i;
}

int set_short_desc(int i)
{
    short = i;
}


init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    start_room_tells();
}


public void
create_room()
{
    ::create_room();
    set_short("@@short_desc@@");
    set_long("@@long_desc@@" + "The dense forest completely " +
       "surrounds the lake. The treeline extends all the way " +
       "to the frozen banks of the lake. Several trees have " +
       "overgrown the edge of the bank and now droop into the cold " +
       "water. Some of the trees have fallen into the water, adding " +
       "a jagged look to the otherwise smooth banks of the lake.\n");

    add_prop("_room_m_da_dragonsteed_no_land","You cant " +
       "land on a lake!.\n");

   add_item(({"mountain","mountain range","pass"}),
       "The vast jagged mountain range extends all along the " +
       "northern horizon. You notice what looks like " +  
       "a mountain pass towards the middle of the field.\n");

    add_item(({"field","snow covered field"}),
       "The field is covered in snow with the exception of some " +
       "rocky exposed areas. Clumps of tall frozen grass " +
       "grow about rocks and shallow areas of the snow drifts.\n");

    add_item(({"snow covered road","snowy road","road","dirt road"}),
       "The snow covered road leads north and southward "+
       "through a densely populated forest, which grows " +
       "on either side of the road.\n");

    add_item(({"forest","trees","undergrowth", "bushes",
               "shrubs","plants","evergreens","floor",
               "ground","shrub","plant","evergreen",
               "bush"}),
       "The evergreens loom high overhead creating a " +
       "semi-shaped canopy over the road. Dense undergrowth " +
       "covers the forest floor on either sides of the road.\n");

    add_item(({"branches","tree branches"}),"The tree branches " +
       "extend from either side entertwining over the road.\n");

    add_item(({"snow"}),"The snow covers everything, piling up along " +
       "the road and at the tree basin.\n");
    
    set_tell_time(300 + random(200));
    add_tell("A ripple forms just above the surface of the water.\n");
    add_tell("You feel something brush you feet beneath you.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_LIGHT, 1);
  
    reset_room();
    seteuid(getuid());
}


public void
enter_inv(object ob,object old)
{
    ::enter_inv(ob,old);

    if (interactive(ob) && ob->query_prop("_is_in_lake"))
    {
        if (ob->query_skill(SS_SWIM) <= 20 && 
           (!(ob->query_prop(MAGIC_I_RES_COLD))))
        {
            ob->catch_msg("Your body freezes within the cold icy water. " +
            "You are unable to stay afloat and slip beneath the water.\n " +
            "You drown in the deep waters of the cold forest lake.\n");
            tell_room(environment(),QCTNAME(ob) + " struggles for a short "+
              "amount of time, but then slips below the surface of the lake.\n,ob");
            ob = this_player();
            set_alarm(0.0,0.0,&do_drown(ob));
            return;
        }

    }
}

public void
do_drown(object ob)
{
    ob->set_hp(0);
    ob->do_die();
}


public string
smell_desc()
{
        switch(random(3))
        {
                case 0:
                     return "The air smells of dry grass and trees.\n";
                     break;
 
                case 1:
                     return "The air smells like stale fishwater.\n";
                     break;

               default:
                     return "The cold air smells of pine trees.\n";
                     break;
        }
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


string short_desc()
{
    switch(short)
        {
                case "middle":
                        return "Swimming within the cold mountain lake";
                        break;

                case "east":
                        return "Standing on the eastern bank of the mountain lake";
                        break;

                case "south":
                        return "Standing on the southern bank of the mountain lake";
                        break;

                case "north":
                        return "Standing on the northern bank of the mountain lake";
                        break;

                case "west":
                        return "Standing on the western bank of the mountain lake";
                        break;

                default:
                        return "Before you, is a very cold looking lake";
                        break;
        }
}


string long_desc()
{
    switch(long)
        {
                case "w_bank":
                     return "You stand on the western bank of a cold mountain lake. ";
                     break;

                case "s_bank":
                    return "You stand on the southern bank of a cold mountain lake. ";
                    break;
 
                case "e_bank":
                    return "You stand on the eastern bank of a cold mountain lake. ";
                    break;

                case "n_bank":
                    return "You stand on the northern bank of a cold mountain lake. ";
                    break;

                case "middle":
                    return "You are attempting to stay afloat in the extremely " +
                           "cold water of the lake. ";
                    break;

                default:
                    return "You stand before a cold looking still lake. ";
                    break;
        }
}


