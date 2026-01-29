inherit "/std/shadow";
 
#include "/d/Rhovanion/defs.h"
#include <macros.h>
 
object swho;
 
void heal_hp(int amount)
{
  int ramount;
  ramount=amount;
  if (amount<0) ramount=-random(-amount);
  if ((random(100)==50)&&(amount<0))
    {
       ramount=-random(-amount*7);
       say("Suddenly there is a bright flash of light around your "+
             "body!\n"+
             "You feel as your magical shield sucks blood from "+
             "your fresh wounds !!!\n"+
             "You scream in pain!\n");
       write("Suddenly there is a bright flash of light around "+
             QTNAME(swho)+"'s body!\n"+
             QTNAME(swho)+" screams in pain!\n");
    }
  swho->heal_hp(ramount);
}
 
object subl_shield;
 
void shadow_me(object whom)
{
  swho=whom;
  subl_shield=clone_object("/d/Rhovanion/paladin/camp/subl_shield.c");
  subl_shield->move(swho);
  subl_shield->install();
  write("As you mutter ancient words of power a magical shield "+
        "glowing in all rainbow colours appears around your body!\n");
  say("As "+QTNAME(swho)+" mumbles something a bright magical "+
      "shield glowing in all rainbow colours appears around "+
      HIS(swho)+" body!\n");
  ::shadow_me(swho);
}
 
void destruct_shield_shadow()
{
  set_alarm(150.0+itof(random(150)),0.0,"dest_shadow");
}
 
void dest_shadow()
{
  subl_shield->remove_me();
  write("Magical shield leaves your body!\n");
  say(QCTNAME(swho)+" shivers slightly as a magical shield leaves "+
      HIS(swho)+" body!\n");
  ::remove_shadow();
}
 
int shield_shadow_exist()
{
  return 5;
}
