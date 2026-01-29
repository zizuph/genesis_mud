/* This is what you've all been waiting for... the infamous Grunts soul!  */
/* With a bit of luck it will give Goblins the important position of      */
/* being the most disgusting, foul race on the face of Genesis.           */
/* This soul was based on the work of others - Tricky, Quis, Nick et al.  */
/* The original soul was developed by Tulix I, 29/3/1993.                 */
/* Recoded 11/08/95 with various improvements, Tulix III.                 */
/* Used it as a base for a wedding soul. Rohim                            */
/* Credits to Melita, Jade and Ladindell for help and inspiration         */

inherit "/cmd/std/command_driver";

#include <filter_funs.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>
#include <options.h>
#include <std.h>
#include "chapel.h"

/*
 * Prototypes
 */
public object is_my_spouse_here();
public string get_genitive_s(object target, object watcher);

/* ************************************************************************
 * Return the proper name of the soul in order to get a nice printout.
 */
public string
get_soul_id()
{
    return GUILD_SOUL_ID;
}

/* ************************************************************************
 * This is a command soul.
 */
public int
query_cmd_soul()
{
   return 1;
}

/* ************************************************************************
 * The list of commands. Please add new ones in alphabetical order.
 */
public mapping
query_cmdlist()
{
   return (["spbehind"     : "behind",
            "spembrace"    : "embrace",
            "spentwine"    : "entwine",
            "spgaze"       : "gaze",
            "spglower"     : "glower",
            "sphelp"       : "help",
            "help"         : "help",
            "sphair"       : "hair",
            "sphug"        : "hug",
            "spkneel"      : "kneel",
            "splap"        : "lap",
            "splust"       : "lust",
            "sppledge"     : "pledge",
            "spprotect"    : "protect",
            "sprotate"     : "rotate",
            "spblush"      : "sblush",
            "spshare"      : "share",
            "sphold"       : "shold",
            "spshow"       : "show",
            "spkiss"       : "skiss",
            "spkiss2"      : "skiss2",
            "spmiss"       : "smiss",
            "sptrace"      : "strace",
            "sptouch"      : "touch"]);
}

/*
 * Function name: all2actbbsp
 * Description  : A little exstended version of all2act. It fixes the right
 *                genetive form and keeps track of seen/unseen
 *                depending on the invis flag.
 * Arguments    : See all2act.
 */

varargs void
all2actbbsp(string str, object *oblist, string str1)
{
    string name;
    int size;
    
    int index = -1;

    str = str + " " + desc_many(oblist) + (str1 ? (str1 + "\n") : ".\n");

    oblist = oblist + ({ this_player() });
    oblist = all_inventory(environment(this_player())) - oblist;
    oblist = FILTER_LIVE(oblist);

    size = sizeof(oblist);
    while(++index < size)
    {
        if (CAN_SEE_IN_ROOM(oblist[index]) &&
            CAN_SEE(oblist[index], this_player()))
            oblist[index]->catch_msg(QCTNAME(this_player()) +
                                     get_genitive_s(TP, oblist[index]) + str);
    }
}

varargs void
gen_all2act(string str, object *oblist, string str1)
{
    object spouse = oblist[0];
    string name;
    int index = -1;
    int size;

    str =  str + " " + desc_many(oblist);
    oblist = oblist + ({ this_player() });
    oblist = all_inventory(environment(this_player())) - oblist;
    oblist = FILTER_LIVE(oblist);
    this_player()->reveal_me(1);
    size  = sizeof(oblist);
    while(++index < size)        
    {
        oblist[index]->catch_msg(QCTNAME(TP) + str +
                                 get_genitive_s(spouse, oblist[index]) +
                                 (str1 ? (str1 + "\n") : ".\n"));
    }
}

public string
get_genitive_s(object target, object watcher)
{
    string str;

    str = target->query_the_name(watcher);
    if (extract(str, strlen(str) - 1) == "s")
        return "' ";
    else
        return "'s ";
}

/*
 * Function name: is_my_spouse_here()
 * Description  : Retruns the object pointer to the spouse if she can be seen,
 *                otherwize returning 0 and generating the appropriate
 *                messages.
l
* Arguments    : None.
 */

public mixed
is_my_spouse_here()
{
    object spouse;
    string name = TP->query_prop(PLAYER_S_SPOUSE);

    NF("You don't have any spouse!\n");
    if(!name)
        return;
    NF("But your beloved is not here!\n");
    spouse = find_player(name); /* checks if she is logged on */
    if(!spouse)
        return;
    spouse =  present(spouse, ENV_TP);
    if (!spouse)
        return;
    if (!CAN_SEE(TP, spouse))
        return;
    NF("You can't see " + SP_OB + " now!\n");
    if (!CAN_SEE_IN_ROOM(TP))
        return;
    return spouse;
}

