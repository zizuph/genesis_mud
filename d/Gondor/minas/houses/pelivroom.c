inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define TP this_player()
#define TO this_object()
#define BS(xxx) break_string(xxx,70)

int scroll_taken,book_taken,parchment_taken,pouch_taken,cbopen,d1open,d2open;

create_room()
{
  set_short("The entrance hall in the first floor of a house in Minas Tirith");
  set_long("@@describe");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,"@@test_time");
  add_exit("/d/Gondor/minas/houses/peentryhall","east",0,0);
  add_item("bookshelf","@@exa_bookshelf");
  add_item("bench","The long bench may well seat four, maybe five persons.\n");
  add_item("table","The wooden table is most likely the dinner table. There are six stools\n"+
    "and chairs by the table.\n");
  add_item(({"stool","chair"}),"There are six chairs and stools here, placed around the\n"+
    "round, wooden dinner table.\n");
  add_item(({"walls","wall"}),"The walls are made of stone, but covered with quite old\n"+
    "tapestries. The walls look very solid.\n");
  add_item("tapestries","The tapestries depict scenes from ancient times. You recognize\n"+
    "the famous motif of Earendil and the Silmaril on the ship he sailed west even\n"+
    "to Valinor, to bid help for the Free Peoples in the War of Wrath against\n"+
    "Morgoth in the end of the First Age.\n");
  add_item("cupboard","@@exa_cupboard");
  add_item("shelf","@@exa_shelf");
  add_item(({"left drawer","first drawer","drawer 1"}),"@@exa_drawer1");
  add_item(({"right drawer","second drawer","drawer 2"}),"@@exa_drawer2");
  add_item(({"drawer","drawers"}),"@@exa_drawers");
}

init()
{
  ::init();
  add_action("do_open","open");
  add_action("do_close","close");
  add_action("get_item","get");
  add_action("get_item","take");
  add_action("read_book","read");
}

read_book(string book)
{
  if (!book) {
    write("Read what?\n");
    return 1;
    }
  book = lower_case(book);
  if (book == "silmarils") {
    write("You take out the book titled Silmarils, and read it.\n");
    say(QCTNAME(TP)+" reads a book titled Silmarils which "+TP->query_pronoun()
      +"\nfound in the bookshelf.\n",TP);
    cat("/d/Gondor/common/library/books/silmarils.txt");
    return 1;
    }
  if (book == "edain") {
    write("You take out the book titled Edain, and read it.\n");
    say(QCTNAME(TP)+" reads a book titled Edain which "+TP->query_pronoun()+
      "\nfound in the bookshelf.\n",TP);
    cat("/d/Gondor/common/library/books/edain.txt");
    if (!scroll_taken) call_out("drop_scroll",4);
    return 1;
    }
  if (book == "first age") {
    write("You take out the book titled First Age, and read it.\n");
    say(QCTNAME(TP)+" reads a book titled First Age which "+TP->query_pronoun()+
      "\nfound in the bookshelf.\n",TP);
    cat("/d/Gondor/common/library/books/firstage.txt");
    return 1;
    }
  return 0;
}

drop_scroll()
{
  tell_room(TO,"A scroll suddenly falls to the floor from out of the book!\n");
  scroll_taken = 1;
  clone_object("/d/Gondor/elessar/quest/revealspy/scroll")->move(TO);
  return 1;
}

do_open(string str)
{
  if (!str) {
    write("Open what?\n");
    return 1;
    }
  if (str == "cupboard" || str == "doors of cupboard") {
    if (cbopen) {
      write("The cupboard has already been opened!\n");
      return 1;
      }
    write("You open the doors of the cupboard.\n");
    say(QCTNAME(TP)+" opens the doors of the cupboard.\n",TP);
    cbopen = 1;
    return 1;
    }
  if (str == "left drawer" || str == "first drawer" || str == "drawer 1") {
    if (!cbopen) {
      write("You don't see any drawers here.\n");
      return 1;
      }
    if (d1open) {
      write("The left drawer is already opened!\n");
      return 1;
      }
    write("You open the left drawer in the cupboard.\n");
    say(QCTNAME(TP)+" opens the left drawer in the cupboard.\n",TP);
    d1open = 1;
    return 1;
    }
  if (str == "right drawer" || str == "second drawer" || str == "drawer 2") {
    if (!cbopen) {
      write("You don't see any drawers here.\n");
      return 1;
      }
    if (d2open) {
      write("The right drawer is already opened!\n");
      return 1;
      }
    write("You open the right drawer in the cupboard.\n");
    say(QCTNAME(TP)+" opens the right drawer in the cupboard.\n");
    d2open = 1;
    return 1;
    }
  return 0;
}

