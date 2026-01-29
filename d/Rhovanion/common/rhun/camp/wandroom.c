inherit "std/room";
#include "/d/Rhovanion/defs.h"
#include "campdef.h"
#include "trygo.o"
#include <ss_types.h>
 
int maxbar;
int stt;
 
void create_room()
{
  set_long("Very dirty looking room. There are many items lying "+
           "around between diffirent piles of garbage. You wonder "+
           "what is this room used for..\n");
  set_short("Dirty room");
  add_item(({"pile","piles","garbage"}),"@@examm");
  stt=0;
 
  add_exit(CAMPDIR+"wcamp1","west",0);
  add_exit(CAMPDIR+"wcamp3","south",0);
  add_exit(CAMPDIR+"wcamp2","east",0);
}
 
string examm()
{
   int sk;
 
   sk=TP->query_skill(SS_AWARENESS);
   if (sk>(10+random(120)))
     {
       add_item("hole","@@exahole");
       return "It's just obviously looking piles of garbage, but "+
              "when you examine it closer you notice small hole "+
              "hidden deep in the piles !\n";
     }
   if (sk>(10+random(100)))
       return "You notice something strange when you examine "+
              "piles of garbage closer !\n";
 
   return "Obviously looking piles of garbage.\n";
}
 
string exahole()
{
  int sk;
 
  sk=TP->query_skill(SS_AWARENESS);
  if (sk>(20+random(125)))
    {
      add_item("chest","@@exachest");
      return "As you examine hole closer you notice well hidden "+
             "chest within it !\n";
    }
  if (sk>(20+random(115)))
    return "Hmmm... Very strange looking hole... \n";
  return "Obviously looking hole. \n";
}
 
string exachest()
{
  int sk;
  object wand;
 
  sk=TP->query_skill(SS_AWARENESS);
  if ((sk>(25+random(135)))&(stt==0))
    {
      wand=clone_object(CAMPDIR+"wand");
      wand->move(TO);
      stt=1;
      return "As you search chest you find a magical wand "+
             "hidden in it !!!\n";
    }
  if (sk>(25+random(115)))
    return "Hmm.. You notice something odd about this chest..\n";
  return "Obviously looking chest.\n";
}
 
 
#include "filter_funs.h"
 
 
void reset_room()
{
 
  object *list;
  object dummy;
  int i,friends;
 
  friends=0;
  list=FILTER_LIVE(all_inventory(TO));
  for(i=0;i<sizeof(list);i++)
    if ((list[i]->query_name()=="Barbarian")||
         (list[i]->query_name()=="Chief"))
           friends++;
  for(i=friends;i<maxbar;i++)
    {
      dummy=clone_object("/d/Rhovanion/paladin/camp/est");
      dummy->move(TO);
    }
  remove_item("hole");
  remove_item("chest");
  stt=0;
}
