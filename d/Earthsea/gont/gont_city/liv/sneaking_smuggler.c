#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";

#include <ss_types.h>
#include "defs.h"

#define ADJS ({ "tiny", "nasty", "nasty", "scowling", "pimpled" })
#define COLOURS ({ "pale", "green-skinned", "wrinkled",\
    "scary", "smelly" })

private int sequence_active = 0;

public void
reset_sequence()
{
    if(sequence_active)
    {
        return;
    }

    sequence_active = 1;
    seq_reset();
    seq_new("work_in_warehouse");
    seq_addfirst("work_in_warehouse", ({
        "sneak n", "sneak ne", "sneak n", "sneak e",
        "emote pushes a few crates aside, bends down and starts " +
        "scratching at the ground.", 3,
        "emote searches through a pile of sacks, but does not seem to " +
        "find what he is looking for.", 8,
        "mumble something about a shipment being late.", 3,
        "shrug",
        "sneak w", "sneak s", "sneak sw", "sneak s",
        "emote leans against the cliff.", 3,
        "emote stares up towards the tower.", 3,
        "kick all angri", 3,
        "tap", "@@check_arrival"
    }));
}

public void
create_earthsea_monster()
{
    string adj1 = ADJS[random(sizeof(ADJS))],
        adj2 = COLOURS[random(sizeof(COLOURS))];
    set_adj(({ adj2, adj1 }));
    set_name("__es_sneaking_smuggler__");
    set_short(adj1 + " " + adj2 + " goblin");
    set_pshort(adj1 + " " + adj2 + " goblins");
    add_name("smuggler");
    set_race_name("goblin");
    set_height("very short");
    set_width("fat");
    set_long("This character looks very mean and "+
       "rotten. You suspect that he is some sort of criminal.\n");
    set_stats(({ 20, 15, 15, 2, 2, 60 }));
    add_equipment(({ WEP + "scramasax", ARM + "jerkin"}));
    set_skill(SS_WEP_SWORD, 35);
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_HIDE, 25);
    set_skill(SS_SNEAK, 25);
    set_act_time(45);
    add_act("snarl . all");
    add_act("grumble tiredly");
    add_act("mumble something to himself.");
    set_skill(SS_HIDE, 20);
    set_skill(SS_SNEAK, 20);
    reset_sequence();
}

public string
check_arrival()
{
    if(file_name(environment(this_object())) !=
        "/d/Earthsea/gont/gont_city/rooms/city_street/city_road23a")
    {
        command("peer");
        command("say Where the heck am I?");
        command("panic");
        command("emote runs off into the distance.");
        remove_object();
        return "";
    }

    sequence_active = 0;

    set_alarm(15.0, 0.0, &reset_sequence());
    return "twiddle";
}
