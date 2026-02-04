/* rumor_monger.c */
// revisions:  Lilith Apr 2022: Updated combat chats to reflect that 
//       killing the npc will have consequences.

#pragma save_binary

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <cmdparse.h>
#include <wa_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild: Rumor Monger.  Players can buy the terminally soused
 * minstrel a drink or two to loosen his tongue.  If asked he will give a list 
 * of the last known location (domain) that a minstrel was reputed to be in.
 * 
 * In the future the Rumor Monger may be used to give quest hints.
 * 
 * Jorl 5/93
 * 
 * Added the alco triggering + the hint giving routines that
 * tells about a minstrel's whereabouts.
 * Mortricia 6/93
 */

/* Globals: */
object asker;
int talking_flag = 0;

/* Prototypes */
void multi_com(string *com);
void drink_it(object ob, object from);
void drop_it(object ob, object from);
void delay_command(string str);
string *display_all();
string last_info(int day, string name);
void stop_talking();

int query_guild_member(string str)
{
    if (str == GUILD_NAME)
    {
	return 1;
    }
    else
    {
	return 0;
    }
}

string query_special_title()
{
    return "Rumor Monger of the Minstrels";
}

void create_monster()
{
    object ins, book, shadow;
    
    if (!IS_CLONE)
	return;
    
    set_name("rumour monger");
    add_name("monger");
    add_adj(({"ancient","weathered"}));
    set_race_name("elf");
    set_long(BS("This sleepy-eyed minstrel is a fixture in the banquet hall. "
         + "His adventuring days long past, he devotes most of his time now to "
         + "drinking and collecting rumours about the doings of Minstrels across "
         + "the world. After a decade or so it was decreed that from now on this "
         + "should be his permanent vocation, and the wise old fellow was named "
         + "official Rumour Monger of the Minstrels. A high honour indeed! Perhaps "
         + "he knows something of your comrades...\n"));
  
    set_cact_time(1);
    add_cact("say You keep fighting me and you'll be punished!");
    add_cact("say My blood on your hands will get you banished from the "+
        "Mintrels!");
    add_cact("say I'm a minstrel, you fool! If you kill me you will regret it.");
    add_cact("say The Muses will punish you for this!");
  
    set_stats(({30,30,99,20,20,30}));
    set_hp(9999);
    set_mana(9999);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 45000);
    add_prop(CONT_I_HEIGHT, 150);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop("_do_i_tell_rumours",1);
    book = clone_object(GUILDOBJ+"song_book");
    book->set_owner(TP());
    book->move(TO());
    book->reset_object();
    shadow = clone_object(GUILDOBJ+"m_shadow");
    shadow->shadow_me(TO(), "layman", "cleric", GUILD_NAME);
    TO()->set_muse(2);
    ins = clone_object(GUILDOBJ+"instrument");
    ins->set_name("lute");
    ins->move(TO());
    ins->do_things();
}

void init_living()
{
   ::init_living();
   add_action("do_ask", "ask");
}

void enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
    if (function_exists("query_alco_amount", ob))
    {
      if (ob->query_alco_amount() > 0)
      {
	set_alarm(3.0, 0.0, &drink_it(ob, from));
      }
      else
      {
	set_alarm(3.0, 0.0, &drop_it(ob, from));
      }
    }
    else
    {
      if (!function_exists("set_owner", ob) &&
	  !function_exists("do_things", ob))
      {
	set_alarm(3.0, 0.0, &drop_it(ob, from));
      }
    }
}

void drop_it(object ob, object from)
{
    command("drop " + ob->query_name());
    if (from && environment(TO()) == environment(from))
    {
	command("stare at " + from->query_real_name());
    }
}

void drink_it(object ob, object from)
{
    string name;
   
    if (from && environment(TO()) == environment(from))
    {
	name = from->query_real_name();
    }
   
    if (strlen(name))
    {
	multi_com(({"drink " + ob->query_name(),
		      "burp",
		      "say Ahhh! That was really good!",
		      "whisper " + name + " I owe you one favour."}));
	asker = from;
    }
    else
    {
	multi_com(({"drink " + ob->query_name(),
			"burp"}));
    }
}

