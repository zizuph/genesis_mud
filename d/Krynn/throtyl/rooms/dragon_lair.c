#include "/d/Krynn/common/defs.h"
#include "../local.h"

#include <money.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <const.h>
#include <poison_types.h>
#include <filter_funs.h>
#include <state_desc.h>

inherit R_FILE
inherit "/lib/unique";

object dragon, chest, thane;
int dragon_spawned = 0;
int thane_spawned = 0;
int open_sarc = 0;
int trap_disarmed = 0;

#define APPROACHED_SARC "_throtyl_approached_sarcophagus"

void
reset_krynn_room()
{
    if(!objectp(dragon))
        dragon_spawned = 0;

    if(!objectp(thane))
        thane_spawned = 0;

    if(objectp(dragon) && (!dragon->query_attack()))
    {
        dragon_spawned = 0;
        tell_room(TO, "The adult red dragon extends his wings " +
            "and flies up in to the shadows of the cavern above.\n");
        dragon->remove_object();
    }

    if(objectp(thane) && (!thane->query_attack()))
    {
        thane_spawned = 0;
        tell_room(TO, "With a wail of frustration the mad ghost " +
            "of a dwarven thane vanishes.\n");
        thane->remove_object();
    }

    if(open_sarc)
    {
        tell_room(TO, "The lid of the sarcophagus slides closed.\n");
        open_sarc = 0;
    }

    trap_disarmed = 0;
}

void
create_krynn_room()
{
    set_short("a dwarven burial chamber");
    set_long("@@long_descr");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"natural cavern","cavern","chamber","burial chamber",
        "grand burial chamber"}),
        "You stand within a grand dwarven burial chamber, carved " +
        "from a single natural cavern whose walls soar up so high " +
        "you cannot make out the ceiling. In the centre of the " +
        "chamber is a sarcophagus carved into the likeness of a " +
        "dwarven king. On either side of the sarcophagus stand " +
        "statues in silent guard.\n");
    add_item(({"walls","wall"}),
        "The walls of the chamber soar up out of sight, the darkness " +
        "obscuring the ceiling.\n");
    add_item(({"darkness","ceiling","shadowy recesses","recesses"}),
        "@@examine_darkness");
    add_item(({"great stone slabs","stone slabs","slabs","floor"}),
        "This natural cavern has had great stone slabs expertly laid " +
        "down, forming a perfectly level floor. In the centre of the " +
        "floor rises a dais upon which rests a dwarven sarcophagus.\n");
    add_item(({"dais","platform"}),
        "In the centre of the chamber rises a platform, upon which sits " +
        "a dwarven sarcophagus.\n");
    add_item(({"sarcophagus","dwarven sarcophagus"}),
        "@@examine_sarc");
    add_item(({"lid","sculpture"}),
        "@@examine_lid");
    add_item(({"trap","dwarven trap","clever dwarven trap"}),
        "@@examine_trap");
    add_item(({"inscription","foot of sarcophagus"}),
        "At the foot of the sarcophagus is an inscription carved in " +
        "dwarven. You may be able to read it.\n");
    add_item(({"dwarven statues","statues","statue"}),
        "Against the walls on either side of of the sarcophagus stand " +
        "rows of statues, dwarven warriors standing guard over " +
        "the fallen Thane, their sculpted mouths open in a silent yet " +
        "eternal death chant.\n"); 

    add_cmd_item(({"inscription"}),"read","@@read_inscription");
    add_cmd_item(({"trap","dwarven trap","clever dwarven trap"}),
        "disarm","@@disarm_trap");
    add_cmd_item(({"sarcophagus","dwarven sarcophagus", "lid"}), "open",
        "The sarcophagus has a heavy lid you may be able to slide open " +
        "if you are strong enough.\n");
    add_cmd_item(({"lid","open lid","lid open","heavy lid","heavy lid open",
        "heavy lid","open heavy lid","heavy lid open"}), 
        ({"slide","push"}), "@@open_lid");

    add_exit(ROOMS + "throtyl-13-5-T","out","@@out");

    reset_krynn_room();
}

