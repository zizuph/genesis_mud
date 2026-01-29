string find_song(int number);
int hsing(string str);


int
hsing(string str)
{
   string the_song;
   int num;
   object tp;

   seteuid(getuid());
   tp = this_player();

   if (!str)
      return 0;

   if (!sscanf(str,"%d",num) == 1)
   {
      if (!sscanf(str,"song %d",num) == 1)
         return 0;
   }
   if (the_song = find_song(num))
   {
      say(QCTNAME(tp) + " sings a merry song:\n");
      write("You sing a merry song:\n");
      tell_room(environment(tp), "\n" + the_song + "\n");
      return 1;
   }
   write("You don't know that many songs...");
   return 1;
}

string
find_song(int number)
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
