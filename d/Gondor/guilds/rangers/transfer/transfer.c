/*
 * /d/Gondor/common/guild/transfer.c
 *
 * This is the transfer room. An old Ranger will be sent here to be 
 * transfered to the new system to handle company decisions and changing
 * the shadow. It should never be removed, as people can be restored 
 * with the old shadow.
 *
 * Gwyneth, 2002
 * November, 2003--Tigerlily--updated scripts, exits, added
 *     apprentice routines
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/binbit.c";


#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "/d/Gondor/defs.h"

#define RANGER_I_CHOSE_ITHIL "_ranger_i_chose_ithil"
#define RANGER_I_CHOSE_NORTH "_ranger_i_chose_north"
#define RANGER_I_CHOSE_APPRENTICE "_ranger_i_chose_apprentice"
#define RANGER_I_CHOSE_ABANDON "_ranger_i_chose_abandon"


object trans_book;

int transfer_north();
int transfer_ithilien();
int abandon_hope();
int transfer_apprentice();
int transfer_ranger(object who, string company);

void
keep_log(object tp)
{
    string text = "";

    if (!objectp(tp))
        text += "Failed to log transfer!";
    else
    {
        text += CAP(tp->query_real_name());
        text += " - Hearing: " + tp->query_skill(SS_HEARING);
        text += ", Brawling: " + tp->query_skill(SS_BRAWLING);
        text += ", Reward: " + tp->query_skill(SS_REWARDED);
        text += ", Punish: " + tp->query_skill(SS_PUNISHED);
        text += ", Punishment: " + tp->query_skill(SS_PUNISHMENT);
        text += ", SpellList: " + tp->query_skill(SS_RANGER_SPELL_LIST);
        text += ", Disfavour: " + tp->query_skill(SS_RANGER_DISFAVOUR);
        text += ", Guild stat: " + tp->query_stat(SS_OCCUP);
        text += ", Master task: " + tp->query_skill(SS_MASTER_TASK);
    }

    MANAGER->rlog("rtransfer", text);
}

void
reset_room()
{
    if (!objectp(trans_book))
    {
        trans_book = clone_object(RANGERS_DIR + "transfer/transfer_book");
        trans_book->move(this_object(), 1);
    }
}

void
create_gondor()
{
    set_short("The Room of Decision");
    set_long("The walls and floor of this hideout " +
        "are rough granite, yet it is not without some amenities. " +
        "Some narrow bunks are built into the walls for " +
        "the comfort of those who need more time for deciding their " +
        "future. Torches set in sconces along the wall provide " +
        "light. There are four arched exits to tunnel passages " +
        "that are darkened with shadows. A makeshift wooden ladder " +
        "is propped against one wall connecting to another chamber " +
        "above.\n"); 
    add_prop(ROOM_M_NO_MAGIC, "Your magic fizzles out.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, "You cannot leave until you decide!\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, "You cannot go there.\n");
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);

    add_item(({ "bunk", "bunks", "narrow bunks", "amenities"}), 
        "The narrow bunks are built into the rock wall, and " +
        "are here for the comfort of those who " +
        "cannot decide on their path. Here they can rest without " +
        "forgetting their skills.\n");
    add_item(({"floor", "walls", "granite", "rough granite" }),
        "The walls and floor are rough natural granite, and " +
        "there are no windows. It is difficult to get your " +
        "bearings here, although you sense that the cave is " +
        "located somewhere in Anorien.\n");
    add_item(({"ladder", "makeshift ladder", "wooden ladder"}), 
        "A rough wooden ladder leads to another chamber " +
        "above.\n");
    add_item(({"passages", "tunnels", "tunnel passages",
        "arched exits", "exits", "passage", "tunnel" }),
        "The tunnels are darkened and obscured by shadows. " +
        "You will need to study the book to decide which path " +
        "to take.\n");
    add_item(({"chamber", "another chamber"}), "A small " +
        "chamber is lighted from above and is accessible " +
        "by a wooden ladder that leads up.\n");
    add_item(({"torches", "sconces", "light"}), "Light " +
        "is provided by torches placed in sconces.\n");
    add_item(({"shadow", "shadows"}),
        "The tunnels are obcured by shadows, and it is impossible " +
        "to determine where they lead.\n");

    add_exit(RANGERS_NOR_DIR + "n_drop_tun", "grey",
         &transfer_north(), 0, 1);
    add_exit(RANGERS_ITH_DIR + "i_drop_tun", "green",
        &transfer_ithilien(), 0, 1);
    add_exit(RANGERS_HQ_DIR + "start", "apprentice", 
        &transfer_apprentice(), 0, 1);
    add_exit(RANGERS_DIR + "transfer/transfer_post", "up", 0, 0);
    add_exit("/d/Gondor/anorien/nimrais/rimvalley4", "abandon",
        &abandon_hope(), 0, 1);

    reset_room();
}

int
transfer_apprentice()
{
    object tp = this_player();
    int level;
  
    if (tp->query_guild_name_occ() == RANGERS_GUILD_NAME)
    {
        tp->set_default_start_location(RANGERS_HQ_START);
        return 0;
    }

    if (!tp->query_is_ranger_pupil())
    {
        write("That path is only for pupils!\n");
        return 1;
    }
    if (!tp->query_prop(RANGER_I_CHOSE_APPRENTICE))
    {
        write("If you choose to become an " +
            "apprentice, you need to be aware " +
            "that there will be a time restriction " +
            "set on your apprenticeship. Read the " +
            "book for more information, then choose " +
            "<apprentice> again if you are sure.\n");
        tp->add_prop(RANGER_I_CHOSE_APPRENTICE, 1);
        return 1;
    }

    if (transfer_ranger(tp, "apprentice") == 1)
        return 0;
    else
        return 1;
}

int
transfer_north()
{
    object tp = this_player();

    if (tp->query_is_ranger_pupil())
    {
        write("You are not able to select this " +
            "tunnel, since you are not a full " +
            "ranger yet.\n");
        return 1;
    }

    if (!tp->query_prop(RANGER_I_CHOSE_NORTH))
    {
        write("If you have read the book, " +
            "searched your heart and are " +
            "sure of your decision, try again.\n");
        tp->add_prop(RANGER_I_CHOSE_NORTH, 1);
        return 1;
    }

    if (transfer_ranger(tp, "north") == 1)
        return 0;
    else
        return 1;
}

int
transfer_ithilien()
{
    object tp = this_player();

    if (tp->query_is_ranger_pupil())
    {
        write("You are not able to select this " +
            "tunnel, since you are not a full " +
            "ranger yet.\n");
        return 1;
    }

    if (!tp->query_prop(RANGER_I_CHOSE_ITHIL))
    {
        write("If you have read the book, " +
            "searched your heart and are " +
            "sure of your decision, try again.\n");
        tp->add_prop(RANGER_I_CHOSE_ITHIL, 1);
        return 1;
    }

    if (transfer_ranger(tp, "ithilien") == 1)
        return 0;
    else
        return 1;
}

int
transfer_ranger(object who, string company)
{
    int ret_val;
    object rshadow, book;

    keep_log(who);

    /* Remove the transfer shadow. */
    who->remove_transfer_shadow();

    /* Clone the new shadow. */
    rshadow = clone_object(RANGERS_SHADOW);
    ret_val = rshadow->shadow_me(who, "occupational", RANGERS_STYLE,
        RANGERS_GUILD_NAME);

    /* Did it work? */
    switch(ret_val)
    {
    case 1:
        if (company == "apprentice")
        {
            write("You enter the shadowy tunnel marked " +
            "Apprentice and return to the headquarters of the " +
            "Rangers of the Westlands. It is good to be home.\n");
            say(QCTNAME(who) + " returns home through the " +
                "tunnel marked Apprentice.\n");
        }
        else
        {
            write("You choose your path and step through the door to join " +
                "the " + capitalize(company) + " company.\n");
            say(QCTNAME(who) + " chooses " + who->query_possessive() +
                " path, stepping through the door marked " + 
                capitalize(company) + ".\n");
        }
        
        /* remove temporary transfer_shadow */
        who->remove_transfer_shadow();
        /* remove cmdsoul too? */
        who->remove_cmd_soul("/d/Gondor/common/guild/rangers_soul");

        /* Make him/her a company ranger, overiding apprentice checks. */

        MANAGER->add_ranger(who->query_real_name(), company, 1);
        MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(who->query_real_name()) + 
            " transfered from the old Ranger shadow and joined the " + 
            capitalize(company) + " company.");

        if (company == "north")
        {
            clone_object(RANGERS_OBJ + "grey_cloak")->move(who, 1);
            write("As you step through the door, a dark-grey cloak " +
                "falls into your hands.\n");
            who->set_default_start_location(RANGERS_NOR_DIR + "start");
        }
        else if (company == "ithilien")
        {
            clone_object(RANGERS_OBJ + "green_cloak")->move(who, 1);
            write("As you step through the door, a dark-green cloak " +
                "falls into your hands.\n");
            who->set_default_start_location(RANGERS_ITH_DIR + "start");
        }
        else
        {
            clone_object(RANGERS_OBJ + "brown_cloak")->move(who, 1);
            write("As you step through the door, a dark-brown cloak " +
                "falls into your hands.\n");
            who->set_default_start_location(RANGERS_HQ_START);
        }

