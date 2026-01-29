#include "../defs.h"
inherit CEREMONY + "ceremony";

#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>

public string sph, *flame_msgs = ({
	"The flame flickers darkly.\n",
	"The flame writhes and twists, a living entity "+
		"whose blue-black fingers fan the ceiling.\n"+
	"Red-glowing sparks shower the area.\n",
	"Wavering sinuously, the flame casts long shadows "+
		"into the mist.\nThe shadows seem to move of their "+
		"own accord, as if alive.\n",
	"The flame seems to gather force,\nIt sends a long, "+
		"blue tendril flickering toward you.\n",
	"The mist gathers about the flame in a soft halo.\n"
});

/* Bathed within the last 1/2 hour? */
#define RECENTLY_BATHED(who) \
    ((time() - who->query_prop(CLEANSED)) < (60 * 30))


public void
ceremony_tell(void)
{
    if (valid_ceremony())
    {
	tell_room(ENV(TO), one_of_list(flame_msgs));
	set_alarm(5.0 + itof(random(20)), 0.0, ceremony_tell);
    }
}

public void
create_ceremony()
{
    /* 0 = Master of Ceremony */
    /* 1 = Target of Ceremony */
    set_ceremony_sequence(({
	0, "raise 'hands'", "raise_hands",
        1, "kneel/bow 'before' [the] 'flame' / 'fire'", "kneel_flame",
        1, "pledge [my] 'soul' 'to' [the] 'flame' / 'fire' / "+
		"'jazur' [of] [flame] / [fire] / [jazur]", "pledge_soul",
        1, "pledge [my] 'body' 'to' [the] 'flame' / 'fire' / "+
		"'jazur' [of] [flame] / [fire] / [jazur]", "pledge_body",
        1, "feel/touch/pass/reach [my] [hand] / [hands] [within] / "+
		"[in] / [into] / [through] [the] 'flame' / 'fire'",
		"reach_hand",
        0, "end [the] 'ceremony' [of] [the] [flame] / [fire] / "+
	    	"[jazur]", "ceremony_end"
    }));

    set_alarm(10.0, 0.0, ceremony_tell);
}

public int
valid_ceremony()
{
    if (!STATE)
    {
	NF("The flame has gone out - no ceremony may be performed.\n");
	return 0;
    }

    if (ENV(TO) && file_name(ENV(TO)) != HOME)
    {
	NF("This ceremony may only be performed at the Flame of Jazur.\n");
	return 0;
    }

    return 1;
}

public varargs int
valid_master(object who = this_player(), object for_obj = who)
{
    if (!IS_MEMBER(who))
       return NF("You are not a member of the Union.\n");

    return MEMBER_SPHERE(who, SPH_FLAME);
}

public int
query_worn_garb(object who)
{
    string *files = ({});

    foreach(object ob: who->query_clothing(-1))
	files += ({ MASTER_OB(ob) });

    return (member_array(OBJ + "sandals", files) != -1) &&
	   (member_array(OBJ + "robe",  files) != -1);
}

public varargs int
valid_target(object who = this_player(), object for_obj = who)
{
    string *fail = ({ });

    if (!IS_MEMBER(who))
    {
	fail = ({ "You are not a member of the Union.\n",
	    	  " must be a member of the Union.\n" });
    }
    else if (!RECENTLY_BATHED(who))
    {
	fail = ({ "You have not been cleansed recently.\n",
	    	  " has not been cleansed recently.\n" });
    }
    else if (!query_worn_garb(who))
    {
	fail = ({ "You must be dressed in robe and sandals "+
	    		"for this ceremony.\n",
		  " must be dressed in robe and sandals "+
		  	"for this ceremony.\n" });
    }

    if (sizeof(fail))
    {
	if (who == for_obj)
	    notify_fail(fail[0]);
	else
	    notify_fail(who->query_The_name(for_obj) + fail[1]);

	return 0;
    }

    return 1;
}

public int
raise_hands(string str)
{
    write("You raise your hands high in a graceful gesture "+
        "that causes the sleeves of your robe to slide up"+
        "wards, baring your arms.\n");
    say(QCTNAME(TP) +" raises "+ HIS(TP) +" hands in a "+
        "graceful gesture that causes the sleeves of "+
        HIS(TP) +" robe to slide upwards, exposing "+
        "the finely chiselled musculature of "+ HIS(TP) +
        " arms to your gaze.\n");
    return 1;        
}