get_item(string str)
{
  if (!str) {
    write("Get what?\n");
    return 1;
    }
  if (str == "parchment" || str == "piece of parchment" ||
    str == "parchment from drawer" || str == "parchment from right drawer") {
    if (!cbopen || !d2open || parchment_taken) return 0;
    write("You take the piece of parchment from the drawer.\n");
    say(QCTNAME(TP)+" takes a piece of parchment from the cupboard.\n",TP);
    parchment_taken = 1;
    clone_object("/d/Gondor/elessar/quest/revealspy/parchment")->move(TP);
    return 1;
    }
  if (str == "pouch" || str == "leather pouch" || str == "pouch from drawer"
    || str == "leather pouch from drawer" || str == "pouch from left drawer") {
    if (!cbopen || !d1open || pouch_taken) return 0;
    write("You take the leather pouch from the drawer.\n");
    say(QCTNAME(TP)+" takes a leather pouch from the cupboard.\n",TP);
    pouch_taken = 1;
    clone_object("/d/Gondor/elessar/quest/revealspy/lpouch")->move(TP);
    return 1;
    }
  if (str == "notebook" || str == "little notebook" ||
    str == "notebook from shelf") {
    if (!cbopen || book_taken) return 0;
    write("You take the little notebook from the shelf inside the cupboard.\n");
    say(QCTNAME(TP)+" takes a little notebook from the cupboard.\n",TP);
    book_taken = 1;
    clone_object("/d/Gondor/elessar/quest/revealspy/notebook")->move(TP);
    return 1;
    }
  return 0;
}

exa_cupboard()
{
  string cbstr;
  if (cbopen) {
    cbstr= "The doors to the cupboard have been opened. Inside you see two "+
    "drawers of the same size, side by side. Below the drawers is a shelf. ";
    if (d1open) cbstr = cbstr+"The left drawer is opened. ";
    if (d2open) cbstr = cbstr+"The right drawer is opened. ";
    }
  else cbstr= "The cupboard is small, just about a meter from top to floor. "+
    "The doors of the cupboard are closed. ";
  return BS(cbstr+"\n");
}

exa_drawers()
{  
  if (!cbopen) return "You don't see any drawers here.\n";
  return "Which drawer? The right or the left one?\n";
}

exa_drawer1()
{
  if (!cbopen) return "You don't see any drawers here.\n";
  if (!d1open) return "The left drawer is closed.\n";
  if (!pouch_taken) 
    return "Inside the left drawer is a leather pouch, and nothing more.\n";
  return "The left drawer is empty.\n";
}

exa_drawer2()
{
  if (!cbopen) return "You don't see any drawers here.\n";
  if (!d2open) return "The right drawer is closed.\n";
  if (!parchment_taken)
    return "Inside the right drawer is a piece of parchment only.\n";
  return "The right drawer is empty.\n";
}

exa_shelf()
{
  if (cbopen) {
    if (!book_taken) return "On the little shelf inside the cupboard is a little notebook.\n";
    else return "There is nothing on the little shelf inside the cupboard.\n";
    }
  return (exa_bookshelf());
}

exa_bookshelf()
{
  return "The bookshelf is large, covering half of the west wall, and it is\n"+
    "filled with books. You find a few interesting titles you would quite\n"+
    "like to read: Silmarils, Edain, First Age.\n";
}



describe()
{
  string longstr;
  longstr = "You are in a nice and cosy livingroom in the first floor of the house. "+
    "A bench is placed along the south wall, and a wooden table with chairs "+
    "in the north end of the room. Along the west wall is a bookshelf, and "+
    "by the east wall, between the two doorways stands a cupboard. "+
    "There is a doorway leading east into the entryhall. ";
  if (tod()=="night" || tod()=="early morning")
    longstr= longstr+"Now as it is "+tod()+", the house is quiet and dark. ";
  if (tod()=="morning" || tod()=="evening")
    longstr =longstr+"Now in the "+tod()+" you hear people in the house. ";
  if (tod()=="noon")
    longstr = longstr+"It is noon, and the house is quiet. ";
    longstr = longstr+"\n";
  return BS(longstr);
}

test_time()
{
  if (tod()=="night" || tod()=="early morning") return 0;
  return 1;
}
