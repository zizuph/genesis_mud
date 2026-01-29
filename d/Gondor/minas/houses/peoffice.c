/*
 * Rewrite with drawer and closet as objects (receptacles)
 * Olorin, Jan 1995
 */
inherit "/std/room";
inherit "/d/Gondor/common/lib/time.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

int     draweropen,
        drawerunlocked,
        closetopen,
        book_taken,
        ring_taken,
        key_taken;

void
create_room()
{
  set_short("An office on the second floor");
  set_long("@@describe");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,1);
  add_item("desk","@@exa_desk");
  add_item(({"cloak", "dark cloak", "grey cloak", "dark grey cloak", }),
      "@@exa_cloak");
  add_item("closet","@@exa_closet");
  add_item(({"clothing","clothes"}),"@@exa_clothes");
  add_item(({"bookshelf", "shelf", }),
      BSN("The bookshelf contains a couple of books "
    + "about the history of Gondor, but none of them interest you "
    + "particularly."));
  add_item("papers", BSN("The papers contain detailed, but uninteresting "
    + "plans for the trade between Minas Tirith and Pelargir."));
  add_item(({"carvings","patterns"}),"@@exa_patterns");
  add_item("drawer","@@exa_drawer");
  add_exit(MINAS_DIR + "houses/pebedroom1","east",0,0);
  seteuid(getuid());
}

void
init()
{
  ::init();
  add_action("check_time","time");
  add_action("do_open","open");
  add_action("do_close","close");
  add_action("do_get","get");
  add_action("unlock_drawer","unlock");
}

string
describe()
{
    string  longstr =
            "You are in the office of the lord of the mansion, up on the "
          + "second floor of the house. It is now "+tod()
          + ". By the south wall of the room stands a large oak desk, "
          + "covered with papers and books. A bookshelf with a few "
          + "books is placed by the east wall, and in the northwestern "
          + "corner of the room is a closet.";
    return BSN(longstr);
}

string
exa_desk()
{
    string deskdesc = 
           "The large brown oak desk looks as if it has been used quite "
         + "a lot. Framing the somewhat notched surface of the desk are "
         + "intricate carvings and patterns. Upon the desk stands an "
         + "inkwell and a featherpen, and there are several sheets of "
         + "paper spread out on the desk. ";
    if (draweropen)
        deskdesc += "There is an open drawer sticking out from the desk.";
    else
        deskdesc += "There is a closed drawer in the desk.";
    return BSN(deskdesc);
}

string
exa_closet()
{
    string  closetdesc =
            "It is a large closet made of solid oak wood. ";
    if (closetopen)
        closetdesc += "The doors of the closet are open, revealing "
          + "several pieces of clothing hanging from a peg inside.";
    else
        closetdesc += "The doors of the closet are closed.";
    return BSN(closetdesc);
}

string
exa_clothes()
{
    string  cldesc;
    if (!closetopen)
        return "You find no clothes.\n";
    cldesc = "There are several clothes hanging in the closet. Your "
      + "attention is automatically drawn to a dark grey cloak which "
      + "looks quite well-used.";
    return BSN(cldesc);
}

string
exa_cloak()
{
    string  clstr =
          "The dark grey cloak is quite well-used, in fact so worn "
          + "out that you wouldn't use it even if you stole it, so you "
          + "decide to let it be. You do however search the pockets, ";

    if (!closetopen)
        return "You find no cloak.\n";
    if (key_taken)
        clstr += "without finding anything though.";
    else
    {
        seteuid(getuid());
        clstr += ", and to your satisfaction you find a rusty little "
          + "key! You take it with you.";
        clone_object("/d/Gondor/elessar/quest/revealspy/deskkey")->move(TP);
        key_taken = 1;
    }
    return BSN(clstr);
}

string
exa_patterns()
{
    int     sl = TP->query_skill(SS_LANGUAGE);

    switch (sl)
    {
        case 0..75:
            return BSN("The patterns are long and intricate, almost as "
              + "if they were forming letters and words. If so, it's a "
              + "language and a form of writing you haven't seen before.");
            break;
        case 76..85:
            return BSN("You recognize the patterns as sentences, written "
              + "with ancient elven letters. The language however is unknown "
              + "to you, but you manage to read the words:")
              + "\tAsh nazg durbatuluk, ash nazg gimbatul,\n"
              + "\tAsh nazg thrakatuluk agh burzum ishi krimpatul.\n"
              + BSN("You don't know what it means, but an eerie feeling "
              + "comes to the room.");
            break;
        case 86..100:
        default:
            return BSN("You recognize the patterns as sentences, written "
              + "with ancient elven letters. You also recognize the "
              + "language, the evil language of Sauron and his servants, "
              + "the Black Speech. The words formed by the carvings are:")
              + "\tAsg nazg durbatuluk, ash nazg gimbatul,\n"
              + "\tAsh nazg thrakatuluk agh burzum ishi krimpatul.\n"
              + "In the Common Speech it means:\n"
              + "\tOne Ring to rule them all, One Ring to find them,\n"
              + "\tOne Ring to bring them all and in the darkness bind them.\n";
            break;
    }
}

