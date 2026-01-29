#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit SANCINROOM;

#define THROTYL "/d/Krynn/throtyl/rooms/throtyl-16-16-5"

int runes_activated = 0;

public string cast_detect_magic();

void
create_sanction_room()
{
    set_short("in a tunnel overlooking the vent of a volcano");
    set_long("You stand at the end of a tunnel within an active volcano " +
        "in the Taman Busuk mountain range. The tunnel ends here at " +
        "the huge vent of the volcano, filling the passage with a cloud " +
        "of toxic fumes and incredibly intense heat. The walls of the " +
        "tunnel are rough, although there is a peculiar smooth square " +
        "of wall on the northern side.\n");

    add_item(({"tunnel","end","passage","vent","huge vent","volcano"}),
        "The tunnel ends here, and overlooks the huge vent of the " +
        "volcano. You cannot see much from here, as roiling black " +
        "clouds of toxic fumes rage up from the volcano's depths.\n");

    add_item(({"walls","smooth square","square","northern wall","wall"}),
        "A square of the wall to your north has been smoothed flat. " +
        "It looks like intricate runes have been carved here.\n");

    add_item(({"runes","intricate runes"}),
        "@@runes_desc");

    add_cmd_item(({"runes","intricate runes"}),"read",
        "@@runes_desc");

    add_cmd_item(({"runes","intricate runes"}),"scribe",
        "@@learn_spell");

    add_cmd_parse("'ickrakarcanis' [on] [the] [intricate] 'runes' ",
        "cast", cast_detect_magic);

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    add_exit(SCITY + "volcano_side", "out", 0);

}

string
runes_desc()
{
    if(runes_activated)
        return "Intricate runes have been carved in to a smooth section " +
            "of the wall here. They glow brightly, allowing you to " +
            "translate that they are a spell of some kind. You could " +
            "possibly scribe these runes into your spellbook.\n";
    else
        return "Intricate runes have been carved in to a smooth section " +
            "of the wall here. They look of an arcane nature, but time " +
            "and the acidic scarring from the volcanic fumes make the " +
            "runes illegible.\n";
}

public void
reset_rune_activation()
{
    tell_room(this_object(), "The intricate runes on the wall suddenly " +
         "stop glowing.\n", ({  }));

    runes_activated = 0;
}

void
detect_magic(object caster)
{
    write("The intricate runes blaze with a blue aura, making them " +
        "readable!\n");
    say("The intricate runes on the northern wall blaze with a blue " +
        "aura.\n");

    runes_activated = 1;
    set_alarm(60.0,0.0, &reset_rune_activation());
}

public string
cast_detect_magic()
{
    if(!WOHS_MANAGER->query_memorised_spell(TP,"ickrakarcanis_memorised") &&
       !TP->query_wiz_level())
    {
        return 0;
    }

    write("You open your hands wide and slowly move them over the " +
        "northern wall while chanting 'ickrak arcanis'.\n");
    say(QCTNAME(TP) + " opens " + TP->query_possessive() + 
        " hands wide and slowly moves them over the smooth northern " +
        "wall of the tunnel.\n");
    set_alarm(3.5, 0.0, &detect_magic(TP));
    return "";
}

string
learn_spell()
{
    if(!runes_activated)
    {
        write("The runes on the wall are illegible.\n");
        return "";
    }

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the intricate runes.\n");
        return "";
    }

    if(this_player()->query_skill(SS_SPELLCRAFT) < 90)
    {
	write("Your spellcraft skills are too poor to decypher the intricate " +
            "runes. You imagine only the greatest of masters would be able " +
            "to work out what they mean!\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + " tries to "+
        "comprehend what the intricate runes say, " +
        "but doesn't have the spellcraft skills.\n", ({ this_player() }));
	return "";
    }

    if((this_player()->query_advanced_spells_max() < 1))
    {
        write("The intricate runes clearly are of a spell of the most " +
            "advanced kind. You don't have the ability yet to learn " +
            "such spells.\n");
        return "";
    }

    if(WOHS_MANAGER->query_scribed_spell(this_player(),"hexlithdrevab"))
    {
        write("Having already scribed Doom Blast in to your spellbook, " +
         "you feel no need to scribe it again.\n");
        return "";
    }

    if(!WOHS_MANAGER->query_scribed_spell(this_player(),"hexlithdrevab"))
    {
    write("You decipher the intricate runes carved in to the wall of the cave " +
       "to be an advanced spell of destruction, and eagerly copy 'Hexlith Drevab' " +
       "- Doom blast - in to your spellbook.\n");
    say("After studying the intricate runes on the wall of the tunnel " 
        +QTNAME(this_player()) + " begins copying a spell in to " +HIS(this_player())+
        " spellbook.\n");
    
    WOHS_MANAGER->scribe_spell_to_spellbook(this_player(),"hexlithdrevab");
        return "";
    }

    return "";
}


