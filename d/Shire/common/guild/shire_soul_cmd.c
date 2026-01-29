/*
 * shire_soul_cmd.c
 *
 * This object holds some general Hin Warrior feelings
 *
 */

inherit "/cmd/std/soul_cmd";

#include "/secure/std.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

#define ME QCTNAME(tp)
#define HIM QTNAME(who)
#define MY tp->query_possessive()
#ifndef HIS_HER
#define HIS_HER tp->query_possessive()
#endif
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
   seteuid(getuid());
   return "shire";
}

query_cmd_soul() 
{
   seteuid(getuid());
   return 1;
}

/* This soul is auto_loading */
string
query_auto_load()
{
   seteuid(getuid());
   return SHIRE_SOUL;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */

mapping
query_cmdlist()
{
   seteuid(getuid());
   return ([
        "armpit":"armpit",
        "barf":"barf",
        "bark":"bark",
        "flame":"flame",
        "flex":"flex",
        "hiss":"hiss",
        "nude":"nude",
        "seduce":"seduce",
        "shuffle":"shuffle",
        "recite":"recite",
        "thumb":"thumb",
        "wigg":"wigg"
   ]);

/* Possible future extensions:
 *   pushup, chew, barf, elevate, gnaw, bite...
*/
}

/****************************************************************************
 *  Some handy functions
 */

fail_ghost()
{
   seteuid(getuid());
   write("You fail.\n");
   return 1;
}

/*
 *   Is this person also a member of the Hin warriors in name?
 */

is_a_shire(/* object */ owner)
{
   seteuid(getuid());
   return (SHIRE_PIPE)->is_a_shire(owner);
}

is_founder(/* string */ owner)
{
   seteuid(getuid());
   return (SHIRE_PIPE)->is_founder(owner);
}

known_present(who,where)
{
   string intro, remem, list;
   seteuid(getuid());
   intro = this_player()->query_introduced();
   remem = this_player()->query_remembered();
   list = (intro ? intro : ({ })) + (remem ? remem : ({ }));
   return present(who,where);
}

/* **************************************************************************
 * Here follow the actual functions. Please add new functions in the 
 * same order as in the function name list.
 * **************************************************************************/


armpit(str) {
  object tp;
  string poss;
 
  seteuid(getuid());
  tp = this_player();
  if (tp->query_ghost()) return fail_ghost();
  if (str) return 0;
  write("You flex your muscles and sniff greedily in your right armpit.\n");
  all(" flexes " + MY + " muscles and sniffs greedily in " + MY +
    " right armpit.");
  SOULDESC("sniffing greedily in " + MY + " right armpit");
  return 1;
}


barf(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();
   if (tp->query_ghost())
      return fail_ghost();
   SOULDESC("barfing all over the place");
   if (!str || str == "")
   {
      write("You barf all over the place, making a huge stinking mess!\n");
      write("Maybe you should stop hitting the bottle so hard?\n");
      all(" barfs all over, making a huge mess!  Maybe " + HE_SHE(tp) +
          " should take it easy on the booze?\n");
      return 1;
   }
   seteuid(getuid());
   who = parse_this(str, "[on] %l");
   if (!sizeof(who)) return 0;
   target(" barfs all over you!  How gross!", who);
   actor("You barf on", who);
   all2act(" barfs all over", who);
   return 1;
}


bark(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();
   if (tp->query_ghost())
      return fail_ghost();
   SOULDESC("barking like a mad dog");
   if (!str || str == "")
   {
      write("You bark like a mad dog.\n");
      all(" barks like a mad dog.");
      return 1;
   }
   seteuid(getuid());
   who = parse_this(str, "[at] %l");
   if (!sizeof(who)) return 0;
   target(" barks in your direction.", who);
   actor("You bark at", who);
   all2act(" barks at", who);
   return 1;
}


flame(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();
   if (tp->query_ghost())
      return fail_ghost();
   if (!str)
   {
      write("You make your own finger burst into flame!\n");
      all(" makes " + MY + " fingers burst into flames!");
      return 1;
   }
   who = present(lower_case(str), environment(tp));
   if (!who || !living(who) || who == tp) return 0;
   if (who->query_wiz_level() && !(tp->query_wiz_level()))
   {
      write("You change your mind and decide not to make a fool of yourself.\n");
      return 1;
   }
   if (!(tp->query_wiz_level())) {
      if (tp->query_mana() < 5) {
         write("You are too low on power.\n");
         return 1;
      }
      tp->add_mana(-5);
   }
   who = parse_this(str, "%l");
   if (!sizeof(who)) return 0;
   target(" waves " + MY + " hands, and you burst into flames!", who);
   actor("You wave your hands and set fire to", who);
   all2act(" waves " + MY + " hands, and sets fire to", who);
   return 1;
}


flex(str)
{
   object tp, who;
   tp = this_player();
   seteuid(getuid());
   if (this_player()->query_ghost())
       return fail_ghost();
   if (str)
      return 0;
   write("You flex your muscles to impress everyone.\n");
   all(" flexes " + MY + " muscles.\nYou are not impressed at all.");
   SOULDESC("flexing " + MY + " muscles");
   return 1;
}


hiss(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();
   if (tp->query_ghost())
      return fail_ghost();
   SOULDESC("hissing dangerously");
   if (!str || str == "")
   {
      write("You hiss dangerously.\n");
      all(" hisses dangerously.");
      return 1;
   }
   who = parse_this(str, "[at] %l");
   if (!sizeof(who)) return 0;
   target(" hisses dangerously in your direction.", who);
   actor("You hiss dangerously at", who);
   all2act(" hisses dangerously at", who);
   return 1;
}


nude(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();

   if(!is_a_shire(tp)) return 0;
   if (tp->query_ghost())
      return fail_ghost();

   if (!str)
   {
      write("You wave your hands and your pants fall down! Everyone laughs at you!\n");
      all(" waves " + MY + " hands, and " + MY + " pants fall down!!\n" +
          "You fall down laughing!");
      SOULDESC("pulling up " + MY + " pants");
      return 1;
   }
   who = parse_this(str, "%l");
   if (!sizeof(who)) return 0;
   if (!(tp->query_wiz_level()))
   {
      if (tp->query_mana() < (5 * sizeof(who)))
      {
         write("You are too low on mental power.\n");
         return 1;
      }
      tp->add_mana(-5 * sizeof(who));
   }
   if(random(4) == 3 && !(tp->query_wiz_level()))
   {
      write("You fail to cast the spell correctly, and your own pants fall down.\n");
      write("Everyone laughs at you.\n");
      all(" waves " + MY + " hands, and " + MY + " pants fall down!!\n" +
          "You fall down laughing!");
      return 1;
   }
   str = capitalize(str);
   
   target(" waves " + MY + " hands and your pants fall down!", who);
   actor("You wave your hands, and embarrass", who);
   all2act(" waves " + MY + " hands, and", who, "'s pants fall down!");
   return 1;
}



seduce(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();
   if (this_player()->query_ghost())
      return fail_ghost();
   if (!str || str == "")
   {
      write("You try to look seductive.\n");
      all(" tries to look seductive.");
      SOULDESC("trying to look seductive");
      return 1;
   }
   who = parse_this(str, "[at] %l");
   if (!sizeof(who)) return 0;
   target(" tries to seduce you.", who);
   actor("You whisper sweet words of love to", who);
   all2act(" tries to seduce", who);
   return 1;
}


shuffle(str)
{
   int tmp;
   string dance;
   object tp, who;

   seteuid(getuid());
   tp = this_player();
   if (tp->query_ghost())
      return fail_ghost();

   tmp = random(6);     /* Most chance of getting the Nobish shuffle */
   if (tmp == 0)
      dance = "Harlem";
   else if (tmp == 1)
      dance = "Bree";
   else if (tmp == 2)
      dance = "Hobbiton";
   else
      dance = "Nobish";
   if (!str)
   {
      write("You do the " + dance + " shuffle!\n");
      all(" does the " + dance + " shuffle! You watch amazed!");
      return 1;
   }
   else
   {
      who = parse_this(str, "[at] %l");
      if (!sizeof(who)) return 0;
      target(" does the " + dance + " shuffle with you!", who);
      actor("You do the " + dance + " shuffle with", who);
      all2act(" does the " + dance + " shuffle with", who,"\nYou watch amazed!");
      return 1;
   }
}


recite(str)
{
   string the_song;
   int num;
   object tp;

   seteuid(getuid());
   tp = this_player();

   if (tp->query_ghost())
      return fail_ghost();
   if (!str)
      return 0;
   if (!is_a_shire(tp))
      return 0;

   if (!sscanf(str,"%d",num) == 1)
   {
      if (!sscanf(str,"song %d",num) == 1)
         return 0;
   }
   if (the_song = find_song(num))
   {
      say(ME + " recites a merry song:\n");
      write("You recite a merry song:\n");
      tell_room(environment(tp), "\n" + the_song + "\n");
      SOULDESC("reciting a merry song");
      return 1;
   }
   write("You don't know that many songs...");
   return 1;
}


find_song(number)
{
   string the_song;

   if (number == 1)
      return
         ("   O Water warm and water hot! \n"
        + "   O Water boiled in pan and pot!\n"
        + "   O Water blue and water green,\n"
        + "   O Water silver-clear and clean,\n"
        + "   Of bath I sing my song !\n\n"
        + "   O praise the steam expectant nose!\n"
        + "   O bless the tub my weary toes!\n"
        + "   O happy fingers come and play!\n"
        + "   O arms and legs, you here may stay,\n"
        + "   And wallow warm and long!\n"
        + "   Put mine away! Forget the clay!\n"
        + "   Shut out the night! Wash of the day!\n"
        + "   In water lapping chin and knees,\n"
        + "   In water kind now lie at ease,\n"
        + "   Until the dinner gong!\n");

   if (number == 2)
      return
         ("   Sing now, ye people of the Tower of Anor,\n"
        + "   for the Realm of Sauron is ended for ever,\n"
        + "   and the Dark Tower is thrown down.\n\n"
        + "   Sing and rejoice, ye people of the Tower of Guard,\n"
        + "   for your watch hath not been in vain,\n"
        + "   and the Black Gate is broken,\n"
        + "   and your King hath passed through,\n"
        + "   and he is victorious.\n\n"
        + "   Sing and be glad, all ye people of the West,\n"
        + "   for your King shall come again,\n"
        + "   and he shall dwell among you\n"
        + "   all the days of his life.\n\n"
        + "   And the Tree that was withered shall be renewed,\n"
        + "   and he shall plant it in the high places,\n"
        + "   and the City shall be blessed.\n"
        + "   Sing all ye people!\n");

   if(number == 3)
      return
         ("   Ho!Ho!Ho!\n"
        + "   To my bottle I go\n"
        + "   To heal my heart and drown my woe.\n"
        + "   Rain may fall and wind may blow,\n"
        + "   And many miles be still to go,\n"
        + "   But under the elm-tree I will lie\n"
        + "   And let the clouds go sailing by!\n"
        + "   Ho!Ho!Ho!\n");

   if(number == 4)
      return
         ("   A troll sat alone on his seat of stone,\n"
        + "   And munched and mumbled a bare old bone;\n"
        + "   And long and long he sat there lone\n"
        + "   and seen no man nor mortal -\n"
        + "   Ortal! Portal!\n"
        + "   And long and long he sat there lone\n"
        + "   and seen no man nor mortal\n");

   if (number == 5)
      return
         ("   Still round the corner there may wait\n"
        + "   a new road or a secret gate;\n"
        + "   and though I oft have passed them by,\n"
        + "   a day will come at last when I\n"
        + "   shall take the hidden paths that run\n"
        + "   West of the Moon, East of the sun.\n");

   if (number == 6)
      return
         ("   The Road goes ever on and on\n"
        + "   Out from the door where it began.\n"
        + "   Now far ahead the Road has gone,\n"
        + "   Let others follow it who can!\n"
        + "   Let them a journey new begin,\n"
        + "   But i at last with weary feet\n"
        + "   Will turn towards the lighted inn,\n"
        + "   My evening rest and sleep to meet.\n");

   if(number == 7)
      return
         ("   Come play on your fiddle a hey-diddle-diddle,\n"
        + "   A jig to wake the dead.\n"
        + "   So the cat played a terrible drunken tune,\n"
        + "   While the landlord shook the man in the moon:\n"
        + "   'tis after three, 'he said.\n");

   if(number == 8)
      return
         ("   O! Wanderers in the shadowed land\n"
        + "   despair not! For though dark they stand,\n"
        + "   all woods there must be end at last,\n"
        + "   and see the open sun go past:\n"
        + "   the setting sun, the rising sun,\n"
        + "   the day's end, or the day begun.\n"
        + "   For east or west all woods must fail...\n");

   if(number == 9)
      return
         ("   Now let the song begin! Let us sing together\n"
        + "   Of sun, stars, moon and mist, rain and cloudy weather,\n"
        + "   Light on the budding leaf, dew on the feather,\n"
        + "   Wind on the open hill, bells on the heather,\n"
        + "   Reeds by the shady pool, lilies on the water:\n"
        + "   Old Tom Bombadil and the River-daughter!\n");

   if(number == 10)
      return
         ("   Gondor! Gondor, between the mountains and the Sea!\n"
        + "   West Wind blew there; the light upon the Silver Tree\n"
        + "   Fell like bright rain in the gardens of the Kings of old.\n"
        + "   O proud walls! White towers! Oh winged crown and throne of gold!\n"
        + "   O Gondor, Gondor! Shall Men behold the Silver Tree,\n"
        + "   Or West Wind blow again between the Mountains and the Sea?\n");

   return 0;
}


thumb(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();
   if (this_player()->query_ghost()) return fail_ghost();
   if (!str || str == "")
   {
      write("You hold up your thumb.\n");
      all(" holds up " + MY + " thumb.");
      SOULDESC("holding up " + MY + " thumb");
      return 1;
   }
   who = parse_this(str, "[at] %l");
   if (!sizeof(who)) return 0;
   target(" holds up " + MY + " thumb in your direction.", who);
   actor("You hold up your thumb at", who);
   all2act(" holds up his thumb at", who);
   return 1;
}


wigg(str)
{
   object tp, who;
   seteuid(getuid());
   tp = this_player();
   if (tp->query_ghost()) return fail_ghost();
   SOULDESC("wiggling " + MY + " finger dangerously.");
   if (!str || str == "")
   {
      write("You wiggle your fingers dangerously.\n");
      all(" wiggles " + MY + " fingers dangerously.");
      return 1;
   }
   who = parse_this(str, "[at] %l");
   if (!sizeof(who)) return 0;
   target(" wiggles " + MY + " fingers dangerously in your general direction.", who);
   actor("You wiggle your fingers at", who);
   all2act(" dangerously wiggles " + MY + " fingers at", who);
   return 1;
}