string
long_descr()
{
    return "You stand in a large natural cavern that has been converted in to " +
        "a grand burial chamber. Great stone slabs - expertly carved - " +
        "line the floor, with a dais raised in the centre of the chamber upon " +
        "which a dwarven sarcophagus lies. Dwarven statues stand in guard " +
        "against the walls of the chamber, which rise high into darkness.\n";
}

void
spawn_dragon(object player)
{
    dragon = clone_object(LIVING + "r_dragon");
    tell_room(TO, "From the darkness above an adult " +
        "red dragon glides down to the stone floor.\n");

    if(player->query_prop(APPROACHED_SARC))
        player->catch_tell("The adult red dragon has landed between " +
            "you and the exit! You are trapped!\n");
    dragon->move(TO, 1);
    set_alarm(0.5, 0.0, &dragon->command("$emote hisses: Tomb hunter now " +
        "the hunted!"));
    set_alarm(0.5, 0.0, &dragon->command("$roar merciless"));
    set_alarm(0.5, 0.0, &dragon->command("$kill " +player->query_real_name()));
    return;
}

void
spawn_thane(object player)
{
    if(objectp(thane))
        return;

    if(thane_spawned)
        return;

    thane = clone_object(LIVING + "thane_ghost");
    tell_room(TO, "\nA wail of death and madness fills the chamber, as an " +
        "undead apparition rises from the sarcophagus!\n\n");

    thane->arm_me();
    thane->move(TO, 1);
    set_alarm(0.1, 0.0, &thane->command("$emote moans: Who awakes me?"));
    set_alarm(0.2, 0.0, &thane->command("$emote wails: Why is my Death Oath " +
        "not redeemed in my falling? Must more blood be spilled?"));
    set_alarm(0.3, 0.0, &thane->command("$roar miserabl"));
    set_alarm(0.4, 0.0, &thane->command("$kill " +player->query_real_name()));
    set_alarm(0.5, 0.0, &thane->set_aggressive(1));
    return;
}

string
examine_darkness()
{
    if(!dragon_spawned && !objectp(dragon))
    {
        set_alarm(1.5, 0.0, &spawn_dragon(TP));
        dragon_spawned = 1;

        return "You look above you into the darkness. You feel an eerie " +
            "sensation as if of being watched, and then notice two blood-red " +
            "orbs deep in the shadowy recesses, the malevolent eyes of a dragon!\n";
    }

    return "You look above you into the darkness, but cannot make out the " +
        "ceiling... the chamber extends upwards beyond your sight.\n";
}

string
examine_sarc()
{
    string sarc_status;

    if(open_sarc)
        sarc_status = " Its lid has been opened and you note it " +
            "is empty.\n";
    else
        sarc_status = "\n";

    TP->add_prop(APPROACHED_SARC, 1);
    TP->catch_tell("You walk up to the sarcophagus and examine it.\n");

    tell_room(TO, QCTNAME(TP)+ " walks up to the sarcophagus and examines " +
        "it.\n", ({ TP }), TP);

    if(!dragon_spawned && !objectp(dragon))
    {
        set_alarm(1.5, 0.0, &spawn_dragon(TP));
        dragon_spawned = 1;
    }

    return "Upon the dais rests a sarcophagus of stone, its lid adorned " +
        "with a sculpture of a dwarven king holding a two-handed mace. " +
        "An inscription has been carved at the foot of the sarcophagus. " +
        sarc_status;
}

string
examine_lid()
{
    string trap_status;

    if(trap_disarmed)
        trap_status = " It looks like the trap has been successfully disarmed.\n";
    else
        trap_status = "\n";

    if(!TP->query_prop(APPROACHED_SARC))
    {
        TP->add_prop(APPROACHED_SARC, 1);
        TP->catch_tell("You walk up to the sarcophagus and examine it's lid.\n");
        tell_room(TO, QCTNAME(TP)+ " walks up to the sarcophagus and examines " +
        "it.\n", ({ TP }), TP);
    }

    if(!dragon_spawned && !objectp(dragon))
    {
        set_alarm(1.5, 0.0, &spawn_dragon(TP));
        dragon_spawned = 1;
    }

    if(TP->query_skill(SS_FR_TRAP) > 40)
        return "The lid of the sarophagus is adorned with a sculpture " +
            "of a dwarven king holding a two-handed mace. While heavy, " +
            "you could probably slide it open... although you notice a " +
            "clever dwarven trap that would likely activate when the " +
            "lid is opened." + trap_status;

    return "The lid of the sarophagus is adorned with a sculpture " +
        "of a dwarven king holding a two-handed mace. While heavy, " +
        "you could probably slide it open. " + trap_status;
}

