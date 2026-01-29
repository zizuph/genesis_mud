inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/herbsearch.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "local.h"
#include "/d/Shire/common/herbs/herb_list.h"

void add_stuff();
public void	drink_message(string from);

string herb_here; 


void create_shire_room()
{
    set_short("Under the Bridge of Stonebows");
    set_long("Here, under the Bridge of Stonebows it is very "+
      "dark and dim, for the stones which constitute the bridge "+
      "are sealed tightly together, and no light passes through. "+
      "The sound of the River Brandywine is loud here as it rushes "+
      "past the obstinate stone pillars that keep the bridge out of "+
      "the mud that one might easily sink down into and never come "+
      "out again. To the north a path leads along the western bank of "+
      "the river, and one also leads south.\n");

    add_item(({"stone","stones","seal","mortar"}),
      "The stones are of immense proportions, and the mortar sealing them "+
      "together seems very thick and strong.\n");
    add_item(({"bridge","stonebows","bridge of stonebows"}),
      "You stand beneath the bridge in the dim, dank space between the "+
      "river and the westernmost pillar of the bridge.\n");
    add_item(({"river","brandywine river","brandywine","baranduin","water"}),
      "The Brandywine River rushes past you amid the support pillars of "+
      "the bridge.  It is muddy and swirling.\n");
    add_item(({"pillar","pillars","stone pillars","stone pillar"}),
      "The stone pillars still stand as straight as they did when this bridge "+
      "was made, more than an age of the world ago.  They seem not to "+
      "budge in their task of holding the bridge up.\n");
    add_item(({"mud","muddy water"}),"The mud in the water must "+
      "come from mud on the river bottom.\n");

    add_exit(ER_BASE_DIR + "girdley/wbrpath1","south",0,2);
    add_exit(ER_BASE_DIR + "girdley/girpath1","north",0,2);
    add_prop(ROOM_I_INSIDE,1);

    reset_shire_room();


     set_up_herbs( ({   SHIRE_HERB_DIR + "huckleberry", SHIRE_HERB_DIR + "lianor_berry", 
                        SHIRE_HERB_DIR+"grass", GONDOR_HERB_DIR+"lothore", 
                        GONDOR_HERB_DIR+"redweed", GONDOR_HERB_DIR+"ungolestel",}),
                  ({"forest","ground","field","flowers","forest"}), 3);

    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
//    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
//    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}

public void
init()
{
    ::init();
    init_drink();
}


void
reset_shire_room()
{
    add_stuff();
    set_searched(-2);

}

void
add_stuff()
{
    object fisherman;

    if(!present("bodulas"))
    {
	fisherman = clone_object(ER_BASE_DIR + "npc/fisherman");
	fisherman->move(TO);
	fisherman->command("emote arrives.");
    }


}

/*
 * Function name:	drink_message
 * Description	:	do the msgs for drinking from river
 */
public void
drink_message(string from)
{
    write("You drink some of the yellow water of the Brandywine river.\n"
      + "It tastes dirty and muddy.\n");
    say(QCTNAME(TP) + " drinks some water from the river.");
} /* drink_message */
