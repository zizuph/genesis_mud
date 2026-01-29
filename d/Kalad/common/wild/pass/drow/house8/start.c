inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/drow/guild/default.h"
#define CAN_START_NOQUAR "_can_start_noquar"
/* by Antharanos */
create_room()
{ 
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A resting area for members of House Noquar");
   set_long("A resting area for members of House Noquar\n"+
      "This room is bathed in the eerie red glow of magical faerie fire, "+
      "red light that is presently illuminating several giant spider webs, "+
      "as well as numerous chests of adamantine. The major feature of the "+
      "room is the glowing red pyramid at the exact center of it.\n"+
      "A black archway lies to the east.\n");
   add_item(({"resting area","area","room"}),
      "A relatively safe and comfortable place which members of House "+
      "Noquar may use when they are not out furthering the cause of Lolth "+
      "and House Noquar.\n");
   add_item(({"eerie red glow","eerie glow","red glow","glow","magical faerie fire","magical fire","faerie fire","fire"}),
      "Intricate geometric designs lace the entirety of the room, providing "+
      "an eerie red illumination for any therein.\n");
   add_item(({"giant spider webs","giant webs","spider webs","webs","web"}),
      "Although delicate in appearance, the incredibly soft silken strands "+
      "make the perfect beds.\n");
   add_item(({"chests","chest"}),
      "Sturdy reinforced adamantine constructs used to store the possessions "+
      "of the various members of House Noquar.\n");
   add_item(({"glowing red pyramid","glowing pyramid","red pyramid","pyramid"}),
      "A three by three by three foot object ensorcelled with red faerie fire. "+
      "One side has a plaque on it, upon which writing has been placed.\n");
   add_item(({"black archway","archway"}),
      "It appears to lead out of this area into another chamber...\n");
   add_item("plaque","There is writing on it.\n");
   add_cmd_item("plaque","read",
      "Members of House Noquar may 'start here' if they so choose.\n");
   add_prop(ROOM_M_NO_ATTACK, "The feeling of peace is too great here.\n");
   add_exit(CPASS(drow/house8/chapel),"east","@@msg",-1,-1);
   set_noshow_obvious(1);
   clone_object(CPASS(drow/obj/h8_chest))->move(TO);
}
void
init()
{
   ::init();
   AA(start,start);
}
int
start(string s)
{
   if(s =="here" && (IS_MEMBER(TP)) && (TP->query_prop(CAN_START_NOQUAR)))
      {
      TP->set_default_start_location("/d/Kalad/common/wild/pass/drow/house8/start");
      write("From now on you shall begin your adventures and intrigues "+
         "from this place, the compound of House Noquar.\n");
      return 1;
   }
   
   write("Either you can't type or you are not a member. Please try again.\n");
   return 1;
}
msg()
{
   write("You enter the black archway...\n");
   say(QCTNAME(TP) + " enters the black archway...\n");
   return 0;
}
