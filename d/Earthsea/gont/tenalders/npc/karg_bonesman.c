#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include "/d/Earthsea/quest_handler/quest_handler.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define GOT_DRUM_PROP "__es_bonesman_gave_drum__"
#define GIVEN_TASK_PROP "__es_bonesman_asked_for_gut__"

public string
ask_drum();

public string
ask_task();

public void
create_earthsea_monster()
{
    set_race_name("karg");
    set_name("drummer");
    add_name("bonesman");
    add_adj(({"short", "sinewy", "kargish"}));
    set_short("short sinewy kargish bonesman");
    set_long("A thin and haggardly little karg that seems " +
        "to revel in annoying others with his given role.\n");
    set_act_time(25);
    add_act("beat drum");
    add_act("rimshot");
    add_act("say Some'a'say I the only bonesman left... issnot so!");
    add_act("say There's more to me than the bones... " +
        "I even knows a few doors.");
    set_default_answer(
        "The bonesman continues tapping his bones, ignoring you.\n");

    add_ask("[for] [squeaky] [little] 'drum'", ask_drum);
    add_ask("[squeakly] [little] 'gut' / 'task'",
        ask_task);
    add_ask("'door' / 'doors'",
        "The bonesman raps a bone against his drum, stares off into " +
        "the distance for a moment, then mutters: Aye... ayeei knows " +
        "a little doors. How did it go... 'The mens don't understand.. " +
        "Harm, back door. Back door with the little girls on the crystal " +
        "ship... but she's a sinful woman!'\n");
    add_ask("[sinful] 'woman'",
        "The bonesman grasps his right bone and roars: " +
        "Stay away from me!\n");
    add_ask("[little] 'girl'",
        "The bonesman looks off into the distance and says: " +
        "Alas... she'ses now a sinful woman.\n");
    add_ask("[crystal] 'ship'",
        "The bonesman smirks and replies: Well it ain't really crystal...\n");

    default_config_npc(90);
    set_all_hitloc_unarmed(30);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_DEFENCE, 75);
    add_prop(OBJ_M_HAS_MONEY, ({ 2, 0, 0, 0 }));
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    add_equipment(({
        "/d/Earthsea/gont/tenalders/arm/drum",
        "/d/Earthsea/gont/tenalders/obj/items/bones"
    }));
}

public string
ask_drum()
{
    object tp = this_player();

    if(QH_QUERY_QUEST_COMPLETED(tp, "bonesmans_drum"))
    {
        command("say Me likes me drums'a.");
        return "The bonesman shrugs.\n";
    }

    command("say You likes'a me drum? Youz can have one tooz!");
    command("say But you gotta do-a a task, see.");
    return "The bonesman smiles professionally.\n";
}

public string
ask_task()
{
    object tp = this_player();

    if(QH_QUERY_QUEST_COMPLETED(tp, "bonesmans_drum"))
    {
        command("say I got's nothin for you!");
        return "The bonesman shrugs.\n";
    }

    if(tp->query_prop(GOT_DRUM_PROP))
    {
        command("say I already gives you drum!");
        command("fume");
        return "The bonesman fumes angrily!\n";
    }

    tp->add_prop(GIVEN_TASK_PROP, 1);
    command("nod thoughtf");
    command("say We needs a piccololo for brighter booms.");
    command("say Some convict said he could help us, but da woman - " +
        "she says we can't talk to him no more.");
    command("say I tries to makes-a little drums, but the goat " +
        "skins - they's too thick!");
    command("say I wants to try a gut, but it's got to be little. " +
        "Little and squeaky.");
    return "The bonesman nods thoughtfully.\n";
}

public void
dismiss_gut(object gut)
{
    command("shrug");
    command("emote disposes of the bird gut.");
    gut->remove_object();
}

public void
reject_plain_gut(object ob, object tp)
{
    if(!tp || !present(tp, environment(this_object())))
    {
        dismiss_gut(ob);
        return;
    }

    if(QH_QUERY_QUEST_COMPLETED(tp, "bonesmans_drum"))
    {
        command("shrug");
        command("say I got's nothin for you!");
        ob->remove_object();
        return;
    }

    command("emote fetches a tiny wooden frame and begins " +
        "attempting to squeeze the gut across a wide opening " +
        "with absolutely no success.");
    command("emote gives it back.");
    command("say Is no good! Maybe tha convict knows?");
    command("sigh");
    ob->move(tp, 1);
}

public void
reward_cured_gut(object ob, object tp)
{
    object drum, to = this_object();

    if(!tp || !present(tp, environment(to)) || !CAN_SEE(to, tp))
    {
        dismiss_gut(ob);
        return;
    }

    if(QH_QUERY_QUEST_COMPLETED(tp, "bonesmans_drum"))
    {
        command("shrug");
        command("say I got's nothin for you!");
        ob->remove_object();
        return;
    }

    if(!(drum = present("drum", to)))
    {
        command("scream");
        command("say I'd thank you, but I gots no drum!");
        command("drop gut");
        command("emote wanders off into the distance, grumbling " +
            "all the way.");
        remove_object();
        return;
    }

    command("cheer");
    command("say Now I can makes da piccololo!");
    drum->remove_prop("__es_drum_from_corpse__");
    command("give drum to " + tp->query_real_name());
    command("say Use dat, me goes to makes da drum!");
    command("emote wanders off into the distance.");
    remove_object();
}

public void
enter_inv(object ob, object from)
{
    int is_gut = ob->id("__es_bird_gut__");

    ::enter_inv(ob, from);

    if(!from)
    {
        return;
    }

    if(!is_gut)
    {
        set_alarm(0.0, 0.0, &command("emote gives it back"));
        ob->move(from, 1);
        return;
    }

    if(!ob->query_prop("__es_bird_gut_cured__"))
    {
        set_alarm(2.0, 0.0, &reject_plain_gut(ob, from));
        return;
    }

    set_alarm(2.0, 0.0, &reward_cured_gut(ob, from));
}
