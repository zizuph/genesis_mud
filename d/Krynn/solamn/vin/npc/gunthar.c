/* Gunthar, the Guildmaster of the Solamnian Knights.
 * modified by Teth on March 20, 1996
 * now includes add_acts and add_ask
 * modified March 20, 1996 to include triggers
 * triggers changed to use emote_hook 16 Jun 96 [Grace]
 */

#include "../knight/guild.h"
#include <macros.h>

inherit M_FILE
inherit "/std/act/action";

#include "killer.h"

#define MY_OWN_ROOM         VROOM + "gunth_room"
#define LOG                 VLOG
#define QUESTLOG           "/d/Krynn/common/log/quests/"
#define BAD_GUY_SAVE_FILE  LOG + "bad_guy_save_file"

object para; /* The paralyze object in case gunthar is bound and gagged */

int react_bless(object who, string adverb);
int react_clasp(object who, string adverb);
int react_bow(object who, string adverb);
int react_kiss(object who, string adverb);
string read_sign_response();
EMOTE_HOOK

string
query_race_name()
{
    return (calling_function() == "query_presentation" ? "Sancristan" : "human");
}

string
normal_long()
{
    return "This human is powerfully built. He has a grand Solamnic " +
    "moustache that flows down his face. His stern eyes seem " +
    "to penetrate your very being, but you can tell that there is " +
    "a gentleness underneath. His rugged skin betrays the fact " +
    "that he is a seasoned warrior, who has seen much and done " +
    "even more.\n"+
    "His tunic is decorated with the symbol of the Order of the Rose.\n";
}

string
gagged_long()
{
    return "You recognize a member of the Solamnian " +
    "Knights. He is gagged and bound!\n";
}

