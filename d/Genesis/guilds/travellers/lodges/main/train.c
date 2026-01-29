#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
 
public void
set_up_skills()
{
    create_skill_raise();

    sk_add_train(SS_APPR_MON, "appraise opponents", 0, 0, 35);
    sk_add_train(SS_APPR_OBJ, "appraise different objects", 0, 0, 35);
    sk_add_train(SS_LANGUAGE, "understand foreign languages", 0, 0, 40);
    sk_add_train(SS_TRACKING, "track", 0, 0, 40);
    sk_add_train(SS_WEP_POLEARM, "fight with a polearm", 0, 0, 50);
    sk_add_train(SS_CLIMB, "climb walls and mountains", 0, 0, 45);
    sk_add_train(SS_ANI_HANDL, "handle animals", 0, 0, 30);
    sk_add_train(SS_LOC_SENSE, "be aware of surroundings", 0, 0, 50);
    sk_add_train(SS_SWIM, "swim", 0, 0, 50);
    sk_add_train(SS_TRADING, "trade successfully", 0, 0, 50);
}

public void
create_traveller_room()
{
    set_short("Travellers Training Room");
    set_long("This is the training room of the Travellers' guild-- " +
        "a large, cozy room with a single flickering lantern hanging " +
        "from the ceiling high above. Maps wallpaper the room, " +
        "detailing some of the areas which guild members have explored. " +
        "Members of the travellers may improve their skills here. In the " +
        "corner is a mat for meditation, where some decide how " +
        "they would like to advance.\n");
 
    add_item(({"lantern","flickering lantern"}), "The lantern hangs from " +
        "a hook attached to the ceiling. Light spills from the lantern, " +
        "casting shadows across the floor where you stand, and " +
        "illuminating the room.\n");
 
    add_item(({ "map", "maps" }),
        "The maps are large drawings of various areas of the " +
        "known and unknown world. Copies of most of them " +
        "are available in the library.\n");
 
    add_exit("balcony", "east");
 
    create_guild_support();
    set_up_skills();
}
 
public void
init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
}
 