/* ************************************************************************
 * The following functions are executed when the user of the soul types the
 * relevant command defined in query_cmdlist.
 */
    
public int
behind(string str)
{
    object spouse = is_my_spouse_here();
    string *how;
    
    if (!spouse)
        return 0;
    how = parse_adverb(str, "lovingly", 1);
    
    actor("You sneak up behind", SPOUSE, " and " + how[1] +
    " put your arms around " + SP_PO + " waist.");
    all2act(" sneaks up behind", SPOUSE, " and " + how[1] +
    " puts " + TP_PO + " arms around " + SP_PO + " waist.");
    target(" sneaks up behind you and " + how[1] + " puts " + TP_PO +
           " arms around " + "your waist.", SPOUSE);
    return 1;
}

public int
embrace(string str)
{
    object spouse = is_my_spouse_here();
    string *how;
    
    if (!spouse)
        return 0;
    how = parse_adverb(str, "tightly", 1);
    actor("You embrace", SPOUSE, ", holding " + SP_OB + " " + how[1] + ".");
    all2act(" embraces", SPOUSE, ", holding " + SP_OB + " " + how[1] + ".");
    target(" embraces you, holding you " + how[1] + ".", SPOUSE);
    return 1;
}

public int
entwine()
{
    object spouse = is_my_spouse_here();
    string str, gen_s;
    
    if (!spouse)
        return 0;
    str = "hand, entwining your fingers with ";
    gen_s = SP_PO;
    gen_s += spouse->query_gender() == 0 ? "." : "s.";
    actor("You take", SPOUSE, get_genitive_s(spouse, TP) + str + gen_s);
    gen_all2act("  takes", SPOUSE, "hand, entwining " + TP_PO + " fingers " +
                "with " + gen_s);
    target(" takes your hand, entwining " + TP_PO + " fingers with yours.",
           SPOUSE);
    return 1;
}

public int
gaze()
{
    object spouse = is_my_spouse_here();
    
    if (!spouse)
        return 0;
    actor("You gaze lovingly at", SPOUSE, ", staring deeply into " + SP_PO +
          " beautiful eyes.");
    all2actbb(" gazes lovingly at", SPOUSE, ", staring deeply into " + SP_PO +
             " eyes.");
    targetbb(" gazes lovingly at you, staring deeply into your eyes.",
             SPOUSE);
    return 1;
}

public int
glower(string str)
{
    object *stuff;
    string *letters;

    NF("Glower at whom?\n");
    if (!str)
        return 0;
    stuff = parse_this(str, " [jealously] [at] [the] %l ");
    NF("You don't find any " + str + ".\n");
    if (!sizeof(stuff))
        return 0;
    actor("You glower jealously at", stuff, ".");
    all2actbbsp("eyes glows jealously at", stuff, ".");
    if (extract(str, strlen(str) - 1) == "s")
        targetbb("' eyes glows jealously at you", stuff);
    else
        targetbb("'s eyes glows jealously at you", stuff);
    return 1;
}

public int
hair(string str)
{
    object spouse = is_my_spouse_here();
    string *how;
    
    if(!spouse)
        return 0;
    how = parse_adverb_with_space(str, "gently", 1);
    actor("You" + how[1] + " brush away a lock of hair from", SPOUSE,
          get_genitive_s(spouse, TP) + "face.");
    gen_all2act(how[1] + " brushes away a lock of hair from", SPOUSE, "face.");
    target(how[1] + " brushes away a lock of hair from your face.", SPOUSE);
    return 1;
}

public int
help(string str)
{
    if (str == "ring" || str == "marriage" || str == "wedding")
    {
        write("\tThis is the emotes you get through marriage.\n" +
              "\tspbehind [adverb]   --  Sneak up behind your spouse and hold him/her.\n" +
              "\tspembrace [adverb]  --  Embrace your beloved in that special way.\n" +
              "\tspentwine           --  Entwine your fingers with your spouse.\n" +
              "\tspgaze              --  Gaze at your lovely spouse.\n" +
              "\tspglower            --  Glower jelously at someone.\n" +
              "\tsphair [adverb]     --  Brush some hair from your spouse's face.\n" +
              "\thelp marriage       --  This piece of text.\n" +
              "\tsphug [adverb]      --  Give your spouse a real hug.\n" +
              "\tspkneel             --  Kneel to your spouse.\n" +
              "\tsplap               --  Snuggle up in your spouse's lap.\n" +
              "\tsplust              --  Show what you think about your spouse.\n" +
              "\tsppledge anew            --  Pledge your love anew.\n" +
              "\tspprotect           --  Boldly protect your spouse.\n" +
              "\tsprotate            --  Rotate your ring.\n" +
              "\tspblush [adverb]    --  Blush at someone's words.\n" +
              "\tspshare             --  Share a secret smile.\n" +
              "\tsphold              --  Hold your spouse in a special way.\n" +
              "\tspshow ring              --  Daunt suitors by showing your ring.\n");
        write("\tspkiss [adverb] [location]\n" +
              "\tspkiss2             --  A hot kiss.\n" +
              "\tspmiss              --  Mope about because your beloved isn't here.\n" +
              "\tsptrace             --  Romantic kind of kiss.\n" +
              "\tsptouch             --  Fondle your spouse in a cute way.\n");      
        return 1;
    }
    return 0;
}

