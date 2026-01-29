/*
 * This is soul with AA emotes
 *  redefined standard emotes:
 *      apologize, applaud, blush, bounce, bow, brighten, burp, 
 *      cheer, choke, chuckle, cough, cower, cry, curtsey, explode, 
 *      giggle, grin, hug, laugh, nudge, panic, pat, peer, point,
 *      poke, scratch, scream, shake, shrug, slap, snarl, spank, 
 *      squeeze, stare, sulk, tickle, wave, wiggle 
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <ss_types.h>
#include <wa_types.h>
#include <adverbs.h>
#include "../guild.h"

#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))
#define DEPTH 1  /*  How many rooms away the shout will be heard.  */

string *panic_arr = ({"$panic", "$tremble", "$shiver", 
					  "$cringe to "+TP->query_real_name(), "$cower", "$jump"});
#define PANIC ONE_OF_LIST(panic_arr)

/* The soul identification */
string get_soul_id()
{
    return GUILD_NAME+" - standard emotes";
}

int
list_changed_emotes(string arg)
{
    NF("Angmar what? Angmar emotes???\n");
    if(arg != "emotes") 
         return 0;
    write("\nList of emotes changed for Angmar's Army:\n"+
            "-----------------------------------------\n\n"+
        "apologize, applaud, blush, bounce, bow, brighten, burp, cheer, choke, "+
        "chuckle, cough, cower, cry, curtsey, explode, giggle, grin, hug, laugh, "+
        "nudge, panic, pat, peer, point, poke, scratch, scream, shake, shrug, "+
        "slap, snarl, spank, squeeze, stare, sulk, tickle, wave, wiggle\n\n"+
        "All of them work like standard ones only results are different. "+
        "Hope you will have fun with them and will find out when and what "+
        "they do!\n\n");
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
    FIXEUID;
    return ([
        "angmar":"list_changed_emotes",
        "apologize":"apologize",
        "applaud":"applaud",
        "blush":"blush",
        "bounce":"bounce",
        "bow":"bow",
        "brighten":"brighten",
        "burp":"burp",
        "cheer":"cheer",
        "choke":"choke",
        "chuckle":"chuckle",
        "cough":"cough",
        "cower":"cower",
        "cry":"cry",
        "curtsey":"curtsey",
        "explode":"explode",
        "giggle":"giggle",
        "grin":"grin",
        "hug":"hug",
        "laugh":"laugh",
        "nudge":"nudge",
        "panic":"panic",
        "pat":"pat",
        "peer":"peer",
        "point":"point",
        "poke":"poke",
        "scratch":"scratch",
        "scream":"scream",
        "shake":"shake",
        "ashake":"shake",
        "shrug":"shrug",
        "slap":"slap",
        "snarl":"snarl",
        "spank":"spank",
        "squeeze":"squeeze",
        "stare":"stare",
        "sulk":"sulk",
        "tickle":"tickle",
        "wave":"wave",
        "wiggle":"wiggle"
        ]);
}

/*************************************************************/

int query_cmd_soul() { return 1; }

/*************************************************************/
/**********  first some handy functions  *********************/
/*************************************************************/

/*** this returns array of worn shields  ***/
object *shields()
{
    object ob, *shields = ({ });
    if((ob = TP->query_armour(W_LEFT)) && (ob->query_at() == A_SHIELD))
        shields += ({ ob });
    if((ob = TP->query_armour(W_RIGHT)) && (ob->query_at() == A_SHIELD))
        shields += ({ ob });
    return shields;
}

/*** this returns array of wielded clubs  ***/
object *clubs()
{
    object ob, *clubs = ({ });
    if((ob = TP->query_weapon(W_RIGHT)) && (ob->query_wt() == W_CLUB))
        clubs += ({ ob });
    if((ob = TP->query_weapon(W_LEFT)) && (ob->query_wt() == W_CLUB))
        clubs += ({ ob });
    if((ob = TP->query_weapon(W_BOTH)) && (ob->query_wt() == W_CLUB))
        clubs += ({ ob });
    return clubs;
}

/*** this returns short() of one worn shield or ""  ***/
string shield()
{
    object sh;
    if (((sh = TP->query_armour(W_LEFT)) && (sh->query_at() == A_SHIELD)) ||
        ((sh = TP->query_armour(W_RIGHT)) && (sh->query_at() == A_SHIELD)))
        return sh->short();
    return "";
}