void
create_krynn_monster()
{
    string str;

    set_name("gunthar");
    set_living_name("gunthar");
    set_race_name("human");
    set_title("uth Wistan, the Lord Justice of Solamnia");
    set_long("@@normal_long@@");
    set_adj("noble");
    add_adj("intense");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(CONT_I_HEIGHT, 182);
    add_prop(CONT_I_WEIGHT, 45000);
    set_alarm(5.0,0.0,
	      "add_cmdsoul", "/d/Krynn/solamn/vin/knight/obj/solamnian_soul");
    set_alarm(5.5, 0.0, "add_cmdsoul", "/d/Krynn/solamn/vin/obj/kattack_special");
    set_alarm(6.0,0.0,"update_hooks");
    set_tell_active(1);

    seteuid(getuid(TO));
    set_act_time(5);
    add_act("@@announce_bad_guy@@");
    add_act("emote tweaks the end of his orange-red moustache.");
    add_act("say Vinas Solamnus was the founder of the Knights of Solamnia!");
    add_act("say The Knights of Solamnia are led by the Conclave.");
    add_act("emote pats the cushion of the chair next to him with " +
	    "his hand, implying that the chair is comfortable.");
    add_act("emote stares at you with intensity, seemingly reading " +
	    "your soul.");
    add_act("emote solemnly declares: Est Sularus oth Mithas!");
    add_act("say The Knights of Solamnia are the finest body of justice and " +
	    "honour throughout the land.");
    add_act("emote examines letters regarding the rumours and hearsay that " +
	    "plague Solamnia.");
    add_act("emote wonders if peace will ever come to Solamnia.");
    add_act("say Glory be to Paladine!");
    add_act("emote sighs and wistfully utters: How I wish I could go back " +
	    "to my castle and enjoy some peace and quiet. Alas, it's not to " +
	    "be.");
    add_act("say I know the three Orders well, having spent time in " +
	    "each.");
    add_act("emote rubs his chin thoughtfully as he contemplates honour.");

    set_default_answer("For some reason, you are ignored.\n");

    add_ask(" [about] 'conclave'", "say Currently, the Conclave of "+
	    "the Knights of Solamnia are:\n"+
	    (ADMIN->query_conclave("crown") != "" ? 
		" - "+ADMIN->query_conclave("crown")+
		" the High Warrior of the Crown\n" : "")+
	    (ADMIN->query_conclave("sword") != "" ? 
		" - "+ADMIN->query_conclave("sword")+
		" the High Clerist of the Sword\n" : "")+
	    (ADMIN->query_conclave("rose") != "" ?
		" - "+ADMIN->query_conclave("rose")+
		" the High Justice of the Rose\n" : "")+
            (ADMIN->query_grandmaster() != 0 ?
	        " - "+C(ADMIN->query_grandmaster())+
		" the Grandmaster of the Knights of Solamnia\n" : ""), 1);
    add_ask(" [about] 'grandmaster'",
       "say "+(ADMIN->query_grandmaster() != 0 ? "The "+
		    "current Grandmaster of the Knights of Solamnia is "+
		    C(ADMIN->query_grandmaster())+
		    "." : "There is no Grandmaster presently."), 1);
    add_ask(" [about] 'crown'", "say The Order of the Crown " +
	    "is currently headed by "+ADMIN->query_conclave("crown")+
	    ". This Order represents " +
	    "the virtues of loyalty and obedience. Habbakuk is the " +
	    "patron god.",1);
    add_ask(" [about] 'sword'","say The Order of the Sword " +
	    "is currently headed by "+ADMIN->query_conclave("sword")+
	    ". Kiri-Jolith is the patron " +
	    "god of this Order that represents courage and heroism.",1);
    add_ask(" [about] 'rose'", "say The Order of the Rose " +
	    "is led by the High Justice, "+ADMIN->query_conclave("rose")+
	    ". Paladine is the patron " +
	    "god of this Order that values honour and justice.",1);
    add_ask(" [about] 'vingaard'", "say Vingaard Keep " +
	    "has never fallen to the forces of evil. And by the gods, it " +
	    "never will!",1);
    add_ask(" [about] 'task' / 'quest'", read_sign_response,1);
    add_ask(" [about] 'honor' / 'honour'","say Honour is near " +
	    "impossible to define. We've made an attempt at it with the " +
	    "Oath and the Measure.",1);
    add_ask(" [about] 'oath'", "say My Honour is My Life.",1);
    add_ask(" [about] 'measure'", "say It is " +
	    "thirty-seven volumes of laws and rules. This is where " +
	    "the Knights have attempted to define Honour.",1);
    add_ask(" [about] 'order' / 'orders'", "say The three Orders of the " +
	    "Knights of Solamnia are Crown, Sword, and Rose.",1);
    add_ask(" [about] 'knight' / 'knights'", "say The " +
	    "Knights of Solamnia are a body of warriors, bound " +
	    "together in holy unity with the purpose of defending " +
	    "the weak and impoverished and those in need, fighting " +
	    "injustice and stemming the tide of evil. Several times "+
	    "in our history, members of the Knights have been " +
	    "called on to defend the world.",1);
    add_ask(" [about] 'huma'","say Some " +
	    "now say that Huma Dragonbane never existed. But I " +
	    "still believe in the story...",1);
    add_ask(" [about] 'rumour' / 'rumours' / 'rumor' / 'rumors'", "say I " +
	    "won't bother you with that.",1);
    add_ask(" [about] [vinas] 'solamnus'", "say " +
	    "A great man. He led an uprising against a cruel king, " +
	    "after seeing the pain the king inflicted, even though " +
	    "he was previously in the service of that king.",1);
    add_ask(" [about] 'paladine' / 'habbakuk' / 'kiri-jolith'", "say One " +
	    "of the three patron gods of the Knights " +
	    "of Solamnia. Another is better able to answer your questions " +
	    "on this matter, or perhaps you could visit our library.",1);
    add_ask(" [about] 'solamnia'","say Solamnia occupies the " +
	    "northwest portions of this continent. It was named in honour of " +
	    "Vinas Solamnus.",1);

    add_ask(" [about] 'scroll'", "@@war_scroll", 1);


    add_emote_hook("kneel", 1.0, react_bless);
    add_emote_hook("clasp", 1.0, react_clasp);
    add_emote_hook("bow", 1.0, react_bow);
    add_emote_hook("kiss", 1.0, react_kiss);

    default_config_mobile(90);
    set_all_attack_unarmed(90, 90);
    set_all_hitloc_unarmed(90);

    set_alignment(1200);
    set_knight_prestige(-16);

    if (IS_CLONE)
      set_alarm(1.0,0.0,"sit_me");

}

