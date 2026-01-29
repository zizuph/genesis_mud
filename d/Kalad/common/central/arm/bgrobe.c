#pragma strict_types

inherit "/d/Kalad/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#define TP this_player()
#define TO this_object()
#define SUBLOC "wearing_robe_subloc"

/* by Korat */
// Fixed remove messages, Fysix, Oct 1997

void
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("filthy");
   add_adj("torn-up");
   set_long("This piece of clothing can hardly be called a robe with all "+
      "those holes in it. The texture of it is stiff and dirty, feeling "+
      "almost like a torn-up rug in the touch. You see a small label "+
      "attached to it.\n");
   set_af(TO);
   set_ac(1);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE, 50);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 500);
}


string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;
   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "You look ";
   else
      str = capitalize(carrier->query_pronoun()) + " looks ";
   return str + "very poor cuddling into that filthy robe.\n";
}

mixed
wear(object what)
{
   write("You cuddle yourself into the filthy robe, while "+
      "making your face turn into a begging plea for any coins "+
      "your spectators might throw to you.\n");
   say(QCTNAME(TP) + " cuddles a filthy robe around "+
      TP->query_possessive() + " body and looks pleadingly around "+
      "for some monetary help ... You cannot avoid feeling sorry "+
      "for this poor person.\n");
   TP->add_subloc(SUBLOC, TO);
   return 0;
}

mixed
remove(object what)
{
object living;

   living = query_worn();
   living->catch_tell("You remove that filthy, " +
      "smelling rove with a sigh of relief. Then " +
      "you start to check how much you managed to earn fooling all " +
      "those stupid rich folks.\n");
   tell_room(environment(living),
      QCTNAME(living) + " removes a filthy robe with a " +
      "relieved sigh, and starts "+
      "to count "+ living->query_possessive() + " coins.\n", living);
   living->remove_subloc(SUBLOC, TO);
   return 1;
}

void
init()
{
   ::init();
   add_action("robepolish", "robepolish");
   add_action("robewipe", "robewipe");
   add_action("robeshiver", "robeshiver");
   add_action("readlabel", "read");
}

int
readlabel(string str)
{
   notify_fail("Read what?");
   if (!str || str != "label")
      return 0;
   write("You read the label inside the robe: \n\n"+
      "Remember, to fool them just use the commands "+
      "robepolish, robewipe and robeshiver. They work!\n\n"+
      "      Product of the beggars guild. (tm) \n");
   return 1;
}

int
robepolish()
{
   if(!query_worn())
      {
      write("You must first wear the robe before you can trick some "+
         "fool into giving you money!\n");
      return 1;
   }
   write("You take the edge of the filthy robe and start to polish "+
      "the shoes of your spectators. What they don't see is your "+
      "greedy grin as you manage to make their boots even more "+
      "dirty.\n");
   say(capitalize(QCTNAME(TP)) + " bends down in front of you and starts to "+
      "polish your boots with the edge of his filthy robe. You "+
      "really feel sorry for this wretched creature.\n");
   return 1;
}

int
robewipe()
{
   if(!query_worn())
      {
      write("You must first wear the robe before you can do anything "+
         "to fool your spectators into giving you money!\n");
      return 1;
   }
   write("You wipe your face and mouth with the filthy robe, "+
      "but only manage to make yourself even more dirty. Maybe "+
      "someone will feel pity for you now?\n");
   say(capitalize(QCTNAME(TP))+ " spits on the edge of the robe and then starts to wipe "+
      TP->query_possessive() + " face with it, ultimately just smearing "+
      "the dirt around more evenly. You feel pity for "+
      "this poor creature.\n");
   return 1;
}

int
robeshiver()
{
   if (!query_worn())
      {
      write("You must wear the robe before you can fake "+
         "the audience!\n");
      return 1;
   }
   write("You cuddle the filthy robe around your body, and "+
      "start to fake a freezing shiver that goes through your body. "+
      "Very effective, maybe!\n");
   say(capitalize(QCTNAME(TP)) + " cuddles the filthy torn-up robe around "+
      TP->query_possessive()+ " body and starts to visibly shiver from "+
      "the cold as a gust of wind blows straight through all the holes "+
      "in it. "+ capitalize(TP->query_pronoun()) + " looks very cold! "+
      "Maybe some warm food could help?\n");
   return 1;
}
