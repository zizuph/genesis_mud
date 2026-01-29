/* Weapon shadow for <kthrust> by Morrigan, 5/4/97 */
/* Navarre August 22 2006, added check in plural_short to
   avoid the "Two 0 lodged in the ground" description showing
   up, when the sword trusted doesn't have pshort set.
   It might not work for all weapons, but atleast an s
   kind of weird placed in rare occassions, is better than 0.
 */


inherit "/std/shadow";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

int depth;

set_depth(int i)
{
    depth = i;
}

int
query_depth()
{
    return depth;
}

void
setup_things()
{
    shadow_who->add_cmd_item(shadow_who->query_names(),
      "pull", VBFC_ME("pull_weapon"));
}

string
short()
{
    return shadow_who->short()+" lodged in the ground";
}

string
query_short()
{
    return shadow_who->query_short()+" lodged in the ground";
}

string
plural_short()
{
    string shortdescr = shadow_who->plural_short();
    if(shortdescr)
    {
      return shortdescr+" lodged in the ground";
    }
    return shadow_who->short()+"s lodged in the ground";
}

int
pull_weapon()
{
    if (TP->query_stat(SS_STR) > query_depth())
	shadow_who->remove_prop(OBJ_M_NO_GET);

    if (shadow_who->move(TP))
    {
	write("You take a firm grip on the "+shadow_who->short()+", "+
	  "but do not manage to pull it from the ground.\n");
	say(QCTNAME(TP)+" takes a firm grip on the "+
	  shadow_who->short()+", but does not manage to pull it from the ground.\n");
	shadow_who->add_prop(OBJ_M_NO_GET, "The weapon cannot be "+
	  "taken, it is lodged firmly in the ground.\n");
	return 1;
    }

    write("You take a firm grip on the "+shadow_who->short()+", "+
      "and pull it from the ground.\n");
    say(QCTNAME(TP)+" takes a firm "+
      "grip on the "+shadow_who->short()+" and pulls it from "+
      "the ground.\n");
    remove_shadow();
    return 1;
}

