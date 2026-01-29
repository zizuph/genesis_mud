/*
 * Thief Hideout 
 * 
 * Thanks to Quaid of Faerun for the help with some of the descriptions
 * and ideas about what should be in the room or not.
 *
 * Quest idea:
 *
 * The drapery of cloth that conceals the small workroom behind it could
 * be apart of a quest, the old thief could have some secret mechanism to
 * reveal his treasures.
 * Something with placing a torch in the stand on the other side, locate
 * his prism/glass or so to focus the beam of light onto a crystal in the
 * west wall above the entrance, when the drapery is open and the beam of
 * light hits it, the secret door would reveal itself and could be opened.
 *
 * Lunatari of Krynn
 * 2008-02-02: Creation and exit to the tunnels.
 * 2008-02-10: Added drapery code and more descriptions.
 */
#include "local.h"
#include <ss_types.h>

inherit DUNGEON_IN;

#define T_OTHER DROOM + "tun17"
#define T_SEARCHED_HAY "_i_found_the_locket_"
#define T_SEARCHED_MADRASS "_i_found_the_hay_" 
#define T_QUEST_LOCKET DOBJ + "thief_locket"

string get_drapery_desc();
string get_room_desc();
int check_drapery();
int check_drapery_show();

create_dungeon_room()
{
   set_short("Inside a small cave");
   set_long(get_room_desc);

   add_item(({"cloth", "curtain", "drapery"}), get_drapery_desc); 
   add_item(({"mattress", "old madrass"}), "Lying on the floor is a very " +
      "old and worn down mattress. The madrass is or well was filled with " + 
      "hay to make it nice and fluffy to sleep ontop of. It has now lost " +
      "most of its hay through a hole that has been torn up in its side.\n");
   add_item(({"bed", "bunk", "sleeping place"}), "On a natural shelf in " +
      "the north wall a crude wooden frame has been placed, it is not " +
      "very big but seems to be able to fit a normal person atleast.\n");
   add_item(({"pile", "debris", "junk"}), "Scattered all over the cave " +
      "are old clothes, rocks, forks, knives and shoes, some broken, " +
      "some just very old and unusable.\n");

   add_item(({"knives", "knife", "fork", "forks", "shoe", "shoes", "rocks",
      "rock", "clothes", "shirt", "trousers"}), 
      "Nothing useful, it is just junk.\n");
   add_item(({"opening", "hole" }), "A narrow hole in the west wall that " +
      "leads into a tunnel on the other side, it seems to provide an " +
      "exit out of this cave.\n");

   add_item(({"hay", "straws" }), "All over the place are spread out " +
      "straws of hay, most likely from the old mattress.\n");

   add_exit("thief2", "east", check_drapery, 5, check_drapery_show);

   add_search(({ "mattress", "old mattress" }), 5, "search_madrass", 2);
   add_search(({ "straws", "hay" }), 15, "search_hay", 2);
   add_search(({ "bed", "bunk", "sleeping place" }), 20, "search_bed", 2);

   DARK;
}

init()
{
  ::init();
  add_action("enter_opening", "enter");
  add_action("move_drapery", "move");
}

mixed
search_hay(object player, string arg)
{
    string found = "Your search and search but find nothing special.";
    object quest;
    
    if (!player->query_prop(T_SEARCHED_MADRASS))
    {
        return "You don't see any special hay to search.";
    }

    if ((player->query_stat(SS_WIS) > 70) &&
        (player->query_skill(SS_AWARENESS) > 20))
    {
    
       if (!player->query_prop(T_SEARCHED_HAY))
       {
          player->add_prop(T_SEARCHED_HAY, 1);
          found = "You search the " + arg + " thoroughly and discover " +
                  "an old antique silver locket.";
          if(quest = clone_object(T_QUEST_LOCKET))
          {
            quest->move(TP, 1);
          }
          
       }
       else
       {
          found = "You search the " + arg + " again but it reveals " +
                 "you nothing more of interest.";
       }
    }
    
    return found + "\n";
}

