/**
 * Navarre January 6th 2008.
 * Increased number of ioun stones available in the realm at a time.
 * But limited the chance of when it will appear.
 *
 * Navarre April 1st 2008.
 * It was reported that you could lay on this bed multiple times
 * and thus get your fatigue fully restored, and this was correct.
 * I have increased the fatigue you gain from sleeping on the bed,
 * But also limited it so that you can only do it once every 900 seconds.
 * 
 * Cotillion, 2020-05-12
 * - Fixed cloning if items into the void
 */

#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <money.h>

#define EMERALD_GEM ("/d/Genesis/gems/obj/emerald")
#define RUBY_GEM ("/d/Genesis/gems/obj/ruby")
#define SAPPHIRE_GEM ("/d/Genesis/gems/obj/sapphire")
#define OPAL_GEM ("/d/Genesis/gems/obj/opal")

inherit "/lib/unique";
inherit ICEINROOM;


object chest1, chest2;

void reset_treasure()
{
    reset_room();
}

void
reset_room()
{
    ::reset_room();
    chest1->remove_object();
    chest2->remove_object();

    if (!objectp(chest1))
    {
        chest1 = clone_object(OBJK + "trapped_chest");
        chest1->move(TO);
    }

    if(!objectp(chest2))
    {
        chest2 = clone_object(OBJK + "trapped_chest");
        chest2->move(TO);
    }
        
    /* Chest 1 */

    string *items = ({
        random(3) ? OBJK + "id_scroll" : 0,
    });

    map(filter(items, stringp), clone_object)->move(chest1, 1);
 
    clone_unique(OBJK + "blue_ioun_stone", 10, ({ ({ RUBY_GEM, 33 }) }), 0)->move(chest1, 1);
    clone_unique(OBJK + "green_ioun_stone", 10, ({ ({ RUBY_GEM, 33 }) }), 0)->move(chest1, 1);

    /* Chest 2 */
    items = ({ 
        random(3) ? EMERALD_GEM : 0, 
        random(3) ? RUBY_GEM : 0, 
        random(3) ? OPAL_GEM : 0, 
        SAPPHIRE_GEM
    });

    map(filter(items, stringp), clone_object)->move(chest2, 1);
    chest2->add_prop(OBJ_M_HAS_MONEY, ({ 0, random(1000), random(25), random(10) }));
    MONEY_EXPAND(chest2);
}

void
create_icewall_room()
{

    set_short("Highlord's treasure chamber");
    set_long("@@long_descr");

    add_exit("bare_tunnel","east");
    add_prop(ROOM_M_NO_TELEPORT, "Dark magical protections prevent you from "+
               "teleporting to that location.\n");

    add_item(({"books","book"}),"The books, written in ancient version " +
        "of the common language, deal with the Second Dragon War.\n");
    add_item(({"cabinet","weapons cabinet"}),"The weapons' cabinet is " +
        "quite empty.\n");
    add_item("rugs","Soft and tasteful rugs cover the stone floor, " +
        "giving this room a deceitful aura of comfort and friendship.\n");
    add_item(({"window","narrow window"}),"There are no windows here. " +
        "The room is illuminated by a soft magic glow.\n");
    add_item(({"furs","pillows","bed"}), "" +
        "The furs look soft and cozy, and the bed itself is more then " +
        "inviting. As you look at it, you cannot help but think how " +
        "comfortable and pillowy it would be... Especially with someone " +
        "to warm it for you.\n\nYou blink, sigh, and return to reality.\n");
    add_item(({"mirrors","walls"}),"Silver plated, crystal mirrors " +
        "span the walls. Worth a fortune, they present a most unusual " +
        "sight in a cold, frozen, and up to now, forsaken land of the " +
        "Icewall glacier.\n");
    add_item(({"manacles","chains"}),"Which ones? The wall, or the " +
        "bedpost irons?\n");
    add_item(({"wall manacles","wall irons","wall chains"}),"Your " +
        "eyes narrow as you appraise the manacles hanging from a thick " +
        "ring studded into the wall. The floor beneath the chains is the " +
        "only spot in the whole chamber showing cold, stone floor. Dark " +
        "stains mark the floor there, as well as the wall itself. " +
        "Obviously prisoners questioned here suffered not only from the " +
        "blows, but also from the knowledge that warmth and comfort " +
        "was just an armreach away.\n");
    add_item(({"bedpost manacles","bedpost irons","bedpost chains"}),"" +
        "The manackles " +
        "chained to the post at the head of the bed are smaller and of " +
        "finger quality. You are not sure if you wish to know what sort " +
        "of questioning has been practised there.\n");
    add_item(({"desk","huge desk","mahogeny desk"}),"The desk truly is " +
        "a piece of sturdy wood work. Scrolls and parchments cramped in " +
        "half-closed drawers show that its ownder, whoever else he " +
        "might be, is a scholar. Old, leather-bound books show years of " +
        "use, and seem even more fragile then the two grey skulls that " +
        "serve as gruesome paperweights.\n");
    add_item("map","The map looks new, and is carefully inked on the " +
        "thinnest of leathers by at least a master cartographer. " +
        "Displayed prominently upon it is the southern part of Ansalon. " +
        "Details such as the glacier covered mountains, and precisely " +
        "marked shoreline around the pre-cataclysm portcity of Tharsis " +
        "clearly indicates that it must have been sketched from air, or " +
        "completed with the help of obscure magic.\n");
    add_item(({"skulls","skull","grey skull","grey skulls"}),"The two " +
        "skulls are ancient and decaying. Human size, but with a delicate " +
        "jaw, they could come from a petite human female or an elf.\n");
    reset_room();
}


