/*
 * Made by korat
 * nov 18. 1995 
 *
 * This platemail is worn by kabal (~/dwarf/npc/kabal.c) a major foe.
*/

inherit "/d/Kalad/std/armour.c";

#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

public int cursed; // variable that decides if it is cursed or not
   
/* function: query_arm_recover
 * description: returns the recover string.
 * returns: the recover string
 */
string
query_arm_recover()
{
      return ::query_arm_recover() + "#TYPE#" + cursed + "#";
}

/* function: init_arm_recover
 * description: Initializes the armour variables at recover
 * argumnet: The recover string as received from query_arm_recover
 */
void
init_arm_recover(string arg)
{
   string foo; // just a dummy variable
   ::init_arm_recover(arg);  // never forget to call the parent function
   sscanf(arg, "%s#TYPE#%s#%s", foo, cursed, foo);
}

/* function: set_plate_cursed
 * description: Sets the magic properties depending on being cursed or not
 */
void
set_plate_cursed()
{
   if (!cursed)
   {
      add_prop(OBJ_S_WIZINFO,"This platemail is enchanted. "+
         "It has a better protection (ac=55), and any weapon "+
         "that hits it will get more corroded. It "+
         "has protection against different elements and forms. "+
         "It cannot be removed, unless it breaks. It was "+
         "once cursed, but this has been disspelled.\n");
      add_prop(MAGIC_AM_ID_INFO,({"With your newly gained knowledge "+
         "about this armour, you know that it is enchanted.\n",5,
         "Its enchantment provides excellent protection.\n",10,
         "Mostly the enchantment is against normal attacks, but also "+
         "against the elements of acid and poison, and the forms of "+
         "death and water.\n",25,
         "When you study the surface of the mithril, you understand "+
         "that any metal hitting it will degrade into its new phase; "+
         "rust.\n",60}));
      return;
   }
   
   /* The platemail is cursed: */

   set_likely_break(1);
   add_prop(OBJ_S_WIZINFO,"This platemail is enchanted and cursed. "+
      "It has a better protection (ac=55), and any weapon "+
      "that hits it will get more corroded. It "+
      "has protection against different elements and forms. "+
      "It cannot be removed, unless it breaks.\n");
   add_prop(MAGIC_AM_ID_INFO,({"With your newly gained knowledge "+
      "about this armour, you know that it is enchanted.\n",5,
      "Its enchantment provides excellent protection.\n",10,
      "Mostly the enchantment is against normal attacks, but also "+
      "against the elements of acid and poison, and the forms of "+
      "death and water.\n",25,
      "When you study the surface of the mithril, you understand "+
      "that any metal hitting it will degrade into its new phase; "+
      "rust.\n",60,
      "This platemail is also cursed! It will degrade the wearers "+
      "defensive skills slowly for each hit it receives.\n",90}));
   return;
}

/* function: create_armour
 * description: the main proc that describes the platemail
 */
void
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_adj("ancient");
   add_adj("mithril");
   set_long("This ancient platemail seems to be made of pure mithril; "+
      "A silver that can be forged in dwarven hands into some of "+
      "the best armours ever to be seen. @@state@@.\n");

   /* The actual ac is 50 since the armour has a bad condition.
      This may be fixed I believe by members of the smiths-guild. */
   set_ac(55);
   set_at(A_TORSO | A_ARMS);
   set_condition(5);
   add_prop(OBJ_I_VALUE, 6000);
   add_prop(OBJ_I_WEIGHT,11000);
   add_prop(OBJ_I_VOLUME,8000);
   set_af(TO);

   /* It is magical. */
   set_plate_cursed(); // different magic-descriptions if cursed/not cursed
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(OBJ_I_RES_MAGIC, 20);
   add_prop(OBJ_I_RES_ACID, 50);
   add_prop(OBJ_I_RES_POISON, 30);
   add_prop(OBJ_I_RES_WATER, 40);
   add_prop(OBJ_I_RES_DEATH, 40);
   add_prop(OBJ_M_NO_SELL, "The shopkeeper refuses to buy the platemail.\n");
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(MAGIC_AM_MAGIC, ({ 85, "enchantment" }));
}

mixed
wear(object what)
{
   if (!living(E(TO))) return 1;
   E(TO)->catch_msg("The platemail fits perfectly! Every inch of "+
      "the mithril seems to caress your body, in a cold "+
      "and everlasting embrace.\n");
   return 0;
}

mixed
remove(object what)
{
   if (TO->query_broken())
      {
      E(TO)->catch_msg("The ancient mithril platemail "+
         "disintegrates into "+
         "hundreds of rust-particles.\n");
      TO->remove_object();
      return 0;
   }
   if(living(E(TO)))
   {
      E(TO)->catch_msg("You try and try to rip it off yourself, but "+
      "in vain. The mithril seems to be almost as a part of your own "+
      "body. A new skin of defence.\n");
      E(TO)->add_mana(-50);
   }
   return -1;
}