mixed
search_bed(object player, string arg)
{
    return "After searching through the sad remains of a sleeping " +
      "place, you find absolutely nothing of interest.\n";
}

mixed
search_mattress(object player, string arg)
{
    string found = "Your search and search but find nothing special.";
    
    if ((player->query_stat(SS_WIS) > 70) &&
        (player->query_skill(SS_AWARENESS) > 20))
    {
    
       if (!player->query_prop(T_SEARCHED_MADRASS))
       {
          player->add_prop(T_SEARCHED_MADRASS, 1);
          found = "You search the " + arg + " thoroughly and discover " +
                  "that the hay looks very interesting and might hold " +
                  "more than the actual madress.";
       }
       else
       {
          found = "You search the " + arg + " again but it reveals " +
                 "you nothing more of interest.";
       }
    }
    
    return found + "\n";
}


string
get_drapery_desc()
{
  string text;

  switch (DMASTER->query_status(S_TDRAPERY))
  {
    case 1:
      text = "The drapery seems to have been moved all the way to the " +
        "left, no longer concealing the alcove to the east."; 
    break;
    default:
      text = "A long piece of rugged cloth hangs from a small wooden " +
        "pole on the east wall. It seems to be a curtain ment to conceal " +
        "whatever lays behind it.";
  }
  return text + "\n";
}

string
get_room_desc()
{
  string text;

  text = "Inside a cave, not small but yet not large either. The cave " +
    "seems to have been some sort of hideout a long time ago. The cave " +
    "is filled with various crates, a table, some broken chairs, a bed " +
    "type creation with an old mattress ontop of it. The floor is covered " +
    "with debris, various items that has their belonging with a thief " +
    "such as lock picks, lay spread out across the cave. ";

  switch (DMASTER->query_status(S_TDRAPERY))
  {
     case 1:
       text += "A drapery hangs on a wooden pole on the east wall, the " +
         "drapery has been pulled all the way to the left, revealing an " +
         "alcove to the east.";
     break;
     default:
       text += "The eastern wall is covered with a huge drapery made " +
         "out of thick black cloth.";
  }

  return text + "\n";
}

int
check_drapery()
{
  if(DMASTER->query_status(S_TDRAPERY)) return 0;

  write("There is no obvious exit east.\n");
  return 1;
}

int
check_drapery_show()
{
  if(DMASTER->query_status(S_TDRAPERY)) return 0;

  return 1;
}


int
move_drapery(string str)
{
  notify_fail("Move what? The drapery?\n");

  if (!str) return 0;

  if (parse_command(str, ({ }),"[the] 'drapery' / 'curtain' / 'cloth'"))
  {
      if(DMASTER->query_status(S_TDRAPERY))
      {
        write("You pull the drapery all the way to the right, until " +
          "it covers the eastern alcove once again.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " pulls the drapery all the " +
          "way to the right, until it covers the alcove once again.\n", TP);
        DMASTER->set_status(S_TDRAPERY, 0);
        return 1;
      }
      else
      {
        write("You pull the drapery all the way to the left, behind " +
          "it an alcove to the east is revealed.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " pulls the drapery all the " +
          "way to the left, revealing an alcove to the east.\n", TP);
        DMASTER->set_status(S_TDRAPERY, 1);
        return 1;
      }

    return 0;
  }

  return 0;
}

int
enter_opening(string str)
{
    notify_fail("Enter what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] 'hole' / 'opening'"))
    {
       write("You enter opening and crawl into the tunnel.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " enters the opening and " +
         "vanishes out of sight.\n", TP);
       set_dircmd("opening");
       TP->move_living("M", T_OTHER, 1);
       tell_room(ENV(TP), QCTNAME(TP) + " crawls in from opening in " +
         "the east.\n", TP);
       return 1; 
    }

    return 0;
}
