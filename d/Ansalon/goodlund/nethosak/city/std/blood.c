/*
 * /d/Ansalon/goodlund/nethosak/docks/obj/blood.c
 *
 * glain
 *
 * This blood is what is left behind from the bleeding wound that 
 * can be recieved from the wounding mace in ../obj/weapon/wound_
 * mace.c.  This is the smaller pool which means that the player
 * only bled in this room once.  Emotes will be added as thought of.
 *
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

int time;

void 
create_object()
{
   set_name(({"pool of blood","blood"}));
   set_short("pool of blood");
   set_pshort("pools of blood");
   set_long("This is a small puddle of freshly spilt blood.  " +
      "From the freshness you guess that the person bleeding " +
      "must have just passed through or is still here " +
      "somewhere.\n");

   add_prop(OBJ_I_NO_GET, 1);

   add_cmd_item("blood", "drink", "@@drink_blood");
   add_cmd_item("blood", "lick", "@@lick_blood");

   time = 600;
   set_alarm(itof(time), 0.0, "dry", TO);
}


string
lick_blood()
{
   write("You quickly take a lick of the blood pooled on the " +
      "ground.  Doesn't taste so good!\n");

   say(QCTNAME(TP) + " quickly takes a lick of the blood pooled " +
      "on the ground.  From the look on " + HIS(TP) + " face it " +
      "must not taste so good.\n");

   return "";
}


/*
 * Function name: dry
 * Description  : Destructs itself - its own little self-cleaning
 *                feature, as I though it would be a bad idea to have
 *                hundreds of these objects laying around for the
 *                whole uptime of the machine.
 *
 */
void 
dry()
{
   tell_room(E(TO), "The small pool of blood on the ground dries " +
      "up, leaving a small stain behind.\n", TO, TO);
   remove_object();
}