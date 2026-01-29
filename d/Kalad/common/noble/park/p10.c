inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define NOBLE_QUEST_RING "_noble_quest_ring"

/* SARR */
/* updated drink function Damaris - 08/2002 */
int ring_here;
int ring_fish;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("Inside the Park of Kabal");
    set_long("You stand inside a beautiful park. A great hedge wall "+
      "surrounds you, providing you with comfort and privacy. The "+
      "path you walk on is made of clean, white stones. There are "+
      "many flowers, trees and bushes all around you, as well as "+
      "various animal life. There are little shaded groves to "+
      "your west, north, south and east, while southeast "+
      "leads back to the path.\n");
    add_item("fountain","It looks beautiful, perhaps you should "+
      "examine it more closer?\n");
    add_item(({"hedge","wall"}),"It is made of trees and bushes "+
      "and it towers over you, protecting you from outside.\n");
    add_item(({"animals","animal life","life"}),"You see "+
      "various birds, squirrels and rabbits abound.\n");
    add_item("fishes","@@fishes@@");
    add_item("birds","They sing sweet songs.\n");
    add_item("squirrels","They chatter loudly, jumping from tree "+
      "to tree.\n");
    add_item("rabbits","They hop along the grass, eating at the "+
      "leaves.\n");
    add_item("path","A very nice clean road that reflects the "+
      "bright Kaladian sun.\n");
    add_item("flowers","Flowers of all kinds and colors dot the "+
      "area.\n");
    add_item("trees","Big oak, cedars and pines dot the land, and "+
      "provide shade for you.\n");
    add_item(({"fish","blue fish","big fish","big blue fish"}),"@@fish@@");
    add_cmd_item(({"fish","blue fish","big fish","big blue fish"}),
      "get","@@get_fish@@");
    add_item("ring","@@ring@@");
    add_item("bushes","Little and big bushes alike with red berries.\n");
    add_cmd_item("ring","get","@@do_get@@");
    add_item("stones","They are large flagstones.\n");
    add_item("berries","Never-wake-up berries.\n");
    clone_object(NOBLE(obj/fountain))->move(TO);
    add_exit(NOBLE(park/p8),"east",0,0,-1);
    add_exit(NOBLE(park/p9),"north",0,0,-1);
    add_exit(NOBLE(park/p12),"south",0,0,-1);
    add_exit(NOBLE(park/p11),"west",0,0,-1);
    add_exit(NOBLE(park/p7),"southeast",0,0,-1);
    add_prop(ROOM_NO_TIME_DESC,1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    reset_room();
}

void
reset_room()
{
    ring_here = 1;
}

void
init()
{
    ::init();
    AA(do_sprinkle,sprinkle);
}

int
do_sprinkle(string str)
{
    int got_seeds,i;
    object *obs;
    object seeds;
    NF("Sprinkle what in where?\n");
    if(str != "seeds in fountain")
	return 0;
    obs = deep_inventory(TP);
    for(i=0;i<sizeof(obs);i++)
    {
	if(obs[i]->query_name() == "yathesearethem")
	{
	    got_seeds = 1;
	    seeds = obs[i];
	}
    }
    NF("You don't have any seeds.\n");
    if(got_seeds == 0)
	return 0;
    if(!TP->query_prop(NOBLE_QUEST_RING) || ring_fish == 0)
    {
	write("You sprinkle the seeds on the water, and a few fish go up "+
	  "and nibble on them.\n");
	say(QCTNAME(TP)+" sprinkles some seeds on the water.\n");
	seeds->remove_object();
	return 1;
    }
    else
    {
	say(QCTNAME(TP)+" sprinkles some seeds on the water, and a "+
	  "big blue fish comes up to eat them...then "+HE(TP)+" nabs "+
	  "the fish and reaches it its mouth and pulls out a ring!\n"+
	  "Then "+HE(TP)+" tosses the fish back in the water.\n");
	write("You sprinkle some seeds on the water, and the "+
	  "big blue fish comes out to eat them...then you nab it! "+
	  "You reach in its mouth, yank out the ring and toss the "+
	  "fish back in.\n");
	clone_object(NOBLE(obj/quest_ring))->move(TP);
	TP->add_prop(NOBLE_QUEST_RING,0);
	seeds->remove_object();
	ring_fish = 0;
	return 1;
    }

}


string
fishes()
{
    if(ring_here)
	return "You see many little colorful fishes swimming about..."+
	"and as you look closer, you see something shiny at the "+
	"bottom that looks like ring!\n";
    else
	return "You see many little colorful fishes swimming about.\n";
}

string
fish()
{
    if(ring_fish == 0)
	return "A lazy looking fish.\n";
    else
	return "The fish smiles up at you.\n";
}

string
ring()
{
    if(ring_here)
	return "It is at the bottom of the fountain, sparkling.\n";
    else
	return "You find no ring.\n";
}

string
do_get(string str)
{
    if(ring_here == 1)
    {
	TP->add_prop(NOBLE_QUEST_RING,1);
	say(QCTNAME(TP)+" fishes around at the bottom of the fountain.\n");
	ring_here = 0;
	ring_fish = 1;
	return "You reach down to grab the ring...but just then a big "+
	"blue fish swims by an swallows the ring!\n";
    }
    else
	return "Get what?\n";
}

string
get_fish()
{
    if(ring_fish == 0)
	return "Now why would you want to do that?\n";
    else
	return "You try to grab the fish, but it is too quick and "+
	"eludes you!\n";
}

