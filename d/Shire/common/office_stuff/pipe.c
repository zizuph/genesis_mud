inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"

#define SMOKE_PARALYZE  MASTER_OB(TO) + "_para"
#define SOULDESC(x)   (TP->add_prop(LIVE_S_SOULEXTRA, x))

//   Protoypes
void puff(object player);

int alarm_id, stage;

void
create_object()
{
    set_name("pipe");
    add_name("_shire_office_pipe");
    set_short("hand-carved dragon-shaped pipe");
    set_adj(({"hand-carved","carved","dragon-shaped","dragon"}));
    set_long("A beautifully hand-carved pipe which has been shaped into "+
      "a dragon. It's head forms the end of this pipe, where smoke "+
      "escapes from it's nostrils.  Much skill and " +
      "effort has gone into the making of this smoking pipe, you " +
      "marvel at the craftsmanship and wonder who this pipe belongs to.\n"+
      "You notice some words scribbled on the side of the pipe.\n");

    add_item("words","They say 'smoke pipe'.\n");

    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 7);
    add_prop(OBJ_I_VALUE, 100);
}

void
init()
{
    ::init();
    add_action("do_smoke", "smoke");
}

int
do_smoke(string str)
{
    if (alarm_id)
    {
	notify_fail("But you are already smoking the "+short()+"!\n");
	return 0;
    }
    if (ENV(TO) != TP)
    {
	notify_fail("You must carry the pipe in order to smoke it.\n");
	return 0;
    }
    if (str != "pipe")
    {
	notify_fail("Smoke the pipe maybe?\n");
	return 0;
    }
    alarm_id = set_alarm(5.0,itof(10 + random(6)), &puff(TP));
    stage = 0;
    say(QCTNAME(TP) +
      " stuffs some tobacco into " + HIS_HER(TP) + " "+short()+" and then " +
      "proceeds to light it. " + CAP(HE_SHE(TP)) + " inhales deeply and " +
      "smiles happily as " + HE_SHE(TP) + " exhales the wonderful smoke.\n");
    SOULDESC("smoking a "+short());
    write("You quickly fill your "+short()+" with some available tobacco " +
      "and imediately light it. As you start to inhale the wonderful " +
      "smoke, you smile happily, thoroughly enjoying it.\n");
    return 1;
}

void
puff(object player)
{
    if (ENV(TO) != player)
    {
	remove_alarm(alarm_id);
	return;
    }
    switch(stage)
    {
    case 0:
	player->catch_msg("You take a puff from your "+short()+".\n");
	say(QCTNAME(player)+" takes a puff from "+HIS_HER(player)+            
	  " "+short()+".\n");
	break;
    case 1:
	player->catch_msg("You take a puff from your "+short()+", the smoke "+
	  "filling you with a strange sensation.\n");
	say(QCTNAME(player)+" takes a puff from "+HIS_HER(player)+
	  " "+short()+".\n");
	break;
    default:
	remove_alarm(alarm_id);
	alarm_id = 0;
	setuid(); seteuid(getuid());
	clone_object(SMOKE_PARALYZE)->move(player, 1);
	break;
    }
    stage += 1;
}
