// Mountain Cold Fatigue
// Tomas  -- Feb 2000

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>


inherit STDROOM;

public int fatigue(int power, int res,int fat, int fur);
void freeze_me();

public void
create_room()
{
    ::create_room();

    freeze_me();

    reset_room();
}


void
freeze_me()
{
  set_alarmv(-1.0, 0.0, "fatigue",({TP}));
  return;
}


public int
fatigue(int power, int res, int fat, int fur)
{
   string mesg, fatmesg;
   power = (5 + random(10));
   res = (TP->query_magic_res(MAGIC_I_RES_COLD));
   fur = (TP->query_prop("wearing_fur"));
   fat = (0 + random(5));  

    if (TP->query_wiz_level())
    {
        return 0;
    }

   switch(power)
     {
        case 0 .. 4:
          mesg = "The cold wind chills your body slightly.\n";
          break;
        case 5 .. 8:
          mesg = "You feel a bit weary.\n";
          break;
        case 9 .. 13:
          mesg = "The icy weather nips at your strength.\n";
          break;
        case 14 .. 15:
          mesg = "You stumble slightly as you suddenly feel " +
                 "rather tired.\n";
          break;
          default:
          mesg = "The bitter cold begins to take its toll. " +
                 "You feel your strength gently ebbing away.\n";
          break;
      }

   switch(fat)
     {
        case 0 .. 4:
          fatmesg = "You wrap yourself tighter within your warm " +
                 "clothing as the wind whips around your body.\n";
          break;
        case 5 .. 8:
          fatmesg = "You shiver slightly in your warm clothing.\n";
          break;
          default:
          fatmesg = "You feel the weather nip at the exposed areas " +
                 "of your body.\n";
          break;
      }
  

   if(res >= power)
   {
      write("wearing cold res");
      return 0;
   }

   if(fur)
   {
       write("wearing furs" + fat + "\n");
       TP->add_fatigue(- fat);
       TP->catch_msg(fatmesg); 
      return 0;
   }
       write("default - " + power + "\n");
     TP->add_fatigue(- power);
     TP->catch_msg(mesg);
     return 0; 
}
