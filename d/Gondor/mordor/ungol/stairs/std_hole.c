/*
 * /d/Gondor/mordor/ungol/stairs/std_hole.c
 *
 * Olorin, 21 December 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/stairs/std_winding";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
#include "stairs.h"

#define RAVINE_MASTER   (STAIRS_DIR + "rav_master")

int searched_here = 0;

void create_hole() 
{ 
    set_short("In a narrow crevice in the Ephel Duath"); 
}

nomask void 
create_room()
{
    set_name("ravine");
    create_hole();

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_prop(OBJ_I_SEARCH_TIME,5);
    add_prop(ROOM_I_LIGHT,0);
}

int f_living(object x) { return living(x); }

void falling_rocks()
{
    object *obs = all_inventory(TO),
           *victims,
            armour;
    int     i,
            hit;

    obs = filter(obs,"f_living",TO);

    victims = ({});
    for(i = 0; i < sizeof(obs); i++)
    {
        if((hit = obs[i]->resolve_task(TASK_ROUTINE,({TS_DEX,SS_ACROBAT,SS_AWARENESS}))) < 0)
        {
            armour = obs[i]->query_armour(TS_HEAD);
            if(objectp(armour))
                hit += armour->query_ac() + armour->query_am()[2];
            if (hit < 0)
                obs[i]->heal_hp(hit);
            obs[i]->catch_msg("You are hit by a falling rock.\n");
            victims += ({obs[i]});
            if(obs[i]->query_hp() <= 0)
                obs[i]->do_die(TO);
        }
    }
    switch(sizeof(victims))
    {
        case 0: 
            tell_room(TO,"Some rocks fall down from above.\n");
            break;
        case 1:
            tell_room(TO,CAP(COMPOSITE_LIVE(victims)) + " is hit by a falling rock.\n",victims);
            break;
        default:
            tell_room(TO,CAP(COMPOSITE_LIVE(victims)) + " are hit by falling rocks.\n", victims);
            break;
    }
}

string do_search(object searcher, string str)
{
    object skeleton;

    if(str != "here" && str != "crevice" && str != "rocks" && str != "heap" 
        && str != "floor" && str != "ground" && str != "rubble" 
        && str != "heaps")
        return "";

    searched_here++;

    if(RAVINE_MASTER->query_hole() != MASTER)
    {
        if(!random(3))
        {
            write(BSN("While you search through the rubble covering the ground, "+
                "you hear the noise of falling stones from above."));
            LSAY("While "," searches through the rubble covering the ground, "+
                "you hear the noise of falling stones from above.");
            falling_rocks();
        }
        return BSN("You search through the rubble covering the ground, but you don't find anything except rocks.");
    }

    if(searched_here > 1)
        return BSN("You search through the rubble covering the ground, but you don't find anything except rocks.");

    skeleton = clone_object(MORGUL_DIR + "obj/elf_skeleton");
    skeleton->move(TO);
    say(QCTNAME(TP) + " finds a skeleton that was buried under a heap of rubble.\n");
    return "You find a skeleton that was buried under a heap of rubble.\n";
}

void reset_room()
{
    object  skeleton;
    if (objectp(skeleton = present("skeleton", TO)))
        skeleton->decay();
    searched_here = 0;
}
