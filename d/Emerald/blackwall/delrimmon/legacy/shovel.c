/* /d/Gondor/olorin/obj/shovel.c
 *
 * Created: 22-may-1993 by Olorin
 *
 */
#pragma strict_types
inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h";

public int do_dig(string str);

public void
create_weapon()
{
  set_name("shovel");
  set_long("This shovel looks positively ancient. Its dull blade is"
    + " supported by a long wooden handle. One could still dig with"
    + " it, most likely.\n");
    set_short("shovel");
  set_default_weapon(15,10,W_POLEARM,W_SLASH|W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_VOLUME,3000);
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,10)+150-random(50));
}

public void
init()
{
  ::init();

  add_action(do_dig, "dig");
}

public int
do_dig(string str)
{
  object room, hole;

    if (!strlen(str))
    {
        NFN0("Where do you want to dig with what?");
    }

    if (!parse_command(str, ({}),
        "[in] 'here' / 'ground' [with] [shovel]"))
    {
        NF("Where do you want to dig with what?\n");
        return 0;
    }

  NF("You cannot dig indoors.\n");
  if (ENV(TP)->query_prop(ROOM_I_INSIDE)) return 0;

  if(TP->query_fatigue() < 40)
  {
    write("You are too tired to dig.\n");
    return 1;
  }
  TP->add_fatigue(-40);

  seteuid(getuid(TO));
  write("You start to dig until you have worked up a sweat.\n");
  say(QCTNAME(TP) + " starts to dig until " + TP->query_pronoun() + " is tired.\n");

  room = ENV(TO);
  while(!room->query_prop(ROOM_I_IS)) room = ENV(room);

  if(hole = present("_hole_",room))
  {
    hole->increase_size();
    return 1;
  }
  else
  {
    hole = clone_object("/d/Emerald/blackwall/delrimmon/legacy/hole.c");
    hole->move(room);
    return 1;
  }
}

