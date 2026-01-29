/*
 *  /d/Gondor/rohan/entwash/entwash.c
 *
 *  to be inherited by swampy rooms in the entwash area
 *
 *  Sept 1995 by Gorboth
 *  copied in part from sewer.c by Olorin
 *
 *  Special thanks to: Olorin, Elessar, Jeremiah
 * 
 *  Revision History:
 *      Changed inherit to /d/Gondor/std/room.c
 *      Changed add_item() to try_item()
 *        -Gorboth, August 27th 1997
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"
#include "/d/Gondor/common/lib/herb_list.h"

#define  ENTWASH_HERBS        ({ (HERB_DIR + "blung"),\
                                 (HERB_DIR + "tuo"),\
                                 (HERB_DIR + "sumac"),\
                                 (HERB_DIR + "tyelka"),\
                                 (HERB_DIR + "ungolestel"),\
                                 (HERB_DIR + "curugwath"),\
                                 (HERB_DIR + "redweed"),\
                                 (HERB_DIR + "coccinea"),\
                              })

// Prototypes
string  long_desc();
string  sh_desc();
string  exa_air();
string  exa_sky();

// Global variables
static string air;
static string extra_long = "";
static int    mist;
static object *bugs;

varargs void    set_mist(int i)  { mist = i; }

void
set_extra_long(string s)
{
    if(strlen(s))
        extra_long = " "+s;
}

string query_extra_long() { return extra_long; }

void
create_swamp()
{
}

void
mist_level()
{
    switch(tod())
    {
        case "night":
        case "midnight":
        case "early morning":
            set_mist(4);
            break;
        case "morning":
        case "evening":
            set_mist(3);
            break;
        case "noon":
        case "afternoon":
            set_mist(random(3));
            break;
    }
}

int
check_light()
{
    int    light;

    mist_level();

    switch(mist)
    {
        case 0..3:
            light = 1;
            break;
        default:
            light = 0;
            break;
    }

    return light;
}
nomask void
create_gondor()
{
    set_name("swamp");
    set_short(sh_desc);
    set_long(long_desc);

    add_prop(ROOM_S_DARK_LONG, "A dark, misty swamp.\n");
    add_prop(ROOM_S_DARK_MSG, "The dense mists seem to block out all"
             + " natural light here, making it impossible to");
    add_prop(ROOM_I_LIGHT, check_light);

    try_item(({"ground","bog","bogs","marsh","marshes","fen","fens"}),
              BSN( ONE_OF_LIST( ({
        "The ground here composed of uneven stretches of mud which"
      + " run between large pools of murky water.",
        "This area is a veritable bog. Large areas of dark water are"
      + " broken only somewhat by scattered patches of weeds and mud.",
        "Vapours rise slowly from the deep mud which composes the"
      + " greater part of these fens. Many puddles are visible leaking"
      + " dark and murky rivulets of water in and amongst the weeds.",
        "Water covers the ground almost completely here, and makes"
      + " movement slow and tiring. Patches of tall weeds are visible"
      + " rising from the surface in scattered clumps."
        }) ) ));
    try_item(({"mud","deep mud","soil"}), BSN(
        "The mud of these fens is thick and mostly black, though it"
      + " is apparent that not earth alone comprises its substance."
      + " Bits and pieces of fallen weeds are meshed in the murky soil."));
    try_item(({"pool","pools","water","puddle","puddles","rivulet",
               "rivulets"}), BSN(
        "The water which makes up much of the ground-cover in this"
      + " place is dark and filled with churning mud. Many rivulets"
      + " bleed liquid from one pool or puddle to the next."));
    try_item(({"weed","weeds","clump","clumps"}), BSN(
        "Tall marshy weeds are growing in clumps all around this"
      + " area. Some protrude from patches of mud, while some simply"
      + " rise from the still surface of the water."));
    try_item(({"sky","sun","sunlight","star","stars"}), exa_sky);
    try_item(({"mist","mists","fog","air","cloud","clouds"}),
            exa_air);
    try_item(({"stream","entwash","streams","mouth","mouths"}), BSN(
        "The river Entwash has fractured into many small streams here,"
      + " all of which are quietly flowing in an easterly direction to"
      + " connect with the mighty Anduin. Runoff and groundswell from"
      + " the flow has created a bog which extends in many directions."
        ));

    set_up_herbs( ({ ONE_OF_LIST(ENTWASH_HERBS),
                     ONE_OF_LIST(ENTWASH_HERBS),
                     ONE_OF_LIST(HERBS), }),
                         ({ "pool","pools","mud","ground",
                            "weed","weeds" }),
                   3 );

    create_swamp();
}

string
sh_desc()
{
    string  fog;

    mist_level();

    switch(mist)
    {
        case 0..1:
            fog = "somewhat misty";
            break;
        case 2:
            fog = "misty";
            break;
        case 3:
            fog = "very misty";
            break;
        case 4:
            fog = "mist choked";
            break;
    }

    return ("a "+fog+" fen within the mouths of the Entwash");
}

string
long_desc()
{
    string  desc;

    mist_level();

    switch(mist)
    {
       case 0..1:
            air = "The air here is dank and chill, moving slowly"
                + " about you as fine threads of mist.";
            break;
        case 2:
            air = "Vaporous clouds of mist wind through the area"
                + " as long tendrils of moisture. It is rather"
                + " cold.";
            break;
        case 3:
            air = "Mist hangs over this area as a dense curtain of"
                + " moisture. The air is thick, heavy, and quite"
                + " cold.";
            break;
        case 4:
            air = "The air here is ill-feeling, and frighteningly"
                + " cold. A dense and seemingly impenetrable"
                + " fog has invaded this place, making visibility"
                + " very difficult indeed.";
        break;
    }

    switch(tod())
    {
        case "noon":
            desc = "It is noon, and the mist has begun to lift.";
            break;
        case "midnight":
            desc = "It is midnight and all is silent.";
            break;
        case "afternoon":
            desc = "The afternoon sun has begun to burn off much of"
                 + " the fog in this area.";
            break;
        case "evening":
            desc = "Evening has descended on the area increasing the"
                 + " feeling of gloom over the fens.";
            break;
        case "night":
            desc = "Darkness runs thick now at night, and the fens are"
                 + " humming with many unknown sounds.";
            break;
        case "early morning":
            desc = "An early morning calm lies over the area, as the"
                 + " bog waits for the darkness to lift.";
            break;
        case "morning":
            desc = "Sunlight peers dimly through the middle morning"
                 + " moisture over the fens.";
            break;
    }

    return BSN("Among the mouths of the Entwash in northern Anorien."
        +" "+ desc + extra_long +" "+ air);
}

string
exa_sky()
{
    string desc,
           time = tod();

    switch(tod())
    {
        case "morning":
        case "afternoon":
        case "evening":
            desc = "Peering up through the "+time+" mist, you are"
                 + " able to see the sun above dimly shining through"
                 + " the thick atmosphere.";
            break;
        default:
            desc = "Not even the brightest stars are visible through"
                 + " the thick "+time+" mists of the Entwash.";
            break;
    }

    return BSN(desc);
}

void
add_vines()
{
    try_item(({"vine","vines"}), BSN( ONE_OF_LIST( ({
        "Oily vines hang from this tree in a thick, matted"
      + " web of vegetation.",
        "The vines are long and brownish-green. A few smaller"
      + " reddish vines can be seen interspersed in the tangled"
      + " foliage.",
        "These vines are thick and hang in wide drooping formations"
      + " from the limbs of the nearby tree.",
        "A thick film of some slimy substance coats these vines."
        }) ) ));

    if (!random(3))
    {
       set_up_herbs( ({HERB_DIR + "sumac"}), ({"vine","vines"}), 1);
    }
}

string
exa_air()
{
    return BSN(air);
}

void
make_bug()
{
    int    i,
           s = sizeof(bugs);

    for (i = 0; i < s; i++)
        if(!objectp(bugs[i]))
            break;

    if (i == s)
        return;

    bugs[i] = clone_object(NPC_DIR + "mosquito");

    bugs[i]->set_poison_file(ENTWASH_DIR + "obj/mosquito_sting");
    bugs[i]->set_restrain_path(ENTWASH_DIR);
    bugs[i]->set_random_move(10);
    bugs[i]->move_living("down", TO);

    set_alarm(10.0, 0.0, "make_bug");
}

void
make_deadtree()
{
    add_vines();

    if(!objectp(present("entwash_dead_tree")))
    {
        clone_object(ENTWASH_DIR + "obj/dead_tree")->move(TO);
    }
}
