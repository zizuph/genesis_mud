inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO      this_object()
#define ETO     environment(TO)
#define MIN_DUR 10
#define MAX_DUR 500
#define MLOSS   20

public void fade();

object it=0;
int aid=0;

public string
query_mm_in()
{
     return "descends upon this place, burning radiant and " +
            "illuminating all things with its sudden majesty.";
}

public string
query_mm_out()
{
     return "disappears in a flash of fiery blue light.";
}


public void
set_master(object target)
{
    it = target;
}

public object
query_master()
{
    return it;
}

public void
set_duration(int dur)
{
    if (dur < MIN_DUR) dur = MIN_DUR;
    if (dur > MAX_DUR) dur = MAX_DUR;
    set_alarm(itof(dur), -1.0, fade);
}

public void
create_monster()
{
   set_race_name("star");
   set_name("star");
   add_adj(({"mysterious", "glowing"}));
   add_name("spirit");
   set_long(
      "A mysterious diamond shaped mass of light, burning with a strange " +
      "blue fire, neither consuming or growing, but existing. It is so bright " +
      "to look upon that after a few moments one must avert their eyes. An " +
      "unknown seems to whisper forth from its midst.\n");

   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_M_NO_ATTACK, 1);
   add_prop(CONT_I_LIGHT, 90);
   add_prop(NPC_I_NO_LOOKS, 1);

   set_gender(2);
   set_appearance(100);

   set_act_time(1);
   add_act("@@burn");
}

public void
burned(object who)
{
    if (present(who, ETO) && who->query_prop(LIVE_I_UNDEAD)){
        who->add_mana(-MLOSS);
        who->catch_msg("The brightness of the mysterious star weakens you.\n");
    }
}

public void
fade()
{
    if (aid) remove_alarm(aid);
    
    command("emote explodes into a fiery nova!");
    map(users(), burned);
    remove_object();
}

public string
burn()
{
    command("emote shines bright and casts forth rays of " +
              "fiery blue light!\n");
    map(users(), burned);
}

public void
master()
{
   if (!it) return;
  
   if (!present(it, ETO)) move_living("X", environment(it));
   aid = set_alarm(itof(4 + random(3)), -1.0, master);
}
