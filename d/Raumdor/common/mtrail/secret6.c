#include "defs.h"
inherit SECRET_ROOM;
/* SARR */

int    book;
object pen;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("Inside an hidden lair");
    set_long(
      "You now stand inside a cozy, but bleak looking cave. A bookshelf with " +
      "many black-bined books lines the north wall, and a large, black oak " +
      "table sits againts the east wall. A small bed is stacked against the " +
      "south wall, with a large chest placed at the foot. The room reeks of " +
      "stench and decay. There is a few burning torches hanging on the " +
      "walls.\n");
    add_item("table", "@@table@@");
    add_item(({"red book", "book", "strange red book"}), "@@rbook@@");
    add_cmd_item(
      ({"red book", "book", "strange red book"}), "get", "@@do_get@@");
    add_item(({"bed", "cot"}),
      "It is small, and covered with a rough wool blanket.\n");
    add_item("bookshelf",
      "They contain many black-bined books. On the top of the shelves are " +
      "human skulls.\n");
    add_item(({"books", "black-bined books"}),
      "They are about a dozen or so, and they are neatly stacked on the " +
      "shelf.\n");
    clone_object(MTRAIL_DIR + "pen_chest")->move(TO);
    add_exit(MTRAIL_DIR + "secret5", "west", 0);
    reset_room();
}

string
rbook()
{
    if (book)
    {
        return "It is a book that looks like it might be important. Perhaps " +
               "you should get it for closer examination.\n";
    }
    else
    {
        return "You find no book.\n";
    }
}

string
table()
{
    if (book)
    {
        return "On the large table, you see many vials and beakers. They " +
               "contain strange and grotesque items and components. A " +
               "strange red book lies on the table that looks very " +
               "interesting.\n";
    }
    else
    {
        return "On the large table, you see many vials and beakers. They " +
               "contain strange and grotesque items and components.\n";
    }
}

string
do_get(string str)
{
    if (book)
    {
        if (present(pen, TO))
        {
            TP->catch_msg(QCTNAME(pen) + " stops you from touching it.\n");
            return "";
        }
        clone_object(MTRAIL_DIR + "pen_book")->move(TP);
        write("You get the book off the table.\n");
        say(QCTNAME(TP) + " takes a book from the table.\n");
        book = 0;
        return "";
    }
    return "You find no book.\n";
}

void
reset_room()
{
    book = 1;
    if (!pen)
    {
        pen = clone_object(COMMON_NPC_DIR + "penthalus");
        pen->move_living("xxx", TO);
    }
}
