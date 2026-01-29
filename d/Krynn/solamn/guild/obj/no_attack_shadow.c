/* prevent the player/npc from being attacked again by a knight. */

/* THIS FILE IS OBSOLETE!! */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit "/std/shadow";

int alrm;

mixed
knights_may_not_attack()
{
    if (!alrm)
      alrm = set_alarm(3600.0,0.0,"remove_shadow",MASTER);
    if (TP->query_knight_level())
      return "You decide not to attack this helpless being.\n";
    else
      return 0;
}

void
attacked_by(object ob)
{
    if (ob->query_knight_level())
      return;
    shadow_who->attacked_by(ob);
}

void
attack_object(object ob)
{
    if (ob->query_knight_level())
      return;
    shadow_who->attack_object(ob);
}

void
wake_up_again()
{
    set_alarm(3.0,0.0,"get_ready");
}

void
get_ready()
{
    shadow_who->command("$get all");
    shadow_who->command("$wear all");
    shadow_who->command("$wield all");
}
