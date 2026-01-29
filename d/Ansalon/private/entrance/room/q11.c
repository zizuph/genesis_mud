#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define ODIR      "/d/Ansalon/private/entrance/obj/"
#define NDIR      "/d/Ansalon/private/entrance/npc/"
#define RDIR      "/d/Ansalon/private/entrance/room/"

object door, big_dragon;
int locket_here = 1;

void
reset_kendermore_room()
{
    if (!big_dragon)
    {
        big_dragon = clone_object(NDIR + "dragon");
        big_dragon->move(TO);
    }
    locket_here = 1;
}

void
create_kendermore_room()
{
    set_short("An extremely large chamber");
    set_long("You've entered an extremely large chamber. @@dragon@@ " + 
        "Two orbs float in mid-air, giving off a soft glow of light. " + 
        "despite the glow of light, shadows dance in the corners. A " + 
        "large tapestry covers the west wall, and a small table stands " + 
        "by one of the orbs.\n");
    add_item(({"table", "small table", "locket", "tarnished locket",
        "broken locket", "silver locket"}), "@@table_locket@@");
    add_item(({"mark", "small mark"}), "@@table_mark@@");
    add_item(({"shadows", "corner", "shadow", "corners"}),
        "The shadows here are very faint, but they dance and play as " + 
        "if alive.\n");
    add_item("orbs", "They seem suspended by magic, as nothing is touching " + 
        "them but air.\n");
    add_item(({"west wall", "back wall", "tapestry", "large tapestry"}),
        "This tapestry covers the entire west wall. It depicts a flight " +
        "of dragons in all their majesty. Twenty metallic dragons soar " + 
        "through the air, a rider on each back. It looks like " +
        "there's enough space for someone to move behind the tapestry.\n");
    add_item(({"dragons", "metallic dragons", "twenty metallic dragons",
        "twenty dragons", "flight"}), "They range in colour from gold, " + 
        "silver, bronze, copper and brass.\n");
    add_item(({"rider", "riders"}), "The riders on the dragons' backs " + 
        "have looks of determination on their faces.\n");
    add_item(({"stone", "rough stone", 
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this chamber.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls"}), "They are " + 
        "made of limestone. " +
        "A large tapestry covers the west wall.\n");
    add_item(({"floor", "floors"}), "They are made of limestone.\n"); 
    add_item("ceiling", "It is made of roughly cut limestone.\n");        
    add_cmd_item("behind tapestry", "move", "@@move_tapestry");

    set_tell_time(300);
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The orbs flicker, sending the shadows dancing.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    door = clone_object(ODIR + "qdoor5");
    door->move(TO);
    reset_kendermore_room();
}

int
query_locket()
{
    return locket_here;
}

void
change_locket()
{
    locket_here = 0;
}

string
table_mark()
{
    if (locket_here)
    {
        return "There is a small mark under the locket made by years of " + 
            "sitting in the same place.\n";
    }
    return "There is a small mark in the shape of a locket on the table, " + 
        "but no locket.\n";
}

string
table_locket()
{
    if (locket_here)
    {
        return "There is a tarnished broken silver locket sitting on the " + 
            "top of the table.\n";
    }
    return "The table is bare, but a small mark indicates that " + 
        "something used to lie there.\n";
}

void
init()
{
    ::init();
    add_action("do_borrow", "borrow");
}

int
do_borrow(string str)
{
    object sil_locket;
    setuid();
    seteuid(getuid());
    sil_locket = clone_object(ODIR + "locket_left");
    if (locket_here)
    {
        if ((str == "locket") || (str == "tarnished locket") ||
          (str == "silver locket") || (str == "tarnished silver locket") ||
          (str == "broken locket") || (str == "locket from table") ||
          (str == "locket from small table"))
        {
            sil_locket->move(TP);
            write("You absentmindedly pick up a tarnished broken silver " + 
                "locket from the table. People should really stop leaving " + 
                "things lying around. Maybe you should keep this safe so " + 
                "it doesn't get stolen.\n");
            locket_here = 0;
            return 1;
        }
    }
    NF("Borrow what? Borrow what from where?\n");
    return 0;
}

string
move_tapestry()
{
    TP->move_living("behind the tapestry", RDIR + "passage2", 0, 1);
    return ("You move behind the tapestry and find yourself in a " +
        "secret passage, how exciting!\n");
}

string
dragon()
{
    if (big_dragon)
        return "The reason for the room's size is clearly apparent -- " + 
            "a young bronze dragon resides here.";
    if (!big_dragon)
        return "It looks like a dragon's room, from the size of the place."; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
        start_room_tells();
}

