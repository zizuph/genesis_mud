/*
 *	/d/Gondor/anorien/road/rroad8.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:      Changed inheritance.
 *  9-April-2004, Tigerlily:  Added exit for new rangers
 *  1-April-2005, Finwe:      Added messages to the exits so rangers watching 
 *                            the road know who is passing by.                    
 *  4-Oktober-2008, Eowul:    Allowed steeds to be present when trying to go
 *                            east.
 *                            
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

string see_ranger_exit();
int ranger_exit();

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("southeastern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("You are standing just outside the ruins of Osgiliath. The road "+
	  "runs south along the river and north into the city. It is joined by "+
	  "another road coming from the west, trees lining it on both sides. "+
	  "Disused streets run among the remains of tall stone buildings long "+
	  "corrupted by wind and weather.");
    
    add_item("trees", "Trees line the road, but many of them have been " +
        "damaged by the effects of war, with broken limbs and no leaves.\n");
    add_item(({"buildings", "building"}), "Among the collapsed and destroyed " +
        "buildings that used to be Osgiliath, you see a partially intact " +
        "house to the east.\n");
    add_item("house", "A house stands partially intact to the east, although " +
        "only two walls remain standing, and these are blackened from fire.\n");
#ifdef NEW_RANGERS_OPEN 
    add_item(({"streets", "street", "disused streets"}), &see_ranger_exit());
    add_exit(RANGERS_ITH_TUNNEL + "ruins_street", "east", &ranger_exit(),
        0, 1);
#endif
/* original exits
    add_exit(OSG_DIR + "wosg1",       "north", 0, 0);
    add_exit(ANO_DIR + "road/rroad7", "south", 0, 0);
    add_exit(ANO_DIR + "road/or5",    "west",  0, 0);
*/

    add_exit(OSG_DIR + "wosg1",       "north", "@@north_msg@@");
    add_exit(ANO_DIR + "road/rroad7", "south", "@@south_msg@@");
    add_exit(ANO_DIR + "road/or5",    "west",  "@@west_msg@@");

}

string
query_dir_to_gate()
{
    return "west";
}

string
see_ranger_exit()
{
    object tp = this_player();

    if (!RANGERS_FULL_MEMBER(tp))
    {
        return "The streets are covered with blackened rubble " +
            "and have large potholes. Clearly this is a war " +
            "zone.\n";
    }
    //else
    return "The streets are blackened with scorched rocks " +
        "and contain large potholes. However, your trained eyes " +
        "notice that tracks lead to the east into a small unused " +
        "street.\n";
}

int
ranger_exit()
{
    object tp = this_player();
    int num_in_room;
    object *others = ({});
    int non_ranger_flag;
    int i;

    non_ranger_flag = 0;
    if (!RANGERS_FULL_MEMBER(tp) && !sizeof(FILTER_IS_WIZARD(({tp}))))
    {
        tp->catch_msg("There is no obvious exit east.\n");
        return 1;
    }
    // else check for others in room
    others = FILTER_IS_SEEN(tp, all_inventory(this_object()) - ({tp}) );
    num_in_room = sizeof(others);

    for (i = 0; i < num_in_room; i++ )
    {
        // set flag for non-rangers in room
        // who can see ranger
        if (!RANGERS_FULL_MEMBER(others[i]) && !others[i]->is_steed())
        {
            non_ranger_flag = 1;
        }
    }
    //account for this_player = 1 in room and non-rangers present;)
    if (non_ranger_flag)
    {
        tp->catch_msg("You cannot access the street " +
            "while you are being watched by non-rangers. " +
            "It must remain secret!\n");
        return 1;
    }
    //else
    return 0;
}

void north_msg()
{
     tell_room(RANGERS_ITH_TUNNEL + "ruins_street", "You notice " +
            QTNAME(TP) + " went north towards Osgiliath.\n");
}

void south_msg()
{
        tell_room(RANGERS_ITH_TUNNEL + "ruins_street", "You spy " +
            QTNAME(TP) + " heading south through Anorien.\n");
}

void west_msg()
{
     tell_room(RANGERS_ITH_TUNNEL + "ruins_street", "You watch " +
            QTNAME(TP) + " go west towards Minas Tirith.\n");
}


public void
enter_inv(object ob, object from)
{
    string dir;
    string * exits = query_exit();
    string name;

   ::enter_inv(ob, from);
    if (interactive(ob))
    {
        name =file_name(from);
        if (member_array(name, exits) != -1)
            dir = exits[member_array(name,exits) + 1];
        tell_room(RANGERS_ITH_TUNNEL + "ruins_street",
            "To the west you notice that " + QTNAME(ob) +
            " arrived from the " + dir + ".\n");
    }
}
