// an addressable letter, part of postmaster tour
// refactored
// Tapakah, 08/2021

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/se_speir/population.h"
#include "/d/Khalakhor/sys/defs.h"
#include "defs.h"

inherit  "/std/object";
inherit KLOGGER;

string name, sept, title;
string *react = ({"worry","snicker","laugh","sigh","ponder","giggle",
                  "frown","gasp","nod","hmm","blink","smile"});

void
set_address (string *address)
{
  name = address[SE_SP_NAME];
  sept = address[SE_SP_SEPT];
  string last = sept ? " " + sept : "";
  string art = sizeof(regexp(({address[SE_SP_LOCATION]}),
                             "^[A-Z].*")) ? "" : "the ";
  title = address[SE_SP_OCCUPATION] + " of " + art + address[SE_SP_LOCATION];
  if (! sept)
    sept = "";
  set_long("It is a letter folded in thirds and sealed with a wax "+
           "seal. It is addressed to: " + name + last +", " + title + ".\n"+
           "If you have found the addressee, you can <deliver> the letter.\n");
  
}
 
void
create_object ()
{
   set_name("letter");
   add_name("_baile_ashlagh_letter");
   add_adj("sealed");
   set_short("sealed letter");
   set_long("It is an unaddressed letter");
   add_prop(OBJ_I_VOLUME,90);
   add_prop(OBJ_I_WEIGHT,50);
   add_prop(OBJ_I_VALUE,0);
   add_cmd_item("letter","open","That would be illegal! It's not for you!\n");
}

int
deliver_letter (string str)
{
  string verb = query_verb();
  if (! str)
    NF0(capitalize(verb) + " what?");

  object recipient;
  
  if (! parse_command(str, all_inventory(TP), " 'letter' 'to' %l ", recipient)) {
    NF0(capitalize(verb) + " what to whom?");
  }
  setuid();
  seteuid(getuid());
  if (recipient->query_name() != name ||
      recipient->cs_query_sept() != sept ||
      recipient->cs_query_title() != title) {
    log_me(TPQN + " bad deliver " +
           implode(({
                     recipient->query_name(),
                     recipient->cs_query_sept(),
                     recipient->cs_query_title()
                   }), ",") + " vs " +
           implode(({
                     name, sept, title  
                   }), ","), "notice", "ashlagh-letter.log");
    NF0("You cannot deliver the letter since it is addressed to someone else.");
  }
  TP->catch_msg("You deliver the letter to " + recipient->query_The_name(TP) + ".\n");
  tell_room(environment(TP),
            QCTNAME(TP) + " delivers a letter to " + QCTNAME(recipient) + ".\n",
            TP);
  recipient->command("emote studies the letter carefully.");
  object sack   = present("_ashlagh_mailsack",TP);
  if (!objectp(sack)) {
    log_me(TPQN + " bad deliver (no sack) " +
           implode(({
                     name, sept, title  
                   }), ","), "notice", "ashlagh-letter.log");
    command("emote looks around suspiciously.");
    command("say You don't have a mailsack. You can't be the deliverer!");
    command("say I don't trust you, this might be evil magic!");
    command("emote drops the letter as if burned.");
    move(environment(TP));
  }
  log_me(TPQN + " good deliver " +
           implode(({
                     name, sept, title  
                   }), ","), "info", "ashlagh-letter.log");
  recipient->command("emote opens the letter and reads it quickly.");
  recipient->command(react[(random(sizeof(react)))]);
  recipient->command("say Thank you for delivering this to me.");
  recipient->command("shake "+TPQN);
  sack->remove_letter();
  remove_object();
  return 1;
}

void
init ()
{
  ::init();
  add_action(deliver_letter, "deliver");
}