/*
 * Function name:	war_scroll
 * Description:
 * Returns:			a command string
 */
string
war_scroll()
{
	object war_scroll;

	if ( (TP->query_knight_sublevel() == 11) || TP->query_wiz_level() )
	{
		war_scroll = clone_object(VOBJ + "war_scroll");
		war_scroll->move(TP);

		TO->command("say I give you this scroll in confidence of your loyalty "
					+ "to the Knighthood, if you pass it on make sure you do not "
					+ "fail my honour.");
		write("You recieve an honoury scroll of confidence!");

		if ( TP->query_wiz_level() )
			write("\n\n\n\t\tDO NOT GIVE THE SCROLL TO ANY MORTALS!! \n\n\n");

		return "kdeclare";
	}
	else
		return "shrug";
}

void
add_introduced(string who)
{
    if (present(who, environment(this_object())))
    {
	command("smile solemnly " + who);
	set_alarm(1.0,0.0,"command","say Hail " + capitalize(who) +
		  "! May the light of Paladine shine on us!");
	set_alarm(1.5,0.0,"command","introduce me");
    }
}


int
react_bow(object who, string adverb)
{
    set_alarm(2.0,0.0,"return_bow", who->query_real_name());
    return 1;
}


return_bow(string who)
{
    object obj;

    if (obj = present(who, environment()))
    {
	command("stand");
	set_alarm(1.0,0.0,"command","kbow " + who);
	set_alarm(2.0,0.0,"command","sit");
	return "";
    }
}

int
react_kiss(object who, string adverb)
{
    set_alarm(2.0,0.0,"return_kiss", who->query_real_name());
    return 1;
}


return_kiss(string who)
{
    object obj;

    if (obj = present(who, environment()))
    {
	command("blush");
	command("say Now now! None of that in here! " +
	  "This is a place for warriors, not lovers, " +
	  capitalize(who)+"!");
	return "";
    }
}


int
react_bless(object who, string adverb)
{
    set_alarm(1.0,0.0,"return_bless", who->query_real_name());
    return 1;
}


return_bless(string who)
{
    object obj;

    if (obj = present(who, environment()))
    {
	command("khonour " + who);
	set_alarm(1.0,0.0,"command","say Go with the blessings of " +
	  "Paladine, Kiri-Jolith, and Habbakuk, "+
	  capitalize(who)+"!");
	return "";
    }
}

int
react_clasp(object who, string adverb)
{
    set_alarm(1.0,0.0,"return_clasp", who->query_real_name());
    return 1;

}


return_clasp(string who)
{
    object obj;
    if (obj = present(who, environment()))
    {
	command("kclasp " + who);
	set_alarm(1.0,0.0,"command","say Well met, Kharas! It is " +
	  "friendly Knights like you, " +capitalize(who)+
	  ", who give the Knighthood a good reputation!");
	set_alarm(2.0,0.0,"command","smile friendly");
	return "";
    }
}

void
sit_me()
{
    command("sit");
}

public int
query_knight_level()
{
    return 5;
}

public int
query_knight_sublevel()
{
    return 10;
}

public void
add_good_guy(string who, string where, string what)
{
    write_file(BAD_GUY_SAVE_FILE,where + "%%" + who + "%%" +
      what + "%%commended%%" + time() + "\n");
}

public void
add_bad_guy(string who, string where, string what, string how)
{
    write_file(BAD_GUY_SAVE_FILE,where + "%%" + who + "%%" +
      what + "%%punished%%" + time() + "\n");
}

string
get_random_entry_from_file()
{
    string *lines;
    string txt = read_file(BAD_GUY_SAVE_FILE);
    if (!txt)
	return 0;
    lines = explode(txt,"\n");
    return lines[random(sizeof(lines))];
}

