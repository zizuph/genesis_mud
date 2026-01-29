/*
 * /d/Gondor/ithilien/forest/camp.c
 *
 * coded by Gnadnar
 *
 * inherited by camp rooms that check for _stopping_npc's 
 *
 * this room:
 *	overlays clone_npc() to add name "_stopping_npc".
 *	provides check_allow() to determine if any stopping npcs
 *	  see this player().
 *	if inheriting room calls set_tent_path() with the name
 *	  of the corresponding tent, takes care of "enter tent".
 * 
 * Added routines so players can examine various items mention 
 * in the room descriptions.
 * -- Finwe, August 2005
 *
 * Fixed typo in set_animal_pens
 * -- Toby, 2005-11-20
 *
 * Fixed formmating
 * -- Finwe, March 2019
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/friend_or_foe";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

//#define max_trolls = random(4);

//int num_harad = random(5), alarm_id;
object leader, *har_s = ({});

public void	set_tent_path(string path);
public void	set_move_msg(string move_msg);
public void	create_camp();
public int	check_allow();
public string	enter_tent();

static string	Tent_path;
static string	Move_msg = "";
static string	And_move_msg = "";

public void
create_camp()
{
}

nomask void
create_gondor()
{
    create_camp();

    if ( strlen(Tent_path) )
	add_cmd_item( ({ "tent", "tents", "large tent", }),
	    "enter", enter_tent);
}

public void	set_tent_path(string path)	{ Tent_path = path; }

public void
set_move_msg(string move_msg)
{
    And_move_msg = " and "+move_msg;
    Move_msg = "You "+move_msg+".\n";
}

public varargs object
clone_npc(object npc, string file, mixed restrain_path, function setup)
{
    if ( objectp(npc) )
	return npc;

    npc = ::clone_npc(npc, file, restrain_path, setup);
    npc->add_name("_stopping_npc");
    return npc;
}

public string
enter_tent()
{
    if (!check_allow())
    {
        ENV(TP)->set_dircmd("tent");
        write("You step into the largest of the tents.\n");
        TP->move_living("into the tent", Tent_path);
    }
    return "";
}


/* there used to be slightly different versions of check_allow() in
 * each file.  they checked:
 *      edge1           CAN_SEE
 *      haradcamp1      CAN_SEE
 *      haradcamp2      CAN_SEE
 *      haradcamp3      CAN_SEE && player's SS_SNEAK > npc's SS_AWARENESS &&
 *                              !fighting
 *      orccamp1        CAN_SEE && player's SS_SNEAK >= npc's SS_AWARENESS
 *      orccamp2        CAN_SEE && player's SS_SNEAK >= npc's SS_AWARENESS
 *      orccamp3        CAN_SEE && player's SS_SNEAK >= npc's SS_AWARENESS
 *      orcpost         CAN_SEE
 *      orcpost2        CAN_SEE && player's SS_SNEAK/2 >= npc's SS_AWARENESS
 *
 * the new check_allow() checks CAN_SEE, player's SS_SNEAK >= npc's
 * SS_AWARENESS and !fighting in all cases. also, the old code usually
 * only checked the first stopping npc; the new code checks all stopping
 * npcs in the room, in case abilities differ.
 *
 * TBD: it seems to me that if you're going to check SS_SNEAK, you also
 * should check whether the player is in fact sneaking.
 */
public int
check_allow()
{
    object	*stoppers, *can_see;
    int		aware, max, i, s;

    if (query_friend_or_foe(TP) == -1)
        return 0;

    stoppers = filter(all_inventory(TO), &->id("_stopping_npc"));

    if ( !(sizeof(stoppers)) )
    {
	    write(Move_msg);
	    return 0;
    }

    can_see = FILTER_CAN_SEE(stoppers, TP);
    
    if ( !(s = sizeof(can_see)) )
    {
        write("You sneak past the " + stoppers[0]->query_race_name() + 
	    And_move_msg + "!\n");
	    return 0;
    }

    if ( !TP->query_attack() )
    {
	    i = max = 0;
	    while ( s-- > 0 )
	    {
	        if ( (aware = can_see[s]->query_skill(SS_AWARENESS)) > max )
	        {
		        i = s;
		        max = aware;
	        }   
	    }

	    if ( TP->query_skill(SS_SNEAK) >= max )
	    {
            write("You sneak past the " + can_see[i]->query_race_name() + 
		        And_move_msg + "!\n");
	        return 0;
	    }
    }

    write("The " + can_see[i]->query_nonmet_name() +
	" stops you from going that way.\n");
    return 1;
}

