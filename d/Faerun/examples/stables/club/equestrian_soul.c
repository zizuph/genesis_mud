/*

Equestrian Society of Bree soul
Palmer, January 2003

ChangeLog:

April 28, 2004 - Palmer:
 Changed emount/edismount to only work on players with Bree
 or Noldor horses so Knights won't have problems with automounting.


*/

#pragma strict_types

inherit "/cmd/std/command_driver";
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Shire/common/defs.h"


public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Equestrian Society"; }
void start_hobble(object player);
void stop_hobble(object player);
int do_mount(object member);
int do_dismount(object member);

public mapping
query_cmdlist()
{
    return ([
                  "emount"       : "emount",
                  "emo"          : "emount",
                  "edismount"    : "edismount",
                  "edi"          : "edismount",
                  "ecrack"       : "ecrack",
                  "ecr"          : "ecrack",
                  "eache"        : "eache",
                  "eac"          : "eache",
                  "edust"        : "edust",
                  "edu"          : "edust",
                  "efinger"      : "efinger",
                  "efi  "        : "efinger",
                  "ethwap"       : "ethwap",
                  "eth"          : "ethwap",
                  "eobserve"     : "eobserve",
                  "eob"          : "eobserve",
                  "esearch"      : "esearch",
                  "ese"          : "esearch",
                  "emap"         : "emap",
                  "ema"          : "ema",
                  "ehelp"        : "ehelp",
                  "ehe"          : "ehelp",
                  "ehobble"      : "ehobble",
                  "eho"          : "ehobble",
                  "eaccuse"      : "eaccuse",
                  "eac"          : "eaccuse",
                  "esniff"       : "esniff",
                  "esn"          : "esniff",
                  "espank"       : "espank",
                  "esp"          : "espank",
                  "epoint"       : "epoint",
                  "epo"          : "epoint",
    ]);
}


int
emount()
{
    object *o = TP->query_team();
    if (sizeof(o))
    {
        write("You signal to your party to mount.\n");
        all(" signals " + HIS_HER(TP) + " party, commanding them to mount.");
    }
    else
    {

        if(!do_mount(TP))
            write("Your steed isn't present.\n");
    return 1;
    }
    do_mount(TP);
    map(o, do_mount);

    return 1;
}

int
do_mount(object o)
{
        object horse;

    horse = o->query_prop("_my_horse");

    if (!objectp(horse))
        return 0;

    if (!present(horse, environment(TP)))
        return 0;

    if (present(o, environment(TP)))
    {
        if (o->query_race() == "elf" ||  o->query_race() == "human")
        o->command("mount horse");
        else
        o->command("mount pony");
        return 1;
    }

}

int
edismount()
{
    object *member = TP->query_team();
    if (sizeof(member))
    {
    write("You signal to your party, indicating they should dismount " +
        "their steeds.\n");
    all(" gestures to " + HIS_HER(TP) + " party, letting them know " +
        "they should dismount.");
    }
    TP->command("dismount");
    map(member, do_dismount);

    return 1;
}


void
do_dismount(object o)
{
    object horse;

    horse = o->query_prop("_my_horse");

    if (!objectp(horse))
    return 0;

    if (!present(horse, environment(TP)))
    return 0;


    if (present(o, environment(TP)))
       o->command("dismount");
}


int
eache()
{
    write("You let everyone know how sore you are after your long ride.\n");
    all(" mentions all of " + HIS_HER(TP) + " aches from the long ride.");
    return 1;
}

int
ecrack()
{
    write("You crack your riding crop loudly in the palm of your hand, " +
        "trying to get everyone's attention.\n");
    all(" cracks " + HIS_HER(TP) + " riding crop loudly in the palm of " +
        HIS_HER(TP)+ " hand, trying to get your attention.");
    return 1;
}

int
edust()
{
    write("You beat the dust from your clothing with your riding crop.\n");
    all(" beats the dust from " + HIS_HER(TP) + " clothing with a riding crop.");
    return 1;
}


int
efinger()
{
    write("You finger your riding crop, anticipating your next ride.\n");
    all(" fingers " + HIS_HER(TP) + " riding crop, thinking about " + 
        HIS_HER(TP) + " next ride.");
    return 1;
}


int
espank(string str)
{
    object *oblist;


    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
        write("Spank whom with your riding crop?\n");
        return 1;
    }

    actor("You smack",oblist, " on the bottom with your riding crop!");
    target(" smacks you on the bottom with " + HIS_HER(TP) + " riding crop.",oblist);
    all2act(" smacks",oblist," on the bottom with " + HIS_HER(TP) + " riding crop.");
    return 1;
}