string
long_descr()
{ 
    return ("" +
        "As you look around this spacious chamber, your battle instincts " +
        "scream in warning and your muscle tense for combat. Decorated with furs, " +
        "lined with crystal mirrors, carpeted with tasteful rugs, and " +
        "cozied by feathery pillows propped on a luxurious, canopied " +
        "bed fit for a king, the room looks like the bedchamber of a Queen... " +
        "At first glance, that is. Massive, iron-banded chests, " +
        "manackles chained to the wall and bedpost, weapon cabinet, " +
        "and most of all, a huge mahony desk on which two skulls " +
        "hold a gigantic map unrolled show that this is the home of a " +
        "general. One who delights in pain and pleasure, and one who " +
        "has the power to get exactly what he wants.\n");
}



int
lay(string str)
{
    if(str != "on bed")
    {
        notify_fail("Lay on what? The bed?\n");
        return 0;
    }

    if(time() - TP->query_prop("_i_used_the_bed_at_time_") < 900)
    {
        write("You try to get comfortable on the bed, but can't seem to fall asleep.\n");
        return 1;
    }
    
    write("With a sigh of pure pleasure, you collapse into the " +
        "fluffy furs, feeling like a Royalborn.\n");
    say(QCTNAME(TP) + ", with a sigh of pure pleasure, collapses " +
        "into the fluffy furs on the bed.\n");
    TP->add_fatigue(50);
    TP->add_prop("_i_used_the_bed_at_time_", time());
    return 1;
} 
     
int
knock(string str)
{
    if(str == "on north wall")
    {
        write("You knock soundly on the north wall, but no hollow " +
            "sound accompanies your test.\n");        
        say(QCTNAME(TP) + " knocks soundly on the north wall, but " +
            "no hollow sound accompanies the test.\n");
        return 1;
    }

    if(str == "on south wall")
    {
        write("You knock soundly on the south wall, and faint hollow " +
            "sound rings out in response.\n");        
        say(QCTNAME(TP) + " knocks soundly on the south wall, and " +
            "faint hollow sound out in response.\n");
        tell_room(ROOMSK + "hall2", "A faint sound " +
            "of knocking resounds, as if someone was banging on the " +
            "north wall from the other side.\n");
        return 1;

    }

    notify_fail("Knock on which wall?\n");

    return 0;
}

void
init()
{
    ::init();

    add_action(knock, "knock");
    add_action(lay,"lay");
}
