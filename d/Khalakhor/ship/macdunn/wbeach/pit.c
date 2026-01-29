// Pit - a ceremonial pit, part of the Sean-Rhian entrance quest
//       a seeker brings 9 tree branches needed, places them in the
//       pit, invokes the deity who sends a ball of fire to burn
//       the branches. The remaining ash is needed for the rest
//       of the quest.
//
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 6/3/98      Zima        Created
//
//
inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Khalakhor/guilds/sean-rhian/defs.h"
#include "/d/Khalakhor/guilds/sean-rhian/objects/branch.h"
#include "/d/Khalakhor/guilds/sean-rhian/objects/powder.h"
#include "/d/Khalakhor/sys/defs.h"
#define  INVOCATION "the cleansing fires of ardaugh"
int responding=0;
 
//
// create_container
//
void create_container()
{
    set_name("pit");
    set_adj(({"large","ceremonial","circular","blackened"}));
    set_short("large pit encircled by ten stone pillars");
    set_long(
       "It is a large circular pit hewn into the stone of the floor "+
       "of the plateau. Its bowl-like surface seems to have been charred "+
       "by fire. Ten stone pillars encircle the pit, the one to the south "+
       "larger than the other nine. It looks like some kind of ancient "+
       "ceremonial site.\n");
 
    add_item(({"pillar","pillars"}),
       "Ten pillars stand around the pit in a circle, each mostly just "+
       "a pile of stones which rise a little above your head. The "+
       "pillar on the south edge of the circle is a bit larger and "+
       "taller than the other nine.\n");
    add_item(({"south pillar","large pillar","tall pillar"}),
       "The large pillar to the south is just has a wider diameter and "+
       "is taller than the others. Other than its size, it doesn't "+
       "seem very different.\n");
    add_item(({"surface","surface of pit","surface of the pit","soot"}),
       "The surface of the pit is smooth and bowl-like, seemingly "+
       "hewn into the stone floor of the plateau. It is covered "+
       "with dark soot as if something has been burned in it.\n");
 
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_WEIGHT,1000000);
    add_prop(CONT_I_MAX_VOLUME,100000);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_NO_GET,1);
 
}
 
//
// branches_here - are all the required branches here?
//
int branches_here()
{
   int i;
   for (i=0; i<NUM_BRANCHES; i++)
      if (!present(BR_ID_PREF+BRANCH[i],TO))
         return 0;
   return 1;
}
 
//
// wrong - respond to wrong invocation
//
void wrong(int rc, object rm)
{
   string m;
   switch (rc) {
      case 1:m="The wind picks up slightly then returns to its normal gale.";
             break;
      case 2:m="The clouds begin to roll above then return to normal.";
             break;
      case 3:m="The clouds begin to roll above.\nYou hear a voice say: "+
               "\nHe who is not favored by the servants of the Servant is "+
               "not heard.";
             break;
      case 4:m="The clouds begin to roll above.\nYou hear a voice say:\n"+
               "I have heard your invocations aspirant, and have answered.";
             break;
      case 5:m="The clouds begin to roll above and turn fire red.\n"+
               "The contents of the pit begins to glow, but then fades.";
             break;
      default:m="There is a rip in the fabric of space in the pit.";
   }
   responding=0;
   tell_room(rm,m+"\n");
}
 
 
//
// resp - respond to a correct invocation
//
void resp(int step, object tp, object rm)
{
   string m;
   int    i,ok;
   object *inv, ash;
 
   if (!present(tp,rm)) step=0;
 
   switch (step)
      {
      case 1:m="The clouds begin to roll in torment in the sky above.";
             break;
      case 2:m="Thunder and lightning rumble through the clouds "+
               "as they turn fiery red!";
             break;
      case 3:m="A ball of fire spews from the clouds and crashes into "+
               "the stone pit!";
             ok=branches_here();
             inv=all_inventory(TO);
             for (i=0; i<sizeof(inv); i++)
                (inv[i]->remove_object());
             if (ok)
                {
                seteuid(getuid());
                ash=clone_object(SR_OBJ+"powder");
                ash->set_powder(POWDER_INCENSE2);
                ash->move(TO);
                }
             break;
      default:m="The clouds return to normal and the skies clear.";
              responding=0;
      }
   tell_room(rm,m+"\n");
   if (responding) set_alarm(7.0,0.0,&resp((step+1),tp,rm));
}
 
//
// invoke - allow an aspirant to invoke the fires
//
int invoke(string cmd)
{
   int rc,level;
   object pen=present(SHAM_PENDANT,TP), rm=ENV(TO);
 
   if ((!objectp(pen))||responding) return 0;
   level=(pen->query_level());
   if (!stringp(cmd))                       { rc=1; cmd="vainly"; }
   else if (lower_case(cmd)!=INVOCATION)    rc=2;
   else if (level<2)                        rc=3;
   else if (level>2)                        rc=4;
   else if (!branches_here())               rc=5;
   else                                     rc=0;
 
   if (rc)
      set_alarm(7.0,0.0,&wrong(rc,rm));
   else
      set_alarm(7.0,0.0,&resp(1,TP,rm));
   responding=1;
 
   write("You raise your hands and invoke "+cmd+".\n");
   tell_room(rm,QCTNAME(TP)+" raises "+HIS_HER(TP)+" hands and makes an "+
                     "invocation.\n",TP);
   return 1;
}
 
//
// init - to add actions
//
void init()
{
   ::init();
   add_action(&invoke(),"invoke");
}