public int
kneel_flame(string str)
{
    write("You kneel before the flame, your head bowed "+
        "nearly to the ground.\n");
    say(QCTNAME(TP) + " kneels before the flame, " + 
        HIS(TP) + " head bowed nearly to the ground.\n");
    return 1;
}

public int
pledge_soul(string str)
{
    TP->command("shout I offer my soul to Jazur,");
    TP->command("shout that it may feed Her Flame!");
    return 1;
}

public int
pledge_body(string str)
{
    TP->command("shout I offer my body to Jazur,");
    TP->command("shout that it too, will restore her Flame!");
    return 1;
}

public void
fire_recede(object who)
{
    who->catch_tell("The blue shroud of the Flame receeds "+
        "from you, leaving behind a feeling of euphoria.\n "+
        "Jazur has accepted the offering of your essence, "+
        "and Her Flame is much renewed by it.\n");
    tell_room(ENV(who), "The shroud of blue flames recedes from "+
	QTNAME(who) +".\n", who, who);

    ENV(who)->change_state((TP->query_max_hp() / 2) * 10);
}

public void
fire_feed(object who)
{    
    who->catch_tell("The Flame enshrouds you, pulling hungrily "+
        "at the very substance of your being, milking you of "+
        "your essence!\n");
    tell_room(ENV(who), "The flame completely enshrouds " +
	QTNAME(who) + ".\nYou can see "+ HIS(who) +
	" face contort in euphoric agony!\n", who, who);

    who->heal_hp(-(who->query_max_hp() / 2));
    who->add_mana(-(who->query_max_mana() / 2));
    who->add_fatigue(-(who->query_max_fatigue() / 2));
    who->command("$pain");

    set_alarm(5.0, 0.0, &fire_recede(who));

    LOG_COUNC(NM(who)+" was fed to the Flame");
}

public int
reach_hand(string str)
{
    write("You reach your hand into the massive crack.\n "+
        "Wisps of blue-black flame wind swiftly up your "+
        "arm.\n");
    say(QCTNAME(TP) + " reaches " + HIS(TP) + 
        " hand into the massive crack where the flame "+
        "flickers.\n"+
        "Dark tendrils of blue-black fire travel swiftly "+
        "up "+ HIS(TP) + " arm.\n");

    set_alarm(4.0, 0.0, &fire_feed(TP));
    return 1;
}

public int
ceremony_end(string str)
{
    string words = "Alus ris sarudas. Jazur ris sarudas!";

    write("You feel overcome with emotion.\n"+
        "Ecstacy and exhaustion flood through you, causing "+
        "you to sway on your feet.\n"+
        "You close the ceremony by pronouncing the phrase: "+
        words +"\n");
    say(QCTNAME(TP) +" sways on "+ HIS(TP) +" feet, awash "+
       "in ecstacy.\n"+ QCTNAME(TP) +" lowers "+ HIS(TP) +
       " arms and recites the closing words of the Ceremony: "+
       words +"\n");

    /* Jazur's empath pays, too */
    TP->heal_hp(-(TP->query_max_hp() / 10));
    TP->add_mana(-(TP->query_max_mana() / 2));
    TP->add_fatigue(-(TP->query_max_fatigue() / 2));

    set_alarm(1.0, 0.0, remove_object);
    LOG_COUNC(NM(TP)+" completed the Flame ceremony");
    return 1;
}

public string
ceremony_help()
{
    return "The Ceremony of the Flame requires the "+
       "following:\n "+
       "   1-The person offering him/her self to the Flame "+
       "in an attempt to renew Her must be cleansed in the "+
       "waters of the astuary, and must be wearing the "+
       "robe and sandals.\n"+
       "   2-Begin the actual ceremony with <raise hands>.\n"+
       "   3-The subject should then <kneel before the "+
       "Flame>.\n"+
       "   4-The subject should <pledge soul to Jazur>.\n"+
       "   5-The subject should <pledge body to Jazur>.\n"+
       "   6-The subject should offer himself to the Flame "+
       "using <reach into the fire>.\n"+
       "   7-Once the offering is accepted, the ceremony "+
       "master must then <end the ceremony of the flame>.\n\n";
}
