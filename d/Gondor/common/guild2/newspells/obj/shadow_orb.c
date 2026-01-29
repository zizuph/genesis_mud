/*
 * The Shadow Orb was created to address the problem that a player
 * can not know if the Black Breath (Morthul) killed a victim or not.
 *
 * Editing began October 21, 2006 by Toby
 * 
 * Implementing October 25, 2006 by Toby, Ok by Gorboth (GM)
 *
 *
 * Files affected/affecting this orb:
 *
 *   /d/Gondor/common/guild2/newspells/obj/black_breath.
 *       - setup_spell_effect()
 *       - dispel_spell_effect( object dispeller )
 *       - kill_player()
 * 
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../spells.h"

inherit "/std/object.c";

object oVictim,
       oMage;
int    iVictimState = 1,
       iNpc = 0;
string sNpcRace,
       sNpcPos,
       sNpcPro;

/* Victim states:
 *   1 : Poisoned
 *   2 : Dead
 *   3 : Survived
 */

string query_victim_name();
string query_mage_name();
string long_desc();
string short_desc();
string wiz_info();
int    query_victim_state();

int do_behold(string str);
int do_command(string str);

/* Following are only called from outside but defined
 * to avoid making this object pop up in /lplog
 */
void update_victim_state(int i);
void set_victim(mixed victim);
void set_mage(mixed mage);


void create_object()
{
   set_name( "orb" );
   set_pname( "orbs" );
   add_name( MORGUL_S_MORTHUL_TGT );
   set_adj( "shadow" );

   set_short( &short_desc() );
   set_pshort( "shadow orbs" );
   set_long( &long_desc() );

   add_prop( OBJ_I_VALUE,     0 );
   add_prop( OBJ_I_WEIGHT, 1200 );
   add_prop( OBJ_I_VOLUME,  650 );

   add_prop(MAGIC_AM_MAGIC,(({40, "shadow"})));
   add_prop(MAGIC_AM_ID_INFO,({
    "The orb you hold in your hand is crafted out of pure Shadow Magic. ", 10,
    "The shadows swirling inside the orb are restless as if wanting to tell you something. ", 20,
    "It reeks of the powers of the Black Master of the east in the lands of Gondor. ", 30,
    "The orb is a result of someone very skilled in the Dark Arts of Mordor. ", 50,
    "Furthermore the orb will reveal if the victim of the Black " +
    "Breath, obviously cast by a powerful Mage of the Society of " +
    "Morgul Mages, dies or survives. ", 75,
    "A Mage can destruct it using the command word 'terhat coron' when the effect of the Black Breath " +
    "has worn off the unfortunate victim. ", 90,
    "\n",1,}));
   add_prop(OBJ_S_WIZINFO, &wiz_info());

   /* terhat- v. -- break apart, break asunder
    * coron n. -- globe, ball
    */
}

string short_desc()
{
   if(this_object()->query_prop(OBJ_I_BROKEN))
      return "cracked shadow orb";
   else
      return "shadow orb";
}

string long_desc()
{
   string str;

   switch (query_victim_state())
   {
      /* I make a separate check on npc because players may change gender or 
         introduce after poison being placed upon them and want it dynamic.*/
      case 1:
         if(!iNpc)
            str = "This glassy black orb swirls with deep shadows. Within the orbs center " +
                  "enveloped in shadows you see the image of " +query_victim_name()+  
                   one_of_list( ({
                    ", " +oVictim->query_possessive()+ " face contorted in agony.\n",
                    ", " +oVictim->query_possessive()+ " face contorted in agony as "+ 
                    oVictim->query_pronoun()+ " doubles over, emptying " +
                    oVictim->query_possessive()+ " stomach on the ground.\n",
                    ". " +capitalize(oVictim->query_pronoun()) + " is doubled over, holding " +
                    oVictim->query_possessive()+ " stomach in pain.\n", }) );
         else
            str = "This glassy black orb swirls with deep shadows. Within the orbs center " +
                  "enveloped in shadows you see the image of a " +sNpcRace+  
                   one_of_list( ({
                    ", " +sNpcPos+ " face contorted in agony.\n",
                    ", " +sNpcPos+ " face contorted in agony as "+sNpcPro+ 
                    " doubles over, emptying " +sNpcPos+ " stomach on the ground.\n",
                    ". " +capitalize(sNpcPro) + " is doubled over, holding " +sNpcPos+
                    " stomach in pain.\n", }) );
         break;
      case 2:
         if(!iNpc)
            str = "This glassy black orb is dark, fading to gray, and tendrils of shadows " +
                  "are seeping out through deep cracks that have wormed their way through " +
                  "the glass. Vaguely the crumpled and dried face of " +query_victim_name()+ " is " +
                  "visible within.\n";
         else
            str = "This glassy black orb is dark, fading to gray, and tendrils of shadows " +
                  "are seeping out through deep cracks that have wormed their way through " +
                  "the glass. Vaguely a crumpled and dried, dead, face of a " +sNpcRace+ 
                  " is visible within.\n";
         break;
      case 3:
         if(!iNpc)
            str = "This glassy orb swirls slowly with empty black shadows. Occationally the " +
                  "shadows part and the face of " +query_victim_name()+ " flickers " +
                  "into view " + one_of_list( ({ "smiling vividly at you.", 
                                                 "grinning healthily at you",
                                                 "wearing a joyful grin.",
                                                 "laughing happily." }) ) + "\n";
         else
            str = "This glassy orb swirls slowly with empty black shadows. Occationally the " +
                  "shadows part and the face of a healthy " +sNpcRace+ " flickers " +
                  "into view " + one_of_list( ({ "smiling vividly at you.", 
                                                 "grinning healthily at you",
                                                 "wearing a joyful grin.",
                                                 "laughing happily." }) ) + "\n";
         break;
   }

   return str;
}

