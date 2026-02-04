/* Chatting monster */
/* Soprano.c, Azireon, Setember 20, 1992 
 * Dedicated humorously to another disliker of soprani--
 * Serena Jost */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"

create_monster()
{
    if (IS_CLONE) {
    set_name("Soprano");
    add_name("woman");
    add_name("soprano");
    set_gender(1);
    set_short("Deranged Woman");
    set_long(break_string(
        "Reeking of mildew and urine, this deranged woman is " +
        "immediately repulsive.  It looks like she has pulled out most " +
        "of her hair but that which remains is yellowing gray and " +
        "stands on end.  She is attired in the soiled remains of what " +
        "must originally have been a beautiful red evening gown.\n", 70));

    set_chat_time(5);
    add_chat(break_string(
        "Why are you never on time?!  That is the trouble with " +
        "you people--laziness!", 60) );
    add_chat(break_string(
        "Don't you dare think that I don't know that you know what " +
        "she knows about what I know they know about me!", 60) );
    add_chat(break_string(
        "Maybe it's just me but I don't like the sound of her " +
        "voice...not to mention her personality...", 60) );
    add_chat("Be quiet when I'm singing!");
    add_chat("Helloooooo!  Is anyone here?");
    add_chat("Would you be a dear and bring me some tea?");
    add_chat("Where is my accompanist?!");
    add_chat(break_string(
        "I don't think you or anyone else around here appreciates " +
        "how much effort and time I have invested in this...", 60) );

    set_cchat_time(3);
    add_cchat("Hi-yah-tuh-ho-oh!  Hi-yah-tuh-ho-oh!\n");
    add_cchat("I still have a high C!\n");

    set_cact_time(5);
    add_cact( ({ "snarl", "growl" }) );

    set_act_time(10);
    add_act("@@hand");
    add_act("@@sing");
    add_act("@@laugh");
    add_act("despair");
    add_act("@@drink");

    set_all_hitloc_unarmed(20);
    set_stats(({ 40, 20, 20, 35, 40, 15 }));
    set_alignment(400);
    set_hp(4000);
    set_exp(10);
    set_skill(SS_DEFENCE, 75);
    default_config_mobile(7);

    trig_new("%s 'bows' %s", "curtsey");
    trig_new("%s 'curtseys' %s", "curtsey");
    trig_new("%s 'applaud' %s", "curtsey");
    trig_new("%s 'claps' %s", "hand");
    }
}

curtsey(str1, str2)
{
    command("say Charmed, " + str1 + ".");
    command("curtsey");
}

hand()
{
    write("The deranged woman extends her smelly hand to you.\n");
    write("She obviously expects you to kiss it.\n");
    command("say The pleasure is all mine!");
    return;
}

drink()
{
    write("The deranged woman walks to the edge of the stage.\n");
    write("To your disbelief, she bends down and drinks from\n");
    write("the pool of fetid water.\n");
    command("say Would you like some?");
    return;
}

sing()
{
    command("say I will now consent to sing for you...");
    write("The deranged woman begins to caterwaul incomprehensibly.\n");
    write("There seems to be no way to make her stop.\n");
    return;
}

laugh()
{
    command("say Aren't you charming, darling?");
    write("The deranged woman laughs in a loud, affected manner.\n");
    return;
}
