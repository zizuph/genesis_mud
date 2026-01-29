/* The Disks of Mishakal. Original by Percy?
 * modified by Teth, Feb 22, 1997
 * - Are now a magic object.
 *
 * Navarre December 31st 2007.
 * Fixing runtime with playerundead = query_prop_setting(LIVE_I_UNDEAD)
 * returning a function instead of a number. Changed to query_prop(LIVE_I_UNDEAD).
*/

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <language.h>
#include "/d/Krynn/std/room/cmd_parse.c"

#define I_WAS_ZAPPED_BY_MISH "_i_was_zapped_by_mish"

void do_read();

public void
create_object()
{
    set_name("disks");
    set_pname("disks");
    add_name(({"set", "set of disks","disks_of_mish","black_item",
        "disks of mishakal"}));
    add_pname(({"sets","sets of disks"}));
    set_adj(({"metal","holy","platinum"}));
    add_adj(({"set","of"}));
    set_short("set of platinum disks");
    set_long("This is a set of platinum disks. Each disk is made " +
      "of hammered platinum, and is wafer-thin. A hole is punched " +
      "through each disk, and a steel rod runs through the holes. " +
      "Every one of the 160 disks is engraved with arcane glyphs " +
      "on both sides, and is 3 human hand spans wide.\n");
    add_item(({"platinum","hammered platinum"}),"The platinum is " +
      "a silvery-blue colour.\n");
    add_item("punched hole","A hole is never much to look at.\n");
    add_item(({"rod","steel rod"}),"The steel rod is as shiny as the " +
      "day it was forged.\n");
    add_item(({"arcane symbols","symbols","arcane glyphs","glyphs"}),
      "The glyphs do not seem to be readable to you, but you could " +
      "try.\n");
    add_cmd_parse("[the] [arcane] [platinum] 'glyphs'",
      "read","@@do_read");

    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 14000 + (random(4000)));
    add_prop(OBJ_M_NO_SELL, "The disks have no value to a merchant.\n");

    add_prop(OBJ_I_ALIGN, 1150);
    add_prop(OBJ_S_WIZINFO, "These are the holy Disks of Mishakal, an " +
      "arcane artifact that reveals some of the divine mysteries to " +
      "to the mortals. These disks are found inside the treasure chest " +
      "located at ~xak/caverns/cavern.c. They are guarded by a " +
      "ancient black dragon, and are no longer easy to get, despite " +
      "the fact that they are quest objects. They are holy and magical, " +
      "causing damage to evil players getting them <once, via a prop> " +
      "and 5% of the time causing death to evil players attempting " +
      "to read the symbols. Undeads get increased damage.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"These are an ancient artifact of " +
        "a god of healing.\n", 8, "The disks are holy, and do not " +
        "reward those of evil tendencies.\n", 16, "Holy as they are, " +
        "the disks cause harm to evil creatures handling them.\n", 24,
        "Evil persons attempting to read the glyphs may face death.\n", 36,
        "Undead creatures handling the disks suffer additional damge.\n", 
        55,}));
    add_prop(MAGIC_AM_MAGIC, ({ 80, "life"}));

}

public void
enter_env(object dest, object old)
{
    int playeralign, playerundead;

    playeralign = dest->query_alignment();
    playerundead = dest->query_prop_setting(LIVE_I_UNDEAD);

    if(!living(dest))
        return;
    if(((playeralign) > 0) &&
      (!(dest->query_prop(LIVE_I_UNDEAD))))
        return;
    if(dest->query_prop(I_WAS_ZAPPED_BY_MISH))
      {
      write("The set of platinum disks do not burn you this time.\n");
      say(QCTNAME(TP) + " hesitantly handles the set of platinum disks.\n");
      return;
    }
    if((playeralign) > 0)
        playeralign = -(playeralign);
    {
    set_alarm(0.3, 0.0, "zap_me");
    return;
    }
    return;
}

void
zap_me()
{

    int playeralign, playerundead;
    
    playeralign = TP->query_alignment();
    playerundead = TP->query_prop(LIVE_I_UNDEAD);

    write("The set of platinum disks burn you as you pick them up!\n");
    say(QCTNAME(TP) + " winces as " +HE(TP)+ " touches the set " +
        "of platinum disks.\n");
    TP->add_prop(I_WAS_ZAPPED_BY_MISH, 1);
    TP->heal_hp((playeralign / 2) + (-((playerundead) * 3)));

    if(TP->query_hp() <= 0)
        TP->do_die(TO);
}



string
do_read()
{
    if(!(random(20)))
    {
        if((TP->query_alignment() < 0) || (TP->query_prop(LIVE_I_UNDEAD)))
        {
            write("The holy glyphs burn inside your mind!\n");
            say(QCTNAME(TP) + " stares vacantly, seeing nothing.\n");
            TP->command("$scream");
            TP->heal_hp(-(TP->query_max_hp()));
            if(TP->query_hp() <= 0)
                TP->do_die(TO);
            return "";
        }
    }
    write("You attempt the read the arcane glyphs but are unable to " +
        "decipher anything. Perhaps the disks were only made to be " +
        "read by clerics of good gods.\n");
    say(QCTNAME(TP) + " inspects the set of platinum disks closely.\n");
    return "";
}


void
init()
{
    ::init();
    init_cmdparse();
}
