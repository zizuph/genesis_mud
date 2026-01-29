/*
A field in the Party Area, where players may get away from the 
Main part of the party and sit and watch the fireworks as well as
Buy firecrackers and other neat things

-Igneous-
*/

#include "defs.h"

inherit PARTY_BASE;

#define SIT_STRING " is sitting down on the hill"
#define SIT_PROP   "_live_i_sitting_on_hill"

//  Prototypes
void fireworks();

int Alarm_id;

void
create_party_room()
{
    set_short("A field nearby the river Bywater in the Shire");
    set_long("This field is filled with activity.  Hobbits running to and "+
      "fro setting up a fireworks display for the guests to "+
      "enjoy.  There is a small hill nearby the Bywater river which looks "+
      "like a comfortable place for one to sit down and enjoy the show. "+
      "Next to where the hobbits are sitting up, there is a sign of "+
      "importance. To the west there is a grand pavilion where the party "+
      "activities take place and to the southwest there is a small tent where "+
      "the cooing of pigeons can be heard.\n");

    add_item(({"display","fireworks","fireworks display"}),
      "A group of hobbits are gathered down by the Bywater river "+
      "attending a fireworks display.  The display itself is quite "+
      "impressive, with almost every kind of firework imaginable "+
      "with its stock.\n");
    add_item(({"river","water","Water","Bywater"}),
      "This is the river known as the Bywater, the hobbits are using it "+
      "to stage their fireworks, so that they don't carelessly start a "+
      "fire near some poor souls hobbit hole.\n");
    add_item(({"hill","small hill"}),
      "A comfortable little hill in perfect sight of where the fireworks "+
      "are going off.  You might want to sit down on it and enjoy the "+
      "display from there.\n");
    add_item(({"sign","sign of importance"}),
      "Perhaps you should try reading it?\n");
    add_item(({"tent","tents","small tent"}),
      "There are tents place all over the surrounding area to accommodate "+
      "the needs of all the party goers.\n");
    add_item(({"pavilion","grand pavilion"}),
      "This is a really big tent, where the main party activities occur.\n");
    add_item(({"sky"}),
      "The sky is filled with the hazy smoke, leftover from the last "+
      "firework.\n");

    add_cmd_item("sign","read","@@do_read@@");

    add_exit(PARTY_DIR+"post","southwest");
    add_exit(PARTY_DIR+"podium","west");
}
string
do_read()
{
    return "You read the sign.\n\nEnjoy the Fireworks display!\n";
}


void
init()
{
    ::init();
    add_action("do_sit","sit");
    add_action("do_sit","rest");
    add_action("do_sit", "lay");
    add_action("do_rise","rise");
    add_action("do_rise","stand");
    add_action("do_check","",1);
}

int
do_sit(string str)
{
    if (str != "hill" && str != "on hill" && str != "down")
    {
	notify_fail(CAP(query_verb())+" on what?  The hill perhaps?\n");
	return 0;
    }
    if (TP->query_prop(SIT_PROP))
    {
    notify_fail("But you are already sitting!\n");
	return 0;
    }
    write("You "+query_verb()+" down on the hill to watch the fireworks display.\n");
    say(QCTNAME(TP)+" "+query_verb()+"s down on the hill.\n");
    TP->add_prop(SIT_PROP,1);
    TP->add_prop(LIVE_S_EXTRA_SHORT, SIT_STRING);
    return 1;
}

int
do_rise(string str)
{
    if (!TP->query_prop(SIT_PROP)) 
    {
	notify_fail("But you are not sitting!\n");
	return 0;
    }
    write("You rise to your feet and stand up on the hill.\n");
    say(QCTNAME(TP)+" rises to "+HIS_HER(TP)+" feet.\n");
    TP->remove_prop(SIT_PROP);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

int
do_check(string str)
{
    if (!TP->query_prop(SIT_PROP)) 
	return 0;
    if (query_verb() == "sneak")
    {
	write("You are unable to sneak around "+
	  "while laying down on your back.  Perhaps "+
	  "you should try getting up first?\n");
	return 1;
    }
    if (member_array(query_verb(),TO->query_exit_cmds()) != -1)
    {
	write("Walking on your back is a skill you haven't mastered "+
	  "as of yet... perhaps you should rise to your feet and try "+
	  "again?\n");
	return 1;
    }
    return 0;
}

void
enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);
    if (!Alarm_id)
	Alarm_id = set_alarm(5.0,0.0,fireworks);
}

