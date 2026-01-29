
/*
 * sw_occ_soul.c
 *
 * Spellweavers' Occupational Guild Soul
 * 	Farlong, 3-10-1994
 * 	(Based on examples supplied by Mylos)
 *
 */

inherit "/cmd/std/command_driver";

#include "/d/Rhovanion/common/rhun/sw/s_s/sw.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <composite.h>

#define WIZLEV_APPRENTICE 1

/* Not sure what these do- let's throw them in anyway*/
static string filter_str;
string *completed;


/*
 * Soul's name
 */

string
get_soul_id()
{
   return "spellweaver";
}


/* 
 * Tell it this is a command soul
 */

int
query_cmd_soul()
{
   return 1;
}


/* Test to see if someone is a member*/
/* Returns 1 if yes; 0 if not. */

int
is_member(mixed who)
{
    object ob;
    if (!who)
        return 0;
    if (stringp(who))
        ob = find_player(lower_case(who));
    else if (objectp(who))
        ob = who;
    else
        return 0;
    if (!ob || !interactive(ob))
        return 0;
    if (ob->query_guild_member(GUILD_NAME))
        return 1;
    return 0;
}


/*
 * List of verbs & functions (Alphabetical)
 */

mapping
query_cmdlist()
{
   return([	"distaste" : "distaste",
		"glow"     : "glow_emote", 
		"hark"     : "hark_tell",
		"members"  : "members", 
		"nymph"    : "nymph",
		"obey"     : "obey",
		"offering" : "offering",
		"submit"   : "submit", 
		"sign"     : "sign",
		"swhelp"   : "swhelp",  
		"swsigns"   : "swsigns",
		"ward"     : "ward",
		"weave"    : "weave",
	]);
}


int
weave(string str)
{
   NF("What?\n");
   if (strlen(str)) return 0;
   write("You weave your hands in strange and mysterious patterns.\n");
   allbb(" weaves "+TPOS+" hands in strange and mysterious patterns.");
   return 1;   
}   

int
distaste(string str)
{
    object *oblist;
    
    if(!strlen(str))
    {
	write("You show your distaste for all that is good and weak.\n");
	allbb(" shows "+TPOS+" distaste for the good and the weak.");
	return 1;
    }
    oblist=parse_this(str, "[at] %l");
    NF("Show distaste for whom?\n");
    if (!sizeof(oblist))
	return 0;
    target(" shows distaste for the goodness in your soul.", oblist);
    actor("You show your distaste for the goodness in", oblist);
    all2act("shows distaste for the goodness in", oblist);
    return 1;
}

int
obey(string str)
{
    object *oblist;
    
    if(!strlen(str))
    {
	write("You command that everyone should obey your wishes.\n");
	allbb(" commands that you obey "+TPOS+" wishes.");
	return 1;
    }
    oblist=parse_this(str, "[at] %l");
    NF("Command whom to obey you?\n");
    if (!sizeof(oblist))
	return 0;
    target(" commands that you obey "+TPOS+" wishes.", oblist); 
    actor("You command that your will be obeyed by", oblist);
    all2act("commands that "+TPOS+" will be obeyed by", oblist);
    return 1;
}

int
submit(string str)
{
    object *oblist;
    
    NF("You must submit to some specific person's will.\n");
    if(!strlen(str))
    {
	return 0;
    }
    oblist=parse_this(str, "[at] %l");
    NF("Submit to whom?\n");
    if (!sizeof(oblist))
	return 0;
    target(" submits to your wishes.", oblist);
    actor("You submit obediently to the will of", oblist);
    all2act("submits to the will of", oblist);
    return 1;
}

int
ward(string str)
{
   NF("What?\n");
   if (strlen(str)) return 0;
   write("You make a sign to ward off enemies.\n");
   allbb(" makes a strange sign to ward off "+TPOS+" enemies.");
   return 1;   
}

int
offering(string str)
{
    NF("What?\n");
    if(strlen(str)) return 0;
    write("You offer a devotion to the dark powers of the Spellweavers.\n");
    allbb(" offers a devotion to the dark powers that be.");
    return 1;
}

int
nymph(string str)
{
    object *oblist;
    
    if(!strlen(str))
    {
	write(break_string("You summon a small, glowing nymph, which"
	    +" hovers near your shoulder for a moment before disappearing"
	    +".\n", 75));
	allbb(break_string("summons a small, glowing nymph,  which"
	    +" hovers near "+TPOS+" shoulder for a moment before"
	    +"disappearing.", 75));
	return 1;
    }
    oblist=parse_this(str, "[at] %l");
    NF("Summon a nymph to whom?\n");
    if (!sizeof(oblist))
	return 0;
    target(break_string(" summons a small, glowing nymph, which"
	+" hovers near your shoulder for a moment before disappearing"
	+".", 75), oblist);
    actor(break_string("You summon a small, glowing nymph, which"
	+" hovers for a moment beside", 75), oblist);
    all2act(break_string("summons a small, glowing nymph, which"
	+" hovers for a moment beside", 75), oblist);
    return 1;
}

is_spellweaver(object ob)
{
    return ob->query_guild_member(GUILD_NAME);
}

