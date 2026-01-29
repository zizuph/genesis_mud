#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include <composite.h>
inherit "/std/object";

int main_alarm;
object lead_singer,
       *mounties;

public void sing_chorus(int index);
public varargs void main_verse(object who, int index, int do_sing_chorus = 1);
public void
create_object()
{
    set_name("singer");
    add_name("_lumberjack_singer");
    set_short("The lumberjack singer");
    set_long("This is the lumberjack song object!\n");
    set_no_show();
    mounties = ({});
}

public void
sing_chorus(int index)
{
    string verse;
    string extra;

    extra = lead_singer->query_pronoun();

    if (index == 5 || index == 7 || index == 9)
    {
        verse = "Oh " + extra + "'s a lumberjack and " + extra +
            "'s ok, " + extra + " sleeps all night and " + extra +
            " works all day!\n";
    }
    else if (index == 6)
    {
        verse = capitalize(extra) + " cuts down trees, " + extra +
            " eats " + lead_singer->query_possessive() + " lunch, " +
            extra + " goes to the lavatree. On Wednesday's " + extra +
            " goes shopping, and has buttered scones for tea!\n";
    }
    else if (index == 8)
    {
        verse = capitalize(extra) + " cuts down trees, " + extra +
            " skips and jumps, " + extra + " likes to press wild  "+
            " flowers. " + capitalize(extra) + " puts on women's " +
            " clothing, and hangs...around in bars????\n";
    }
    else if (index == 10)
    {
        verse = capitalize(extra) + " cuts down trees, " + extra +
            "wear high heels, suspenders and a...bra???\n";
    }

    if (sizeof(mounties))
    {
        tell_room(environment(lead_singer), COMPOSITE_LIVE(mounties) +
            " sing: " + verse);
        if (index == 10)
        {
            tell_room(environment(lead_singer),
                QCTNAME(mounties[random(sizeof(mounties))]) + " says: " +
               "What's this?\n");
            tell_room(environment(lead_singer),
               QCTNAME(mounties[random(sizeof(mounties))]) + " says: " +
                "Wants to be a _girlie_!?!?\n");
            tell_room(environment(lead_singer),
               QCTNAME(mounties[random(sizeof(mounties))]) + " gags.\n");
            tell_room(environment(lead_singer),
                QCTNAME(mounties[random(sizeof(mounties))]) + " says: " +
                "And I thought you were so rugged!\n");
            tell_room(environment(lead_singer),
                QCTNAME(mounties[random(sizeof(mounties))]) + " says: " +
               "Bloody poufter!\n");
            return;
        }
    }
    main_alarm = set_alarm(5.0, 0.0, &main_verse(lead_singer, index+1, 1));    
}

public varargs void
main_verse(object who, int index, int do_sing_chorus = 1)
{
    string verse;

    if (!index)
    {
        tell_object(who, "You mutter: I...I always wanted to be...\n");
        tell_room(environment(who), QCTNAME(who) + " mutters: " +
            "I...I always wanted to be...\n", who);
    }
 
    else if (index == 1)
    {
        tell_object(who, "You exclaim: A lumberjack!\n");
        tell_room(environment(who), QCTNAME(who) + " exclaims: " +
            "A lumberjack!\n", who);
        tell_room(environment(who), "Suddenly you hear a piano " +
            "playing....\n");
    }

    else if (index == 2)
        verse = "Leaping from tree to tree! As they float down the " +
            "mighty rivers of British Columbia!\n";

    else if (index == 3)
        verse = "The larch! The Pine! The Giant Redwood!\n"; 

    else if (index == 4)
        verse = "With my best girl by my side! We'd sing! Sing! " +
            "Sing...\n";

    else if (index == 5 || index == 7 || index == 9 || index == 11)
        verse = "Oh, I'm a lumberjack and I'm ok, I sleep all night " +
            "and I work all day!\n";

    else if (index == 6)
        verse = "I cut down trees, I eat my lunch, I go to the " +
            "lavatree. On Wednesdays I go shoppin', and have " +
            "buttered scones for tea!\n";

    else if (index == 8)
        verse = "I cut down trees, I skip and jump, I like to " +
            "press wild flowers. I put on women's clothing, and " +
            "hang around in bars!\n";

    else if (index == 10)
        verse = "I chop down trees, I wear high heels, suspenders " +
            "and a bra. I wish I'd been a girlie, just like my " +
            "dear papa!\n";

    if (index > 1 && index < 5)
    {
        tell_room(who, "You exclaim: " + verse);
        tell_room(environment(who), QCTNAME(who) + " exclaims: " +
            verse, who);
    }
    else if (index > 1)
    {
        tell_object(who, "You sing: " + verse);
        tell_room(environment(who), QCTNAME(who) + " sings: " +
            verse, who);
    }

    if (index == 11)
    {
        tell_object(who, "Done singing.\n");
        return;
    }

    if (index >= 5 && do_sing_chorus)
        main_alarm = set_alarm(5.0, 0.0, &sing_chorus(index));
    else
        main_alarm = set_alarm(5.0, 0.0, &main_verse(who, index+1));
}

public void
start_singing(object who)
{
    lead_singer = who;

    who->command("say I...I never wanted to be a wizard.");
    if (get_alarm(main_alarm))
        return;
    main_alarm = set_alarm(2.0, 0.0, &main_verse(who, 0));
}

public void
stop_singing(object who)
{
    if (who == lead_singer)
    {
        tell_object(who, "You decide enough's enough and stop singing.\n");
        tell_room(environment(who), QCTNAME(who) + " decides enough's " +
            "enough and stops singing.\n", who);
        remove_object();
    }
    else if (member_array(who, mounties) > -1)
    {
        tell_object(who, "You decided you've had enough of this " +
            "foolishness and stop singing.\n");
        tell_room(environment(who), QCTNAME(who) + " decides he's had " +
            "enough of this foolishness and stops singing.\n");
        mounties -= ({who});
    }
}

public void
add_singer(object who)
{
    if (member_array(who, mounties) > -1)
    {
        tell_object(who, "You're already singing, you malodorous pervert!\n");
        return;
    }
    else
    {
        who->catch_msg("Unable to resist the silliness, you join " +
            QTNAME(lead_singer) + " in a rousing rendition of the " +
            "Lumberjack Song!\n");
        tell_room(environment(who), "Unable to resist the silliness, " +
            QTNAME(who) + " joins " + QTNAME(lead_singer) + " in a " +
            "rousing rendition of the Lumberjack Song!\n");
        mounties += ({who});
    }
}

public void
add_mountie(string str)
{
    add_singer(find_player(str));
}

public void
add_lumberjack(string str)
{
    start_singing(find_player(str));
}
