inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"

void
create_object()
{
    ::create_object();
    set_name("_fang_");
    add_name("badge");
    set_adj("blood-red");
    set_short("blood-red badge");
    set_pshort("blood-red badges");
    set_long("This blood-red badge is in the shape of a sharp fang. You "+
      "are to wear it on your chest, to show your devotion to the cause "+
      "of the Red Fang.\n"+
      "Try 'fanghelp' to get information on your commands.\n");
    add_prop(OBJ_I_VALUE,1440);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,250);
    add_prop(OBJ_M_NO_DROP,"You cannot be rid of this unless you leave "+
      "the Red Fang Guild.\n");
    add_prop(OBJ_M_NO_SELL,"You dare not sale your badge of honor.\n");
    set_alarm(3.0,0.0,"message");

    set_slots(A_CHEST);
}

void
message(object ob)
{
    tell_object(ob,"Hail Red Fang Warrior! Power to the Goblin Race!\n");
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (to->query_wiz_level())
	return;

    if(to->query_race_name() != "goblin")
    {
	to->catch_msg("Your badge is blown up as you have betrayed the "+
	  "Red Fang by changing your race!\n");
	remove_object();
    }

    if(living(to))
	message(to);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