void
leave_inv(object ob,object to)
{
    ::leave_inv(ob,to);
    //   Just to make sure the extra is removed if manage to leave 
    if (ob->query_prop(LIVE_S_EXTRA_SHORT) == SIT_STRING)
	ob->remove_prop(LIVE_S_EXTRA_SHORT);
}

void
fireworks()
{
    if (!PARTY_MASTER->query_is_party())
    {
	Alarm_id = 0;
	return;
    }
    switch(random(12))
    {
    case 0..2:
	PARTY_MASTER->tell_party_rooms(
	  "A loud whistle is heard as a rocket takes flight.",
	  "outside");
	break;
    case 3:
	PARTY_MASTER->tell_party_rooms(
	  "A green tree appears in the sky, with a trunk of dark smoke: "+
	  "its leaves opening like a whole spring in a moment and its "+
	  "shining branches dropping glowing flowers down towards the earth, "+
	  "disappearing with a sweet scent just before they touch the "+
	  "ground.",
	  "outside");
	break;
    case 4:
	PARTY_MASTER->tell_party_rooms(
	  "A thunderous explosion erupts in the sky, as a brilliant red "+
	  "cloud appears and a shower of sparkling yellow rain falls "+
	  "towards the ground.",
	  "outside");
	PARTY_MASTER->tell_party_rooms("A loud explosion is heard as "+
	  "one of the fireworks goes off outside.","inside");
	break;
    case 5:
	PARTY_MASTER->tell_party_rooms(
	  "A forest of silver spears spring suddenly from the "+
	  "ground and into the air with a yell of an embattled army, "+
	  "and then towards the ground again, into the Water with a hiss "+
	  "like a hundred snakes.",
	  "outside");
	break;
    case 6:
	PARTY_MASTER->tell_party_rooms(
	  "A great pillar of purple fire erupts from the ground, sending "+
	  "multi-coloured sparks across the sky.",
	  "outside");
	break;
    case 7:
	PARTY_MASTER->tell_party_rooms(
	  "In a blaze of pink smoke, a delicate red rose forms in the sky...  "+
	  "A tiny bud at first, but it soon blossoms, with its pedals slowly "+
	  "opening towards you revealing its beauty, which sadly, soon fades "+
	  "away to nothingness.",
	  "outside");
	break;
    case 8:
	PARTY_MASTER->tell_party_rooms(
	  "With a blinding burst of light, a multitude of falling stars "+
	  "appear in the sky.  Slowly they make their way towards the ground "+
	  "changing from their original bright white, to a brilliant blue, "+
	  "then to a hazy orange, and finally they disappear from your "+
	  "sight, just before they touch the ground.",
	  "outside");
	break;
    case 9:
	PARTY_MASTER->tell_party_rooms(
	  "In an explosion of light, many tiny white hot sparks appear in "+
	  "the sky fading in and out of sight while making a delightful "+
	  "crackling sound.",
	  "outside");
	break;
    case 10:
	PARTY_MASTER->tell_party_rooms(
	  "In a violent explosion of light and sound, pillars of fire coloured "+
	  "golden-red, mithril-silver, and blazing orange shoot up into "+
	  "the air emitting a loud whistling sound as they fly up into "+
	  "the sky above you.",
	  "outside");
	break;
    case 11:
	PARTY_MASTER->tell_party_rooms(
	  "A great smoke appears in the sky, and shapes itself into a mountain "+
	  "as seen from a distance.  The mountainous shape begins to glow at "+
	  "the summit and spouts green and scarlet flames.  Out of the flames "+
	  "flies a red-golden "+
	  "dragon!!  A bright fire shoots from its jaws as its eyes glare "+
	  "down on you.   The dragon roars as it passes over you three times "+
	  "and on the final pass it does a somersault and bursts over Bywater "+
	  "with a deafening explosion!",
	  "outside");
	break;
    }
    Alarm_id = set_alarm(itof(random(60) + 15), 0.0, fireworks);
}
