#include "../guild.h"
#include <stdproperties.h>
#include <std.h>

int lockout()
{
#ifdef ROOM_LOCKOUT
  object where;
  string name, jrname, this_domain;

  name = this_player()->query_real_name();
  this_domain = SECURITY->domain_object(this_object());

// npcs of this domain may enter
  if (this_player()->query_npc())
  {
    if (SECURITY->domain_object(this_player()) == this_domain)
    {
      return 0;
    }
  }
  else
  {
// If it's a junior, try to get the wizard's name from the jr name
    if (sscanf(name, "%wjr", jrname))
    {
      name = jrname;
    }

// wizards of this domain, arches++, and their jr's may enter
    if (SECURITY->query_wiz_rank(name) >= WIZ_ARCH ||
        SECURITY->query_wiz_dom(name) == this_domain)
    {
      return 0;
    }
  }

  if (!(where = this_player()->query_prop(LIVE_O_LAST_ROOM)))
  {
    where = this_player()->query_def_start();
  }

  return !(this_player()->move_living("X", where, 1, 1));

#else
  return 0;
#endif
}

