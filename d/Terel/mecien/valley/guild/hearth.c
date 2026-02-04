/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO  this_object()
#define TP  this_player()
#define ETP environment(TP)

#define N_SOOT   8
#define SAC_PROP "no_sacrifice"

public void new_soot();

int has_soot;

public void
init()
{
   ::init();
    add_action("do_sacrifice", "sacrifice");
    add_action("do_touch", "touch");
}

public void
reset_room()
{
    set_alarm(2.0, -1.0, new_soot);
}

public void
create_room()
{
   set_short("Hearth");
   set_long(
      "Arcane and mysterious, this chamber is ancient. Its form being that "
    + "of a pyramid type dome, the stone of a dark black speckled gold. Housed "
    + "in the center of the chamber is a large candescent golden brazier that "
    + "is set deep into the floor, around which is a dias and a luminous white "
    + "crown-like safeguard. A tall and ominous flame of blue rises forth from "
    + "the golden brazier, producing a scintillating light throughout the hall.\n");

   add_item(({"fire", "flame", "mystic flame"}),
            "An ominous fiery pillar of blue, it rises out of the brazier. The "
          + "flame seems to have some charism to it, a mysterious feeling that "
          + "it is something not of this world.\n");
   add_item("brazier", "It is made of gold, but looks almost white, being "
          + "candescent. The fires are so bright that there is no telling what "
          + "fuels the flame.\n");
   add_item(({"crown", "safeguard", "crown-like safeguard", "guard"}), "@@my_crown");
   add_item(({"soot"}), "@@my_soot");
   
   add_exit(GUILD_DIR + "u_hall2", "north", 0);
   add_exit(GUILD_DIR + "sfc", "south", "@@check");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 2);
   
   reset_room();
}

public string
my_crown()
{
    if (has_soot)
        return "It is a beautiful ornamental guard that rings " +
               "the brazier made of some luminous white material. " +
               "Parts of it are coated with soot though.\n";
    else
        return "It is a beautiful ornamental guard that rings " +
               "the brazier made of some luminous white material. " +
               "Despite of its nearness to the fire, it is free from soot.\n";
}

public string
my_soot()
{
    if (has_soot)
        return "The soot covers parts of the crown-like guard " +
               "around the brazier.\n";
    else
        return "You find no soot.\n";
}

public int
check()
{
   if (!MEMBER(TP)) {
      write("Some Ancient power keeps you from that place.\n");
      return 1;
   }
   return 0;
}

public void
new_soot()
{
    if (has_soot == N_SOOT) {
        tell_room(TO, "A blue flame suddenly emerges from the brazier and " +
                      "reaches the soot-coated crown.\n");
        return;
    };
    
    tell_room(TO, "A blue flame suddenly emerges from the brazier and " +
                  "reaches the crown. As a result, some soot is left " +
                  "on the crown.\n");
    has_soot = N_SOOT;
}

public int
do_touch(string str)
{
   object soot, alb;

   notify_fail("Touch what with what?\n");
   if (!str) return 0;
   
   if (!parse_command(str, TP, " 'crown' / 'guard' 'with' %o ", alb))
       return 0;

   notify_fail("You do not have the holy alb!\n");
   if (present(alb, TP) != present(MYSTIC_ALB, TP)) return 0;

   TP->catch_msg("You touch the holy alb to the crown-like guard.\n");
   tell_room(ETP, QCTNAME(TP) + " touches " + LANG_ADDART(alb->short()) +
                  " to the crown-like guard surrounding the fire.\n", TP);
   
   if (has_soot <= 0) return 1;
   
   TP->catch_msg("A piece of soot is removed from the crown-like guard.\n");
   
   seteuid(getuid());
   soot = clone_object(GUILD_DIR + "obj/soot");
   if (soot->move(TP)) {
       soot->move(ETP);
       tell_room(ETP, "A piece of soot falls to the floor.\n");
   } else
       TP->catch_msg("You catch the piece of soot before it reaches the floor.\n");
   has_soot--;
   return 1;
}

public int
do_sacrifice(string str)
{
   object ob, *obs;
   int mana, suc;
   int *val;
   
   notify_fail("Sacrifice what?\n");
   if (!str) return 0;
   
   if (!parse_command(str, TP, "%i", obs)) return 0;
   if (sizeof(obs) < 2) return 0;
   
   notify_fail("Only one item may be sacrificed.\n");
   if (sizeof(obs) > 2) return 0;
   
   ob = obs[1];
   
   if (living(ob) || ob->query_prop(SAC_PROP) || TP->query_prop(SAC_PROP)) {
       write("It cannot be done.\n");
       return 1;
   }
   write("You place " + ob->short() + " within the sacred fires.\n");
   write("Your offering is consumed by the flames.\n");
   say(QCTNAME(TP) + " makes a sacrifice to the sacred fire.\n");
   suc  = TP->query_skill(SS_ELEMENT_FIRE);
   suc += random(TP->query_stat(SS_WIS));
   val = (int *)ob->query_prop(MAGIC_I_RES_FIRE);
   if (pointerp(val)) suc -= val[0];
   if (suc > 40 + random(50)) {
       write("The Ancient powers touch you.\n");
       mana = ob->query_value();
       if (mana <  1) mana = 1;
       if (mana > 20) mana = 20;
       TP->add_mana(mana);
       TP->add_prop(SAC_PROP, 1);
       set_alarm(2.0, -1.0, new_soot); 
   }
   ob->remove_object();
   return 1;
}
