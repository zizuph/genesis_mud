/* /d/Calia/argos/farmstead/mobiles/spirit.c
**   A wailing spirit - This is the main mobile of the farmstead
**   widow quest. It contains all logic for checking the completion
**   of steps, as well as rewarding the player
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/22/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

// global variables
int busy_ask = 0;
// prototypes
void default_response();
void husband_response();
void soup_response();
void start_quest();
void do_quest();

void
create_monster()
{
    seteuid(getuid());
    if (!IS_CLONE) return;

    set_name(({ "sophia", "spirit", "ghost" }));
    set_race_name("ghost");

    add_adj("wailing");
    set_short("wailing spirit");
    set_long(
        "This is the ethereal ghost of a farm-dwelling woman. It seems to be "
        + "locked in a state of eternal torment, unable to rest before the "
        + "completion of some unfinished business.\n"
    );

    set_gender(G_FEMALE);

    add_prop(LIVE_I_UNDEAD, 10);
    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, " does not accept gifts from you.\n");
    add_prop(OBJ_M_NO_ATTACK, "She is already quite dead.\n");

    set_act_time(5);
    add_act("say Where is my husband gone to? He should be home by now!");
    add_act("scream");
    add_act("wail");
    add_act("cry");
    add_act("worry");
    add_act("emote emits a shrill shriek!");

    set_default_answer("@@default_response");
    add_ask(({ " [about] [her] 'husband' " }), "@@husband_response");
    add_ask(
        ({ " %s 'how' [does] [your] [the] 'husband' 'look' / 'looks' " }),
        "@@husband_response"
    );
    add_ask(
        ({
            " %s 'help' / 'task' / 'quest' / 'find' [your] [him] / [husband] "
        }),
        "@@start_quest"
    );
    add_ask(({ " [to] 'serve' [the] 'supper' " }), "@@do_quest");
    add_ask(
        ({ " [about] [the] [what] [how] [to] [make] 'soup' " }),
        "@@soup_response"
    );
    add_ask(
        ({ " [what] / [what's] [is] [for] 'supper' " }),
        "say What's for supper? I've made soup!",
        1
    );
}

void
default_response()
{
    if (CAN_SEE(TO, TP) && !busy_ask)
    {
        command(
            "say to " + OB_NAME(TP) + " I can't deal with that right now, I'm "
            + "waiting for my husband to join me for supper."
        );
        command("peer worried");
        command(
            "say to " + OB_NAME(TP) + " He should have been home by now. Have "
            + "you seen him, perhaps? Could you help me find him?"
        );
    }
}

void
husband_dialogue(object player)
{
    busy_ask = 0;
    set_this_player(player);
    if (CAN_SEE(TO, TP))
    {
        command(
            "say My husband is such a handsome man. Prominent jaw. Full head "
            + "of hair, as thick and fair as a lump of straw. Oh, and such "
            + "large and plentiful teeth. Like a handful of pebbles, they are!"
        );
        command("sigh wistf");
    }
}

void
husband_response()
{
    if (CAN_SEE(TO, TP) && !busy_ask)
    {
        busy_ask = 1;
        command("say My husband?");
        command("emote 's face appears to briefly light up.");
        set_alarm(2.0, 0.0, &husband_dialogue(TP));
    }
}

void
soup_dialogue(int stage, object player)
{
    set_this_player(player);
    if (CAN_SEE(TO, TP))
    {
        if (stage == 1)
        {
            command("hmm");
            command(
                "say to " + OB_NAME(TP) + " Oh well, I suppose I can share it "
                + "with you."
            );
            set_alarm(2.0, 0.0, &soup_dialogue(2, TP));
        }
        if (stage == 2)
        {
            command(
                "say to " + OB_NAME(TP) + " First you add some water and a "
                + "turnip to a cauldron, see."
            );
            command("gesture vivid");
            set_alarm(2.0, 0.0, &soup_dialogue(3, TP));
        }
        if (stage == 3)
        {
            command(
                "say to " + OB_NAME(TP) + " And then you boil it. Best soup "
                + "ye'll ever taste!"
            );
            command("smile proud");
            busy_ask = 0;
        }
    } else {
        busy_ask = 0;
    }
}

void
soup_response()
{
    if (CAN_SEE(TO, TP) && !busy_ask)
    {
        busy_ask = 1;
        command(
            "say to " + OB_NAME(TP) + " The soup? It's an old family recipe."
        );
        set_alarm(2.0, 0.0, &soup_dialogue(1, TP));
    }
}

void
start_quest()
{
    if (CAN_SEE(TO, TP) && !busy_ask)
    {
        command("say to " + OB_NAME(TP) + " You will help me? Wonderful!");
        command(
            "say to " + OB_NAME(TP) + " Go and find my husband, then have him "
            + "join me at the table. Once he's here, ask me to serve supper."
        );
        command("smile");
    }
}

void
reward_quest(object player)
{
    set_this_player(player);

    write(
        "Having shared a final meal with her beloved husband, "
        + TO->query_the_name(TP) + " looks relieved, as if she finally found "
        + "peace.\n"
    );
    command("emote lets out a sigh of relief and fades away.");

    if (!present(TP, environment(TO)))
    {
        return;
    }

    if (!TP->test_bit(QUEST_DOM, QUEST_GROUP, QUEST_BIT))
    {
        if (
            TP->query_prop(FARMSTEAD_I_HAIR) &&
            TP->query_prop(FARMSTEAD_I_TEETH) &&
            TP->query_prop(FARMSTEAD_I_COOKED) &&
            TP->query_prop(FARMSTEAD_I_PLACED_SKULL)
        )
        {
            write("You feel more experienced!\n");
            TP->add_exp_quest(QUEST_EXP);
            TP->set_bit(QUEST_GROUP, QUEST_BIT);
            TP->command("save");

            string log_string = ctime(time()) + ": " + TP->query_name() + " ("
            + TP->query_average_stat() + ") completed farmstead widow "
            + "quest. Exp: " + QUEST_EXP + "\n";
            write_file(DOC_DIR + "quest_log.txt", log_string);
        } else {
            write(
                "Since you didn't complete all the steps yourself, you aren't "
                + "any more experienced than you were before. You feel as if "
                + "you could try again soon, though.\n"
            );
        }
    } else {
        write(
            "You have already gleaned all there is to learn from completing "
            + "this quest.\n"
        );
    }

    environment(TO)->reset_quest();
    remove_object();
}

int
check_skull(object skull, object player)
{
    set_this_player(player);
    tell_room(
        environment(TO),
        QCTNAME(TO) + " closely scrutinizes the " + skull->short() + ".\n",
        0
    );
    command("say Yes, prominent jaw...");

    if (skull->query_teeth() && skull->query_hair())
    {
        command("say A thick and full head of fair hair...");
        command("say Plentiful teeth...");
        command("beam");
        command("say Husband! There you are!");
        command(
            "say Oh, how joyous! Let's eat, the supper has been waiting "
            + "for ages, it feels like..."
        );
        return 1;
    }

    if (skull->query_hair())
    {
        command("say A thick and full head of fair hair...");
        command("gasp");
        command(
            "say But no teeth?"
        );
    } else {
        command("gasp");
        command("say But no hair?");
    }

    command("say What foolery is this? This looks nothing like my husband!");
    write(
        TO->query_The_name(TP) + " shrieks shrilly and slams the table, "
        + "sending the " + skull->short() + " soaring through the air.\nYou "
        + "catch it right before it hits the ground.\n"
    );
    tell_room(
        environment(TO),
        QCTNAME(TO) + " shrieks shrilly and slams the table, sending the "
        + skull->short() + " soaring through the air.\n" + QCTNAME(TP)
        + " nimbly catches it.\n",
        TP
    );
    skull->move(TP, 1);
    environment(TO)->reset_skull_pointer();
    busy_ask = 0;
    return 0;
}

/*
 * Function name: quest_steps
 * Description  : Checks if the player has completed all the necessary
 *                steps of the farmstead widow quest, providing cues to
 *                the player through dialogue. The file-global variable
 *                busy_ask is used to ensure that other dialogue
 *                responses will be blocked while this is running, so
 *                as not to interfere.
 * Arguments    : int step: 1 | 2 - Controls which step of the quest will
 *                  checked in this iteration, as the function recurses until
 *                  it is complete.
 *                object player - A reference to this_player, as this may get
 *                  lost when calling a function through set_alarm
 */
