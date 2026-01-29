/*
 *  The Go board, as Fub redesigned it at our mud named Muis.
 *  Features some more Go problems. I added some randomness to the whole.
 *                                            Tricky 29-4-92
 */

#pragma save_binary

inherit "/std/object";

#include "/sys/stdproperties.h"

int problem_no;
int *problem_numbers;

success_noise(str);
failure_noise(str);

create_object() {
  set_name(({"go_board","board","go board"}));
  set_adj("go");
  set_short("go board");
  set_long("@@show_problem");
  add_prop(OBJ_I_NO_GET,1);

  problem_numbers = ({ 0,1,2,3,4,5,6,7,8,9,10,11,12,13 });
  choose_new_problem();

  enable_reset();
}

reset_object() {
  if (problem_no == -1)
  {
    problem_numbers = ({ 0,1,2,3,4,5,6,7,8,9,10,11,12,13 });
    choose_new_problem();
  }
}

show_problem() {
  string bord;
  if (problem_no >= 0) {
    bord = "The board looks like this:\n\n";
  }
  else {
    return("The board is empty at the moment.\n");
  }
  if (problem_no == 0) {
    bord += "5|.......\n";
    bord += "4|.......\n";
    bord += "3|@@@@@..\n";
    bord += "2|OOOO@..\n";
    bord += "1|...O@..\n";
    bord += " +-------\n";
    bord += "  abcdefg\n";
    bord += "\nBlack ('@') has to make the next move.\n";
    return(bord);
  }
  if (problem_no == 1) {
    bord += "7|.......\n";
    bord += "6|.......\n";
    bord += "5|@@@....\n";
    bord += "4|OOO@@..\n";
    bord += "3|O.OO@..\n";
    bord += "2|...O@..\n";
    bord += "1|..OO@..\n";
    bord += " +-------\n";
    bord += "  abcdefg\n";
    bord += "\nBlack ('@') has to make the next move.\n";
    return(bord);
  }
  if (problem_no == 2) {
    bord += ".O..|8\n";
    bord += "..O.|7\n";
    bord += ".O..|6\n";
    bord += ".O@.|5\n";
    bord += ".O@.|4\n";
    bord += ".O@@|3\n";
    bord += ".O@.|2\n";
    bord += ".O@.|1\n";
    bord += "----\n";
    bord += "qrst\n";
    bord += "\nWhich move would white ('O') make to win the game?\n";
    return(bord);
  }
  if (problem_no == 3) {
    bord += "  +-------\n";
    bord += "19|.......\n";
    bord += "18|.......\n";
    bord += "17|...@.O.\n";
    bord += "16|...@...\n";
    bord += "15|...O.O.\n";
    bord += "14|...O...\n";
    bord += "13|..@@OO.\n";
    bord += "12|....@..\n";
    bord += "11|...@...\n";
    bord += "   abcdefg\n";
    bord += "\nWhat would black ('@') play to connect both groups?\n";
    return(bord);
  }
  if (problem_no == 4) {
    bord += "  +-------\n";
    bord += "19|.......\n";
    bord += "18|.@@....\n";
    bord += "17|.@O@@@.\n";
    bord += "16|.@OOO@.\n";
    bord += "15|.O..OO.\n";
    bord += "14|.......\n";
    bord += "13|..@.O..\n";
    bord += "12|.......\n";
    bord += "11|..OOO..\n";
    bord += "   abcdefg\n";
    bord += "\nWhat would black ('@') play to connect his single piece to the rest?\n";
    return(bord);
  }
  if (problem_no == 5) {
    bord += "  +------\n";
    bord += "19|......\n";
    bord += "18|......\n";
    bord += "17|..O...\n";
    bord += "16|..@O..\n";
    bord += "15|@@@O..\n";
    bord += "14|.OO@..\n";
    bord += "13|.O@@..\n";
    bord += "12|.O@...\n";
    bord += "11|.@@...\n";
    bord += "10|......\n";
    bord += "   abcdef\n";
    bord += "\nWhich move would white ('O') make in order to get the 4 black pieces?\n";
    return(bord);
  }
  if (problem_no == 6) {
    bord += "11|......\n";
    bord += "10|....@.\n";
    bord += " 9|..@@..\n";
    bord += " 8|..O@..\n";
    bord += " 7|...OO.\n";
    bord += " 6|......\n";
    bord += " 5|..@.O.\n";
    bord += " 4|......\n";
    bord += " 3|....O.\n";
    bord += " 2|..O...\n";
    bord += " 1|......\n";
    bord += "  +------\n";
    bord += "   abcdef\n";
    bord += "\nHow must black ('@') connect his piece on c5 with the other "
          + "pieces?\n";
    return(bord);
  }
  if (problem_no == 7) {
    bord += "  +-----\n";
    bord += "19|.....\n";
    bord += "18|..@@.\n";
    bord += "17|.OO@.\n";
    bord += "16|.@.@.\n";
    bord += "15|.@...\n";
    bord += "14|.OO..\n";
    bord += "13|.....\n";
    bord += "   abcde\n";
    bord += "\nWhat will white ('O') play to connect his pieces?\n";
    return(bord);
  }
  if (problem_no == 8) {
    bord += "  +------\n";
    bord += "19|......\n";
    bord += "18|O@@@..\n";
    bord += "17|.OO@..\n";
    bord += "16|..@O@.\n";
    bord += "15|.@@O..\n";
    bord += "14|.OOO..\n";
    bord += "13|...O..\n";
    bord += "12|......\n";
    bord += "   abcdef\n";
    bord += "\nWhat move would black ('@') play to catch the three white "+
            "pieces?\n";
    return(bord);
  }
  if (problem_no == 9) {
    bord += "11|.........\n";
    bord += "10|.........\n";
    bord += " 9|.@@@.@@..\n";
    bord += " 8|.OO....@.\n";
    bord += " 7|..OO.O.@.\n";
    bord += " 6|......O@.\n";
    bord += " 5|..O.@.O@.\n";
    bord += " 4|.....@@O.\n";
    bord += " 3|...O...O.\n";
    bord += " 2|....O.O..\n";
    bord += " 1|.........\n";
    bord += "  +---------\n";
    bord += "   abcdefghj\n";
    bord += "\nWhich move would black ('@') make, in order to save his three "
          + " stones\nthat are surrounded by white pieces?\n";
    return(bord);
  }
  if (problem_no == 10) {
    bord += "11|......\n";
    bord += "10|..@O..\n";
    bord += " 9|..@O..\n";
    bord += " 8|....O.\n";
    bord += " 7|..OO..\n";
    bord += " 6|.@@O..\n";
    bord += " 5|@OO...\n";
    bord += " 4|.@O.O.\n";
    bord += " 3|.@....\n";
    bord += " 2|..@...\n";
    bord += " 1|......\n";
    bord += "  +------\n";
    bord += "   abcdef\n";
    bord += "\nWhat would black ('@') do to connect the upper two stones "
          + "with the rest?\n";
    return(bord);
  }
  if (problem_no == 11) {
    bord += "8|.......\n";
    bord += "7|.OO....\n";
    bord += "6|@@OOO..\n";
    bord += "5|.O@@.O.\n";
    bord += "4|@@..@O.\n";
    bord += "3|..@@O..\n";
    bord += "2|.OOOO..\n";
    bord += "1|.......\n";
    bord += " +-------\n";
    bord += "  abcdefg\n";
    bord += "\nWhite ('O') is the next one to move.\n";
    return(bord);
  }
  if (problem_no == 12) {
    bord += "6|..O......\n";
    bord += "5|.....@.@.\n";
    bord += "4|OOOO...@O\n";
    bord += "3|@@O@@@@OO\n";
    bord += "2|.@@O@OO..\n";
    bord += "1|...OO....\n";
    bord += " +---------\n";
    bord += "  abcdefghj\n";
    bord += "\nHow should white ('O') move to catch four black stones?\n";
    return(bord);
  }
  if (problem_no == 13) {
    bord += "5|..........\n";
    bord += "4|...@@@@@..\n";
    bord += "3|@@@.O...@.\n";
    bord += "2|@OO@OOOO@.\n";
    bord += "1|@OO.O...@.\n";
    bord += " +----------\n";
    bord += "  abcdefghij\n";
    bord += "\nWhite ('O') is the next one to move.\n";
    return(bord);
  }
}

