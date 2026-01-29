/* Base bridge to be used in the wildlife
 * garden at Telberin, Emerald. Coded by Marisol
 * Copyright (c) 1999 (04/21/99) Marisol Ramos */


#include "../defs.h"

inherit TELBERIN_ROOM;
inherit "/d/Emerald/lib/room_tell";

#include "/d/Emerald/sys/properties.h" 

void
create_wild_bridge()
{
}

nomask void
create_telberin_room()
{             

    set_short("wooden bridge");
    set_em_long("An artful wooden bridge is set over the small creek "+
        "that divide the garden is sections. The water flows, jumps "+
        "and rushes under the bridge, to finally fill a small pond at "+
        "the center of the garden. Fine drops of water fills the air "+
        "now and then. Around the border of the pond, you can see a "+
        "cluster of weeds with butterflies hovering over their orange "+
        "flowers. You can see the lawn continue in both sides of the "+
        "bridge, while the water run it courses under weeds and "+
        "hedge.\n");

    add_item(({"hedge", "hedge of rhododendron", "rhododendron"}),
        "This is a tall rhododendron hedge that blocks your view "+
        "outside the garden. Emerald leaves and bright pink flowers "+
        "comprise the tall hedge that surrounds the garden.\n");  

    add_item("creeks",
        "Two artificial creeks crisscross the garden. They divide the "+
        "garden in four section with its flowers. The water flows from "+
        "the south of the garden to the pond at the center. It flows "+
        "out of the pond to the north under the rhododendron. Aesthetic "+
        "boulders are placed in both sides of these little creeks and "+
        "inside on it, making the display truthful to nature. A green "+
        "weed with orange blossoms crawls around the pond, with "+
        "butterflies flapping delicately from flower to flower. The "+
        "sound of the water is soothing, making this place one of "+
        "beauty and peace.\n");                                                         

    add_item("pond",
        "A small pond is feed by two artificial creeks. The water is "+
        "clean and clear. The rocky bottom of the pond can be seen "+
        "from the bridge. Playful fishes swim without fear inside "+
        "the peaceful water. The pond can't be reach by walking feet, "+
        "though. A healthy weed with very bright orange flowers "+
        "surround the pond, cutting it off from pedestrians.\n");



    add_item(({"healthy weed", "weed","weeds", "orange flowers"}),
        "These weeds are Butterfly Weed, a very charming wildflower "+
        "with its merry orange blossoms, that butterflies love to "+
        "visit, together with industrious bees.\n");

    
    add_item("lawn",
        "It is a soft green, sweet-smelling grass.\n");

    add_item("garden",
        "This garden is a miracle of design and beauty. Wildflowers, "+
        "domestic flowers and several bushes are arranged artfully to "+
        "promote the presence of butterflies, hummingbirds, bees and "+
        "other fauna. The place brings a sense of peace and beauty that "+
        "inspires the soul. The garden follow the geometrical pattern "+
        "of a sextagon, with two elf-made creeks bubbling around the "+
        "premise. The green lawn is the perfect place for a relaxing "+
        "picnic. A hedge of rhododendron enclosed the garden, creating "+
        "a secret place away from the rest of the city.\n");  

    add_item(({"butterflies", "hummingbirds", "bees"}),
        "There are many beautiful butterflies flying in and out of "+
        "flowers, together with hummingbirds and bees, all feeding from "+
        "the sweet nectars of delicate blossoms.\n"); 

    set_tell_time(100);
    add_tell(({
        "The water is bubbling merrily under and away the bridge.\n",
        "You hear the happy chirping of a robin.\n",
        "A lark sings his heart out in a nearby branch.\n",
        "An emerald hummingbird flies swiftly from flower to flower.\n",
        "A bright yellow butterfly flaps her wings slowly on a bright "+
        "orange blossom before flying away.\n",
        "You hear the busy buzzing of bees and flies somewhere in "+
        "the garden.\n",
        "You feel the cool spray of water droplets over your face.\n",
        "A bright green and black butterfly hovers over your head "+
        "before flying away.\n",
        }));

    create_wild_bridge();
}                                  

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}


void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
        write("The air here in the bridge is fresh and sweet with "+
        "the scent of water and wild blossoms.\n");
        return;
    }

}                                      