/*** this returns short() of one wielded club or ""  ***/
string club()
{
    object club;
    club = TP->query_weapon(W_RIGHT);
    if(!club || club->query_wt() != W_CLUB)
    {
        club = TP->query_weapon(W_BOTH);
        if(!club)
            club = TP->query_weapon(W_LEFT);
    }
    if(!club || club->query_wt() != W_CLUB)
        return "";
    return club->short();
}

string
str_a_arr(mixed arr)
{
    return COMPOSITE_DEAD(arr);
}
string
str_the_arr(mixed arr)
{
    string s, str = COMPOSITE_DEAD(arr);
    str = implode(explode(str, " a "), " the ");
    str = implode(explode(str, " an "), " the ");
    if((sscanf(str, "a %s", s) == 1) || (sscanf(str, "an %s", s) == 1))
        str = "the "+s;
    return str;
}
string
str_arr(mixed arr)
{
    string s, str = COMPOSITE_DEAD(arr);
    str = implode(explode(str, " a "), " ");
    str = implode(explode(str, " an "), " ");
    if((sscanf(str, "a %s", s) == 1) || (sscanf(str, "an %s", s) == 1))
        str = s;
    return str;
}
/*************************************************************/
/**********  now redefined emotes  ***************************/
/*************************************************************/

int
apologize(string str)
{
    object *oblist, *items = clubs();
    string *how, what;
    if(!sizeof(items)) return 0;
    how = parse_adverb_with_space(str, "remorsefully", 0);
    what = str_arr(items);
    if (!strlen(how[0]))
    {
        write("You apologize"+how[1]+", hiding your "+what+
            " behind your back.\n");
        all(" apologizes"+how[1]+", hiding "+HIS(TP)+" "+what+
            " behind "+HIS(TP)+" back.");
        return 1;
    }
    oblist = parse_this(how[0], "[to] [the] %l");
    if (!sizeof(oblist)) return 0;
    target(" apologizes"+how[1]+" to you, hiding "+HIS(TP)+" "+what+
        " behind "+HIS(TP)+" back.", oblist);
    actor("You apologize"+how[1]+" to",oblist,", hiding your "+what+
        " behind your back.");
    all2act(" apologizes"+how[1]+" to", oblist, ", hiding "+HIS(TP)+" "+
        what+" behind "+HIS(TP)+" back.");
    return 1;
}

int
applaud(string str)
{
    object *oblist, *items = shields()+clubs();
    string *how, what;
    if(sizeof(items) < 2) return 0;
    what = str_arr(items);
    how = parse_adverb_with_space(str, "wholeheartedly", 0);
    if (!strlen(how[0]))
    {
        all(" applauds"+how[1]+", hitting "+HIS(TP)+" "+what+" together.");
        write("You applaud"+how[1]+", hitting your "+what+" together.\n");
        return 1;
    }
    oblist = parse_this(how[0], "[for] / [to] [the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Applaud to whom?\n");
        return 0;
    }
    target(" applauds"+how[1]+" to you, hitting "+HIS(TP)+" "+what+
        " together.", oblist);
    actor("You applaud"+how[1]+" to", oblist, 
        ", hitting your "+what+" together.");
    all2act(" applauds"+how[1]+" to", oblist, ", hitting "+HIS(TP)+" "+
        what+" together.");
    return 1;
}

int
blush(string str)
{
    object *items = shields();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, "profusely");
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    what = str_arr(items);
    write("Your try to hide your burning cheeks behind your "+what+".\n");
    allbb(" hides behind "+HIS(TP)+" "+what+", blushing"+str+".");
    return 1;
}

int
bounce(string str)
{
    object *items = clubs() + shields();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, "uncontrollably");
    if (str == NO_ADVERB_WITH_SPACE)
        return 0;
    what = str_arr(items);
    write("You bounce around"+str+", waving with your "+what+".\n");
    all(" bounces around"+str+", waving with "+HIS(TP)+" "+what+".");
    return 1;
}

int
bow(string str)
{
    object *oblist;
    string *how, what = club();
    if(what == "") return 0;
    how = parse_adverb_with_space(str, "gracefully", 0);
    if(!strlen(how[0]))
    {
        write("You bow"+how[1]+", waving with your "+what+".\n");
        allbb(" bows"+how[1]+", waving with "+HIS(TP)+" "+what+".");
        return 1;
    }
    oblist = parse_this(how[0], "[to] / [before] [the] %l");
    if (!sizeof(oblist)) return 0;
    targetbb(" bows"+how[1]+" to you, waving with "+HIS(TP)+" "+what+".", oblist);
    actor("You bow"+how[1]+" to", oblist, ", waving with your "+what+".");
    all2actbb(" bows"+how[1]+" to", oblist, ", waving with "+HIS(TP)+" "+what+".");
    return 1;
}

