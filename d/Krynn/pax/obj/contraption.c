/* 
   contraption.c
   -------------

   Coded ........: 95/03/11
   By ...........: Jeremiah

   Latest update : 95/06/09
   By ...........: Jeremiah

*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

int    swinging  = 0; /* 1 = someone just hit the shield             */
int    att_duck  = 0; /* 1 = the player attempts to duck             */
int    ducking   = 0; /* 1 = the player who hit is ducking           */
int    att_cover = 0; /* 1 = the player attempts to cover            */
int    covering  = 0; /* 1 = the player who hit is covering (shield) */
int    alarm_id  = 0; /* id of the cover/duck set_alarm function     */
object hitter;        /* the one who just hit the shield             */

void
create_object()
{
   set_name(({"thing", "contraption", "strange contraption"}));
   set_short("strange contraption");
   set_long("A highly peculiar contraption. A seven foot pole solidly " +
            "mounted, vertically, in a stone base on the floor. It looks " +
            "as if the pole is able to rotate around its own axis. Around " +
            "the stone base, a wooden rack has been placed to support the " +
            "vertical pole. About 5 feet above the base, a smaller pole " +
            "has been attached, in a hole drilled into the first pole, " +
            "horizontally, stretching equally to each side. At the point " +
            "where to two poles are connecting, they have been reinforced " +
            "by leather strappings. On the right side on the horizontal " +
            "pole, a wooden shield has been fixed, and on the left side, " +
            "a heavy sandbag. A bag, with a crude drawing of a grinning " +
            "face, has been pulled over the top of the vertical pole.\n");
   

   add_item(({"shield", "wooden shield"}), "A large wooden shield fixed to " +
            "the horizontal pole of the contraption. It has many cuts, as " +
            "if someone has been hitting on it with sharp weapons. Maybe " +
            "you can try to hit the shield too?\n");

   add_item("sandbag", "This is a heavy bag filled with sand. You are " +
            "quite sure that it would hurt pretty bad if someone, for " + 
            "some reason, was to drop it on you, or hit you with it.\n");

   add_item("bag", "A bag pulled over the top of the vertical pole. " +
            "A grinning face has been crudely drawn on the bag. Somehow " +
            "you feel it is looking mockingly at you.\n");

   add_item(({"pole", "poles"}), "There are two poles. a large seven " +
            "foot pole, placed in a stone base on the floor, rising " +
            "vertically into the air, and a smaller, about six foot, pole " +
            "attached horizontally to the larger pole.\n");

   add_item(({"base", "stone base"}), "A rather large square stone " +
            "with a hole down the center. A greasy substance has been " +
            "applied to the hole. A pole has been vertically placed into " +
            "the hole, and the greasy substance seems to make is easier " +
            "for the pole to rotate around its axis. On each side of the " +
            "base an iron handle has been mounted.\n");

   add_item(({"rack", "wooden rack"}), "A solid wooden rack mounted " +
            "over and into the stone base, to stabilize and support " +
            "the vertical pole.\n"); 

   add_item(({"strappings", "leather strappings"}), "Leather strappings " +
            "tied reinforcingly around the point where tho two poles " +
            "are connected.\n"); 
 

   add_prop(OBJ_I_NO_GET,"This thing is far to bulky for you to carry.\n");
   add_prop(OBJ_I_NO_INS,"This thing is far to bulky for that.\n");
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_WEIGHT,150000);
   add_prop(OBJ_I_VOLUME,200000);

   seteuid(getuid(TO));
}


init()
{
   ::init();
   add_action("do_hit", "hit");
   add_action("do_duck", "duck");
   add_action("do_cover", "cover");
   add_action("do_disassemble", "disassemble");
}


string
wielding()
{
   object *weapons;

   weapons = TP->query_weapon(-1);
   if(sizeof(weapons) > 0)
      return weapons[0]->short();

   return 0;
}


void
swing_sandbag(object who)
{
   if((!ducking) && (!covering))
   {
      who->catch_msg("The sandbag swings around, and hits you hard " + 
                     "over the head. You fall to the ground in a very " +
                     "unflattering way. You weren't fast enough to duck " +
                     "or cover yourself .. What a bummer!\n" +
                     "What was that? didn't the face on the pole grin " +
                     "at you?\n");

      tell_room(E(TO), "The sandbag swings around, and hits " + QCTNAME(who) +
                " over the head. " + C(PRONOUN(who)) + " falls to the " +
                "ground in a very unflattering way. " + C(PRONOUN(who)) +
                " looks rather baffled.\n", who);  
   }

   if(ducking)
   {
      who->catch_msg("The sandbag swings harmlessly over your head. " +
                     "You managed to duck in time to avoid it. Very " +
                     "impressive!\n");
 
      tell_room(E(TO), "The sandbag swings harmlessly over the head of " +
                QCTNAME(who) + ". " + C(PRONOUN(who)) + " managed to " + 
                "duck in time to avoid getting hit. Quite impressive!\n", 
                who);
   }

   if(covering)
   {
      who->catch_msg("The sandbag hits your shield with a heavy 'THUD!'. " +
                     "The impact of the sandbag forces you to take a step " +
                     "backwards. You managed to cover yourself with your " +
                     "shield. Very good!\n");
 
      tell_room(E(TO), "With a heavy 'THUD!', the sandbag hits " + 
                QCTNAME(who) + "'s shield. The impact of the sandbag " + 
                "forces " + OBJECTIVE(who) + " to take a step backward. " +
                C(PRONOUN(who)) + " managed to cover " + OBJECTIVE(who) +
                "self with " + POSSESSIVE(who) + " shield. It looked " +
                "very good. Maybe you should try?.\n", who);
   }

   hitter    = 0;
   swinging  = 0;
   att_duck  = 0;
   ducking   = 0;
   att_cover = 0;
   covering  = 0;
   if(alarm_id)
   {
      remove_alarm(alarm_id);  
      alarm_id = 0;
   }
}