void
quest_steps(int step, object player)
{
    set_this_player(player);
    if (CAN_SEE(TO, TP))
    {
        // Check if skull related steps were completed
        if (step == 1)
        {
            object skull = environment(TO)->get_skull_ref();
            if (skull)
            {
                if (check_skull(skull, TP))
                {
                    set_alarm(2.0, 0.0, &quest_steps(2, TP));
                }
            } else {
                command("peer confused");
                command(
                    "say to " + OB_NAME(TP) + " But my husband is not sat "
                    + "at the table!"
                );
                command("sniff");
                command(
                    "say to " + OB_NAME(TP) + " I will not serve supper "
                    + "before he is here."
                );
                busy_ask = 0;
            }
        }

        // Check if soup related steps were completed and if so give reward
        if (step == 2)
        {
            if (environment(TO)->query_soup_cooked())
            {
                command("emote pours two bowls of soup and takes a seat "
                + "at the table.");
                set_alarm(2.0, 0.0, &reward_quest(TP));
            } else {
                command("emote takes a peek into the cauldron.");
                command("gasp");
                command(
                    "say What is this? My soup is gone? No, no, no, this "
                    + "isn't right. This isn't right at all!"
                );
                command("cry uncontrollably");
            }
            busy_ask = 0;
        }
    } else {
        busy_ask = 0;
    }
}

void
do_quest()
{
    if (CAN_SEE(TO, TP) && !busy_ask)
    {
        busy_ask = 1;
        command("say to " + OB_NAME(TP) + " All is set then?");
        set_alarm(2.0, 0.0, &quest_steps(1, TP));
    } else {
        command("say Who said that?");
    }
}
