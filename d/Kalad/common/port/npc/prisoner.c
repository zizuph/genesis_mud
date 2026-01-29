inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
object prisoner;
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("seville");
    add_name("prisoner");
    set_race_name("human");
    set_adj("tortured");
    set_long("This pitiful excuse for a human being looks to have been beaten "+
      "nearly to death. Lacerations on his neck appear to be the result of "+
      "continuously being chained to the wall. His upper torso is bare of "+
      "clothing, leaving him exposed to the damp, disease-festering environment "+
      "of this cell. His eyes seem to beg for an end to this living hell.\n");
    set_stats(({15,10,10,25,25,5}));
    set_alignment(1000);
    set_act_time(6);
    add_act("stare");
    add_act("groan");
    add_act("sniff");
    add_act("say Please...end my suffering...\n");
    set_cact_time(3);
    add_cact("cry");
    add_cact("emote looks resigned to his fate.");
    set_knight_prestige(-10);
    set_title("the Tortured");
    add_speak("Please end my suffering...I beg of you...\n");
}
end(string s)
{
    notify_fail("What do you want to end?\n");

    if(s!="suffering"&&s!="hell")
	return 0;

    seteuid(getuid(TO));

    TP->catch_msg("You raise your fist aloft and repeatedly strike the prisoner upon the skull...\n");

    if(!TP->test_bit("Kalad",0,7))
    {
	TP->add_exp(2500);
	TP->set_bit(0,7);
	TP->catch_msg("You feel more experienced!\n");
    }

    say(QCTNAME(TP)+" raises " + TP->query_possessive() + " fist aloft and repeatedly strikes the prisoner upon the skull...\n");

    set_alarm(5.0,0.0,"smashed");

    return 1;
}

smashed()
{
    object remains;
    tell_room(E(TO),"The prisoner is smashed into a puddle of bloody gore!\n");
    remains = clone_object("/d/Kalad/common/port/obj/gore");
    remains -> move(environment(TO));
    if(prisoner = present("seville", environment(TP)))
    {
	prisoner -> remove_object();
    }
}
init_living()
{
    ::init_living();
    add_action("end","end");
}
