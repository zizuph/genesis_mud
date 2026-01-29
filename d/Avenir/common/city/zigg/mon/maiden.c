// file name:	maiden.c
// creator(s):	Lucius, July 2006
// purpose:	Maiden at the entrance to the Ziggurat.
/*
 * Revisions:
 *   Lucius, Sep 2016:  Added a couple checks to prevent runtime errors.
 *
 */
#pragma strict_types

#include "zigg.h"

#include <macros.h>
#include <ss_types.h>

inherit ZIG_NPC;

private static int alarm;


static void
zig_npc(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"maiden", "anchorite"}));
    set_title("Esteemed Anchorite to Hizarbin");
    set_race_name("elf");
    set_adj(({"comely", "young"}));
    default_config_npc(100, 30);
    set_alignment(0);
    set_appearance_offset(0);
    set_gender(G_FEMALE);

    set_knight_prestige(-5);

    set_skill(SS_DEFENSE, 90);
    set_skill(SS_AWARENESS, 90);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_dont_answer_unseen(1);
    set_default_answer("@@what_me@@");

    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
      "say There are two markets: the one for outlanders, and "+
      "the one for sybarites. You passed through the bazaar "+
      "to get here. That one is for outlanders. The merchantile "+
      "pale is what sybarites use most.", 1);
    add_ask(({"park","island", "holm", "Holm"}),
      "say The Holm of the Icondite is where the shadow-elves Hunt. "+
      "They're pretty particular about who they let on that island "+
      "and when, but then I expect you know that by now.",1);
    add_ask(({"bath", "melchior's bath"}),
      "say It is near the First Gate",1);
    add_ask(({"sybarus","bazaar"}),
      "say It is over the Bridge of Sighs.",1);
    add_ask(({"bridge","bridge of sighs"}),
      "say It is the link between the City and the Bazaar.",1);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}),
      "say Just look around, for you are already standing within it.", 1);
    add_ask(({"task", "job", "quest",}), "@@give_task@@");
    add_ask(({"help",}),
      "say The help I offer is in the form of blessings and anointments.", 1);
    add_ask(({"infidel", "infidels"}),
      "say I do not wish to speak to you of Infidels.", 1);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
      "say The Faithful serve the Will of the Idrys.",1);
    add_ask(({"master", "Master", "god", "God"}),
      "say My Master is Hizarbin.", 1);
    add_ask(({"hizarbin", "Hizarbin"}),
      "say Hizarbin is the Idrys of the Eleventh Hour. "+
      "If you seek entrance, you shall need his blessing.", 1);
    add_ask(({"priest","priestess", "anchorite", "guild"}),
      "say I am an Anchorite of Hizarbin, a priestess who has dedicated "+
      "her life to serving His Will.", 1);
    add_ask(({"union", "shadow union", "shadow warrior"}),
      "say They are known for Purity, but even they need be cleansed "+
      "by Hizarbin before entering here. Our standards are impeccable.", 1);
    add_ask(({"dej-minha"}),
      "say They are the Hegemon's. They answer only to him. "+
      "I would not cross the dej-minha, were I you.", 1);
    add_ask(({"jadestone", "jadestone doll"}),
      "say She can be found at the bazaar.", 1);
    add_ask(({"name","intro","introduction"}),
      "say Name? My name is bouyed upon the waves of the Dark Sea "+
      "and is only for Hizarbin to know.", 1);
    add_ask(({"blessing","anoint","anointment"}),
      "say Whose blessing is it you seek?", 1);
    add_ask(({"blessing of hizarbin","blessing of Hizarbin",
	      "hizarbin's blessing", "Hizarbin's blessing",
	      "hizarbins blessing", "Hizarbins blessing",}),
	"@@give_blessing@@");
    add_ask(({"idrys","Idrys","gods","Gods"}),
	"say There are many Idrys, but I follow "+
	"Hizarbin as an Anchorite.", 1);
    add_ask(({"ziggurat","Ziggurat","pleasure palace"}),
	"say You stand atop pleasure palace of Syb'arus. The idrys must "+
	"have taken an interest in you for the Hegemon has decreed that "+
	"a sigil is no longer needed for those wishing to visit the first "+
	"two levels. They are dull anyway and would soon be vacant had he "+
	"not. You will surely need Hizarbin's blessing of Purity before "+
	"proceeding, however.", 1);	
    add_ask(({"hegemon","Hegemon"}),
	"say He guides Syb'arus with his wisdom. Truly he is the Chosen of "+
	"the Idrys.", 1);
	
    configure_eyes("soft", "sea-foam blue", 2);
    configure_hair("long", "pale blue", "rippling in waves down her back");
}

