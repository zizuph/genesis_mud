/*
 * A letter from Captain to Fahlmar
 * Tapakah, 09/2021
 */

#pragma strict_types;

#include "ss_types.h"
#include "stdproperties.h"

#include "../defs.h"

inherit "/std/object";

#define MIN_LANGUAGE_TO_READ_COMPLETELY 61
#define MIN_LANGUAGE_TO_READ_MINIMALLY 25

string message = ""+
  "Dear Fahlmar, \n"+
  "\n"+
  "We have established the camp not far from the narrow gorge\n"+
  "between the shore and the mountain. Soon the scouts will try\n"+
  "to scale the mountains and see if there is any activity from\n"+
  "the north reaching this far into our lands. The spirits are\n"+
  "good, but the supplies are a bit scarce.\n"+
  "\n"+
  "Shall Khalakhor Be Free,\n"+
  "Maeldun Macdunn.\n";

string
read_message ()
{
  int message_length = strlen(message);
  int l,e,e_end;
  int effective_skill, skill_span, pivot_point, delta;
  int *erato = ({2,3,5,7,11});
  int flag;
  string ch, random_ch;
  string text = "";

  effective_skill = (TP->query_skill(SS_LANGUAGE) -
                     MIN_LANGUAGE_TO_READ_MINIMALLY) / 4;
  skill_span = MIN_LANGUAGE_TO_READ_COMPLETELY -
    MIN_LANGUAGE_TO_READ_MINIMALLY;
  pivot_point = skill_span / 8;
  delta = effective_skill - pivot_point;

  for (l=0; l<message_length; l++) {
    ch = message[l..l];
    switch(ch) {
    case "\n":
    case " ":
    case ",":
    case ".":
      text += ch;
      break;
    default:
      if (TP->query_skill(SS_LANGUAGE) < MIN_LANGUAGE_TO_READ_MINIMALLY)
        text += "#";
      else if (TP->query_skill(SS_LANGUAGE) >= MIN_LANGUAGE_TO_READ_COMPLETELY)
        text += ch;
      else {
        for (e = 0, e_end = sizeof(erato); e < e_end; e++) {
          if (e > abs(delta))
            break;
          flag = l % erato[e] ? 0 : 1;
          if (!e)
            random_ch = flag ? "#" : ch;
          else {
            if (delta < 0 && flag)
              random_ch = "#";
            else if (delta > 0 && flag)
              random_ch = ch;
          }
        }
        text += random_ch;
      }
    }
    
  }
  return text;
}

string
long_message ()
{
  return "The message, written in a local language, reads\n\n" + read_message();
}

void
create_object ()
{
  set_name("letter");
  add_adj(({"crinkled", "oblong"}));
  set_short("crinkled oblong letter");
  set_long(long_message);
  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME, 500);
  add_prop(OBJ_I_VALUE, 5);
}

int
read_me (string str)
{
  if (!str || str != "letter" && str != "message")
    NF0("Read what?\n");
  string message = read_message();
  TP->catch_msg(message);
  return 1;
}

void
init ()
{
  ::init();
  add_action(read_me, "read");
}
