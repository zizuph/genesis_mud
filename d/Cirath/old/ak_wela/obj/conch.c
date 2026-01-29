inherit "/std/object";
#include "/d/Cirath/common/defs.h"
#define ERASE_COST 15 // Mana cost to blank out a message
#define LISTEN_COST 2 // Mana cost to listen to a message

// Not implemented yet.
#define RECORD_FACTOR 2 // # of chars you can record per mana point

#define UNINTENDED_DIFF -25
#define SAME_RACE_DIFF 20

#define KNOW_ALL 90
#define KNOW_SEX 60
#define KNOW_RACE 40

string record_who, message, race;
int intended, gender;

string
id_voice(object who)
{
    int difficulty = 0;

    if (!intended)
        difficulty += UNINTENDED_DIFF;
    if (TP->query_race() == race)
        difficulty += SAME_RACE_DIFF;
    if (TP->query_stat() + difficulty >= KNOW_ALL)
        if (TP-> /* 'met' record_who */)
            return capitalize(LANG_POSS(record_who));
        else return "a " + (gender == G_FEMALE) ? "female " : "male " +
                    LANG_POSS(race);
    else if (TP->query_stat() + difficulty >= KNOW_SEX)
        return "a " + (gender == G_FEMALE) ? "female " : "male " +
               LANG_POSS(race);
    else if (TP->query_stat() + difficulty >= KNOW_RACE)
        return LANG_ADDART(LANG_POSS(race));
    else return "";
}

int
listen(string what)
{
    string sound;

    if (!id(what))
    {
        notify_fail("Listen to what?\n");
        return 0;
    }
    if (ETO != TP)
    {
        notify_fail("You have to hold it to get it that close to your ear!\n");
        return 0;
    }
    if (TP->query_mana() < LISTEN_COST)
    {
        TP->catch_msg("You strain desperately to hear anything, " +
            "but find yourself listening to only a faint hiss.\n");
        TP->set_mana(0);
        return 1;
    }
    else TP->set_mana(TP->query_mana() - LISTEN_COST);

    sound = "You hear the roar of the mighty ocean pounding against " +
            "the shore.";
    if (strlen(message))
    {
        if (intended)
        {
            sound += "  Calling out loud and clear above the noise of " +
                     "the crashing waves, you hear " + id_voice(TP) +
                     " voice:\n" + message + ".\n";
        }
        else
        {
            sound += "  Faintly, you hear " + id_voice(TP) + " in the background, " +
                     "almost drowned out by the sound of the waves.  " +
                     (gender == G_FEMALE ? "She " : "He ") + "seems to " +
                     "be saying: " + message + ".\n";
        }
    }
    else if (TP->query_stat(SS_INT) > 40)
    {
        sound += "  You know that it is simply a natural illusion, an echo " +
                 "of many small noises picked up and amplified by the " +
                 "shell cavity";
        if (TP->query_stat(SS_WIS) > 75 || TP->query_skill(SS_AWARENESS) > 50)
            sound += ", but it sounds so real that you wonder if there " +
                     "might not be more to this shell than meets the ear";
        sound += ".\n";
    }
    else if (TP->query_stat(SS_WIS) > 75 || TP->query_skill(SS_AWARENESS) > 50)
        sound += "  The sound is so real and lifelike that you realize " +
                 "there must be something very special indeed about this " +
                 "beautiful conch shell.\n";
    TP->catch_msg(sound);
    return 1;

}

varargs int
erase(string what)
{
    if (!TP || !objectp(TP))
    {
        record_who = message = race = "";
        intended = gender = 0;
        return 1;
    }
    else if (what != "recording" && what != "message")
    {
        notify_fail(query_verb() + " what?\n");
        return 0;
    }
    else if (TP->query_mana() < ERASE_COST)
    {
        TP->catch_msg("You try in vain to will the shell to forget " +
           "its message, and the effort leaves you exhausted.\n");
        TP->set_mana(0);
        return 0;
    }
    else
    {
        TP->catch_msg("You concentrate intently on nothing at all, " +
                           "and then direct the thought at the shell.  The " +
                           "sense of order within the shell disappears as " +
                           "you relax.\n");
        TP->set_mana(TP->query_mana() - ERASE_COST);
        return 1;
    }
}

int
record(string what)
{
    if (query_verb() != "record")
    {
        if (parse_command(what, ({ TO }),
                          " 'into' / 'to' 'conch' / 'shell' %s ", message))
        {
            intended = 1;
            gender = TP->query_gender();
            race = TP->query_race();
            record_who = TP->query_real_name();
            return 1;
        }
        else // Might have something left in it from parse_command
        {
            message = "";
            return 0;
        }
    }
    else
    {
        message = what;
        intended = 1;
        gender = TP->query_gender();
        race = TP->query_race();
        record_who = TP->query_real_name();
    }
    return 1;
}

void
init()
{
    ::init();

    add_action(listen, "listen");
    add_action(erase, "erase");
    add_action(erase, "forget");
    add_action(erase, "delete");
    add_action(record, "record");
    add_action(record, "speak");
    add_action(record, "talk");
}

void
create_object()
{
    set_name("shell");
    add_name("conch");
    add_name("seashell");

    set_adj("large");
    add_adj("pink");
    add_adj("beautiful");
    set_short("large pink conch shell");
    set_long("This large of a shell is a rare find, especially just " +
             "washed up on a beach.  It is probably quite valuable.  " +
             "Legends say that if you listen to a conch shell, you " +
             "can hear the sound of the ocean.\n");

    set_alarm(1.0, 0.0, "erase");

    add_prop(OBJ_I_VALUE, 720);
    add_prop(MAGIC_AM_MAGIC, ({ 24, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO, ({ 2, "This shell is magical.\n" }) );
}

