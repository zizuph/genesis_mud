/*
 * FBASEROAD.c
 * This is the base road for the forest and common items, including
 * search functions for herbs, and a 'pick/pluck' herb command. Max
 * 2 herbs per room per reboot. Once the herb is gone - no one can pick.
 *     - Alaron August 31, 1996
 * Modified March 2, 1997 - Added random knife location
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define KNIFE_SERVER "/d/Emerald/kroad/knife_server"
#define MAX_HERBS 2
#define MAX_HERB_TYPE 10
#define KRYNN_HERB_DIR "/d/Krynn/common/herbs"
#define HERBS ({"/d/Emerald/common/herbs/loyol",\
		KRYNN_HERB_DIR+"/bunchberry.c",\
		KRYNN_HERB_DIR+"/poison_ivy.c",\
		KRYNN_HERB_DIR+"/crocus.c",\
                KRYNN_HERB_DIR+"/grey_willow.c",\
                KRYNN_HERB_DIR+"/tiger_lily.c",\
                KRYNN_HERB_DIR+"/lady_slipper.c",\
		KRYNN_HERB_DIR+"/wild_cuke.c",\
		KRYNN_HERB_DIR+"/wild_plum.c",\
		KRYNN_HERB_DIR+"/cranberry.c"})

inherit "/std/room";

void create_road();
void relocate_knife();
void set_allow_knife(int a);

int reset_count;
int current_herbs;

object knife_server;

void
set_allow_knife(int a)
{
    knife_server->set_allow_knife(a);
}

void
create_room()
{
    if (!LOAD_ERR(KNIFE_SERVER))
	knife_server = find_object(KNIFE_SERVER);

    current_herbs = MAX_HERBS;

    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 4);

    // Add a few items which are common to all rooms on the road.

    add_item( ({"forest", "trees", "forest edge"}),
	     "The road is bordered by an enormous, "+
	     "sprawling forest. The treeline runs seemingly forever "+
	     "as far as the eye can see.\n");

    add_item( ({"road", "down", "dirt", "path", "ground"}),
	     "The road is made of hard, packed dirt. The dirt is dark and "+
	     "moist from its proximity to the ocean and salt-water breeze. "+
	     "It looks well-travelled.\n");

    add_item( ({"up", "sky"}),
	     "The sky is an incredible shade of blue. There are several "+
	     "clouds drifting across over the ocean. If you look at the "+
	     "clouds long enough they begin to resemble common shapes.\n");

    create_road();

}

void
relocate_knife()
{
    knife_server->relocate_knife();
}

string
herb_search(object ob, string str)
{
    if ( (member_array(str, ({"bushes", "herb", "herbs", "flowers"})))!=-1)
	return TO->herb_search2(ob);
    else if ( (member_array(str, ({"dirt", "sand", "ground", "road"})))!=-1)
	return TO->knife_search(ob);
    else
	return "";
}

string
knife_search(object ob)
{
    int locnum;
    int slocnum;
    int result;
    object knife;
    string shortd;

    result = sscanf(file_name(TO), "/d/Emerald/kroad/road%d", locnum);
    slocnum = knife_server->query_knife_location();
    if (locnum != slocnum)
	return "Your search reveals nothing special.\n";
    if (!knife_server->query_allow_knife())
	return "Your search reveals nothing special.\n";
    
    reset_euid();
    
    knife = clone_object("/d/Emerald/kroad/wep/aknife");
    shortd = knife->short();
    knife->move(ob,1);
    set_allow_knife(0);  // disable finding the knife until jonah has it.
    return "You sift through the moist dirt of the road, and notice "+
	"a glinting metallic object ... Scuffing away more dirt, your "+
        "search reveals an "+shortd+"!\n";
}  

string
herb_search2(object ob)
{
    if (!current_herbs)
    {
	return "You find several places where there may have been some "+
	    "herbs among the foliage, but it looks like its been "+
	    "picked clean.\n";
    }
    else
    {
       	current_herbs--;
	
	reset_euid();
	clone_object(HERBS[random(MAX_HERB_TYPE)])->move(TP);

	return "You manage to locate an herb among the bushes and "+
	    "pull it free of its roots.\n";
    }
}

create_road() { }

void
reset_room()
{
    reset_count++;

    if (reset_count > 4)
    {
        reset_count = 0;
        current_herbs = MAX_HERBS;
     }
}
