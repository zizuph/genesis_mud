#include <wa_types.h>

inherit "std/armour";

void
create_armour()
{
  set_name("amulet");
  set_short("mysterious amulet");
  set_long("The amulet seems surrounded in an aura of peace and beauty.  "+
    "Suspended from a fine silver chain hangs a mysterious medallion, "+
    "of unique design.  At the center of the amulet, a four-pointed silver "+
    "star seems to glow with an inner strength.  The points of the star "+
    "support a circle which encompasses the circumference of the medallion, "+
    "made of silver, inlaid with white pearl.  Twined about the circle, jade "+
    "has been carved in remarkable semblance of a green serpant, and "+
    "polished until its scales gleam like tiny emeralds.  Looking more "+
    "closely, you notice fine letters engraved onto the back of the "+
    "circle.\n");

  set_adj("mysterious");

  set_ac(0);

  set_at(A_NECK);

}

void
init()
{
  ::init();
  add_action("read","read");
}

int
read(string str)
{
  notify_fail("Read what?\n");

  if(!strlen(str))
    return 0;

  if(member_array(str, ({"letters","fine letters","engraving","amulet"}))<0)
    return 0;

  write("Turning over the amulet, you read the simple insription :\n"+
    "In the Mystery of the Prophet, Mecien, Zaracen of the East, never "+
    "forget.\n");
  return 1;
}

string
query_auto_load()
{
  return "/d/Immortal/stexx/private/amulet:";
}