public int
hug(string str)
{
    object spouse = is_my_spouse_here();
    string *how;

    if (!spouse)
        return 0;
    how = parse_adverb(str, "tightly", 1);
    
    actor("You pull", SPOUSE, " close and hug " + SP_OB + " " + how[1] + ".");
    all2act(" pulls", SPOUSE, " close, hugging " + SP_OB + " " + how[1] + ".");
    target(" pulls you close, hugging you " + how[1] + ".", SPOUSE);
    return 1;
}
    

public int
kneel()
{
    object spouse = is_my_spouse_here();
    
    if (!spouse)
        return 0;
    actor("You kneel before", SPOUSE, ", pledging your loving devotion to " +
    SP_OB + ".");
    all2actbb(" kneels before", SPOUSE, ", pledging " + TP_PO + " devotion to "
              + SP_OB + ".");
    targetbb(" kneels in front of you, pledging " + TP_PO +
             " loving devotion to you.", SPOUSE);
    return 1;
}

public int
lap()
{
    object spouse = is_my_spouse_here();
    
    if (!spouse)
        return 0;
    actor("You snuggle up in", SPOUSE, "'s lap.");
    all2act(" snuggles up in", SPOUSE, "'s lap.");
    target(" snuggles up in your lap.", SPOUSE);
    return 1;
}

public int
lust()
{
    object spouse = is_my_spouse_here();
    
    if (!spouse)
        return 0;
    actor("You show how much you lust for", SPOUSE, ".");
    all2act(" shows how much " + TP->query_pronoun() + " lusts for", SPOUSE,
            ".");
    target(" shows how much " + TP->query_pronoun() + " lusts for you!",
           SPOUSE);
    return 1;
}

public int
pledge(string str)
{
    object spouse;
    string name;
    int fingered;
    
    NF("Pledge what?\n");
    if (str != "anew")
        return 0;
    NF("You don't have any spouse!\n");
    name = TP->query_prop(PLAYER_S_SPOUSE);
    if (!name)
        return 0;
    spouse = find_player(name);
    if (!spouse)
    {
        spouse = SECURITY->finger_player(name);
        fingered = 1;
    }
    actor("You pledge your love for", SPOUSE, " anew.");
    all2act(" pledges " + TP_PO + " love for", SPOUSE, " anew.");
    target(" pledges " + TP_PO + " love for you anew.", SPOUSE);
    if (fingered)
        spouse->remove_object();
    return 1;
}

public int
protect()
{
    object spouse = is_my_spouse_here();
    if(!spouse)
        return 0;
    actor("You boldly step in front of", SPOUSE, ", protecting " +
    SP_OB + " from danger.");
    all2act(" boldly steps in front of", SPOUSE, ", protecting " +
    SP_OB + " from danger.");
    target(" boldly steps in front of you, protecting you from danger.",
           SPOUSE);
    return 1;
}

public int
rotate(string str)
{
    object ring;

    NF("Rotate what?\n");
    if (!str)
        return 0;
    NF("You have lost your marriage ring!\n");
    ring = present(RING_ID, TP);
    if (!ring)
        return 0;
    NF("But you are not wearing the marriage ring!\n");
    if (!ring->query_worn())
        return 0;
    write("You rotate your ring, thinking of your beloved.\n");
    allbb(" rotates " + TP_PO + " ring, a wistful expression on " + TP_PO +
          " face.");
    return 1;
}
    
public int
sblush(string str)
{
    object *player = ({ });
    string *how;
    NF("Blush [how] at whom?\n");
    if(!str)
        return 0;
    how = parse_adverb(str, "profusely", 0);
    
    player = parse_this(how[0], "[at] / [the] %l");
    NF("Blush " + how[1] + " at whom?\n");
    if (!sizeof(player))
        return 0;
    NF("You can't blush at more than one person's words at the time.\n");
    if (sizeof(player) > 1)
        return 0;
    actor("You blush " +  how[1] + " at", player,
          get_genitive_s(player[0], TP) + "words.");
    all2actbb(" blushes " + how[1] + " at", player,
                get_genitive_s(player[0], TP) + "words.");
    target(" blushes " + how[1] + " at your words.", player);
    return 1;
}

