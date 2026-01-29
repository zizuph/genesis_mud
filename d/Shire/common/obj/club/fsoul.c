
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

// Dunstable, 12/20/94, apologies to the Rangersoul of Elessar's :)

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Old Fogey"; }
void start_limp(object player);
void stop_limp(object player);

public mapping
query_cmdlist()
{
    return ([
      "fache"          :      "fache",
      "fbunion"       :      "fbunion",
      "fforget"       :      "fforget",
      "fgout"          :       "fgout",
      "fhelp"          :       "fhelp",
      "fjig"            :       "fjig",
      "flimp"          :       "flimp",
      "fpain"           :       "fpain",
      "fpoint"          :       "fpoint",
      "fremind"       :       "fremind",
      "frhumatism" :       "frhumatism",
      "fsmack"        :       "fsmack",
      "fstammer"    :       "fstammer",
      "fsmile"         :       "fsmile",
      "fwarn"          :       "fwarn",
    ]);
}

int
fache()
{
    write("You let everyone know why your body aches.\n");
    all(" mentions all of his aches and where each came from.");
    return 1;
}

int
fbunion()
{
    write("You hurridly remove your shoes to rub your sore bunions.\n");
    all(" rapidly removes his shoes to rub his sore bunions.");
    return 1;
}


int
fforget()
{
    write("You seem to have forgotten what you were about to say.\n");
    all(" looks as if he's forgotten what he was going to say.");
    return 1;
}


int
fgout()
{
    write("You let everyone know about your gout.\n");
    all(" moans a little about how poorly his gout is progressing.");
    return 1;
}


int
fhelp()
{

    write("Old Fogeys have the following commands at their service:\n"+
      "==========================================================\n"+
      "   fache:              Mention how painful your aches are.\n"+
      "   fgout:               Let everyone know your gout is acting up again.\n"+
      "   fhelp:               This menu.\n"+
      "   fjig:                 Dance a jig like only you know how.\n"+
      "   flimp:               Let your leg drag a bit. 'flimp stop' will make you\n"+
      "                           walk again normally.\n"+
      "   fpain:               Let a moment of pain show on your face.\n"+
      "   fpoint:              Point at something with your cane.\n"+
      "   fremind:           Remind people of things they might have forgotten.\n"+
      "   frhumatism:     Let your fingers tremble as sign of your decay. \n"+
      "   fsmile:             Let your toothless grin show!\n"+
      "   fstammer:        Speak in an unhasty way, so as to annoy the young 'uns!\n"+
      "   fwarn:              Warn your fellows about the danger of wiles.\n");

    return 1;

}

int
fjig()
{
    write("You dance a jig the way your grandfather taught you!\n");
    all(" dances a herky-jerky jig and nearly falls flat on his face!");
    return 1;
}

int
flimp(string str)
{
    if(!str)
    {
	if (TP->query_fogey_limp_shadow())
	{
	    write("You're already limping.  Use 'flimp stop' to stop.\n");
	    return 1;
	}

	write("You limp a little as you walk.\n");
	all(" begins to limp a little as he walks, he must be getting tired.");
	start_limp(TP);
	return 1;
    }

    if(str != "stop")
    {
	write("Flimp stop, perhaps?\n");
	return 1;
    }
    write("You stop limping.\n");
    all(" seems to straighten up and walk more properly.");
    stop_limp(TP);
    return 1;

}


void
start_limp(object player)
{
    object shadow;

    setuid(); seteuid(getuid());
    shadow = clone_object("/d/Shire/common/obj/club/limp_shadow");
    if (!shadow->shadow_me(player))
	shadow->remove_object();
}

void
stop_limp(object player)
{
    player->remove_fogey_limp_shadow();
}


int
fpain()
{
    int ran;
    ran = random(3);

    switch(ran)
    {
    case 0:
	write("You wince at an intense pain in your back.\n");
	all(" bends over, racked with back pain.");
	break;

    case 1:
	write("You grumble about how your shoulder hurts.\n");
	all(" grabs his shoulder in agony.");
	break;

    case 2:
	write("You mumble a bit about the pain in your hip.\n");
	all(" mumbles endlessly about pain in his hip.");
	break;

    case 3:
	write("You are racked with chest pain.");
	all(" bends over, clutching his chest in excruciating pain.");
	break;
    }
    return 1;

}

int
fpoint(string str)
{
    object *oblist = ({}),
    item,
    *items,
    tp = TP;
    string *how,
    item_str;

    how = parse_adverb_with_space(str, "grumpily", 0);

    oblist = FILTER_LIVE(all_inventory(ENV(tp))) - ({ tp });

    if (!strlen(how[0]))
    {
	write("You"+how[1]+" point in a general direction with your cane.\n");
	all(how[1]+" points in a general direction with his cane.");
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
	notify_fail("Point at what? It's rude to point at people!\n");
	return 1;
    }

    write("You point at "+item_str+ how[1]+" with your cane.\n");
    all(" points at "+item_str + how[1]+" with his cane.");

    return 1;
}



int
fremind(string str)
{
    if(!str)
    {
	write("You remind everyone about how it was in the good old days.\n");
	all(" reminds everyone how wonderful things were in his day.");
	return 1;

    }

    if(strlen(str) > 40)
    {
	write("You tried to remind everyone of something, but you forget what!\n");
	return 1;
    }

    write("You remind everyone of: "+ str + ".\n");
    all(" reminds you that "+ str + ".");
    return 1;

}

int
frhumatism()
{
    write("You wring your hands, muttering about your rhumatism.\n");
    all(" wrings his hands, complaining about rhumatism.");
    return 1;
}

int
fstammer(string str)
{
    if(!strlen(str))
    {
	write("You stammer on about nothing in particular.\n");
	all(" stammers on about nothing coherent.");
	return 1;
    }


    write("You stammer: "+ str + "...\n");
    all(" stammers: "+ str + "...");
    return 1;

}

int
fsmack()
{
    write("You smack your lips together, lost in thought.\n");
    all(" smacks his lips together loudly, annoying everyone nearby.");
    return 1;
}


int
fsmile()
{
    write("You smile an old toothless grin.\n");
    all(" smiles, revealing his broad, toothless grin.");
    return 1;
}

int
fwarn(string str)
{
    object *oblist;

    if(!str) 
    {
	write("You warn all who will listen about the dangers of wicked wiles.\n");
	all(" warns you about the danger of wicked wiles in the world today.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Warn everyone about whom?\n");
	return 1;
    }

    actor("You warn everyone present about the wiles of",oblist,".");
    target(" warns everyone nearby about your wicked wiles.",oblist);
    all2act(" warns you of the wicked wiles of",oblist,".");
    return 1;
}