int 
make_haradrim(int num_harad)
{
    int i;  
    object *har_s = allocate(num_harad);


    if(num_harad<1)
        return 0;

//    har_s = allocate(num_harad);

    if(!leader)
    {
        leader = clone_object(NPC_DIR + "har_c");
        leader->move(TO);
        tell_room(TO,CAP(LANG_ADDART(leader->query_nonmet_name())) +
           " charges in and prepares for battle.\n");
    }


    for(i = 0; i < num_harad; i++)
        if(!present("_harad_soldier_"))
        {
      	    har_s[i] = clone_object(NPC_DIR + "har_s");
            har_s[i]->move(TO);
            leader->team_join(har_s[i]);
          	tell_room(TO,CAP(LANG_ADDART(har_s[i]->query_nonmet_name()))+
          	    " charges in, preparing for battle.\n");
        }

//        else
//        if(har_s[i]->query_leader() !=leader)
//        leader->team_join(har_s[i]);

    return 1;
}

/*
 * Room descriptions 
 */

/*
 * Function name : set_add_dung
 * Description   : adds descr of dung and flies
 */
void set_add_dung()
{
    add_item(({"dung", "crap", "manure"}),
        "They are large piles of excrement from the animals that come " +
        "this way. The fresh ones smell horribly and are surrounded by " +
        "hordes of flies. Some are dried and grey looking and are knocked " +
        "to the side of the path.\n");
    add_item(({"flies"}),
        "They are large, two-winged black creatures that buzz around " +
        "piles of fresh dung and through the camp. They are annoying and " +
        "seem to congregate around the manure and animals. \n");
}

/*
 * Function name : set_add_forest
 * Description   : adds descr of the forest
 */
void set_add_forest()
{
    add_item(({"forest"}),
        "It is made up of ash trees and giant oaks. The forest has been " +
        "cleared away leaving a belt of green that surrounds the camp.\n");
    add_item(({"ash", "ash trees"}),
        "They are tall trees with multiple branches and small leaves. " +
        "They look tough and ancient.\n");
    add_item(({"oak trees", "oak"}),
        "These are tall, ancient looking trees. Their multiple branches " +
        "are covered with many green leaves.\n");
    add_item(({"trees"}),
        "They are tall and ancient and surround the camp. Those closest " +
        "to the camp have broken and splintered branches and don't have " +
        "any leaves on them.\n");
    add_item(({"branches"}),
        "They are thick and grow out from the trees. Some are twisted " +
        "and broken from the animals and Haradrim that pass by.\n");
    add_item(({"broken branches", "splintered branches", "twisted branches"}),
        "The look like they were ripped off the trees by animals. They " +
        "are broken and high up in the trees.\n");
}

/*
 * Function name : set_add_river
 * Description   : adds descr of river that flowes thru the camp
 */
void set_add_river()
{
    add_item(({"river"}),
        "The river looks dirty and flows east and west through the camp. " +
        "The water is a dark brown and doesn't look good enough to drink " +
        "from.\n");
}


/*
 * Function name : set_tall_tents
 * Description   : adds descr of tents for in south camp
 */
void set_tall_tents()
{
    add_item( ({ "tent", "tents" }),	
	    "The tents appear to be well-maintained and made of canvas. They " +
        "are square shaped and taller than those north of here.\n");
    add_item(({"canvas"}),
        "It is a gray material used to make the tents. It is tightly woven " +
        "and looks sturdy. The material appears to be in good condition.\n");    
}

/*
 * Function name : set_oli_pens
 * Description   : adds descr of 
 */
void set_oli_pens()
{
    add_item(({"pens", "large pens"}),
        "These are large areas sectioned of by tall fences. They are " +
        "where oliphaunts are kept. The pens are muddy and dirty looking.\n");
    add_item(({"fences"}),
        "The fences are as tall as a man and surround the pens. They are " +
        "made of wooden rails connected together horizontally and attached " +
        "to fence posts sunk into the ground.\n");
    add_item(({"fence posts", "posts"}),
        "They are spaced evenly around the perimeter of the pens. The " +
        "posts are from hewn trees and sunk into the ground. Wooden" +
        " rails are connected to the fence posts\n");
    add_item(({"rails", "wooden rails"}),
        "These are long trees that are connected together and attached " +
        "to the fence posts.\n");

}

/*
 * Function name : set_animal_pens
 * Description   : adds descr of animal pens
 */
void set_animal_pens()
{
    add_item(({"pens", "animal pens", "small pens"}),
        "These are areas sectioned of by fences. A variety of animals " +
        "are kept in them, some for eating, and others for riding.\n");
    add_item(({"fences"}),
        "The fences are made of rails and fence posts and surround the " +
        "pens. They are crude looking but effective in keeping the animals in.\n");
    add_item(({"fence posts", "posts"}),
        "They are spaced evenly around the perimeter of the pens. The " +
        "posts are from hewn trees and sunk into the ground. Wooden " +
        "rails are connected to the fence posts\n");
    add_item(({"rails", "wooden rails"}),
        "These are long trees that are connected together and attached " +
        "to the fence posts.\n");
}