static void
add_clothing(void)
{
    object cm = CM->get_this_object();

    cm->set_cset("cool");
    cm->make_girl(TO, -1);

    command("wear garments");
}

public void
equip_me(void)
{
}

public void
unseen_hook(void)
{
    command("emote peers thoughtfully around.");
}

private void
react_infidel(object who)
{
    command("shout Defenders! We have an Infidel amongst us.");
    command("point "+ OB_NAME(who));
    query_team_others()->command("kill "+ OB_NAME(who));
}

/* default answer to questions */
public string
what_me(void)
{
    if (IS_INFIDEL(TP))
    {
	command("frown pious");
	react_infidel(TP);
	return "";
    }

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(5))
    {
    case 0:
	command("laugh .");
	command("say You can't really be expecting me to answer that!");
	break;
    case 1:
	command("say I would not presume to offer an opinion on that.");
	command("smile tight");
	break;
    case 2:
	command("say I am not the person to ask that of. I am but "+
	  "a humble priestess, a servant of Hizarbin.");
	break;
    case 3:
	command("say It is the questions in life that motivate us. "+
	  "Do you really want an answer to that?");
	command("frown");
	break;
    case 4:
	command("say Knowledge is Power. Why should I empower you?");
	command("wave air");
	break;
    }
    return "";
}

private void
anoint_remove(object who)
{
    if (!objectp(who))
	return;

    who->remove_prop(PROP_I_CLEANSED);
}

private void
anoint(object who)
{
    who->add_prop(PROP_I_CLEANSED, 1);
    set_alarm(600.0, 0.0, &anoint_remove(who));

    /* Selectively remove these dirty-only items. */
    who->query_subloc_obj("_kalad_dirty_subloc")->remove_object();
    who->query_subloc_obj("stink_object_subloc")->remove_object();
    who->query_subloc_obj("_fireplace_soot_subloc_")->remove_object();
    who->query_subloc_obj("wearing_blood_object_subloc")->remove_object();
    present("DUNG_OBJ", who)->remove_object();

    who->catch_tell("Your dirt and grime seem to lift from your skin "+
	"and flake off, leaving you with a sense of purity.\n");
    tell_room(ENV(TO), QCTPNAME(who) +" dirt and grime seems "+
	"to flake off and fall away.\n", who, who);
}