int
do_hit(string what)
{
   int delay;

   if(swinging)
   {
      write("The shield is in motion, you cannot hit it now.\n");
      return 1;
   }   

   if((what == "shield") || (what == "wooden shield"))
   {
      if(!wielding())
      {
         write("You try to hit the wooden shield, but in the last moment " +
               "you remember that you're not wielding anything. So you " +
               "decide not to try. You might hurt your hand.\n");
         return 1;
      }  
      
      hitter = TP;
      swinging = 1;
      
      write("You swing your " + wielding() + " at the wooden shield, " +
            "and hit it!. The shield flies away from you. The " +
            "center pole rotates around its own axis, and the sandbag " +
            "comes flying against you.\n");

      say(QCTNAME(TP) + " swings " + POSSESSIVE(TP) + " " + wielding() +
          " at the wooden shield and hits it. The shield flies away from " +
          OBJECTIVE(TP) + ". The center pole rotates around its own axis " +
          "and the sandbag comes flying against " + OBJECTIVE(TP) + ".\n");


      delay = 400/(TP->query_stat(0)) + 1;
      set_alarm(itof(delay), 0.0, "swing_sandbag", TP);

      return 1;
   }
   NF("You try to hit what?, the shield maybe?\n"); 
   return 0;
}


void
avoid_sandbag(object who)
{
   object lwho;
 
   lwho = who;
   ducking = 1;

   lwho->catch_msg("You duck, attempting to avoid the swinging " +
                     "sandbag.\n");

   tell_room(E(lwho), QCTNAME(lwho) + " ducks, attempting to avoid " +
             "the swinging sandbag.\n", lwho);
} 


int
do_duck(string what)
{
   int delay;

   if(TP != hitter)
   {
      write("There's no reason to duck now. Is there ?\n");
      return 1;
   }

   if(att_duck)
   {
      write("Yes, yes");
      return 1;
   }

   att_duck = 1;

   delay = 400/(TP->query_stat(0)) - 1;
   if(delay < 1)
      delay = 1;

   alarm_id = set_alarm(itof(delay), 0.0, "avoid_sandbag", TP);
   return 1;
}


void
cover_sandbag(object who)
{
   object lwho;

   lwho = who;
   covering = 1;

   lwho->catch_msg("You raise your shield, attempting to cover yourself " +
                     "against the swinging sandbag.\n");

   tell_room(E(lwho), QCTNAME(lwho) + " raises " + POSSESSIVE(lwho) +  
             " shield, attempting to cover " + OBJECTIVE(lwho) + 
             "self against the swinging sandbag.\n", lwho);
}


int
do_cover(string what)
{
   int delay;

   if(TP != hitter)
   {
      write("There's no reason to cover now. Is there ?\n");
      return 1;
   }

   if(!(member_array(A_SHIELD,(TP->query_armour(-1))->query_at()) >= 0))
   {
      write("It won't do you any good trying to cover yourself, without " +
            "anything to cover yourself with. Maybe use a shield?\n");
      return 1;
   }

   if(covering)
   {
      write("Yes, yes");
      return 1;
   }

   att_cover = 1;

   delay = 400/(TP->query_stat(1)) - 1;
   if(delay < 1)
      delay = 1;

   alarm_id = set_alarm(itof(delay), 0.0, "cover_sandbag", TP);
   return 1;
}


int
do_disassemble(string what)
{
   int    i;
   string *parts = ({"stone_base", "wooden_rack", "vpole", "hpole",
                    "cshield", "sandbag", "bag", "strappings"});

   if(!what)
   {
      write("Disassemble what?\n");
      return 1;
   }

   if(what != "thing" && what != "contraption" &&
      what != "strange contraption")
   {
      write("You don't think you see that anywhere here.\n");
      return 1; 
   }

   if(!(TP->test_bit("krynn", 1, 15)))
   {
      write("You try to disassemble the strange contraption, " +
            "but somehow you don't seem to get the grasp of " +
            "the idea behind it all.\n");
      tell_room(E(TO), QCTNAME(TP) + " starts to pull at the strange " +
            "contraption, then gets an expression of utter confusion " +
            "on the face, and gives up.\n", TP, TO);

      return 1;
   }

   write("With gnomish expertise, you disassemble the strange " +
         "contraption\n");
   tell_room(E(TO), "With gnomish expertise, " + QCTNAME(TP) + 
         " disassembles the strange contraption.\n", TP, TO);

   for(i=0; i<8; i++)
   {
      clone_object(POBJ + parts[i])->move(E(TO));
   }
   
   remove_object();
   return 1;
}

