inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside a cave");
   set_long("You find yourself in the narrow end of this cave, "+
      "just behind that barrier you managed to pass through. "+
      "This part of the dark and cold cave seems to be spared "+
      "from being used as refugee for animals, and looks quite "+
      "empty. The only interesting things to study is the walls, "+
      "that really looks just like all the other walls you have seen.\n");
   add_item(({"wall","walls"}),
      "The walls looks like naturally shaped surfaces of "+
      "the mountain. Nothing peculiar with it, just the usual sharp "+
      "edges, small cracks and loose pebbles at the foot of the "+
      "walls. @@dwarf_skill@@\n");
   add_item(({"sharp edges","edges"}),"The edges looks ... sharp?\n");
   add_item(({"small cracks","cracks"}),"The cracks is everywhere on the "+
      "surface of the walls. Nothing peculiar with them really.\n");
   add_item("pebbles","The pebbles is just some small rocks that "+
      "has fallen loose from the walls during time.\n");
   add_item("granite","@@granite@@");
   add_item("quartz","@@quartz@@");
   add_item("crystal","@@crystal@@");
   add_exit(CPASS(dwarf/chasm3),"out",0,-1,-1);
}
string
dwarf_skill()
{
   if(TP->query_race()!="dwarf")
      return "The rock itself seems to be of granite.";
   return
   "The rock is made of granite, that you know is a "+
   "coarse-grained igneous rock composed "+
   "chiefly of orthoclase and albite  feldspars and of quartz. "+
   "This granite seems to have a higher ammount of quartz than "+
   "usual.";
}
string
granite()
{
   if(TP->query_race()!="dwarf")
      return "Its that plain rock that someone, probably a "+
   "dwarf, named as granite. You have seen it before.\n";
   return
   "Granite! That marvellous rock of such strength and "+
   "complexity. You touch the walls to feel the coarse "+
   "grains properly, and notice at once that this wall "+
   "is fairly saturated with quartz; one of the main "+
   "ingredients of granite.\n";
}
string
quartz()
{
   if(TP->query_race()!="dwarf")
      return
   "You try to find some quartz in the surface of the granite "+
   "walls, but fail. Your geologist skills are not good enough it seems. "+
   "Maybe if you was a dwarf, you could figure it out.\n";
   return
   "You carefully study the small deposits of quartz on the walls "+
   "surface. Except from the granite itself that seems to be chiefly "+
   "consisting of it, you notice one small area where the quartz seems "+
   "to have crystalized itself.\n";
}
string
crystal()
{
   if(TP->query_race()!="dwarf")
      return "You look and look, but find no crystal. Have you "+
   "searched the pebbles yet? Maybe there is one among them.\n";
   return
   "The crystal seems to be fairly clear, almost transparent, "+
   "but it is hard to tell as it is firmly attached to the wall. "+
   "After a while you notice something wierd about it though. Some "+
   "runes seems to be written inside it! Magic!!\n";
}
init()
{
   ::init();
   add_action("read","read");
   add_action("touch","touch");
}
int
read(string str)
{
   notify_fail("Read what?\n");
   if(TP->query_race()!="dwarf")
      return 0;
   if(!str || str!="runes") return 0;
   write("You try to decipher the runes.\n");
   tell_room(TO,QCTNAME(TP)+" bends down in front of the wall, "+
      "and starts to mumble for "+TP->query_possessive()+"self "+
      "almost as "+TP->query_pronoun()+" was reading something.\n",TP);
   if(TP->query_skill(SS_LANGUAGE)<30)
      {
      write("After a while you give up. Your skill is just not up "+
         "to this. What an embarrasment you are for your race! A dwarf "+
         "that cannot read a single rune!\n");
      return 1;
   }
   write("You manage to decipher the runes: 'Touch me' it says.\n");
   return 1;
}
int
touch(string what)
{
   object *team;
   int index;
   int size;
   if(TP->query_race()!="dwarf")
      {
      write("What?\n");
      return 1;
   }
   if(what != "crystal")
      {
      write("Touch what?\n");
      return 1;
   }
   write("You touch the crystal, and your fingers seems to enter it!\n");
   tell_room(TO,"The wall suddenly starts to glow faintly!\n");
   write("You feel yourself "+
      "being sucked in through the surface of the rock, and into "+
      "another place...\n");
   say(QCTNAME(TP)+" suddenly dissapears!\n");
   TP->move_living("M",CPASS(dwarf/crypt/c11));
   
   /* move the team with the leader */
   if(size = sizeof(team = TP->query_team()))
      {
      index = -1;
      while(++index < size)
      {
         if ((environment(team[index]) == TO))
            team[index]->catch_msg("You feel yourself being sucked "+
            "in through the surface of the rock, and into another place ...\n");
         tell_room(TO,QCTNAME(team[index])+" suddenly dissapears!\n", team[index]);
         team[index]->move_living("M",CPASS(dwarf/crypt/c11));
      }
   }
   return 1;
}
