#pragma strict_types

#include "../defs.h"
#include "../../local.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <cmdparse.h>
#include DL_CLOCK

inherit TEMPLE + "std_base";
inherit "/lib/commands";

string
sun_desc()
{
    string *moons;

    moons = ({ (GET_MOON_PHASE(SOLINARI) == "new" ? 0 :
        "the " + GET_MOON_PHASE(SOLINARI) + " " + capitalize(SOLINARI)),
        (GET_MOON_PHASE(LUNITARI) == "new" ? 0 :
        "the " + GET_MOON_PHASE(LUNITARI) + " " + capitalize(LUNITARI)),
        (this_player()->query_priest_level() == GUILD_LEVEL_HIGH_PRIEST &&
        GET_MOON_PHASE(NUITARI) != "new" ? "you see a faint " +
        "outline from what must be the mythical " + capitalize(NUITARI) : 0) });

    moons -= ({ 0 });        

/*        
        20 april 12-16
        verksg 5
        22 april 18-21
        23 april 10-16 
  */  
    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            return "over which " + (sizeof(moons) ? COMPOSITE_WORDS(moons) +
                " cast their pale glow on the dark landscape." : "you " +
                "notice the lack of any moons which makes the night " +
                "dark indeed.");
        case TOD_DAWN:
            return "over which the sun is about to come up, basking " +
                "the sky in a multitude of colours in the range of " +
                "orange and yellow.";
        case TOD_DAY:
            return "over which the sun " + (CLOCK->query_hour() < 11 ?
                "is speeding towards zenith" : (CLOCK->query_hour() > 13 ?
                "is slowly descending" : "is at zenith")) + ".";
        case TOD_TWILIGHT:
            return "over which the sun is settling, slowly disappearing " +
                "behind its ridge while drawing the curtain that is " +
                "darkness over the sky.";
    }
}

void
create_temple_room()
{
    set_short("On a stone balcony overlooking Neraka");
    set_long("This is a large stone balcony situated at the very top " +
        "of a spiraling tower of the temple. It is semi-circular with " +
        "the railing also made of stone. To the southwest is an archway " +
        "which leads into the tower. Looking around, you notice the " +
        "extraordinary view from up here.\n");

    add_item(({"large stone balcony", "stone balcony", "large balcony",
        "balcony"}), "Semi-circular it extends about the length of a " +
        "man from the archway to its railing. The surface is smooth " +
        "and made of stone.\n");
    add_item(({"railing"}), "Following the outer edges of the balcony " +
        "is a stone railing keeping you from accidently falling off. " +
        "After all, it would be certain death to do so unless you " +
        "can fly.\n");
    add_item(({"tower", "spiraling tower"}), "As it spirals upwards " +
        "to the sky about as high as a tall pine tree, you are " +
        "awestruck by the sheer size of the temple. While most of it " +
        "is blocked behind that very tower, you can still see some " +
        "other towers of similar fashion over its edges.\n");
    add_item("view", "You can overlook most of the city from here. " +
        "The southern and western parts are blocked by the temple " +
        "itself which reaches further up, almost touching the sky. " +
        "Army camps spread out beyond the citywalls, behind them " +
        "the plains and in the horizon a mountain range stretches for " +
        "as far as you can see, @@sun_desc@@\n");
    add_item(({"army camps", "camps"}), "There is a great activity " +
        "below to the northeast where the black dragonarmy has set up " +
        "camp and also to the southeast where you see blue banners " +
        "twisting and turning in the wind.\n");
    add_item(({"city walls", "citywalls"}), "The citywalls run twofold " +
        "along the edges of the city core, with guard towers built into " +
        "the outer one every once in a while.\n");
    add_item("plains", "The plains beyond the city proper are desolate " +
        "save for the occasional tree struggling for survival.\n");
    add_item(({"mountains", "mountain range"}), "Wrapping up the visible " +
        "area in a blanket is the mountain range at the horizon.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(NERAKA_I_IS_TEMPLE_ROOF, 1);

    add_exit( LVLFIVE + "stair5.c", "southwest" );
}

int
do_throw(string arg)
{
    object *oblist;

    if (!arg || !strlen(arg))
    {
        notify_fail("Throw who off the balcony?\n");
        return 0;
    }
    
    if (!parse_command(arg, environment(this_player()),
        "[the] %l [off] [the] 'balcony'", oblist))
    {
        notify_fail("Throw who off the balcony?\n");
        return 0;
    }
    
    oblist = NORMAL_ACCESS(oblist, 0, 0);
    
    if (!sizeof(oblist) || oblist[0] == this_player())
    {
        notify_fail("Throw who off the balcony?\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    write_file("/d/Ansalon/log/pot/sadism",
        capitalize(this_player()->query_real_name()) + " " +
        "wants to see " + COMPOSITE_WORDS(map(oblist->query_real_name(),
        capitalize)) + " dead.\n");

    write("Are you truly that sadistic that you throw " +
        COMPOSITE_LIVE(oblist) + " off the balcony?\n");
    targetbb(" gets something gleaming in " +
        HIS(this_player()) + " eyes as " + HE(this_player()) + " looks " +
        "at you and measures the way down, off the railing.", oblist);
    all2actbb(" gets something gleaming in " +
        HIS(this_player()) + " eyes as " + HE(this_player()) + " looks " +
        "at ", oblist, " and measures the way down, off the railing.");
 
    return 1;
}

int
do_jump(string arg)
{
    if (!arg || !strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (!parse_command(arg, this_player(), "[off] [the] 'balcony'"))
    {
        notify_fail(capitalize(query_verb()) + " off what?\n");
        return 0;
    }
    
    if ((time() - this_player()->query_prop("_pot_i_live_i_am_stupid")) > 60)
    {
        this_player()->add_prop("_pot_i_live_i_am_stupid", time());
        
        write("You pause for a moment to reconsider suicide.\n");
        say(QCTNAME(this_player()) + " pauses for a moment.\n");
        return 1;
    }

    write("You " + query_verb() + " off the balcony.\n");
    say(QCTNAME(this_player()) + " " + query_verb() + " off the balcony.\n");
    write("You plummet to a certain death.\n");

    /* So that the one jumping off won't get the message
     */
    (NERAKA_ADMIN)->tell_neraka(({"inner/", "outer/"}),
        "You hear the terrified screams of someone who is falling " +
        "to a certain death coming from the temple.\n", 1);
    tell_room(NINNER + "s25", "Falling from above, " +
        QTNAME(this_player()) + " lands on the ground with " +
        "a sickening sound as bones break.\n");

    this_player()->remove_prop("_pot_i_live_i_am_stupid");
    this_player()->move(NINNER + "s25");
    this_player()->set_hp(0);
    this_player()->do_die(this_object());

    /* So that the one jumping off (who now is at s25) won't get the message
     */
    (NERAKA_ADMIN)->tell_neraka("temple/lvl5/",
        "You hear a voice screaming terrifiedly from below the balcony, " +
        "fading lower and lower until you hear a sickening thump.\n", 3);

    return 1;
}

void
init()
{
    ::init();
    
    add_action(do_throw, "throw");
    add_action(do_jump, "jump");
    add_action(do_jump, "leap");
}
