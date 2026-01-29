
/*
 * great_hall.c
 *
 * Great hall for the Spirit Circle of Psuchae Temple
 * Only Spirit Circle members can go north into the ritual chamber and
 * east into the divination chamber. Everyone who goes south into the
 * entryway will be warned that they are now considered 'unpure' and 
 * if they wish to re-enter the temple, they shall have to purify
 * themselves again. Wizards can go into either of the restricted
 * chambers.
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 25, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
create_room()
{
    set_short("Great hall");
    set_long("You are standing in an absolutely enormous chamber "+
        "in the temple known as the great hall. The domed ceiling "+
        "must be at least fourty feet above you at its highest "+
        "point. The walls here are made from small grey stone "+
        "bricks. A large set of oak double doors lead out of the "+
        "temple to the south. There are two sets of maple double "+
        "doors leading out of this chamber, one set to the north "+
        "and one set to the east. There is an open black door set "+
        "into the west wall. There are four large braziers here, "+
        "one in each corner. They give off enough light for "+
        "the entire chamber. In the middle of the stone floor you "+
        "see a large mosaic.\n");
   
    add_item(({"oak double doors", "oak double door",
        "solid oak double doors","solid oak double door",
        "south double doors","south double door","south door",
        "south doors"}), "To "+
        "the south lies a set of solid oak double doors. "+
        "They are closed.\n");
    add_item(({"mosaic","large mosaic"}),"This colourful mosaic "+
        "on the centre of the floor depicts a shadowy figure "+
        "standing in the centre of a garden surrounded by five "+
        "stones.\n");
    add_item(({"slab","stone slab","large stone slab","slabs",
        "stone slabs","large stone slabs"}),"The large stone "+
        "slabs make up the stone floor that you are standing "+
        "upon. In the centre of the slabs you see a large mosaic.\n");
    add_item(({"floor","stone floor"}),"You are standing on a "+
        "very large stone floor. It appears to be constructed "+
        "from very large stone slabs placed in a rectangular "+
        "pattern. In the centre of the floor is a large mosaic.\n");
    add_item(({"flame","burning flame","flames","burning flames",
        "large flame","large flames","large burning flame",
        "large burning flames"}),"There is a large burning flame in "+
        "each of the braziers in the corners of this chamber. The "+
        "light from these braziers reflects off of the ceiling and "+
        "makes interesting patterns on the walls.\n");
    add_item(({"brazier","braziers","large brazier","large braziers",
        "four braziers","four large braziers"}),"There are four large "+
        "braziers in this chamber, one in each of the corners. Each "+
        "of the braziers is made from iron and has a large burning "+
        "flame in them.\n");
    add_item(({"chamber", "smaller chamber"}), "Through the open "+
        "black door set into the western wall you see a smaller "+
        "chamber than this one. It is hard to make out any other "+
        "details from this vantage point.\n");
    add_item(({"door","black door","open door","open black door",
        "western door","west door"}),"There is an open black door "+
        "set into the western wall. Through the door you see a "+
        "smaller chamber than this one.\n");
    add_item(({"eastern doors","eastern door","eastern maple door",
        "eastern maple doors","eastern maple double door",
        "eastern maple double doors","east door","east doors"}),
        "These are a set "+
        "of maple double doors set into the eastern wall. Carved "+
        "across both doors is an inscription.\n");
    add_item("inscription","The inscription carved across the maple "+
        "double doors set in the eastern wall reads:\nDivination Chamber.\n");
    add_item(({"northern doors","northern door","northern maple door",
        "northern maple doors","northern maple double door",
        "northern maple double doors","north door","north doors"}),
        "These are a set of maple double "+
        "doors set into the northern wall. They have a pentagram "+
        "carved into them, half of the pentagram is on each door.\n");
    add_item("pentagram","The pentagram is carved across the maple "+
        "double doors set in the northern wall. Half of the pentagram "+
        "is on each of the doors in the set.\n");
    add_item(({"maple double door", "maple double doors"}), "Which "+
        "set of maple double doors do you wish to examine? The "+
        "northern maple double doors or the eastern maple double "+
        "doors?\n");
    add_item(({"double doors", "double door"}), "Which set of "+
        "double doors do you want to look at? The oak double doors, "+
        "the northern maple double doors, or the eastern maple "+
        "double doors?\n");
    add_item(({"ceiling","domed ceiling","roof","domed roof"}),
        "The large domed ceiling is at least fourty feet above "+
        "you at its highest point. It appears to be totally covered "+
        "in gold. The flames from the braziers in the corners "+
        "flicker off of it and make some interesting patterns on the "+
        "walls.\n");
    add_item(({"patterns", "interesting patterns","pattern",
        "interesting pattern","shadows"}), "The light from the four braziers "+
        "in the four corners of the chamber reflecting off of the "+
        "gold covered domed ceiling make interesting patterns and "+
        "shadows on the walls. These patterns are all colours of "+
        "the rainbow intermixed with shadows.\n");
    add_item(({"wall", "walls","brick","grey brick","stone brick",
        "small brick","small grey brick","grey stone brick",
        "small grey stone brick","bricks","grey bricks","stone bricks",
        "small bricks","small grey bricks","grey stone bricks",
        "small grey stone bricks","brick wall","brick walls","mortar"}), 
        "The walls are constructed from small grey stone bricks "+
        "stacked on each other and filled with grey mortar. "+
        "Interesting patterns dance across the walls. Set into "+
        "the western wall is an open black door. There are three "+
        "sets of double doors; one set of oak double doors in the "+
        "southern wall, one set of maple double doors in the "+
        "northern wall, and finally one other set of maple "+
        "double doors set into the eastern wall.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");
    clone_object(SPIRIT_NPCS+"greeter")->move(TO);

    add_exit(SPIRIT_TEMPLE+"ritual_chamber","north","@@check_spirit",1);
    add_exit(SPIRIT_TEMPLE+"entryway","south","@@non_pure",1);
    add_exit(SPIRIT_TEMPLE+"antechamber","west",0,1);
    add_exit(SPIRIT_TEMPLE+"divination_chamber","east","@@check_spirit",1);
}

int
check_spirit()
{
    if (TP->query_skill(SS_SPIRIT_PUNISHMENT) == SPELL_BANNED)
    {
        write("A voice echoes through your mind: You have been "+
            "banned from using spells by the council. You may not "+
            "enter the Divination Chamber.\n");
        return 1;
    }

    if (present("_schosen_",TP) && 
        TP->query_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS) == 2)
    {
        if (present("_psuchae_staff_",TP))
        {
            write("You have already created the Staff of Psuchae. You "+
                "cannot re-enter the Ritual Chamber.\n");
            return 1;
        }

        write("You push on the double doors and they open before you, "+
            "allowing you to pass into the chamber beyond them. The "+
            "doors closes quickly behind you.\n");
        say(QCTNAME(TP)+" pushes on the double doors and they open "+
            "before "+HIM+", allowing "+HIM+" to pass into the chamber "+
            "beyond, the doors closing behind "+HIM+".\n");
        return 0;
    }

    if (is_spirit(TP))
    {
        write("You push on the double doors and they open before you, "+
            "allowing you to pass into the chamber beyond them. The "+
            "doors closes quickly behind you.\n");
        say(QCTNAME(TP)+" pushes on the double doors and they open "+
            "before "+HIM+", allowing "+HIM+" to pass into the chamber "+
            "beyond, the doors closing behind "+HIM+".\n");
        return 0;
    }

    if(TP->query_wiz_level())
    {
        write("Normally you would not be allowed in this chamber, "+
            "but since you are a wizard an exception can be made. "+
            "You press on the double doors and they open before you, "+
            "allowing you to pass into the chamber beyond them.\n");
        say(QCTNAME(TP)+" presses on the double doors and they open "+
            "before "+HIM+", allowing "+HIM+" to pass into the chamber "+
            "beyond, the doors closing behind "+HIM+".\n");
        return 0;
    }
    
    write("A voice from above:\nOnly those who "+
        "follow the Spiritual Path may pass.\n\n");
    return 1;
}

int
non_pure()
{
    if (present(CEREMONIAL_GARB,deep_inventory(TP)))
    {
        write("You cannot leave the temple with ceremonial items! "+
            "Please return them to the sacristy first.\n");
        return 1;
    }

    if (present(CEREMONIAL_GARB,TP))
    {
        write("You cannot leave the temple with ceremonial items! "+
            "Please return them to the sacristy first.\n");
        return 1;
    }

    if (TP->query_skill(SS_SPIRIT_PUNISHMENT) == TEMPLE_RESTRICTED)
    {
        write("You have been restricted to the Temple by the Spirit "+
            "Circle council, so you cannot leave.\n");
        return 1;
    }

    if (TP->query_wiz_level())
    {
        write("Normally if you left the sanctity of the great "+
            "hall, you would feel that if you wanted to return that "+
            "you would have to purify yourself once again, but since "+
            "you are a wizard, you do not need to worry about that "+
            "anyways.\n");
        TP->remove_prop(PRAYED_AT_TEMPLE_ALTAR);
        TP->remove_prop(BATHED_IN_TEMPLE_BATH);
        return 0;
    }
    
    else
    {
        write("\n\nAs you leave the sanctity of the great hall, you feel "+
            "if you wanted to return inside that you would have to "+
            "purify yourself once again.\n\n");
        TP->remove_prop(PRAYED_AT_TEMPLE_ALTAR);
        TP->remove_prop(BATHED_IN_TEMPLE_BATH);
        return 0;
    }
}

int
do_read(string str)
{
    if(!str)
    {
        NF("Read what? The inscription? <read inscription>\n");
        return 0;
    }

    if (str != "inscription")
    {
        NF("Read what? The inscription? <read inscription>\n");
        return 0;
    }

    write("The inscription carved across the maple double doors set "+
        "into the eastern wall reads:\nDivination Chamber\n");
    return 1;
}

int
do_bathe(string str)
{
    int old_val, new_val;

    if (!str)
        return 0;

    if (parse_command(str, ({}), 
        "[the] [black] 'diamond' [in] [the] [brazier] [flame]"))
    {
        if (!present("black_diamond",TP))
        {
            NF("You do not have a black diamond!\n");
            return 0;
        }

        write("You drop the black diamond into the brazier and "+
            "watch as the flames lick at it's surface. Braving "+
            "the pain, you reach in and quickly grab the black "+
            "diamond out of the flames. Amazingly, the flames do "+
            "not burn your skin, nor is the black diamond hot to "+
            "the touch.\n");
        say(QCTNAME(TP)+" drops something into one of the braziers, "+
            "then quickly retrieves it again.\n");
        old_val = TP->query_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS);
        new_val = MIN(2,old_val + 1);
        TP->add_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS,new_val);
        return 1;
    }

    else if (parse_command(str, ({}), 
        "[the] 'stick' [in] [the] [brazier] [flame]"))
    {
        if (!present("stick",TP))
        {
            NF("You do not have a stick!\n");
            return 0;
        }

        write("You drop the stick into the brazier and "+
            "watch as the flames lick at it's surface. Braving "+
            "the pain, you reach in and quickly grab the stick "+
            "out of the flames. Amazingly, the flames do "+
            "not burn your skin, nor is the stick hot to "+
            "the touch.\n");
        say(QCTNAME(TP)+" drops something into one of the braziers, "+
            "then quickly retrieves it again.\n");
        old_val = TP->query_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS);
        new_val = MIN(2,old_val + 1);
        TP->add_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS,new_val);
        return 1;
    }

    else if (parse_command(str, ({}), 
        "[the] 'staff' [in] [the] [brazier] [flame]"))
    {
        if (!present("staff",TP))
        {
            NF("You do not have a staff!\n");
            return 0;
        }

        write("You drop the staff into the brazier and "+
            "watch as the flames lick at it's surface. Braving "+
            "the pain, you reach in and quickly grab the staff "+
            "out of the flames. Amazingly, the flames do "+
            "not burn your skin, nor is the staff hot to "+
            "the touch.\n");
        say(QCTNAME(TP)+" drops something into one of the braziers, "+
            "then quickly retrieves it again.\n");
        old_val = TP->query_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS);
        new_val = MIN(2,old_val + 1);
        TP->add_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS,new_val);
        return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(do_bathe,"bathe");
    add_action(do_bathe,"purify");
    add_action(do_read,"read");
}
