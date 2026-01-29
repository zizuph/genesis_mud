#pragma save_binary
#pragma strict_types

#include "local.h"
#include "/d/Shire/private/shire_admin.h"

inherit EAST_ROAD;
inherit "/d/Shire/std/room/room_tell";

void
create_room()
{
    set_short("Inside the ruined Forsaken Inn");
    set_long("Water drips from the sagging beams hanging "+
      "precariously above you, and splashes and pools amongst "+
      "the ruined and furniture and fittings around you. The "+
      "entire upper level is destroyed, and you can see light "+
      "seeping in through some of the many holes in the roof, "+
      "which you can see from the holes in the floor above you"+
      ". All of the windows and most of the shutters are dest"+
      "royed, along with what must have once been the kitchen. "+
      "From the darkened east end of the building you hear some "+
      "kind of low pitched moaning; looking closer it seems that "+
      "there is a wide hole in the floor where a staircase used "+
      "to go down. A wide opening in the west wall allows you a "+
      "way out of this unsettling place.\n");

    add_item(({"water","drips","pools"}),
      "The prodigious holes in the shingled roof leave little "+
      "protection from the elements, even with the first level "+
      "above you, as there is little left of what once must have "+
      "been some of the finest woodwork. Water has run down "+
      "through the above floor as well as down the walls, and "+
      "now collects in large tepid pools under your feet.\n");
    add_item(({"wood","beams","shingles","woodwork"}),
      "The timber in this building was undoubtedly meant to "+
      "last a life-time, but its been several times that since "+
      "anyone has cared for this place. The shingles on the roof "+
      "have crumbled, the wooden floors have flexed and sagged "+
      "from taking on water, and all the finishings are destroyed "+
      "just the same.\n");
    add_item(({"windows","shutters","outside"}),
      "You can catch a staggered glimpse of the outside through "+
      "the now missing windows and broken shutters, as well as "+
      "a good draft.\n");
    add_item(({"kitchen","bar"}),
      "Over to the eastern end of the building you can see what "+
      "is left of the bar, and behind it the sorry remains of "+
      "the Inn's kitchen. Cracks in the floor give warning not "+
      "to take too close a look.\n");
    add_item(({"moaning","low pitched moaning"}),
      "As you walk a little closer to the east side of the room, "+
      "the sound becomes a little clearer, you guess its the "+
      "voice of someone with a deep and gruff voice singing.\n");
    add_item(({"singing","gruff voice"}),
      "You suspect the voice belongs to a male human or dwarf "+
      "who has most likely had quite a lot to drink.\n");
    add_item(({"wide hole","hole","staircase"}),
      "Taking care to avoid the weaker parts of the sodden floor "+
      "you approach the wide hole in the dark eastern end of the "+
      "building. You can see part of a staircase heading down, "+
      "but seems that most of it has rotted away leaving dangerous "+
      "footing for any stupid or brave enough to want to go down.\n"+
      "If you think you're either of the above, you may try to "+
      "climb down into the hole.\n");

    set_room_tell_time(30);
    add_room_tell("A gust of cool wind blows by, and the timbers of the "+
      "of the Forsaken Inn emit an eerie groan.\n");
    add_room_tell("One of the window shutters slams against the wall, "+
      "startling you.\n");
    add_room_tell("You feel a thud as something crashes nearby.\n");
    add_room_tell("A faint rumbling like singing reaches your ears.\n");
    add_room_tell("You hear a deep-throated roar, that must be coming "+
      "from inside the Inn.\n");
    add_room_tell("From inside the Inn you hear a loud splash.\n");

    add_exit(ER_DIR + "erb6",  "out", 0, 1);

}

void init()
{
    ::init();
    add_action("climbdown", "climb");
}

int climbdown(string down)
{
    notify_fail("Climb where?\n");

    if (down!="down") return 0;
    write("You hope for the best and slip your legs over the edge "+
      "of the hole, scrambling for a foothold. As you put your "+
      "weight down on what seems to be a step it gives way and "+
      "leaves you tumbling ungracefully to the dirty floor below.\n\n");
    say(QCTNAME(TP)+" slips into the hole in the floor, seems to "+
      "be doing well, then suddenly slips out of sight.\n");

    TP->move_living("down through the hole", ER_DIR + "inn2");

    TELL_ADMIN(TP->query_cap_name() +" is climbing down towards Khaaz.");
    return 1;

}
