/*
 * Room of the Old Road in Mirkwood.
 *
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";

/*
 * Function name: create_mirkwood_road_room
 * Description  : Create this room of the old road
 */
void create_mirkwood_road_room()
{
    // Force the randomized messages to always be the same for roads
    set_room_seed(22);
    set_mirkwood_location(LOCATION_MIDDLE);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the middle of Mirkwood Forest");

    add_long("Amidst the long shadows which stretch out to cover the " +
    	"undergrowth on both sides of the road, you spot a tall " +
    	"pillar of rock to the south. ", LIGHT_BRIGHT);

    add_item_light(({"rock", "pillar", "pillar of rock", "rock pillar"}),
        "A tall rock pillar rises up amongst the trees on the south " +
        "side of the road. As you take a closer look, various " +
        "scratches on the surface actually appear to be a variety " +
        "of carved images.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"scratches"}),
        "These are not sratches, they are carvings.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"images", "image", "carving", "carvings"}),
        "These carvings seem to be mostly animalistic, depicting " +
        "a variety of scenes containing primarily images which appear " +
        "to be combinations of bears and spiders. You could almost swear " +
        "that the bears are actually fighting the spiders in " +
        "some of the carvings.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"bear", "bears", "bear carving", "bear carvings"}),
        "There are dozens of different bear carvings scattered all over " +
        "the surface of this massive stone pillar. Most of the bears are " +
        "depicted in a very aggressive manner, often battling against " +
        "the spider images.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"spider", "spiders", "spider carving", "spider carvings"}),
        "There are many images of spiders carved into the massive stone " +
        "pillar. All of the spiders seem to be battling the various bear " +
        "images which have also been etched into the stone. Strangely " +
        "enough, some of the spider carvings are covered with what " +
        "seem to be reddish-brown handprints.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"handprint", "handprints"}),
        "It looks like an old, bloody handprint. Almost as if someone " +
        "was trying desperately to press down onto some of the " +
        "spider images.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"shadow", "shadows", "long shadow", "long shadows"}),
        "There are many shadows everywhere you look, but this particular " +
        "shadow has been created from a tall stone pillar which " +
        "caught your eye from the road. The shadow stretches over some " +
        "rocks and leaves, long and pointed just like the pillar itself. " +
        "If you had not been carrying your own light, you are certain " +
        "that you never would have seen it.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"leaves", "pile of leaves", "leaf pile"}),
        "Several leaf piles are scattered across the forest floor. " +
        "When you consider just how many trees are here, you hardly " +
        "find that surprising. Many of the leaves are piled " +
        "around the base of a tall stone pillar.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"rocks", "pile of rocks", "rock pile"}),
        "There are many small piles of rocks scattered around the" +
        "forest floor, including one small cluster that crowns the " +
        "long pointed shadow created by the stone pillar. You notice " +
        "in passing that the pillar is covered in a bunch of " +
        "strange carvings.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"cluster","rock cluster"}),
    	"This small cluster of rocks forms a rough circle right " +
    	"at the end of the tip of the shadow created by the stone " +
    	"pillar.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"rock circle", "circle", "crown", "rock crown"}),
        "This is a small, circular cluster of rocks resting against " +
        "the base of an old oak. It looks pretty much like every other " +
        "cluster of rocks in the forest. You only noticed this particular " +
        "circle because the tip of the shadow from the stone pillar fell " +
        "right in the center of the circle.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"oak", "old oak", "old oak tree"}),
        "This tree is no different than any of the other oak trees in " +
        "Mirkwood. You only really paid attention to it because of the " +
        "small cluster of rocks at its base, which sat atop the shadow " +
        "from the pillar. But, as you look closer, you see a small " +
        "wooden shelter has been constructed on the far side of the " +
        "tree trunk.\n", ({LIGHT_BRIGHT}));
    
    add_exit("r23", "east");
    add_exit("r21", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f26", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f27", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f28", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f26", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f27", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f28", "southeast");

    setuid();
    seteuid(getuid());
    object shelter = clone_object(MIRKWOOD_OBJ_DIR + "shelter");
    shelter->move(this_object());
}

int press_cmd(string args) {
    int light_level = query_light_level_for_living(this_player());

    if (!args || !strlen(args) || (light_level != LIGHT_BRIGHT)) {
        notify_fail("What?\n");
        return 0;
    }

    if (parse_command(args, ({}), "[hand] 'print' / 'handprint'")) {
        write("You lay your hand down over the handprint and press, "
            + "but nothing seems to happen.\n");
        say(QCTNAME(this_player()) + " presses something on the pillar.\n");
        return 1;
    }

    if (parse_command(args, ({}), "'image' / 'images' / 'carving' / 'carvings'")) {
        write("Would you like to press the bear " + args + " or the spider " + args + "?\n");
        return 1;    
    }

    if (parse_command(args, ({}), "'bear' [image] / [images] / [carving] / [carvings]")) {
        write("You press down firmly on the bear image and wait a few "
              + "moments, but nothing seems to happen.\n");
        say(QCTNAME(this_player()) + " presses something on the pillar.\n");
        return 1;    
    }

    if (parse_command(args, ({}), "'spider' [image] / [images] / [carving] / [carvings]")) {
        write("You press down firmly on the spider image and wait a few "
              + "moments, but nothing seems to happen.\n");
        say(QCTNAME(this_player()) + " presses something on the pillar.\n");
        return 1;    
    }

    notify_fail("Perhaps you wanted to press on one " +
        "of the carvings instead?\n");
    return 0;
}

void init() {
    ::init();
    add_action(press_cmd, "press");
}
