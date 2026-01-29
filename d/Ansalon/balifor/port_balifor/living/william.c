#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit AM_FILE

/*
* Prototypes.
*/

return_happy(object who);
return_sad(object who);
return_joke(object who);

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;
    set_race_name("human");
    set_name("William");
    set_adj("jovial");
    add_adj("kind-hearted");
    set_long("Before you stands a portly male human " +
      "with a nose that reminds you of a pigs snout. " +
      "This doesn't seem to have had a negative effect " +
      "on him, for he seems quite jovial and kind-hearted.\n");
    set_title("Sweetwater the Owner of the Pig and Whistle Inn");
    set_adj(({"jovial","kind-hearted"}));
    add_name(({"william","barkeeper","innkeeper"}));
    set_stats(({60,60,60,60,60,60}));
    set_gender(0);   
    set_alignment(300);

    set_act_time(3);
    add_act("emote bursts into hearty laughter.");
    add_act("emote looks fondly around his Inn.");
    add_act("emote smile warmly at his customers.");
    add_act("emote cleans the bar with an old rag.");
    add_act("emote grabs some empty mugs on the bar, "+
      "and takes them back to the kitchen.");
    add_act("emote fills some mugs then takes " +
      "them to one of the tables.");   
    add_act("emote mumbles something about the draconians.");
    add_act("emote says: Business has never been as good as "+
      "when the Red Wizard performed here.");
    add_act("emote says, with a smile, to one of the customers: "+  
      "You planning on buying anything, or were you just "+
      "going to stare at the wall all day and night?");

    trig_new("%w 'introduces' %s", "react_intro");
    trig_new("%w 'kicks' %s", "react_violence");
    trig_new("%w 'slaps' %s", "react_violence");
    trig_new("%w 'tackles' %s", "react_violence");  
    trig_new("%w 'attacks' %s", "react_attack");
    trig_new("%w 'hugs' %s", "react_happy");
    trig_new("%w 'kisses' %s", "react_happy");
    trig_new("%w 'smiles' %s", "react_happy");
    trig_new("%w 'laughs' %s", "react_joke");
    trig_new("%w 'falls down laughing.'", "react_joke");
    trig_new("%w 'giggles' %s", "react_joke");
    trig_new("%w 'chuckles %s", "react_joke");
    trig_new("%w 'sighs' %s", "react_sad");
    trig_new("%w 'frowns' %s", "react_sad");
    trig_new("%w 'screams' %s", "react_loud");
}

int react_intro(string who)
{
    object owho;

    if (who)
    {
	who = lower_case(who);
	if((owho = find_player(who)))
	{
	    set_alarm(2.0,0.0,"return_intro", owho);
	}
	return 1;
    }
}

void
return_intro(object who)
{
    string who_name;

    if (present(who, environment(this_object())))
    {
	who_name = who->query_real_name();
	command("smile warmly " + who_name);
	set_alarm(1.0,0.0,"command","say Hello there " + capitalize(who_name) +
	  "! Welcome to the Pig and Whistle Inn.");
	set_alarm(1.5,0.0,"command","introduce me");
    }
}

int react_violence(string who)
{
    if (who)
    {
	who = lower_case(who);
	if(find_player(who))
	{
	    set_alarm(2.0,0.0,"return_violence", who);
	}
	return 1;
    }
}

void return_violence(string who)
{
    command("frown");
    set_alarm(1.0,0.0,"command","say Come now, there's no need "+
      "for violence. Sit down, and have a drink, eh?");
}

int react_attack(string who)
{
    if (who)
    {
	who = lower_case(who);
	if(find_player(who))
	{
	    set_alarm(1.0,0.0,"return_attack", who);
	}
	return 1;
    }
}

void return_attack(string who)
{
    command("grumble unh " + who);
    set_alarm(1.0,0.0,"command","shout I'll have none of that in "+
      "my Inn, do you hear?");
}

int react_happy(string who)
{
    object player;

    if (who)
    {
	who = lower_case(who);
	if(find_player(who))
	{
	    player = present(who, E(TO));
	    set_alarm(1.0, 0.0, &return_happy(player));
	}
	return 1;
    }
}

void return_happy(object who)
{
    command("smile");
    tell_room(E(TO), QCTNAME(TO) + " says: Nice seeing you smile "
      + QNAME(who) + ". Reminds me of the days before the draconians "
      + "came.\n", TO);
    set_alarm(1.5,0.0,"command","sigh wist");
}

int react_joke(string who)
{
    object player;

    if (who)
    {
	who = lower_case(who);
	if(find_player(who))
	{
	    player = present(who, E(TO));
	    set_alarm(1.0, 0.0, &return_joke(player));
	}
	return 1;
    }
}

void return_joke(object who)
{
    command("eyebrow cur " + who->query_real_name());
    tell_room(E(TO), QCTNAME(TO) + " says: Come now "+QTNAME(who)+
      ", if you've got a joke, share it with the rest of "+
      "us! I like a joke as much as the next man!\n", TO);
}

int react_sad(string who)
{
    object player;

    if (who)
    {
	who = lower_case(who);
	if(find_player(who))
	{
	    player = present(who, E(TO));
	    set_alarm(1.0, 0.0, &return_sad(player));
	}
	return 1;
    }
}

void return_sad(object who)
{
    command("sigh");
    tell_room(E(TO), QCTNAME(TO) + " says: Dark days, these are, "+
      "since the draconians came. But cheer up "+QTNAME(who)+
      ", you're with friends here.\n", TO);
}

int react_loud(string who)
{
    if (who)
    {
	who = lower_case(who);
	if(find_player(who))
	{
	    set_alarm(1.0,0.0,"return_loud", who);
	}
	return 1;
    }
}

void return_loud(string who)
{
    command("poke " + who);
    set_alarm(1.0,0.0,"command","say You'll have to quiet "+
      "down a bit, or you'll drive my other customers "+
      "away!");
}