int
brighten(string str)
{
    string what = club();
    if(what == "") return 0;
    if (strlen(str)) return 0;
    write("You think about it, then bonk yourself on the head with your "+
        what+"! Your face brightens!\n");
    all(" thinks about it, then bonks "+HIM(TP)+"self on the head with "+
        HIS(TP)+" "+what+"! "+CAP(HIS(TP))+" face brightens.");
    return 1;
}

int
burp(string str)
{
    object *items = shields();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, "rudely");
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    what = str_arr(shields());
    write("You burp"+str+".\nThe sound echoes in your "+what+".\n");
    all(" burps"+str+".\nThe sound echoes in "+HIS(TP)+" "+what+".");
    return 1;
}

int
cheer(string str)
{
    object *items = clubs() + shields();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, "enthusiastically");
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    what = str_arr(items);
    write("You cheer"+str+", waving with your "+what+".\n");
    all(" cheers"+str+", waving with "+HIS(TP)+" "+what+".");
    return 1;
}

int
choke(string str)
{
    string what = club();
    if(what == "") return 0;
    if (strlen(str)) return 0;
    write("Cough, cough, cough, hark !!!\nHitting your back with your "+
        what+" doesn't help much.\n");
    all("'s face colour slowly darkens as "+HE(TP)+" chokes, trying in vain "+
        "help "+HIM(TP)+"self by hitting "+HIS(TP)+" back with "+HIS(TP)+
        " "+what+".");
    return 1;
}

int
chuckle(string str)
{
    object *items = shields();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, "politely");
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    what = str_arr(items);
    write("You chuckle"+str+" behind your "+what+".\n");
    all(" chuckles"+str+" behind "+HIS(TP)+" "+what+".");
    return 1;
}

int
cough(string str)
{
    string what = shield();
    if(what == "") return 0;
    str = check_adverb_with_space(str, "noisily");
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    write("You cover quickly your mouth and cough into your "+what+".\n");
    all(" covers quickly "+HIS(TP)+" mouth and coughs into "+HIS(TP)+" "+what+".");
    return 1;
}

int
cower(string str)
{
    object *items = shields();
    string what;
    if(!sizeof(items)) return 0;
    if (strlen(str)) return 0;
    what = str_arr(items);
    write("You try to hide behind your "+what+".\n");
    allbb(" tries to hide behind "+HIS(TP)+" "+what+".");
    return 1;
}

int
cry(string str)
{
    string what;
    if (strlen(str)) return 0;
    what = club();
    if(!sizeof(parse_this("elf", "%l")))
    {
        if(what == "") what = shield();
        if(what != "")
        {
            write("You bursts into tears, wishing some elves were around to smash "+
                "with your "+what+" and make you feel better.\n");
            all(" bursts into tears, wishing some elves were around to smash "+
                "with "+HIS(TP)+" "+what+" and make "+HIM(TP)+" feel better.");
        }
        else
        {
            write("You bursts into tears, wishing some elves were around to bash "+
                "and make you feel better.\n");
            all(" bursts into tears, wishing some elves were around to bash "+
                "and make "+HIM(TP)+" feel better.");
        }
        return 1;
    }
    if(what != "")
    {
        write("You bursts into tears, wiping them out with your "+what+".\n");
        all(" bursts into tears, wiping them out with "+HIS(TP)+" "+what+".");
        return 1;
    }
    what = shield();
    if(what != "")
    {
        write("You bursts into tears, catching them into your "+what+".\n");
        all(" bursts into tears, catching them into "+HIS(TP)+" "+what+".");
        return 1;
    }
    return 0;
}

int
curtsey(string str)
{
    object *oblist;
    string *how, what = club();
    if(what == "") return 0;
    how = parse_adverb_with_space(str, "gracefully", 0);
    if(!strlen(how[0]))
    {
        write("You curtsey"+how[1]+", waving with your "+what+".\n");
        allbb(" curtseys"+how[1]+", waving with "+HIS(TP)+" "+what+".");
        return 1;
    }
    oblist = parse_this(how[0], "[to] / [before] [the] %l");
    if (!sizeof(oblist)) return 0;
    targetbb(" curtseys"+how[1]+" to you, waving with "+HIS(TP)+" "+what+".", oblist);
    actor("You curtsey"+how[1]+" to", oblist, ", waving with your "+what+".");
    all2actbb(" curtseys"+how[1]+" to", oblist, ", waving with "+HIS(TP)+" "+what+".");
    return 1;
}

