inherit "/d/Gondor/common/room";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
/* I'll put the scroll back later, somewhere else, so nobody
 * change this number - it's intentional.   Elessar.
 */
#define AWARE_NEEDED  35

int scroll_found = 0;

void
reset_room()
{
    scroll_found = 0;
}

void
create_room()
{
  set_short("In a dusty room in the ruins of Osgiliath");
  set_long(BSN("The air in the large room is incredibly stale, and the "+
    "floor covered in dust. The many shelves indicate that this was once "+
    "a library, but there aren't many books left now. "+
    "Only in a few shelves can you see some dusty sheets of paper, and "+
    "old leather bindings that once held books together. "+
    "The only door out is in the west wall, the rotting remains now "+
    "lying on the floor."));
  add_prop(ROOM_M_NO_TELEPORT, check_teleport);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,0);
  add_prop(OBJ_S_SEARCH_FUN,"search_for_scroll");
  add_prop(OBJ_I_SEARCH_TIME,8);
  add_item(({"walls","wall"}),BSN("The walls are made of smooth white stone, though "+
    "the passage of time has left some tracks. Several old shelves "+
    "line the walls, some already collapsed on the floor."));
  add_item("shelves",BSN("The shelves are made of wood, and thus "+
    "have not all survived the centuries too well. Some have collapsed "+
    "in heaps on the floor, while the strongest still stand, only "+
    "holding a few sheets of paper. The library is dead."));
  add_item(({"sheets","paper"}),BSN("The sheets of paper left seem "+
    "to crumble to dust even when you look at them. The slightest "+
    "touch will probably destroy the rest."));
  add_item(({"books","bindings","leather bindings"}),BSN(
    "The books are so decayed you decide to leave them be."));
  add_item(({"ceiling","floor"}),BSN("Both the floor and the ceiling are "+
    "made of stone. The construction is ancient, but has proved "+
    "strong enough to preserve this library many centuries already."));
  add_item("dust", BSN("The dust stands nearly an inch thick in this " +
    "place, covering everything. It rises into the air as you move, " +
    "causing you to cough."));
  add_exit(OSG_DIR+"w3stairway","west",0,1);
    reset_room();
  clone_object(OSG_DIR+"obj/libvaultout")->move(TO);
}

search_for_scroll(object player, string str)
{
  string place;
  string *places;
  string sobj;
  object obj;
  places = ({ "floor","shelves","papers","sheets" });
  if (strlen(str) && member_array(str,places)) return find_scroll(player);
  else if (str == "books")
    return "The books fall apart as soon as you touch them.\n"+
      "Perhaps you can find more if you search through the papers on the floor.\n";
  else if (str == "scrolls")
    return "There are no scrolls here to search.\n";
  return "";
}

find_scroll(object pl)
{
  object scroll;
  if (scroll_found || pl->query_skill(SS_AWARENESS)<random(AWARE_NEEDED)) return "You find nothing of interest there.\n";
  if (!present("ranger_spell_book",pl)) return "You don't find anything of interest here.\n";
  if (present("ranger_spell_book",pl)->query_spell_known("re")) return "You don't find anything of interest here.\n";
  seteuid(getuid(TO));
  scroll = clone_object(OSG_DIR+"obj/scroll");
  scroll->move(TO);
  say(QCTNAME(pl)+" finds a scroll among the decaying papers in the shelves.\n",pl);
  scroll_found = 1;
  return "You find a scroll among the decaying papers in one of the collapsed shelves!\n";
}
