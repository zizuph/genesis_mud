/*Created by Macker 7/11/94*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit VILLAGE_INROOM;

/*
object *warriors = ({ 0, 0, 0, 0 });
object *fishers = ({ 0, 0, 0, 0 });
object *people = ({ 0, 0, 0, 0, 0, 0, 0, 0 });
*/
object master;
object *warriors = ({ });
object *fishers = ({ });
object *people = ({ });

void
reset_village_room()
{
    int num_war = 4;
    int num_fish = 4;
    int num_people = 8;
    int i;
    
	if(!master)
	(master = clone_object(PLAINS_L + "m_warrior.c" + 
		""))->move(TO);
	if(!sizeof(warriors))
      {
	  num_war = random(num_war);
	  for(i=0;i<=num_war;i++)
	(warriors = warriors + ({clone_object(PLAINS_L +
	"warrior.c")}))->move(TO);
      }
	if(!sizeof(fishers))
      {
	  num_fish = random(num_fish);
	  for(i=0;i<=num_fish;i++)
(fishers = fishers + ({clone_object(PLAINS_L +
	"fisher.c")}))->move(TO);
      }
	if(!sizeof(people))
      {
	  num_people = random(num_people);
	  for(i=0;i<=num_people;i++)
	(people = people + ({clone_object(PLAINS_L + 
	"villager.c")}))->move(TO); 
      }
}

void
create_village_room()
{
    set_short("Gathering Place");
    set_long(
	     "You are inside a building in the ice folks' village. " +
	     "This is where the ice folk gather to talk, sharpen weapons, " +
	     "tend fishing equipment, and keep warm by the large fire " +
	     "which burns in the middle of the room.\n");
    
    add_item( ({"building", "room"}),
	     "This building has only this one room. The walls are made of " +
	     "packed, frozen snow. Why don't you look around?\n");
    add_item( ({"hide", "door", "entrance"}), "It is not actually a door. " +
	     "It is a heavy animal hide hanging from above the doorway. " +
	     "It is moved aside each time someone enters or leaves the " +
	     "building.\n");
    add_item("village", "You are in the village, you silly person. Just " +
	     "look around!\n");
    add_item( ({"people", "folk", "ice folk", "ice people"}),
	     "The ice folk you see are wrapped tightly in hides from " +
	     "various animals. Their faces look worn from the years spent " +
	     "in this harsh environment. Surprisingly they do not look " +
	     "unhappy. In fact, they seem to be content with their lives " +
	     "in this frozen wasteland. You are sure they have their share " +
	     "of problems though.\n" +
	     "They are all gathered around the fire, talking and " +
	     "doing other various things.\n");
    add_item( ({"fire", "bonfire"}), "It is a big bonfire in the middle " +
	     "of the room. Just when you are about to wonder why " +
	     "the building doesn't burn down, you remember that the " +
	     "building is made of ice. So why doesn't it melt? Hmm...why " +
	     "don't you look at the ceiling?\n");
    add_item("ceiling", "It too is made of ice, but there is a hole above " +
	     "the fire which you assume leads to the roof.\n");
    add_item("hole", "Yes, you are certain it leads to the roof. It " +
	     "must be used to allow the smoke from the fire to escape to " +
	     "the outside.\n");
    
    LIGHT;
    add_exit(VILLAGE +
	     "village_2.c", "south");
    
    add_exit(VILLAGE +
	     "village_4.c", "north");
    
    reset_room();
}

object * 
query_warriors()
{
    return warriors;
}

int 
remove_warrior(object who)
{
    warriors = warriors - ({who});
    return 1;
}


object *
query_villagers()
{
    return people;
}

int
remove_villager(object who)
{
    people = people - ({who});
    return 1;
}
  
object *
query_fishers()
{
    return fishers;
}

int
remove_fisher(object who)
{
    fishers = fishers - ({who});
    return 1;
}

void
remove_master()
{
	master = 0;
return;
}


int
query_all_hit_list(object who)
{
int i;
	for(i=0;i<sizeof(warriors);i++)
	{
		if((warriors[i])->query_hit_list(who))
		return 1;
	}
return 0;
}