int
explodes(string str)
{
    object *oblist, *higher, *items = clubs() + shields();
    string what;
    int i;
    if(!sizeof(items)) return 0;
    what = str_arr(items);
    if (!strlen(str))
    {
        write("You hold your breath and explode in anger, waving dangerously with your "+what+".\n");
        all(" explodes with anger, waving dangerously with "+HIS(TP)+" "+what+".");
        return 1;
    }
    oblist = parse_this(str, "[at] [the] %l");
    if (!sizeof(oblist)) return 0;
    higher = ({ });
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
    oblist -= higher;
    if (!sizeof(oblist))
    {
        actor("You must control yourself in contact with", higher, 
            ". Your rank is still too low...");
        return 1;
    }
    target(" explodes with anger at you, waving dangerously with "+HIS(TP)+" "+what+".", oblist);
    actor("You explode in anger at", oblist, ", waving dangerously with your "+what+".");
    all2act(" explodes with anger at", oblist, ", waving dangerously with "+HIS(TP)+" "+what+".");
    for(i=0; i<sizeof(oblist); i++)
        if(random(TP->query_skill(SS_WEP_CLUB)) > random(oblist[i]->query_stat(SS_DIS)))
            oblist[i]->command(PANIC);
    return 1;
}

int
giggle(string str)
{
    object *items = shields();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, "inanely");
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    what = str_arr(items);
    write("You giggle"+str+" from behind your "+what+".\n");
    all(" giggles"+str+" from behind "+HIS(TP)+" "+what+".");
    return 1;
}

int
grin(string str)
{
    object *oblist, *higher, *items = clubs();
    string *how, what;
    int i;
    if(!sizeof(items)) return 0;
    what = str_arr(items);
    how = parse_adverb_with_space(str, "evilly", 0);
    if (!strlen(how[0]))
    {
        write("You grin"+how[1]+", swinging your "+what+" around.\n");
        allbb(" grins"+how[1]+", swinging "+HIS(TP)+" "+what+" around.");
        return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist)) return 0;
    higher = ({ });
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
    oblist -= higher;
    if (!sizeof(oblist))
    {
        actor("You must control yourself in contact with", higher, 
            ". Your rank is still too low...");
        return 1;
    }
    targetbb(" grins"+how[1]+" at you, swinging "+HIS(TP)+" "+what+" under your nose.", oblist);
    actor("You grin"+how[1]+" at", oblist, ", swinging your "+what+
        " under "+(sizeof(oblist)>1 ? "their noses." : HIS(oblist[0])+" nose."));
    all2act(" grins"+how[1]+" at", oblist, ", swinging "+HIS(TP)+" "+
        what+" under "+(sizeof(oblist)>1 ? "their noses." : HIS(oblist[0])+" nose."));
    for(i=0; i<sizeof(oblist); i++)
        if(random(TP->query_skill(SS_WEP_CLUB)) > random(oblist[i]->query_stat(SS_DIS)))
            oblist[i]->command(PANIC);
    return 1;
}

int
hug(string str)
{
    object *oblist, *items = shields();
    string *how, what;
    
    if(!sizeof(items)) return 0;
    how = parse_adverb_with_space(str, "fiercefully", 1);
    oblist = parse_this(how[0], "[the] %l");
    if (!sizeof(oblist)) return 0;
    what = str_arr(items);
    target(" hugs you"+how[1]+", pressing "+HIS(TP)+" "+what+" into your ribs.", oblist);
    actor("You hug", oblist, how[1]+", pressing your "+what+
        " into "+(sizeof(oblist)>1 ? "their" : HIS(oblist[0]))+" ribs.");
    all2act(" hugs", oblist, how[1]+", pressing "+HIS(TP)+" "+what+
        " into "+(sizeof(oblist)>1 ? "their" : HIS(oblist[0]))+" ribs.");
    return 1;
}