int do_ask(string str)
{
    int days;
    object *ob, who;
    string s1, s2, s3;
    string race, path, pronoun, poss, domain;
    string dom_mess;
    string *names;
   
    if (!str) return 0;
   
    if (sscanf(str, "%s about %s", s1, s2) != 2) {
	if (sscanf(str, "%s %s", s1, s2) != 2) return 0;
    }
    ob = FIND_STR_IN_OBJECT(s1, environment(TO()));
    if (sizeof(ob) == 0 || sizeof(ob) >= 2) return 0;
    if (ob[0] != TO()) return 0;
   
    write("You ask the "+short()+" about "+s2+".\n");
    say(QCTNAME(TP()) + " asks the "+short()+" about "+capitalize(s2)+".\n");
   
    if (!MEMBER(TP())) {
	multi_com(({"say Hey! You're not a Minstrel!", "shrug coldly"}));
	return 1;
    }

    if (talking_flag)
    {
	write("He holds up a finger, as if to tell you to wait a moment.\n");
	return 1;
    }
    
    if (TP() != asker
	&& TP()->query_special_title(TP()->query_real_name()) == 0)
    {
	multi_com(({"shrug", "say I am so thirsty...", "sigh"}));
	return 1;
    }
    if (lower_case(s2) == "minstrels"
	|| s2 == "the minstrels"
	|| s2 == "the Minstrels"
	|| s2 == "comrades"
	|| s2 == "my comrades") {
	command("say Let me see... Minstrels in the world are:");
	multi_com(display_all());
	asker = 0;
	return 1;
    }
    
    who = find_living(lower_case(s2));
    if (!who || !MEMBER(who)) {
	names = explode(read_file(LOGFILE), ":");
	if (member_array(capitalize(s2), names) >= 0) {
	    who = "/secure/master"->finger_player(lower_case(s2));
	    if (!who)
	    {
		multi_com(({"ponder",
			      "say I really don't know.",
			      "shrug"}));
		asker = 0;
		return 1;
	    }
	    days = time() - who->query_login_time();
	    days = days/3600/24;
	    multi_com(({"ponder",
			    "say Let me see...",
			    last_info(days, s2),
			    "smile"}));
	    who->remove_object();
	    asker = 0;
	    return 1;
	}
	multi_com(({"ponder",
			"say Who on earth is " + capitalize(s2) + "?",
			"shrug"}));
	return 1;
    }
    race = who->query_race_name();
    pronoun = who->query_pronoun();
    poss = who->query_possessive();
    if (pronoun == "he") {
	s3 = "him";
    }
    else if (pronoun == "she")
    {
	s3 = "her";
    }
    else
    {
	s3 = "it";
    }
    if (environment(who) == environment(TO())) {
	multi_com(({"point at " + who->query_real_name(),
			"giggle"}));
	asker = 0;
	return 1;
    }
    path = MASTER_OB(environment(who));
    if (sscanf(path, "/d/%s/%s", domain, s1) != 2) {
	multi_com(({"ponder",
		    "say Let me see... " + capitalize(pronoun)
		  + " is " + LANG_ADDART(race) + ". Isn't "
		  + pronoun + "?",
		      "say But I have no idea where " + pronoun +
			  " can be.",
			  "shrug",
			  "say I haven't seen " + s3 + " here lately."}));
    }
    else
    {
	if (domain == "Terel")
	{
	    dom_mess = "Not far from here in other words.";
        } else if (domain == "Earthsea")
	{
	    dom_mess = "It is a gentle land, full of herbs. ";
        } else if (domain == "Krynn")
	{
	    dom_mess = "I hear there's a war going on there.";
        } else if (domain == "Ansalon")
	{
	    dom_mess = "War-torn and full of dragons, that place is.";

        } else if (domain == "Calia")
	{
	    dom_mess = capitalize(pronoun) + " went there probably to" +
		" kill off some krougs. What else can you " +
		    "do there?";
        } else if (domain == "Emerald")
	{
	    dom_mess = "It sure is bright there " +
		"in that God-forsaken place.";
        } else if (domain == "Genesis")
	{
	    dom_mess = "You know, the place where everything began.";
        } else if (domain == "Sparkle")
	{
	    dom_mess = "Probably not there for long... so many boats "+
                "to catch.";
        } else if (domain == "Cirath")
	{
	    dom_mess = "I wonder what kind of audience " + pronoun + 
                " is finding in that God-forsaken place.";
        } else if (domain == "Liwitch")
	{
	    dom_mess = "Though I doubt that any mortal ever will "+
		"walk there.";
        } else if (domain == "Shire")
	{
	    dom_mess = "It's the land of hobbits.";
        } else if (domain == "Gondor")
	{
	    dom_mess = "It's the land of the great cities.";
        } else if (domain == "Raumdor")
	{
	    dom_mess = "Don't ask me why "+ pronoun +" is there, though.";
        } else if (domain == "Khalakhor")
	{
	    dom_mess = "There are quite a few islands though, so who "+
                "knows where...";
        } else if (domain == "Faerun")
	{
	    dom_mess = "But probably not for long... there don't seem "+
                "to be many people there.";
        } else if (domain == "Avenir")
	{
	    dom_mess = "The people there seem to appreciate a good Minstrel.";
        } else if (domain == "Kalad")
	{
	    dom_mess = "I have never been there though.";

        } else
	{
	    dom_mess = "It's a place I never heard of before.";
        }
	multi_com(({"ponder",
	       "say Let me see... " + capitalize(pronoun) +
	       " is " + LANG_ADDART(race) + ". Isn't " +
               pronoun + "?",
               "say Now, where is " + pronoun + "?",
               "ponder",
               "say Yes! Now I remember.",
               "say I heard a rumour that " + pronoun +
               " might be in a land called " + domain + ".",
               "say " + dom_mess,
               "giggle"}));
    }
    asker = 0;
    return 1;
}

