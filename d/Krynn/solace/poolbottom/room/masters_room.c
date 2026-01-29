#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;
object door, servant;

void
reset_poolbottom_room()
{
      if(!door->query_locked())
      {
        tell_room(environment(this_object()), "An ethereal servant suddenly appears " +
         "and begins tidying the room.\n");
        setuid();
        seteuid(getuid());
        servant = clone_object(LIVING + "ethereal_servant");
        servant->arm_me();
        servant->move(this_object());
        servant->command("close door");
        servant->command("lock door with key");
        servant->remove_object();
        tell_room(environment(this_object()), "The ethereal servant vanishes, off to clean " +
         "other parts of the school.\n");
       }
        
	return;
}

create_poolbottom_room()
{
    set_short("private residence of Master Theobald");
    set_long("You stand within the large private residence of Master Theobald, the " +
       "head of the school of High Magic. At the back of the residence stands a large " +
       "fireplace - sweltering heat radiating from the fire permanently raging from " +
       "within. To the left of the room is a neatly-made bed with a dresser beside it. " +
       "To the right of the room is a solid writing desk of oak, with a small bookshelf " +
       "behind it.\n");

    add_item(({"ornate door","door","entrance"}),
       "To your south is an ornate door, the exit to  Master Theobald's private residence.\n");

    add_item(({"fireplace","large fireplace","fire"}),
       "Built into the southern wall is a large fireplace. A fire rages from the inner " +
       "hearth with consistent intensity - it seems some sort of fire enchantment keeps " +
       "the fire going and the temperature of the room at a sweltering heat.\n");

    add_item(({"neatly-made bed","bed"}),"This is the bed of Master Theobald. It is very well " +
       "made, with the sheets and cover tightly tucked and crisply pressed... likely the work " +
       "of a summoned unseen servant.\n");

    add_item(({"dresser","clothes"}),"Beside the bed is a dresser, containing clothes of the Master of " +
       "Poolbottom.\n");

    add_item(({"solid writing desk","writing desk","desk","desk of oak","oak desk"}),
       "This is the writing desk of Master Theobald, the head of the school of High Magic. " +
       "Ledgers and student notes cover one side of the desk while on the other side " +
       "is the Master's thick spell tome, sitting open.\n");

    add_item(({"ledgers","student notes","notes"}),"You flick through the ledgers and " +
       "student notes, and quickly come to realisation that the school is doing VERY well " +
       "financially, and that Master Theobald doesn't have many nice things to say about " +
       "his students.\n");

    add_item(({"master's thick spell tome","spell tome","masters spell tome", 
       "thick spell tome","tome","spellbook","master's spellbook"}),
       "Ah the Master's spellbook! A potential treasure trove of spells, however your quick " +
       "eye notices glimmering runes of protection surrounding it. You have no doubt anyone trying " +
       "to touch it or pick it up will greatly regret it. You can, however, try and read or study the page " +
       "it is open on.\n");

        add_cmd_item(({"master's thick spell tome","spell tome","masters spell tome", 
        "master's spellbook","thick spell tome","tome","spellbook"}),({"read","study"}),"@@read_book");

        add_cmd_item(({"master's thick spell tome","spell tome","masters spell tome", "thick spell tome","tome","spellbook",
        "up master's thick spell tome","up spell tome"," up masters spell tome", "up thick spell tome","up tome","up spellbook",
        "page of spellbook","page of thick spellbook","page of masters spellbook","page","page of tome","page of spell tome"}),
       ({"get","turn","pick","take"}),"@@steal_book");

    add_item(({"walls","sandstone walls","grey sandstone walls","high sandstone walls",
               "blocks","sandstone blocks","grey sandstone blocks"}),
       "The school has been build from grey sandstone blocks mined from quarries " +
       "far to the south near Pax Tharkas. The workmanship of the walls is seamless, " +
       "most likely done by a master dwarven mason.\n");

    door = clone_object(EOBJ + "theobald_doorb");
    door->move(this_object());

    reset_poolbottom_room();
}

string
read_book()
{
    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
	write("Your spellcraft skills are too poor even begin comprehending " +
          "the magical runes on the open page of the spell tome before you.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + " tries to "+
        "comprehend the runes within the thick spell tome on the writing desk, " +
        "but doesn't have the spellcraft skills.\n", ({ this_player() }));
	return "";
    }

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        write("You are unable to decypher the magical writing " +
        "in the spell tome.\n");
        return "";
    } 

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the magical " +
        "runes in the spell tome. Perhaps try again after preparing yourself " +
        "to read magic?\n");
        return "";
    } 

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"apianak"))
    {
        write("The spell tome seems to be open on the spell 'apianak', or " +
            "flame dart, which you have already scribed in your spellbook.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + " reviews "+
        "the content of the page the spell tome is open on, but discovers " +
        "nothing of interest.\n", ({ this_player() }));
        return "";
    }

    write("Ah! The spell tome is open on a page detailing an unknown spell to you! " +
        "The flame dart spell!\n" +
        "You carefully study the runes of the spell tome and scribe the " +
        "spell in to your spellbook!\n");
    say(QCTNAME(this_player()) + " carefully reviews the spell tome on the table and begins copying a spell in to " +
        this_player()->query_possessive() + " leather-bound spellbook.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"apianak");

    return "";
}

string
steal_book()
{
    write("BOOOOOOOOOOOOOOOM!!!!!!!!\n" +
       "You touch the thick spell tome on the desk and shimmering runes of protection around it explode " +
       "in fiery wrath! You scream out in pain!\n");

    say("As " +QTNAME(this_player()) + " reaches out to the thick spell tome on the writing table you " +
       "notice protective runes around it begin to glow angrily and then explode in a fiery wrath!\n" +
       QCTNAME(this_player())+ " screams out in agony!\n");

    // Spellbook rune does a lot of damage! But meant more to scare, not kill, so no do_die
    this_player()->heal_hp(-4000);

    return "";
}