#define ROKE_I_GOT_ROSE "_roke_i_got_rose"

#include <macros.h>
#include <const.h>

#include "defs.h"

inherit ROKEDIR + "lib/monster";

int
query_knight_prestige ()
{
  return -2;
}

void
allow_rose (object who)
{
  if (objectp(who))
    who->remove_prop(ROKE_I_GOT_ROSE);
}


void
return_smile (object who)
{
  object obj;
   
  if (obj = present(who, environment()))
    if (obj->query_gender() != query_gender() &&
        !obj->query_prop(ROKE_I_GOT_ROSE)) {
      command("smile at " + OB_NAME(obj));
      command("say You have a beautiful " +
              "smile, " + obj->query_nonmet_name() + ".");
      clone_object(ROKEDIR + "obj/rose")->move(this_object());
      command("give rose to " + OB_NAME(obj));
      obj->add_prop(ROKE_I_GOT_ROSE, 1);
      set_alarm(900.0, 0.0, &allow_rose(obj));
    }
    else
      command("smile at " + OB_NAME(obj));
}

void
emote_hook(string emote, object actor, string adverb, object *oblist,
           int cmd_attr, int target)
{
  if (emote != "smile") return;

  set_alarm(2.0, 0.0, &return_smile(actor, target));
}
