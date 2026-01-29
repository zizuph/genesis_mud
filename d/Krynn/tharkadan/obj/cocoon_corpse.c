inherit "/std/object";
inherit "/lib/unique";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"

#define MAGIC_HOOPAK  WEP + "hoopak"
#define MAGIC_CLUB    WEP + "mag_theiwar_hammer"
#define MAGIC_WAND    TOBJ + "light_wand"
#define SCROLL        "/d/Krynn/common/scrolls/eruption_scroll.c"
#define HOOPAK        "/d/Ansalon/goodlund/kendermore/obj/hoopak"
#define CLUB          WEP + "theiwar_hammer"

int cocoon_opened = 0;
int corpse_type = random(4);
string *corpse_types = ({ "kender adventurer", "dark dwarf",
  "red-robed wizard", "red-robed wizard" });
object treasure;

void
create_object()
{
    set_name(({"cocoon","corpse"}));
    set_short("humanoid-shaped cocoon");
    add_adj(({"humanoid","humanoid-shaped"}));
    set_long("@@cocoon_desc");
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_WEIGHT,100000);
    add_prop(OBJ_M_NO_GET, 1);

    add_cmd_item(({"cocoon", "open cocoon","humanoid-shaped cocoon"}),
      ({"slice"}),"@@cocoon_open");
    setuid; seteuid(getuid());
}

void
remove_remains()
{
    tell_room(E(TO),"The cocoon and the corpse within decay to dust.\n");
    TO->remove_object();
}

string
cocoon_desc()
{
    if(!cocoon_opened)
    {
	return "This humanoid-shaped cocoon has entombed some " +
	"unfortunate person within a thick case of spider " +
	"webbing. You could probably slice it open.\n";
    }

    switch(corpse_type)
    {
    case 0:
	return "This humanoid-shaped cocoon has been sliced open, " +
	"revealing the corpse of an unlucky kender adventurer " +
	"inside.\n";
	break;
    case 1:
	return "This humanoid-shaped cocoon has been sliced open, " +
	"revealing the corpse of an unlucky Theiwar dark dwarf.\n";
	break;
    default:
	return "This humanoid-shaped cocoon has been sliced open, " +
	"revealing the corpse of an unlucky human red-robed " +
	"wizard.\n";
	break;
    }
}

object
query_wielded_weapon(object actor)
{
    object * weapons;

    weapons = filter(actor->query_weapon(-1), 
      &operator(&)(W_SLASH) @ &->query_dt()); 
    if (!sizeof(weapons))
    {
	// Not wielding a slashing weapon
	return 0;
    }

    return weapons[random(sizeof(weapons))];
}

string
cocoon_open()
{
    if(cocoon_opened)
    {
	return "This cocoon has already been sliced open!\n";
    }

    if (!objectp(query_wielded_weapon(TP)))
    {
	write("You'll need a slashing weapon to slice open the cocoon!\n");
	return "";
    }

    switch(corpse_type)
    {
    case 0:
	treasure = clone_unique(MAGIC_HOOPAK, 15, HOOPAK);
	break;
    case 1:
	treasure = clone_unique(MAGIC_CLUB, 15, CLUB);
	break;
    case 2:
	treasure = clone_object(MAGIC_WAND);
	break;
    default:
	treasure = clone_object(SCROLL);
	break;
    }

    string weapon = treasure->short();

    write("You slice open the cocoon, revealing the corpse of a " +
      corpse_types[corpse_type]+ ". You notice the corpse is " +
      "tightly holding a " +weapon+ ", which you extract.\n");
    say(QCTNAME(TP)+ " slices open the cocoon, revealing the corpse of " +
      "a " + corpse_types[corpse_type] + ". " + QCTNAME(TP) + 
      " notices the corpse is tightly holding a " + weapon + 
      ", which " + HE(TP) + " extracts.\n");

    treasure->move(TP, 1);
    cocoon_opened = 1;

    set_alarm(45.0,0.0,&remove_remains());
    return "";
}