/* Function: state
 * Description: We add to set_long to show the state of the
 *              armour. It starts out being in a bad state.
 * Retruns: The description according to condition
 */
string
state()
{
   string str;
   switch (TO->query_condition())
   {
      case 0..1:
      str = "The mithril shines so much that it hurts your eyes to watch it.\n";
      break;
      case 2..3:
      str = "The mithril looks to be in a good state, ready to "+
      "stop any blow aimed at you.\n";
      break;
      case 4:
      str = "The platemail has some holes in it, but still looks "+
      "fairly sturdy.\n";
      break;
      default:
      str = "The platemail has several holes in it, telling a tale "+
      "of hard fights and grand battles. A rather large hole is "+
      "situated right above the place where the wearers heart would be.\n";
      break;
   }
   return str;
}

/* function: got_hit
 * description: Called when this platemail is hit.
 *              Used here to lower the condition of the weapon
 *              that hit us. A special ability of this armour.
 * arguments: hid - hit location id
 *            ph - % hurt
 *            att - the one who hit us
 *            dt - damage type
 *            dam - the damage we received
 */
void
got_hit(int hid, int ph, object att, int dt, int dam)
{
   object wep;
   mixed *strenght;
   string str1, str2;
   int type = 0;

   /* no hit - return */
   if(ph<1) return;

   /* not the platemail that got hit - return */
   if (hid != A_BODY && hid != A_L_ARM && hid != A_R_ARM)
      return;

   /* find out what hit us */
   switch(dt)
   {
      case W_LEFT: wep = att->query_weapon(W_LEFT); break;
      case W_RIGHT: wep = att->query_weapon(W_RIGHT); break;
      case W_BOTH: wep = att->query_weapon(W_BOTH); break;
      default: break;
   }

   if (!objectp(wep))
      return;

   /* magical weapons more resistant */
   if (wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
      {
      strenght = wep->query_prop(MAGIC_AM_MAGIC);
      if (random(strenght[0]) > 40) return;
   }

   wep -> set_dull(wep->query_dull()+1);

   /* we give a message about what happened */
   switch (random(4))
   {
      case 0:
      str1 = "Your "+wep->query_short()+" hits the "+TO->query_short()+", and gets damaged.\n";
      str2 = "The "+wep->query_short()+" gets damaged as it hits your "+TO->query_short()+".\n";
      break;
      case 1:
      str1 = "Your "+wep->query_short()+" vibrates in your hand when it hits "+
      "the "+TO->query_short()+".\n";
      str2 = "The "+wep->query_short()+" bounches off your "+TO->query_short()+" and looks more scarred.\n";
      break;
      case 2:
      str1 = "The "+wep->query_short()+" ricoshettes back as it hits the "+TO->query_short()+".\n";
      str2 = "The "+wep->query_short()+" ricoshettes back as it hits your "+TO->query_short()+".\n";
      break;
      case 3:
      str1 = "Your "+wep->query_short()+" gets more scarred when it hits the "+TO->query_short()+".\n";
      str2 = "The "+wep->query_short()+" seems to get more scarred after its hit on your "+TO->query_short()+".\n";
      break;
      default:break;
   }
   att->catch_msg(str1);
   E(TO)->catch_msg(str2);

   /* if we are cursed - we do some bad things to the wearer */
   if (cursed) set_alarm(0.0,0.0,"curse");
   return;
}

/* function: curse
 * description: The next is a curse. 
 *              Randomly either parry or defence will 
 *              be lowered when this platemail is hit with damage.
*/
void
curse()
{
   object me;
   int less_skill;
   int skill;
   
   me = TO->query_worn();
   if (me->id("kabal")) return; /* kabal shouldn't be affected */
   if (!objectp(me)) return; /* the platemail is not worn. Should not happen! */
   
   /* select either parry or defence */
   skill = random(2) + 23; /* parry = 23 and defence = 24 */

   /* decrease skill with 0, 1 or 2 points. */
   less_skill = random(3);
   if (me->query_skill(skill) - less_skill >= 0)
      me->set_skill_extra(skill, (me->query_skill_extra(skill) - less_skill));
   
  /* we might be aware enough to notice the change */
   if(less_skill && (me->query_skill(SS_AWARENESS)) > random(100))
      me->catch_msg("You feel yourself a bit uneasy. Something is wrong ...\n");

   return;
}

/* function: remove_curse
 * description: Called to remove the curse
 */
void
remove_curse()
{
   cursed = 0;
   return;
}