int
laugh(string str)
{
    object *oblist, *higher, *items = clubs();
    string *how, what;
    int i;
    if(!sizeof(items)) return 0;
    what = str_arr(items);
    if (!strlen(str))
    {
        write("You fall down laughing, beating your "+what+" on the ground.\n");
        all(" falls down laughing, beating "+HIS(TP)+" "+what+" on the ground.");
        return 1;
    }
    how = parse_adverb_with_space(str, "exuberantly", 0);
    if (!strlen(how[0]))
    {
        write("You laugh"+how[1]+", beating your "+what+" on the ground.\n");
        all(" laughs" + how[1] + ", beating "+HIS(TP)+" "+what+" on the ground.");
        return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist)) return 0;
    higher = ({ });
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
    oblist -= higher;
    if (!sizeof(oblist))
    {
        actor("You must control yourself in contact with", higher, ". Your rank is still too low...");
        return 1;
    }
    target(" laughs"+how[1]+" at you, beating "+HIS(TP)+" "+what+" on the ground.", oblist);
    actor("You laugh" + how[1] + " at", oblist, ", beating your "+what+" on the ground.");
    all2act(" laughs" + how[1] + " at", oblist, ", beating "+HIS(TP)+" "+what+" on the ground.");
    return 1;
}

int
nudge(string str)
{
    object *oblist;
    string what = club();
    if(what == "") what = shield();
    if(what == "") return 0;
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist)) return 0;
    target(" nudges you with "+HIS(TP)+" "+what+".", oblist);
    actor("You nudge", oblist, " with your "+what+".");
    all2act(" nudges", oblist, " with "+HIS(TP)+" "+what+".");
    return 1;
}

int
panic(string str)
{
    string what = club();
    if(what == "") return 0;
    if (strlen(str)) return 0;
    write("You panic and try to hide behind your "+what+".\n");
    allbb(" panics and tries to hide behind "+HIS(TP)+" "+what+".");
    return 1;
}

int
pat(string str)
{
    object *oblist, *higher;
    string *zones, one, two, what = club();
    int i;
    if(what == "") return 0;
    if (!strlen(str)) return 0;
    zones = ({ "back", "head", "shoulder" });
    if (sscanf(str, "%s %s", one, two) == 2)
    {
        if (member_array(two, zones) == -1)
            return 0;
        str = one;
    }
    if (!strlen(two))
        two = "head";
    if ((str == (string)TP->query_real_name()) ||
        (str == "me") ||
        (str == "myself"))
    {
        write("You pat yourself on your "+two+" with your "+what+".\n");
        all(" pats "+HIM(TP)+"self on "+HIS(TP)+" "+two+" with "+HIS(TP)+" "+what+".");
        return 1;
    }
    oblist = parse_this(str, "[the] %l [on] [the]");
    if (!sizeof(oblist)) return 0;
    higher = ({ });
    if(two == "head")
        for(i=0; i<sizeof(oblist); i++)
            if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
    oblist -= higher;
    if (sizeof(oblist))
    {
        target(" pats you on your "+two+" with "+HIS(TP)+" "+what+".", oblist);
        actor("You pat", oblist, " on "+
            (sizeof(oblist) > 1 ? "their "+two+"s" : HIS(oblist[0])+" "+two)+
            " with your "+what+".");
        all2act(" pats", oblist, " on " +
            (sizeof(oblist)> 1 ? "their "+two+"s" : HIS(oblist[0])+" "+two)+
            " with "+HIS(TP)+" "+what+".");
    }
    if (sizeof(higher))
    {
        target(" kneels in front of you and offers you "+HIS(TP)+" "+what+
            ". You take it and bonk "+HIM(TP)+" on the head with it.", higher);
        actor("You kneel in front of", higher, " and offer "+
            (sizeof(higher) > 1 ? "them" : HIM(higher[0]))+" your "+what+". "
            +(sizeof(higher) > 1 ? "They take it in turn and bonk" :
                                   CAP(HE(higher[0]))+" takes it and bonks")+
            " you on the head with it.");
        all2act(" kneels in front of", higher, " and offer "+
            (sizeof(higher) > 1 ? "them" : HIM(higher[0]))+" "+HIS(TP)+" "+what+". "
            +(sizeof(higher) > 1 ? "They take it in turn and bonk ":
                                   CAP(HE(higher[0]))+" takes it and bonks ")+
            HIM(TP)+" on the head with it.");
    }
    return 1;
}

int
peer(string str)
{
    object *oblist, *items = shields();
    string *how, what;
    if(!sizeof(items)) return 0;
    what = str_arr(items);
    how = parse_adverb_with_space(str, "quizzically", 0);
    if (!strlen(how[0]))
    {
        write("You peer"+how[1]+" around from behind your "+what+".\n");
        allbb(" peers"+how[1]+" around from behind "+HIS(TP)+" "+what+".");
        return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist)) return 0;
    targetbb(" peers"+how[1]+" at you from behind "+HIS(TP)+" "+what+".", oblist);
    actor("You peer"+how[1]+" at", oblist," from behind your "+what+".  Hmm......");
    all2actbb(" peers"+how[1]+" at", oblist, " from behind "+HIS(TP)+" "+what+".");
    return 1;
}