/*
        book = present("ranger_spell_book", who);
        if (objectp(book))
        {
            book->remove_object();
        }
        clone_object(RANGERS_SPELL + "spellbook")->move(who, 1);
*/

        who->remove_prop(RANGER_I_CHOSE_ITHIL);
        who->remove_prop(RANGER_I_CHOSE_NORTH);
        who->remove_prop(RANGER_I_CHOSE_APPRENTICE);
        set_bin_bits(1, 18, 2, who, 0);
        set_bin_bits(1, 16, 2, who, 0);
        who->set_ranger_incognito(1);
        return 1;
    case -4:
        /* This shouldn't usually happen unless perhaps an old Ranger/Thief
           is restored, but then that should be dealt with before he/she
           joins again. */
        write("Your other guilds prohibit you from joining this one! " +
            "From here, mail 'gondor' or contact an immortal for help!\n");
        MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(who->query_real_name()) + 
            " tried to transfer to the guild, but couldn't due to " +
            "conflicting guilds.");
        return 0;
        break;
    default:
        write("You were unable to enter the Rangers due to " +
            "a problem in the fabric of space. From here, 'mail gondor' " +
            "or contact an immortal for help!\n");
        MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(who->query_real_name()) + 
            " tried to transfer to the guild, but couldn't due to an error.");
         return 0;
        break;
    }

    /* We couldn't shadow the player, so remove the shadow object */
    rshadow->remove_shadow();
    return 0;
}

