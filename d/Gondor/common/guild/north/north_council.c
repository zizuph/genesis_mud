#pragma save_binary

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/post2";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <std.h>
#include <files.h>
#include <mail.h>
#include <const.h>
#include <macros.h>

#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define SETTLE_NAME   "long settle"
#define SETTLE_CAPACITY   8
#define MORE_OBJ   "/std/board/board_more"
#define STATUS_LOG   (LOG_DIR + "ron_status")

#define RON_DAEMON    "/d/Gondor/common/guild/north/member_master"
//      Prototypes
        int     croom_read(string str);
        string  exa_poster();
        public void     leave_inv(object ob, object dest);
        public string   look_at(string arg);    /* VBFC for room and chairs */
        public int      plump(string arg);
        public string   read_aliases();

static string gWho;
static object gWriting;

void 
create_gondor()
{
    set_short("The Chamber of Officers");
    set_long(BSN(
        "The Chamber of Officers. "+
        "A desk with a chair is placed over by the west wall of this small "+
        "chamber. Above the desk there is a poster on the wall. On the south "+
        "wall a banner hangs above a long settle.")); 

    add_item(({"desk","chair"}),"The furniture is made of oak.\n");
    add_item("banner",BSN(
        "This banner flew on one of Elendil's four original ships. Despite "+
        "that it is somewhat torn at the edges it still looks to be in a "+
        "rather good shape. It was saved from the destruction of Fornost and "+
        "is now safe here."));
    add_chair(SETTLE_NAME,
        "[down] [in] / [on] [the] [long] 'settle'",
        SETTLE_CAPACITY, "on");
 
    add_item( ({ "long settle", "settle" }), &look_at(SETTLE_NAME));
    add_item( ({ "carving", "carvings", "carved back", "back", }),
        BSN("Delicate carvings of vines and flowers twine round "+
            "the back of the settle."));
    add_item( ({ "vine", "flower", "vines", "flowers", }),
        BSN("The vines and flowers are carved in careful detail; "+
            "they almost seem to grow from the wood."));
    add_item( ({ "blond oak", "oak", "wood" }),
        BSN("The settle is made from blond oak, carefully polished "+
            "and beautifully carved."));
    add_item( ({ "colourful cushion", "cushion", "colourful cushions",
        "cushions", }),
        BSN("Cushions of all colours are heaped on the settle."));

    add_item( ({ "poster", "commands" }), exa_poster);
    add_cmd_item(({"poster", "commands"}), "read", exa_poster);
 
    add_item( ({ "plaque", "aliases", }), read_aliases);
    add_cmd_item( ({ "plaque", "aliases", }), "read", 
                read_aliases);
 
    seteuid(getuid());
    clone_object(RANGER_NORTH_DIR+"obj/c_door_out")->move(TO, 1);
    clone_object(RANGER_NORTH_DIR + "boards/private_board")->move(TO, 1);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    create_post();
}

string
read_aliases()
{
    return "Here you may read and write your mail as in any post office.\n"+
        "Check the mailreader for instructions.\n" +
        "The following aliases can be used here:\n" +
        "\tchieftain   - the chieftain of the Rangers,\n" +
        "\tofficers    - the officers of the Rangers of the North\n\n" +
        "To send anonymous mail signed with your Ranger nickname, use 'amail'.\n";
}

string 
exa_poster()
{
    cat(RANGER_NORTH_HELP_DIR + "officers_room_poster.txt");
    return "";
}
 
void test_allowed(object obj, object from)
{
    int     wizrank;
    string  name;
 
    if (!(wizrank = SECURITY->query_wiz_rank(name = obj->query_real_name())))
        if (RON_DAEMON->is_officer(CAP(name)))
            return;
    if (wizrank >= WIZ_ARCH)
        return;
    if (SECURITY->query_wiz_dom(name) == "Gondor")
        return;
    log_file("ranger_security",
        (interactive(obj) ? CAP(name) :
                            CAP(name)+" "+file_name(obj))+
        " tried to enter the Rangers of the North" +
        " council room on "+ctime(time())+"\n");
    tell_object(obj,"You are not allowed to enter this room!\n");
    obj->move(from);
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob) && from)
        test_allowed(ob, from);
}

/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from chair/sofa occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object to)
{
    post_leave_inv(ob, to);
 
    ::leave_inv(ob, to);
    leave_inv_room_chairs(ob, to);

    if (ob == gWriting)
    {
        if (present("_editor_", ob))
            present("_editor_", ob)->remove_object();
        gWriting = 0;
        gWho = "";
    }
}

/*
 * Function name:       look_at
 * Description  :       VBFC to describe room/settle + occupants
 * Arguments    :       string arg -- what's being looked at
 *                                    null str -> it's the room
 * Returns      :       string -- the description
 */
public string
look_at(string arg)
{
    if (arg == SETTLE_NAME)
    {
        return BSN(
            "The settle has a handsomely carved back and colourful "
          + "cushions. It is long enough to seat several people "
          + "very comfortably.")
          + sitting_on_chair(SETTLE_NAME, this_player(), 0);
    }
    return "";  /* "cannot happen" */
} /* look_at */

/*
 * Function name:       plump
 * Description  :       let 'em plump the cushions
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
plump(string arg)
{
    string      vb = QVB;
    if (strlen(arg) &&
        parse_command(LOW(arg), ({}),
            "[up] [the] [settle] 'cushion' / 'cushions' "+
            "[on] [the] [long] [settle]"))
    {
        WRITE("You "+vb+" the cushions on the settle.");
        SAY(" "+vb+"s the cushions on the settle.");
        return 1;
    }
    NF0(CAP(vb)+" what?\n");
} /* plump */

int
croom_read(string str)
{
    if (!str)
    {
        notify_fail("Read what?\n");
        return 0;
    }
    if (str == "status")
    {
        clone_object(MORE_OBJ)->more(STATUS_LOG, 2);
        return 1;
    }
}

int
send_anon_mail(string txt)
{
    if (!strlen(txt))
    {
        NFN("Message aborted.");
        return 0;
    }
    MAIL_READER->create_mail("Greetings", TP->query_ranger_name(),
      gWho, "", txt);
    MAIL_READER->create_mail("Cc to self: " + CAP(gWho), TP->query_ranger_name(),
      TP->query_real_name(), "", txt);
    gWho = "";
    return 1;
}

int
mail_anon(string str)
{
    if (objectp(gWriting) && gWriting != TP)
    {
        notify_fail("Someone is already writing a letter. You will have to wait.\n");
        return 0;
    }
    if (!strlen(str))
    {
        notify_fail("Who do you want to write anonymously to?\n");
        return 0;
    }
    if (!SECURITY->finger_player(lower_case(str)))
    {
        notify_fail("You have a feeling writing to that person will be "
          + "a futile attempt.\n");
        return 0;
    }
    gWho = LOW(str);
    gWriting = TP;
    clone_object(EDITOR_OBJECT)->edit("send_anon_mail");
    return 1;
}

void
init()
{
    ::init();
    post_init();
    add_action("mail_anon", "amail");
}

