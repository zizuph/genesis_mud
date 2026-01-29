/*
 * /d/Gondor/common/npc/surgeon_haldira.c
 *
 * This surgeon is able to remove scars from you.
 *
 * She is cloned from /d/Gondor/minas/houses/healing/haldira_waiting_room.c
 *
 * /Mercade, 4 May 1994
 *
 * Revision history:
 *  Gwyneth (Nov 4, 2000) - Replaced ~elessar/lib/goodkill.h with
 *                          /d/Gondor/common/lib/logkill.c
 */

inherit "/d/Gondor/common/dwarf_guild/npc/remember";

#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <math.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/defs.h"

#define SAVE_FILE       (MASTER)
#define MY_NAME         "haldira"
#define BASE            (60)
#define COMPUTE_STAT    (((BASE * 4) / 3) + random(BASE / 2) + 1)
#define COMPUTE_SKILL   (MAX(COMPUTE_STAT, 100))
#define CLONE_OBJECT(s) clone_object(s)->move(TO, 1)
#define PARALYZE        "/std/paralyze"
#define PARALYZE_ID     "surgeon_paralyze"
#define BANDAGE         (OBJ_DIR + "bandage")
#define BANDAGE_SHADOW  (OBJ_DIR + "bandage_shadow")

#define PRICES ({ 40, 39, 60, 33, 35, 45, 49, 62, 61, 63 })
#define FACE   ({ 4, 128, 256, 512 })

#define MESSAGES_1 ({                                 \
    ".... hmmm .... cut .... whisper ....",           \
    ".... better .... ouch .... little mistake ....", \
    ".... phew .... almost wrong .... okay now ....",  \
    ".... still unconscious .... or not ....",        \
    ".... ponder .... beautiful .... no marks ....",  \
    ".... errr .... yeah .... mutter .... ",          \
    ".... whisper .... curse .... moan ....",         \
    "AARRRGGHHH .... &#%$@^%# .... darn ....",        \
    ".... relief .... nice .... phew ...." })

#define MESSAGES_2 ({                             \
    "That won't take long.",                      \
    "Almost done.",                               \
    "It was not as bad as I thought it would be.", \
    "Maybe it will succeed.",                     \
    "Ah, now I only have to stitch it.",          \
    "That looks better than I expected it to do." })

static object  client     = 0;
static string *messages_1 = MESSAGES_1;
static string *messages_2 = MESSAGES_2;
static int     scar       = 0;

void
create_monster() 
{
    set_name(MY_NAME);
    add_name( "surgeon" );
    set_living_name(MY_NAME);
    set_race_name("elf");

    set_adj("smart-looking");
    add_adj("agile");

    set_long(BSN("You are looking at a very smart-looking elf. She is " +
	"a real master with her knife and she has great knowledge of the " +
	"anatomy of elves, dwarves, halflings or humans. She may be able to " +
	"remove the scars disfiguring your appearance."));

    set_title("the Surgeon of Minas Tirith");

    set_gender(G_FEMALE);

    set_base_stat(SS_STR, COMPUTE_STAT);
    set_base_stat(SS_DEX, COMPUTE_STAT + (BASE / 3));
    set_base_stat(SS_CON, COMPUTE_STAT);
    set_base_stat(SS_WIS, COMPUTE_STAT + (BASE / 3));
    set_base_stat(SS_INT, COMPUTE_STAT);
    set_base_stat(SS_DIS, COMPUTE_STAT);

    REFRESH;  /* hp, mana, fatigue  */
    FIX_EUID; /* set the euid right */

    set_alignment(500);

    set_skill(SS_BLIND_COMBAT, COMPUTE_SKILL);
    set_skill(SS_WEP_KNIFE,    100);
    set_skill(SS_PARRY,        COMPUTE_SKILL);
    set_skill(SS_DEFENCE,      COMPUTE_SKILL);
    set_skill(SS_AWARENESS,    COMPUTE_SKILL);
    set_skill(SS_UNARM_COMBAT, COMPUTE_SKILL);

    add_prop(OBJ_M_NO_TELEPORT, 1);

    set_cact_time(10);
    add_cact("emote dances around you with swift footwork.");
    add_cact("@@slash_them_all@@");

    set_npc_save_file(SAVE_FILE);
    create_remember();
}

void
arm_surgeon()
{
    object ob;

    fix_souls();

    /* Stupid messages are set after create_living() is called, so we have
     * to set them here. */
    set_mm_in("stalks in gracefully.");
    set_mm_out("stalks away in a graceful manner.");

    CLONE_OBJECT(WEP_DIR + "scalpel");
    CLONE_OBJECT(ARM_DIR + "s_cloak");
    CLONE_OBJECT(ARM_DIR + "s_mask" );
    CLONE_OBJECT(ARM_DIR + "s_apron");
    CLONE_OBJECT(ARM_DIR + "s_pants");

    command("wear all");

    ob = clone_object(DWARF_DIR + "obj/wallet");
    ob->move(TO, 1);

    MONEY_MAKE_GC(random(10))->move(ob, 1);
    MONEY_MAKE_SC(random(20))->move(ob, 1);
    MONEY_MAKE_CC(random(30))->move(ob, 1);
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);

    set_alarm(1.0, 0.0, "command", "wield all");
}

