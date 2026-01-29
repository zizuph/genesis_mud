#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;
 
object rat;
object rat2;

void 
reset_mithas_room()
{
    if(!objectp(rat))
    {
      rat = clone_object(MNPC + "rat");
      rat -> move(this_object());
   }
   if(!objectp(rat2))
      {
      rat2 = clone_object(MNPC + "rat");
      rat2 -> move(this_object());
   }
}
void
create_mithas_room()
{
   set_short("Pier to Flotsam");
   set_long("@@long_descr");
   add_item("sign","A sign with words. Read them. \n");
   add_cmd_item("sign", "read", "@@read_sign");
   add_item(({"water", "sea"}), "The water within the Blood Sea has "+
         "a strange and reddish color. Rumor has it that the color "+
         "is the result of the blood of many victims who lost their "+
         "lives during Krynn's most terrible hour, though it "+
         "could be the clay stirred up from the sea bottom by the "+
         "maelstrom.\n");
   add_exit(MROOM + "pier1","south",0);
   add_exit(MROOM + "pier4","southeast",0); 


    add_item(({"bay","horned bay","bloodsea","blood sea"}), "The horned bay "+
               "stretches itself towards the north, south and further out "+
               "to the west where it meets the Bloodsea.\n");   

    add_item(({"pier","wooden pier","small pier","small wooden pier"}), "It's a very "+
               "old and wooden pier, it looks very unstable.\n");

    add_item(({"mithas", "isle", "village", "nethosak"}), "The great Imperial "+
            "city of Nethosak, home of the minotaurs of Ansalon, lies to the "+
            "east. This great city is the home of the Emperor of the Minotaurs "+
            "and the Great Arena, where minotaurs and other lucky 'volunteers' "+
            "fight against each other, sometimes to the death. This is also the "+
            "place of the Temple of the Stars, where the High Priest of the "+
            "minotaurs performs rituals to their god. A strong smell of "+
            "smoke and sweat fills the air.\n");


   set_tell_time(100);
   add_tell(({
       "The fresh breeze of the sea caresses your face.\n",
       "The waves from the sea slam violently into the pier.\n",
       "You hear the screams of seagulls nearby.\n", }));
   reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on a small wooden "+
          "pier on the isle of Mithas. To the west "+
          "you can see the Horned Bay which "+
          "shelter this isle from the ravages of "+
          "the Blood Sea. A bit further to the "+
          "east you can see the entrance to "+
          "the village of Nethosak. The pier "+
          "looks rather old, but still very sturdy. "+
          "The pier continues to the southeast toward the "+
          "city and south to another pier. " +season_descr()+
          "There's a small sign here.\n";
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}

int
read_sign()
{
  write("   ___________________________ \n"+
        "  |                           |\n"+
        "  |      Ship to Flotsam      |\n"+
        "  |---------------------------|\n"+
        "  | Price: 30 copper.         |\n"+
        "  |                           |\n"+
        "  |                           |\n"+
        "  |___________________________|\n"); 

    return 1;
}

