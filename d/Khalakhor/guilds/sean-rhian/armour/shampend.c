//
// Shamrock Pendant - pendant worn by those seeking to enter the
//                    Order who have been given permission.
//                    Autoloading object
//                    Wearable object
//                    Needed to do the entrance quest
//
// Zima   May 26, 1998
//
inherit "/std/object";
inherit "/lib/wearable_item";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "defs.h"
 
int level=0;
int *chant=({0,0,0,0,0,0,0,0,0,0});
 
int* query_chant()       { return chant; }
 
public void update_desc()
{
   string metal;
   switch (level)
      {
      case 0: metal="copper";   break;
      case 1: metal="silver";   break;
      case 2: metal="gold";     break;
      case 3: metal="platinum"; break;
      case 4: metal="diamond";  break;
      }
   set_short(metal+" shamrock pendant");
   set_long("It is a small "+metal+" pendant worn upon the chest, cast in "+
            "the form of a shamrock. It is engraved with the words: "+
            "Seek Wisdom in the Mysteries revealed unto Ossian.\n");
}
 
void set_level(int i)    { level=i; update_desc(); }
int  query_level()       { return level;           }
 
public nomask void create_object()
{
    set_name("pendant");
    add_name(SHAM_PENDANT);
    add_adj(({"shamrock","asipirant","sean-rhian"}));
    update_desc();
 
    set_slots(A_CHEST);
    set_layers(0);     // allow other things to be worn on the chest
    set_looseness(3);  // allow up to 3 things worn beneath on chest
 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE,  0);
    chant[0]=1; // not used, so give it to 'em
}
 
public void leave_env(object env, object to)
{
    // 'remove pendant' if still worn and leaving player
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
 
// Autoload - save/restore level on quit/login; disable recovery
string query_auto_load()    { return (MASTER+":"+level); }
void   init_arg(string arg) { level=atoi(arg); update_desc(); }
string query_recover()      { return 0; }
 
public canticles_done(object tp, int i, object room)
{
   object rm=ENV(tp);
   float  satime=6.0;
   if (rm!=room) return;
   switch (i) {
      case 1:
              if (level<1)
                 {
                 tp->catch_msg("You hear a voices in your mind. They say:\n"+
                               "Who are you to honor us?\n"+
                               "One who has not adored the holy icon!\n"+
                               "Your praises go unheard!\n");
                 return;
                 }
              else if (level>1)
                 {
                 tp->catch_msg("You hear a voices in your mind. They say:\n"+
                               "Your praises are heard once again, "+
                               "apirant to the Harmony of Ardaugh\n");
                 return;
                 }
              tell_room(rm,"A gentle breeze begins to move and grow in "+
                           "strength.\n");
              break;
      case 2: tp->catch_msg("A vision of nine mystical figures begins to "+
                            "emerge in your mind.\n");
              tell_room(rm,QCTNAME(tp)+" seems to go into a trance.\n",tp);
              break;
      case 3: tp->catch_msg("The figures say in unison: Your canticles "+
                            "of praise have been heard, aspirant!\n");
              satime=3.0;
              break;
      case 4: tp->catch_msg("The figures say in unison: You have gained "+
                            "our favor! May Ardaugh be your guide!\n");
              set_level(2); // aspirant advances to next level
              satime=3.0;
              break;
      case 5: tp->catch_msg("The figures say in unison: Go in Harmony, "+
                            capitalize(tp->query_name())+"!\n");
              break;
      case 6: tp->catch_msg("The figures disappear and your mind clears.\n");
              tell_room(rm,QCTNAME(tp)+" seems to come out of "+
                           HIS_HER(tp)+" trance.\n",tp);
              break;
      case 7: tell_room(rm,"The mysterious breeze dies down and ceases.\n");
              return;
      default:tell_room(rm,"There is a rip in the fabric of this space.\n");
   }
   set_alarm(satime,0.0,&canticles_done(tp,(i+1),rm));
}
 
public void report_correct_chant(int cnum, object tp)
{
   int i, done_all=1;
   if ((cnum<0)||(cnum>=sizeof(chant))) return; // incorrect number
   chant[cnum]=1;
 
   // see if all chants have been done
   for (i=0; i<sizeof(chant); i++)
      if (chant[i]==0) done_all=0;
 
   // if all done, aspirant has completed this stage
   if (done_all) set_alarm(5.0,0.0,&canticles_done(tp,1,ENV(tp)));
}
void reply_prayer(object tp, object mon, object altar, int step)
{
   object rm=environment(altar);
   if ((!objectp(tp)) || (rm!=ENV(tp))) return;
   switch (step) {
      case 1: if (level>0)
                 {
                 tp->catch_msg("You hear a voice in your mind saying:\n"+
                 "Perserve in faith aspirant, and you shall receive!\n");
                 return;
                 }
              tell_room(rm,"The shamrock in the "+(mon->short())+
                 " begins to glow more brightly.\nThe flames of the "+
                 "candles flanking the "+(altar->short())+" flicker "+
                 "wildly.\n");
              break;
      case 2: tp->catch_msg("A vision of a beatiful angel begins to form "+
                            "in your mind.\n");
              break;
      case 3: tp->catch_msg("The angel says: Your prayers have been heard, "+
                            "aspirant!\n");
              break;
      case 4: tp->catch_msg("The angel says: Perservere in faith and "+
                            "you shall receive wisdom!\n");
              break;
      case 5: tell_room(rm,"The shamrock in the "+(mon->short())+
                            " dims slightly.\n");
              set_level(1); // advance to next level
              return;
     default: tp->catch_msg("There is a tear in the fabric of space in "+
                            "your pendant.\n");
   }
   set_alarm(6.0,0.0,&reply_prayer(tp,mon,altar,(step+1)));
}
 
void report_prayer(object tp, object monstrance, object altar)
{
   set_alarm(7.0,0.0,&reply_prayer(tp,monstrance,altar,1));
}

/* Function name: appraise_object (MASK)
 * Description  : Appraise the object.
 * Arguments    : int num - The appraise number, randomized.
 * Returns      : n/a
 */

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