string wiz_info()
{
   return "This is a orb that Mages get when casting the Morgul spell Morthul " +
          "(Black Breath) successfully on a victim. It has three states (1/2/3) and they " +
          "represent respectively: Poisoned/Dead/Survived. \n" +
          "Current state             : " + iVictimState + "\n" +
          "Target of this orb        : " +query_victim_name()+ "\n" +
          "The Mage that cast Morthul: " +query_mage_name()+ ".\n\n";
}

public void init()
{
   ::init();

   add_action( do_behold  , "behold");
   add_action( do_command , "terhat");
}

int do_behold(string str)
{
   notify_fail("Behold what? The orb?\n");

   str = lower_case(str);

   if(!str)
      return 0;

   if( parse_command(str, ({ }), " [the] [glassy] 'orb' ") )
   {
      this_player()->catch_msg("You hold forth the orb in your right hand, " +
         "beholding it intently you see the following:\n" + long_desc());
      say(QCTNAME(this_player()) + " holds forth a glassy orb in an outstretched " +
         "hand beholding it intently.\n");
      return 1;
   }
   else
      return 0;
}

int do_command(string str)
{
   notify_fail("Break asunder what? The orb?\n");

   str = lower_case(str);

   if(!str)
      return 0;
   
   if(oVictim->query_prop(MORGUL_S_MORTHUL_TGT)->query_victim_state() == 1)
   {
      this_player()->catch_msg("The power of the Dark Lord is still at work " +
         "in the orb and its unfortunant victim. You can not break it now.\n");
      return 1;
   }

   if(str = "coron")
   {
      this_player()->catch_msg("You hold forth the orb, in a rasping voice " +
         "you silently, yet commanding, chant: Terhat Coron!\n" +
         "The shadows remaining in the orb pulses momentarily then the orb " +
         "chatters in the air just as you release it from your hand.\n");
      say(QCTNAME(this_player()) + " holds forth a glassy orb rasping " +
         "silently yet commanding to it. " +capitalize(this_player()->query_pronoun())+
         " releases the orb that chatters in the air.\n");

      oVictim->remove_prop(MORGUL_S_MORTHUL_TGT);
      remove_object();
      return 1;
   }
   else
      return 0;
}

void update_victim_state(int i)
{
   if(i == 2)
   {
      add_prop(OBJ_I_BROKEN,1);
      tell_room(environment(this_object()), "The shadow orb pulsates firecly, " +
                      "deep shadows within in an inferno. Suddenly it cracks!\n");
   }

   if(i == 3)
      tell_room(environment(this_object()), "The shadow orb pulsates once, " +
                      "then the shadows loose its fierceness.\n");

   iVictimState = i;

   return;
}

void set_victim(mixed victim)
{
   if (objectp( victim ))
   {
      oVictim = victim;
   }
   else if (stringp( victim ))
   {
      oVictim = find_player(victim);
   }

   add_name(MORGUL_S_MORTHUL_TGT + oVictim->query_name());

   if(oVictim->query_npc())
   {
      iNpc = 1;
      sNpcRace = oVictim->query_race_name();
      sNpcPos = oVictim->query_possessive();
      sNpcPro = oVictim->query_pronoun();
      
      if(oVictim->query_guild_name_occ() == "Rangers of the Westlands")
         sNpcRace = "ranger";
   }

   return;
}

void set_mage(mixed mage)
{
   if (objectp( mage ))
   {
      oMage = mage;
   }
   else if (stringp( mage ))
   {
      oMage = find_player(mage);
   }

   return;
}

int query_victim_state()
{
   return iVictimState;
}

string query_victim_name()
{ 
   return oVictim->query_the_name(this_player());
}

string query_mage_name()
{ 
   return oMage->query_the_name(this_player());
}

