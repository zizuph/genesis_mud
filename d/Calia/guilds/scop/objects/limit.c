
/* Action/speech limiter
 * for use by the Spirit Circle of Psuchae guild members.
 * This will limit speech commands plus some actions that
 * would look funny for a person to do with no tongue.
 *
 * Original code by Maniac (drown object in Calian sea)
 *
 */

#pragma save_binary

inherit "/std/object";
inherit "/cmd/std/command_driver";
#include <stdproperties.h>
#include <ss_types.h> 
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"

void
create_object()
{
    set_short("_action_limiter_");
    set_long("_action_limiter_");
    set_name("_action_limiter_");
    add_name("_spirit_action_limiter_");
    add_name("limiter");
    set_no_show();
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_M_NO_INS, 1);
}


void
enter_env(object to, object from)
{
    object player;

    ::enter_env(to, from);

    if (living(to)) {
        seteuid(getuid()); 
        player = to;
    }
    else { 
        remove_object();
        return;
    } 

}

public int
banned_emote(string str)
{
    write("You cannot do this emote without a tongue.\n");
    return 1;
}

public int
communicate(string str = "")
{

    /* Doesn't the ''' look cute? It is the fastest ;-) */
    if (query_verb()[0] == ''')
    {
        str = extract(query_verb(), 1) + " " + str;
    }

    write("You cannot speak with no tongue!\n");
    return 1;
}

int
ack(string str)
{
    write("You try to make an ack sound, but cannot with no tongue.\n");
    return 1;
}

int
agree(string str)
{
    object *oblist, tp;
    string qp;

    tp = TP;
    qp = tp->query_possessive();

    if (!stringp(str)) {
        write("You nod your head in agreement.\n");
        allbb(" nods " + qp + " head in agreement.");
        return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
        write("Agree with whom?\n");
        return 1;
    }

    targetbb(" nods " + qp + " head in agreement at you.", oblist);
    actor("You nod your head in agreement at", oblist);
    all2actbb(" nods " + qp + " head in agreement at", oblist);
    return 1;
}


/* Give someone an apologetic look. */
int
apologize(string str)
{
    object *oblist, tp;

    if (!stringp(str)) {
        write("You look apologetic.\n");
        allbb(" looks apologetic.");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        write("Give whom an apologetic look?\n");
        return 1;
    }

    targetbb(" gives you an apologetic look.", oblist);
    actor("You give", oblist, " an apologetic look.");
    all2actbb(" gives", oblist, " an apologetic look.");
    return 1;
}

int
beg(string str)
{
    object *oblist;
    object tp = this_player();
    string pn = tp->query_pronoun();


    if (!stringp(str)) { 
        write("Beg whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l [pardon] [forgiveness]");

    if (!sizeof(oblist)) {
        write("Beg whom?\n");
        return 1;
    }

    target(" looks like "+ pn + " is begging to you.", oblist);
    actor("You beg to", oblist, ".");
    all2act(" looks like "+pn+" is begging to ", oblist, ".");
    return 1;
}

int
cheer(string str)
{
    write("You cannot cheer with no tongue.\n");
    return 1;
}

int
chuckle()
{
    write("You give a muffled chuckle.\n");
    all(" gives a muffled chuckle.");
    return 1;
}

int
complain(string str)
{
    write("You cannot complain with no tongue.\n");
    return 1;
}

int
compliment(string str)
{
    object *oblist;
    
    if (!stringp(str)) {
        write("Compliment whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Compliment whom?\n");
        return 1;
    }

    targetbb(" nods " + this_player()->query_possessive() +
        " head at you in complimentary fashion.", oblist);
    actor("You nod your head at", oblist, " in complimentary fashion.");
    all2actbb(" nods " + this_player()->query_possessive() +
        " head at", oblist, " in complimentary fashion.");
    return 1;
}

int
congrat(string str)
{
    object *oblist;
    
    if (!stringp(str)) {
        write("Congratulate whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Congratulate whom?\n");
        return 1;
    }

    targetbb(" gives you a look of approval.", oblist);
    actor("You give", oblist, " a look of approval.");
    all2actbb(" gives", oblist, " a look of approval.");
    return 1;
}

int
congratulate(string str)
{
    object *oblist;
    
    if (!stringp(str)) {
        write("Congratulate whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Congratulate whom?\n");
        return 1;
    }

    targetbb(" gives you a look of approval.", oblist);
    actor("You give", oblist, " a look of approval.");
    all2actbb(" gives", oblist, " a look of approval.");
    return 1;
}

int
converse()
{
    write("You may not converse without a tongue.\n");
    return 1;
}

int
curse()
{
    write("You may not curse without a tongue.\n");
    return 1;
}

int
disagree(string str)
{
    object *oblist;
    object tp = this_player();

    if (!stringp(str))
    {
        write("You shake your head in disagreement.\n");
        allbb(" shakes " + tp->query_possessive() + " head in disagreement.");
        return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
        write("Disagree with whom?\n");
        return 1;
    }

    targetbb(" shakes " + tp->query_possessive() + " head at you " +
            "in disagreement.", oblist);
    actor("You shake your head at", oblist, " in disagreement.");
    all2actbb(" shakes " + tp->query_possessive() + " head at", oblist, 
              " in disagreement.");
    return 1;
}

int
duh(string str)
{
    object *oblist;
    object tp = this_player();

    if (!stringp(str))
    {
        write("You knock on your head.\n");
        all(" knocks on " + tp->query_possessive() + " head.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist)) {
        write("Duh at whom?\n");
        return 1;
    }

    if (sizeof(oblist) == 1)
        str = "head";
    else
        str = "heads";

    target(" knocks on your head.", oblist);
    actor("You knock on the " + str + " of", oblist);
    all2actbb(" knocks on the " + str + " of", oblist);
    return 1;
}

int
eeks()
{
    write("Yout cannot go 'eek' with no tongue.\n");
    return 1;
}

int
forgive(string str)
{
    object *oblist;
    object tp = this_player();

    if (!stringp(str))
    {
        write("Give a look of forgiveness to whom?.\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Give a look of forgiveness to whom?\n");
        return 1;
    }

    targetbb(" gives you a look of forgiveness.", oblist);
    actor("You give a look of forgiveness to", oblist, ".");
    all2actbb(" gives a look of forgiveness to", oblist,".");
    return 1;
}

int
french()
{
    write("You cannot french kiss anyone without a tongue.\n");
    return 1;
}

int
giggle()
{
    write("You cannot giggle without a tongue.\n");
    return 1;
}

int
grovel(string str)
{
    object *oblist;

    if (!stringp(str)) {
        write("Grovel in front of whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[to] / [for] / [before] [the] %l");

    if (!sizeof(oblist))
    {
        write("Grovel in front of whom?\n");
        return 1;
    }

    target(" falls to the ground and grovels silently to you.", 
           oblist);
    actor("You fall to the ground in front of", oblist, 
          ", grovelling silently.");
    all2act(" falls to the ground in front of", oblist, 
            ", grovelling silently.");
    return 1;
}

int
hum()
{
    write("You hum an eerie tune.\n");
    all(" hums an eerie tune.");
    return 1;
}

public int
do_intro(string str)
{
    int size, index;
    object *oblist, *targets, *others = ({}), *knows_member = ({}),
           *known_by_member = ({});
    string title, arg;
 
    oblist = FILTER_OTHER_LIVE(all_inventory(environment(TP)));
 
    if (!sizeof(oblist))
    {
        NF("Introduce yourself to whom?\n");
        return 0;
    }

    else if (!strlen(str) || str == "me" || str == "myself")
    {
        targets = oblist;
        others = ({});
    }

    else
    {
        targets = parse_this(str, "[me] [myself] [to] [the] %l");
 
        if (!sizeof(targets))
        {
            NF("Introduce yourself to whom?\n");
            return 0;
        }
 
        others = (oblist - targets);
    }
 
    for (index = 0, size = sizeof(targets); index < size; index++)
    {
        if (TP->query_met(targets[index]->query_real_name()))
            known_by_member += ({ targets[index] });
        if (targets[index]->query_met(TP->query_real_name()) &&
          !targets[index]->query_npc())
            knows_member += ({ targets[index] });
    }

    title = capitalize(TP->query_real_name()) + " " +
        TP->query_title();

    TP->reveal_me(1);
        
    for (index = 0; index < sizeof(others) ; index++)
    {
        others[index]->catch_tell(TP->query_The_name(others[index]) + 
            " nods " + TP->query_possessive() + " head towards " + 
            FO_COMPOSITE_LIVE(targets, others[index]) + ".\n");
    }
     
    say("You suddenly feel the presence of "+QTNAME(TP)+
        " entering your mind, revealing "+TP->query_possessive()+
        " identity as " + title + ".\n", others + ({ TP }));
    write("You telepathically reveal your identity to " +
        COMPOSITE_LIVE(targets) + ".\n");
 
    targets -= knows_member;
 
    for (index = 0, size = sizeof(targets); index < size; index++)
    {
        targets[index]->add_introduced(TP->query_real_name());
    }
    return 1;
}

int
laugh(string str)
{
    write("You cannot laugh without a tongue.\n");    
    return 1;
}

int
lick(string str)
{
    write("You cannot lick without a tongue.\n");    
    return 1;
}


int
love(string str)
{
    object *oblist;

    if (!stringp(str)) {
        write("Love whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Love whom?\n");
        return 1;
    }

    target(" looks lovingly at you.", oblist);
    actor("You look lovingly at", oblist);
    all2act(" looks lovingly at", oblist);

    return 1;
}

int
mumble()
{
    write("You cannot mumble without a tongue.\n");
    return 1;
}

int
ponder()
{
    write("You ponder the situation.\n");
    all(" ponders the situation.");
    return 1;
}

int
roar(string str)
{
    write("You cannot roar without a tongue!\n");
    return 1;
}

int
scold(string str)
{
    object *oblist;

    if (!stringp(str))
    {
        write("Scold whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Scold whom?\n");
        return 1;
    }

    target(" waggles an irate finger at you!", oblist);
    actor("You waggle an irate finger at", oblist);
    all2act(" waggles an irate finger at", oblist);
    return 1;
}

int
scream(string str)
{
    write("You give a look like you want to scream.\n");
    allbb(" looks like "+TP->query_pronoun()+" wants to scream.");
    return 1;
}

int
sing()
{
    write("You cannot sing without a tongue.\n");
    return 1;
}

int
stick()
{
    write("You try to stick your tongue out but realize you don't have one!\n");
    allbb(" tries to stick "+TP->query_possessive()+" tongue out but then "+
        "realizes "+TP->query_pronoun()+" doesn't have one!");
    return 1;
}
int
think()
{
    write("You try to look thoughtful, but fail.\n");
    all(" tries to look thoughtful, but fails.");
    return 1;
}

int
thank(string str)
{
    object *oblist;
    object tp = this_player();

    if (!stringp(str))
    {
        write("Thank whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
        write("Thank whom?\n");
        return 1;
    }

    targetbb(" gives you a look of thanks.", oblist);
    actor("You give", oblist, " a look of thanks.");
    all2actbb(" gives", oblist," a look of thanks.");
    return 1;
}

int
swear()
{
    write("You cannot swear without a tongue.\n");
    return 1;
}

int
whine(string str)
{
    object *oblist;

    if (!stringp(str))
    {
        write("You look ready to whine but are frustrated by having no " +
             "tongue.\n");
        allbb(" looks ready to whine but is frustrated by the fact that " +
             TP->query_pronoun()+" has no tongue.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Whine at whom?\n");
        return 1;
    }

    targetbb(" looks ready to whine at you but is frustrated by the " +
            "fact that "+TP->query_pronoun()+" has no tongue.", oblist);
    actor("You look ready to whine at", oblist, " but are frustrated " +
          "by having no tongue.");
    all2actbb(" looks ready to whine at", oblist, " but is frustrated by " +
              "the fact that "+TP->query_pronoun()+" has no tongue.");
    return 1;
}

int
yodel(string str)
{
    write("You cannot yodel without a tongue.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(communicate, "ask");
    add_action(communicate, "rsay"); 
    add_action(communicate, "shout");  
    add_action(communicate, "'", 1);
    add_action(communicate, "signal");
    add_action(communicate, "say");
    add_action(communicate, "tsay");
    add_action(communicate, "dsay");
    add_action(communicate, "whisper");
    add_action(communicate, "egsay");
    add_action(communicate, "asay");

    add_action(banned_emote, "niclasp1");
    add_action(banned_emote, "niclasp2");
    add_action(banned_emote, "niwarcry");
    add_action(banned_emote, "nocall");
    add_action(banned_emote, "nodismiss");
    add_action(banned_emote, "nofarewell");
    add_action(banned_emote, "nohymn");
    add_action(banned_emote, "nooath");
    add_action(banned_emote, "notale");
    add_action(banned_emote, "eache");
    add_action(banned_emote, "stpause");
    add_action(banned_emote, "stbid");
    add_action(banned_emote, "egdistrust");
    add_action(banned_emote, "eggiggle");
    add_action(banned_emote, "eggreet");
    add_action(banned_emote, "eglaugh");
    add_action(banned_emote, "egsing1");
    add_action(banned_emote, "egsing2");
    add_action(banned_emote, "egwarcry");
    add_action(banned_emote, "egpray");
    add_action(banned_emote, "gcfrench");
    add_action(banned_emote, "gcwarn");
    add_action(banned_emote, "lclove");
    add_action(banned_emote, "gclove");
    add_action(banned_emote, "lcwarn");
    add_action(banned_emote, "wcompliment");
    add_action(banned_emote, "whail");
    add_action(banned_emote, "wnotice");
    add_action(banned_emote, "wrejoice");

    add_action(ack, "ack"); 
    add_action(agree, "agree"); 
    add_action(apologize, "apologize"); 
    add_action(beg, "beg"); 
    add_action(cheer, "cheer");  
    add_action(chuckle, "chuckle"); 
    add_action(complain, "complain"); 
    add_action(compliment, "compliment");
    add_action(congrat, "congrat");
    add_action(congratulate, "congratulate");
    add_action(converse, "converse");
    add_action(curse, "curse");
    add_action(disagree, "disagree"); 
    add_action(duh, "duh");   
    add_action(eeks, "eeks"); 
    add_action(french, "french");
    add_action(forgive, "forgive");
    add_action(giggle, "giggle"); 
    add_action(grovel, "grovel"); 
    add_action(hum, "hum");
    add_action(do_intro, "introduce");
    add_action(laugh, "laugh");
    add_action(lick, "lick");
    add_action(love, "love"); 
    add_action(mumble, "mumble");
    add_action(ponder, "ponder");
    add_action(roar, "roar"); 
    add_action(scold, "scold");   
    add_action(scream, "scream"); 
    add_action(sing, "sing");
    add_action(stick, "stick");
    add_action(swear, "swear");
    add_action(thank, "thank");
    add_action(think, "think");
    add_action(whine, "whine"); 
    add_action(yodel, "yodel");
}