int
sign(string str)
{
    object *people, *spellweavers;
    int i;
    string isee, yousee;
    
    people=FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
    spellweavers=filter(people, "is_spellweaver", TO);
    people-=spellweavers;
    
    NF("You must specify a sign to make.  Type swsigns to list them.\n");
    if(!strlen(str))
	return 0;
    
    NF("Make what spellweaver sign?\n");
   
    if (str=="greetings")
    {
	isee="of greeting.";
	yousee=isee;
    }
    else if(str=="flee")
    {
	isee="urging your fellow guildmembers to flee!";
	yousee="urging you to flee!";
    }
    else if(str=="attack")
    {
	isee="calling for an attack!";
	yousee=isee;
    }
    else if(str=="agree")
    {
	isee="signifying your agreement.";
	yousee="signifying "+TPOS+" agreement.";
    }
    else if(str=="negative")
    {
	isee="to the negative.";
	yousee=isee;
    }
    else if(str=="adieu")
    {
	isee="bidding your fellow Spellweavers `Goodbye.'";
	yousee="bidding you `Goodbye.'";
    }
    else if(str=="another")
    {
	isee="indicating that you shall see your fellow\n"
	    +"guildmembers at some other time.";
	yousee="indicating that "+TPRO+" will see you again\n"
	    +" at some point in the future.";
    }
    else if(str=="help")
    {
	isee="requesting help.";
	yousee="requesting your help.";
    }
    else return 0;
    
    if(TP->query_get_echo())
	write("You make a Spellweaver sign "+isee+"\n");
    else
	write("Ok.\n");
    if(sizeof(spellweavers))
	spellweavers->catch_msg(QCTNAME(TP)+"makes a Spellweaver sign"
	    +yousee+"\n", TP);
    if(sizeof(people))
	people->catch_msg(QCTNAME(TP)+"makes a mysterious sign.\n", TP);
    return 1;
}

int
swsigns(string str)
{
    NF("What?\n");
    if(strlen(str)) return 0;
    write("You may make the following Spellweaver signs of communication:\n"
	+"adieu\n"
	+"agree\n"
	+"another\n"
	+"attack\n"
	+"flee\n"
	+"greetings\n"
	+"negative\n");
    return 1;
}

int
swhelp(string str)
{
    NF("What?\n");
    if(strlen(str)) return 0;
    write("The following Spellweaver emotes are available to you:\n"
	+"distaste : show distaste for the good and weak.\n"
	+"draw     : draw the rune to summon a spirit and cast a spell.\n"
    +"glow     : cause your hands to glow with arcane power.\n"
	+"members  : list the Spellweavers present in the game.\n"
	+"nymph    : summon a small nymph.\n"
	+"obey     : command that others obey your wishes.\n"
	+"offering : offer a devotion to the dark forces that be.\n"
	+"submit   : submit to someone's wishes.\n"
	+"sign     : make a Spellweaver sign of communication.\n"
	+"swhelp   : this help message.\n"
	+"swsigns  : list the available communication signs.\n"
	+"ward     : draw a rune to ward off enemies.\n"
	+"weave    : weave your hands in strange and intricate patterns.\n"
	    )
		;
	    
}

int
members()
{
  string sh_name, sh_title, str;
  int i, cnt, lsize;
  object player_ob, active, *list;

  list = filter_array(users(),"is_member",this_object());
  lsize = sizeof(list);
  cnt = 0;

  tell_room(ENV(TP), QCTNAME(TP)+" sketches a rune in midair with "
    +TPOS+" finger.\n",TP);
  write(break_string("You sketch a rune of seeing in midair, and the"
	+" faces of the"
    +" following Spellweavers appear before you:\n",75));

  for (i=0; i < lsize; i++) 
  {
    str = "";
    player_ob = list[i];

    {
      /* Everyone knows one another in the guild */
      if (!(sh_name = player_ob->query_name()))
            sh_name = "";

      if (!(sh_title = player_ob->query_title()))
            sh_title = "";

      str = sh_name + " " + sh_title;

      if (player_ob->query_ghost())
        str += " <dead>";

      /* Mark invisible players for wizards */
      if (player_ob->query_invis() &&
        this_player()->query_wiz_level() >= WIZLEV_APPRENTICE)
      str = "(" + str + ")";
      cnt++;      /* Increment for another member */

      this_player()->catch_msg("--> " + str + "\n");
    }
  }
  write("There are currently "+cnt+" Spellweavers in the game.\n");
  return 1;
}


/* The Spellweaver "tell"-- copied from an example of Quetzl's with his help */

int hark_tell(string str)
{
    string name, message;
    object ob;

	NF("Hark what?\n");
	if(!parse_command(str,TP,"%w %s",name,message))
        return 0;

    ob = find_player(name);
    
    NF("You couldn't locate that person.\n");
    if(!ob)
         return 0;

    NF("You can't send a hark message to a non-member!\n");
    if (!(ob->query_guild_member(GUILD_NAME)))
        return 0;
NF("That person is in a state of business and cannot receive your message.\n");
if((ob->query_prop(WIZARD_I_BUSY_LEVEL))&156)
    return 0;
    ob->catch_msg(QCTNAME(TP)+" sends "+TPOS+" thoughts to you"
	+" on a dark cloud, saying:\n"+
        message + "\n");
    if (TP->query_get_echo()) 
	TP->catch_msg("You send these thoughts to "+QTNAME(ob)+":\n"
	    +message+"\n");
    else
	write("Ok.\n");
    if(!(TP->query_wiz_level()))
    TP->set_mana(TP->query_mana()-10);
    return 1;
}

int
glow_emote(string str)
{
   NF("What?\n");
   if (strlen(str)) return 0;
   write("Your hands glow briefly with arcane power.\n");
   allbb("'s hands glow briefly with arcane power.");
   return 1; 
}