int
point(string str)
{
    object *oblist;
    string *tmp, what = club();
    if(what == "") return 0;
    notify_fail("Where do you want to point?\n");
    if (!strlen(str))
    {
        write("You point with your "+what+" all around.\n");
        allbb(" points with "+HIS(TP)+" "+what+" all around.");
        return 1;
    }
    if (str == "up" || str == "down" || str == "north" || str == "south" ||
        str == "west" || str == "east" || str == "northwest" ||
        str == "northeast" || str == "southwest" || str == "southeast")
    {
        write("You point "+str+" with your "+what+".\n");
        allbb(" points "+str+" with "+HIS(TP)+" "+what+".");
        return 1;
    }
    if (str == TP->query_real_name() || str == "me" || str == "myself")
    {
        write("You point at yourself with your "+what+".\n");
        allbb(" points at "+HIM(TP)+"self with "+HIS(TP)+" "+what+".");
        return 1;
    }
    oblist = parse_this(str, "[at] [the] %l");
    if (!sizeof(oblist))
    {
        tmp = explode(str, " ");
        if (sizeof(tmp) > 1 && tmp[0] == "at")
            str = implode(tmp[1 .. sizeof(tmp) - 1], " ");
        oblist = FIND_STR_IN_OBJECT(str, ENV(TP));
        if (!sizeof(oblist))
        {
            if (ENV(TP)->item_id(str))
            {
                write("You point at the "+str+" with your "+what+".\n");
                allbb(" points at "+LANG_ADDART(str)+" with "+HIS(TP)+" "+what+".");
                return 1;
            }
            return 0;
        }
        write("You point at "+LANG_THESHORT(oblist[0])+" with your "+what+".\n");
        allbb(" points at "+LANG_THESHORT(oblist[0])+" with "+HIS(TP)+" "+what+".");
        return 1;
    }
    targetbb(" points at you with "+HIS(TP)+" "+what+".", oblist);
    actor("You point at", oblist, " with your "+what+".");
    all2actbb(" points at", oblist, " with "+HIS(TP)+" "+what+".");
    return 1;
}

int
poke(string str)
{
    object *oblist;
    string *zones, one, two, what = club();
    if(what == "") return 0;
    if(!strlen(str)) return 0;
    zones = ({"eye", "ear", "thorax", "abdomen", "shoulder", "ribs"});
    if (sscanf(str, "%s %s", one, two) == 2)
    {
        if(member_array(two, zones) == -1) return 0;
        str = one;
    }
    if (!strlen(two)) two = "ribs";
    oblist = parse_this(str, "[the] %l [in] [the]");
    if (!sizeof(oblist)) return 0;
    target(" pokes you in the "+two+" with "+HIS(TP)+" "+what+".", oblist);
    actor("You poke", oblist, " in the "+two+" with your "+what+".");
    all2act(" pokes", oblist, " in the "+two+" with "+HIS(TP)+" "+what+".");
    return 1;
}

int
scratch(string str)
{
    object *oblist;
    string *zones, one, two, what = shield();
    if(what == "") return 0;
    zones = ({ "head", "chin", "back", "behind", "nose" });
    if (!strlen(str)) str = "head";
    if (member_array(str, zones) != -1)
    {
        write("You scratch your "+str+" with the edge of your "+what+".\n");
        allbb(" scratches "+HIS(TP)+" "+str+" with the edge of "+HIS(TP)+" "+what+".");
        return 1;
    }
    if (sscanf(str, "%s %s", one, two) == 2)
        if (member_array(two, zones) == -1)
            return 0;
    if (!strlen(two)) two = "head";
    oblist = parse_this(one, "[the] %l [at] [the]");
    if (!sizeof(oblist)) return 0;
    target(" scratches your "+two+" with the edge of "+HIS(TP)+" "+what+".", oblist);
    actor("You scratch", oblist, "'s "+two+" with the edge of your "+what+".");
    all2act(" scratches", oblist, "'s "+two+" with the edge of "+HIS(TP)+" "+what+".");
    return 1;
}

/* **************************************************************************
 * Shout - shout something.
 */

