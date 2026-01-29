inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

// Global variables
static string  extra_long = "";
static object *rats;

void
set_extra_long(string s)
{
    if (strlen(s))
        extra_long = " "+s;
}

string  query_extra_long() { return extra_long; }

void
create_sewer()
{
}

nomask void
create_room()
{
    set_name("sewer");
    set_short("Sewers under Minas Tirith");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -random(2));

    add_item(({"wall","walls"}), BSN( ONE_OF_LIST( ({
        "The walls are made from the rock under Minas Tirith; looking at "
      + "the walls you can make out the grains of salt that glitter as "
      + "the light reflects off them.",
        "The sewers were hewn into the living rock of the hill onto "
      + "which the city is built. The walls still show the traces of "
      + "this mighty work, and their straight course is testimony "
      + "to the expert craftmanship of the builders of sewers and city.",
        "The walls are neither smooth nor polished, but between the "
      + "bends in the tunnel they run completely straight.",
        }) ) ));

    add_item("air", BSN("The air down here is stale but in a few places "
      + "the air is fresh; you may have to smell the air to find out."));

    create_sewer();

    set_long("@@long_desc");
}

string
long_desc()
{
    return BSN(
        "You are in the sewers under Minas Tirith. It is pitch black in "
      + "these damp passages, the walls are made of white stone and the "
      + "air down here is rather stale."
      + extra_long);
}

void
init()
{
    ::init();
    add_action("do_time_in_tunnel", "time");
}

int
do_time_in_tunnel(string str)
{
    write(BSN("You guess it is " + CLOCK->query_time_of_day()
      +" now, but since you are in this sewer, " +
      "you cannot estimate the time more precisely."));
    return 1;
}

varargs void
floor(string dir)
{
    string desc;

    desc = ONE_OF_LIST( ({
        "The ground is damp from the drainage of water that flows "
      + "through the sewers when it rains and it is covered with silt "
      + "and mud. Some spots are damper then others.",
        "Silt and mud cover the ground of the tunnel, left over from "
      + "the water torrents that must fill these sewers in times of "
      + "heavy rain. In some places there are still a few puddles "
      + "of dirty water.",
        "The floor is slightly bent to be at deepest in the middle "
      + "of the tunnel. It was constructed more for easy flow of water "
      + "than for easy walking.",
        "The floor is bending upwards close to the walls, so that "
      + "water flowing down in the sewers is channelled into the "
      + "middle of the tunnel.",
        }) );

    if (stringp(dir))
        desc += (" The floor shows a slight slope towards the "
          + dir + ".");

    add_item(({"ground", "floor", }), BSN(desc) );
    add_item(({"silt", "mud", }), BSN(
        "The silt and mud have been carried here from the streets "
      + "of Minas Tirith by the water that is running through the "
      + "sewers after rainfalls."));
}

varargs void
passage(string dir)
{
    string  desc;

    desc = ONE_OF_LIST( ({
        "The passage is dark and very uninviting; you can hear things "
      + "scurrying through the dark.",
        "The tunnel is very narrow and filled with stale air.",
        "The sewer is dark and narrow, hardly wide enough for a single "
      + "person to walk here.",
        }) );

    if (stringp(dir))
        desc += (" The floor is slightly sloping down to the "+dir+".");

    add_item(({"passage", "tunnel", "sewer", }), BSN(desc) );
}

int
grid_block()
{
    write(BSN("You cannot go there, the metal grid blocks the passage "
      + "into that direction."));
    if (TP->query_wiz_level() || TP->query_npc())
        return 0;
    return 1;
}

void
grid(string dir)
{
    string  desc;

    if (!strlen(dir))
        return;

    desc = "The massive metal grid blocks the passage to the "
      + dir + ". It is made of thick vertical iron rods that "
      + "reach from the floor to the roof of the tunnel. At "
      + "both ends the rods are set securely into deep holes "
      + "in the rock holding the rods.";

    add_item(({"grid", "metal grid", "iron grid", }), BSN(desc) );
    add_item(({"rods", "holes", "rod", "hole"}), BSN(
      "The rods are thick and made of iron, and they appear very " +
      "securely embedded in deep holes in the rock."));
    add_item("rock", BSN("The rock holding the thick iron rods " +
      "appears very solid."));
}

void
recess(string dir)
{
    string  desc;

    desc = ONE_OF_LIST( ({
        "There is a narrow recess in the "+dir+" wall of the "
      + "tunnel. Its purpose is probably to receive a drain "
      + "coming down from the surface.",
        "A dark and narrow recess interrupts the wall to the "
      + dir + ". It is possible to enter it, but the shadows "
      + "are not inviting.",
        "The recess in the "+dir+" wall is a short narrow "
      + "deadend, probably taking in the water coming down from "
      + "a surface in a drain.",
        }) );
    add_item(({"recess", "niche", dir+" wall", "dead end", "deadend", }),
        BSN(desc));
}

varargs void
roof(string extra = "")
{
    string  desc,
           *items = ({ "roof", "ceiling", });

    desc = ONE_OF_LIST( ({
       "The roof of the tunnel is made from the same white rocks as "
     + "the walls. It vaults gently about eight feet above the ground.",
       "The roof is about eight feet high and constructed as a vault "
     + "resting on the walls to both sides of the tunnel.",
       "The slightly vaulted roof was made of stones hewn from the "
     + "same white rock as the walls and is about eight feet high.",
            }) );

    switch (extra)
    {
        case "drain":
            items += ({ "drain", });
            desc += " The drain in the roof serves to let water flow "
              + "down from the surface into the sewers.";
            break;
        case "":
        default:
            break;
    }

    add_item(items, BSN(desc));
}

void
make_rat()
{
    int     i,
            s = sizeof(rats);

    for (i = 0; i < s; i++)
        if (!objectp(rats[i]))
            break;

    if (i == s)
        return;

    rats[i] = clone_object(NPC_DIR + "rat");
    rats[i]->set_stats(({ 10, 20, 15, 2, 2, 40, }));
    rats[i]->set_long(BSN("A big fat filthy rat with sharp teeth, "
      + "mean red eyes, and a long tail.\n"));
    rats[i]->set_adj("big");

    rats[i]->set_restrain_path(MINAS_DIR + "sewer");
    rats[i]->set_random_move(10);
    rats[i]->set_whimpy(60);
    rats[i]->set_aggressive(1);
    rats[i]->move_living("down", TO);

#define A_BITE  0
    //                        wep type  HIT PEN  DAM type  %use    desc
    rats[i]->set_attack_unarmed(A_BITE,  20, 12, W_IMPALE,   80, "jaws");

    set_alarm(3.0, 0.0, "make_rat");
}
 
