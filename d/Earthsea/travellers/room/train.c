#pragma strict_types
#pragma save_binary

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>

inherit TRAVELLERS_STD_DIR + "room_base";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

public void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_APPR_MON, "appraise opponents", "appraise enemy",
        0, 35);
    sk_add_train(SS_APPR_OBJ, "appraise objects", "appraise object",
        0, 35);
    sk_add_train(SS_LANGUAGE, "understand foreign languages", "language",
        0, 40);
    sk_add_train(SS_TRACKING, "track", "track", 0, 40);
    sk_add_train(SS_WEP_POLEARM, "fight with a polearm", "polearm",
        0, 50);
    sk_add_train(SS_CLIMB, "climb walls and mountains", "climb",
        0, 45);
    sk_add_train(SS_ANI_HANDL, "handle animals", "handle animals",
        0, 30);
    sk_add_train(SS_LOC_SENSE, "be aware of surroundings", "awareness",
        0, 50);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 50);
    sk_add_train(SS_TRADING, "trade successfully", "trade",
        0, 50);
}

public void
create_traveller_room()
{
    add_prop(ROOM_S_MAP_FILE, "trav_map.txt");
    set_short("Travellers Training Room");
    set_long("This is the training room of the Travellers' guild-- " +
        "a large, cozy room with a single flickering lantern hanging " +
        "from the ceiling high above. Maps wallpaper the room, "  +
        "detailing some of the areas which guild members have explored. " +
        "Members of the travellers may improve their skills here. On " +
        "the far wall is a sign. In the corner is a mat for meditation, " +
        "where some decide how they would like to advance.\n");
    add_item(({ "lantern", "flickering lantern" }),
        "The lantern hangs from a hook attached to the ceiling. Light " +
        "spills from the lantern, casting shadows across the floor " +
        "where you stand, and illuminating the room.\n");
    add_item(({ "map", "maps" }),
      "The maps are large drawings of various areas of the " +
      "known and unknown world. Copies of most of them " +
      "are available in the library.\n");
    add_item("sign","You see a sign on the wall, " +
        "perhaps you can read it.\n");
    add_cmd_item("sign","read",
        "Travellers may learn the following skills within this " +
        "training facility:\n" +
        "\tAppraise objects\t\tConfident acolyte\n" +
        "\tAppraise opponents\t\tConfident acolyte\n" +
        "\tUnderstand foreign languages\tSuperior acolyte\n" +
        "\tTracking\t\t\tSuperior acolyte\n" +
        "\tFight with a polearm\t\tSuperior journeyman\n" +
        "\tClimb walls and mountains\tConfident journeyman\n" +
        "\tHandle animals\t\t\tSuperior layman\n" +
        "\tLocation Sense\t\t\tSuperior journeyman\n" +
        "\tSwimming\t\t\tSuperior journeyman\n" +
        "\tTrade successfully\t\tSuperior journeyman\n");
    add_exit("balcony", "east");
    set_up_skills();
}

public void
init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
}