void
remove_entry_from_file(string entry)
{
    int i;
    string *lines;
    string txt = read_file(BAD_GUY_SAVE_FILE);
    if (!txt)
	return 0;
    lines = explode(txt,"\n");
    rm(BAD_GUY_SAVE_FILE);
    for(i=0;i<sizeof(lines);i++)
	if (lines[i] != entry)
	    write_file(BAD_GUY_SAVE_FILE,lines[i]);
}

string
announce_bad_guy()
{
    string str;
    mixed entry = get_random_entry_from_file();
    mixed parts;
    if (!entry)
	return "";
    parts = explode(entry,"%%");
    if (atoi(parts[4]) + SECONDS_IN_2_DAYS < time())
    {
	remove_entry_from_file(entry);
	return "";
    }
    str =  ({"I have heard from " + parts[0] + " that " +
      parts[1] + " has " + parts[2] + ".",
      "It has come to my attention from " + parts[0] +
      " that " + parts[1] + " has " + parts[2] + ".",
      "I've received a report from " + parts[0] + " that " +
      parts[1] + " has " + parts[2] + ".",})[random(3)];
    str += " This should be " + parts[3] + " by the conclave.";
    command("whisper to " + L((ADMIN)->query_conclave("rose")) + " " + str);
    command("whisper to " + L((ADMIN)->query_conclave("sword")) + " " + str);
    command("whisper to aridor " + str);
    command("whisper to morrigan " + str);
    return "whisper to " + L((ADMIN)->query_conclave("crown")) + " " + str;
}

void
init_living()
{
    ADA("free");
    ADD("free","untie");
    ::init_living();
}


int
free(string str)
{
    string dummy = "";
    NF("What?\n");
    if (!str)
	return 0;
    if (query_long() != "@@gagged_long@@")
	return 0;
    NF(capitalize(query_verb()) + " who?\n");
    if (lower_case(str) != "gunthar")
	return 0;
    NF("You cannot reach Gunthar, there is still an enemy around.\n");
    if (present("draconian",E(TO)) || present("kitiara",E(TO)) ||
      present("skie",E(TO)))
	return 0;

    set_short(0);
    set_long("@@normal_long@@");
    set_m_in("arrives.");
    set_m_out("leaves");
    para->remove_object();
    command("thank " + TP->query_real_name());
    command("say I am very proud of your valor and knightly attitude!");

    if (!TP->test_bit("Krynn",2,10))
    {
	if (TP->query_knight_level())
	    TP->catch_msg("Gunthar lays a hand on your head and you feel " +
	      "rewarded and more experienced!\n");
	else
	    TP->catch_msg("Gunthar lays a hand on your head and you feel " +
	      "more experienced!\n");
	seteuid(getuid(TO));
	TP->set_bit(2,10);
	TP->add_exp(1000);
	TP->change_prestige(2500,0);
	write_file(QUESTLOG + "free_gunthar",extract(ctime(time()), 4, 15)
	  + " " + capitalize(TP->query_real_name()) + "\n");
    }
    else
    {
	if (TP->query_knight_level())
	    TP->catch_msg("Gunthar lays a hand on your head and you feel " +
	      "rewarded!\n");
	TP->change_prestige(3500,0);
	write_file(LOG + "free_gunthar",extract(ctime(time()), 4, 15)
	  + " " + capitalize(TP->query_real_name()) + "\n");
    }
    command("smile");
    if (E(TO) != find_object(MY_OWN_ROOM))
    {
	command("say I will return to my proper place now.");
	command("emote leaves.");
	move(MY_OWN_ROOM);
	command("emote arrives.");
	command("sit");
    }
    //set_short("Gunthar");
    return 1;
}

string
read_sign_response()
{
    if(file_name(environment(TO))=="/d/Krynn/solamn/vin/room/gunth_room")
    {
        return "say Read the sign for instructions.";
    }
    return "say Now is not the right time for such matters!";
}
    
void
capture_me()
{
    set_short(0);
    set_long("@@gagged_long@@");
    set_m_in("is dragged in by the draconian.");
    set_m_out("is dragged");
    para = clone_object("/std/paralyze");
    para->move(TO);
}