int
abandon_hope()
{
    object token, spellbook, tp = this_player();


    if (!tp->query_prop(RANGER_I_CHOSE_ABANDON))
    {
        write("Are you sure you want to abandon hope? " +
            "If so, try again.\n");
        tp->add_prop(RANGER_I_CHOSE_ABANDON, 1);
        return 1;
    }

    keep_log(tp);

// remove shadow, etc., resets bits and skills
// reset start location
 
    tp->remove_skill(SS_HEARING);
    tp->remove_skill(SS_BRAWLING);
    tp->remove_skill(SS_REWARDED);
    tp->remove_skill(SS_PUNISHED);
    tp->remove_skill(SS_PUNISHMENT);
    tp->remove_skill(SS_RANGER_SPELL_LIST);
    tp->remove_skill(SS_RANGER_DISFAVOUR);
    tp->remove_skill(SS_MASTER_TASK);

    set_bin_bits(1, 18, 2, tp, 0);
    set_bin_bits(1, 16, 2, tp, 0);

    tp->remove_transfer_shadow();
    tp->set_default_start_location(tp->query_def_start());
    tp->clear_guild_stat(SS_OCCUP);

    if (objectp(spellbook = present("ranger_spell_book", tp)))
        spellbook->remove_object();

    if (objectp(token = present("ranger_guild_object", tp)))
    {
        tell_object(tp, "A white pigeon comes flying, and takes " +
            "your " + token->short() + " in its beak.\nThe white " +
            "pigeon flies away with it.\n");
        token->remove_object();
    }

    tp->remove_prop(RANGER_I_CHOSE_ABANDON);
    return 0;
}