void
spring_trap()
{
    object *player;
    int i,ti;

    player = FILTER_LIVE(all_inventory(TO));
    seteuid(getuid(TO));

    tell_room(TO, "From the open mouths of the dwarven statues " +
        "flow foul green gases, filling the chamber!\n", ({ }), TP);

    for (i = 0; i < sizeof(player); i++)
    {
        object poison;

        poison = clone_object("/std/poison_effect");
        poison->set_interval(2);
        poison->set_time(120);
        poison->set_damage(({POISON_STAT, SS_CON }));
        poison->set_strength(50);
        poison->set_poison_type("constitution");
        poison->move(player[i], 1);
        poison->start_poison(TO); 
    }
}

string
examine_trap()
{
    if(!TP->query_prop(APPROACHED_SARC))
    {
        TP->add_prop(APPROACHED_SARC, 1);
        TP->catch_tell("You walk up to the sarcophagus and examine it's lid.\n");
        tell_room(TO, QCTNAME(TP)+ " walks up to the sarcophagus and examines " +
        "it.\n", ({ TP }), TP);
    }

    if(!dragon_spawned && !objectp(dragon))
    {
        set_alarm(1.5, 0.0, &spawn_dragon(TP));
        dragon_spawned = 1;
    }

    if(TP->query_skill(SS_FR_TRAP) > 40)
        if(!trap_disarmed)
            return "A clever dwarven trap. Likely some sort of poison trap. " +
                "It would take some skill to disarm it.\n";
        else
            return "A clever dwarven trap that now has been disarmed. You " +
                "can slide open the lid without risk of setting it off.\n";

    return "Examine what?\n";
}

string
disarm_trap()
{
    if(objectp(dragon))
        return "You can't disarm the trap while the dragon is here!\n";

    if(!TP->query_prop(APPROACHED_SARC))
    {
        TP->add_prop(APPROACHED_SARC, 1);
        TP->catch_tell("You walk up to the sarcophagus and examine it's lid.\n");
        tell_room(TO, QCTNAME(TP)+ " walks up to the sarcophagus and examines " +
        "it.\n", ({ TP }), TP);
    }

    if(!dragon_spawned && !objectp(dragon))
    {
        set_alarm(1.5, 0.0, &spawn_dragon(TP));
        dragon_spawned = 1;
    }

    int disarm_roll = random(100);

    if(trap_disarmed)
        return "The trap is already disarmed!\n";

    if(TP->query_skill(SS_FR_TRAP) > disarm_roll)
    {
        write("You successfully disarm the poison trap on the " +
            "sarcophagus!\n");
        say(QCTNAME(TP)+ " successfully disarms the poison trap on the " +
            "sarcophagus!\n");
        trap_disarmed = 1;
        return "";
    }

    if(disarm_roll > 80)
    {
        // If the disarm roll is in the top 20% and was unsuccessfully
        // disarmed it sets off the trap.
        write("You fail to disarm the poison trap, and set it off!\n");
        say(QCTNAME(TP)+ " fails in disarming the poison trap on the " +
            "sarcophagus, and sets it off!\n");
        trap_disarmed = 1;
        spring_trap();
        return "";
    }

    write("You fail to disarm the trap on the sarcophagus.\n");
    say(QCTNAME(TP)+ " fails to disarm the trap on the sarcophagus.\n");
    return "";
}

