/* created by Erine /12/11/94 */
/* some simple stuff <panic and descs> added by Kishpa 10/02/96 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "/sys/global/cmdparse.c"
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

int alpeb, alload, alaim, alshoot;
object tstaff;
create_weapon()
{
   seteuid(getuid(TO));
   set_name("hoopak");
   set_adj("kender");
   set_wf(this_object());
   add_name("staff");

   set_short("kender hoopak");
   set_pshort("kender hoopaks");

   set_long("@@long_desc@@");
   set_default_weapon(27, 27, W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);
   add_prop(OBJ_I_VOLUME, 250);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,9) + random(40)); 
   tstaff = this_object();
}
string long_desc()
{
   string ken; /* to add_desc*/
   /* later it will be connected with function wield() so previous */
   /* wielder will be mentioned <not by name ofcourse> */
   object owner; // just to define where hoopak is. I wonder if it will work
      
   owner=E(TO);
   ken = "creator must have been your kin.\n";
   
   if(living(owner) != 1)
      {
      ken = "former user must have been a kender.\n";
   }
   else
      {
      if(owner->query_race_name() != "kender")
         ken = "former user must have been a kender.\n";
   }
   
   return("This is a staff, that is for sure, but not so usual "+
      "one. It is made from single piece of supple willow wood that, "+
      "from the forked top to the very end, is polished probably from "+
      "long usage. The bottom end of it is copper clad and comes to a "+
      "sharp point. The oposite side of it, is adjusted to be used as "+
      "catapult and holds a leather sling. Also some very bright coloured "+
      "feathers are attached at the top. Judging from the shape and "+
      "adornment it's " + ken );
   
}

void 
init()
{
   ::init();
   
   add_action("shoot_player", "shoot");
   add_action("make_noise", "swing");
   add_action("make_noise", "spin");
}

/* function : scared()
* desc     : makes listener of hoopak's sound to panic if coward
   * arg      : object victim - ob[i] that specific player
   */
void scared(object victim)
{
   int success;
   success = victim ->query_stat(SS_DIS) + (victim->query_stat(SS_INT) +
      victim->query_stat(SS_WIS))/2;
   success -= 20 + random(50);
   
   tell_object(victim, "You are shaken by the experience.\n");
   if(success <=0)
      {
      victim->add_panic(-success);
      tell_object(victim, "Scared to the bone by the eerie sound you "+
         "decide to look for a safer place.\n");
      tell_room(E(victim), QCTNAME(victim) + " cannot withstand the eerie "+
         "sound and looses his selfcontrol.\n", victim);
      victim->command("panic");
      victim->run_away();
   }
   else
      {
      victim->add_panic(20);
      tell_object(victim,"Sneering at the " + TP->query_race_name() + " you look not at " +
         "all scared of the eerie sound.\n");
      tell_room(E(victim), QCTNAME(victim) + " only sneers when " +
         QTNAME(TP) + " swings " + TP->query_possessive() + " hoopak.\n",
         ({victim, TP}));
      TP->catch_msg(QCTNAME(victim) +" only sneers when you swing your hoopak.\n");
   }
   return;
}
/* function: make_act()
* disp    : this function is called to force livings in room to do what we want
*           customize it that player will do some actions
*/
void make_act()
{
   object me,*ob;
   int i;
   
   me = TP;
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   if(ob != 0)
      {
      for (i = 0; i < sizeof(ob); i++)
      {
         scared(ob[i]);
      }
   }
   TP->catch_msg("There is noone to be scared except you.\n");   
}


int
make_noise(string str)
{
   int a;
   mixed *rooms = ({" "});
   mixed center;
   int g_file;
   
   if(present("hoopak", TP))
      {
      if(str == "hoopak" || str == "staff")
         {
         say(QCTNAME(TP) +" raises " + TP->query_possessive()+ " hand high in the "+
            "air and starts to spin "+ TP->query_possessive() +" hoopak. A hollow, "+
            "whinning sound that starts out low, grows higher and higher and "+
            "higher ... When it seems to be able to make your head explode it "+
            "comes to sudden end. Silence is as much terrifying as the sound "+
            "itself was.\n");
         
         write("You start to swing the hoopak over your head. For the moment nothing "+
            "happenes then suddenly it starts to generate a low sound at first and "+
            "it slowly rises to a high-pitched screaming sound. You decide to stop "+
            "because it is starting to put a strain on your arm.\n");   
         
         make_act(); // this one is to force players <livings> in room to 
         // perform some actions - panic for example
         
         center = file_name(E(TP));
         rooms = call_other(center,"query_exit_rooms");
         for(a = 0;a < sizeof(rooms); a++) 
         {
            mixed b;
            mixed *orign = ({" "});
            g_file = file_size(rooms[a]);
            if(!(g_file == -1 || g_file == -2))
               {
               orign = call_other(rooms[a],"query_exit");
               for(b = 0;b < sizeof(orign);b = b + 3)
               {
                  if(center == orign[b])
                     tell_room(rooms[a],"You hear a odd sound that seems" +
                     " to come from the " + orign[b+1] + ".\n");
               }
             }
         }
         
         return 1;
      }
      write("Swing what?!?\n");
      return 1;  
   }
   else
      write("You don't have anything to swing with.\n");
   return 1;
   
}

