inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by korat 
 * The npc in this room takes any object with 'mithril' in its
 * description. He also repairs a specific armour. 
*/

object smith;

void
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("within a smith in Underhome");
   set_long("From the furnace in the center of this room, a steady "+
      "blazing heat pours out, shining up everything in the "+
      "room with a red, flickering colour. "+
      "A large basin of polluted water stands along the wall, "+
      "sending out a steady stream of steam as red-hot "+
      "pieces of metal is inserted into it. The neverending "+
      "sound of heated metal being hammered into "+
      "desired shapes on the large iron anvil, fills "+
      "the room.\n");
   add_item("basin","The basin is cut out of the rock and "+
      "contains many gallons of polluted water.\n");
   add_item("anvil","It is a heavy iron block with a smooth "+
      "face of steel, on which heated metal are hammered into the "+
      "shape of shields, platemails and other artifacts of warfare.\n");
   add_item("furnace","It is a structure where the metal is "+
      "heated up until it is red-hot and ready to be formed by "+
      "skilled hands.\n");
   
   add_exit(CPASS(dwarf/s17),"east","@@msg",-1,-1);

   set_alarm(2.0,0.0,"reset_room");
}

void
reset_room()
{
   if(!objectp(smith))
      {
      smith=clone_object(CPASS(dwarf/npc/blacksmith2));
      smith->arm_me();
      smith->move_living("M",TO);
      tell_room(TO,"A blacksmith starts to hammer on a red-hot "+
         "piece of steel.\n");
   }
}

int
msg()
{
   write("You leave the oppressive heat of the forge behind.\n");
   say(QCTNAME(TP) + " looks relieved as " + TP->query_pronoun() + " exits "+
      "the building.\n");
   return 0;
}


void
init()
{
   ::init();
   add_action("do_offer","offer",0);
   add_action("do_fix","mend",0); /* no mending, but we react to it */
   add_action("do_fix","wax",0);  /* no waxing, but we react to it */
}

int
do_fix(string str)
{
   object *weapon;
   int int_str, value, is_armour, is_weapon, *money_arr;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
   verb;
   
   verb = query_verb();
   
   if (!str)
   {
      smith->do_say(capitalize(verb) + " what?");
      return 0;
   }
   
   /*   Check if the player defines what she wants to pay with
    *   and what you would like in return.
   */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
      {
      get_type = "";
      /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
         {
         pay_type = "";
         item_name = str;
       }
   }
   
   if (pay_type != "")
      {
      if (member_array(pay_type, MONEY_TYPES) < 0)
         {
         tell_room(this_object(), break_string(
               "The smith says: I don't accept those " + pay_type + " coins, "
            + TP->query_nonmet_name() + ".\n",70));
         return 1;
       }
   }
   
   if (get_type != "")
      {
      if (member_array(get_type, MONEY_TYPES) < 0)
         {
         smith->do_say(capitalize(get_type) + " coins? Never "
               + "heard of those.");
         return 1;
       }
   }
   
   if (!(weapon = FIND_STR_IN_OBJECT(str,TP)) ||
         !sizeof(weapon))
   {
      smith->do_say("Mend what?");
      return 1;
   }
   
   if (sizeof(weapon) > 1)
   {
      smith->do_say("Be more specific. Which one?");
      return 1;
   }

   is_armour = function_exists("create_object",weapon[0]) != "/std/weapon";
   is_weapon = function_exists("create_object",weapon[0]) != "/std/armour";

   if (!is_armour && !is_weapon)
   {
      smith->do_say("You cannot be serious!");
      return 1;
   }

   /* We check if it is a weapon - if so we return a string */
   if (is_weapon)
   {
      smith->do_say("Go and see the weapon-smith just south of here. "+
         "I deal with armours, stranger!");
      return 1;
   }

   /* We check if this armour is kabals platemail */
   if (is_armour && weapon[0]->query_prop("_kabal_platemail"))
   {
      smith->command("gasp");
      smith->do_say("This cannot be true!");
      smith->do_say("It is the platemail of our bane, Kabal! "+
          "And it is of pure mithril!!");
      if (TP->query_prop("_korat_did_give_mithril"))
      {
         smith->do_say("I will fix it for you since you sold me "+
            "some mithril today. This platemail is magical though "+
            "so I cannot be sure how well the repair will be.");
         smith->command("emote starts to work on the platemail.");
         smith->command("emote shouts to his workers to heat up "+
             "the furnace.");
         smith->command("emote melts some silverish metal.");
         smith->command("emote heats up the ruined parts of the "+
             "ancient platemail.");
         smith->do_say("Hard work this!");
         smith->command("emote starts to hammer on the platemail, "+
             "adding the silverish metal to it.");
         smith->command("emote seems to be finnished.");
         weapon[0]->remove_prop(OBJ_I_BROKEN);
         weapon[0]->set_condition(0);
         weapon[0]->set_ac(random(11)+40); /* ac between 40 and 50 */
         switch (weapon[0]->query_ac())
         {
            case 0..42:
               smith->do_say("The result was not as good as I hoped.");
               break;
            case 43..45:
               smith->do_say("I am happy with the result!");
               break;
            default:
               smith->do_say("An excellent result, stranger!");
               break;
         }
         smith->command("emote returns the ancient platemail.");
         TP->remove_prop("_korat_did_sell_mithril");
         return 1;
      }
      smith->do_say("I can fix it for you, but I need some mithril "+
         "first. Offer me another weapon or armour with mithril in it "+
         "and I will help you out with this platemail.");
      return 1;
   }

   smith->do_say("I am too busy to help you out, stranger!");
   return 1;
}

int
do_offer(string str)
{
   object *weapon;
   int int_str, value, is_armour, is_weapon;
   string item_name, verb;
   string long, short;
   string dumm1, dumm2;
   
   verb = query_verb();
   
   if (!str)
   {
      smith->do_say(capitalize(verb) + " what?");
      return 1;
   }
   
   if (!(weapon = FIND_STR_IN_OBJECT(str,TP)) ||
         !sizeof(weapon))
   {
      smith->do_say("Sell me what?");
      return 1;
   }
   
   if (sizeof(weapon) > 1)
   {
      smith->do_say("Be more specific. Which one?");
      return 1;
   }

   is_armour = function_exists("create_object",weapon[0]) != "/std/weapon";
   is_weapon = function_exists("create_object",weapon[0]) != "/std/armour";

   if (!is_armour && !is_weapon)
   {
      smith->do_say("You cannot be serious! Thats not a weapon or an armour.");
      return 1;
   }

   /* We check if short or long has the word 'mithril' in it */
   long = weapon[0]->query_long();
   short = weapon[0]->query_short();

   if (sscanf(long, "%s mithril %s",dumm1,dumm2) == 2 ||
      (sscanf(short, "%s mithril %s",dumm1,dumm2) == 2)))
   {
      smith->command("smile");
      smith->do_say("I will take this with happiness, stranger!");
      TP->add_prop("_korat_did_give_mithril",1);
      smith->command("emtoe takes the "+ short + " and "+
         "starts to melt it in the furnace."); 
      weapon[0]->remove_object();
      smith->do_say("I will remember this, stranger. A gift like this "+
         "is worth my services to you later. But do not wait too long, "+
         "because my memory is not what it was.");
      return 1;
   }

   smith->do_say("I don't understand this ...");
   return 1;
}
