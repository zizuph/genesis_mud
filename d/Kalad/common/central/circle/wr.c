/*
ROOM: Hallway upstairs
BY: Korat
Date: Feb 14, 1995

- modified by Valen, 20011205, by AoP request

*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <filter_funs.h>
#define QG "/d/Kalad/common/central/npc/quest_officer"
#define WALL_ROOM "/d/Kalad/common/central/circle/window"
#define QUEST_NAME "assasinquest"
object ob1;
object ob2;
object ob3;
int enemy_here_alarm;
int still_night;

/* variables that checks the players actions towards */
/* looking at and searching the books and the bookshelf. */

int book1;
int book2;
int book3;
int book4;
int book5;
int did_exa_books;
int did_exa_dustfree_books;
int did_exa_shelves;
int did_exa_dustfree_shelves;
int did_exa_dust;
int did_exa_dustbooks;
int correct_book;
int note_found;

enter_inv(object ob,object from)
{
   object *inv;
   if (ob->query_npc())
      {
      ::enter_inv(ob,from);
      return;
   }
   inv = all_inventory();
   inv=FILTER_PLAYERS(inv);
   if (sizeof(inv)==1)
      {
      ::enter_inv(ob,from);
      set_alarm(0.0,0.0,"reset_variables");
      return;
   }
   /* someone already here! */
   if (living(ob))
      {
      ob->catch_msg("There is already someone there!\n");
      ob->catch_msg("In the panic you decide to get out of here fast!\n");
      ob->move(from);
   }
   tell_room(TO,"The "+ob->short()+" hurriedly leaves back through the "
   +"window.\n");
   tell_room(WALL_ROOM,"Suddenly "+ob->short()+" comes crawling back "
   +"through the window.\n");
   ob->move(WALL_ROOM);
}


void
create_room()
{
   ::create_room();                         
   hear_bell = 2;                           
   
   set_short("a room inside the council of Lord's building");
   set_long(
      "This room is quite small. ");
   set_time_desc(
      "Along the northern wall you see a huge bookshelf covering it, "+
      "while in the middle of the room there is a wooden desk. Except "+
      "that, you feel fairly nervous, standing here in the "+
      "middle of the day. Maybe its because you came in through "+
      "the window like a common thief.\n",
      "In the darkness you can faintly see a huge bookshelf covering "+
      "the northern wall, filled to the rim with books. "+
      "Other than that you notice a wooden desk that stands "+
      "in the middle of the room. You feel a bit nervous since "+
      "daylight will soon come and wake people up.\n");
   add_item("desk","The desk is littered with letters, books and "+
      "other writing tools like pencils.\n");
   add_item("bookshelf","The shelves are filled to the rim with books. "+
      "There must be hundreds of them!\n");
   add_item("book","Book?? There are hundreds of them!\n");
   add_item("books","You let your eyes sweep over them all..."+
      "and discover hundreds of dust covered books, all with a number "
      +"on its cover. It would take a day to study them all thoroughly..."
      +"and a creeping feeling tells you that you will not have a day "
      +"alone here.\n");
   add_item("dust covered books","@@again@@Well, most of the books here "+
      "seems to be covered with dust, but "+
      "some of them, spread around in the bookshelf, "+
      "is dustfree.\n");
   add_item("dustfree","@@what_dustfree_to_look_at@@");
   add_item("dustfree books","@@dustfree_books@@");
   add_item("shelf","Shelf?? There is piles of shelves here.\n");
   add_item("shelves","You check all the shelves, and notice that most of "+
      "them are covered in dust. These books can't have been read for "
      +"ages!\n");
   add_item("dust covered shelves","Most of the shelves are filled "+
      "with dust, making you wanting to sneeze loudly! You "+
      "manage to control yourself, and notice that some shelves "+
      "are fairly dust free.\n");
   add_item("dust free shelves","@@dustfree_shelves@@");
   add_item(({"dust","dust cover"}),"You start "+
      "to examine all the dust around here. Very "+
      "interesting! Most of the books and most of the shelves, "+
      "and of course most of the floor contains a lot of this "+
      "substance. @@again1@@  \n");
   add_item(({"letter","letters","pencil"}),"Its just what you see. Letters "+
      "pencils and books.\n");
   add_exit(CENTRAL(circle/window),"window","@@guards",0,0);
   if (DAY) still_night = 0; else still_night = 1;
   if (DAY) set_alarm(0.0,0.0,"get_guards");
   set_alarm(60.0,60.0,"check_time");
}

