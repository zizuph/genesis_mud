inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 3;
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The roof of the Bell Tower of Kabal");
   set_long("You are atop the bell tower of Kabal, the wind whipping "+
      "across your face. From here, you get an astounding view of the "+
      "expansive city of Kabal. As the bell tower is located in the very "+
      "heart of the city, you can make out nearly every major site in the "+
      "city. Looking down you can see the great citadel of the High Lord, "+
      "while east is the famed gladiatorial arena of Kabal. In the distance "+
      "to the northeast is a castle-sized building, the headquarters of "+
      "the Trading Company of Kabal. Lying farther to the northwest, past "+
      "a large stand of trees are several large stone buildings, the "+
      "palatial residences of the nobles of the city. Looking out far to the "+
      "south, beyond the cliff's edge, lies the sparkling blue Bay of "+
      "Kabal. Lastly, yet more massive than all the rest are the towering "+
      "heights of the Hespyre mountain range, which rises in ever "+
      "increasing heights to the east.\n");
   add_item(({"expansive city","city","kabal"}),"It spreads out before "+
      "you, a testament to the creative forces of humanity.\n");
   add_item(({"great citadel","citadel"}),"The magnificent residence of the "+
      "High Lord of Kabal.\n");
   add_item(({"famed gladiatorial arena","famed arena","gladiatorial arena","arena"}),
      "A large circular structure where daily contests involving life and "+
      "death are carried out. Even now you think you can hear the cheers "+
      "of the spectators.\n");
   add_item(({"castle-sized building","headquarters","trading company","company"}),
      "A dark-stoned building with a looming countenance. The extremely wealthy "+
      "Trading Company dwells within its foreboding walls.\n");
   add_item(({"large stand","stand","trees","tree"}),"The clustering "+
      "of trees is known throughout the city as Twilight Park, located "+
      "within the Noble District. Rumors have it that many outlaws use its "+
      "shadowy interior as a hideout from the law.\n");
   add_item(({"large stone buildings","large buildings","stone buildings","palacial residences","residences"}),
      "The residences of the noble population of Kabal. Even from here their beauty is quite impressive.\n");
   add_item(({"sparkling blue bay of kabal","sparkling bay","blue bay","bay of kabal","bay"}),
      "A great natural harbor used to the utmost advantage by the seagoing "+
      "community of Kabal.\n");
   add_item(({"hespyre mountain range","hespyre range","mountain range","range"}),
      "A massive series of dark grey mountains that rises above the city "+
      "to the east, pinning the city of Kabal between itself and the "+
      "rolling blue depths of the Kaladian sea.\n");
   add_item(({"kaladian sea","sea"}),"A great expanse of blue visible "+
      "to the west.\n");
   add_exit(CENTRAL(tower/top),"southwest",0,-1,-1);
}
void
init()
{
   ::init();
   
   add_action("jump", "jump");
   add_action("throw_item", "throw");
}
int
jump(string str)
{
   write("You try to jump as high as possible and you slip. It's seems to " +
      "be a long\nway down....\n");
   say(QCTNAME(TP) + " foolishly jumps and falls from the bell tower.\n");
   
   TP->move_living("M","/d/Kalad/common/central/tower/falling",1);
   return 1;
}

int
throw_item(string str)
{
   object *arr;/* Local variables, array of objects */
   int i;/* Local variable, integer, used in the for-loop */
   
   if (!str)
      {
      notify_fail("Throw what?\n");
      return 0;
   }
   
   arr = FIND_STR_IN_OBJECT(str, this_player());
   
   if (!sizeof(arr))
      {
      notify_fail("You don't have any '" + str + "'.\n");
      return 0;
   }
   
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->move("/d/Kalad/common/central/tower/falling");
   
   write("You throw " + COMPOSITE_DEAD(arr) + " off the bell tower.\n");
   say(QCTNAME(TP) + " throws " + QCOMPDEAD + " off the bell tower.\n");
   return 1;
}
