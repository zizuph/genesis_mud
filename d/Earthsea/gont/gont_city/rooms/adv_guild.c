#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>

public void
set_up_skills()
{
    string str;
    str = "fight unarmed";
    sk_add_train(SS_UNARM_COMBAT, str, 0, 0, 30);
    sk_add_train(SS_DEFENCE, ({"defend yourself", "defend oneself"}),
        0, 0, 20);
    str = "use a sword"; 
    sk_add_train(SS_WEP_SWORD, str, "sword", 0, 30);
    str = "use a polearm";
    sk_add_train(SS_WEP_POLEARM, str, "polearm", 0, 30);
    str = "use a knife"; 
    sk_add_train(SS_WEP_KNIFE, str, "knife", 0, 30);
    str = "use a club"; 
    sk_add_train(SS_WEP_CLUB, str, "club", 0, 30);
    str = "use an axe";
    sk_add_train(SS_WEP_AXE, str, "axe", 0, 30);
    str = "fight in the dark";
    sk_add_train(SS_BLIND_COMBAT, str, "blind combat", 0, 20);
    str = "swim";
    sk_add_train(SS_SWIM, str, 0, 0, 30);
    str = "climb";
    sk_add_train(SS_CLIMB, str, 0, 0, 30);
    sk_add_train(SS_LOC_SENSE, ({"sense your location",
        "sense locations"}), "location sense", 0, 30);
    str = "track";
    sk_add_train(SS_TRACKING, str, 0, 0, 30);
    str = "be aware of surroundings";
    sk_add_train(SS_AWARENESS, str, 0, 0, 30);
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Earthsea Adventurers' Guild");
    set_long("This is the local Adventurer's "+
        "Guild, where travellers from anywhere may <improve> "+
        "their skills or possibly <learn> new ones. You may "+
        "also <list guilds> here to get useful information "+
        "on the guilds you belong to. It is quite a large "+
        "room about the size of a gymnasium. You notice that there "+
        "are some futons arranged on the floor for those "+
        "who wish to <meditate>, as well as training equipment "+
        "for warriors. There are two exits on either "+
        "side to smaller rooms where travellers may compose or "+
        "read notes.\n");
    add_item((({"futons", "floor"})),
        "The futons are on the floor arranged against the "+
        "wall for those who wish to meditate.\n");
    add_item((({"equipment", "training equipment"})),
        "You notice some dummy weapons and weights for training "+
        "about the floor, so that you may improve your skills "+
        "and conditioning here.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("city_street/city_road13", "south");
    add_exit("board_room", "board");
    add_exit("common_board", "common");
    create_guild_support();
    create_skill_raise();
    set_up_skills();
}

public void
init()
{
    ::init();
    init_skill_raise();
    init_guild_support();
}