init() {
  ::init();
  add_action("tell_me","say");
  add_action("tell_me","'");
}


/*
 * Note by Tricky:
 * This function must always return 0, else nothing will be said in the room.
 */
tell_me(str) {
  string pre, wat;

  if(!str) return 0;

  str = lower_case(str);

  if (sscanf(str, "%stry %s", pre, wat) != 2)
    if (sscanf(str,"%splay %s", pre, wat) != 2)
      wat = "";

  if (wat != "")
  {
    if (problem_no == 0)
    {
      if (wat == "b1" || wat == "b 1" || wat == "1 b" || wat == "1b")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 1)
    {
      if (wat == "b2" || wat == "b 2" || wat == "2 b" || wat == "2b")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 2)
    {
      if (wat == "t5" || wat == "t 5" || wat == "5t" || wat == "5 t")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 3)
    {
      if (wat == "b15" || wat == "b 15" || wat == "15b" || wat == "15 b")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 4)
    {
      if (wat == "b14" || wat == "b 14" || wat == "14b" || wat == "14 b")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 5)
    {
      if (wat == "a16" || wat == "a 16" || wat == "16a" || wat == "16 a")
      return solved();
      else
        return wrong();
    }
    if (problem_no == 6)
    {
      if (wat == "b7" || wat == "b 7" || wat == "7 b" || wat == "7b")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 7)
    {
      if (wat == "a15" || wat == "a 15" || wat == "15 a" || wat == "15a")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 8)
    {
      if (wat == "a16" || wat == "a 16" || wat == "16 a" || wat == "16a")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 9)
    {
      if (wat == "f6" || wat == "f 6" || wat == "6 f" || wat == "6f")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 10)
    {
      if (wat == "b8" || wat == "b 8" || wat == "8 b" || wat == "8b")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 11)
    {
      if (wat == "d4" || wat == "d 4" || wat == "4 d" || wat == "4d")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 12)
    {
      if (wat == "a2" || wat == "a 2" || wat == "2 a" || wat == "2a")
        return solved();
      else
        return wrong();
    }
    if (problem_no == 13)
    {
      if (wat == "d3" || wat == "d 3" || wat == "3 d" || wat == "3d")
        return solved();
      else
        return wrong();
    }

    go_player_say("Go player says: Leave me alone! I am trying to think!\n");
    return(0);
  }
  return(0);
}

