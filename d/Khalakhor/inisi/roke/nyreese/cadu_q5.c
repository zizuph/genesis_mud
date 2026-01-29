/*
 * cadu_q5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*
 * Originally made by Gresolle
 * Re-formatted by Mona to make it readable Aug 96
 */

#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object hen;

void get_scroll (object who);
void tell_him (object who);

void
tell_him(object who)
{
  tell_room(NYREESEDIR + "cas_a11", QCNAME(who) + " appears from nowhere.\n");
  who->move(NYREESEDIR + "cas_a11");
  who->catch_msg("...you find yourself in a damp room with stone walls.\n");
  who->command("puke");
}

int
trans()
{
  if (!QDONE(ROKEGROUP, STATUEQUEST))
    NF0("The statues say: No reason to move you.");

  TP->catch_msg("As you call upon the statues, one of them " +
                "comes alive and casts a mighty spell of transportation" +
                " on you.\nYou disintegrate and suddenly...\n");
  say("One of the statues comes alive and mumbles a few magic " +
      "words.\n" + QCTNAME(TP) + " is slowly disintegrated.\nThe " +
      "remaining molecules rise slowly to the sky and moves" +
      " away towards unknown territories.\n");
  set_alarm(5.0, 0.0, &tell_him(TP));
  set_dircmd("me");
  TP->move_living("M", clone_object(NYREESEDIR + "cas_tmp_room"));

  return 1;
}

void
get_scroll(object who)
{
  clone_object(ROKEDIR + "obj/cadu_scroll")->move(who);
  who->catch_msg("The statues give you a scroll.\n");
}

int
mmvm (string s)
{
  if (!strlen(s) || !parse_command(s, TO, "'me' [mighty] [statues]"))
    NF0("Move who?");

  return trans();
}

int
sfish ()
{
  object fish;
  string str;

  if (!(fish = present("fish", TP)))
    NF0("You don't have a fish to sacrifice!");

  fish->remove_object();

  str = "Suddenly the statues comes to life " +
    "and bends down towards you. With one voice, they whisper: " +
    "You shall be rewarded for your kindness!";
  if (!QDONE(ROKEGROUP, SCROLLQUEST))
    str += " We have a mission " +
      "for you to complete: Many years ago, when evilness ruled " +
      "over the world, an evil prince stole The Scroll of Great " +
      "Wisdom and hid it in the Castle of Cadu. We want you to " +
      "seek out and find it so it can be returned to safety " +
      "where it can serve as guidance for the people." +
      " As a help for you to complete the quest we give you this" +
      " scroll of transportation. Examine it, and get wiser. When" +
      " you have found The Scroll of Great Wisdom, return to us " +
      "and ask for your reward.";
  else
    str += " As a help for you to travel we give you this" +
      " scroll of transportation. Examine it, and get wiser.";

  write(str + "\n");
  say("The statues whisper something to " + QTNAME(TP) + ".\n");
  set_alarm(3.0, 0.0, &get_scroll(this_player()));

  if (!QDONE(ROKEGROUP, STATUEQUEST)) {
    write("Suddenly you feel very dizzy, but when you recover you " +
          "realize that you are more experienced than before.\n");
    QSET(ROKEGROUP, STATUEQUEST);
    QLOG("Statue quest", STATUEQUESTXP);
    TP->add_exp_quest(STATUEQUESTXP);
  }
  return 1;
}

string
plaque ()
{
  return "The inscription on the "+
    "plaque reads: Raised in honour of Ged, Glindor "+
    "and Gresolle who built the Isle of Nyreese.\n";
}

void
create_room ()
{
  set_short("Town square");
  set_long("You are at the town square in Cadu. In " +
           "the middle of the square are three statues of important-" +
           "looking people. The statues emit an aura of powerful " +
           "magic. They look very interesting and beautiful.\n");
  add_item(({"statue", "statues"}),
           "The statues" +
           " are made out of roughly hewn stone. The once finely " +
           "chiseled rock bears the ungentle mark of the " +
           "fingers of Father time. There is a strong presence" +
           " of magic here, lending an ethereal god-like " +
           "ambience to the weather-worn figures. There is a " +
           "small plaque at the base of the statues.\n");
  /*
    add_item("statues", break_string("These are statues of three of "+
    "the powerful wizards of Roke, Proctor Ged, Proctor Glindor"+
    "and Lord Gresolle. The statues are made in finest gold by "+
    "the best goldsmiths in Roke, and they are covered by "+
    "valuable gems. The younger wizard Motorhead's statue is "+
    "still under construction. You spot a plaque on the base of"+
    " the statues.\n", 70));
    add_item("statue","There are three statues. Don't you want to "+
    "look at all of them at once?\n");
    add_item("base","This is the base of the statues. It has a "+
    "large golden plaque attached to it's southern side.\n");
  */

  add_cmd_item("plaque", "read", plaque);
  add_item("plaque", plaque);

  add_exit("cadu_q4", "west" );
  add_exit("cadu_q6", "east" );
  add_exit("cadu_q8", "north");
  add_exit("cadu_q2", "south");
  add_exit("cadu_q1", "southwest");
  add_exit("cadu_q3", "southeast");
  add_exit("cadu_q7", "northwest");
  add_exit("cadu_q9", "northeast");

  OUTSIDE;
  reset_room();
}

void
reset_room ()
{
  if (hen) return;
  hen = clone_object(ROKEDIR + "npc/hen");
  hen->move(TO);
}

void
init ()
{
  ::init();
  add_action(sfish, "sacrifice");
  add_action(sfish, "offer");
  add_action(mmvm,  "move");
}
