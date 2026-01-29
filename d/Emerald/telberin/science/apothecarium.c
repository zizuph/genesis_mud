/*
 *  /d/Emerald/telberin/science/apothecarium.c
 *
 *  This is the training area offering skills for those
 *  who wish to improve their abilities the Science Quarter
 *  of Telberin.
 *
 *  Copyright (c) June 2003 by Cooper Sherry (Gorboth)
 *
 *    Copied from the Minas Morgul Training Hall in
 *    Gondor which was created by Olorin
 */
#pragma strict_types

#include "../defs.h"

inherit TELBERIN_BUILDING;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

/* 1 = closed,   0 = open.  */
#define CLOSED          0       
#define HIS(x)          (x)->query_possessive()
#define HIM(x)          (x)->query_objective()

/* 
 *      Prototypes 
 */
private void      set_up_skills();
public string     exa_pricelist();

/*
 *      Global variables:
 */
static int     Closed = CLOSED;
static object  Trainer;


/*
 * Function name:        create_telberin_building
 * Description  :        set up the room with special
 *                       building functionality
 */
public void
create_telberin_building()
{
    set_short("in a cramped room filled with vials and potions");
    set_em_long("This room is quite cramped, as it has been stuffed"
      + " full of vials, beakers, oil burners, and other such"
      + " scientific materials as are used to mix and heat potions."
      + " A long table at the far end of the room is filled with"
      + " scrolls and books which have been heaped upon one another"
      + " to create a rather large mess. A rack upon the north wall"
      + " is filled with potions of various colors. The Science Guild"
      + " of Telberin has set up this shop as a service to the city."
      + " It is even said that people who wish to study the scientific"
      + " arts may <learn> or <improve> skills if any of their members"
      + " are present to teach them. You also notice a pricelist"
      + " fixed to the wall.\n");

    add_item( ({ "here", "area", "building", "room", "apothecarium",
                 "shop" }),
        long);
    add_item( ({ "vial", "vials", "tube", "tubes", "glass tube",
                 "glass tubes" }),
        "Glass vials and tubes are set up all over the room. Some of"
      + " them contain fluids which are bubbling from the heat of an"
      + " oil burner or two, while others appear to have run derelict,"
      + " and are filled with dried film or dusty residue.\n");
    add_item( ({ "fluid", "fluids", "solution", "solutions" }),
        "The solutions within the vials are unknown to you. Many of them"
      + " are brightly colored, and vigorously boiling.\n");
    add_item( ({ "beaker", "beakers" }),
        "Beakers stand on nearly every flat surface which can hold them."
      + " Some are empty, but most have been filled with liquids of"
      + " various colors.\n");
    add_item( ({ "liquid", "liquids" }),
        "Liquids fill many of the vials which litter the surfaces of this"
      + " room. A few of them seem to be giving off a strong aroma, which"
      + " adds to the rather pungent fumes which Apothecariums are known"
      + " for.\n");
    add_item( ({ "burner", "burners", "oil burner", "oil burners" }),
        "Oil burners have been lit beneath many of the vials causing their"
      + " contents to bubble and froth. The room is noticably warm.\n");
    add_item( ({ "table", "long table", "wood table", "wooden table",
                 "long wooden table" }),
        "A wooden table stands against the eastern wall. Books and scrolls"
      + " are heaped in large piles along its length, apparently ready to"
      + " slide off at any moment.\n");
    add_item( ({ "book", "scroll", "books", "scrolls", "scrolls and books",
                 "books and scrolls", "heaps", "mess", "large mess" }),
        "The books and scrolls appear to be filled with various recipies"
      + " and methods for concocting potions.\n");
    add_cmd_item( ({ "book", "scroll", "books", "scrolls", "recipies",
                     "recipie" }),
                  ({ "read", "exa" }),
        "You can make out a word now and again, but between the sloppy"
      + " handwriting and arcane shorthand, you have no prayer of"
      + " beginning to interperet what is written here.\n");
    add_item( ({ "rack", "potion rack" }),
        "A potion rack has been affixed to the northern wall. It is"
      + " filled with potions of various sizes and colors.\n");
    add_item( ({ "northern wall", "north wall", "north" }),
        "A potion rack has been affixed to the otherwise bare northern"
      + " wall of the room.\n");
    add_item( ({ "potion", "potions" }),
        "The potions within the rack on the northern wall run the gamut"
      + " of shapes, sizes, and colors. It is likely that their creator"
      + " is well learned in the science of alchemy. You could"
      + " perhaps <buy> some if the apothecary is present.\n");
    add_item( ({ "up", "roof", "ceiling", "stain", "stains", 
                 "dark stain", "dark stains" }),
        "Dark stains cover parts of the ceiling, where smoke and other"
      + " fumes have risen countless times to coat the surface.\n");
    add_item( ({ "down", "floor", "ground", "floorboard", "floorboards" }),
        "The floorboards of this room are well swept.\n");
    add_item( ({ "wall", "walls" }),
        "The walls of this room are crowded with the many vials and other"
      + " processes which have been set up.\n");
    add_item( ({ "east wall", "eastern wall", "east" }),
        "A long wooden table rests against the eastern wall.\n");
    add_item( ({ "south", "south wall", "southern wall" }),
        "Like the other walls, the southern wall is crowded with many"
      + " vials and beakers.\n");
    add_item( ({ "west", "west wall", "western wall", "door",
                 "doorway" }),
        "A doorway leads out to the street from the western wall.\n");
    add_item( ({ "street", "outside" }),
        "There are no windows which might provide a view of the outside,"
      + " and the doorway is closed.\n");
    add_item( ({ "pricelist", "price list" }), "@@exa_pricelist@@");
    add_cmd_item( ({ "pricelist", "price list" }),
                  ({ "read" }), "@@exa_pricelist@@");

    add_exit("/d/Emerald/telberin/scholars_way02", "west", 0, 1, 1);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);

    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the apothecarium.");

    reset_room();

    setuid();
    seteuid(getuid());
} /* create_telberin_building */

private void
make_trainer()
{
    if (objectp(Trainer))
        return;

    Trainer = clone_object("/d/Emerald/telberin/science/npc/trainer");
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

    me = "mix potions";  ot = me;
    sk_add_train(SS_ALCHEMY,      ({ me, ot }),  0, 0, 20 );
    me = "find and identify herbs"; ot = me;
    sk_add_train(SS_HERBALISM,  ({ me, ot }),  0, 0, 20 );
    me = "orient oneself using nature"; ot = me;
    sk_add_train(SS_LOC_SENSE,  ({ me, ot }),  0, 0, 30 );
}

string
wizinfo() 
{
  return "This is the exclusive location in the game where mortals may"
       + " purchase magic resistance potions - a carefully controlled"
       + " factor to game design, maintained with approval and"
       + " oversight of the AoB team.\n";
}

public mixed
query_location_ids()
{
    return "[the] 'apothecarium' / 'building' / 'shop'";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "It's an Apothecarium.\n";
}


public string
query_entry_desc()
{
    return "into the apothecarium";
}


/*
 * Function name:        exa_pricelist
 * Description  :        print the pricelist
 * Returns      :        string - the text to print
 */
public string
exa_pricelist()
{
    return read_file(
        "/d/Emerald/telberin/science/potions/potion_poster.txt");
} /* exa_pricelist */