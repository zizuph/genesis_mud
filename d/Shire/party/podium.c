#include "defs.h"

inherit PARTY_BASE;

#define ALLOWED ({"sneak","applaud","clap","chuckle","smile","bug",\
      "idea","commune","reply","typo","cheer","praise"})
#define SPEECH_PROP  "_i_am_giving_a_speech"

object speaker;
int quiet = 0;
int talking = 1;

void
create_party_room()
{
    add_prop(ROOM_S_MAP_FILE, "party.txt");

    set_short("Inside a grand pavilion");
    set_long("You are standing within a huge tent used as a gathering "+
      "place for the party.   A large banner with the words, @@word_desc@@"+
      " written on it, hangs from the ceiling of this pavilion.  In one "+
      "corner a rather large "+
      "podium stands, which is used for giving speeches.  You hear fireworks "+
      "to your east; to your west the smells of food wafts to your nose, "+
      "while to your south a makeshift post office has been placed.\n");

    add_item(({"podium","large podium"}), "@@podium_desc@@");
    add_item(({"banner","large banner"}),
      "A simple banner with the words @@word_desc@@ on it.\n");
    add_item(({"tent","pavilion","large tent"}),
      "This is a rather large tent made of a durable canvas.  It must be "+
      "at least 10 feet high and have enough room for hundreds of people to "+
      "sit in it.  This is the Head Pavilion for the party, a gathering "+
      "place for people to chat in the relative quiet of this tent.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop("_room_i_allow_steed", 1);

    add_exit(PARTY_DIR+"entrance","north");
    add_exit(PARTY_DIR+"field","east");
    add_exit(PARTY_DIR+"post","south");
    add_exit(PARTY_DIR+"dinner","west");
}

string
word_desc()
{
    mixed str = PARTY_MASTER->query_party_for();

    return "'Welcome to "+LANG_POSS(PARTY_MASTER->query_hosts())+" party to "+
    "celebrate "+(stringp(str) ? LANG_POSS(str) +" " : "")+
    "" +PARTY_MASTER->query_reason() + "!'";
}

string
podium_desc()
{
    if (!objectp(speaker) || !present(speaker, ENV(TP)))
	return "A large marble podium stands in the northern part of "+
	"the podium, it stands a good 4 feet about the ground making "+
	"anyone who should stand on it clearly visible "+
	"to everyone within the tent.\n";

    return (TP == speaker ? "You are" : QCTNAME(speaker)) +
    " standing upon the podium."+
    (TP == speaker ? "" : " It looks like "+HE_SHE(speaker)+
      "is in the middle of a speech.") + "\n";
}

void
init() 
{
    ::init();
    add_action("speech","speech");
    add_action("end_speech","done");
    add_action("end_speech","finish");
    add_action("do_quiet","quiet");
    if (PARTY_MASTER->query_is_host(TP->query_real_name()) ||
      PARTY_MASTER->query_is_guest_of_honour(TP->query_real_name()) ||
      TP->query_wiz_level())
    {
	add_action("interrupt","interrupt");
    }
    else
    {
	add_action("prevent_spam","",1);
    }
}

int
speech(string str)
{
    if (!talking)
    {
	notify_fail("But someone is alreday giving a speech. You'll "+
	  "have to wait your turn.\n");
	return 0;
    }
    write("You inform everyone that you about to give a speech.\n"+
      "If the audience is too loud you may 'quiet' them if you wish to.\n");
    PARTY_MASTER->tell_party_rooms(QCTNAME(TP)+" is about to give "+
      "a speech in the Head Pavilion.","all",({TP}));
    TP->add_prop(SPEECH_PROP,1);
    speaker = TP;
    talking = 0;
    return 1;
}

int
end_speech(string str)
{
    if (TP->query_prop(SPEECH_PROP))
    {
	write("You have finished your speech.\n");
	say(QCTNAME(TP)+" is finished with "+HIS_HER(TP)+" speech.\n");
	TP->remove_prop(SPEECH_PROP);
	talking = 1;
	quiet = 0;
	speaker = 0;
    }
    else
    {
	write("But you're not giving a speech!\n");
    }
    return 1;
}

int
interrupt(string str)
{
    if (talking)
    {
	notify_fail("There is no one giving a speech to interrupt!\n");
	return 0;
    }
    speaker->remove_prop(SPEECH_PROP);
    talking = 1;
    quiet = 0;
    speaker = 0;
    TP->catch_msg("You interrupt "+QTNAME(speaker)+"'s speech.\n");
    say(QCTNAME(TP)+" interrupts "+QTNAME(speaker)+"'s speech.\n");
    return 1;
}

int
do_quiet(string str)
{
    if (!TP->query_prop(SPEECH_PROP))
	return 0;

    if (quiet)
    {
	write("You allow the crowd to speak freely again.\n");
	say(QCTNAME(TP)+" allows everyone to speak freely again.\n");
	quiet = 0;
    }
    else
    {
	write("You motion the crowd to be silent.\n");
	say(QCTNAME(TP)+" motions everyone to be quiet.\n");
	quiet = 1;
    }
    return 1;
}

int
prevent_spam(string str)
{
    if (!quiet)
	return 0;
    if (TP->query_prop(SPEECH_PROP))
	return 0;
    if (member_array(query_verb(),ALLOWED) != -1)
	return 0;
    if (member_array(query_verb(),TO->query_exit_cmds()) != -1)
	return 0;
    write("Shhhh.....someone is giving a speech, you best "+
      "be quiet so they can finish it without interruption.\n");
    return 1;
}

void
leave_inv(object ob,object to)
{
    ::leave_inv(ob,to);
    if (ob->query_prop(SPEECH_PROP))
    {
	quiet = 0;
	talking = 1;
	speaker = 0;
	ob->remove_prop(SPEECH_PROP);
    }
}