int
shoot_player(string str)
{
   string self;
   string a,b;int i;
   object * temparray;
   object target;
   object obj;
   /* If this code look fimiliar .. Well it should I was wonder around
   mackers workroom one day and when i got back home LO and Behold!
   this code was in one of my pouches so i decided to use it.. after
   all what good is code that is not in use :)
    Erine
   "Borrowed from code by macker feather.c"
   */
 if(present("hoopak", TP))
 {
   if(!(interactive(E(TO))))
     {
        write("Why would you want to shoot that?!?!\n");
        return 1;
     }

       if((!strlen(str) || !str))
         {
           write("Well darn it all anways. What are your gonna shoot?\n");
        return 1;
         }

        i = sscanf(str, "%s with %s", a, b);
        if(!((a)&&((b=="hoopak")||(b=="staff"))))
        {
                NF("Shoot who with what?!?\n");
                return 0;
        }
        temparray = (find_str_in_object(a, E(E(TO))));
        if(sizeof(temparray) == 0)
                target = 0;
        else
                target = temparray[0];
        if((i)&&((b=="hoopak")||(b=="staff"))&&((a=="me")||(a=="myself")))
                target = TP;
        if(!(living(target)))
        {
                NF("Seems like a useless idea to shoot that doesn't it??\n");
                return 0;
        }
        if((i)&&(((a=="me")||(a=="myself"))&&((b=="hoopak")||(b=="staff"))))

        if(!(((b=="hoopak")||(b=="staff"))&&(i)&&(target)))
        {
                        NF("Shoot who with what?\n");
                return 0;
        }
        if(target==TP)
        {
        if(TP->query_gender() == 0)
                self = "himself";
        else
        if(TP->query_gender() == 1)
                self = "herself";
        else
                self = "itself";
        write("This feat seems quite hard to accomplish not to mention " +
              "the fact you may miss and make someone lose an eye! " +
              "You decide not to do this.\n");
return 1;
        }
                NF("Shoot who with what?\n");
                if(!((target)&&(i)))
                return 0;
                if(TP->query_met(target))
                b = QCTNAME(target);
TP->catch_msg("You bend down and pick up a pebble from the ground.\n");
tell_room(E(TP),C(QCTNAME(TP)) + " bends down and pick a pebble up from "+
         "the ground.\n",TP);
alload = set_alarm(4.0,0.0,"load_hoopak");
alaim = set_alarm(6.0,0.0,"aim",a,target);
alshoot = set_alarm(8.0,0.0,"shoot",a,target);
  obj = clone_object("std/paralyze");
  obj->set_stop_object(tstaff);
  obj->set_stop_fun("stop_shoot");
  obj->set_remove_time(8);
  obj->set_fail_message("You are trying to shoot somebody with your " +
     "hoopak. Maybe you should 'stop' before trying anything else.\n");
  obj->set_stop_message("You stop trying to shoot people with your hoopak.\n");
  obj->move(TP);
        return 1;
 }
 write("If you want to shoot someone you first have to have something to "+
 "shoot with.\n");
}


void
load_hoopak()
{
TP->catch_msg("You proceed to load the hoopak.\n");
tell_room(E(TP), C(QCTNAME(TP)) + " sticks " +
    TP->query_possessive() + " tongue out as " +
    TP->query_pronoun() + " loads the hoopak with a pebble.\n",TP);
}

void
aim(string b, object target)
{
TP->cath_msg("You start to aim the hoopak at " + b +
    " and hope they stand still long enough for you to get them in yout "+
      "sight.\n");
target->catch_msg(QCTNAME(TP) + " aims the hoopak in your direction.\n");
tell_room(E(TP), QCTNAME(TP) +" aims the hoopak in " + b + "'s general "+
   "direction.\n", ({TP, target}));
}

void
shoot(string b, object target)
{
  TP->catch_msg("You let the pebble fly towards " + b + ".\n " + 
    "The pebble hits " + target->query_objective() + " harmlessly.\n");
  target->catch_msg(C(QCTNAME(TP)) + " lets the pebble fly from the hoopak.\n"
+
     "It hits you harmlessly and falls to the ground.\n");
  tell_room(E(TP), C(QCTNAME(TP)) + " let the pebble go and fly towards " +
QCTNAME(target) +
     ".\nThe pebble hits " + target->query_objective() + " harmlessly and "
     + "falls to the ground.\n",({TP,target}));
}
void
stop_shoot()

{
remove_alarm(alload);
remove_alarm(alaim);
remove_alarm(alshoot);

}
mixed
wield(object what)
{

if (TP->query_race_name() != "kender")
return "Only kender can wield a hoopak properly!\n";

wielder = TP;
return 0;
}