/*
 * Function name: shout_name
 * Description  : Called through VBFC to find the name/description of the
 *                person who does the shouting.
 * Returns      : string - the name/description of the living.
 */
string
shout_name()
{
    object pobj = previous_object(); /* Reciever of message */
    if (file_name(pobj) == VBFC_OBJECT)
    {
        pobj = previous_object(-1);
    }
    if (pobj->query_met(this_player()))
    {
        return this_player()->query_name();
    }
    return capitalize(LANG_ADDART(this_player()->query_gender_string())) +
        " " + this_player()->query_race_name() + " voice";
}

int
scream(string str)
{
    object *oblist, *higher, *rooms, troom, *items = clubs();
    int i;
    if(!sizeof(items)) return 0;
    if (strlen(str)) return 0;
    if (!(troom = ENV(TP))) return 0;
    rooms = FIND_NEIGHBOURS(troom, DEPTH);
    for (i = 0; i < sizeof(rooms); i++)
        tell_room(rooms[i], "@@shout_name:"+file_name(TO)+"@@ screams loudly!\n", TP);
    oblist = parse_this("all", "%l");
    higher = ({ });
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
    oblist -= higher;
    write("ARRGGGGGGHHHHHH!!!!\n");
    allbb(" screams loudly, angrily smashing everything around with "+HIS(TP)+" "+str_arr(items)+".");
    for(i=0; i<sizeof(oblist); i++)
        if(random(TP->query_skill(SS_WEP_CLUB)) > random(oblist[i]->query_stat(SS_DIS)))
            oblist[i]->command(PANIC);
    return 1;
}

int
shake(string str)
{
    object *oblist, *members;
    int i;
    if (!strlen(str)) return 0;
    if (!sizeof(oblist = parse_this(str, "[with] [the] %l"))) return 0;
    target(" shakes your hand.", oblist);
    actor("You shake hands with", oblist);
    members = ({ });
    for(i=0; i<sizeof(oblist); i++)
        if(IS_MEMBER(oblist[i]))
        {
            members += ({ oblist[i] });
            oblist[i]->catch_msg("You notice secret Angmar sign and return it back.\n");
        }
    all2act(" shakes", oblist, "'s hand.");
    if(sizeof(members)) actor("Your secret sign was returned by", members);
    return 1;
}

int
shrug(string str)
{
    object *items = shields()+clubs();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, "helplessly");
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    what = str_the_arr(items);
    write("You shrug"+str+", flailing your arms with "+what+" widely.\n");
    allbb(" shrugs"+str+", flailing "+HIS(TP)+" arms with "+what+" widely.");
    return 1;
}