private void
blessing(object who, int count)
{
    float delay = 2.5;

    alarm = 0;

    if (!objectp(who) || !present(who, environment()))
    {
	command("sigh disgust");
	return;
    }

    switch(count++)
    {
    case 0:
	command("say So you wish a blessing from revered Hizarbin?");
	break;
    case 1:
	command("peer probing "+ OB_NAME(who));
	break;
    case 2:
	command("emote turns to face the fountain and passes "+
	    "her hand over the rippling waters.");
	break;
    case 3:
	command("emote seems to concentrate and the black waters "+
	    "go still.");
	break;
    case 4:
	command("emote begins a faintly heard chant, her body taking on "+
	    "a slight, sinuous swaying.");
	break;
    case 5:
	command("emote 's eyes bleed to black as the fountain's waters "+
	    "grow clear.");
	break;
    case 6:
	command("emote touches two fingertips to the now still, "+
	    "crystalline surface of the pool.");
	break;
    case 7:
	command("emote withdraws her fingertips, the movement followed "+
	    "by the sharp sounds of the waters surface cracking.");
	break;
    case 8:
	who->catch_tell(TO->query_The_name(who) +" turns back to you as "+
	    "the black waters once more swallow the clear shards as they "+
	    "sink beneath sight.\n");
	tell_room(ENV(TO), QCTNAME(TO) +" turns back to "+ QTNAME(who) +
	    " as the black waters once more swallow the clear shards as "+
	    "they sink beneath sight.\n", who, TO);
	break;
    case 9:
	who->catch_tell(TO->query_The_name(who) +" touches her "+
	    "glistening fingertips to your forehead, the moisture "+
	    "feeling of liquid ice.\n");
	tell_room(ENV(TO), QCTNAME(TO) +" touches her glistening "+
	    "fingertips to "+ QTPNAME(who) +" forehead.\n", who, TO);
	break;
    case 10:
	who->catch_tell(TO->query_The_name(who) +" draws three wavy "+
	    "lines upon your brow, her eyes slowly returning to their "+
	    "former blue as she does.\n");
	tell_room(ENV(TO), QCTNAME(TO) +" draws three wavy lines upon "+
	    QTPNAME(who) +" brow, her eyes slowly returning to their "+
	    "former blue as she does.\n", who, TO);
	break;
    case 11:
	delay = 2.0;
	command("emote withdraws, a distant smile adorning her lips.");
	break;
    case 12:
	delay = 2.0;
	anoint(who);
	break;
    case 13:
	delay = 2.0;
	command("say to "+ OB_NAME(who) +" You are purified.");
	break;
    case 14:
	delay = 2.0;
	command("say Go now, partake of the Ziggurat's succulence.");
	break;
    case 15:
	command("wave dismiss");
	/* The END. */
	return;
    default:
	/* Error? */
	command("peer confus");
	return;
    }

    alarm = set_alarm(delay, 0.0, &blessing(who, count));
}

public string
give_blessing(void)
{
    object tp = TP;

    if (alarm)
	return "";

    if (IS_INFIDEL(TP))
    {
	command("say Hizarbin's blessing is not for you Infidel!");
	command("shout Defenders! Slay the Infidel!");
	query_team_others()->command("kill "+ OB_NAME(TP));
	return "";
    }

    if (TP->query_prop(PROP_I_CLEANSED) == 1)
    {
	command("say to "+ OB_NAME(TP) +" You already carry the "+
	    "necessary blessing, continue on.");
	return "";
    }
    
    if (TP->query_prop(PROP_I_CLEANSED) == 2)
    {
	command("say to "+ OB_NAME(TP) +" You have traveled through the "+
	    "pure and sacred waters of the fountain. There is no greater "+
	    "blessing I could confer. For now, you are Clean enough to "+
	    "enter.");
	return "";
    }

    alarm = set_alarm(3.0, 0.0, &blessing(tp, 0));
    return "";
}

public string
give_task(void)
{
    command("say Thy task is to not offend the Idrys.");
    command("emote smiles quirkily.");
    return "";
}

static void
check_meet(object who, string oname)
{
    if (IS_INFIDEL(who))
    {
	react_infidel(who);
	return;
    }

    int i = random(15);

    if (who->query_prop(DANCER))
    {
	if (i < 4)
	{
	    command("say to "+ oname +
	      " Are you on the roster for the Ziggurat today?");
	}
    }
    else if (IS_SYBARITE(who))
    {
	if (i < 7)
	    command("bow respect "+ oname);
	else if (i == 7)
	    command("smile joy "+ oname);
	else if (i > 7)
	{
	    command("say to "+ oname +
	      " May the Idrys smile upon you this day.");
	}
    }
    else
    {
	if (i > 5)
	    command("say Celebrate the Source, Outlander.");
    }
}

public void
notify_ob_attacked_me(object me, object foe)
{
    /* We don't assist. */
}

private void
no_attack(object ob)
{
    if (!objectp(ob) || !sizeof(query_team_others()))
	return;

    stop_fight(ob);
    ob->stop_fight(TO);

    tell_room(ENV(), QCTNAME(TO) +" nimbly moves out of the way.\n");
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(3.0, 0.0, &no_attack(ob));
}