solved() {
  int rnd;
  string tmp;

  rnd = random(4);

  if (rnd == 0)
    tmp = "Go player says: Yes! That works! Very good!\n";
  else if (rnd == 1)
    tmp = "Go player says: How can that be? Why couldn't I see that?\n";
  else if (rnd == 2)
    tmp = "Go player says: Geee, so simple and yet it works... Amazing!\n";
  else if (rnd == 3)
    tmp = "Go player says: Sheesh! You are already better at this than I am!\n";

  set_alarm(2.0, 0.0, &success_noise(tmp));

  /* Add quest experience, although not too much! */
  /* Disabled by Shiva, Aug 5, 1998.  Quests should not be able
   * to be repeated.
  if (this_player()->query_exp() < 100000)
    this_player()->add_exp(10 + random(30));
  */
  return 0;
}

wrong() {
  int rnd;
  string tmp;

  rnd = random(5);

  if (rnd == 0)
     tmp = "Go player says: I don't think it is that easy.\n";
  else if (rnd == 1)
     tmp = "Go player falls down laughing.\n"
         + "Go player says: Are you kidding? Of course that won't work!\n";
  else if (rnd == 2)
     tmp = "Go player says: My god! Not even a gnome would come up with that!\n"
         + "Go player says: I don't think you know anything about Go, do you?\n"
         + "The Go player tries to concentrate again.\n";
  else if (rnd == 3)
     tmp = "Go player says: Uh... This is Go, not chess!\n";
  else if (rnd == 4)
     tmp = "Go player says: If I were you, I would take a Go course!\n";

  tmp += "The Go player quickly puts another problem on the board.\n";

  set_alarm(2.0, 0.0, &failure_noise(tmp));
  return 0;
}

make_noise(str)
{
  go_player_say("The Go player contemplates the proposed play.\n");
  go_player_say(str);
}

failure_noise(str)
{
  int i;

  i = random(sizeof(problem_numbers));
  problem_no = problem_numbers[i];
  make_noise(str);
}

success_noise(str)
{
  str = choose_new_problem(str);
  make_noise(str);
}

choose_new_problem(str)
{
  int i,index;

  index = member_array(problem_no, problem_numbers);
  problem_numbers = exclude_array(problem_numbers,index,index);

  if (sizeof(problem_numbers))
  {
    i = random(sizeof(problem_numbers));
    problem_no = problem_numbers[i];
    str = str + "The Go player immediately puts a new problem on the board.\n";
  }
  else
    problem_no = -1;

  return str;
}

go_player_say(str)
{
   object pl;

   pl = present("go_player", environment());
   if (pl)
   {
      pl->make_noise(str);
   }
}