int
slap(string str)
{
    object *oblist, *higher;
    string what;
    int i;
    if(sizeof(shields()+clubs())<2) return 0;
    if (!sizeof(oblist = parse_this(str, "[the] %l"))) return 0;
    higher = ({ });
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
    oblist -= higher;
    if (!sizeof(oblist))
    {
        actor("You must control yourself in contact with", higher, ". Your rank is still too low...");
        return 1;
    }
    what = club();
    if(what != "") what = shield();
    target(" tried to slap you, but "+HIS(TP)+" "+what+" hit you first!\nOuch!!!", oblist);
    actor("You tried to slap", oblist, ", but your "+what+" hit "+
        (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    all2act(" tried to slap", oblist, ", but "+HIS(TP)+" "+what+" hit "+
        (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    return 1;
}

int
snarl(string str)
{
    object *oblist, *higher, *items = clubs();
    string *how, what;
    int i;
    if(!sizeof(items)) return 0;
    how = parse_adverb_with_space(str, "savagely", 0);
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist)) return 0;
    higher = ({ });
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
    oblist -= higher;
    if (!sizeof(oblist))
    {
        actor("You must control yourself in contact with", higher, 
            ". Your rank is still too low...");
        return 1;
    }
    what = str_arr(items);
    target(" snarls"+how[1]+" at you, waving with "+what+" over your head.\nAren't you scared ?", oblist);
    actor("You snarl" + how[1] + " at", oblist, ", waving with "+what+" over "+
        (sizeof(oblist)>1 ? "their heads." : HIS(oblist[0])+" head."));
    all2act(" snarls" + how[1] + " at", oblist, ", waving with "+what+" over "+
        (sizeof(oblist)>1 ? "their heads." : HIS(oblist[0])+" head."));
    for(i=0; i<sizeof(oblist); i++)
        if(random(TP->query_skill(SS_WEP_CLUB)) > random(oblist[i]->query_stat(SS_DIS)))
            oblist[i]->command(PANIC);
    return 1;
}

int
spank(string str)
{
    object *oblist;
    string *how, what;
    if(sizeof(shields()+clubs())<2) return 0;
    how = parse_adverb_with_space(str, "playfully", 1);
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist)) return 0;
    what = club();
    if(what == ""); what = shield();
    target(" tried to spank you"+how[1]+", but "+HIS(TP)+" "+what+
        " hit you first!\nOuch!!!", oblist);
    actor("You tried to spank", oblist, how[1]+", but your "+what+" hit "+
        (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    all2act(" tried to spank", oblist, how[1]+", but "+HIS(TP)+" "+what+
        " hit "+(sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    return 1;
}

int
squeeze(string str)
{
    object *oblist, *items = shields();
    string *how, what;
    if(!sizeof(items)) return 0;
    how = parse_adverb_with_space(str, "fondly", 1);
    oblist = parse_this(how[0], "[the] %l");
    if (!sizeof(oblist)) return 0;
    what = str_arr(items);
    target(" squeezes you"+how[1]+", forgetting that "+HIS(TP)+" "+
        what+" hurt"+(sizeof(items)>1 ? "" : "s")+" your ribs.", oblist);
    actor("You squeeze", oblist, how[1]+".");
    all2act(" squeezes", oblist, how[1]+", forgetting that "+HIS(TP)+" "+
        what+" hurt"+(sizeof(items)>1 ? "" : "s")+
        " "+(sizeof(oblist)>1 ? "their" : HIS(oblist[0]))+" ribs.");
    return 1;
}

int
stare(string str)
{
    object *oblist;
    if(!strlen(str)) return 0;
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l"))) return 0;
    targetbb(" stares at you with a dangerous gleam in "+HIS(TP)+" eyes.", oblist);
    actor("You stare at", oblist, " with a dangerous gleam in your eyes.");
    all2actbb(" stares at", oblist, " with a dangerous gleam in "+HIS(TP)+" eyes.");
    return 1;
}

int
sulk(string str)
{
    object *items = shields();
    string what;
    if(!sizeof(items)) return 0;
    if (strlen(str)) return 0;
    what = str_arr(items);
    write("You sulk behind your "+what+".\n");
    allbb(" sulks behind "+HIS(TP)+" "+what+".");
    return 1;
}

int
tickle(string str)
{
    object *oblist, *items = clubs();
    string *how, what;
    if(!sizeof(items)) return 0;
    how = parse_adverb_with_space(str, "playfully", 1);
    oblist = parse_this(how[0], "[the] %l");
    if (!sizeof(oblist)) return 0;
    what = str_arr(items);
    target(" tickles you"+how[1]+" in the ribs with "+HIS(TP)+" "+what+".", oblist);
    actor("You tickle", oblist, how[1]+" in the ribs with your "+what+".");
    all2act(" tickles", oblist, how[1]+" in the ribs with "+HIS(TP)+" "+what+".");
    oblist->command("$laugh");
    return 1;
}

int
wave(string str)
{
    object *oblist, *items = shields();
    string *how, what;
    if(!sizeof(items)) return 0;
    how = parse_adverb_with_space(str, "happily", 0);
    what = str_arr(items);
    if (!strlen(how[0]))
    {
        write("You wave"+how[1]+", making a little drift with your "+what+".\n");
        allbb(" waves"+how[1]+", making a little drift with "+HIS(TP)+" "+what+".");
        return 1;
    }
    oblist = parse_this(how[0], "[to] [the] %l");
    if (!sizeof(oblist)) return 0;
    targetbb(" waves"+how[1]+" in your direction, making a little drift with "+HIS(TP)+" "+what+".", oblist);
    actor("You wave"+how[1]+" in", oblist, "'s direction, making a little drift with your "+what+".");
    all2actbb(" waves"+how[1]+" in", oblist, "'s direction, making a little drift with "+HIS(TP)+" "+what+".");
    return 1;
}

int
wiggle(string str)
{
    object *items = clubs();
    string what;
    if(!sizeof(items)) return 0;
    str = check_adverb_with_space(str, BLANK_ADVERB);
    if (str == NO_ADVERB_WITH_SPACE) return 0;
    what = str_arr(items);
    write("You wiggle your bottom"+str+", rubbing it gently with "+what+".\n");
    allbb(" wiggles "+HIS(TP)+" bottom"+str+", rubbing it gently with "+what+".");
    return 1;
}