void
init_living()
{
    ::init_living();

    if (this_player()->query_wiz_level())
    {
	return;
    }

    if (ENV()->query_private())
    {
	set_alarm(3.0, 0.0, "help_client");
    }
    else
    {
	add_action("remove", "remove");
    }
}

string
scar_to_part()
{
    switch(scar)
    {
    case   1:
    case   2:
	return "leg";
    case   4:
    case 128:
    case 256:
    case 512:
	return "head";
    case   8:
    case  16:
	return "arm";
    case  32:
    case  64:
	return "hand";
    default:
	return "body-part";
    }
}

int
scar_to_type()
{
    switch(scar)
    {
    case   1:
    case   2:
	return A_LEGS;
    case   4:
    case 128:
    case 256:
    case 512:
	return A_HEAD;
    case   8:
	return A_L_ARM;
    case  16:
	return A_R_ARM;
    case  32:
	return A_L_HAND;
    case  64:
	return A_R_HAND;
    default:
	return 0;
    }
}

int
remove(string str)
{
    object tp = TP;
    string location;
    int    scars;

    if (!strlen(str) ||
	(this_player()->query_wiz_level()))
    {
	NFN0("Remove what?");
    }

    if (parse_command(str, tp, "[a] 'scar' [from] [my] %s", location) != 1)
    {
	notify_fail("Remove scar from where, " + player_name(tp) + "?");
	return 0;
    }

    if (objectp(client))
    {
	npc_say("Sorry, but I'm going to help " + player_name(client) +
	    " first.");
	return 1;
    }

    if (tp->query_no_scar_bandage_shadow())
    {
	npc_say("No, " + player_name(tp) + ", you are still recovering " +
	    "from earlier surgery, judging to your bandage.");
	return 1;
    }

    scars = tp->query_scar();

    if ((scar = member_array(location, F_SCAR_DESCS)) == -1)
    {
	npc_say("You have no scar on your " + location + ", " +
	    player_name(tp) + ".");
	return 1;
    }

    if (!(scars & (1 << scar)))
    {
	npc_say("You have no scar on your " + location + ", " +
	    player_name(tp) + ".");
	return 1;
    }

    if (TOTAL_MONEY(tp) < (PRICES[scar] * 1728))
    {
	npc_say("You do not have enough money to pay the price of " +
	    PRICES[scar] + " platinum coins, " + player_name(tp) + ".");
	return 1;
    }

    scar = (1 << scar);
    npc_say("Follow me, " + player_name(tp) + ". In my private quarters " +
	"I shall treat you. If you follow me, you have to realize the " +
	"following things: in the first half hour after the surgery you " +
        "should not be engaged in combat. Also, you may not wear anything " +
	"on your " + scar_to_part() + ".");

    if (scar_to_part() == "hand")
    {
	npc_say("Oh, and you may not wield anything either.");
    }

    npc_say("Be advised that you may not log out either or that the game " +
	"may not reboot while you are recovering. Take that into " +
	"consideration before you follow me.");

    client = tp;
    set_alarm( 3.0, 0.0, "command", "private");
    set_alarm(60.0, 0.0, "check_client");

    return 1;
}

void
check_client()
{
    if (present(client, ENV()))
    {
	return;
    }

    command("out");

    if (present(client, ENV()))
    {
	command("hmm");
	npc_say("You did not follow me, " + player_name(client) +
	    ", so I could not help you. If you want me to help you, " +
	    "you can ask me again.");
    }

    npc_say("Well, if someone wants my help, he or she " +
	"can ask me for it now.");

    client = 0;
}

