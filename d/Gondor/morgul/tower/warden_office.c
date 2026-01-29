/*
 * /d/Gondor/morgul/tower/warden_office.c
 * The room for the Warden of the Tower
 *
 * Olorin, 12-jan-1996
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define PLAYER_I_WRITING	"_player_i_writing"
#define LIVE_I_MORGUL_WARDEN	"_live_i_morgul_warden"
#define WARDEN_ROOM             "/d/Gondor/morgul/tower/warden_room"

static  object  busy;

public void
create_morgul_tower_room()
{
    set_level(1);
    set_room_type("dark, gloomy chamber");
    set_extra_long("this is the private office of the Warden of the Tower. "
      + "He only admits members of the Society into this office. "
      + "In the middle of the room, there is a wooden desk. Behind it on "
      + "the wall are shelves and racks, filled with thick and dusty "
      + "books, weapons, armours, and instruments of torture.");

    add_walls();
    add_roof();
    add_floor();

    add_item(({"shelves", "shelf", "books", }), BSN(
        "The shelves are filled with many books of different types, some "
      + "thick, some thin. Most of them look like they are used to keep "
      + "some kind of records, and it seems unlikely that any of them "
      + "contain belles-lettres or fiction."));

    add_item(({"desk", "wooden desk", }), BSN(
        "The warden probably uses this desk for the paper work he has "
      + "to do. On top of the desk, there is one pile of papers filled "
      + "with reports, and another one of empty sheets of paper. "
      + "Between the two piles are some pens and an inkpot. You could "
      + "sit down at this desk and write something. The warden will "
      + "bring what you wrote to the attention of the nazgul, but he "
      + "will not reveal your name to them."));
    add_item(({"paper", "sheets", "pile of empty sheets", "empty sheets", }),
        BSN("Just a pile of empty sheets of paper. You could write something "
      + "on them, if you so desire."));
    add_item(({"papers", "reports", "pile of reports", }), BSN(
        "You should better leave these reports alone. The warden will "
      + "read them and bring those which he deems important enough to "
      + "the attention of the nazgul."));
    add_item(({"pen", "pens", "ink", "inkpot", }), BSN("Standard "
      + "writing utensils, probably used by the warden for his paper "
      + "work. The pens are cut from vulture quills, and the ink "
      + "has a deep red colour that makes you wonder about its origin."));

    add_item(({"racks", "instruments", "torture instruments",
        "instruments of torture", }), BSN(
        "There are racks filled with weapons and armours, and others "
      + "filled with instruments of torture, like thumb-screws, iron rods, "
      + "thin needles, and garottes. All these instruments are in "
      + "excellent shape and seem well used."));
    add_item(({"thumb-screws", "thumb-screw", }), BSN(
        "A metal cylinder to receive the thumbs of people who are too "
      + "curious. A few turns of the screws will make you very talkative, "
      + "besides turning your thumbs into a mixture of bone meal and "
      + "tartare."));
    add_item(({"rod", "iron rod", "rods", "iron rods", }), BSN(
        "Extremely simple, but also extremely useful. It is hardly imaginable "
      + "what a simple iron rod can do in the hand of an experienced craftsman. "
      + "One usually starts with breaking toes and fingers, continues with "
      + "broken shins, arms, and ribs, and ends by introducing the red hot "
      + "rod into diverse body openings."));
    add_item(({"needles", "thin needles", "needle", "thin needle", }), BSN(
        "Thin, but durable needles made from steel. Poking and tickling "
      + "with these needles is very effective in any kind of argument. "
      + "The smaller needles are good to slip them under finger nails, "
      + "the larger needles can slip almost as easliy through arms and "
      + "legs, or can be used to cause softly sucking chest wounds by "
      + "poking around in the lungs - an extremely convincing argument!"));
    add_item(({"garottes", "garotte", }), BSN(
        "A garotte is nothing but a valve made from an iron band. The only "
      + "truly notable feature is that it is applied to throats. Hasty "
      + "people have been known to use it in executions, by strangling "
      + "their victims to death. The advanced torturer will use a garotte "
      + "to strangle, as lack of breath helps most people to see the "
      + "facts of life a lot clearer, but he will not strangle to death, "
      + "at least not prematurely."));

    add_exit(TOWER_DIR  + "warden_room", "south",  "@@check_exit@@", 1);

    add_prop(ROOM_I_LIGHT, 1);

    clone_object(MORGUL_DIR + "obj/rack")->move(TO);
}

public void
done_writing(string str)
{
    busy = 0;
    TP->remove_prop(PLAYER_I_WRITING);

    if (!strlen(str))
    {
        write("You tear the paper to shreds and throw it away.\n");
        return;
    }

    write("You finish writing and add your report to the pile of reports "
     + "lying on the desk.\n");
    say(QCTNAME(TP) + " finishes writing and puts the new report into "
     + "the pile of reports lying on the desk.\n");
    
    write_file(MORGUL_COMPLAINTS, str);
}

public int
do_write(string str)
{
    string  desc,
            header;

    if (objectp(busy) && present(busy))
    {
        desc = QCTNAME(busy);
        NF(CAP(desc) + " is using the desk at the moment.\n");
        return 0;
    }

    write("You sit down at the desk, take a sheet of paper and start writing.\n");
    say(QCTNAME(TP)+" sits down at the desk and starts writing.\n");
    TP->add_prop(PLAYER_I_WRITING, 1);
    busy = TP;

    header = "\nReport by a member of the Society, "+ctime(time())+".\n\n";
    if (strlen(str))
        header += str + "\n";

    clone_object(EDITOR_OBJECT)->edit("done_writing", header, (strlen(str) ? 5 : 4));

    return 1;
}

public void
init()
{
    ::init();
    add_action(do_write, "write");
}

public int
check_exit()
{
    if (TP->query_prop(PLAYER_I_WRITING))
    {
        write("You are still writing. You cannot leave now.\n");
        return 1;
    }
    return 0;
}

public void
kick_out(object tp, object warden)
{
    if (!CAN_SEE_IN_ROOM(warden) || !CAN_SEE(warden, tp))
        return;

    if (IS_MORGUL_MAGE(tp))
        return;

    warden->command("growl " + tp->query_real_name());
    if (tp->query_prop(LIVE_I_MORGUL_WARDEN))
    {
        warden->do_attack(tp);
    }
    else
    {
        warden->command("mhiss You have no business here! Get out!");
        warden->command("mglare " + tp->query_real_name());
    }

    write("The "+warden->query_nonmet_name()+" kicks you out of his office.\n");
    say("The " + warden->query_nonmet_name() + " kicks " + QCTNAME(tp)
      + " out of this office.\n", tp);

    tp->add_prop(LIVE_I_MORGUL_WARDEN, tp->query_prop(LIVE_I_MORGUL_WARDEN) + 1);
    tp->command("$south");
}



/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob:   The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    object  warden;

    ::enter_inv(ob, from);

    if (!objectp(from) || !objectp(ob) || !living(ob))
        return;

    warden = WARDEN_ROOM->query_warden();

    if (!objectp(warden) || !present(warden, TO))
        return;

    set_alarm(0.5, 0.0, &kick_out(ob, warden));
}