public int
share(string str)
{
    object spouse = is_my_spouse_here();

    if (!spouse)
        return 0;
    NF("Share secret?\n");
    if (str != "secret")
        return 0;
    actor("You share a secret smile with", SPOUSE, ".");
    all2actbb(" shares a secret smile with", SPOUSE, ".");
    target(" shares a secret smile with you.", SPOUSE);
    return 1;
}

    
public int
shold(string str)
{
    object spouse = is_my_spouse_here();

    if (!spouse)
        return 0;
    if (!str)
    {
        actor("You hold", SPOUSE, " close, trying to make " + SP_OB +
              " feel warm.");
        all2act(" holds", SPOUSE, " close.");
        target(" holds you close, making you feel warm and cozy.", SPOUSE);
        return 1;
    }
    NF("Hold hands?\n");
    if (str != "hand" && str != "hands")
        return 0;
    actor("You gently take", SPOUSE, get_genitive_s(spouse, TP) + str +
          " in yours.");
    gen_all2act("  gently takes", SPOUSE, str + " in " + TP_PO + ".");
    target(" gently takes your " + str + " into " + TP_PO + ".", SPOUSE);
    return 1;
}    

public int
show(string str)
{
     object ring;

     NF("Show what?\n");
     if (!str)
         return 0;
     NF("You have lost you wedding ring!\n");
     ring = present(RING_ID, TP);
     if (!ring)
         return 0;
     NF("But you are not wearing the marriage ring!\n");
     if (!ring->query_worn())
         return 0;
     write("You hold up your marriage ring for all to see.\n");
     allbb(" proudly holds up " + TP_PO + " marriage ring for all to see.");
     return 1;
}

public int
skiss(string str)
{
    object spouse = is_my_spouse_here();
    string *how;
    string *locations = ({"neck", "hand", "cheek", "nose", "forehead",
                          "tummy", "lips", "mouth"});
    string *words = ({""});
    int apa;

    if (!spouse)
        return 0;
    how = parse_adverb_with_space(str, "softly", 0);
    if(strlen(how[0]) > 0)
    {
        words = explode(how[0], " ");
        apa = member_array(words[sizeof(words) - 1], locations);
        if(apa >= 0)
            how[1] += " on the " + locations[apa];
    }
    how[1] += ".";
    actor("You kiss", SPOUSE, how[1]);
    target(" kisses you" + how[1], SPOUSE);
    all2act(" kisses", SPOUSE, how[1]);
    return 1;
}

public int
skiss2()
{
    object spouse = is_my_spouse_here();

    if(!spouse)
        return 0;
    actor("You pull", SPOUSE, " close and trace " + SP_PO +" lips with your " +
          "tongue, kissing " + SP_OB + " passionately.");
    all2act(" pulls", SPOUSE, " close and gives " + SP_OB +" a hot kiss.");
    target(" pulls you close and traces your lips with " + TP_PO +
           " tongue, kissing you passionately, leaving you breathless.",
           SPOUSE);
    return 1;
}

public int
smiss()
{
    string name = TP->query_prop(PLAYER_S_SPOUSE);
    object spouse;
    
    NF("You don't have any spouse!\n");
    if (!name)
        return 0;
    spouse = find_player(name); /* checks if she is logged on */
    NF("But " + capitalize(spouse->query_real_name()) + " is here!\n");
    if (spouse)
    {
        if(present(spouse, ENV_TP) && CAN_SEE(TP, spouse) &&
           CAN_SEE_IN_ROOM(TP))
            return 0;
        spouse->catch_msg("You suddenly get the feeling that " +
                          capitalize(TP->query_real_name()) + " needs you!\n");
    }
    allbb(" mopes about, casting blank looks into the distance.");
     if (TP->query_option(OPT_ECHO))
        TP->catch_msg("Oh, if only " + capitalize(name) +
                      " were here now!\n");
    else
        TP->catch_msg("Ok.\n");
    return 1;
}

public int
strace()
{
    object spouse = is_my_spouse_here();

    if(!spouse)
        return 0;
    actor("You trace a finger down", SPOUSE, get_genitive_s(spouse, TP) +
          "cheek, gently kissing " + SP_PO + " lips.");
    gen_all2act("  traces a finger down", SPOUSE, "cheek, gently kissing " +
                SP_PO + " lips.");
    target(" traces a finger down your cheek, gently kissing your lips.",
           SPOUSE);
    return 1;
}

public int
touch()
{
    object spouse = is_my_spouse_here();
    if (!spouse)
        return 0;
    actor("You touch", SPOUSE, " with loving and caring hands.");
    all2act(" touches", SPOUSE, " with loving and caring hands.");
    target(" touches you with loving and caring hands.", SPOUSE);
    return 1;
}


