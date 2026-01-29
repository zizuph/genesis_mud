#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>

#define HORN_IS_HUNG   "_horn_is_hung"

inherit "/std/object";

public int do_sound(string str);

public string
check_hung()
{
    if (query_prop(HORN_IS_HUNG))
        return "The horn is hanging by sturdy iron chains from the " +
            "wooden framework.";
    else
        return "";
}

public void
create_object()
{
    set_name("horn");
    add_name("_eldoral_lake_horn");
   set_adj("large");
    add_adj("ram's");
    set_short("large ram's horn");
    set_long("A large ram's horn, carefully polished and hollowed " +
        "to form a horn that can be sounded, for whatever reason. " +
        "Upon it's surface is an intricate, weaving pattern of " +
        "abstract lines twisting in and out. @@check_hung@@\n");
    add_item(({"pattern", "pattern on horn", "lines", "lines on horn"}),
        "They appear to have no purpose, simply weaving aimlessly " +
        "around the horn in a delicate pattern. However, after " +
        "staring for a moment you can see a small boat of some sort " +
        "depicted not by the lines, but by the pattern they create.\n");

    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_S_WIZINFO, "This horn is used to summon a skiff " +
        "which will take players across Eldoral Lake to the " +
        "island. It is placed randomly, and players must search " +
        "the rooms in /d/Calia/eldoral/mountain/* until they " +
        "find it. It is also guarded by a kroug which must be " +
        "first killed. Once found, players should take it to " +
        "/d/Calia/eldoral/mountain/mshore2, where it can be " +
        "hung on a frame and sounded to summon the skiff. " +
        "The horn is destroyed in the process.\n");
    add_prop(MAGIC_AM_MAGIC, ({50, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
        ({"You sense the sound of the horn would draw " +
          "the attention of someone or something.\n",
          10,
          "By sounding the horn in the right place, " +
          "something will come to you.\n",
          30,
          "The sound will summon a skiff, which will " +
          "carry you through the mist, across still " +
          "waters.\n",
          50}));
    add_prop(OBJ_M_NO_BUY, 1);
}

public void
init()
{
    ::init();
    add_action(do_sound, "sound");
    add_action(do_sound, "blow");
}

public int
do_sound(string str)
{
    object ob,
           *obarr;
    notify_fail(capitalize(query_verb()) + " what?\n");

    if (!str || !strlen(str))
        return 0;

    obarr = FIND_STR_IN_OBJECT(str, TP);

    if (!sizeof(obarr))
        return 0;

    if (sizeof(obarr) > 1)
    {
        write("You can only " + query_verb() + " one object at a time.\n");
        return 1;
    }

    if (obarr[0] != TO)
        return 0;

    if (!query_prop(HORN_IS_HUNG))
    {
        write("You blow hard into the ram's horn, but you can't " +
        "quite seem to make it make any noise.\n");
        return 1;
    }
    else
    {
        write("You blow into the horn, and to your amazement it begins " +
            "to vibrate lightly upon the chains. Suddenly, a single " +
            "loud, clear note roars out of the horn, and echoes " +
            "across the misty waters. If anything was out there, it " +
            "would definately have heard it.\n");
        say(QCTNAME(TP) + " blows into the horn, and to your amazement " +
            "it begins to vibrate lightly upon the chains. Suddenly, " +
            "a single loud, clear note roars out of the horn, and echoes " +
            "across the misty waters. If anything was out there, it " +
            "would definately have heard it.\n");
        environment(TO)->try_to_start_skiff();
        seteuid(getuid());
        if (!BITMASTER->test_bit(ELDORAL_HORN_QUEST_BIT, TP))
            BITMASTER->set_bit(ELDORAL_HORN_QUEST_BIT, TP);
        tell_room(environment(TO), "Suddenly, the ram's horn shatters " +
            "into a thousand pieces, which vanish upon the wind!\n");
        remove_object();
        return 1;
    }

    return 0;
}

public void
hang_horn()
{
    add_prop(HORN_IS_HUNG, 1);
    add_prop(OBJ_M_NO_GET, "The horn has somehow fused with the " +
        "chains, it cannot be removed.\n");
    set_no_show_composite(1);
}

public void
remove_horn()
{
    remove_prop(HORN_IS_HUNG);
    remove_prop(OBJ_M_NO_GET);
    set_no_show_composite(0);
}