string
open_lid()
{
    if(open_sarc)
        return "The lid of the sarcophagus has already been pushed open.\n";

    if(objectp(dragon))
        return "You can't slide the lid open while the dragon is here!\n";

    if(!TP->query_prop(APPROACHED_SARC))
    {
        TP->add_prop(APPROACHED_SARC, 1);
        TP->catch_tell("You walk up to the sarcophagus and begin sliding open " +
            "it's lid.\n");
        tell_room(TO, QCTNAME(TP)+ " walks up to the sarcophagus and starts " +
            "sliding the lid open.\n", ({ TP }), TP);
    }

    if(!dragon_spawned && !objectp(dragon))
    {
        spawn_dragon(TP);
        dragon_spawned = 1;
        return "";
    }

    if(TP->query_stat(SS_STR) < SD_AV_GREAT_ADVENTURER)
    {
        // SS_STR of less than 86 isn't strong enough to slide the lid
        write("You try valiantly to open the lid of the sarcophagus, " +
            "but you are not strong enough!\n");
        say(QCTNAME(TP)+ " struggles valiantly to slide the lid of the " +
            "sarcophagus off, but is not strong enough!\n");

        return "";
    }

    write("You slide open the lid of the sarcophagus...\n");
    say(QCTNAME(TP)+ " slides open the lid of the sarcophagus.\n");

    if(!trap_disarmed)
    {
        write("...and carelessly set off a trap!\n");
        say("You hear a 'click' as a trap is set off!\n");
        trap_disarmed = 1;
        spring_trap();
    }

    set_alarm(1.5, 0.0, &spawn_thane(TP));
    open_sarc = 1;
    return "";
}

string
read_inscription()
{
    if(objectp(dragon))
        return "You can't read the inscription while the dragon is here!\n";

    if(TP->query_race_name() == "dwarf" || 
       TP->query_skill(SS_LANGUAGE) > 40)
    {
        write("You read the dwarven inscription:\n" +
              "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" +
              "        ~                                     ~\n" +
              "        ~ Here lies Mad Thane Ruul Curseforge ~\n" +
              "        ~         of the Neidar Clan          ~\n" +
              "        ~                                     ~\n" +
              "        ~ Took the Doomseeker Oath against    ~\n" +
              "        ~ the Mountain Dwarves of Kayolin.    ~\n" +
              "        ~                                     ~\n" +
              "        ~ Fell at the battle of Ravenscar     ~\n" +
              "        ~ with the blood of a score score     ~\n" +
              "        ~ Hylar and Deiwar on his mighty      ~\n" +
              "        ~ warhammer, 'Kinslayer'.             ~\n" +
              "        ~                                     ~\n" +
              "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        say(QCTNAME(TP)+ " carefully reads the dwarven inscription at " +
            "the foot of the sarcophagus.\n");
        return "";
    }
    write("You try and read the inscription but are unfamiliar with " +
        "dwarven languages.\n");
    say(QCTNAME(TP)+ " unsuccessfully tries to read the dwarven " +
        "inscription at the foot of the sarcophagus.\n");
    return "";
}

int
out()
{
    if (TP->query_guild_name_occ() == "Order of the Dragon" || 
        TP->query_guild_name_lay() == "Order of the Dragon")
    {
        write("You leave the dwarven burial chamber and back down to the moors of " +
        "Throtyl.\n");
        TP->remove_prop(APPROACHED_SARC);

        return 0;
    }

    if(objectp(dragon) && TP->query_prop(APPROACHED_SARC))
    {
        if(random(TP->query_skill(SS_ACROBAT)) > random(100))
        {
            write("With great acrobatic skill, you manage to roll under " +
                "the adult red dragon and out the exit of the chamber!\n");
            say("With great acrobatic skill, " +QTNAME(TP)+ " manages to " +
                "to roll under the adult red dragon and out the exit of " +
                "the chamber!\n");
            TP->remove_prop(APPROACHED_SARC);
            return 0;
        }
        write("The adult red dragon stands between you and the exit to the " +
            "chamber! You are trapped!\n");
        say("The adult red dragon stands between the exit of the chamber and " +
            QTNAME(TP)+ ", blocking " +HIM(TP)+ " from fleeing!\n");
        return 1;
    }

    write("You leave the dwarven burial chamber and back down to the moors of " +
        "Throtyl.\n");
    TP->remove_prop(APPROACHED_SARC);

    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!dragon_spawned)
    {
        if(random(ob->query_skill(SS_AWARENESS)) > random(100))
            set_alarm(0.5, 0.0, &ob->catch_tell("You faintly feel the stale " +
                "air of the tomb swirl above you, as if disturbed " +
                "by something large moving.\n"));
    }

}