init()
{
   ::init();
   add_action("read","study book");
   add_action("read","study");
}

int
read(string str)
{
   int number;
   string *text;
   notify_fail("Study what? To study a book from the shelves, type "+
         "'study book' and then the number of the book to study.\n");
   if (!str) return 0;
   notify_fail("Study which book? Type 'study book' and then the number of "+
         "the book to study.\n");
   text = explode(str, " ");
   if (!sscanf(text[sizeof(text)-1],"%d",number))
      return 0;
   TP->catch_msg("You start to leaf through the book.\n");
   if ((number != book1 ) &&
         (number != book2) &&
      (number != book3) &&
      (number != book4) &&
      (number != book5))
   {
      set_alarm(5.0,0.0,"read_wrong_book");
      return 1;
   }
   set_alarm(5.0,0.0,"read_book",number);
   return 1;
}

read_wrong_book()
{
   TP->catch_msg("After a while you end up utterly bored, and not "+
      "any wiser. You put the book back.\n");
}

read_book(int num)
{
   object note;
   if (num == correct_book)
      {
      note = clone_object("/d/Kalad/common/central/obj/quest_note");
      TP->catch_msg("The book is utterly boring! But...ohh, what's that? "
      +"A small sheet hidden within the book! You take it out.\n");
      note->move(TP);
      note_found = 1;
/*
      if(TP->test_bit("Kalad",1,11))
         {
*/

/*
 - modified by Valen, 20011205
   message commented out to avoid confusing a player who can start to think
   that something was done wrong. By the way, why the award was removed?

         TP->catch_msg("You don't feel more experienced.\n");
*/

/*
       }
      else
         {
*/
         TP->set_bit(1,11);
/*
         TP->add_exp(5000);
         TP->catch_msg("You feel more experienced!\n");
         seteuid(getuid(TO));
         log_file(QUEST_NAME, extract(ctime(time()),4,15) + " "+
            capitalize(TP->query_real_name()) + " rewarded with 5000 xp,"+
            "<"+TP->query_average_stat()+"> average stats.\n");
       }
*/
      return;
   }
   TP->catch_msg("The whole book is boring, boring and boring. "+
      "You put it back with a sigh.\n");
}



reset_variables()
{
   did_exa_books = 0;
   did_exa_dustfree_books = 0;
   did_exa_shelves = 0;
   did_exa_dustfree_shelves = 0;
   did_exa_dust = 0;
   did_exa_dustbooks = 0;
   note_found = 0;
   book1=random(20)+1;
   book2=random(20)+21;
   book3=random(20)+41;
   book4=random(20)+61;
   book5=random(20)+81;
   switch (random(5)+1)
   {
      case 1: correct_book=book1; break;
      case 2: correct_book=book2; break;
      case 3: correct_book=book3; break;
      case 4: correct_book=book4; break;
      default: correct_book=book5; break;
   }
}


again()
{
   if (did_exa_dustfree_books) return "Again?? ";
   did_exa_dustbooks = 1;
   return "";
}

again1()
{
   if (did_exa_dust)
      {
      set_alarm(0.0,0.0,"get_guards");
      return "After crawling around in the dust, you "+
      "just cannot control yourself! You sneeze loudly!";
   }
   did_exa_dust = 1;
   return "After crawling around in the dust, you get "+
   "an urgent need to sneeze loudly, but manage to stop "+
   "in time!";
}

dustfree_books()
{
   int i;
   string str;
   str = "";
   if (did_exa_dustfree_books) str = "Again?? ";
   did_exa_dustfree_books = 1;
   str = str+"You let your eyes sweep over all the books, and "+
   "in the end you see fifty books without dust. Someone "+
    "actually uses them! You wonder what for...";
   if (did_exa_dustfree_shelves)
      {
      str=str+"You realise that there only are "+
      "five books that has recently been used, since those "+
      "five are the only ones that are dusfree and has recent traces of "+
      "being moved on the shelves. Maybe you should study them? ";
      str = str+"You make a mental note of what books that is: Book "+
      book1+", "+book2+", "+book3+", "+book4+" and "+book5+".";
   }
   str=str+"\n";
   return str;
}

