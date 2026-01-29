#include "../guild.h"

inherit KOT_SOUL_DIR + "kot_soul";

#include <cmdparse.h>
#include "/d/Emerald/sys/skills.h"
#include <files.h>
#include <macros.h>

#define tpos this_player()->query_possessive()
#ifndef TP
#define TP this_player()
#endif

#define HIS_OR_THEIR ( (sizeof(oblist)>1) ? "their" : oblist[0]->query_possessive())
#define HIM_OR_THEM ( (sizeof(oblist)>1) ? "them" : oblist[0]->query_objective())

mapping
query_caste_cmdlist()
{
    return ([
             "ktbless"        : "bless",
             "ktcomfort"      : "comfort",
	     "ktcurse"        : "curse",
             "ktenlighten"    : "enlighten",
             "ktgrip"         : "grip",
	     "ktpray"         : "pray",
             "ktconvey"       : "convey",
	     "ktclasp"        : "clasp",
           ]);
}

void
create_caste_soul()
{
    read_help_dir(KOT_HELP_DIR, "cleric_help");
}

int
bless(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	notify_fail("Bless whom?\n");
	return 0;
    }

    oblist = parse_this(str,"[the] %l");
    
    if (!sizeof(oblist))
    {
	notify_fail("Who do you wish to bless?\n");
	return 0;
    }
    
    target(" lays "+TP->query_possessive()+" hands upon your "+
	   "forehead, gently whispering something in ancient elven "+
	   "which, somehow, you know to be a blessing.", oblist);
    actor("You lay your hands upon", oblist,", whispering the ancient "+
	  "elven prayer to invoke the blessing of Telan-Ri.");
    all2act(" lays "+TP->query_possessive()+" hands upon",oblist," whispering "+
	    "something in ancient elven.");
    return 1;
}

int
curse(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	notify_fail("Curse whom?\n");
	return 0;
    }

    oblist = parse_this(str,"[the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Whom do you wish to curse?\n");
	return 0;
    }
    
    target(" thrusts "+TP->query_possessive()+" fist at you, shaking it "+
	   "angrily as "+TP->query_pronoun()+" curses you and your "+
	   "evil ways!", oblist);
    actor("You thrust your fist at",oblist,", shaking it at "+
	  HIM_OR_THEM+", cursing "+HIM_OR_THEM+" for "+
	  HIS_OR_THEIR+" evil ways!");
    all2act(" thrusts "+TP->query_possessive()+" fist at",oblist,", shaking "+
	    "it angrily as "+TP->query_pronoun()+" curses "+
	    HIM_OR_THEM+" for "+HIS_OR_THEIR+" evil ways!");
    return 1;
}

int
comfort(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	notify_fail("Comfort whom?\n");
	return 0;
    }

    oblist = parse_this(str,"[the] %l");
    if (objectp(oblist))
	oblist = ({ oblist });
    if (!sizeof(oblist))
    {
	notify_fail("Whom do you wish to comfort?\n");
	return 0;
    }
    if (sizeof(oblist)>1)
    {
	notify_fail("You can't comfort more than one person at a "+
		    "time.\n");
	return 0;
    }
    
    oblist[0]->catch_msg(QCTNAME(TP)+" lays a gentle hand upon "+
			 "your shoulder, offering you "+
			 "comfort from your many troubles.\n");
    actor("You lay your hand upon",oblist,"'s shoulder, offering "+
	  oblist[0]->query_objective()+" reassurance and comfort "+
	  "from "+oblist[0]->query_possessive()+" troubles.");
    all2act(" lays "+TP->query_possessive()+" hand upon",oblist,"'s "+
	    "shoulder, offering "+oblist[0]->query_objective()+" "+
	    "reassurance and comfort.");
    return 1;
}

int
el_filter(object ob)
{
    if ( (ob->query_alignment()>0) && (!ob->query_kot_member()) &&
         (ob->query_race_name()=="elf"))
       return 1;
    else return 0;
}

int
enlighten(string str)
{
    object *oblist;
    object *oblist2;

    if (!strlen(str))
    {
	notify_fail("Enlighten whom?\n");
	return 0;
    }
    
    oblist = parse_this(str,"[the] %l");
    oblist2 = filter(oblist, el_filter);
    if (!sizeof(oblist2))
    {
	notify_fail("You do not sense anyone in need of enlightenment.\n");
	return 0;
    }
    
    
   target(" attempts to enlighten you to the teachings of Telan-Ri.",
          oblist);
    actor("You attempt to enlighten",oblist," to the teachings of "+
	  "Telan-Ri.");
    all2act(" attempts to enlighten", oblist," to the teachings of "+
	    "Telan-Ri.");
    return 1;
}


int
grip(string str)
{
    write("You grip your hands together in silent fury.\n");
    all(" grips "+tpos+" hands together in silent fury.");
    return 1;
}

int
pray(string str)
{
    if (TP->query_attack())
    {
	notify_fail("You cannot pray while in combat.\n");
	return 0;
    }
    
    write("You fold your hands before your chest, touch the tips of "+
	  "your fingers to your forehead and whisper a prayer to "+
	  "Telan-Ri in the ancient tongue.\n");
    say(QCTNAME(TP)+" folds "+TP->query_possessive()+" hands before "+
	    TP->query_possessive()+" chest, touching the tips of "+
	    TP->query_possessive()+" fingers to "+TP->query_possessive()+
	    " forehead, whispering something in prayer.\n");
    return 1;
}

int
clasp(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	notify_fail("Shake hands with whom?\n");
	return 0;
    }

    oblist = parse_this(str,"[hands] [with] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("You can't find anyone to shake hands with.\n");
	return 0;
    }

    if (sizeof(oblist)>1)
    {
	notify_fail("You can't shake hands with more than one person "+
		    "at a time.\n");
	return 0;
    }

    actor("You clasp",oblist,"'s hand within yours, giving "+
	  oblist[0]->query_objective()+" a firm, encouraging handshake.");
    target(" clasps your hand within "+TP->query_possessive()+", giving "+
	   "you a firm, encouraging handshake.", oblist);
    all2act(" clasps",oblist,"'s hand within "+TP->query_possessive()+", "+
	    "giving "+oblist[0]->query_objective()+" a firm, encouraging "+
	    "handshake.");
    return 1;
}

int
revoke(string str)
{
    if (!strlen(str) || (str != "my devotion"))
    {
	notify_fail("Revoke your devotion to Telan-Ri?\nIf you are "+
		"sure, 'ktrevoke my devotion', but there is no going back!\n");
	return 0;
    }

    write("You lower your eyes and revoke your devotion to Telan-Ri.\n"+
	  "Suddenly, your soul feels much emptier.\n");
    say(QCTNAME(TP)+" lowers "+TP->query_possessive()+" eyes and revokes "+
	  TP->query_possessive()+" devotion to Telan-Ri.\n");
    this_player()->remove_kot_member();
    return 1;
}