int
ethwap(string str)
{
    object *oblist;

    if(!str)
    {
        write("You shake your riding crop at everyone.\n");
        all(" shakes " + HIS_HER(TP) + " riding crop at you.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
        write("Thwap whom with your riding crop?\n");
        return 1;
    }

    actor("You thwap",oblist, " on the head with your riding crop!");
    target(" thwaps you on the head with " + HIS_HER(TP) + " riding crop.",oblist);
    all2act(" thwaps",oblist," on the head with " + HIS_HER(TP) + " riding crop.");
    return 1;
}


int
eobserve(string str)
{
    object *oblist;

    if(!str)
    {
        write("You smack the palm of your hand with your riding crop, " +
            "deep in thought.\n");
        all(" smacks the palm of " + HIS_HER(TP) + " hand with " + 
            HIS_HER(TP) + " riding crop, deep in thought.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
        write("Observe whom?\n");
        return 1;
    }

    actor("You observe",oblist, " while smacking the palm of your hand " +
        "with your riding crop.");
    target(" observes you as " + HE_SHE(TP) + " smacks " + HIS_HER(TP) + 
        " palm with " + HIS_HER(TP) + " riding crop.",oblist);
    all2act(" observes",oblist," as " + HE_SHE(TP) + " smacks "+ 
        HIS_HER(TP) + " palm with " + HIS_HER(TP) + " riding crop.",oblist);
    return 1;
}


int
esearch()
{
    write("You grip your riding crop nervously, searching for your steed.\n");
    all(" grips " + HIS_HER(TP) + " riding crop nervously, looking for " + 
        HIS_HER(TP) + " steed.");
    return 1;
}

int
emap()
{
    write("You map out the next trail in the dust with your riding crop.\n");
    all(" maps out the next trail in the dust with " + HIS_HER(TP) + 
        " riding crop.");
    return 1;
}


int
esniff()
{
    write("You sniff the air, then subtly check the soles of your boots.\n");
    all(" sniffs the air, then subtly checks the soles of " + HIS_HER(TP) + " boots.");
    return 1;
}



int
eaccuse(string str)
{
    object *oblist;

    if(!str)
    {
        write("Accuse who?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
        write("Accuse whom?\n");
        return 1;
    }

    actor("You smell",oblist, ", look around, then check the soles of your boots.");
    target(" smells you, looks around, then checks the soles of " + 
        HIS_HER(TP) + " boots.",oblist);
    all2act(" smells", oblist, ", looks around, then checks the soles of " + 
        HIS_HER(TP) + " boots.",oblist);
    return 1;
}


int
ehobble(string str)
{
    if (TP->query_equestrian_hobble_shadow() && str != "stop")
    {
        write("You're already hobbleing.  Use 'ehobble stop' to stop.\n");
        return 1;
    }

    if(!str)
    {
        write("You hobble a little as you walk.\n");
        all(" begins to walk a little bow-legged.");
        start_hobble(TP);
        return 1;
    }

    if(str != "stop")
    {
        write("ehobble stop, perhaps?\n");
        return 1;
    }
    write("You stop hobbleing.\n");
    all(" seems to straighten up and walk more properly.");
    stop_hobble(TP);
    return 1;

}


void
start_hobble(object player)
{
    object shadow;

    setuid(); seteuid(getuid());
    shadow = clone_object("/d/Shire/bree/rooms/town/stable/club/limp_shadow");
    if (!shadow->shadow_me(player))
    shadow->remove_object();
}

void
stop_hobble(object player)
{
    player->remove_equestrian_hobble_shadow();
}


int
epoint(string str)
{
    object *oblist = ({}),
    item,
    *items,
    tp = TP;
    string *how,
    item_str;

    how = parse_adverb_with_space(str, "casually", 0);

    oblist = FILTER_LIVE(all_inventory(ENV(tp))) - ({ tp });

    if (!strlen(how[0]))
    {
        write("You"+how[1]+" point in a general direction with your " +
            "riding crop.\n");
        all(how[1]+" points in a general direction with " + HIS_HER(TP) + 
            " riding crop.");
        return 1;
    }

    if (environment(tp)->item_id(how[0]))
        item_str = "the " + how[0];
    else if (parse_command(how[0], all_inventory(environment(tp)), "%i", items))
    {
        items = NORMAL_ACCESS(items, 0, 0);
        items = FILTER_DEAD(items);

        if (!sizeof(items))
        {
            notify_fail("Point at what?  It's rude to point at people!\n");
            return 0;
        }

        item_str = COMPOSITE_DEAD(items);
    }
    else
    {
        notify_fail("Point at what?\n");
        return 0;
    }

    write("You point at "+item_str+ how[1]+" with your crop.\n");
    all(" points at "+item_str + how[1]+" with " + HIS_HER(TP) + " crop.");

    return 1;
}


int
ehelp()
{

    write("As an Equestrian, you may:\n"+
      "==========================================================\n"+
   "   emount:         Command your party to mount up.\n"+
   "   edismount:      Command your party to dismount.\n"+
   "   ecrack:         Get everyone's attention.\n"+
   "   edust:          Dust your clothing off with your riding crop.\n"+
   "   efinger:        Wish you were off riding your steed.\n"+
   "   ethwap:         Thwap someone on the head with your riding crop.\n"+
   "   eobserve:       Look someone over carefully.\n"+
   "   ehobble:        Walk like you just got off a horse.\n"+
   "   ehobble stop:   Walk normally again.\n"+
   "   esearch:        Look for your steed.\n"+
   "   epoint:         Point at something with your riding crop.\n"+
   "   emap:           Draw a map in the dust with your riding crop.\n"+
   "   eache:          Mention how sore you are after your long ride.\n"+
   "   eaccuse:        Who stepped in it?\n"+
   "   esniff:         Check your boots to see if you stepped in it.\n"+
   "   You may also use the first three letters of each command to execute that command.\n");

    return 1;

}

