inherit "/std/room";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

object follower;

void
create_room()
 {
  set_short("Leader's Quarters");
  set_long("A good sized room opens before you here.  Unlike the "
  	+"squalor of the main encampment, this room is lavishly "
  	+"decorated.  Large pillows cover a portion of the floor, "
  	+"acting as both bed and casual seating.  A few small "
  	+"chests lie around the room, as well as a large footlocker."
  	+"  Against the wall near the entrance is a large desk and "
  	+"chair covered in parchment and writing instruments.  "
  	+"Whoever lives in this room is an extraordinary gith indeed.\n");
  add_item(({"pillow","large pillow","pillows","large pillows"}),
  	"Designed as a combination bed, and general seating, "
  	+"these pillows are of all shapes and sizes.  The one "
  	+"universal attricute they all share os the obvious value "
  	+"they have.  Crafted in fine satins, cottons, and wools "
  	+"and interwoven with fine gold thread, they look to be fit "
  	+"for a king.\n");
  add_item("footlocker","It is a large wooden chest bound in iron "
  	+"that looks to be very old, yet sturdy.  It is closed "
  	+"at the moment, and you see no lock on it.\n");
  add_item(({"hole","rent"}),"It looks to have been created a long "
  	+"time ago, "
  	+"probably during some forgotten conflict.  It leads into "
  	+"the fortress.\n");  
  add_item(({"chests","small chests","chest","small chest"}),
  	"There are chests of all varieties here, ranging from "
  	+"small jewelry box size chests, to chests which were "
  	+"obviously used for coins, perfumes, many things.  They "
  	+"look to be spaced about to make it look there is more "
  	+"value here than there really is.\n");
  add_item("desk","A beautiful deep red wood, this is an exquisite "
  	+"agafari wood desk.  Agafari wood is lustrous in color, as "
  	+"well as incredibly tough.  This desk can withstand a lot "
  	+"of punishment and still retain its luster.  There is a "
  	+"matching chair at the desk as well.  There are a variety "
  	+"of papers scattered across the desk.\n");
  add_item("chair","Made of the same deep red agafari wood as the "
  	+"desk, this chair is obviously its partner.  Soft cushions "
  	+"pad the seat, back, and arms, making it look to be an "
  	+"extremely comfortable chair.  Unfortunately for the "
  	+"gith, their hunched backs do not make chairs popular.\n");
  add_item(({"pad","pads"}),"They are on the chair and are there "
  	+"for comfort.\n");
  add_item(({"parchment","paper","papers","parchments"}),
  	"A large number of yellowed papers and parchments cover "
  	+"the desk, some with writing, some with just symbols.\n");
  add_item(({"writing","symbols","symbol"}),"You are unable to "
  	+"decipher the ancient writing, or the cryptic symbols.\n");
  add_item(({"instruments","writing instruments","instrument"}),
  	"Pieces of sharpened, hollowed-out bone form crude quills "
  	+"that can write.  They aren't fancy, but they are "
  	+"functional.\n");
  add_cmd_item("chest","open","You strain against the chest, but to "
  	+"no avail, it appears to be locked.\n");
  add_cmd_item("chest","unlock","You search for a way to unlock the "
  	+"chest, but notice no keyhole and no lock mechanism.  "
  	+"Strange indeed.\n");
   add_exit(CAMP + "c25","northeast","@@block");
   set_alarm(1.0,0.0,"reset_room");
}

int
block()
{
    object leader;
    leader = present("windreaver");
    if(member_array(leader,TP->query_enemy(-1))!=-1)
     {
      TP->catch_msg("You try to escape, but the gith have cunningly "
	   +"trapped you in the room!\n");
      return 1;
     }
    return 0;
}
void
reset_room()
{
    if (leader) return;
  bring_room_team(GITH_NPC+"g_leader",1,3,GITH_NPC+"g_guard",1);

}

