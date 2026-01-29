inherit "/std/room";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"

#define PLAYER_KILLED_PANDORA "_player_killed_pandora"
int key_taken_flag;

void reward_player(object ob);

reset_room()
{
  key_taken_flag = 0;
}
 
create_room()
{
  object key;
  set_noshow_obvious(1);

  set_short("Laboratory");
  set_long(BSS("This is Pandora's laboratory, you see lots of vials, bottles "+
	       "and books on the large desk. In front of you, you see a big window. "+
	       "The only exit is down.\n"));
  add_prop(ROOM_I_INSIDE, 1);

  add_exit(HOUS_D+"stair3","down",0);

  clone_object(A_NPC_D+"pand")->move_living(" arrives in a puff of smoke", this_object());

  add_item(({"large desk", "desk"}), BSS("The desk is covered by bottles, vials and books. You wonder how anyone can work here. You think you noticed something dark on the desk.\n"));
  add_item(({"book", "books"}), BSS("These books are the alchemist books of Pandora.\n"));
  add_item(({"vial", "vials"}), BSS("The vials contain some greasy stuff, you do not want to touch it.\n"));
  add_item(({"bottle", "bottles"}), BSS("The bottles contains different potions.\n"));
  add_item(({"big window", "window"}), BSS("Looking through this window, you understand why Pandora always knows what's going on around in the city of Tyr.\n"));

  add_prop(OBJ_S_SEARCH_FUN, "search_it");
  call_out("reset_room", 1);
  
}

string
search_it(object player, string what)
{
  if(what != "desk")
    return 0;
   
  
  if (present("pandora")){
    write(BSS("Pandora obviously doesn't like you snooping around "+
		"her laboratory. She mumbles a few words and you find "+
	      "yourself in a totally different place.\n"));
    player->move_living("X", CELL_D+"cell1");
    return "";
  }
  if(key_taken_flag)
    return 0;


    setuid();
    seteuid(getuid(this_object()));
    clone_object(DOOR_D+"secret_key")->move(player);
    key_taken_flag = 1;
    this_object()->reward_player(this_player());
    return "Your search reveals a strange key, and you quickly pick it up.\n";

}

void
reward_player(object ob)
{
   int xp, cnt;
   
   if(ob)
      if(objectp(ob))
      if(present(ob, this_object())) 
      {
         if(!ob->test_bit("Roke", GROUP2, ANTONSHIT1))
         {
            ob->set_bit(GROUP2, ANTONSHIT1);
            seteuid(getuid());
            xp = 7500;
            if(ob->query_prop(PLAYER_KILLED_PANDORA)) 
                xp = 5000;
            ob->add_exp(xp, 0);
            ob->catch_msg("You feel more experienced.\n");
	    QLOG("pandora part 1");
         }
   }
}