void
help_client()
{
    object block;

    if (!present(client, ENV()))
    {
	check_client();
	return;
    }

    if (objectp(block = client->query_armour(scar_to_type())))
    {
	set_alarm(3.0, 0.0, "command", "out");
	npc_say("How can I help you, " + player_name(client) +
	    ", if you are wearing " + LANG_ADDART(block) + " on your " +
	    scar_to_part() + "?");
	client = 0;
	return;
    }

    if (((scar == 32) || (scar == 64)) &&
	(objectp(block = client->query_weapon(scar_to_type()))))
    {
	set_alarm(3.0, 0.0, "command", "out");
	npc_say("How can I help you, " + player_name(client) +
	    ", if you are wielding " + LANG_ADDART(block) + " in your " +
	    scar_to_part() + "?");
	client = 0;
	return;
    }

    npc_say("Okay, " + player_name(client) + " I shall try to help you. " +
	"Do not forget that you have to wear the bandages for at least " +
	"half an hour without removing it and without wearing anything " +
	"on your " + scar_to_part() + ". Also, refrain from entering combat until " +
	"the wound is healed.");

    client->LCATCH_MSG("After you sit down on the table, ",
	" takes a bottle and lets you smell it. You pass out immediately.",
	TO);
    tell_room(ENV(), "After " + PRONOUN(client) + " sits down on the table, " +
	QTNAME(client) + " passes out immediately after " + QTNAME(TO) +
	" takes a bottle and lets " + OBJECTIVE(client) + " smell it.\n",
	({ TO, client }) );

    FIX_EUID;

    block = clone_object(PARALYZE);
    block->set_stop_object(0);
    block->set_stop_fun(0);
    block->set_remove_time(120);
    block->set_stop_verb(0);
    block->set_fail_message("You are unconscious and cannot do that.\n");
    block->set_stop_message(0);
    block->add_name(PARALYZE_ID);
    block->move(client, 1);

    set_alarm( 30.0, 0.0, "after_30_60");
    set_alarm( 60.0, 0.0, "after_30_60");
    set_alarm( 90.0, 0.0, "after_90");
    set_alarm(120.0, 0.0, "fix_client");
}

void
after_30_60()
{
    tell_object(client, ONE_OF_LIST(messages_1) + "\n");
}

void
after_90()
{
    npc_say(ONE_OF_LIST(messages_2));
}

void
fix_client()
{
    object bandage;
    object shadow;

    if (objectp(bandage = present(PARALYZE_ID, client)))
    {
	bandage->remove_object();
    }

    set_this_player(this_object());

    tell_object(client, "You slowly regain consciousness.\n");
    TELL_ROOM(ENV(), client, " slowly regains consciousness.", ({ client }) );

    if (!MONEY_ADD(client, -(PRICES[QUICK_FIND_EXP(scar)] * 1728)))
    {
	command("ponder");
	npc_say("Now that is not nice, " + player_name(client) + "! " +
	    "Before I treated you, you could pay me and now you cannot " +
	    "any more. I have no option than to send you away without " +
	    "extra care. Your scar will not disappear.");
	set_alarm(1.0, 0.0, "command",
	    "wave grimly to " + CAP(client->query_real_name()));
	set_alarm(3.0, 0.0, "command", "out");
	client = 0;
	return;
    }

    npc_say("It all worked out just fine, " + player_name(client) +
	". Now I shall bind the wound up. Remember that you may not " +
	"remove the bandage within half an hour. Also, you may not wear " +
	"anything on the treated part of your body. Stay out of combat " +
	"for the same period, for if you make an unexpected move, it may " +
	"disrupt the wound and leave an ugly scar.");
    npc_say("After half an hour you may remove the bandage. Do not remove " +
	"it earlier, but be sure that you remove it to make sure that the " +
	"wound is healed. Remove it manually to ensure that the surgery " +
	"was indeed successful.");

    client->CATCH_MSG(" puts a bandage over your " + scar_to_part() + ".",
	TO);
    tell_room(ENV(), QCTNAME(TO) + " puts a bandage of the " + scar_to_part() +
	" of " + QTNAME(client) + ".", ({ client, TO }));

    FIX_EUID;

    bandage = clone_object(BANDAGE);
    bandage->set_scar(scar);
    bandage->set_client(client);
    bandage->move(client, 1);

    shadow = clone_object(BANDAGE_SHADOW);
    shadow->set_bandage_object_and_scar(bandage, scar);
    shadow->shadow_me(client);

    npc_say("It was a pleasure helping you, " + player_name(client) +
	"! Now be careful and so long!");
    command("wave to " + CAP(client->query_real_name()));
    client = 0;
    set_alarm(3.0, 0.0, "command", "out");
}

string
slash_them_all()
{
    object *enemies = query_enemy(-1) & all_inventory(ENV());
    object victim;

    /* Should never be true. */
    if (!sizeof(enemies))
    {
	return "emote peers suspiciously at you.";
    }

    victim = ONE_OF_LIST(enemies);

    victim->heal_hp(victim->query_max_hp() / -4);

    victim->LCATCH_MSG("Suddenly ", " slashes you with " + POSSESSIVE(TO) +
	" scalpel, hitting a vein and hurting you badly.", TO);
    tell_watcher("Suddenly " + QTNAME(TO) + " slashes " + QTNAME(victim) +
	" with " + POSSESSIVE(TO) + " scalpel, hitting a vein and hurting " +
	OBJECTIVE(victim) + " badly.", victim);

    if (victim->query_hp() <= 0)
    {
	victim->do_die(TO);
    }

    return "say I am peaceful by nature. You forced me into this!";
}

object
query_client()
{
    return client;
}

/*
 * We are friendly for other domains... Solamnian knights may not kill her!
 */
int
query_knight_prestige()
{
    return -8;
}
