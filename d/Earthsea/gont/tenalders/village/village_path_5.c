/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

public void
create_earthsea_room()
{
    set_short("Village path");
    set_long("A gravel path. The path winds among several " +
        "thatch-covered huts that comprise this small " +
        "village, situated on a somewhat more level area of " +
        "the mountain side. The path continues north " +
        "and southwest from here. To the south you see a hut " +
            "which is blackened by smoke and soot. From the sound " +
            "of ringing metal, you deduce that it is a blacksmith's " +
            "shop\n");
    add_item((({"hut", "south hut", "thatch-covered huts", "huts"})),
        "Among the small huts of this village, the one just to the " +
        "south is blackened by soot and appears to be a blacksmith's " +
        "shop.\n");
    add_item("village", "The small village is comprised of " +
        "a number of thatch-covered huts that cling to the " +
        "mountainside.\n");
    add_item("sign","A small wooden plank with words painted on " +
        "them. You might try reading the sign.\n");
    add_item(({"gravel path","gravel"}),"You see nothing largely " +
        "interesting about the the path.\n");
    add_item(({"mountain","mountainside","mountain side","side"}),
        "The mountain reaches high above you.\n");
    add_item(({"soot"}),"The sides of the hut have been stained " +
        "by smoke from the forge within.\n");
    add_exit("village_path_4", "north");
    add_exit("village_path_6", "southwest");
    add_exit("smithy", "south");
}
