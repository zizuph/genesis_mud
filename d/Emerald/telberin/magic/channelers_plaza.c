#include "/d/Emerald/telberin/defs.h"

inherit TELBERIN_CHANNELERS_WAY;

public void
create_channelers_way()
{
    set_em_long("Channelers Way opens into a wide oval plaza here,"
      + " ringed by various buildings. Directly to the north, a"
      + " long reflecting pool runs the length of the Magic Quarter,"
      + " before it halts at the distant feet of the Tower of"
      + " Telan-Ri. To the east, another great tower rises above the"
      + " street. In the center of Channelers Plaza, a beautiful"
      + " fountain shimmers in the air. People pass to and fro"
      + " along the plaza, many heading back along Channelers Way as"
      + " it runs northwest and northeast.\n");

    add_item( ({ "tower of telan-ri" }),
        "The Tower of Telan-Ri is visible to the north, its tall"
      + " branching form rising like a great tree from the end of"
      + " the long reflecting pool which separates this plaza from"
      + " the Royal Circle.\n");
    add_item( ({ "east", "tower", "great tower", "guild",
                 "mage guild", "mage guild of telberin", 
                 "column", "great column" }),
        "To the east stands the Mage Guild of Telberin."
      + " Unlike the other great buildings in the City, this"
      + " one is not highly ornamented, or branching with many"
      + " spires and turrets. Rather, it appears as a single"
      + " great column which narrows as it rises. The only"
      + " features visible upon its sides are narrow windows,"
      + " and a large arched entryway.\n");
    add_item( ({ "entry", "entryway", "arched entryway",
                  "large arched entryway", "arch", "large arch",
                  "archway", "entrance", "open archway",
                  "large archway", "entrance to the tower",
                  "tower entrance" }),
        "The entrance to the tower lies directly to the east. It"
      + " does not involve any kind of door. Rather, it is an open"
      + " archway leading within the Mage Guild.\n");
    add_item( ({ "plaza", "oval plaza", "wide plaza",
                 "wide oval plaza", "channelers plaza", "here",
                 "area" }),
        "Channelers Plaza is a major center for those concerned with"
      + " the methods of magic in Telberin. This interest is reflected"
      + " both in the appearance of the persons here as well as the"
      + " buildings in the area.\n");
    add_item( ({ "building", "buildings" }),
        "The buildings in this area have an air of mystery about them."
      + " Some appear to be little more than residences. Others,"
      + " however, have signs of magic within. Smoke of various"
      + " colors pours from the chimneytops, and queer lights shimmer"
      + " in a number of windows. A clear standout from the other"
      + " buildings, the Mage Guild of Telberin looms above you to"
      + " the east.\n");
    add_item( ({ "chimney", "chimneys", "chimneytop", "chimneytops",
                 "smoke" }),
        "From a number of the nearby chimneytops, smoke of very"
      + " curious color is rising. Sometimes the smoke appears orange,"
      + " while at other times it has a more turquoise hue.\n");
    add_item( ({ "queer lights", "lights" }),
        "Every so often, a strange burst of multicolored lights"
      + " comes from the windows of nearby buildings. There must be"
      + " magic afoot here.\n");
    add_item( ({ "window", "windows", "narrow window",
                 "narrow windows" }),
        "The tower to the east is flecked along its height by"
      + " a great number of windows. As the tower rises out of view,"
      + " the windows begin to appears a tiny specks. The number of"
      + " levels within the tower is impossible to guess, but must"
      + " be very great indeed.\n");
    add_item( ({ "fountain", "air", "beautiful fountain",
                 "light", "fountain of light" }),
        "This fountain is remarkable in a number of ways. Rather than"
      + " the usual waterfalls and spouts, light itself issues forth"
      + " from unseen sources to dance and play in the middle of the"
      + " square. The effect is somewhat like a slow-moving fireworks"
      + " display, though much more graceful and controlled. Perhaps"
      + " most astonishing is the lack of any monument or structure"
      + " from which the light issues. Rather, it simply flows and"
      + " frolicks above the pavement, unconcerned with physical"
      + " constraints. Every so often, people will actually walk right"
      + " through the display, themselves momentarily colored by its"
      + " bright hues.\n");
    add_item( ({ "person", "persons", "people" }),
        "There are many people travelling through this area. Most"
      + " do not speak, and seem lost in some thought or another."
      + " The vast majority of persons here have a mystical air"
      + " about them, and a look in their eyes which suggests"
      + " arcane knowledge.\n");

    add_building("mage_guild1");
    add_exit("/d/Emerald/telberin/channelers_way03", "northwest");
    add_exit("mage_guild1", "east", 0, 1, 1);

    set_no_exit_msg( ({ "north" }),
        "You walk a few steps into the lawn which borders the long"
      + " reflecting pool, only to be halted at the water's edge.\n");
    set_no_exit_msg( ({ "southeast", "south", "southwest", "west" }),
        "You wander along the row of buildings, peering into windows."
      + " Once in a while, you catch a glance from the inhabitants"
      + " which suggests that your curiosity is not welcome. You make"
      + " your way back to the center of the plaza.\n");
    set_no_exit_msg( ({ "northeast" }),
        "Due to recent raids, the eastern stretch of Channelers Way"
      + " has been shut off to travel. Repair work is visible along"
      + " its damaged path.\n");
}
