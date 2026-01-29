
/*
 * startroom.c
 *
 * Starting room for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
create_room()
{
    set_short("Sleeping chamber");
    set_long("Rows of small wooden bunks line the walls of this "+
        "chamber. This simple room is the sleeping chamber of the "+
        "temple. The walls are plain, grey stone as are the ceiling "+
        "and the floor. A small room lies to the west and a hallway "+
        "stretches out to the south leading back to the main area "+
        "of the temple. There is a curtain hanging on the northern "+
        "section of the west wall. A small sign hangs on the wall next "+
        "to a rack.\n");
    
    add_item("rack","There is a rack hanging on the wall. On the "+
        "rack are some cloaks. You might be able to unhook one if you "+
        "wanted one, or when you are finished with them, you might want "+
        "to hook it back on for next time. <unhook cloak> <hook cloak>\n");
    add_item(({"curtain","silver curtain"}),"A silver curtain hangs "+
        "on the northern section of the west wall. Upon closer "+
        "inspection you see there is a chamber beyond it and you "+
        "could enter it if you wanted. <enter curtain>\n");
    add_item("small room","To the west lies a small room.\n");
    add_item("hallway","The hallway leads off to the south, back "+
        "to the main area of the temple.\n");
    add_item("floor","The floor is made from the same plain grey "+
        "stone as the walls and ceiling are made from.\n");
    add_item(({"roof","ceiling"}),"The ceiling is made of the "+
        "same plain grey stone as the walls and floor are made from.\n");
    add_item(({"wall","walls"}),"The walls are very plain and "+
        "made out of grey stones placed together.\n");
    add_item(({"bunk","bunks","wooden bunk","wooden bunks",
        "small wooden bunk","small wooden bunks","row","rows"}),
        "There are several rows of wooden bunks lining the walls "+
        "of this chamber. They look fairly plain, yet comfortable "+
        "to sleep on. Being a member of the Circle, you may claim "+
        "one as your own and <start here> when you enter the realms.\n");
    add_item(({"sign","small sign"}),"There is a small sign hanging on "+
        "the wall. You can probably read what is on it.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"study","west","@@check_punishments",1);
    add_exit(SPIRIT_TEMPLE+"hallway","south",0,1);
    ("/d/Calia/guilds/scop/temple/statue_chamber")->teleledningsanka();
    ("/d/Calia/guilds/scop/temple/statue_chamber")->check_elders();
}

int
check_punishments()
{
    if (TP->query_skill(SS_SPIRIT_PUNISHMENT) == SPELL_BANNED)
    {
        write("A voice echoes through your mind: You have been "+
            "banned from using your gifts by the council. You may not "+
            "enter the study.\n");
        return 1;
    }

    return 0;
}

int
do_enter(string str)
{
    NF("Enter what? The curtain? <enter curtain>\n");
    
    if (!str)
        return 0;
    
    if (str == "curtain")
    {
        write("You push the curtain aside and make your way past it "+
            "and into the chamber beyond.\n");
        set_dircmd("curtain");
        TP->move_living("by pushing the curtain aside and making "+
            HIS+" way past it and into the chamber beyond",
            SPIRIT_TEMPLE+"statue_chamber");
        return 1;
    }
    return 0;
}

int
do_start(string where)
{
    if (!is_spirit(TP))
    {
        NF("You are not a member of this guild!\n");
        return 0;
    }

    if (where != "here")
    {
        NF("Start where?  Here?\n");
        return 0;
    }

    TP->set_default_start_location("/d/Calia/guilds/scop/temple/startroom");
    write("Psuchae welcomes you to your new home. You shall start here "+
        "now.\n");
    return 1;
}

int
do_read(string str)
{
    if (str != "sign")
    {
        NF("Read what? The sign? <read sign>\n");
        return 0;
    }

    write("The sign reads:\nIf for some reason you have lost your "+
        "holy symbol, simply return to this place and type <recover "+
        "symbol>.\n");
    return 1;
}

int
do_recover(string str)
{
    if (!is_spirit(TP))
    {
        NF("Recover what?\n");
        return 0;
    }

    if (str != "symbol")
    {
        NF("Recover what? Your holy symbol? <recover symbol>\n");
        return 0;
    }

    if (present("spirit_holy_symbol",TP))
    {
        NF("You already have your holy symbol!\n");
        return 0;
    }

    write("A shadowy hand appears from the wall, holding a new "+
        "holy symbol for you. You reach out and take it.\n");
    clone_object(SPIRIT_OBJECTS+"holy_symbol")->move(TP);
    return 1;
}

int
do_unhook(string str)
{
    if (str != "cloak")
    {
        NF("Unhook what? A cloak? <unhook cloak>\n");
        return 0;
    }

    write("You unhook a cloak from the rack and take it.\n");
    say(QCTNAME(TP)+" unhooks a cloak from the rack and takes it.\n");
    clone_object("/d/Calia/guilds/elementalists/objs/cloak")->move(TP);
    return 1;
}

int
do_hook(string str)
{
    object cloak;

    if (str != "cloak")
    {
        NF("Hook what? A cloak? <hook cloak>\n");
        return 0;
    }

    cloak = present("_wor_cloak_",TP);
    
    if (!cloak)
    {
        NF("You do not have a cloak to hang back on the hook.\n");
        return 0;
    }

    write("You hang your cloak back on the hook.\n");
    say(QCTNAME(TP)+" hangs "+TP->query_possessive()+" cloak back on "+
        "the hook.\n");
    cloak->remove_object();
    return 1;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_start,"start");
    add_action(do_read,"read");
    add_action(do_recover,"recover");
    add_action(do_unhook,"unhook");
    add_action(do_hook,"hook");
}
