inherit "/std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"

void reward_player(object ob);
 
create_room()
{
    object door;

    set_short("Dark creepy room");
    set_long(BSS("This is a dark creepy room that Pandora does her best to hide from "+
                "the rest of the world. There are a large desk, some vials and bottles here. "+
                "There is something lying over the floor.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 

    add_item(({"strange door", "door"}), BSS("It is more like the wall has opened.\n"));

    add_item(({"symbol","symbols","rune","runes"}), BSS(
		"There are a load of symbols carved into "+
		"the desk. They seems to have been "+
		"there for ages.\n"));
    add_item(({"floor", "floor"}), BSS("You cannot really see the floor because there lies a thin layer of fog over it.\n"));
    add_item(({"thin fog", "fog"}), BSS("The fog is a thin layer of white smoke.\n"));
    add_item("desk",BSS(
              "The desk is large and dusty, it seems no one has been here "+
              "for quite some time, though you see a small spot on the edge "+
              "of the desk with almost no dust at all, just as if someone "+
              "has removed something there not so long ago. There are "+
              "some runes and symbols carved into the wood on some places of "+
              "the desk.\n"));

    add_item(({"vial","vials"}),BSS(
                "The vials are all dirty and used, but since the smell of the contents "+
		"almost knocks you over, you can safely assume "+
		"that it has been a long time since they were used.\n"));

    add_item(({"bottle","bottles"}),BSS(
                "The bottles are empty, yet some of them have drops of "+
		"liquid in them that do not smell good.\n"));

    door= clone_object(DOOR_D+"secr_door_d");
    door->move(this_object());

    add_prop(OBJ_S_SEARCH_FUN, "search_it");
}

string
search_it(object player, string what)
{
    if (what != "floor")
        return 0;
    if (player->query_skill(SS_AWARENESS)>45 && !QDONE(GROUP2,ANTONSHIT2));
    {
      clone_object(A_OBJ_D+"papyrous")->move(this_object());
      reward_player(this_player());
      return "Your search reveals a strange looking object!\n";
    }
    return 0;
}

void
reward_player(object ob)
{
   int xp, cnt;
   
/* this is a great example of what not to make your code look like!
   Anton-the-shithead has really screwed up! */

   if(ob)
      if(objectp(ob))
      if(present(ob, this_object())) 
      {
         if(!ob->test_bit("Roke", GROUP2, ANTONSHIT2))
    	 {
            ob->set_bit(GROUP2, ANTONSHIT2);
            seteuid(getuid());
            xp = 18000;
            ob->add_exp(xp, 0);
            ob->catch_msg("You feel more experienced.\n");
	    QLOG("pandora part 2");
         }
   }
}



