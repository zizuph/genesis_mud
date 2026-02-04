/* created by Arman June 2018 */
#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

create_room()
{
    set_short("Minstrel Club join room");
    set_long("Minstrel Club join room. You can <select> a specific " +
        "instrument to perform with:\n" +
        "    lute,\n" +
        "    recorder,\n" +
        "    dulcimer,\n" +
        "    harp,\n" +
        "    shawm,\n" +
        "    viol, or\n" +
        "    trumpet.\n" +
        "\n\n");

}

void
init()
{
    ::init();
    add_action("select", "select");
    add_action("abandon", "abandon");

}

string
eligible_instruments(string str)
{
    switch(str)
    {
        case "lute":
            return "lute";
            break;
        case "recorder":
            return "recorder";
            break;
        case "dulcimer":
            return "dulcimer";
            break;
        case "harp":
            return "harp";
            break;
        case "shawm":
            return "shawm";
            break;
        case "viol":
            return "viol";
            break;
        case "trumpet":
            return "trumpet";
            break;
    }

    return 0;
}

int
select(string str)
{
    setuid();
    seteuid(getuid());

    object club_obj = clone_object(NEW_GUILDOBJ + "instrument_club");
    object book = clone_object(NEW_GUILDOBJ + "club_songbook");
    string instrument;

    NF("Select which instrument?\n");
    if (!str)
	return 0;

    instrument = lower_case(str);

    NF("That isn't an eligible instrument to select.\n");
    if(!eligible_instruments(instrument))
	return 0;

    NF("You are already a performer!\n");
    if(IS_PERFORMER(this_player()))
        return 0;
    
    PERFORM_MANAGER->add_member(this_player());
    PERFORM_MANAGER->set_reputation_level(this_player(), 0);

    club_obj->move(this_player(), 1);
    club_obj->set_name(instrument);

    say(QCTNAME(this_player()) + " has selected an " +
        "instrument and taken up the role of performer of Genesis!\n", 
        this_player());
    write("You have selected an instrument and are now a " +
        "performer of Genesis!\n");

    if (!present("minstrel_song_book", this_player()))
    {
        book->move(this_player(), 1);
        book->set_owner(this_player());
	write("You also take a songbook to pen your songs in!\n");	    
    }

    return 1;

}

public int
abandon(string str)
{
    NF("Abandon what? Being a performer?\n");
    if (!str || str != "being a performer")
	return 0;

    NF("You are not a performer, so can't abandon being one!\n");
    if(!IS_PERFORMER(this_player()))
        return 0;

    NF("As a Minstrel, you can't not be a performer!\n");
    if(MEMBER(this_player()))
        return 0;

    tell_object(this_player(),"As with many before you who thought " +
        "fame and fortune awaited them through music, " +
        "realisation has hit that this is not a path for you. " +
        "You abandon being a performer.\n");

    PERFORM_MANAGER->remove_member(this_player());

    if(present("minstrel_instrument", this_player()))
        present("minstrel_instrument", this_player())->do_things();

    if(present("minstrel_song_book", this_player()))
        present("minstrel_song_book", this_player())->remove_object();

    return 1;
}