dustfree_shelves()
{
   int i;
   string str;
   if (did_exa_dustfree_books) str="Again?? ";
   else str="";
   did_exa_dustfree_shelves = 1;
   str=str+"You start to examine the dustfree shelves, and "+
   "after some time you realise that some of the books "+
   "on these shelves has been recently used. ";
   if (did_exa_dustfree_books) str=str+" When your brilliant mind "+
      "starts to think, you realise that there are five books that has "
      +"been used most recently, since they are dust free, and they show "
      +"signs of being moved on the shelves. You make a mental note of "
      +"which books that is: Book "+book1+", "+book2+", "+book3+", "
      +book4+" and "+book5+". "+ "Maybe you should study them some?";
   str=str+"\n";
   return str;
}


/* Make the guards that will try to kill the thief/player */
/* These guards will be of similar stats as the player */
/* and will attack with a special skill. The player can */
/* leave out the window; but the guards will try to stop */
/* him/her. They have a 1 to con/10 chance of leaving */
get_guards()
{
   object *enemy;
   enemy = FILTER_PLAYERS(all_inventory(TO));
   if (sizeof(enemy)>1) return;
   set_alarm(10.0,0.0,"make_guards",enemy[0]);
   tell_room(TO,"Someone shouts: GUUAAARRRDDSSSsssss!\n");
}

make_guards(object enemy)
{
   int str, dex, con;
   str = TP->query_stat(SS_STR);
   dex = TP->query_stat(SS_DEX);
   con = TP->query_stat(SS_CON);
   if (!objectp(ob1))
      {
      ob1 = clone_object(QG);
      ob1 -> arm_me();
      ob1 -> set_stats(({ str, dex, con, 50, 50, 140}));
      ob1 -> move_living("M",TO);
      ob1 -> set_hp(ob1->query_max_hp());
      if(con<80) ob1->set_skill(SS_WEP_SWORD,50);
      tell_room(TO,"Suddenly some guards comes stumbling into the room "
      +"through a secret door in the bookshelf!\n");
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object(QG);
      ob2 -> arm_me();
      ob2  -> set_stats(({ str, dex, con, 50, 50, 140}));
      ob2 -> move_living("M",TO);
      ob2->set_hp(ob2->query_max_hp());
      if(con<80) ob2->set_skill(SS_WEP_SWORD,50);
      ob2 -> team_join(ob1);
   }
   if(!objectp(ob3))
      {
      ob3 = clone_object(QG);
      ob3 -> arm_me();
      ob3  -> set_stats(({ str, dex, con, 50, 50, 140}));
      ob3 -> move_living("M",TO);
      ob3->set_hp(ob3->query_max_hp());
      if(con<80) ob3->set_skill(SS_WEP_SWORD,50);
      ob3 -> team_join(ob1);
   }
   /* check to see if the enemy is gone. If so, then remove the guards. */
      enemy_here_alarm=set_alarm(100.0,60.0,"enemy_gone",enemy);
}

enemy_gone(object enemy)
{
   object who;
   if(who=present(enemy,TO))
      return;
   tell_room(TO,"Since the thief escaped, the guards decide to leave.\n");
   if (objectp(ob1)) ob1->remove_object();
   if (objectp(ob2)) ob2->remove_object();
   if (objectp(ob3)) ob3->remove_object();
   remove_alarm(enemy_here_alarm);
}

/* if day comes, the guards will enter tokill the thief/player */
   /* The player are given 10 seconds to get out. */
check_time()
{
   if (DAY) tell_room(TO,"Its day now....\n");
   if (!DAY) tell_room(TO,"Its night now....\n");
   if (DAY && still_night)
      {
      still_night = 0;
      set_alarm(10.0,0.0,"make_guards");
      tell_room(TO,"You notice daylight starts to shine through the "+
         "window. Suddenly you here voices behind the bookshelf!\n");
      return;
   }
   if (!DAY && !still_night)
      still_night = 1;
}

guards()
{
   int pres;
   int chance, con_stat;
   if (objectp(ob1) || objectp(ob2) || objectp(ob3)) pres = 1; else pres = 0;
   if (pres == 1){
      con_stat= TP->query_stat(SS_CON);
      chance = random(con_stat/10);
      if (chance>0)
         {
         write("The guards pulls you back from the window, stopping your "
         +"escape.\n");
         say("The guards pulls "+QTNAME(TP)+" back from the window, "+
            "preventing the escape.\n");
         return pres;
       }
      TP->catch_msg("You manage to jump out of the window!\n");
      say("The guards failed in catching the thief!\n");
      pres = 0;
   }
   return pres;
}