void multi_com(string *com)
{
   int i, n;
   float delay;

   talking_flag = 1;
   n = sizeof(com);
   if (!n) return;

   delay = 2.0;
   for (i=0; i<n; i++)
   {
      set_alarm(delay, 0.0, &delay_command( com[i] ));
      delay += 4.0;
   }
   set_alarm(delay, 0.0, stop_talking);
}

void stop_talking()
{
    talking_flag = 0;
}

void delay_command(string str)
{
   TO()->command(str);
}

string * display_all()
{
    object *member;
    int i, n;
    string name, title;
    string *s;
   
    s = ({});
    member = ON_LINE();
    n = sizeof(member);
    for (i=0; i<n; i++) {
	name  = member[i]->query_name();
	title = member[i]->query_title();
	s += ({"say "+name+", "+title});
    }
    s += ({"scratch"});
    s += ({"say I think that's all."});
    return s;
}

string last_info(int day, string name)
{
    string s;
    if (day == 0) {
	s = "say I think I saw "+capitalize(name)+" earlier today.";
    } else if (day == 1) {
	s = "say I think I saw "+capitalize(name)+" yesterday.";
    } else if (day <= 6) {
	s = "say I think I saw "+capitalize(name)+" some days ago.";
    } else if (day < 30) {
	s = "say I think I saw "+capitalize(name)+" some weeks ago.";
    } else {
	s = "say I haven't seen "+capitalize(name)+" this last month.";
    }
    return s;
}

void attacked_by(object attacker)
{
   // Break the peace, forfeit your weapons.
    ::attacked_by(attacker);
   (GUILD+"office")->purge_tickets(attacker);
   command("say You've broken the peace! Whatever you checked in is forfeit now!");
}


public void do_die(object killer)
{
 //   string logfile, *loglines;
 //   int i;
    
    seteuid(getuid());
    if (MEMBER(killer))
    {
	killer->CM("You deal the fatal blow, and stand triumphant over the "
	+ "fallen body of the ancient minstrel. Yet the victory seems curiously hollow, "
	+ "and your "+ present("minstrel_instrument", killer)->query_name() 
	+ " slips from your suddenly "
	+ "numb fingers. \n");
//  Removed by Lilith, April 2022
//       write_file(BANISHDIR+killer->query_real_name()+"_banished",
//		   "Banished forever from the Minstrels.\n");
//	killer->muse_banish();
        killer->muse_punish();
    }
    (GUILD+"office")->rm_died(killer);
    (GUILD+"tower_roof")->rm_died();
    ::do_die(killer);
}
