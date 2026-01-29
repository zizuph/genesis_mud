/*
   Wayreth.

   redstudy.c
   ----------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 97/03/03
   By ...........: Kentari

*/

#include "/d/Krynn/wayreth/local.h"
#include "../guild/local.h"
#include <macros.h>
inherit TOWERROOM;

#undef ADMIN
#define ADMIN  "/d/Krynn/wayreth/guild/admin/admin.c"
#define RED    ADMIN->query_conclave_head("red")

#define MAILREADER_ID   "_reader_"

void
create_tower_room()
{
    set_short("This is the study of the Master of the Red Robes");
    set_long("You have entered the study of "+capitalize(RED)+", " +
             "the current Master of the Red Robes. The room has a " +
             "pleasant temperature which apparently originates from " +
             "the ruby-red glowing orb on the wooden pedestal in the " +
             "corner of the room. Burning candles complement the " +
             "illumination provided by the orb, and create a strange " +
             "but not unpleasant atmosphere. A large redwood desk and " +
             "comfortable black leather armchair catch your eye, as " +
             "does the matching cabinet standing against the wall. " +
             "A comfortable couch is positioned close to a bulging redwood " +
             "bookshelf. You notice some paintings on the walls.\n");

    AI(({"glowing orb","ruby-red orb","ruby-red glowing orb","orb"}), 
        "The orb emits a constant glow and provides a pleasant warmth.\n");

    AI(({"pedestal","wooden pedestal"}), "The pedestal is an excellent "+
        "piece of craftmanship, made of heavily ornamented wood. It "+
        "supports the glowing orb.\n");

    AI(({"wood","ornamented wood","heavily ornamented wood"}), "The heavily " +
        "ornamented wood of the pedestal is most likely red maple.\n");

    AI(({"redwood desk", "desk"}), "Piles of scrolls cover the desk. You " +
        "wonder how " +capitalize(RED)+ " keeps track of things. You might " +
        "be able to peek at the scrolls.\n");

    AI(({"comfortable chair", "comfortable armchair", "black chair",
        "black armchair", "leather chair", "leather armchair", "chair",
        "armchair"}), "An enormous black leather chair is positioned " +
        "behind the large desk.\n");

    AI(({"candles","burning candles"}),"The burning candles add a " +
        "demure glow to the room.\n");

    AI(({"demure glow","glow"}),"It is caused by the candles and the orb.\n");

    AI("runes","The runes on the scroll waver before your eyes.\n");

    AI("cabinet", "The low cabinet is a true masterpiece of " +
        "craftmanship combining simplicity with elegance. Positioned on " +
        "its top are two crystal carafes and some glasses, and a delicate " +
        "balance made of red copper.\n");

    AI(({"copper balance", "delicate balance", "balance"}), "The " +
        "balance looks delicate, yet somehow sturdy. One tray contains " +
        "black pepper, the other white salt, measured out perfectly " +
        "equal, so that the balance is suspended equally between the two " +
        "extremes of its possibilities, forming a level plane.\n");

    AI(({"black pepper","pepper"}),"The pepper is magically held in place.\n");
    ACI(({"pepper","black pepper"}),"get","Something prevents you from " +
        "doing that.\n");

    AI(({"salt","white salt"}),"The salt is magically held in place.\n");
    ACI(({"salt","white salt"}),"get","Something prevents you from " +
        "doing that.\n");

    AI("carafe", "The crystal carafes are partly filled, one with a " +
        "merlot colored liquid, the other one filled with a milky " +
        "white substance.\n");

    AI(({"glass", "glasses"}), "Six crystal glasses match the carafes.\n");

    AI("bookshelf", "The shelf is filled to the maximum of its capacity " +
        "with heavy dusty tomes and scrolls.\n");

    ACI("orb", "touch", "You move towards the orb but something prevents " +                "you from touching it.\n");

    AI(({"comfortable couch","couch"}),"The couch looks comfortable " +
        "indeed.\n");
    ACI(({"comfortable couch","couch"}),"sit","Sitting on the couch " +
        "would be a bad idea, after all. A closer inspection reveals " +
        "that it is an interdimensional travel device, which needs to " +
        "be attuned to the user.\n");

    AI("paintings","Two paintings stand out.\n");

    AI("first painting","This painting is of a furry-eared human, " +
        "wearing Red Robes. Most likely, the painting is of the first " +
        "Master of the Red Robes.\n");

    AI("second painting","This painting is of a human, average in all " +
        "respects, wearing tattered Red Robes. Seeing this painting makes " +
        "you feel a sense of loss, as if you were looking at the end of " +
        "the Order of the Red Robes.\n");

    add_exit(WTOWER + "conclave", "east", 0);
}

public void
init()
{
    object mr;
    string *conclave;

    if (TP->query_real_name() == RED)
    {
        mr = clone_object("/secure/mail_reader");

        conclave = ADMIN->query_conclave_member();
        if (sizeof(conclave))
            mr->set_alias("conclave", conclave);

        if (sizeof(GUILDMASTERS))
            mr->set_alias("guildmaster", GUILDMASTERS);

        mr->move(TP, 1);     
    }

    add_action("do_peek", "peek");
    ::init();
}

public int do_peek(string str)
{
    if((str=="scrolls")||(str=="at scrolls")||(str=="at scrolls on table"))
    {
        say(QCTNAME(TP) + " peeks at the scrolls on the table.\n");
        write("You peek at the scrolls on the table. Runes waver before " +
            "your eyes. Obviously, the scrolls are not fully translated " +
            "yet.\n");
        return 1;
    }
    NF("Peek at what?\n");
    return 0;
}

public int
query_start_room() { return 1; }

static int
query_prevent_snoop() { return 1; }

void
leave_inv(object ob, object to)
{
    object reader;

    ::leave_inv(ob, to);

    reader = present(MAILREADER_ID, ob);

    if (reader)
        reader->remove_object();
}
   