string
exa_drawer()
{
    string  drstr =
            "There's a drawer in the large oak desk, ";
    if (!draweropen)
        drstr += "currently closed.";
    else
    {
        drstr += "currently opened. There is ";
        if (!book_taken)
            drstr += "a large black book and ";
        if (!ring_taken)
            drstr += "a gold ring there, and ";
        drstr += "nothing else in the drawer.";
    }
    return BSN(drstr);
}

int
do_open(string str)
{
    if (!str)
    {
        NFN("Open what?");
        return 0;
    }
    if (str == "drawer" || str == "drawer in desk" || str == "desk-drawer" ||
        str == "drawer of desk" || str == "the drawer")
    {
        if (draweropen)
        {
            write("It is already open.\n");
            return 1;
        }
        if (!drawerunlocked)
        {
            write("The drawer is locked.\n");
            say(QCTNAME(TP)+" tries to open the drawer in the desk, but it "
              + "is locked.\n",TP);
            return 1;
        }
        write("You open the drawer.\n");
        say(QCTNAME(TP)+" opens the drawer in the desk.\n",TP);
        draweropen = 1;
        return 1;
    }
    if (str == "closet" || str == "the closet" || str == "doors of closet")
    {
        if (closetopen)
        {
            write("It is already open.\n");
            return 1;
        }
        write("You open the doors of the closet.\n");
        say(QCTNAME(TP)+" opens the doors of the closet.\n",TP);
        closetopen = 1;
        return 1;
    }
    return 0;
}

int
do_get(string str)
{
    object  book,
            ring;

    if (!str)
    {
        NFN("Get what?");
        return 0;
    }
    if (str == "book" || str == "black book" || str == "book from drawer")
    {
        if (book_taken)
        {
            write("There is no book in the drawer.\n");
            return 1;
        }
        seteuid(getuid());
        book = clone_object("/d/Gondor/elessar/quest/revealspy/blackbook");
        if (!(book->move(TP)))
        {
            book->remove_object();
            NF("It's too heavy for you; you are carrying too much!\n");
            return 0;
        }
        book_taken = 1;
        write("You take the black book from the drawer.\n");
        say(QCTNAME(TP)+" takes a black book from the drawer in the desk.\n",TP);
        return 1;
    }
    if (str == "ring" || str == "gold ring" || str == "ring from drawer")
    {
        if (ring_taken)
        {
            write("There's no ring here.\n");
            return 1;
        }
        seteuid(getuid());
        ring = clone_object("/d/Gondor/elessar/obj/goldring");
        if (!(ring->move(TP)))
        {
            ring->remove_object();
            NF("You are carrying too much, and can't carry more!\n");
            return 0;
        }
        ring_taken = 1;
        write("You take the golden ring from the drawer.\n");
        say(QCTNAME(TP)+" takes a golden ring from the drawer in the desk.\n",TP);
        return 1;
    }
    if ((str == "clothes" || str == "clothing" || str == "cloak") && closetopen)
    {
        write("Nah, you have no use for these clothes.\n");
        return 1;
    }
    return 0;
}

int
unlock_drawer(string str)
{
  string s1;
  if (!str) {
    write("Unlock what?\n");
    return 1;
    }
  if (sscanf(str,"drawer %s",s1)!=1) {
    write("Unlock drawer with what?\n");
    return 1;
    }
  if (!present("Key_To_PeDesk",TP)) {
    write("You haven't got the right key!\n");
    return 1;
    }
  write("You unlock the drawer in the desk with the rusty little key.\n");
  say(QCTNAME(TP)+" unlocks the drawer in the desk with a little key.\n",TP);
  drawerunlocked = 1;
  return 1;
}

int
do_close(string str)
{
  if (!str) { write("Close what?\n");  return 1;  }
  if (str == "closet" || str == "doors of closet" || str == "closet doors") {
    if (!closetopen) {  write("The closet is already closed!\n"); return 1; }
    write("You close the closet.\n");
    say(QCTNAME(TP)+" closes the closet.\n",TP);
    closetopen = 0;
    return 1;
    }
  if (str == "drawer" || str == "desk-drawer" || str == "drawer in desk") {
    if (!draweropen) {  write("The drawer is already closed!\n"); return 1; }
    write("You close the drawer.\n");
    say(QCTNAME(TP)+" closes the drawer in the desk.\n",TP);
    draweropen = 0;
    return 1;
    }
  return 0;
}
