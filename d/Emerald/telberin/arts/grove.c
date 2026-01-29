/*
 *  /d/Emerald/telberin/arts/grove.c
 *
 *  This is the training area offering skills for those
 *  who wish to improve their abilities the Arts Quarter
 *  of Telberin.
 *
 *  Copyright (c) April 2003 by Cooper Sherry (Gorboth)
 *
 *    Copied from the Minas Morgul Training Hall in
 *    Gondor which was created by Olorin
 */
#pragma strict_types

inherit "/d/Emerald/telberin/telberin_room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

/* 1 = closed,   0 = open.  */
#define CLOSED          0       
#define HIS(x)	        (x)->query_possessive()
#define HIM(x)	        (x)->query_objective()

/* 
 *      Prototypes 
 */
private void set_up_skills();

/*
 *      Global variables:
 */
static int     Closed = CLOSED;
static object  Trainer;


/*
 * Function name:        create_telberin_room
 * Description  :        set up the room
 */
public void
create_telberin_room()
{
    set_short("in a secluded grove of trees before the lake");
    set_em_long("A thick grove of birch trees gather together here to"
      + " form a shimmering backdrop of green against the blue waters"
      + " of the lake. This area is sometimes used by thespians from"
      + " the Actors Guild of Telberin who are interested in helping"
      + " those who wish to <learn> or <improve> skills from their"
      + " craft. A cobblestone path leads southwest between the wings"
      + " of a complex of buildings.\n");

    add_item( ({ "building", "buildings", "complex", "guild",
                 "minstrel guild", "complex of buildings" }),
        "The Minstrel Guild lies to the southwest. A path runs"
      + " between a few of its buildings heading toward the"
      + " plaza at the center of the Arts Quarter.\n");
    add_item( ({ "cobblestone", "cobblestones", "path",
                 "cobblestone path" }),
        "A path leads to the southwest, passing between buildings"
      + " as it makes its way back to Cantors Plaza.\n");
    add_item( ({ "grove", "thick grove", "tree", "trees",
                 "birch tree", "birch trees", "birch", "birches",
                 "grove of trees", "thick grove of trees",
                 "grove of birch trees", "thick grove of birch trees" }),
        "Birch trees have clustered together here to form a dramatic"
      + " backdrop against the shining waters of the lake. It is no"
      + " wonder that thespians select this as a dramatic natural"
      + " stage for their art.\n");
    add_item( ({ "lake", "water", "waters", "waters of the lake",
                 "lake telberin" }),
        "The lake is visible between the birch trees, its waters"
      + " shining brightly.\n");
    add_item( ({ "sky", "up" }),
        "The sky is a vibrant blue framed by the birch trees on one"
      + " side and the buildings on the other.\n");
    add_item( ({ "ground", "down", "floor" }),
        "A path lies on the ground here, leading to the southwest.\n");

    add_exit("/d/Emerald/telberin/arts/cantors_plaza", "southwest");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    create_guild_support();
    create_skill_raise();
    set_up_skills();

    reset_room();
}

private void
make_trainer()
{
    if (objectp(Trainer))
        return;

    Trainer = clone_object("/d/Emerald/telberin/arts/npc/trainer");
    Trainer->add_name("_train_elf");
    Trainer->move_living("down", this_object());
}

public void
reset_room()
{
    make_trainer();
}

public void
enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !interactive(ob) || !Closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nWARNING!\nYou shouldn't be here. "+
              "I'm doing some work on the guild.\n");
    else 
    {
        write("The guild is closed. Come back later.\n");
        ob->move_living("north",
            "/d/Emerald/telberin/arts/cantors_plaza");
    }
}

public int
try_skills(string str)
{
    object elf;

    this_player()->reveal_me(1);
    if (!objectp(elf = present("_train_elf", this_object())))
    {
        write("There is no one present who could train you.\n");
        return 1;
    }
    if (!CAN_SEE(elf, this_player()))
    {
        write("The " + elf->query_nonmet_name() + " cannot see you!\n");
        return 1;
    }
    return 0;
}

public void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();
    add_action(try_skills, "learn");
    add_action(try_skills, "improve");
}

public string 
close_guild()
{
    Closed = !Closed;

    if (Closed)
    {
        return "  **The guild is now closed**";
    }

    return "  **The guild is now open**";
}

public int    query_closed() { return Closed; }

private void 
set_up_skills()
{
    string me, ot;

    me = "perform acrobatic maneuvers";  ot = me;
    sk_add_train(SS_ACROBAT,      ({ me, ot }),  0, 0, 20 );
    me = "understand and speak other languages"; ot = me;
    sk_add_train(SS_LANGUAGE,  ({ me, ot }),  0, 0, 30 );
}

string
wizinfo() 
{
  return (
    "If there should be due cause to close down the guild, do so by\n"+
    "typing:  Call here close_guild\n"+
    "This will temporarily prevent mortals from entering. After a\n"+
    "reboot, the guild will be open by default. Please send me some\n"+
    "mail if there is anything that needs to be fixed.\n\n   Gorboth.\n");
}


